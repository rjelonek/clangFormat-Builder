#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "AboutForm.h"
#include "Theming.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TaboutForm::TaboutForm(TComponent *Owner) : TForm(Owner) {}

void TaboutForm::InitializeComponents()
{
	ClientHeight = 240;
	ClientWidth = 500;
}

void __fastcall TaboutForm::FormShow(TObject *Sender)
{
	InitializeComponents();
	ClangFormat::Theming theming;
	theming.RegisterFormClass(this->ClassType(), this);
	if (theming.IsThemingSupported())
		this->Padding->SetBounds(0, 0, 0, 0);
}
//---------------------------------------------------------------------------
