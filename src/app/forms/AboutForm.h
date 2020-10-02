#ifndef AboutFormH
#define AboutFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

class TaboutForm : public TForm
{
	__published : // IDE-managed Components
				  void __fastcall FormShow(TObject *Sender);

  private: // User declarations
	void InitializeComponents();

  public: // User declarations
	__fastcall TaboutForm(TComponent *Owner);
};
#endif
