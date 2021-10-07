#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "FileSourceObserver.h"
#include "CodeFormatter.h"

namespace ClangFormat
{
	namespace Observer
	{
		FileSourceObserver::FileSourceObserver(boost::shared_ptr<Configuration::Settings> settings) : settings(settings)
		{
			fileSourceEditor = 0x0;
			observerIndex = -1;
		}

		__fastcall FileSourceObserver::~FileSourceObserver()
		{
			Unregister();
		}

		HRESULT __stdcall FileSourceObserver::QueryInterface(REFIID riid, void **ppv)
		{
			return TInterfacedObject::QueryInterface(riid, (void *)ppv);
		}

		ULONG __stdcall FileSourceObserver::AddRef()
		{
			return TInterfacedObject::_AddRef();
		}

		ULONG __stdcall FileSourceObserver::Release()
		{
			return TInterfacedObject::_Release();
		}

		void __fastcall FileSourceObserver::AfterConstruction() {}

		void __fastcall FileSourceObserver::BeforeDestruction() {}

		void __fastcall FileSourceObserver::AfterSave() {}

		void __fastcall FileSourceObserver::BeforeSave()
		{
			if (settings->general.autoFormatting && fileSourceEditor->Modified)
			{
				CodeFormatter codeFormatter(settings);
				codeFormatter.FormatSource(fileSourceEditor);
			}
		}

		void __fastcall FileSourceObserver::Destroyed() {}

		void __fastcall FileSourceObserver::Modified() {}

		bool FileSourceObserver::Register(_di_IOTAEditor editor)
		{
			bool retVal = false;
			if (editor)
			{
				String extension = TPath::GetExtension(editor->FileName).LowerCase();
				if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".cc")
				{
					Unregister();
					if (!fileSourceEditor && observerIndex < 0 && ::Supports(editor, __uuidof(IOTASourceEditor), &fileSourceEditor))
					{
						observerIndex = fileSourceEditor->AddNotifier(this);
						retVal = observerIndex > -1;
					}
				}
			}

			return retVal;
		}

		void FileSourceObserver::Unregister()
		{
			if (fileSourceEditor && observerIndex > -1)
				fileSourceEditor->RemoveNotifier(observerIndex);

			observerIndex = -1;
			fileSourceEditor = 0x0;
		}
	} // namespace Observer
} // namespace ClangFormat
