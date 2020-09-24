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
					String projectPath = TPath::GetDirectoryName(project->FileName);
					messages.AddSeparator();
					messages.AddTitle("Converting files to UTF8 BOM in " + projectPath);
					TStringDynArray cppFiles = TDirectory::GetFiles(projectPath, "*.cpp", TSearchOption::soAllDirectories);
					TStringDynArray hFiles = TDirectory::GetFiles(projectPath, "*.h", TSearchOption::soAllDirectories);
					String filesCount = IntToStr(cppFiles.Length + hFiles.Length);
					int processedFilesCount = 0;
					ConvertingResult result = ConvertingResult::Ok;
					for (int i = 0; i < cppFiles.Length; ++i)
					{
						++processedFilesCount;
						messages.AddSubInfo(IntToStr(processedFilesCount) + "/" + filesCount + " Checking file " + cppFiles[i]);
						result = ToUTF8Bom(cppFiles[i]);
						if (result == ConvertingResult::Ok)
							messages.AddSubInfo("\tFile converted");
						else if (result == ConvertingResult::Failed)
						{
							retVal = false;
							messages.AddError("Converting \"" + cppFiles[i] + "\" failed");
						}
					}

					for (int i = 0; i < hFiles.Length; ++i)
					{
						++processedFilesCount;
						messages.AddSubInfo(IntToStr(processedFilesCount) + "/" + filesCount + " Checking file " + hFiles[i]);
						result = ToUTF8Bom(hFiles[i]);
						if (result == ConvertingResult::Ok)
							messages.AddSubInfo("\tFile converted");
						else if (result == ConvertingResult::Failed)
						{
							retVal = false;
							messages.AddError("Converting \"" + hFiles[i] + "\" failed");
						}
					}

					messages.AddInfo("Converting files to UTF8 BOM finished");
					if (!IOTAEditExtension::IsAnyFileModified())
						project->Refresh(false);

					MessageBox(0x0, "Converting files to UTF8 BOM finished", AnsiString(Application->Title).c_str(), MB_OK);
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
