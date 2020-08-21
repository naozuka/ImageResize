//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TFileListBox *FileListBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edtWidthOld;
	TEdit *edtHeightOld;
	TEdit *edtWidthNew;
	TEdit *edtHeightNew;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edtWidthMax;
	TEdit *edtHeightMax;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FileListBox1Click(TObject *Sender);
private:	// User declarations
	TRect __fastcall CalculateNewSize(int imgWidth, int imgHeight, TRect maxSize);
	void __fastcall DrawGraphicIntoImage(String fileName, TImage *image, TGraphic *graphic, TRect maxSize);
	void __fastcall SmoothResize(TBitmap *abmp, int newWidth, int newHeight);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
