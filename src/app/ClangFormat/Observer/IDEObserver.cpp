#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "IDEObserver.h"

namespace ClangFormat
{
	namespace Observer
	{
		IDEObserver::IDEObserver(boost::shared_ptr<Configuration::Settings> settings) : settings(settings)
		{
			observerIndex = -1;
			services = 0x0;
		}

		__fastcall IDEObserver::~IDEObserver()
		{
			for (std::map<_di_IOTAEditor, FileSourceObserver *>::iterator item = fileSourceObservers.begin(); item != fileSourceObservers.end();
				 ++item)
			{
				delete item->second;
				item->second = 0x0;
			}

			fileSourceObservers.clear();
			UnregisterIDE();
		}

		HRESULT __stdcall IDEObserver::QueryInterface(REFIID riid, void **ppv)
		{
			return TInterfacedObject::QueryInterface(riid, (void *)ppv);
		}

		ULONG __stdcall IDEObserver::AddRef()
		{
			return TInterfacedObject::_AddRef();
		}

		ULONG __stdcall IDEObserver::Release()
		{
			return TInterfacedObject::_Release();
		}

		void __fastcall IDEObserver::AfterConstruction() {}

		void __fastcall IDEObserver::BeforeDestruction() {}

		void __fastcall IDEObserver::AfterSave() {}

		void __fastcall IDEObserver::BeforeSave() {}

		void __fastcall IDEObserver::Destroyed() {}

		void __fastcall IDEObserver::Modified() {}

		void __fastcall IDEObserver::FileNotification(TOTAFileNotification NotifyCode, const System::UnicodeString FileName, bool &Cancel)
		{
			if (NotifyCode == ofnFileOpened || NotifyCode == ofnFileClosing)
			{
				_di_IOTAModuleServices moduleServices = 0x0;
				if (BorlandIDEServices && BorlandIDEServices->Supports(moduleServices))
				{
					for (int moduleIndex = 0; moduleIndex < moduleServices->ModuleCount; ++moduleIndex)
					{
						_di_IOTAModule module = moduleServices->Modules[moduleIndex];
						if (module && module->FileName == FileName && module->ModuleFileCount > 0)
							for (int fileIndex = 0; fileIndex < module->ModuleFileCount; ++fileIndex)
							{
								_di_IOTAEditor editor = module->ModuleFileEditors[fileIndex];
								if (NotifyCode == ofnFileOpened)
								{
									FileSourceObserver *fileSourceObserver = new FileSourceObserver(settings);
									if (fileSourceObserver->Register(editor))
										fileSourceObservers[editor] = fileSourceObserver;
									else
									{
										delete fileSourceObserver;
										fileSourceObserver = 0x0;
									}
								}
								else if (NotifyCode == ofnFileClosing)
								{
									std::map<_di_IOTAEditor, FileSourceObserver *>::iterator foundItem = fileSourceObservers.find(editor);
									if (foundItem != fileSourceObservers.end())
									{
										delete foundItem->second;
										foundItem->second = 0x0;
										fileSourceObservers.erase(foundItem);
									}
								}
							}
					}
				}
			}
		}

		void __fastcall IDEObserver::BeforeCompile(const _di_IOTAProject Project, bool &Cancel) {}

		void __fastcall IDEObserver::AfterCompile(bool Succeeded) {}

		bool IDEObserver::RegisterIDE()
		{
			bool retVal = false;
			UnregisterIDE();
			if (!services && observerIndex < 0)
				if (BorlandIDEServices && BorlandIDEServices->Supports(services))
				{
					observerIndex = services->AddNotifier(this);
					retVal = observerIndex > -1;
				}

			return retVal;
		}

		void IDEObserver::UnregisterIDE()
		{
			if (services && observerIndex > -1)
				services->RemoveNotifier(observerIndex);

			observerIndex = -1;
			services = 0x0;
		}
	} // namespace Observer
} // namespace ClangFormat
