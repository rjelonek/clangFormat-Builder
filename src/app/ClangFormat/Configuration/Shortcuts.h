#ifndef ShortcutsH
#define ShortcutsH

#include <System.IniFiles.hpp>

namespace ClangFormat
{
	namespace Configuration
	{
		class Shortcuts
		{
		  public:
			Shortcuts();
			void SetDefaultValues();

			TShortCut autoFormatting;
			TShortCut formatAllSources;
			TShortCut formatSelectedLines;
		};
	}; // namespace Configuration
};	   // namespace ClangFormat

#endif
