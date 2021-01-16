#ifndef SettingsFormH
#define SettingsFormH

#include "Settings.h"
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>

class TsettingsForm : public TForm
{
  __published: // IDE-managed Components
	TCheckBox *autoFormattingCheckBox;
	TLabel *shortcutsLabel;
	TLabel *generalLabel;
	TPanel *clangFormatPathPanel;
	TPanel *formatAllSourcesPanel;
	TPanel *stylePanel;
	TPanel *autoFormattingPanel;
	TComboBox *styleComboBox;
	TLabel *styleLabel;
	TLabel *clangFormatPathLabel;
	TEdit *clangFormatPathEdit;
	THotKey *autoFormattingHotKey;
	TLabel *autoFormattingLabel;
	THotKey *formatAllSourcesHotKey;
	TLabel *formatAllSourcesLabel;
	TButton *selectFileButton;
	TOpenDialog *selectFileOpenDialog;
	TButton *closeButton;
	TPanel *fallbackStylePanel;
	TLabel *fallbackStyleLabel;
	TComboBox *fallbackStyleComboBox;
	TButton *resetButton;
	TPanel *contentPanel;
	TPanel *footerPanel;
	TPanel *formatSelectedLinesPanel;
	TLabel *formatSelectedLinesLabel;
	THotKey *formatSelectedLinesHotKey;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall selectFileButtonClick(TObject *Sender);
	void __fastcall autoFormattingCheckBoxClick(TObject *Sender);
	void __fastcall styleComboBoxChange(TObject *Sender);
	void __fastcall autoFormattingHotKeyChange(TObject *Sender);
	void __fastcall formatAllSourcesHotKeyChange(TObject *Sender);
	void __fastcall fallbackStyleComboBoxChange(TObject *Sender);
	void __fastcall resetButtonClick(TObject *Sender);
	void __fastcall formatSelectedLinesHotKeyChange(TObject *Sender);

  private: // User declarations
	boost::shared_ptr<ClangFormat::Configuration::Settings> settings;
	void InitializeComponents();
	void UpdateClangFormatVersionInfo();

  public: // User declarations
	__fastcall TsettingsForm(TComponent *Owner, boost::shared_ptr<ClangFormat::Configuration::Settings> settings);
};

#endif
