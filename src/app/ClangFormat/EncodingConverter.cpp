#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "EncodingConverter.h"
#include "IOTAEditExtension.h"
#include <System.WideStrUtils.hpp>

namespace ClangFormat
{
	TByteDynArray SystemExtension::Concat(TByteDynArray &first, TByteDynArray &second)
	{
		TByteDynArray retVal;
		retVal.Length = first.Length + second.Length;
		for (int i = 0; i < first.Length; ++i)
			retVal[i] = first[i];

		int newIndex = first.Length;
		for (int i = 0; i < second.Length; ++i, ++newIndex)
			retVal[newIndex] = second[i];

		return retVal;
	}

	bool EncodingConverter::AllFilesToUTF8Bom()
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
					messages.AddTitle("Converting files to UTF8 BOM in project " + TPath::GetFileNameWithoutExtension(project->FileName));

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
					ConvertingResult result = ConvertingResult::Ok;
					for (int fileIndex = 0; fileIndex < filteredProjectFiles->Count; ++fileIndex)
					{
						messages.AddSubInfo(IntToStr(fileIndex + 1) + "/" + filesCount + " Checking file " + filteredProjectFiles->Strings[fileIndex]);
						result = ToUTF8Bom(filteredProjectFiles->Strings[fileIndex]);
						if (result == ConvertingResult::Ok)
							messages.AddSubInfo("\tFile converted");
						else if (result == ConvertingResult::Failed)
						{
							retVal = false;
							messages.AddError("Converting \"" + filteredProjectFiles->Strings[fileIndex] + "\" failed");
						}
					}

					messages.AddInfo("Converting files to UTF8 BOM in project finished");
					if (!IOTAEditExtension::IsAnyFileModified())
						project->Refresh(false);

					MessageBox(0x0, L"Converting files to UTF8 BOM in project finished", Application->Title.c_str(), MB_OK);
				}
			}
		}

		return retVal;
	}

	ConvertingResult EncodingConverter::ToUTF8Bom(String filePath)
	{
		ConvertingResult retVal = ConvertingResult::Ok;
		try
		{
			TByteDynArray rawContent = TFile::ReadAllBytes(filePath);
			TEncoding *encoding = 0x0;
			int offset = TEncoding::GetBufferEncoding(rawContent, encoding);
			if (encoding != TEncoding::UTF8)
			{
				TByteDynArray bom = TEncoding::UTF8->GetPreamble();
				if (IsUTF8String(encoding->GetString(rawContent)))
					TFile::WriteAllBytes(filePath, SystemExtension::Concat(bom, rawContent));
				else
				{
					TByteDynArray convertedContent = TEncoding::Convert(encoding, TEncoding::UTF8, rawContent, offset, rawContent.Length - offset);
					TFile::WriteAllBytes(filePath, SystemExtension::Concat(bom, convertedContent));
				}
			}
			else
				retVal = ConvertingResult::AlreadySavedWithDesiredEncoding;
		}
		catch (Exception &ex)
		{
			messages.AddError(ex.Message, __FUNC__);
			retVal = ConvertingResult::Failed;
		}

		return retVal;
	}
} // namespace ClangFormat
