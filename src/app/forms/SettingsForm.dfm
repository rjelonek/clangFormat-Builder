object settingsForm: TsettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'ClangFormat settings'
  ClientHeight = 240
  ClientWidth = 500
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
  object contentPanel: TPanel
    Left = 5
    Top = 0
    Width = 490
    Height = 210
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object shortcutsLabel: TLabel
      AlignWithMargins = True
      Left = 3
      Top = 103
      Width = 484
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
      Width = 484
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
      Width = 472
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
      Top = 126
      Width = 475
      Height = 21
      Margins.Left = 15
      Margins.Right = 0
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      DesignSize = (
        475
        21)
      object clangFormatPathLabel: TLabel
        Left = 0
        Top = 3
        Width = 87
        Height = 13
        Caption = 'Clang format path'
      end
      object clangFormatPathEdit: TEdit
        Left = 102
        Top = 0
        Width = 347
        Height = 21
        Anchors = [akTop, akRight]
        ReadOnly = True
        TabOrder = 0
      end
      object selectFileButton: TButton
        Left = 454
        Top = 0
        Width = 21
        Height = 21
        Align = alRight
        Caption = '...'
        TabOrder = 1
        OnClick = selectFileButtonClick
      end
    end
    object formatAllSourcesPanel: TPanel
      AlignWithMargins = True
      Left = 15
      Top = 153
      Width = 472
      Height = 21
      Margins.Left = 15
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 4
      DesignSize = (
        472
        21)
      object formatAllSourcesLabel: TLabel
        Left = 0
        Top = 4
        Width = 87
        Height = 13
        Caption = 'Format all sources'
      end
      object formatAllSourcesHotKey: THotKey
        Left = 102
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
      Width = 472
      Height = 21
      Margins.Left = 15
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        472
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
        Left = 102
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
      Top = 180
      Width = 472
      Height = 21
      Margins.Left = 15
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 5
      DesignSize = (
        472
        21)
      object autoFormattingLabel: TLabel
        Left = 0
        Top = 4
        Width = 76
        Height = 13
        Caption = 'Auto formatting'
      end
      object autoFormattingHotKey: THotKey
        Left = 102
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
    object fallbackStylePanel: TPanel
      AlignWithMargins = True
      Left = 15
      Top = 76
      Width = 472
      Height = 21
      Margins.Left = 15
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      DesignSize = (
        472
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
        Left = 102
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
  end
  object footerPanel: TPanel
    Left = 5
    Top = 210
    Width = 490
    Height = 25
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object resetButton: TButton
      Left = 312
      Top = 0
      Width = 100
      Height = 25
      Align = alRight
      Caption = 'Reset to default'
      TabOrder = 0
      OnClick = resetButtonClick
    end
    object closeButton: TButton
      AlignWithMargins = True
      Left = 415
      Top = 0
      Width = 75
      Height = 25
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alRight
      Caption = 'Close'
      Default = True
      ModalResult = 8
      TabOrder = 1
    end
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
