#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "CodeFormatter.h"
#include "Settings.h"
#include "IOTAEditExtension.h"

namespace ClangFormat
{
	CodeFormatter::CodeFormatter(boost::shared_ptr<Configuration::Settings> settings) : settings(settings) {}

	String CodeFormatter::GetText(_di_IOTASourceEditor sourceEditor, int &editorSize)
	{
		String retVal = "";
		editorSize = 0;
		if (sourceEditor)
		{
			_di_IOTAEditReader reader = sourceEditor->CreateReader();
			if (reader)
			{
				const int maxReadSize = 31 * 1024 + 1;
				char buffer[maxReadSize];
				std::memset(buffer, 0x0, sizeof(char) * maxReadSize);
				int startPos = 0;
				int readSize = -1;
				while (readSize != 0)
				{
					readSize = reader->GetText(startPos, buffer, maxReadSize - 1);
					if (readSize > 0)
					{
						retVal += UTF8ToString(buffer);
						std::memset(buffer, 0x0, sizeof(char) * maxReadSize);
						startPos += readSize;
					}
				}

				editorSize = startPos;
				reader->Release();
				reader = 0x0;
			}
		}
		return retVal;
	}

	void CodeFormatter::SetText(_di_IOTASourceEditor sourceEditor, int editorSize, String textToSet)
	{
		_di_IOTAEditWriter writer = sourceEditor->CreateUndoableWriter();
		if (writer)
		{
			try
			{
				writer->DeleteTo(editorSize);
				writer->Insert(UTF8Encode(textToSet).c_str());
			}
			catch (Exception &ex)
			{
				messages.AddError(ex.Message, __FUNC__);
			}

			writer->Release();
			writer = 0x0;
		}
	}

	bool CodeFormatter::FormatSource(String filePath, String style, String fallbackStyle)
	{
		bool retVal = false;
		if (!settings->general.clangFormatPath.IsEmpty() && TFile::Exists(filePath) && !style.IsEmpty())
		{
			SHELLEXECUTEINFOW ShExecInfo;
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = 0x0;
			ShExecInfo.lpVerb = L"Open";
			ShExecInfo.lpFile = settings->general.clangFormatPath.c_str();
			ShExecInfo.lpParameters = String("--style=" + style + " --fallback-style=" + fallbackStyle + " -i \"" + filePath + "\"").c_str();
			ShExecInfo.lpDirectory = 0x0;
			ShExecInfo.nShow = SW_HIDE;
			ShExecInfo.hInstApp = 0x0;
			if (ShellExecuteExW(&ShExecInfo))
			{
				WaitForSingleObject(ShExecInfo.hProcess, 30000);
				DWORD dwExitCode;
				GetExitCodeProcess(ShExecInfo.hProcess, &dwExitCode);

				if (dwExitCode == STILL_ACTIVE)
					TerminateProcess(ShExecInfo.hProcess, 1);
				else if (dwExitCode == 0)
					retVal = true;
			}
		}

		return retVal;
	}

	void CodeFormatter::GetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList)
	{
		bookmarkList.clear();
		if (sourceEditor && sourceEditor->EditViewCount > 0)
		{
			_di_IOTAEditView editView = sourceEditor->EditViews[0];
			for (int i = 0; i < 10; ++i)
			{
				if (editView->BookmarkPos[i].Line > 0)
					bookmarkList[i] = sourceEditor->EditViews[0]->BookmarkPos[i];
			}
		}
	}

	void CodeFormatter::SetBookmarkList(_di_IOTASourceEditor sourceEditor, std::map<int, TOTACharPos> &bookmarkList)
	{
		if (!bookmarkList.empty() && sourceEditor && sourceEditor->EditViewCount > 0)
		{
			_di_IOTAEditView editView = sourceEditor->EditViews[0];
			TOTAEditPos lastCursorPosition = editView->CursorPos;
			for (std::map<int, TOTACharPos>::iterator bookmark = bookmarkList.begin(); bookmark != bookmarkList.end(); ++bookmark)
			{
				TOTAEditPos bookmarkPosition;
				bookmarkPosition.Col = bookmark->second.CharIndex;
				bookmarkPosition.Line = bookmark->second.Line;
				editView->SetCursorPos(bookmarkPosition);
				editView->BookmarkToggle(bookmark->first);
			}

			editView->SetCursorPos(lastCursorPosition);
		}
	}

	FormatResult CodeFormatter::FormatSource(_di_IOTASourceEditor sourceEditor)
	{
		FormatResult retVal = FormatResult::FormattingFailed;
		if (sourceEditor && !settings->general.style.IsEmpty())
		{
			String extension = TPath::GetExtension(sourceEditor->FileName).LowerCase();
			if (extension == ".cpp" || extension == ".h")
			{
				messages.AddInfo("Formatting \"" + sourceEditor->FileName + "\"");
				int editorSize = 0;
				String textFromEditor = GetText(sourceEditor, editorSize);
				if (!textFromEditor.IsEmpty())
				{
					String tempFile = sourceEditor->FileName + ".temp";
					try
					{
						TFile::WriteAllText(tempFile, textFromEditor, TEncoding::UTF8);
						if (FormatSource(tempFile, settings->general.style, settings->general.fallbackStyle))
						{
							String formattedText = TFile::ReadAllText(tempFile, TEncoding::UTF8);
							std::map<int, TOTACharPos> bookmarkList;
							GetBookmarkList(sourceEditor, bookmarkList);
							SetText(sourceEditor, editorSize, formattedText.Trim());
							SetBookmarkList(sourceEditor, bookmarkList);
							retVal = FormatResult::Ok;
						}
						else
							messages.AddError("Formatting \"" + sourceEditor->FileName + "\" failed");

						if (TFile::Exists(tempFile))
							TFile::Delete(tempFile);
					}
					catch (Exception &ex)
					{
						messages.AddError(ex.Message + " (\"" + sourceEditor->FileName + "\")", __FUNC__);
					}
				}
				else
					retVal = FormatResult::Ok;
			}
			else
			{
				retVal = FormatResult::NotSupportedFile;
				messages.AddError("File \"" + sourceEditor->FileName + "\" is not supported");
			}
		}
		else if (!sourceEditor)
		{
			retVal = FormatResult::EditorNotAvailable;
			messages.AddError("Source editor is not available");
		}

		return retVal;
	}

	FormatResult CodeFormatter::FormatCurrentSource()
	{
		FormatResult retVal = FormatResult::EditorNotAvailable;
		_di_IOTAModuleServices moduleServices = 0x0;
		if (BorlandIDEServices && BorlandIDEServices->Supports(moduleServices))
		{
			_di_IOTAModule module = moduleServices->CurrentModule();
			if (module)
			{
				_di_IOTAEditor editor = module->CurrentEditor;
				if (editor)
				{
					_di_IOTASourceEditor fileSourceEditor;
					if (::Supports(editor, __uuidof(IOTASourceEditor), &fileSourceEditor))
						retVal = FormatSource(fileSourceEditor);
					else
						messages.AddError("Source editor for file \"" + editor->FileName + "\" is not available");
				}
			}
		}

		return retVal;
	}

	bool CodeFormatter::FormatAllSources()
	{
		bool retVal = true;
		_di_IOTAModuleServices moduleServices = 0x0;
		if (BorlandIDEServices && BorlandIDEServices->Supports(moduleServices))
		{
			_di_IOTAProjectGroup projectGroup = moduleServices->MainProjectGroup;
			if (projectGroup)
			{
				_di_IOTAProject project = projectGroup->ActiveProject;
				if (project)
				{
					String projectPath = TPath::GetDirectoryName(project->FileName);
					messages.AddSeparator();
					messages.AddTitle("Formatting all sources in \"" + projectPath + "\"");
					if (!settings->general.style.IsEmpty())
					{
						TStringDynArray cppFiles = TDirectory::GetFiles(projectPath, "*.cpp", TSearchOption::soAllDirectories);
						TStringDynArray hFiles = TDirectory::GetFiles(projectPath, "*.h", TSearchOption::soAllDirectories);
						String filesCount = IntToStr(cppFiles.Length + hFiles.Length);
						int processedFilesCount = 0;
						for (int i = 0; i < cppFiles.Length; ++i)
						{
							++processedFilesCount;
							messages.AddSubInfo(IntToStr(processedFilesCount) + "/" + filesCount + " \"" + cppFiles[i] + "\"");
							if (!FormatSource(cppFiles[i], settings->general.style, settings->general.fallbackStyle))
							{
								retVal = false;
								messages.AddError("Formatting \"" + cppFiles[i] + "\" failed");
							}
						}

						for (int i = 0; i < hFiles.Length; ++i)
						{
							++processedFilesCount;
							messages.AddSubInfo(IntToStr(processedFilesCount) + "/" + filesCount + " \"" + hFiles[i] + "\"");
							if (!FormatSource(hFiles[i], settings->general.style, settings->general.fallbackStyle))
							{
								retVal = false;
								messages.AddError("Formatting \"" + hFiles[i] + "\" failed");
							}
						}

						messages.AddInfo("Formatting all sources finished");
						if (!IOTAEditExtension::IsAnyFileModified())
							project->Refresh(false);

						MessageBox(0x0, "Formatting all sources finished", AnsiString(Application->Title).c_str(), MB_OK);
					}
				}
			}
		}

		return retVal;
	}
} // namespace ClangFormat
