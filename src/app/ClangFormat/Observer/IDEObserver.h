#ifndef IDEObserverH
#define IDEObserverH

#include <ToolsAPI.hpp>
#include <memory>
#include <map>
#include "FileSourceObserver.h"

namespace ClangFormat
{
	namespace Observer
	{
		class IDEObserver : public TNotifierObject, public IOTANotifier, public IOTAIDENotifier
		{
		  private:
			std::map<_di_IOTAEditor, FileSourceObserver *> fileSourceObservers;
			int observerIndex;
			_di_IOTAServices services;
			boost::shared_ptr<Configuration::Settings> settings;

		  public:
			IDEObserver(boost::shared_ptr<Configuration::Settings> settings);
			__fastcall ~IDEObserver();
			HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
			ULONG __stdcall AddRef();
			ULONG __stdcall Release();

			void __fastcall AfterConstruction();
			void __fastcall BeforeDestruction();

			void __fastcall AfterSave();
			void __fastcall BeforeSave();
			void __fastcall Destroyed();
			void __fastcall Modified();

			void __fastcall FileNotification(TOTAFileNotification NotifyCode, const System::UnicodeString FileName, bool &Cancel);
			void __fastcall BeforeCompile(const _di_IOTAProject Project, bool &Cancel);
			void __fastcall AfterCompile(bool Succeeded);

			bool RegisterIDE();
			void UnregisterIDE();
		};
	} // namespace Observer
} // namespace ClangFormat
#endif
