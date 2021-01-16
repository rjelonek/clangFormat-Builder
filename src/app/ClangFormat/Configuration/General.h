#ifndef GeneralH
#define GeneralH

#include <System.hpp>

namespace ClangFormat
{
	namespace Configuration
	{
		class General
		{
		  private:
			String GetFirstFoundClangFormat();

		  public:
			General();
			void SetDefaultValues();

			bool autoFormatting;
			String style;
			String fallbackStyle;
			String clangFormatPath;
		};
	}; // namespace Configuration
};	   // namespace ClangFormat

#endif
