object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'FOMOD Creation Tool'
  ClientHeight = 800
  ClientWidth = 1087
  Color = clBtnFace
  Constraints.MinHeight = 650
  Constraints.MinWidth = 550
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 1087
    Height = 800
    ActivePage = ModInfoTabSheet
    Align = alClient
    TabOrder = 0
    OnChange = StepsTabControlChange
    object ModInfoTabSheet: TTabSheet
      Caption = 'Mod info'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 1079
        Height = 660
        Align = alClient
        Caption = 'Mod infornation'
        TabOrder = 0
        ExplicitHeight = 433
        object Panel5: TPanel
          Left = 2
          Top = 15
          Width = 1075
          Height = 154
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object ModAuthorEdit: TLabeledEdit
            Left = 110
            Top = 40
            Width = 305
            Height = 21
            AutoSize = False
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.Caption = 'Mod author'
            LabelPosition = lpLeft
            LabelSpacing = 43
            TabOrder = 0
            OnChange = ModAuthorEditChange
          end
          object ModCategoryEdit: TLabeledEdit
            Left = 110
            Top = 121
            Width = 305
            Height = 21
            AutoSize = False
            EditLabel.Width = 66
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = 'Mod category'
            EditLabel.ParentBiDiMode = False
            LabelPosition = lpLeft
            LabelSpacing = 32
            TabOrder = 1
            OnChange = ModCategoryEditChange
          end
          object ModNameEdit: TLabeledEdit
            Left = 110
            Top = 13
            Width = 305
            Height = 21
            AutoSize = False
            EditLabel.Width = 49
            EditLabel.Height = 13
            EditLabel.Caption = 'Mod name'
            LabelPosition = lpLeft
            LabelSpacing = 49
            TabOrder = 2
            OnChange = ModNameEditChange
          end
          object ModURLEdit: TLabeledEdit
            Left = 110
            Top = 94
            Width = 305
            Height = 21
            AutoSize = False
            EditLabel.Width = 95
            EditLabel.Height = 13
            EditLabel.Caption = 'Mod page on Nexus'
            LabelPosition = lpLeft
            TabOrder = 3
            OnChange = ModURLEditChange
          end
          object ModVersionEdit: TLabeledEdit
            Left = 110
            Top = 67
            Width = 137
            Height = 21
            AutoSize = False
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.Caption = 'Mod version'
            LabelPosition = lpLeft
            LabelSpacing = 40
            TabOrder = 4
            OnChange = ModVersionEditChange
          end
        end
        object Panel6: TPanel
          Left = 2
          Top = 169
          Width = 1075
          Height = 489
          Align = alClient
          BevelOuter = bvNone
          Caption = 'Panel6'
          Padding.Left = 14
          Padding.Right = 14
          Padding.Bottom = 14
          TabOrder = 1
          ExplicitHeight = 262
          object Label10: TLabel
            Left = 14
            Top = 0
            Width = 1047
            Height = 24
            Align = alTop
            AutoSize = False
            Caption = 'Mod description'
            ExplicitTop = 6
          end
          object ModDesccriptionMemo: TMemo
            Left = 14
            Top = 24
            Width = 1047
            Height = 451
            Align = alClient
            ScrollBars = ssVertical
            TabOrder = 0
            OnChange = ModDesccriptionMemoChange
            ExplicitHeight = 224
          end
        end
      end
      object WorkSpaceGroupBox: TGroupBox
        Left = 0
        Top = 660
        Width = 1079
        Height = 64
        Align = alBottom
        Caption = 'Workspace'
        TabOrder = 1
        ExplicitTop = 433
        object RootDirEdit: TLabeledEdit
          Left = 112
          Top = 27
          Width = 305
          Height = 21
          AutoSize = False
          EditLabel.Width = 69
          EditLabel.Height = 13
          EditLabel.Caption = 'Root derictory'
          LabelPosition = lpLeft
          LabelSpacing = 29
          TabOrder = 0
          OnChange = RootDirEditChange
        end
        object OpenRootDirButton: TButton
          Left = 423
          Top = 24
          Width = 75
          Height = 25
          Caption = 'Open'
          TabOrder = 1
          OnClick = OpenRootDirButtonClick
        end
      end
      object Panel3: TPanel
        Left = 0
        Top = 724
        Width = 1079
        Height = 48
        Align = alBottom
        TabOrder = 2
        object Panel4: TPanel
          Left = 971
          Top = 1
          Width = 107
          Height = 46
          Align = alRight
          BevelOuter = bvNone
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object ProceedButton: TButton
            Left = 14
            Top = 13
            Width = 75
            Height = 25
            Caption = 'Proceed'
            Enabled = False
            TabOrder = 0
            OnClick = ProceedButtonClick
          end
        end
      end
    end
    object StepsTabSheet: TTabSheet
      Caption = 'Steps'
      Enabled = False
      ImageIndex = 1
      object Panel1: TPanel
        Left = 0
        Top = 731
        Width = 1079
        Height = 41
        Align = alBottom
        TabOrder = 0
        object Panel2: TPanel
          Left = 664
          Top = 1
          Width = 414
          Height = 39
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 0
          object DeleteStepButton: TButton
            Left = 252
            Top = 5
            Width = 75
            Height = 25
            Caption = 'Delete step'
            Enabled = False
            TabOrder = 0
            OnClick = DeleteStepButtonClick
          end
          object NewStepButton: TButton
            Left = 333
            Top = 5
            Width = 75
            Height = 25
            Caption = 'New step'
            TabOrder = 1
            OnClick = NewStepButtonClick
          end
          object MoveLeftButton: TButton
            Left = 5
            Top = 5
            Width = 75
            Height = 25
            Caption = 'Move left'
            Enabled = False
            TabOrder = 2
            OnClick = MoveLeftButtonClick
          end
          object MoveRightButton: TButton
            Left = 83
            Top = 5
            Width = 75
            Height = 25
            Caption = 'Move right'
            Enabled = False
            TabOrder = 3
            OnClick = MoveRightButtonClick
          end
        end
      end
      object PageControl1: TPageControl
        Left = 0
        Top = 27
        Width = 1079
        Height = 704
        ActivePage = GroupsFileTabSheet
        Align = alClient
        TabOrder = 1
        object GroupsFileTabSheet: TTabSheet
          Caption = 'Groups and Files'
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 1071
            Height = 676
            HorzScrollBar.Range = 1066
            VertScrollBar.Range = 617
            Align = alClient
            AutoScroll = False
            TabOrder = 0
            object FilesGroupBox: TGroupBox
              Left = 0
              Top = 497
              Width = 1067
              Height = 175
              Align = alClient
              Caption = 'Files'
              TabOrder = 0
              object FilesPanel: TPanel
                Left = 2
                Top = 15
                Width = 1063
                Height = 158
                Align = alClient
                BevelOuter = bvNone
                TabOrder = 0
                object Label8: TLabel
                  Left = 16
                  Top = 7
                  Width = 45
                  Height = 13
                  Caption = 'Copy this'
                end
                object Label9: TLabel
                  Left = 525
                  Top = 6
                  Width = 31
                  Height = 13
                  Caption = 'DATA\'
                end
                object AddFileButton: TButton
                  Left = 980
                  Top = 29
                  Width = 75
                  Height = 25
                  Caption = 'Add file'
                  Enabled = False
                  TabOrder = 0
                  OnClick = AddFileButtonClick
                end
                object AddFolderButton: TButton
                  Left = 980
                  Top = 60
                  Width = 75
                  Height = 25
                  Caption = 'Add folder'
                  Enabled = False
                  TabOrder = 1
                  OnClick = AddFolderButtonClick
                end
                object DstFilesListView: TListView
                  Left = 525
                  Top = 25
                  Width = 449
                  Height = 112
                  Hint = 
                    'To edit: select destination path and then click on it again. It'#39 +
                    's like you rename files in Windows.'
                  Columns = <
                    item
                      Caption = 'Destination path'
                      Width = 425
                    end>
                  ColumnClick = False
                  GridLines = True
                  RowSelect = True
                  ParentShowHint = False
                  PopupMenu = PopupMenu
                  ShowHint = True
                  TabOrder = 2
                  ViewStyle = vsReport
                  OnEdited = DstFilesListViewEdited
                  OnSelectItem = DstFilesListViewSelectItem
                end
                object RemoveFileFolderButton: TButton
                  Left = 980
                  Top = 91
                  Width = 75
                  Height = 25
                  Caption = 'Remove'
                  Enabled = False
                  TabOrder = 3
                  OnClick = RemoveFileFolderButtonClick
                end
                object SrcFilesListView: TListView
                  Left = 16
                  Top = 26
                  Width = 503
                  Height = 111
                  Columns = <
                    item
                      Caption = 'File/Folder'
                      Width = 70
                    end
                    item
                      Caption = 'Source path'
                      Width = 409
                    end>
                  ColumnClick = False
                  GridLines = True
                  ReadOnly = True
                  RowSelect = True
                  TabOrder = 4
                  ViewStyle = vsReport
                  OnSelectItem = SrcFilesListViewSelectItem
                end
              end
            end
            object GroupsGroupBox: TGroupBox
              Left = 0
              Top = 49
              Width = 1067
              Height = 448
              Align = alTop
              Caption = 'Groups && plugins'
              TabOrder = 1
              object PageControl2: TPageControl
                Left = 698
                Top = 15
                Width = 367
                Height = 431
                ActivePage = FlagSetTabSheet
                Align = alRight
                TabOrder = 0
                object FlagSetTabSheet: TTabSheet
                  Caption = 'Flag set'
                  object AddVaribleButton: TButton
                    Left = 281
                    Top = 20
                    Width = 75
                    Height = 25
                    Caption = 'Add'
                    Enabled = False
                    TabOrder = 0
                    OnClick = AddVaribleButtonClick
                  end
                  object DeleteVaribleButton: TButton
                    Left = 281
                    Top = 51
                    Width = 75
                    Height = 25
                    Caption = 'Delete'
                    Enabled = False
                    TabOrder = 1
                    OnClick = DeleteVaribleButtonClick
                  end
                  object Panel17: TPanel
                    Left = 0
                    Top = 0
                    Width = 275
                    Height = 403
                    Align = alLeft
                    BevelOuter = bvNone
                    TabOrder = 2
                    object FlagSetListView: TListView
                      Left = 0
                      Top = 51
                      Width = 275
                      Height = 352
                      Align = alClient
                      Columns = <
                        item
                          Caption = 'Flag name'
                          Width = 130
                        end
                        item
                        end
                        item
                          AutoSize = True
                          Caption = 'Value'
                        end>
                      ColumnClick = False
                      GridLines = True
                      ReadOnly = True
                      RowSelect = True
                      TabOrder = 0
                      ViewStyle = vsReport
                      OnSelectItem = FlagSetListViewSelectItem
                    end
                    object Panel18: TPanel
                      Left = 0
                      Top = 0
                      Width = 275
                      Height = 51
                      Align = alTop
                      BevelOuter = bvNone
                      TabOrder = 1
                      object Label6: TLabel
                        Left = 4
                        Top = 5
                        Width = 173
                        Height = 13
                        Alignment = taCenter
                        AutoSize = False
                        Caption = 'Flag name'
                      end
                      object Label7: TLabel
                        Left = 185
                        Top = 25
                        Width = 34
                        Height = 13
                        AutoSize = False
                        Caption = 'set'
                      end
                      object VaribleComboBox: TComboBox
                        Left = 3
                        Top = 24
                        Width = 176
                        Height = 21
                        ItemHeight = 13
                        TabOrder = 0
                      end
                      object VaribleValueComboBox: TComboBox
                        Left = 223
                        Top = 24
                        Width = 50
                        Height = 21
                        ItemHeight = 13
                        ItemIndex = 0
                        TabOrder = 1
                        Text = 'On'
                        Items.Strings = (
                          'On'
                          'Off')
                      end
                    end
                  end
                end
                object PluginDependenciesTabSheet: TTabSheet
                  Caption = 'Plugin dependencies'
                  ImageIndex = 1
                  object PluginDependenciesListView: TListView
                    Left = 0
                    Top = 233
                    Width = 359
                    Height = 170
                    Align = alClient
                    Columns = <
                      item
                        Caption = 'Type'
                      end
                      item
                        AutoSize = True
                        Caption = 'File/Flag name'
                      end
                      item
                        Caption = 'State/Value'
                        Width = 70
                      end
                      item
                        Caption = 'Operator'
                        Width = 60
                      end>
                    ColumnClick = False
                    GridLines = True
                    ReadOnly = True
                    RowSelect = True
                    TabOrder = 0
                    ViewStyle = vsReport
                    OnSelectItem = PluginDependenciesListViewSelectItem
                  end
                  object Panel16: TPanel
                    Left = 0
                    Top = 0
                    Width = 359
                    Height = 233
                    Align = alTop
                    BevelOuter = bvNone
                    TabOrder = 1
                    object Label11: TLabel
                      Left = 3
                      Top = 177
                      Width = 69
                      Height = 13
                      Alignment = taCenter
                      Caption = 'File/Flag name'
                    end
                    object Label14: TLabel
                      Left = 3
                      Top = 81
                      Width = 44
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Operator'
                    end
                    object Label13: TLabel
                      Left = 3
                      Top = 151
                      Width = 85
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Dependency type'
                    end
                    object Label12: TLabel
                      Left = 3
                      Top = 205
                      Width = 26
                      Height = 13
                      Caption = 'State'
                    end
                    object Label17: TLabel
                      Left = 3
                      Top = 108
                      Width = 53
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Type name'
                    end
                    object Shape2: TShape
                      Left = 3
                      Top = 137
                      Width = 353
                      Height = 1
                    end
                    object Label15: TLabel
                      Left = 3
                      Top = 12
                      Width = 89
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Default type name'
                    end
                    object Shape1: TShape
                      Left = 3
                      Top = 39
                      Width = 353
                      Height = 1
                    end
                    object pdOperatorComboBox: TComboBox
                      Left = 96
                      Top = 78
                      Width = 51
                      Height = 21
                      Enabled = False
                      ItemHeight = 13
                      ItemIndex = 0
                      TabOrder = 0
                      Text = 'And'
                      OnChange = pdOperatorComboBoxChange
                      Items.Strings = (
                        'And'
                        'Or')
                    end
                    object pdDefTypeComboBox: TComboBox
                      Left = 96
                      Top = 9
                      Width = 121
                      Height = 21
                      Enabled = False
                      ItemHeight = 13
                      ItemIndex = 0
                      TabOrder = 1
                      Text = 'Optional'
                      OnChange = pdDefTypeComboBoxChange
                      Items.Strings = (
                        'Optional'
                        'Required'
                        'Recommended'
                        'CouldBeUsable'
                        'NotUsable')
                    end
                    object pdDependencyTypeComboBox: TComboBox
                      Left = 96
                      Top = 148
                      Width = 51
                      Height = 21
                      Style = csDropDownList
                      Enabled = False
                      ItemHeight = 13
                      ItemIndex = 0
                      TabOrder = 2
                      Text = 'file'
                      OnChange = pdDependencyTypeComboBoxChange
                      Items.Strings = (
                        'file'
                        'flag')
                    end
                    object pdAddButton: TButton
                      Left = 281
                      Top = 172
                      Width = 75
                      Height = 25
                      Caption = 'Add'
                      Enabled = False
                      TabOrder = 3
                      OnClick = pdAddButtonClick
                    end
                    object pdDeleteButton: TButton
                      Left = 281
                      Top = 201
                      Width = 75
                      Height = 25
                      Caption = 'Delete'
                      Enabled = False
                      TabOrder = 4
                      OnClick = pdDeleteButtonClick
                    end
                    object pdNewPatternButton: TButton
                      Left = 272
                      Top = 78
                      Width = 84
                      Height = 25
                      Caption = 'New pattern'
                      Enabled = False
                      TabOrder = 5
                      OnClick = pdNewPatternButtonClick
                    end
                    object pdFileFlagNameComboBox: TComboBox
                      Left = 97
                      Top = 175
                      Width = 176
                      Height = 21
                      ItemHeight = 13
                      TabOrder = 6
                    end
                    object pdDeletePatternButton: TButton
                      Left = 273
                      Top = 105
                      Width = 83
                      Height = 25
                      Caption = 'Delete pattern'
                      Enabled = False
                      TabOrder = 7
                      OnClick = pdDeletePatternButtonClick
                    end
                    object pdTypeNameComboBox: TComboBox
                      Left = 96
                      Top = 105
                      Width = 121
                      Height = 21
                      Enabled = False
                      ItemHeight = 13
                      ItemIndex = 0
                      TabOrder = 8
                      Text = 'Optional'
                      OnChange = pdTypeNameComboBoxChange
                      Items.Strings = (
                        'Optional'
                        'Required'
                        'Recommended'
                        'CouldBeUsable'
                        'NotUsable')
                    end
                    object pdPatternsPageControl: TPageControl
                      Left = 3
                      Top = 46
                      Width = 353
                      Height = 29
                      TabOrder = 9
                      OnChange = pdPatternsPageControlChange
                    end
                    object pdStateValueComboBox: TComboBox
                      Left = 97
                      Top = 202
                      Width = 120
                      Height = 21
                      ItemHeight = 13
                      TabOrder = 10
                      Items.Strings = (
                        'Active'
                        'Inactive'
                        'Missing')
                    end
                  end
                end
              end
              object Panel8: TPanel
                Left = 2
                Top = 15
                Width = 696
                Height = 431
                Align = alClient
                BevelOuter = bvNone
                TabOrder = 1
                object Panel7: TPanel
                  Left = 0
                  Top = 281
                  Width = 696
                  Height = 150
                  Align = alBottom
                  BevelOuter = bvNone
                  TabOrder = 0
                  object Shape3: TShape
                    Left = 486
                    Top = 12
                    Width = 196
                    Height = 133
                  end
                  object Label20: TLabel
                    Left = 486
                    Top = 76
                    Width = 196
                    Height = 13
                    Align = alCustom
                    Alignment = taCenter
                    AutoSize = False
                    Caption = '[No image]'
                  end
                  object PluginImage: TImage
                    Left = 486
                    Top = 12
                    Width = 196
                    Height = 133
                    Stretch = True
                  end
                  object PluginImageEdit: TLabeledEdit
                    Left = 71
                    Top = 16
                    Width = 237
                    Height = 21
                    AutoSize = False
                    EditLabel.Width = 59
                    EditLabel.Height = 13
                    EditLabel.Caption = 'Plugin image'
                    Enabled = False
                    LabelPosition = lpLeft
                    ReadOnly = True
                    TabOrder = 0
                  end
                  object ClearPluginImageButton: TButton
                    Left = 395
                    Top = 16
                    Width = 75
                    Height = 25
                    Caption = 'Clear'
                    Enabled = False
                    TabOrder = 1
                    OnClick = ClearPluginImageButtonClick
                  end
                  object ChoosePluginImageButton: TButton
                    Left = 314
                    Top = 16
                    Width = 75
                    Height = 25
                    Caption = 'Choose'
                    Enabled = False
                    TabOrder = 2
                    OnClick = ChoosePluginImageButtonClick
                  end
                end
                object Panel9: TPanel
                  Left = 0
                  Top = 0
                  Width = 696
                  Height = 169
                  Align = alTop
                  BevelOuter = bvNone
                  TabOrder = 1
                  object Label4: TLabel
                    Left = 214
                    Top = 20
                    Width = 22
                    Height = 13
                    Caption = 'type'
                  end
                  object AddGroupButton: TButton
                    Left = 214
                    Top = 44
                    Width = 75
                    Height = 25
                    Caption = 'Add'
                    TabOrder = 0
                    OnClick = AddGroupButtonClick
                  end
                  object AddPluginButton: TButton
                    Left = 606
                    Top = 17
                    Width = 75
                    Height = 25
                    Caption = 'Add'
                    Enabled = False
                    TabOrder = 1
                    OnClick = AddPluginButtonClick
                  end
                  object GroupDownButton: TButton
                    Left = 214
                    Top = 137
                    Width = 75
                    Height = 25
                    Caption = 'Move down'
                    Enabled = False
                    TabOrder = 2
                    OnClick = GroupDownButtonClick
                  end
                  object GroupListView: TListView
                    Left = 9
                    Top = 44
                    Width = 199
                    Height = 118
                    Hint = 
                      'To edit: select destination path and then click on it again. It'#39 +
                      's like you rename files in Windows.'
                    Columns = <
                      item
                        Caption = 'Name'
                        Width = 100
                      end
                      item
                        Caption = 'Type'
                        Width = 75
                      end>
                    ColumnClick = False
                    GridLines = True
                    RowSelect = True
                    ParentShowHint = False
                    PopupMenu = PopupMenu
                    ShowHint = True
                    TabOrder = 3
                    ViewStyle = vsReport
                    OnEdited = GroupListViewEdited
                    OnSelectItem = GroupListViewSelectItem
                  end
                  object GroupNameEdit: TLabeledEdit
                    Left = 71
                    Top = 17
                    Width = 137
                    Height = 21
                    AutoSize = False
                    EditLabel.Width = 58
                    EditLabel.Height = 13
                    EditLabel.Caption = 'Group name'
                    LabelPosition = lpLeft
                    TabOrder = 4
                  end
                  object GroupTypeComboBox: TComboBox
                    Left = 242
                    Top = 17
                    Width = 112
                    Height = 21
                    Style = csDropDownList
                    ItemHeight = 13
                    ItemIndex = 0
                    TabOrder = 5
                    Text = 'SelectExactlyOne'
                    Items.Strings = (
                      'SelectExactlyOne'
                      'SelectAny'
                      'SelectAtMostOne'
                      'SelectAtLeastOne'
                      'SelectAll')
                  end
                  object GroupUpButton: TButton
                    Left = 214
                    Top = 106
                    Width = 75
                    Height = 25
                    Caption = 'Move up'
                    Enabled = False
                    TabOrder = 6
                    OnClick = GroupUpButtonClick
                  end
                  object PluginDownButton: TButton
                    Left = 606
                    Top = 137
                    Width = 75
                    Height = 25
                    Caption = 'Move down'
                    Enabled = False
                    TabOrder = 7
                    OnClick = PluginDownButtonClick
                  end
                  object PluginListView: TListView
                    Left = 402
                    Top = 44
                    Width = 199
                    Height = 118
                    Hint = 
                      'To edit: select destination path and then click on it again. It'#39 +
                      's like you rename files in Windows.'
                    Columns = <
                      item
                        Caption = 'Name'
                        Width = 175
                      end>
                    ColumnClick = False
                    GridLines = True
                    RowSelect = True
                    ParentShowHint = False
                    PopupMenu = PopupMenu
                    ShowHint = True
                    TabOrder = 8
                    ViewStyle = vsReport
                    OnEdited = PluginListViewEdited
                    OnSelectItem = PluginListViewSelectItem
                  end
                  object PluginNameEdit: TLabeledEdit
                    Left = 464
                    Top = 17
                    Width = 137
                    Height = 21
                    AutoSize = False
                    EditLabel.Width = 57
                    EditLabel.Height = 13
                    EditLabel.Caption = 'Plugin name'
                    LabelPosition = lpLeft
                    TabOrder = 9
                  end
                  object PluginUpButton: TButton
                    Left = 606
                    Top = 106
                    Width = 75
                    Height = 25
                    Caption = 'Move up'
                    Enabled = False
                    TabOrder = 10
                    OnClick = PluginUpButtonClick
                  end
                  object RemoveGroupButton: TButton
                    Left = 214
                    Top = 75
                    Width = 75
                    Height = 25
                    Caption = 'Remove'
                    Enabled = False
                    TabOrder = 11
                    OnClick = RemoveGroupButtonClick
                  end
                  object RemovePluginButton: TButton
                    Left = 606
                    Top = 44
                    Width = 75
                    Height = 25
                    Caption = 'Remove'
                    Enabled = False
                    TabOrder = 12
                    OnClick = RemovePluginButtonClick
                  end
                end
                object Panel10: TPanel
                  Left = 0
                  Top = 169
                  Width = 696
                  Height = 112
                  Align = alClient
                  BevelOuter = bvNone
                  Caption = 'Panel10'
                  Constraints.MinHeight = 100
                  Padding.Left = 8
                  Padding.Right = 8
                  TabOrder = 2
                  object Label5: TLabel
                    Left = 8
                    Top = 0
                    Width = 680
                    Height = 18
                    Align = alTop
                    AutoSize = False
                    Caption = 'Plugin description'
                  end
                  object PluginDescriptionMemo: TMemo
                    Left = 8
                    Top = 18
                    Width = 680
                    Height = 94
                    Align = alClient
                    Enabled = False
                    ScrollBars = ssVertical
                    TabOrder = 0
                    OnChange = PluginDescriptionMemoChange
                  end
                end
              end
            end
            object StepSettingsGroupBox: TGroupBox
              Left = 0
              Top = 0
              Width = 1067
              Height = 49
              Align = alTop
              Caption = 'Step settings'
              TabOrder = 2
              object StepNameEdit: TLabeledEdit
                Left = 80
                Top = 19
                Width = 355
                Height = 21
                AutoSize = False
                EditLabel.Width = 51
                EditLabel.Height = 13
                EditLabel.Caption = 'Step name'
                LabelPosition = lpLeft
                TabOrder = 0
                Text = 'Step1'
                OnChange = StepNameEditChange
              end
            end
          end
        end
        object ConditionsTabSheet: TTabSheet
          Caption = 'Conditions'
          ImageIndex = 1
          object ScrollBox: TScrollBox
            Left = 0
            Top = 0
            Width = 1071
            Height = 676
            Align = alClient
            TabOrder = 0
            object GroupBox4: TGroupBox
              Left = 0
              Top = 0
              Width = 1067
              Height = 672
              Align = alClient
              Caption = 'Condition set'
              TabOrder = 0
              object Label1: TLabel
                Left = 16
                Top = 21
                Width = 6
                Height = 13
                Caption = 'if'
              end
              object Label3: TLabel
                Left = 351
                Top = 43
                Width = 34
                Height = 13
                AutoSize = False
                Caption = 'equals'
              end
              object Label16: TLabel
                Left = 16
                Top = 43
                Width = 22
                Height = 13
                Alignment = taCenter
                Caption = 'type'
              end
              object ConditionComboBox: TComboBox
                Left = 120
                Top = 40
                Width = 225
                Height = 21
                ItemHeight = 13
                TabOrder = 0
              end
              object ConditionValueComboBox: TComboBox
                Left = 399
                Top = 40
                Width = 87
                Height = 21
                ItemHeight = 13
                TabOrder = 1
                Text = 'On'
                Items.Strings = (
                  'On'
                  'Off'
                  'Active'
                  'Inactive'
                  'Missing')
              end
              object ConditionListView: TListView
                Left = 16
                Top = 67
                Width = 521
                Height = 510
                Columns = <
                  item
                    Caption = 'type'
                  end
                  item
                    Caption = 'File/Flag name'
                    Width = 290
                  end
                  item
                  end
                  item
                    Caption = 'Value'
                  end
                  item
                  end>
                ColumnClick = False
                GridLines = True
                ReadOnly = True
                RowSelect = True
                TabOrder = 2
                ViewStyle = vsReport
              end
              object AddConditionButton: TButton
                Left = 543
                Top = 36
                Width = 75
                Height = 25
                Caption = 'Add'
                TabOrder = 3
                OnClick = AddConditionButtonClick
              end
              object DeleteConditionButton: TButton
                Left = 543
                Top = 67
                Width = 75
                Height = 25
                Caption = 'Delete'
                TabOrder = 4
                OnClick = DeleteConditionButtonClick
              end
              object VisibilityTypeComboBox: TComboBox
                Left = 52
                Top = 40
                Width = 51
                Height = 21
                Style = csDropDownList
                ItemHeight = 13
                ItemIndex = 1
                TabOrder = 5
                Text = 'flag'
                OnChange = VisibilityTypeComboBoxChange
                Items.Strings = (
                  'file'
                  'flag')
              end
            end
          end
        end
      end
      object StepsTabControl: TPageControl
        Left = 0
        Top = 0
        Width = 1079
        Height = 27
        ActivePage = TabSheet1
        Align = alTop
        TabOrder = 2
        OnChange = StepsTabControlChange
        object TabSheet1: TTabSheet
          Caption = 'Step1'
        end
      end
    end
    object RequiredInstalsTabSheet: TTabSheet
      Caption = 'Required instalations'
      Enabled = False
      ImageIndex = 3
      object Panel11: TPanel
        Left = 0
        Top = 0
        Width = 1079
        Height = 772
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Label2: TLabel
          Left = 16
          Top = 7
          Width = 45
          Height = 13
          Caption = 'Copy this'
        end
        object Label21: TLabel
          Left = 525
          Top = 6
          Width = 31
          Height = 13
          Caption = 'DATA\'
        end
        object AddRequiredFileButton: TButton
          Left = 980
          Top = 29
          Width = 75
          Height = 25
          Caption = 'Add file'
          TabOrder = 0
          OnClick = AddRequiredFileButtonClick
        end
        object AddRequiredFolderButton: TButton
          Left = 980
          Top = 60
          Width = 75
          Height = 25
          Caption = 'Add folder'
          TabOrder = 1
          OnClick = AddRequiredFolderButtonClick
        end
        object RequiredFilesDstListView: TListView
          Left = 525
          Top = 25
          Width = 449
          Height = 112
          Hint = 
            'To edit: select destination path and then click on it again. It'#39 +
            's like you rename files in Windows.'
          Columns = <
            item
              Caption = 'Destination path'
              Width = 425
            end>
          ColumnClick = False
          GridLines = True
          RowSelect = True
          ParentShowHint = False
          PopupMenu = PopupMenu
          ShowHint = True
          TabOrder = 2
          ViewStyle = vsReport
          OnEdited = RequiredFilesDstListViewEdited
          OnSelectItem = RequiredFilesDstListViewSelectItem
        end
        object RemoveRequiredFileFolderButton: TButton
          Left = 980
          Top = 91
          Width = 75
          Height = 25
          Caption = 'Remove'
          Enabled = False
          TabOrder = 3
          OnClick = RemoveRequiredFileFolderButtonClick
        end
        object RequiredFilesSrcListView: TListView
          Left = 16
          Top = 26
          Width = 503
          Height = 111
          Columns = <
            item
              Caption = 'File/Folder'
              Width = 70
            end
            item
              Caption = 'Source path'
              Width = 409
            end>
          ColumnClick = False
          GridLines = True
          ReadOnly = True
          RowSelect = True
          TabOrder = 4
          ViewStyle = vsReport
          OnSelectItem = RequiredFilesSrcListViewSelectItem
        end
      end
    end
    object ConditionalInstalsTabSheet: TTabSheet
      Caption = 'Conditional instalations'
      Enabled = False
      ImageIndex = 4
      object ConiditionalFilesPageControl: TPageControl
        Left = 0
        Top = 0
        Width = 1079
        Height = 27
        Align = alTop
        TabOrder = 0
        OnChange = ConiditionalFilesPageControlChange
      end
      object Panel12: TPanel
        Left = 0
        Top = 731
        Width = 1079
        Height = 41
        Align = alBottom
        TabOrder = 1
        object Panel13: TPanel
          Left = 664
          Top = 1
          Width = 414
          Height = 39
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 0
          object RemoveCondFilePatternButton: TButton
            Left = 248
            Top = 5
            Width = 79
            Height = 25
            Caption = 'Delete pattern'
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = RemoveCondFilePatternButtonClick
          end
          object AddCondFilePatternButton: TButton
            Left = 333
            Top = 5
            Width = 75
            Height = 25
            Caption = 'New pattern'
            TabOrder = 1
            OnClick = AddCondFilePatternButtonClick
          end
          object MoveLeftCondFilePatternButton: TButton
            Left = 5
            Top = 5
            Width = 75
            Height = 25
            Caption = 'Move left'
            Enabled = False
            TabOrder = 2
            OnClick = MoveLeftCondFilePatternButtonClick
          end
          object MoveRightCondFilePatternButton: TButton
            Left = 83
            Top = 5
            Width = 75
            Height = 25
            Caption = 'Move right'
            Enabled = False
            TabOrder = 3
            OnClick = MoveRightCondFilePatternButtonClick
          end
        end
      end
      object Panel14: TPanel
        Left = 0
        Top = 27
        Width = 1079
        Height = 208
        Align = alTop
        TabOrder = 2
        object Label24: TLabel
          Left = 17
          Top = 23
          Width = 44
          Height = 13
          Alignment = taCenter
          Caption = 'Operator'
        end
        object Label25: TLabel
          Left = 471
          Top = 50
          Width = 85
          Height = 13
          Alignment = taCenter
          Caption = 'Dependency type'
        end
        object Label26: TLabel
          Left = 471
          Top = 77
          Width = 69
          Height = 13
          Alignment = taCenter
          Caption = 'File/Flag name'
        end
        object Label27: TLabel
          Left = 471
          Top = 101
          Width = 26
          Height = 13
          Caption = 'Value'
        end
        object CondFilePatternOperatorComboBox: TComboBox
          Left = 77
          Top = 20
          Width = 51
          Height = 21
          Enabled = False
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 0
          Text = 'And'
          OnChange = CondFilePatternOperatorComboBoxChange
          Items.Strings = (
            'And'
            'Or')
        end
        object CondFileDependTypeComboBox: TComboBox
          Left = 562
          Top = 47
          Width = 51
          Height = 21
          Style = csDropDownList
          Enabled = False
          ItemHeight = 13
          ItemIndex = 1
          TabOrder = 1
          Text = 'flag'
          OnChange = CondFileDependTypeComboBoxChange
          Items.Strings = (
            'file'
            'flag')
        end
        object CondFileDependValueComboBox: TComboBox
          Left = 562
          Top = 101
          Width = 120
          Height = 21
          Enabled = False
          ItemHeight = 13
          TabOrder = 2
          Items.Strings = (
            'Active'
            'Inactive'
            'Missing')
        end
        object CondFilePatternListView: TListView
          Left = 16
          Top = 47
          Width = 353
          Height = 144
          Columns = <
            item
              Caption = 'Type'
            end
            item
              AutoSize = True
              Caption = 'File/Flag name'
            end
            item
              Caption = 'State/Value'
              Width = 70
            end
            item
              Caption = 'Operator'
              Width = 60
            end>
          ColumnClick = False
          GridLines = True
          ReadOnly = True
          RowSelect = True
          TabOrder = 3
          ViewStyle = vsReport
          OnSelectItem = CondFilePatternListViewSelectItem
        end
        object AddCondFileConditionButton: TButton
          Left = 375
          Top = 45
          Width = 75
          Height = 25
          Caption = 'Add'
          Enabled = False
          TabOrder = 4
          OnClick = AddCondFileConditionButtonClick
        end
        object RemoveCondFileConditionButton: TButton
          Left = 375
          Top = 74
          Width = 75
          Height = 25
          Caption = 'Delete'
          Enabled = False
          TabOrder = 5
          OnClick = RemoveCondFileConditionButtonClick
        end
        object CondFileDependNameComboBox: TComboBox
          Left = 562
          Top = 74
          Width = 176
          Height = 21
          Enabled = False
          ItemHeight = 13
          TabOrder = 6
        end
      end
      object Panel15: TPanel
        Left = 0
        Top = 235
        Width = 1079
        Height = 496
        Align = alClient
        TabOrder = 3
        object Label22: TLabel
          Left = 525
          Top = 6
          Width = 31
          Height = 13
          Caption = 'DATA\'
        end
        object Label23: TLabel
          Left = 16
          Top = 7
          Width = 45
          Height = 13
          Caption = 'Copy this'
        end
        object CondFilesDstListView: TListView
          Left = 525
          Top = 25
          Width = 449
          Height = 112
          Hint = 
            'To edit: select destination path and then click on it again. It'#39 +
            's like you rename files in Windows.'
          Columns = <
            item
              Caption = 'Destination path'
              Width = 425
            end>
          ColumnClick = False
          GridLines = True
          RowSelect = True
          ParentShowHint = False
          PopupMenu = PopupMenu
          ShowHint = True
          TabOrder = 0
          ViewStyle = vsReport
          OnEdited = CondFilesDstListViewEdited
          OnSelectItem = CondFilesDstListViewSelectItem
        end
        object CondFilesSrcListView: TListView
          Left = 16
          Top = 26
          Width = 503
          Height = 111
          Columns = <
            item
              Caption = 'File/Folder'
              Width = 70
            end
            item
              Caption = 'Source path'
              Width = 409
            end>
          ColumnClick = False
          GridLines = True
          ReadOnly = True
          RowSelect = True
          TabOrder = 1
          ViewStyle = vsReport
          OnSelectItem = CondFilesSrcListViewSelectItem
        end
        object CondFileAddFileButton: TButton
          Left = 980
          Top = 29
          Width = 75
          Height = 25
          Caption = 'Add file'
          TabOrder = 2
          OnClick = CondFileAddFileButtonClick
        end
        object CondFileAddFolderButton: TButton
          Left = 980
          Top = 60
          Width = 75
          Height = 25
          Caption = 'Add folder'
          TabOrder = 3
          OnClick = CondFileAddFolderButtonClick
        end
        object CondFileRemoveFileFolderButton: TButton
          Left = 980
          Top = 91
          Width = 75
          Height = 25
          Caption = 'Remove'
          Enabled = False
          TabOrder = 4
          OnClick = CondFileRemoveFileFolderButtonClick
        end
      end
    end
    object InfoTabSheet: TTabSheet
      Caption = 'Info'
      ImageIndex = 2
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 1079
        Height = 772
        Align = alClient
        Lines.Strings = (
          'FOMOD Creation Tool'
          'Quick guide'
          ''
          'Preparation.'
          
            'First of first you should prepare folder where will be your mod ' +
            'files and '#39'fomod'#39' folder. it'#39's up to you how you organize struct' +
            'ure of your mod, but keep in mind that some people may want to d' +
            'o manual installation so '
          'making this structure reasonable is good idea.'
          ''
          '1. Program menu.'
          '1.1. FOMOD menu.'
          
            '1.1.1. New. Delete all steps if such exist, cleans all mod info ' +
            'fields, clean root catalog.'
          
            '1.1.2. Open folder. Opens existing fomod .xml files. You should ' +
            'specify root folder that contains '#39'fomod'#39' folder. FOMOD Creation' +
            ' Tool since 1.2 version support unicode text only in UTF-16 (UCS' +
            '-2) Little Endian '
          
            'encoding. If fomod that you willing to open in other that this e' +
            'ncoding you should convert it manually. To do this open .xml'#39's f' +
            'ile in Window Notepad, choose '#39'File->Save as'#39' menu, in save wind' +
            'ow choose encoding '
          
            #39'Unicode'#39', save file with same name, replace existing one. If yo' +
            'u using Notepad++ open .xml file, choose '#39'Encoding->Encode in UC' +
            'S-2 Little Endian'#39', save file.'
          
            '1.1.3. Open file. Opens existing fomod .xml files. You may choos' +
            'e info.xml or ModuleConfig.xml file, FOMOD CT will catch up pair' +
            ' for it if such exist. FOMOD Creation Tool since 1.2 version sup' +
            'port unicode text only in '
          'UTF-16 (UCS-2) Little Endian encoding.'
          
            '1.1.4. Save. Saves fomod .xml files. FOMOD Creation Tool since 1' +
            '.2 version support unicode text only in UTF-16 (UCS-2) Little En' +
            'dian encoding and will save files in this encoding.'
          
            '1.1.5. Merge FOMOD. Allow you to merge two FOMODs. Fomod recipie' +
            'nt should be loaded from file or created, fomod donor you specif' +
            'y in dialog window. Choose only ModuleConfig.xml files. Steps, r' +
            'equired files and '
          
            'conditional installations would be added to the end of recipient' +
            ' fomod.'
          '1.1.6. Exit. Exits from program.'
          '1.2. Script menu.'
          
            '1.2.1. Run before save. Opens window where you can write down so' +
            'me Windows console based script. This script will be compiled in' +
            ' Windows .bat file and executed before your fomod will be saved.' +
            ' You can use '
          
            'FOMOD Creation Tool macro to insert specific data in script. Mor' +
            'e about supported macro you can read in script window.'
          'Example:'
          'del "$MODROOT$\*.rar" /q'
          'This deletes existing .rar archives from root catalog.'
          
            '1.2.2. Run after save. Opens window where you can write down som' +
            'e Windows console based script. This script will be compiled in ' +
            'Windows .bat file and executed after your fomod saved. You can u' +
            'se FOMOD Creation '
          
            'Tool macro to insert specific data in script. More about support' +
            'ed macro you can read in script window.'
          'Example:'
          'd:'
          'cd "$MODROOT$"'
          
            '"C:\Program Files\WinRAR\rar.exe" a -r -ep1 "$MODNAME$_$MODVERSI' +
            'ON$.rar" *'
          
            'This will change active drive to D:\. Then set active path to mo' +
            'd root directory. Then using WinRar pack all files in root direc' +
            'tory in archive named with mod name and mod version.'
          ''
          '2. Programm main interface.'
          '2.1. Mod info.'
          
            'At start of programm you'#39'll see '#39'Mod info'#39' tab where you put inf' +
            'ormation about your mod.'
          '2.1.1. Mod information.'
          'Mod name - name of your mod.'
          'Mod author - it'#39's you, comrade.'
          'Mod version - i think it'#39's understandable.'
          
            'Mod page on Nexus - URL to your mod'#39's page on www.nexusmods.com.' +
            ' To get it create file in your account on Nexus, but not upload ' +
            'anything and not publish it, you'#39'll be able to copy URL of your ' +
            'future mod now.'
          
            'Mod description - text that will be shown in right part of NMM w' +
            'hen your mod selected. This field can be multiline, but that doe' +
            'sn'#39't mean that in NMM (or any other mod installer) this descript' +
            'ion will be multilined. Use '
          
            'some special codes or BB codes in order to get correct page layo' +
            'ut.'
          'Mod category - category on Nexus your mod belong.'
          
            'Technically this fields not necessary but you want your mod look' +
            ' gleam and neat, aren'#39't you?'
          '2.1.2. Workspace.'
          
            'There you set root folder, which you prepare and where will be y' +
            'our mod files and '#39'fomod'#39' folder, if there no '#39'fomod'#39' folder pro' +
            'gramm will offer you to create one. After workspace is setted co' +
            'rrectly '#39'Proceed'#39' button is '
          
            'enabled. Once '#39'Proceed'#39' button hited you'#39'll see '#39'Steps'#39' tab and ' +
            'not be able to change root directory.'
          '2.2. Steps.'
          'Basic tab where you create your FOMOD installation.'
          '2.2.1. Groups and Files'
          
            '2.2.1.1. Step name. Sets name of step in installation, will not ' +
            'be displayed anywhere, it'#39's for your convenience but it can'#39't be' +
            ' empty.'
          
            '2.2.1.2. Groups. Add at least one group to each step. Group name' +
            ' will be displayed at left part of instalation window. Choose ty' +
            'pe for your groups. You may change group name from context menu ' +
            'or by selecting '
          
            'group in list end then press left mouse button again on it, just' +
            ' like you rename files in Windows. Group type can'#39't be changed. ' +
            'There is four types:'
          
            '- SelectExatlyOne - you can select only one option in group, can' +
            #39't select none or several.'
          
            '- SelectAny - you can select none, several or all options in gro' +
            'up;'
          
            '- SelectAtMostOne - you can select none or only one option in gr' +
            'oups.'
          
            '- SelectAtLeastOne - you can select one, several ar all options ' +
            'in group, can'#39't select none.'
          '- SelectAll - you must select all options in group.'
          
            '2.2.1.3. Plugins. Plugins is a options under groups wich you cho' +
            'ose upon instalation. At least one plugin must be in each group.' +
            ' Group must be selected in group list in order to add plugin in ' +
            'it. You may change plugin '
          
            'name from context menu or by selecting plugin in list end then p' +
            'ress left mouse button again on it, just like you rename files i' +
            'n Windows.'
          
            '2.2.1.4. Plugin description. Text that will be shown in right to' +
            'p part of instalation window when plugin is selected by user. Th' +
            'is field can be multiline, but that doesn'#39't mean that in NMM (or' +
            ' any other mod installer) this '
          
            'description will be multilined. Use some special codes or BB cod' +
            'es in order to get correct page layout. Plugin must be selected ' +
            'in order to add description.'
          
            '2.2.1.5. Plugin image. Image that will be shown at right bottom ' +
            'part of instalation window when plugin is selected by user. Use ' +
            'english letters in image name. It will be wise to put you images' +
            ' in '#39'fomod'#39' folder, but nit '
          
            'necessary. Plugin must be selected in order to add description. ' +
            'Image must belong to root directory.'
          
            '2.2.1.6. Variable set. If you making FOMOD instalation with cond' +
            'otions you should operate with some variables. Every plugin may ' +
            'set several variables to any text value, '#39'On'#39' and '#39'Off'#39' for exam' +
            'ple. If you don'#39't need '
          
            'conditions leave it blanck. Plugin must be selected in order to ' +
            'add varible.'
          
            '2.2.1.7. Plugin dependencies. For more experienced modders. Here' +
            ' you can set conditions for showing information messages to user' +
            ' and, in theory, auto-checking plugins. Note: text in messages i' +
            's pre-defined by '
          'fomod installer, not this program. Fields:'
          
            'Default type name - specifies default type of plugin. Can be set' +
            ' to: Optional, Required, Recommended, CouldBeUsable, Not Usable.' +
            ' If you don'#39't add dependency patterns this field will be transla' +
            'ted to xml as '
          
            'typeDescriptor/type, otherwise typeDescriptor/dependency Type/de' +
            'faultType.'
          
            'Operator - specifies logic of conditions, should they all be mee' +
            't or enough only one to be true. Can be set to '#39'And'#39' or '#39'Or'#39'.'
          
            'Type name - same as default type name but valid only for one dep' +
            'endency pattern.'
          
            'Dependency type - specifies would be condition based on file dep' +
            'endency or flag. Available if at least one dependency pattern cr' +
            'eated.'
          
            'File/Flag name - self explanatory. Available if at least one dep' +
            'endency pattern created.'
          
            'State(Value) - value to be meet for condition to be true. Availa' +
            'ble if at least one dependency pattern created.'
          
            '2.2.1.8. Files. Each plugin may instal some files. You may add f' +
            'iles one by one to plugin or add entire folder. Plugin must be s' +
            'elected in order to add files and/or folders. Note: path for fil' +
            'es and folders is relative, but '
          
            'source path relate from root directory, place where '#39'fomod'#39' fold' +
            'er is, and destination path relates from '#39'DATA'#39' folder in game d' +
            'irectory. FOMOD Creation Tool will attempt to automatically dete' +
            'rmine correct destination '
          
            'path. Program recognize files: .esp, .esm; also recognize folder' +
            's: STRINGS, TEXTURES, MUSIC, SOUND, INTERFACE, MESHES, PROGRAMS,' +
            ' MATERIALS, LODSETTINGS, VIS, MISC, SCRIPTS, SHADERSFX. You may '
          
            'change destination path from context menu or by selecting file i' +
            'n list end then press left mouse button again on it, just like y' +
            'ou rename files in Windows.'
          '2.2.2. Conditions.'
          
            'If you making FOMOD instalation with multiple steps and conditio' +
            'ns you must set this conditions.'
          
            '2.2.2.1. Condition set. When you setted variables for your plugi' +
            'ns (group options) this variables will be available in dropdown ' +
            'list. Choose one or several and choose corresponding comparison ' +
            'value. If variable is equal '
          
            'to comparison value this step will be shown in instalation. If n' +
            'ot then step will be skiped and hiden from user. If several cond' +
            'ition setted then all of them should be fulfilled at the same ti' +
            'me.'
          '2.3. Required installations.'
          'Files specified here will be installed under any circumstances.'
          '2.4. Conditional installations.'
          
            'Files specified here will be installed depending on conditions w' +
            'hich may be flags and/or other files. Conditional installation s' +
            'plitted into patterns. Each patterns consist of a set of depende' +
            'ncies, logic operator between it, '
          
            'and set of files that will be installed if result condition is t' +
            'rue. '
          '2.5. Finalization.'
          
            'Choose FOMOD->Save menu when you set everithing you wnated. '#39'inf' +
            'o.xml'#39' and '#39'ModuleConfig.xml'#39' files will be created in '#39'fomod'#39' d' +
            'irectory. Now you can pack you mod in archive and test it before' +
            ' uploading anywhere. ')
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object SaveConfirmationPanel: TPanel
    Left = 1055
    Top = 0
    Width = 408
    Height = 79
    TabOrder = 1
    Visible = False
    object Label18: TLabel
      Left = 24
      Top = 16
      Width = 152
      Height = 23
      Caption = 'Saving info.xml ...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 24
      Top = 43
      Width = 235
      Height = 23
      Caption = 'Saving ModuleConfig.xml ...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object mdlconfXMLStateLabel: TLabel
      Left = 296
      Top = 43
      Width = 64
      Height = 23
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object infoXMLStateLabel: TLabel
      Left = 296
      Top = 16
      Width = 64
      Height = 23
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofEnableSizing]
    Left = 792
    Top = 24
  end
  object OpenFolderDialog: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoPathMustExist]
    Left = 872
    Top = 24
  end
  object MainMenu: TMainMenu
    Left = 712
    Top = 24
    object File1: TMenuItem
      Caption = 'FOMOD'
      object NewMenu: TMenuItem
        Caption = 'New'
        OnClick = NewMenuClick
      end
      object OpenMenu: TMenuItem
        Caption = 'Open folder'
        ShortCut = 16463
        OnClick = OpenMenuClick
      end
      object OpenfileMenu: TMenuItem
        Caption = 'Open file'
        OnClick = OpenfileMenuClick
      end
      object SaveMenu: TMenuItem
        Caption = 'Save'
        Enabled = False
        ShortCut = 16467
        OnClick = SaveMenuClick
      end
      object MergeFOMODMenu: TMenuItem
        Caption = 'Merge FOMOD'
        Enabled = False
        OnClick = MergeFOMODMenuClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object ExitMenu: TMenuItem
        Caption = 'Exit'
        ShortCut = 32883
        OnClick = ExitMenuClick
      end
    end
    object Script1: TMenuItem
      Caption = 'Script'
      object RunBeforeSaveMenu: TMenuItem
        Caption = 'Run before save'
        OnClick = RunBeforeSaveMenuClick
      end
      object RunAfterSaveMenu: TMenuItem
        Caption = 'Run after save'
        OnClick = RunAfterSaveMenuClick
      end
    end
  end
  object ShowConfirmationTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = ShowConfirmationTimerTimer
    Left = 592
    Top = 24
  end
  object PopupMenu: TPopupMenu
    OnPopup = PopupMenuPopup
    Left = 960
    Top = 24
    object EditListElementCMenu: TMenuItem
      Caption = 'Edit'
      OnClick = EditListElementCMenuClick
    end
  end
end
