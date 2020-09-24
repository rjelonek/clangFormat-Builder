#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "Menu.h"
#include "CodeFormatter.h"
#include "Settings.h"
#include "EncodingConverter.h"
#include "SettingsForm.h"

namespace ClangFormat
{
	Menu::Menu(boost::shared_ptr<Configuration::Settings> settings) : settings(settings)
	{
		clangFormatMenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
		formatCurrentSourceSubmenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
		formatAllSourcesSubmenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
		enableAutoFormattingSubmenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
		convertAllFilesToUTF8BomSubmenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
		optionsSubmenu = std::unique_ptr<TMenuItem>(new TMenuItem(0x0));
	}

	void __fastcall Menu::FormatCurrentSourceSubmenuClick(System::TObject *Sender)
	{
		CodeFormatter codeFormatter(settings);
		codeFormatter.FormatCurrentSource();
	}

	void __fastcall Menu::FormatAllSourcesSubmenuClick(System::TObject *Sender)
	{
		CodeFormatter codeFormatter(settings);
		codeFormatter.FormatAllSources();
	}

	void __fastcall Menu::EnableAutoFormattingSubmenuClick(System::TObject *Sender)
	{
		enableAutoFormattingSubmenu->Checked = !enableAutoFormattingSubmenu->Checked;
		settings->general.autoFormatting = enableAutoFormattingSubmenu->Checked;
		settings->Save();
	}

	void __fastcall Menu::ConvertAllFilesToUTF8BomSubmenuClick(System::TObject *Sender)
	{
		EncodingConverter encodingConverter;
		encodingConverter.AllFilesToUTF8Bom();
	}

	void __fastcall Menu::OptionsSubmenuClick(System::TObject *Sender)
	{
		std::unique_ptr<TsettingsForm> settingsForm(new TsettingsForm(Application, settings));
		settingsForm->ShowModal();

		settings->Save();
		SetShortCuts();
		SetStates();
	}

	void Menu::Add()
	{
		_di_INTAServices services;
		if (BorlandIDEServices && BorlandIDEServices->Supports(services) && services->MainMenu)
		{
			if (!services->MainMenu->Items->Find("ClangFormat"))
			{
				SetCaptions();
				SetShortCuts();
				SetEvents();
				SetMenus();
				SetStates();
				services->MainMenu->Items->Add(clangFormatMenu.get());
			}
		}
	}

	void Menu::SetCaptions()
	{
		clangFormatMenu->Caption = "ClangFormat";
		formatCurrentSourceSubmenu->Caption = "Format current source";
		formatAllSourcesSubmenu->Caption = "Format all sources";
		enableAutoFormattingSubmenu->Caption = "Enable auto formatting";
		convertAllFilesToUTF8BomSubmenu->Caption = "Convert all files to UTF8 BOM";
		optionsSubmenu->Caption = "Options...";
	}

	void Menu::SetShortCuts()
	{
		formatCurrentSourceSubmenu->ShortCut = settings->shortcuts.formatAllSources;
		enableAutoFormattingSubmenu->ShortCut = settings->shortcuts.autoFormatting;
	}

	void Menu::SetEvents()
	{
		formatCurrentSourceSubmenu->OnClick = FormatCurrentSourceSubmenuClick;
		formatAllSourcesSubmenu->OnClick = FormatAllSourcesSubmenuClick;
		enableAutoFormattingSubmenu->OnClick = EnableAutoFormattingSubmenuClick;
		convertAllFilesToUTF8BomSubmenu->OnClick = ConvertAllFilesToUTF8BomSubmenuClick;
		optionsSubmenu->OnClick = OptionsSubmenuClick;
	}

	void Menu::SetMenus()
	{
		clangFormatMenu->Add(formatCurrentSourceSubmenu.get());
		clangFormatMenu->Add(formatAllSourcesSubmenu.get());
		clangFormatMenu->Add(enableAutoFormattingSubmenu.get());
		clangFormatMenu->Add(convertAllFilesToUTF8BomSubmenu.get());
		clangFormatMenu->Add(optionsSubmenu.get());
	}

	void Menu::SetStates()
	{
		enableAutoFormattingSubmenu->Checked = settings->general.autoFormatting;
	}
} // namespace ClangFormat
