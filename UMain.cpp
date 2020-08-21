//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMain.h"
#include "PngImage.hpp"
#include "Jpeg.hpp"
//#include "Math.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	FileListBox1->Directory = ExtractFilePath(ParamStr(0)) + "\\images";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
	String fileName = FileListBox1->Directory + "\\" + FileListBox1->Items->Strings[FileListBox1->ItemIndex];

	if (FileExists(fileName))
	{
		TGraphic *graphic = NULL;
		FileListBox1->Enabled = false;

		int maxWidth = StrToIntDef(edtWidthMax->Text, 700);
		int maxHeight = StrToIntDef(edtHeightMax->Text, 500);

		try
		{
			String ext = ExtractFileExt(fileName);
			TRect maxSize = Rect(0, 0, maxWidth, maxHeight);

			if (ext == ".png")
				graphic = new TPngImage();
			else if (ext == ".jpg" || ext == ".jpeg")
				graphic = new TJPEGImage();
			else if (ext == ".bmp")
				graphic = new TBitmap();
			else
				throw new Exception("Not supported format: " + ext);

			DrawGraphicIntoImage(fileName, Image1, graphic, maxSize);
		}
		__finally
		{
			FileListBox1->Enabled = true;

			if (graphic != NULL)
				delete graphic;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawGraphicIntoImage(String fileName, TImage *image, TGraphic *graphic, TRect maxSize)
{
	TBitmap *bmp = new TBitmap();
	try
	{
		graphic->LoadFromFile(fileName);
		TRect newSize = CalculateNewSize(graphic->Width, graphic->Height, maxSize);

		bmp->Width = graphic->Width;
		bmp->Height = graphic->Height;
		bmp->Canvas->FillRect(Bounds(0, 0, graphic->Width, graphic->Height));
		bmp->Canvas->StretchDraw(Rect(0, 0, graphic->Width, graphic->Height), graphic);
		graphic->Assign(bmp);

		SmoothResize(bmp, newSize.Width(), newSize.Height());

		image->Width = newSize.Width();
		image->Height = newSize.Height();
		image->Picture->Assign(bmp);
	}
	__finally
	{
		delete bmp;
	}
}
//---------------------------------------------------------------------------

TRect __fastcall TForm1::CalculateNewSize(int imgWidth, int imgHeight, TRect maxSize)
{
	double dWidth = (double)imgWidth;
	double dHeight = (double)imgHeight;
	double dMaxWidth = (double)maxSize.Width();
	double dMaxHeight = (double)maxSize.Height();

	int newWidth = maxSize.Width()+1;
	int newHeight = maxSize.Height()+1;

	edtWidthOld->Text = IntToStr(imgWidth);
	edtHeightOld->Text = IntToStr(imgHeight);

	while (newWidth > maxSize.Width() || newHeight > maxSize.Height())
	{
		if (imgWidth > maxSize.Width())
		{
			double perc = 1 - ((dWidth - dMaxWidth) / dWidth);
			newWidth = maxSize.Width();
			newHeight = (int)(dHeight * perc);
		}
		else if (imgHeight > maxSize.Height())
		{
			double perc = 1 - ((dHeight - dMaxHeight) / dHeight);
			newHeight = maxSize.Height();
			newWidth = (int)(dWidth * perc);
		}

		imgWidth = newWidth;
		imgHeight = newHeight;
		double dWidth = (double)imgWidth;
		double dHeight = (double)imgHeight;
	}

	edtWidthNew->Text = IntToStr(newWidth);
	edtHeightNew->Text = IntToStr(newHeight);

	return Rect(0, 0, newWidth, newHeight);
}
//---------------------------------------------------------------------------

// Got this code in Pascal from this link and translated to C++
// https://groups.google.com/g/borland.public.delphi.graphics/c/n7vFd1RJMZI?pli=1

void __fastcall TForm1::SmoothResize(TBitmap *abmp, int newWidth, int newHeight)
{
	abmp->PixelFormat = pf24bit;
	TBitmap *bTmp = new TBitmap();
	double weight_y[2];
	double weight_x[2];

	TRGBTriple *sli;
	TRGBTriple *slo;

	try
	{
		bTmp->PixelFormat = pf24bit;
		bTmp->Width = newWidth;
		bTmp->Height = newHeight;

		double bTmpHeight = bTmp->Height;
		double bTmpWidth = bTmp->Width;
		double abmpHeight = abmp->Height;
		double abmpWidth = abmp->Width;

		double xscale = bTmpWidth / (abmpWidth-1);
		double yscale = bTmpHeight / (abmpHeight-1);

		for (int to_y = 0; to_y <= (bTmp->Height-1); to_y++)
		{
			double sfrom_y = to_y / yscale;
			int ifrom_y = (int)(sfrom_y);
			weight_y[1] = sfrom_y - ifrom_y;
			weight_y[0] = 1 - weight_y[1];

			for (int to_x = 0; to_x <= (bTmp->Width-1); to_x++)
			{
				double sfrom_x = to_x / xscale;
				int ifrom_x = (int)(sfrom_x);
				weight_x[1] = sfrom_x - ifrom_x;
				weight_x[0] = 1 - weight_x[1];
				double total_red = 0.0;
				double total_green = 0.0;
				double total_blue = 0.0;

				for (int ix = 0; ix <= 1; ix++)
				{
					for (int iy = 0; iy <= 1; iy++)
					{
						sli = reinterpret_cast<TRGBTriple *>(abmp->ScanLine[ifrom_y + iy]);
						int new_red = sli[ifrom_x + ix].rgbtRed;
						int new_green = sli[ifrom_x + ix].rgbtGreen;
						int new_blue = sli[ifrom_x + ix].rgbtBlue;
						double weight = weight_x[ix] * weight_y[iy];
						total_red = total_red + new_red * weight;
						total_green = total_green + new_green * weight;
						total_blue = total_blue + new_blue * weight;
					}
				}

				slo = reinterpret_cast<TRGBTriple *>(bTmp->ScanLine[to_y]);
				slo[to_x].rgbtRed = (int)(total_red);
				slo[to_x].rgbtGreen = (int)(total_green);
				slo[to_x].rgbtBlue = (int)(total_blue);
			}
		}

		abmp->Width = bTmp->Width;
		abmp->Height = bTmp->Height;
		abmp->Canvas->Draw(0,0,bTmp);
	}
	__finally
	{
		sli = NULL;
		slo = NULL;
		delete bTmp;
	}
}
//---------------------------------------------------------------------------


