object aboutForm: TaboutForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'About ClangFormat'
  ClientHeight = 185
  ClientWidth = 300
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Padding.Left = 5
  Padding.Right = 5
  Padding.Bottom = 5
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object copyrightLabel: TLabel
    Left = 5
    Top = 167
    Width = 290
    Height = 13
    Align = alBottom
    Alignment = taCenter
    Caption = 'Copyright'
  end
  object titleLabel: TLabel
    AlignWithMargins = True
    Left = 8
    Top = 10
    Width = 284
    Height = 19
    Margins.Top = 10
    Align = alTop
    Alignment = taCenter
    Caption = 'Title'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object bevel: TBevel
    AlignWithMargins = True
    Left = 30
    Top = 35
    Width = 240
    Height = 1
    Margins.Left = 25
    Margins.Right = 25
    Margins.Bottom = 5
    Align = alTop
    Shape = bsTopLine
  end
  object versionLabel: TLabel
    AlignWithMargins = True
    Left = 8
    Top = 44
    Width = 284
    Height = 13
    Align = alTop
    Alignment = taCenter
    Caption = 'Version'
  end
  object licenseLabel: TLabel
    AlignWithMargins = True
    Left = 8
    Top = 105
    Width = 284
    Height = 13
    Align = alTop
    Alignment = taCenter
    Caption = 'This project is licensed under the Apache-2.0 License'
  end
  object sourcesPanel: TPanel
    AlignWithMargins = True
    Left = 8
    Top = 75
    Width = 284
    Height = 17
    Margins.Top = 15
    Margins.Bottom = 10
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 0
    object sourceUrlLinkLabel: TLinkLabel
      Left = 84
      Top = 0
      Width = 131
      Height = 17
      Caption = 'Sources are available here'
      TabOrder = 0
      OnLinkClick = LinkLabelLinkClick
    end
  end
  object licensePanel: TPanel
    Left = 5
    Top = 121
    Width = 290
    Height = 23
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 1
    object licenseLinkLabel: TLinkLabel
      AlignWithMargins = True
      Left = 52
      Top = 3
      Width = 213
      Height = 17
      Caption = 'See the LICENSE file for the full license text'
      TabOrder = 0
      OnLinkClick = LinkLabelLinkClick
    end
  end
end
