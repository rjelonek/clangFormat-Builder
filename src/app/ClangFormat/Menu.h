#ifndef MenuH
#define MenuH

#include "Settings.h"
#include <Vcl.Menus.hpp>
#include <memory>

namespace ClangFormat
{
	class Menu
	{
	  private:
		std::unique_ptr<TMenuItem> clangFormatMenu;
		std::unique_ptr<TMenuItem> formatCurrentSourceSubmenu;
		std::unique_ptr<TMenuItem> formatSelectedLinesSubmenu;
		std::unique_ptr<TMenuItem> formatAllSourcesSubmenu;
		std::unique_ptr<TMenuItem> enableAutoFormattingSubmenu;
		std::unique_ptr<TMenuItem> convertAllFilesToUTF8BomSubmenu;
		std::unique_ptr<TMenuItem> optionsSubmenu;
		std::unique_ptr<TMenuItem> aboutSubmenu;
		boost::shared_ptr<Configuration::Settings> settings;

		void __fastcall FormatCurrentSourceSubmenuClick(System::TObject *Sender);
		void __fastcall FormatSelectedLinesSubmenuClick(System::TObject *Sender);
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

		int IndexOfIdeToolsMenu(TMainMenu *mainMenu);

	  public:
		Menu(boost::shared_ptr<Configuration::Settings> settings);
		void Add();
	};
}; // namespace ClangFormat
#endif
