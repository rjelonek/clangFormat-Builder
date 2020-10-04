#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "Theming.h"
#include <ToolsAPI.hpp>

namespace ClangFormat
{
	Theming::Theming() : themingSupported(__BORLANDC__ >= 0x0730) {}

	void Theming::RegisterFormClass(TMetaClass *classType, TComponent *component)
	{
		if (classType)
		{
#if __BORLANDC__ >= 0x0730
#if __BORLANDC__ >= 0x0750 // Breaking change to the Open Tools API - They fixed the wrongly defined interface
			_di_IOTAIDEThemingServices themingServices = 0x0;
#else
			_di_IOTAIDEThemingServices250 themingServices = 0x0;
#endif
			if (BorlandIDEServices && BorlandIDEServices->Supports(themingServices))
			{
				if (themingServices->IDEThemingEnabled)
				{
					themingServices->RegisterFormClass(classType);
					if (component)
						themingServices->ApplyTheme(component);
				}
			}
#endif
		}
	}

	bool Theming::IsThemingSupported()
	{
		return themingSupported;
	}
} // namespace ClangFormat
