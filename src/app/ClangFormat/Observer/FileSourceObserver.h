#ifndef FileSourceObserverH
#define FileSourceObserverH

#include <ToolsAPI.hpp>
#include "Settings.h"

namespace ClangFormat
{
	namespace Observer
	{
		class FileSourceObserver : public TNotifierObject, public IOTANotifier
		{
		  private:
			_di_IOTASourceEditor fileSourceEditor;
			int observerIndex;
			boost::shared_ptr<Configuration::Settings> settings;

		  public:
			FileSourceObserver(boost::shared_ptr<Configuration::Settings> settings);
			__fastcall ~FileSourceObserver();
			HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
			ULONG __stdcall AddRef();
			ULONG __stdcall Release();

			void __fastcall AfterConstruction();
			void __fastcall BeforeDestruction();

			void __fastcall AfterSave();
			void __fastcall BeforeSave();
			void __fastcall Destroyed();
			void __fastcall Modified();

			bool Register(_di_IOTAEditor editor);
			void Unregister();
		};
	} // namespace Observer
} // namespace ClangFormat

#endif
