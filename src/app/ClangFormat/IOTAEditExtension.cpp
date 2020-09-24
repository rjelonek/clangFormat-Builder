#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "IOTAEditExtension.h"

namespace ClangFormat
{
	bool IOTAEditExtension::IsAnyFileModified()
	{
		bool retVal = false;
		_di_IOTAModuleServices moduleServices = 0x0;
		if (BorlandIDEServices && BorlandIDEServices->Supports(moduleServices))
		{
			for (int moduleIndex = 0; moduleIndex < moduleServices->ModuleCount; ++moduleIndex)
			{
				_di_IOTAModule module = moduleServices->Modules[moduleIndex];
				if (module && module->ModuleFileCount > 0)
					for (int fileIndex = 0; fileIndex < module->ModuleFileCount; ++fileIndex)
						if (module->ModuleFileEditors[fileIndex]->Modified)
						{
							retVal = true;
							break;
						}
			}
		}

		return retVal;
	}
} // namespace ClangFormat
