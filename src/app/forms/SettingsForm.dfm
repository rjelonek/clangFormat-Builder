object settingsForm: TsettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'ClangFormat settings'
  ClientHeight = 232
  ClientWidth = 500
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    500
    232)
  PixelsPerInch = 96
  TextHeight = 13
  object shortcutsLabel: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 130
    Width = 494
    Height = 17
    Align = alTop
    Caption = 'Shortcuts'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object generalLabel: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 494
    Height = 17
    Align = alTop
    Caption = 'General'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object autoFormattingCheckBox: TCheckBox
    AlignWithMargins = True
    Left = 15
    Top = 26
    Width = 482
    Height = 17
    Margins.Left = 15
    Align = alTop
    Caption = 'Enable auto formatting'
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = autoFormattingCheckBoxClick
  end
  object clangFormatPathPanel: TPanel
    AlignWithMargins = True
    Left = 15
    Top = 103
    Width = 482
    Height = 21
    Margins.Left = 15
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    DesignSize = (
      482
      21)
    object clangFormatPathLabel: TLabel
      Left = 0
      Top = 3
      Width = 87
      Height = 13
      Caption = 'Clang format path'
    end
    object clangFormatPathEdit: TEdit
      Left = 112
      Top = 0
      Width = 347
      Height = 21
      Anchors = [akTop, akRight]
      ReadOnly = True
      TabOrder = 0
    end
    object selectFileButton: TButton
      Left = 461
      Top = 0
      Width = 21
      Height = 21
      Caption = '...'
      TabOrder = 1
      OnClick = selectFileButtonClick
    end
  end
  object formatAllSourcesPanel: TPanel
    AlignWithMargins = True
    Left = 15
    Top = 180
    Width = 482
    Height = 21
    Margins.Left = 15
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 5
    DesignSize = (
      482
      21)
    object formatAllSourcesLabel: TLabel
      Left = 0
      Top = 4
      Width = 87
      Height = 13
      Caption = 'Format all sources'
    end
    object formatAllSourcesHotKey: THotKey
      Left = 112
      Top = 0
      Width = 145
      Height = 19
      Anchors = [akTop, akRight]
      HotKey = 0
      Modifiers = []
      TabOrder = 0
      OnChange = formatAllSourcesHotKeyChange
    end
  end
  object stylePanel: TPanel
    AlignWithMargins = True
    Left = 15
    Top = 49
    Width = 482
    Height = 21
    Margins.Left = 15
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      482
      21)
    object styleLabel: TLabel
      Left = 0
      Top = 0
      Width = 61
      Height = 21
      Align = alLeft
      Caption = 'Default style'
    end
    object styleComboBox: TComboBox
      Left = 112
      Top = 0
      Width = 145
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      ItemIndex = 0
      TabOrder = 0
      Text = 'File'
      OnChange = styleComboBoxChange
      Items.Strings = (
        'File'
        'LLVM'
        'Google'
        'Chromium'
        'Mozilla'
        'WebKit'
        'Microsoft')
    end
  end
  object autoFormattingPanel: TPanel
    AlignWithMargins = True
    Left = 15
    Top = 153
    Width = 482
    Height = 21
    Margins.Left = 15
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    DesignSize = (
      482
      21)
    object autoFormattingLabel: TLabel
      Left = 0
      Top = 4
      Width = 76
      Height = 13
      Caption = 'Auto formatting'
    end
    object autoFormattingHotKey: THotKey
      Left = 112
      Top = 0
      Width = 145
      Height = 19
      Anchors = [akTop, akRight]
      HotKey = 0
      Modifiers = []
      TabOrder = 0
      OnChange = autoFormattingHotKeyChange
    end
  end
  object closeButton: TButton
    Left = 422
    Top = 204
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Close'
    ModalResult = 8
    TabOrder = 6
  end
  object fallbackStylePanel: TPanel
    AlignWithMargins = True
    Left = 15
    Top = 76
    Width = 482
    Height = 21
    Margins.Left = 15
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      482
      21)
    object fallbackStyleLabel: TLabel
      Left = 0
      Top = 0
      Width = 64
      Height = 21
      Align = alLeft
      Caption = 'Fallback style'
    end
    object fallbackStyleComboBox: TComboBox
      Left = 112
      Top = 0
      Width = 145
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      ItemIndex = 0
      TabOrder = 0
      Text = 'None'
      OnChange = fallbackStyleComboBoxChange
      Items.Strings = (
        'None'
        'LLVM'
        'Google'
        'Chromium'
        'Mozilla'
        'WebKit'
        'Microsoft')
    end
  end
  object resetButton: TButton
    Left = 317
    Top = 204
    Width = 100
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Reset to default'
    TabOrder = 7
    OnClick = resetButtonClick
  end
  object selectFileOpenDialog: TOpenDialog
    DefaultExt = '.exe'
    FileName = 'clang-format.exe'
    Filter = '*.exe'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Select clang-format'
    Left = 376
    Top = 32
  end
end
