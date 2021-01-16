#ifndef ClangFormatWrapperH
#define ClangFormatWrapperH

#include "Settings.h"
#include <System.hpp>
#include <boost/shared_ptr.hpp>

namespace ClangFormat
{
	class ClangFormatWrapper
	{
	  private:
		boost::shared_ptr<Configuration::Settings> settings;

	  public:
		ClangFormatWrapper(boost::shared_ptr<Configuration::Settings> settings);
		bool FormatSource(const String &textToFormat, String &output, String &errorMessage, const String pathFile, String style, String fallbackStyle, unsigned int startLine, unsigned int endLine);
		String GetVersion();
	};
} // namespace ClangFormat

#endif
