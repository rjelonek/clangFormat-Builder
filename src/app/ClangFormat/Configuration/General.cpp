#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "General.h"
#include "Message.h"
#include <System.RegularExpressions.hpp>

namespace ClangFormat
{
	namespace Configuration
	{
		General::General()
		{
			SetDefaultValues();
		}

		void General::SetDefaultValues()
		{
			autoFormatting = true;
			style = "File";
			fallbackStyle = "None";
			clangFormatPath = GetFirstFoundClangFormat();
		}

		String General::GetFirstFoundClangFormat()
		{
			String retVal = "";
			String environmentPath = GetEnvironmentVariable("PATH");
			TRegExOptions regExOptions = TRegExOptions() << TRegExOption::roIgnoreCase;
			TMatch result = TRegEx::Match(environmentPath, "[^;]+", regExOptions);
			while (result.Success)
			{
				try
				{
					if (TFile::Exists(result.Value + "\\clang-format.exe"))
					{
						retVal = result.Value + "\\clang-format.exe";
						break;
					}
				}
				catch (Exception &ex)
				{
					ClangFormat::Message().AddError(ex.Message, __FUNC__);
				}

				result = result.NextMatch();
			}

			return retVal;
		}
	}; // namespace Configuration
};	   // namespace ClangFormat
