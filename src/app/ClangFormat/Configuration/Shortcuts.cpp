#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "Shortcuts.h"

namespace ClangFormat
{
	namespace Configuration
	{
		Shortcuts::Shortcuts()
		{
			SetDefaultValues();
		}

		void Shortcuts::SetDefaultValues()
		{
			autoFormatting = TextToShortCut("Alt+D");
			formatAllSources = TextToShortCut("Alt+A");
			formatSelectedLines = TextToShortCut("Alt+S");
		}
	}; // namespace Configuration
};	   // namespace ClangFormat
