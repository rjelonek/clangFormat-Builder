#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "AboutForm.h"
#include "Theming.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TaboutForm::TaboutForm(TComponent *Owner) : TForm(Owner) {}

void TaboutForm::InitializeComponents()
{
	ClientHeight = 185;
	ClientWidth = 300;

	sourceUrlLinkLabel->Caption = "Sources are available <a href=\"https://github.com/rjelonek/clangFormat-Builder\">here</a>";
	licenseLinkLabel->Caption =
		"See the <a href=\"https://github.com/rjelonek/clangFormat-Builder/blob/master/LICENSE\">LICENSE</a> file for the full license text";

	sourceUrlLinkLabel->Left = (sourcesPanel->Width - sourceUrlLinkLabel->Width) / 2;
	licenseLinkLabel->Left = (licensePanel->Width - licenseLinkLabel->Width) / 2;
}

void __fastcall TaboutForm::FormShow(TObject *Sender)
{
	ClangFormat::Theming theming;
	theming.RegisterFormClass(this->ClassType(), this);
	if (theming.IsThemingSupported())
		this->Padding->SetBounds(0, 0, 0, 0);

	InitializeComponents();
}

void __fastcall TaboutForm::LinkLabelLinkClick(TObject *Sender, const UnicodeString Link, TSysLinkType LinkType)
{
	String operation = "open";
	ShellExecuteW(0x0, operation.c_str(), Link.c_str(), 0x0, 0x0, SW_SHOWNORMAL);
}
