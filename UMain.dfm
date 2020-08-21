object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Image Resize'
  ClientHeight = 519
  ClientWidth = 1149
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 440
    Top = 8
    Width = 700
    Height = 500
  end
  object Label1: TLabel
    Left = 8
    Top = 445
    Width = 47
    Height = 13
    Caption = 'Old Width'
  end
  object Label2: TLabel
    Left = 72
    Top = 445
    Width = 50
    Height = 13
    Caption = 'Old Height'
  end
  object Label3: TLabel
    Left = 152
    Top = 445
    Width = 52
    Height = 13
    Caption = 'New Width'
  end
  object Label4: TLabel
    Left = 216
    Top = 445
    Width = 55
    Height = 13
    Caption = 'New Height'
  end
  object Label5: TLabel
    Left = 296
    Top = 445
    Width = 51
    Height = 13
    Caption = 'Max Width'
  end
  object Label6: TLabel
    Left = 360
    Top = 445
    Width = 54
    Height = 13
    Caption = 'Max Height'
  end
  object FileListBox1: TFileListBox
    Left = 8
    Top = 8
    Width = 413
    Height = 417
    ItemHeight = 13
    TabOrder = 0
    OnClick = FileListBox1Click
  end
  object edtWidthOld: TEdit
    Left = 8
    Top = 464
    Width = 61
    Height = 21
    Enabled = False
    TabOrder = 1
  end
  object edtHeightOld: TEdit
    Left = 72
    Top = 464
    Width = 61
    Height = 21
    Enabled = False
    TabOrder = 2
  end
  object edtWidthNew: TEdit
    Left = 152
    Top = 464
    Width = 61
    Height = 21
    Enabled = False
    TabOrder = 3
  end
  object edtHeightNew: TEdit
    Left = 216
    Top = 464
    Width = 61
    Height = 21
    Enabled = False
    TabOrder = 4
  end
  object edtWidthMax: TEdit
    Left = 296
    Top = 464
    Width = 61
    Height = 21
    TabOrder = 5
    Text = '700'
  end
  object edtHeightMax: TEdit
    Left = 360
    Top = 464
    Width = 61
    Height = 21
    TabOrder = 6
    Text = '500'
  end
end
