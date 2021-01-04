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
		return FormatSource(filePath, style, fallbackStyle, 0, 0);
	}

	bool CodeFormatter::FormatSource(String filePath, String style, String fallbackStyle, unsigned int startLine, unsigned int endLine)
	{
		bool retVal = false;
		if (!settings->general.clangFormatPath.IsEmpty() && TFile::Exists(filePath) && !style.IsEmpty())
		{
			String styleParam = " --style=" + style;
			String fallbackStyleParam = " --fallback-style=" + fallbackStyle;
			String filePathParam = " -i \"" + filePath + "\"";
			String linesParam = "";
			if (startLine != 0 && endLine != 0)
				linesParam = " --lines=" + UIntToStr(startLine) + ":" + UIntToStr(endLine);

			SHELLEXECUTEINFOW ShExecInfo;
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = 0x0;
			ShExecInfo.lpVerb = L"Open";
			ShExecInfo.lpFile = settings->general.clangFormatPath.c_str();
			ShExecInfo.lpParameters = String(styleParam + fallbackStyleParam + filePathParam + linesParam).c_str();
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

	FormatResult CodeFormatter::FormatSource(_di_IOTASourceEditor sourceEditor, unsigned int startLine, unsigned int endLine)
	{
		FormatResult retVal = FormatResult::FormattingFailed;
		if (sourceEditor && !settings->general.style.IsEmpty())
		{
			String extension = TPath::GetExtension(sourceEditor->FileName).LowerCase();
			if (extension == ".cpp" || extension == ".h")
			{
				String lines = "";
				if (startLine != 0 && endLine != 0)
					lines = " --lines=" + UIntToStr(startLine) + ":" + UIntToStr(endLine);

				messages.AddInfo("Formatting \"" + sourceEditor->FileName + "\"" + lines);
				int editorSize = 0;
				String textFromEditor = GetText(sourceEditor, editorSize);
				if (!textFromEditor.IsEmpty())
				{
					String tempFile = sourceEditor->FileName + ".temp";
					try
					{
						TFile::WriteAllText(tempFile, textFromEditor, TEncoding::UTF8);
						if (FormatSource(tempFile, settings->general.style, settings->general.fallbackStyle, startLine, endLine))
						{
							String formattedText = TFile::ReadAllText(tempFile, TEncoding::UTF8);
							std::map<int, TOTACharPos> bookmarkList;
							GetBookmarkList(sourceEditor, bookmarkList);
							SetText(sourceEditor, editorSize, formattedText.Trim());
							SetBookmarkList(sourceEditor, bookmarkList);
							retVal = FormatResult::Ok;
						}
						else
							messages.AddError("Formatting \"" + sourceEditor->FileName + "\"" + lines + " failed");

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
		return FormatSource(sourceEditor, 0, 0);
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

	FormatResult CodeFormatter::FormatSelectedLines()
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
						retVal = FormatSource(fileSourceEditor, fileSourceEditor->BlockStart.Line, fileSourceEditor->BlockAfter.Line);
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
					messages.AddSeparator();
					messages.AddTitle("Formatting all sources in project \"" + TPath::GetFileNameWithoutExtension(project->FileName) + "\"");
					if (!settings->general.style.IsEmpty())
					{
						std::unique_ptr<TStringList> projectFiles(new TStringList(0x0));
						std::unique_ptr<TStringList> filteredProjectFiles(new TStringList(0x0));
						project->GetCompleteFileList(projectFiles.get());
						for (int fileIndex = 0; fileIndex < projectFiles->Count; ++fileIndex)
						{
							String extension = TPath::GetExtension(projectFiles->Strings[fileIndex]).LowerCase();
							if (extension == ".cpp" || extension == ".h")
								filteredProjectFiles->Add(projectFiles->Strings[fileIndex]);
						}

						String filesCount = IntToStr(filteredProjectFiles->Count);
						for (int fileIndex = 0; fileIndex < filteredProjectFiles->Count; ++fileIndex)
						{
							messages.AddSubInfo(IntToStr(fileIndex + 1) + "/" + filesCount + " \"" + filteredProjectFiles->Strings[fileIndex] + "\"");
							if (!FormatSource(filteredProjectFiles->Strings[fileIndex], settings->general.style, settings->general.fallbackStyle))
							{
								retVal = false;
								messages.AddError("Formatting \"" + filteredProjectFiles->Strings[fileIndex] + "\" failed");
							}
						}

						messages.AddInfo("Formatting all sources in project finished");
						if (!IOTAEditExtension::IsAnyFileModified())
							project->Refresh(false);

						MessageBox(0x0, L"Formatting all sources in project finished", Application->Title.c_str(), MB_OK);
					}
				}
			}
		}

		return retVal;
	}
} // namespace ClangFormat
