object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 291
  ClientWidth = 563
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 250
    Width = 563
    Height = 41
    Align = alBottom
    TabOrder = 0
    ExplicitWidth = 513
    object Panel3: TPanel
      Left = 386
      Top = 1
      Width = 176
      Height = 39
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 336
      object CancelButton: TButton
        Left = 7
        Top = 6
        Width = 75
        Height = 25
        Caption = 'Cancel'
        ModalResult = 2
        TabOrder = 0
      end
      object SaveButton: TButton
        Left = 88
        Top = 6
        Width = 75
        Height = 25
        Caption = 'Save'
        ModalResult = 1
        TabOrder = 1
      end
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 563
    Height = 250
    ActivePage = SettingsGeneralTabSheet
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 513
    object SettingsGeneralTabSheet: TTabSheet
      Caption = 'General'
      object IntTextSizeLabel: TLabel
        Left = 16
        Top = 144
        Width = 89
        Height = 13
        Caption = 'Interface text size'
      end
      object LanguageLabel: TLabel
        Left = 16
        Top = 16
        Width = 47
        Height = 13
        Caption = 'Language'
      end
      object HideOpenFileCheckBox: TCheckBox
        Left = 16
        Top = 80
        Width = 321
        Height = 17
        Caption = 'Hide '#39'Open file'#39
        TabOrder = 0
      end
      object HideOpenFolderCheckBox: TCheckBox
        Left = 16
        Top = 57
        Width = 321
        Height = 17
        Caption = 'Hide '#39'Open folder'#39
        TabOrder = 1
      end
      object IntTextSizeComboBox: TComboBox
        Left = 339
        Top = 141
        Width = 206
        Height = 21
        ItemIndex = 2
        TabOrder = 2
        Text = '8'
        Items.Strings = (
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12')
      end
      object LanguagesComboBox: TComboBox
        Left = 339
        Top = 13
        Width = 206
        Height = 21
        TabOrder = 3
      end
      object ReplaceRNCheckBox: TCheckBox
        Left = 16
        Top = 103
        Width = 321
        Height = 17
        Caption = 'Replace new line code with &&#13;&&#10;'
        TabOrder = 4
      end
    end
    object SettingsRecentTabSheet: TTabSheet
      Caption = 'Recent files'
      ImageIndex = 1
      object MaxRecentLabel: TLabel
        Left = 16
        Top = 16
        Width = 100
        Height = 13
        Caption = 'Maximum recent files'
      end
      object RecentListView: TListView
        Left = 3
        Top = 48
        Width = 385
        Height = 171
        Columns = <
          item
            AutoSize = True
          end>
        ColumnClick = False
        GridLines = True
        RowSelect = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        ViewStyle = vsReport
        OnSelectItem = RecentListViewSelectItem
      end
      object MaxRecentEdit: TEdit
        Left = 331
        Top = 13
        Width = 57
        Height = 21
        NumbersOnly = True
        TabOrder = 1
        Text = '10'
      end
      object MoveUpButton: TButton
        Left = 394
        Top = 48
        Width = 108
        Height = 25
        Caption = 'Move up'
        Enabled = False
        TabOrder = 2
        OnClick = MoveUpButtonClick
      end
      object MoveDownButton: TButton
        Left = 394
        Top = 79
        Width = 108
        Height = 25
        Caption = 'Move down'
        Enabled = False
        TabOrder = 3
        OnClick = MoveDownButtonClick
      end
      object RemoveButton: TButton
        Left = 394
        Top = 110
        Width = 108
        Height = 25
        Caption = 'Remove'
        Enabled = False
        TabOrder = 4
        OnClick = RemoveButtonClick
      end
    end
  end
end
