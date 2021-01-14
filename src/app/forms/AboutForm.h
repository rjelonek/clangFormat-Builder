#ifndef AboutFormH
#define AboutFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>

class TaboutForm : public TForm
{
	__published : // IDE-managed Components
				  TLabel *copyrightLabel;
	TLabel *titleLabel;
	TBevel *bevel;
	TLabel *versionLabel;
	TPanel *sourcesPanel;
	TLabel *licenseLabel;
	TLinkLabel *sourceUrlLinkLabel;
	TPanel *licensePanel;
	TLinkLabel *licenseLinkLabel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LinkLabelLinkClick(TObject *Sender, const UnicodeString Link, TSysLinkType LinkType);

  private: // User declarations
	void InitializeComponents();

  public: // User declarations
	__fastcall TaboutForm(TComponent *Owner);
};
#endif
