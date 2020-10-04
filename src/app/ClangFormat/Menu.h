#ifndef MenuH
#define MenuH

#include <memory>
#include <Vcl.Menus.hpp>
#include "Settings.h"

namespace ClangFormat
{
	class Menu
	{
	  private:
		std::unique_ptr<TMenuItem> clangFormatMenu;
		std::unique_ptr<TMenuItem> formatCurrentSourceSubmenu;
		std::unique_ptr<TMenuItem> formatAllSourcesSubmenu;
		std::unique_ptr<TMenuItem> enableAutoFormattingSubmenu;
		std::unique_ptr<TMenuItem> convertAllFilesToUTF8BomSubmenu;
		std::unique_ptr<TMenuItem> optionsSubmenu;
		std::unique_ptr<TMenuItem> aboutSubmenu;
		boost::shared_ptr<Configuration::Settings> settings;

		void __fastcall FormatCurrentSourceSubmenuClick(System::TObject *Sender);
		void __fastcall FormatAllSourcesSubmenuClick(System::TObject *Sender);
		void __fastcall EnableAutoFormattingSubmenuClick(System::TObject *Sender);
		void __fastcall ConvertAllFilesToUTF8BomSubmenuClick(System::TObject *Sender);
		void __fastcall OptionsSubmenuClick(System::TObject *Sender);
		void __fastcall AboutSubmenuClick(System::TObject *Sender);

		void SetCaptions();
		void SetShortCuts();
		void SetEvents();
		void SetMenus();
		void SetStates();

	  public:
		Menu(boost::shared_ptr<Configuration::Settings> settings);
		void Add();
	};
}; // namespace ClangFormat
#endif
