#pragma hdrstop

#include "ClangFormatWrapper.h"
#include <System.SysUtils.hpp>
#include "Settings.h"
#include <System.IOUtils.hpp>
#include "Pipe.h"
#include <System.RegularExpressions.hpp>

namespace ClangFormat
{
	ClangFormatWrapper::ClangFormatWrapper(boost::shared_ptr<Configuration::Settings> settings) : settings(settings) {}

	bool ClangFormatWrapper::FormatSource(const String &textToFormat, String &output, String &errorMessage, const String pathFile, String style,
										  String fallbackStyle, unsigned int startLine, unsigned int endLine)
	{
		bool retVal = false;
		output = EmptyStr;
		errorMessage = EmptyStr;
		if (!settings->general.clangFormatPath.IsEmpty() && !textToFormat.IsEmpty() && !style.IsEmpty())
		{
			String styleParam = " --style=" + style;
			String fallbackStyleParam = " --fallback-style=" + fallbackStyle;
			String fileNameParam = EmptyStr;
			String startupDirectory = EmptyStr;
			if (!pathFile.IsEmpty())
			{
				fileNameParam = " --assume-filename=\"" + TPath::GetFileName(pathFile) + "\"";
				startupDirectory = TPath::GetDirectoryName(pathFile);
			}

			String linesParam = EmptyStr;
			if (startLine != 0 && endLine != 0)
				linesParam = " --lines=" + UIntToStr(startLine) + ":" + UIntToStr(endLine);

			Pipe pipe;
			if (pipe.Open(settings->general.clangFormatPath + styleParam + fallbackStyleParam + fileNameParam + linesParam, startupDirectory))
			{
				if (pipe.Write(textToFormat))
					pipe.Read(output);

				pipe.ReadError(errorMessage);
				retVal = errorMessage.IsEmpty();
			}

			pipe.Close();
		}

		return retVal;
	}

	String ClangFormatWrapper::GetVersion()
	{
		String version = EmptyStr;
		ClangFormat::Pipe pipe;
		if (pipe.Open(settings->general.clangFormatPath + " --version", ""))
		{
			String versionTemp;
			pipe.Read(versionTemp);
			TMatch result = TRegEx::Match(versionTemp, "\\d+.\\d+.\\d+");
			if (result.Success)
				version = result.Value;
		}

		pipe.Close();
		return version;
	}
} // namespace ClangFormat
