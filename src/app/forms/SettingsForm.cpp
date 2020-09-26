﻿#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "SettingsForm.h"
#include "Settings.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TsettingsForm::TsettingsForm(TComponent *Owner, boost::shared_ptr<ClangFormat::Configuration::Settings> settings)
	: TForm(Owner), settings(settings)
{
}

void TsettingsForm::InitializeComponents()
{
	ClientHeight = 240;
	ClientWidth = 500;

	autoFormattingCheckBox->Checked = settings->general.autoFormatting;
	styleComboBox->ItemIndex = styleComboBox->Items->IndexOf(settings->general.style);
	fallbackStyleComboBox->ItemIndex = fallbackStyleComboBox->Items->IndexOf(settings->general.fallbackStyle);
	clangFormatPathEdit->Text = settings->general.clangFormatPath;
	autoFormattingHotKey->HotKey = settings->shortcuts.autoFormatting;
	formatAllSourcesHotKey->HotKey = settings->shortcuts.formatAllSources;

	styleComboBox->ShowHint = true;
	styleComboBox->Hint = "Coding style. Use style=file to load style configuration from .clang-format file located in one of the parent directories "
						  "of the source file.";

	fallbackStyleComboBox->ShowHint = true;
	fallbackStyleComboBox->Hint = "The name of the predefined style used as a fallback in case clang-format is invoked with style=file, but can not "
								  "find the .clang-format file to use. Use fallback-style=none to skip formatting.";
}

void __fastcall TsettingsForm::FormShow(TObject *Sender)
{
	InitializeComponents();
}

void __fastcall TsettingsForm::selectFileButtonClick(TObject *Sender)
{
	try
	{
		if (!clangFormatPathEdit->Text.IsEmpty())
			selectFileOpenDialog->InitialDir = TPath::GetDirectoryName(clangFormatPathEdit->Text);

		if (selectFileOpenDialog->Execute(this->Handle))
		{
			settings->general.clangFormatPath = selectFileOpenDialog->FileName;
			clangFormatPathEdit->Text = selectFileOpenDialog->FileName;
		}
	}
	catch (Exception &ex)
	{
		ShowMessage(ex.Message);
	}
}

void __fastcall TsettingsForm::autoFormattingCheckBoxClick(TObject *Sender)
{
	settings->general.autoFormatting = autoFormattingCheckBox->Checked;
}

void __fastcall TsettingsForm::styleComboBoxChange(TObject *Sender)
{
	settings->general.style = styleComboBox->Text;
}

void __fastcall TsettingsForm::fallbackStyleComboBoxChange(TObject *Sender)
{
	settings->general.fallbackStyle = fallbackStyleComboBox->Text;
}

void __fastcall TsettingsForm::autoFormattingHotKeyChange(TObject *Sender)
{
	settings->shortcuts.autoFormatting = autoFormattingHotKey->HotKey;
}

void __fastcall TsettingsForm::formatAllSourcesHotKeyChange(TObject *Sender)
{
	settings->shortcuts.formatAllSources = formatAllSourcesHotKey->HotKey;
}

void __fastcall TsettingsForm::resetButtonClick(TObject *Sender)
{
	settings->SetDefaultValues();
	InitializeComponents();
}
