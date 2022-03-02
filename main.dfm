object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'FOMOD Creation Tool'
  ClientHeight = 858
  ClientWidth = 1108
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
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 1108
    Height = 858
    ActivePage = ModInfoTabSheet
    Align = alClient
    TabOrder = 0
    OnChange = StepsTabControlChange
    object ModInfoTabSheet: TTabSheet
      Caption = 'Mod info'
      object ModInfoGroupBox: TGroupBox
        Left = 0
        Top = 0
        Width = 1100
        Height = 718
        Align = alClient
        Caption = 'Mod infornation'
        TabOrder = 0
        object Panel5: TPanel
          Left = 2
          Top = 15
          Width = 1096
          Height = 290
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object ModCategoryLabel: TLabel
            Left = 13
            Top = 124
            Width = 66
            Height = 13
            Caption = 'Mod category'
          end
          object ModNameLabel: TLabel
            Left = 13
            Top = 16
            Width = 49
            Height = 13
            Caption = 'Mod name'
          end
          object ModAuthorLabel: TLabel
            Left = 14
            Top = 43
            Width = 55
            Height = 13
            Caption = 'Mod author'
          end
          object ModVersionLabel: TLabel
            Left = 13
            Top = 70
            Width = 58
            Height = 13
            Caption = 'Mod version'
          end
          object ModURLLabel: TLabel
            Left = 13
            Top = 97
            Width = 95
            Height = 13
            Caption = 'Mod page on Nexus'
          end
          object ModHeaderImageLabel: TLabel
            Left = 13
            Top = 151
            Width = 88
            Height = 13
            Caption = 'Mod header image'
          end
          object Shape4: TShape
            Left = 734
            Top = 151
            Width = 196
            Height = 133
          end
          object NoHeaderImageLabel: TLabel
            Left = 734
            Top = 208
            Width = 196
            Height = 76
            Align = alCustom
            Alignment = taCenter
            AutoSize = False
            Caption = '[No image]'
          end
          object HeaderImage: TImage
            Left = 734
            Top = 151
            Width = 196
            Height = 133
            Stretch = True
          end
          object ModCategoryComboBox: TComboBox
            Left = 159
            Top = 121
            Width = 346
            Height = 21
            ItemHeight = 13
            TabOrder = 4
            OnChange = ModCategoryEditChange
            Items.Strings = (
              'Ammo'
              'Animation'
              'Armour'
              'Audio - Misc'
              'Audio - Music'
              'Audio - SFX'
              'Audio - Voice'
              'Body, Face, and Hair'
              'Bug Fixes'
              'Buildings'
              'Character Presets'
              'Cheats and God items'
              'Clothing'
              'Clothing - Backpacks'
              'Collectibles, Treasure Hunts, and Puzzles'
              'Companions'
              'Crafting - Equipment'
              'Crafting - Home/Settlement'
              'Crafting - Other'
              'Creatures'
              'ENB Presets'
              'Environment'
              'Factions'
              'Gameplay Effects and Changes'
              'Immersion'
              'Items (Food, Drinks, Chems, etc)'
              'Locations - New'
              'Locations - Vanilla'
              'Miscellaneous'
              'Modders Resources and Tutorials'
              'Models and Textures'
              'New Lands'
              'NPC'
              'NPC - Vendors'
              'Overhauls'
              'Patches'
              'Performance'
              'Perks'
              'Pip-Boy'
              'Player Homes'
              'Player Settlement'
              'Poses'
              'Power Armour'
              'Quests and Adventures'
              'Radio'
              'ReShade Presets'
              'Save Games'
              'Skills and Leveling'
              'Tattoos'
              'Transfer Settlement Blueprints'
              'User Interface'
              'Utilities'
              'Vehicles'
              'Videos and Trailers'
              'Visuals and Graphics'
              'Weapons'
              'Weapons and Armour'
              'Weather and Lighting')
          end
          object ModAuthorEdit: TEdit
            Left = 159
            Top = 40
            Width = 346
            Height = 21
            TabOrder = 1
            OnChange = ModAuthorEditChange
          end
          object ModNameEdit: TEdit
            Left = 159
            Top = 13
            Width = 346
            Height = 21
            TabOrder = 0
            OnChange = ModNameEditChange
          end
          object ModVersionEdit: TEdit
            Left = 159
            Top = 67
            Width = 146
            Height = 21
            TabOrder = 2
            OnChange = ModVersionEditChange
          end
          object ModURLEdit: TEdit
            Left = 159
            Top = 94
            Width = 346
            Height = 21
            TabOrder = 3
            OnChange = ModURLEditChange
          end
          object ClearHeaderImageButton: TButton
            Left = 623
            Top = 148
            Width = 75
            Height = 25
            Caption = 'Clear'
            TabOrder = 7
            OnClick = ClearHeaderImageButtonClick
          end
          object ChooseHeaderImageButton: TButton
            Left = 533
            Top = 148
            Width = 75
            Height = 25
            Caption = 'Choose'
            TabOrder = 6
            OnClick = ChooseHeaderImageButtonClick
          end
          object ModHeaderImageEdit: TEdit
            Left = 159
            Top = 148
            Width = 346
            Height = 21
            TabOrder = 5
          end
        end
        object Panel6: TPanel
          Left = 2
          Top = 305
          Width = 1096
          Height = 411
          Align = alClient
          BevelOuter = bvNone
          Caption = 'Panel6'
          Padding.Left = 14
          Padding.Right = 14
          Padding.Bottom = 14
          TabOrder = 1
          object ModDescriptionLabel: TLabel
            Left = 14
            Top = 0
            Width = 1068
            Height = 24
            Align = alTop
            AutoSize = False
            Caption = 'Mod description'
            ExplicitTop = 6
            ExplicitWidth = 1047
          end
          object ModDesccriptionMemo: TMemo
            Left = 14
            Top = 24
            Width = 1068
            Height = 373
            Align = alClient
            ScrollBars = ssVertical
            TabOrder = 0
            OnChange = ModDesccriptionMemoChange
          end
        end
      end
      object WorkSpaceGroupBox: TGroupBox
        Left = 0
        Top = 718
        Width = 1100
        Height = 64
        Align = alBottom
        Caption = 'Workspace'
        TabOrder = 1
        object RootDirLabel: TLabel
          Left = 15
          Top = 26
          Width = 69
          Height = 13
          Caption = 'Root directory'
        end
        object OpenRootDirButton: TButton
          Left = 551
          Top = 24
          Width = 75
          Height = 25
          Caption = 'Open'
          TabOrder = 1
          OnClick = OpenRootDirButtonClick
        end
        object RootDirEdit: TEdit
          Left = 121
          Top = 23
          Width = 424
          Height = 21
          TabOrder = 0
          OnChange = RootDirEditChange
        end
      end
      object Panel3: TPanel
        Left = 0
        Top = 782
        Width = 1100
        Height = 48
        Align = alBottom
        TabOrder = 2
        object Panel4: TPanel
          Left = 952
          Top = 1
          Width = 147
          Height = 46
          Align = alRight
          BevelOuter = bvNone
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object ProceedButton: TButton
            Left = 14
            Top = 13
            Width = 116
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
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Panel1: TPanel
        Left = 0
        Top = 789
        Width = 1100
        Height = 41
        Align = alBottom
        TabOrder = 0
        object Panel2: TPanel
          Left = 533
          Top = 1
          Width = 566
          Height = 39
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 0
          object DeleteStepButton: TButton
            Left = 315
            Top = 5
            Width = 116
            Height = 25
            Caption = 'Delete step'
            Enabled = False
            TabOrder = 2
            OnClick = DeleteStepButtonClick
          end
          object NewStepButton: TButton
            Left = 437
            Top = 5
            Width = 116
            Height = 25
            Caption = 'New step'
            TabOrder = 3
            OnClick = NewStepButtonClick
          end
          object MoveLeftButton: TButton
            Left = 13
            Top = 5
            Width = 116
            Height = 25
            Caption = 'Move left'
            Enabled = False
            TabOrder = 0
            OnClick = MoveLeftButtonClick
          end
          object MoveRightButton: TButton
            Left = 135
            Top = 5
            Width = 116
            Height = 25
            Caption = 'Move right'
            Enabled = False
            TabOrder = 1
            OnClick = MoveRightButtonClick
          end
        end
      end
      object StepsPageControl: TPageControl
        Left = 0
        Top = 27
        Width = 1100
        Height = 762
        ActivePage = GroupsFileTabSheet
        Align = alClient
        TabOrder = 1
        object GroupsFileTabSheet: TTabSheet
          Caption = 'Groups and Files'
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 1092
            Height = 734
            HorzScrollBar.Range = 1066
            VertScrollBar.Range = 617
            Align = alClient
            AutoScroll = False
            TabOrder = 0
            object FilesGroupBox: TGroupBox
              Left = 0
              Top = 497
              Width = 1088
              Height = 233
              Align = alClient
              Caption = 'Files'
              TabOrder = 2
              object FilesPanel: TPanel
                Left = 2
                Top = 15
                Width = 1084
                Height = 216
                Align = alClient
                BevelOuter = bvNone
                TabOrder = 0
                object CpyLabel: TLabel
                  Left = 16
                  Top = 7
                  Width = 45
                  Height = 13
                  Caption = 'Copy this'
                end
                object DataLabel: TLabel
                  Left = 525
                  Top = 6
                  Width = 31
                  Height = 13
                  Caption = 'DATA\'
                end
                object AddFileButton: TButton
                  Left = 980
                  Top = 29
                  Width = 101
                  Height = 25
                  Caption = 'Add file'
                  Enabled = False
                  TabOrder = 0
                  OnClick = AddFileButtonClick
                end
                object AddFolderButton: TButton
                  Left = 980
                  Top = 60
                  Width = 101
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
                      Width = 375
                    end
                    item
                      Caption = 'Priority'
                    end>
                  ColumnClick = False
                  GridLines = True
                  RowSelect = True
                  ParentShowHint = False
                  PopupMenu = PopupMenuFiles
                  ShowHint = True
                  TabOrder = 2
                  ViewStyle = vsReport
                  OnEdited = DstFilesListViewEdited
                  OnSelectItem = DstFilesListViewSelectItem
                end
                object RemoveFileFolderButton: TButton
                  Left = 980
                  Top = 91
                  Width = 101
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
                  Height = 112
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
              Width = 1088
              Height = 448
              Align = alTop
              Caption = 'Groups && plugins'
              TabOrder = 1
              object PageControl2: TPageControl
                Left = 719
                Top = 15
                Width = 367
                Height = 431
                ActivePage = FlagSetTabSheet
                Align = alRight
                TabOrder = 1
                object FlagSetTabSheet: TTabSheet
                  Caption = 'Flag set'
                  ExplicitLeft = 0
                  ExplicitTop = 0
                  ExplicitWidth = 0
                  ExplicitHeight = 0
                  object AddVaribleButton: TButton
                    Left = 281
                    Top = 20
                    Width = 75
                    Height = 25
                    Caption = 'Add'
                    Enabled = False
                    TabOrder = 1
                    OnClick = AddVaribleButtonClick
                  end
                  object DeleteVaribleButton: TButton
                    Left = 281
                    Top = 51
                    Width = 75
                    Height = 25
                    Caption = 'Delete'
                    Enabled = False
                    TabOrder = 2
                    OnClick = DeleteVaribleButtonClick
                  end
                  object Panel17: TPanel
                    Left = 0
                    Top = 0
                    Width = 275
                    Height = 403
                    Align = alLeft
                    BevelOuter = bvNone
                    TabOrder = 0
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
                      object FNameLabel: TLabel
                        Left = 4
                        Top = 5
                        Width = 173
                        Height = 28
                        Alignment = taCenter
                        AutoSize = False
                        Caption = 'Flag name'
                      end
                      object FSetLabel: TLabel
                        Left = 185
                        Top = 25
                        Width = 15
                        Height = 13
                        Caption = 'set'
                      end
                      object VaribleComboBox: TComboBox
                        Left = 3
                        Top = 24
                        Width = 176
                        Height = 21
                        ItemHeight = 0
                        TabOrder = 0
                      end
                      object VaribleValueComboBox: TComboBox
                        Left = 223
                        Top = 24
                        Width = 50
                        Height = 21
                        ItemHeight = 0
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
                  ExplicitLeft = 0
                  ExplicitTop = 0
                  ExplicitWidth = 0
                  ExplicitHeight = 0
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
                    object pdNameLabel: TLabel
                      Left = 3
                      Top = 177
                      Width = 69
                      Height = 13
                      Alignment = taCenter
                      Caption = 'File/Flag name'
                    end
                    object pdOperatorLabel: TLabel
                      Left = 3
                      Top = 81
                      Width = 44
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Operator'
                    end
                    object pdDepTypeLabel: TLabel
                      Left = 3
                      Top = 151
                      Width = 85
                      Height = 13
                      Alignment = taCenter
                      Caption = 'Dependency type'
                    end
                    object pdValueLabel: TLabel
                      Left = 3
                      Top = 205
                      Width = 26
                      Height = 13
                      Caption = 'State'
                    end
                    object pdTypeNameLabel: TLabel
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
                    object pdDefTypeNameLabel: TLabel
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
                      Left = 128
                      Top = 78
                      Width = 73
                      Height = 21
                      Enabled = False
                      ItemHeight = 0
                      ItemIndex = 0
                      TabOrder = 3
                      Text = 'And'
                      OnChange = pdOperatorComboBoxChange
                      Items.Strings = (
                        'And'
                        'Or')
                    end
                    object pdDefTypeComboBox: TComboBox
                      Left = 128
                      Top = 9
                      Width = 145
                      Height = 21
                      Enabled = False
                      ItemHeight = 0
                      ItemIndex = 0
                      TabOrder = 0
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
                      Left = 130
                      Top = 148
                      Width = 63
                      Height = 19
                      Style = csOwnerDrawFixed
                      Enabled = False
                      ItemHeight = 13
                      ItemIndex = 0
                      TabOrder = 6
                      Text = 'file'
                      OnChange = pdDependencyTypeComboBoxChange
                      Items.Strings = (
                        'file'
                        'flag')
                    end
                    object pdAddButton: TButton
                      Left = 255
                      Top = 172
                      Width = 101
                      Height = 25
                      Caption = 'Add'
                      Enabled = False
                      TabOrder = 9
                      OnClick = pdAddButtonClick
                    end
                    object pdDeleteButton: TButton
                      Left = 255
                      Top = 202
                      Width = 101
                      Height = 25
                      Caption = 'Delete'
                      Enabled = False
                      TabOrder = 10
                      OnClick = pdDeleteButtonClick
                    end
                    object pdNewPatternButton: TButton
                      Left = 255
                      Top = 78
                      Width = 101
                      Height = 25
                      Caption = 'New pattern'
                      Enabled = False
                      TabOrder = 2
                      OnClick = pdNewPatternButtonClick
                    end
                    object pdFileFlagNameComboBox: TComboBox
                      Left = 130
                      Top = 175
                      Width = 119
                      Height = 21
                      ItemHeight = 0
                      TabOrder = 7
                    end
                    object pdDeletePatternButton: TButton
                      Left = 255
                      Top = 105
                      Width = 101
                      Height = 25
                      Caption = 'Delete pattern'
                      Enabled = False
                      TabOrder = 5
                      OnClick = pdDeletePatternButtonClick
                    end
                    object pdTypeNameComboBox: TComboBox
                      Left = 127
                      Top = 105
                      Width = 122
                      Height = 21
                      Enabled = False
                      ItemHeight = 0
                      ItemIndex = 0
                      TabOrder = 4
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
                      TabOrder = 1
                      OnChange = pdPatternsPageControlChange
                    end
                    object pdStateValueComboBox: TComboBox
                      Left = 130
                      Top = 200
                      Width = 119
                      Height = 21
                      ItemHeight = 0
                      TabOrder = 8
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
                Width = 717
                Height = 431
                Align = alClient
                BevelOuter = bvNone
                TabOrder = 0
                object Panel7: TPanel
                  Left = 0
                  Top = 281
                  Width = 717
                  Height = 150
                  Align = alBottom
                  BevelOuter = bvNone
                  TabOrder = 2
                  object Shape3: TShape
                    Left = 486
                    Top = 12
                    Width = 196
                    Height = 133
                  end
                  object NoImageLabel: TLabel
                    Left = 486
                    Top = 72
                    Width = 196
                    Height = 74
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
                    TabOrder = 2
                    OnClick = ClearPluginImageButtonClick
                  end
                  object ChoosePluginImageButton: TButton
                    Left = 314
                    Top = 16
                    Width = 75
                    Height = 25
                    Caption = 'Choose'
                    Enabled = False
                    TabOrder = 1
                    OnClick = ChoosePluginImageButtonClick
                  end
                end
                object Panel9: TPanel
                  Left = 0
                  Top = 0
                  Width = 717
                  Height = 169
                  Align = alTop
                  BevelOuter = bvNone
                  TabOrder = 0
                  object GTypeLabel: TLabel
                    Left = 214
                    Top = 20
                    Width = 22
                    Height = 13
                    Caption = 'type'
                  end
                  object AddGroupButton: TButton
                    Left = 242
                    Top = 44
                    Width = 112
                    Height = 25
                    Caption = 'Add'
                    TabOrder = 3
                    OnClick = AddGroupButtonClick
                  end
                  object AddPluginButton: TButton
                    Left = 575
                    Top = 18
                    Width = 107
                    Height = 25
                    Caption = 'Add'
                    Enabled = False
                    TabOrder = 9
                    OnClick = AddPluginButtonClick
                  end
                  object GroupDownButton: TButton
                    Left = 242
                    Top = 137
                    Width = 112
                    Height = 25
                    Caption = 'Move down'
                    Enabled = False
                    TabOrder = 6
                    OnClick = GroupDownButtonClick
                  end
                  object GroupListView: TListView
                    Left = 9
                    Top = 44
                    Width = 227
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
                        Width = 103
                      end>
                    ColumnClick = False
                    GridLines = True
                    RowSelect = True
                    ParentShowHint = False
                    PopupMenu = PopupMenu2
                    ShowHint = True
                    TabOrder = 2
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
                    TabOrder = 0
                  end
                  object GroupTypeComboBox: TComboBox
                    Left = 242
                    Top = 17
                    Width = 112
                    Height = 19
                    Style = csOwnerDrawFixed
                    ItemHeight = 13
                    ItemIndex = 0
                    TabOrder = 1
                    Text = 'SelectExactlyOne'
                    Items.Strings = (
                      'SelectExactlyOne'
                      'SelectAny'
                      'SelectAtMostOne'
                      'SelectAtLeastOne'
                      'SelectAll')
                  end
                  object GroupUpButton: TButton
                    Left = 242
                    Top = 106
                    Width = 112
                    Height = 25
                    Caption = 'Move up'
                    Enabled = False
                    TabOrder = 5
                    OnClick = GroupUpButtonClick
                  end
                  object PluginDownButton: TButton
                    Left = 575
                    Top = 138
                    Width = 107
                    Height = 25
                    Caption = 'Move down'
                    Enabled = False
                    TabOrder = 12
                    OnClick = PluginDownButtonClick
                  end
                  object PluginListView: TListView
                    Left = 370
                    Top = 45
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
                    Left = 432
                    Top = 18
                    Width = 137
                    Height = 21
                    AutoSize = False
                    EditLabel.Width = 57
                    EditLabel.Height = 13
                    EditLabel.Caption = 'Plugin name'
                    LabelPosition = lpLeft
                    TabOrder = 7
                  end
                  object PluginUpButton: TButton
                    Left = 575
                    Top = 107
                    Width = 107
                    Height = 25
                    Caption = 'Move up'
                    Enabled = False
                    TabOrder = 11
                    OnClick = PluginUpButtonClick
                  end
                  object RemoveGroupButton: TButton
                    Left = 242
                    Top = 75
                    Width = 112
                    Height = 25
                    Caption = 'Remove'
                    Enabled = False
                    TabOrder = 4
                    OnClick = RemoveGroupButtonClick
                  end
                  object RemovePluginButton: TButton
                    Left = 575
                    Top = 45
                    Width = 107
                    Height = 25
                    Caption = 'Remove'
                    Enabled = False
                    TabOrder = 10
                    OnClick = RemovePluginButtonClick
                  end
                end
                object Panel10: TPanel
                  Left = 0
                  Top = 169
                  Width = 717
                  Height = 112
                  Align = alClient
                  BevelOuter = bvNone
                  Caption = 'Panel10'
                  Constraints.MinHeight = 100
                  Padding.Left = 8
                  Padding.Right = 8
                  TabOrder = 1
                  object PluginDescLabel: TLabel
                    Left = 8
                    Top = 0
                    Width = 701
                    Height = 18
                    Align = alTop
                    AutoSize = False
                    Caption = 'Plugin description'
                    ExplicitWidth = 680
                  end
                  object PluginDescriptionMemo: TMemo
                    Left = 8
                    Top = 18
                    Width = 701
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
              Width = 1088
              Height = 49
              Align = alTop
              Caption = 'Step settings'
              TabOrder = 0
              object StepNameLabel: TLabel
                Left = 18
                Top = 24
                Width = 51
                Height = 13
                Caption = 'Step name'
              end
              object StepNameEdit: TEdit
                Left = 103
                Top = 22
                Width = 253
                Height = 21
                TabOrder = 0
                OnChange = StepNameEditChange
              end
            end
          end
        end
        object ConditionsTabSheet: TTabSheet
          Caption = 'Conditions'
          ImageIndex = 1
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
          object ScrollBox: TScrollBox
            Left = 0
            Top = 0
            Width = 1092
            Height = 734
            Align = alClient
            TabOrder = 0
            object ConditionSetGroupBox: TGroupBox
              Left = 0
              Top = 0
              Width = 1088
              Height = 730
              Align = alClient
              Caption = 'Condition set'
              TabOrder = 0
              object IfLabel: TLabel
                Left = 16
                Top = 22
                Width = 6
                Height = 13
                Caption = 'if'
              end
              object equalsLabel: TLabel
                Left = 351
                Top = 44
                Width = 31
                Height = 13
                Caption = 'equals'
              end
              object typeLabel: TLabel
                Left = 16
                Top = 44
                Width = 22
                Height = 13
                Alignment = taCenter
                Caption = 'type'
              end
              object visOperatorLabel: TLabel
                Left = 504
                Top = 22
                Width = 44
                Height = 13
                Alignment = taCenter
                Caption = 'Operator'
              end
              object ConditionComboBox: TComboBox
                Left = 120
                Top = 41
                Width = 225
                Height = 21
                ItemHeight = 0
                TabOrder = 1
              end
              object ConditionValueComboBox: TComboBox
                Left = 399
                Top = 41
                Width = 87
                Height = 21
                ItemHeight = 0
                ItemIndex = 0
                TabOrder = 2
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
                Top = 68
                Width = 569
                Height = 510
                Columns = <
                  item
                    Caption = 'type'
                  end
                  item
                    Caption = 'File/Flag name'
                    Width = 340
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
                TabOrder = 6
                ViewStyle = vsReport
                OnSelectItem = ConditionListViewSelectItem
              end
              object AddConditionButton: TButton
                Left = 599
                Top = 39
                Width = 75
                Height = 25
                Caption = 'Add'
                TabOrder = 4
                OnClick = AddConditionButtonClick
              end
              object DeleteConditionButton: TButton
                Left = 599
                Top = 70
                Width = 75
                Height = 25
                Caption = 'Delete'
                Enabled = False
                TabOrder = 5
                OnClick = DeleteConditionButtonClick
              end
              object VisibilityTypeComboBox: TComboBox
                Left = 52
                Top = 41
                Width = 51
                Height = 19
                Style = csOwnerDrawFixed
                ItemHeight = 13
                ItemIndex = 1
                TabOrder = 0
                Text = 'flag'
                OnChange = VisibilityTypeComboBoxChange
                Items.Strings = (
                  'file'
                  'flag')
              end
              object visOperatorComboBox: TComboBox
                Left = 504
                Top = 41
                Width = 73
                Height = 21
                ItemHeight = 0
                ItemIndex = 0
                TabOrder = 3
                Text = 'And'
                OnChange = visOperatorComboBoxChange
                Items.Strings = (
                  'And'
                  'Or')
              end
            end
          end
        end
      end
      object StepsTabControl: TPageControl
        Left = 0
        Top = 0
        Width = 1100
        Height = 27
        Align = alTop
        TabOrder = 2
        OnChange = StepsTabControlChange
      end
    end
    object RequiredInstallsTabSheet: TTabSheet
      Caption = 'Required installations'
      Enabled = False
      ImageIndex = 3
      object Panel11: TPanel
        Left = 0
        Top = 0
        Width = 1100
        Height = 830
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object CpyLabel2: TLabel
          Left = 16
          Top = 7
          Width = 45
          Height = 13
          Caption = 'Copy this'
        end
        object DataLabel2: TLabel
          Left = 525
          Top = 6
          Width = 31
          Height = 13
          Caption = 'DATA\'
        end
        object AddRequiredFileButton: TButton
          Left = 980
          Top = 29
          Width = 101
          Height = 25
          Caption = 'Add file'
          TabOrder = 2
          OnClick = AddRequiredFileButtonClick
        end
        object AddRequiredFolderButton: TButton
          Left = 980
          Top = 60
          Width = 101
          Height = 25
          Caption = 'Add folder'
          TabOrder = 3
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
              Width = 375
            end
            item
              Caption = 'Priority'
            end>
          ColumnClick = False
          GridLines = True
          RowSelect = True
          ParentShowHint = False
          PopupMenu = PopupMenuFiles
          ShowHint = True
          TabOrder = 1
          ViewStyle = vsReport
          OnEdited = RequiredFilesDstListViewEdited
          OnSelectItem = RequiredFilesDstListViewSelectItem
        end
        object RemoveRequiredFileFolderButton: TButton
          Left = 980
          Top = 91
          Width = 101
          Height = 25
          Caption = 'Remove'
          Enabled = False
          TabOrder = 4
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
          TabOrder = 0
          ViewStyle = vsReport
          OnSelectItem = RequiredFilesSrcListViewSelectItem
        end
      end
    end
    object ConditionalInstallsTabSheet: TTabSheet
      Caption = 'Conditional installations'
      Enabled = False
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object ConiditionalFilesPageControl: TPageControl
        Left = 0
        Top = 0
        Width = 1100
        Height = 27
        Align = alTop
        TabOrder = 0
        OnChange = ConiditionalFilesPageControlChange
      end
      object Panel12: TPanel
        Left = 0
        Top = 789
        Width = 1100
        Height = 41
        Align = alBottom
        TabOrder = 3
        object Panel13: TPanel
          Left = 533
          Top = 1
          Width = 566
          Height = 39
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 0
          object RemoveCondFilePatternButton: TButton
            Left = 315
            Top = 5
            Width = 116
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
            Left = 437
            Top = 5
            Width = 116
            Height = 25
            Caption = 'New pattern'
            TabOrder = 1
            OnClick = AddCondFilePatternButtonClick
          end
          object MoveLeftCondFilePatternButton: TButton
            Left = 13
            Top = 5
            Width = 116
            Height = 25
            Caption = 'Move left'
            Enabled = False
            TabOrder = 2
            OnClick = MoveLeftCondFilePatternButtonClick
          end
          object MoveRightCondFilePatternButton: TButton
            Left = 135
            Top = 5
            Width = 116
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
        Width = 1100
        Height = 208
        Align = alTop
        TabOrder = 1
        object ciOperatorLabel: TLabel
          Left = 17
          Top = 23
          Width = 44
          Height = 13
          Alignment = taCenter
          Caption = 'Operator'
        end
        object ciDepTypeLabel: TLabel
          Left = 471
          Top = 50
          Width = 85
          Height = 13
          Alignment = taCenter
          Caption = 'Dependency type'
        end
        object ciNameLabel: TLabel
          Left = 471
          Top = 77
          Width = 69
          Height = 13
          Alignment = taCenter
          Caption = 'File/Flag name'
        end
        object ciValueLabel: TLabel
          Left = 471
          Top = 104
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
          ItemHeight = 0
          ItemIndex = 0
          TabOrder = 0
          Text = 'And'
          OnChange = CondFilePatternOperatorComboBoxChange
          Items.Strings = (
            'And'
            'Or')
        end
        object CondFileDependTypeComboBox: TComboBox
          Left = 598
          Top = 47
          Width = 51
          Height = 19
          Style = csOwnerDrawFixed
          Enabled = False
          ItemHeight = 13
          ItemIndex = 1
          TabOrder = 4
          Text = 'flag'
          OnChange = CondFileDependTypeComboBoxChange
          Items.Strings = (
            'file'
            'flag')
        end
        object CondFileDependValueComboBox: TComboBox
          Left = 598
          Top = 101
          Width = 120
          Height = 21
          Enabled = False
          ItemHeight = 0
          TabOrder = 6
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
          TabOrder = 1
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
          TabOrder = 2
          OnClick = AddCondFileConditionButtonClick
        end
        object RemoveCondFileConditionButton: TButton
          Left = 375
          Top = 74
          Width = 75
          Height = 25
          Caption = 'Delete'
          Enabled = False
          TabOrder = 3
          OnClick = RemoveCondFileConditionButtonClick
        end
        object CondFileDependNameComboBox: TComboBox
          Left = 598
          Top = 74
          Width = 176
          Height = 21
          Enabled = False
          ItemHeight = 0
          TabOrder = 5
        end
      end
      object Panel15: TPanel
        Left = 0
        Top = 235
        Width = 1100
        Height = 554
        Align = alClient
        TabOrder = 2
        object DataLabel3: TLabel
          Left = 525
          Top = 6
          Width = 31
          Height = 13
          Caption = 'DATA\'
        end
        object CpyLabel3: TLabel
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
              Width = 375
            end
            item
              Caption = 'Priority'
            end>
          ColumnClick = False
          GridLines = True
          RowSelect = True
          ParentShowHint = False
          PopupMenu = PopupMenuFiles
          ShowHint = True
          TabOrder = 1
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
          TabOrder = 0
          ViewStyle = vsReport
          OnSelectItem = CondFilesSrcListViewSelectItem
        end
        object CondFileAddFileButton: TButton
          Left = 980
          Top = 29
          Width = 101
          Height = 25
          Caption = 'Add file'
          TabOrder = 2
          OnClick = CondFileAddFileButtonClick
        end
        object CondFileAddFolderButton: TButton
          Left = 980
          Top = 60
          Width = 101
          Height = 25
          Caption = 'Add folder'
          TabOrder = 3
          OnClick = CondFileAddFolderButtonClick
        end
        object CondFileRemoveFileFolderButton: TButton
          Left = 980
          Top = 91
          Width = 101
          Height = 25
          Caption = 'Remove'
          Enabled = False
          TabOrder = 4
          OnClick = CondFileRemoveFileFolderButtonClick
        end
      end
    end
    object InfoTabSheet: TTabSheet
      Caption = 'Help'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 1100
        Height = 830
        Align = alClient
        Lines.Strings = (
          'FOMOD Creation Tool'
          'Quick guide'
          ' '
          'Preparation.'
          
            'First of first you should prepare folder where will be your mod ' +
            'files and '#39'fomod'#39' folder. it'#39's up to you how you organize struct' +
            'ure of your mod, but keep in mind that some people may want to d' +
            'o manual installation so making '
          'this structure reasonable is good idea.'
          ' '
          '1. Program menu.'
          '1.1. FOMOD menu.'
          
            '1.1.1. New. Delete all steps if such exist, cleans all mod info ' +
            'fields, clean root catalog.'
          
            '1.1.2. Open folder. Opens existing fomod .xml files. You should ' +
            'specify root folder that contains '#39'fomod'#39' folder. FOMOD Creation' +
            ' Tool mainly support unicode text in UTF-16 (UCS-2) Little Endia' +
            'n encoding, and since 1.6 '
          
            'version limitedly support UTF-8. Non-english symbols in UTF-8 ma' +
            'y be interpreted incorrectly.'
          
            '1.1.3. Open file. Opens existing fomod .xml files. You may choos' +
            'e info.xml or ModuleConfig.xml file, FOMOD CT will catch up pair' +
            ' for it if such exist. FOMOD Creation Tool mainly support unicod' +
            'e text in UTF-16 (UCS-2) Little '
          
            'Endian encoding, and since 1.6 version limitedly support UTF-8. ' +
            'Non-english symbols in UTF-8 may be interpreted incorrectly.'
          
            '1.1.4. Save. Saves fomod .xml files. FOMOD Creation Tool since 1' +
            '.2 version support unicode text only in UTF-16 (UCS-2) Little En' +
            'dian encoding and will save files in this encoding.'
          
            '1.1.5. Merge FOMOD. Allow you to merge two FOMODs. Fomod recipie' +
            'nt should be loaded from file or created, fomod donor you specif' +
            'y in dialog window. Choose only ModuleConfig.xml files. Steps, r' +
            'equired files and '
          
            'conditional installations would be added to the end of recipient' +
            ' fomod.'
          '1.1.6. Recent. List of recently opened/saved fomods.'
          '1.1.7. Exit. Exits from program.'
          '1.2. Options menu.'
          
            '1.2.1. Settings. Opens a settings window. Opens a settings windo' +
            'w. There you can choose language file, hide/show menu items '#39'Ope' +
            'n folder'#39' and '#39'Open file'#39'. Set interface text size (interface ma' +
            'y look clumsy with big '
          'letters).Manage recent files.'
          
            '1.2.2. Run before save. Opens window where you can write down so' +
            'me Windows console based script. This script will be compiled in' +
            ' Windows .bat file and executed before your fomod will be saved.' +
            ' You can use FOMOD '
          
            'Creation Tool macro to insert specific data in script. More abou' +
            't supported macro you can read in script window.'
          ''
          'Example:'
          ''
          'del "$MODROOT$\*.rar" /q'
          ''
          'This deletes existing .rar archives from root catalog.'
          
            '1.2.3. Run after save. Opens window where you can write down som' +
            'e Windows console based script. This script will be compiled in ' +
            'Windows .bat file and executed after your fomod saved. You can u' +
            'se FOMOD Creation '
          
            'Tool macro to insert specific data in script. More about support' +
            'ed macro you can read in script window.'
          ''
          'Example:'
          ''
          'd:'
          'cd "$MODROOT$"'
          
            '"C:\Program Files\WinRAR\rar.exe" a -r -ep1 "$MODNAME$_$MODVERSI' +
            'ON$.rar" *'
          ''
          
            'This will change active drive to D:\. Then set active path to mo' +
            'd root directory. Then using WinRar pack all files in root direc' +
            'tory in archive named with mod name and mod version.'
          ' '
          '2. Program main interface.'
          ''
          '2.1. Mod info.'
          
            'At start of program you'#39'll see '#39'Mod info'#39' tab where you put info' +
            'rmation about your mod.'
          '2.1.1. Mod information.'
          #8226'         Mod name - name of your mod.'
          #8226'         Mod author - it'#39's you, comrade.'
          #8226'         Mod version - i think it'#39's understandable.'
          
            #8226'         Mod page on Nexus - URL to your mod'#39's page on www.nexu' +
            'smods.com. To get it create file in your account on Nexus, but n' +
            'ot upload anything and not publish it, you'#39'll be able to copy UR' +
            'L of your future mod now.'
          
            #8226'         Mod header image - image that will be shown on top of ' +
            'installation window to the right from mod name.'
          
            #8226'         Mod description - text that will be shown in right par' +
            't of NMM when your mod selected. This field can be multiline, bu' +
            't that doesn'#39't mean that in NMM (or any other mod installer) thi' +
            's description will be multiline. Use '
          
            'some special codes or BB codes in order to get correct page layo' +
            'ut.'
          #8226'         Mod category - category on Nexus your mod belongs.'
          
            #8226'         Technically this fields not necessary but you want you' +
            'r mod look gleam and neat, aren'#39't you?'
          '2.1.2. Workspace.'
          
            'There you set root folder, which you prepare and where will be y' +
            'our mod files and '#39'fomod'#39' folder, if there no '#39'fomod'#39' folder pro' +
            'gram will offer you to create one. After workspace is set correc' +
            'tly '#39'Proceed'#39' button is enabled. '
          
            'Once '#39'Proceed'#39' button is click you'#39'll see '#39'Steps'#39' tab and not be' +
            ' able to change root directory.'
          ''
          '2.2. Steps.'
          'Basic tab where you create your FOMOD installation.'
          '2.2.1. Groups and Files'
          
            '2.2.1.1. Step name. Sets name of step in installation, will not ' +
            'be displayed anywhere, it'#39's for your convenience but it can'#39't be' +
            ' empty.'
          
            '2.2.1.2. Groups. Add at least one group to each step. Group name' +
            ' will be displayed at left part of installation window. Choose t' +
            'ype for your groups. You may change group name from context menu' +
            ' or by selecting group in '
          
            'list end then press left mouse button again on it, just like you' +
            ' rename files in Windows. Group can be changed via context menu.' +
            ' There are four types of groups:'
          
            #8226'         SelectExatlyOne - you can select only one option in gr' +
            'oup, can'#39't select none or several.'
          
            #8226'         SelectAny - you can select none, several or all option' +
            's in group;'
          
            #8226'         SelectAtMostOne - you can select none or only one opti' +
            'on in groups.'
          
            #8226'         SelectAtLeastOne - you can select one, several or all ' +
            'options in group, can'#39't select none.'
          #8226'         SelectAll - you must select all options in group.'
          
            '2.2.1.3. Plugins. Plugins is a options under groups which you ch' +
            'oose upon installation. At least one plugin must be in each grou' +
            'p. Group must be selected in group list in order to add plugin i' +
            'n it. You may change plugin name '
          
            'from context menu or by selecting plugin in list end then press ' +
            'left mouse button again on it, just like you rename files in Win' +
            'dows.'
          
            '2.2.1.4. Plugin description. Text that will be shown in right to' +
            'p part of installation window when plugin is selected by user. T' +
            'his field can be multiline, but that doesn'#39't mean that in NMM (o' +
            'r any other mod installer) this '
          
            'description will be multiline. Use some special codes or BB code' +
            's in order to get correct page layout. Plugin must be selected i' +
            'n order to add description.'
          
            '2.2.1.5. Plugin image. Image that will be shown at right bottom ' +
            'part of installation window when plugin is selected by user. Use' +
            ' English letters in image name. It will be wise to put you image' +
            's in '#39'fomod'#39' folder, but nit '
          
            'necessary. Plugin must be selected in order to add description. ' +
            'Image must belong to root directory.'
          
            '2.2.1.6. Variable set. If you are making FOMOD installation with' +
            ' conditions you should operate with some variables. Every plugin' +
            ' may set several variables to any text value, '#39'On'#39' and '#39'Off'#39' for' +
            ' example. If you don'#39't need '
          
            'conditions leave it blank. Plugin must be selected in order to a' +
            'dd variable.'
          
            '2.2.1.7. Plugin dependencies. For more experienced modders. Here' +
            ' you can set conditions for showing information messages to user' +
            ' and, in theory, auto-checking plugins. Note: text in messages i' +
            's pre-defined by fomod '
          'installer, not this program. Fields:'
          
            #8226'         Default type name - specifies default type of plugin. ' +
            'Can be set to: Optional, Required, Recommended, CouldBeUsable, N' +
            'ot Usable. If you don'#39't add dependency patterns this field will ' +
            'be translated to xml as '
          
            'typeDescriptor/type, otherwise typeDescriptor/dependency Type/de' +
            'faultType.'
          
            #8226'         Operator - specifies logic of conditions, should they ' +
            'all be meet or enough only one to be true. Can be set to '#39'And'#39' o' +
            'r '#39'Or'#39'.'
          
            #8226'         Type name - same as default type name but valid only f' +
            'or one dependency pattern.'
          
            #8226'         Dependency type - specifies would be condition based o' +
            'n file dependency or flag. Available if at least one dependency ' +
            'pattern created.'
          
            #8226'         File/Flag name - self-explanatory. Available if at lea' +
            'st one dependency pattern created.'
          
            #8226'         State(Value) - value to be meet for condition to be tr' +
            'ue. Available if at least one dependency pattern created.'
          
            '2.2.1.8. Files. Each plugin may install some files. You may add ' +
            'files one by one to plugin or add entire folder. Plugin must be ' +
            'selected in order to add files and/or folders. Each file/folder ' +
            'have three main property: source '
          
            'path, destination path, priority. Path for files and folders is ' +
            'relative, but source path relates from root directory, place whe' +
            're '#39'fomod'#39' folder is, and destination path relates from '#39'DATA'#39' f' +
            'older in game directory. FOMOD '
          
            'Creation Tool will attempt to automatically determine correct de' +
            'stination path. Program recognize files: .esp, .esm; also recogn' +
            'ize folders: STRINGS, TEXTURES, MUSIC, SOUND, INTERFACE, MESHES,' +
            ' PROGRAMS, '
          
            'MATERIALS, LODSETTINGS, VIS, MISC, SCRIPTS, SHADERSFX. Priority ' +
            'determine order in which files/folders will be installed. Files ' +
            'with lower priority number will be installed first, with highest' +
            ' - last. Priority may be used in '
          
            'case your installation will overwrite its own files. For example' +
            ', by default your mod install files from folders A, B and C, but' +
            ' if user choose some option then fomod installer should take fil' +
            'es from catalog '#208' and overwrite files '
          
            'installed from catalog B. So, to not let things go wrong, like f' +
            'iles from B overwrites D, '#208' files should have priority number hi' +
            'gher then B. Priority also may be used to specify order in which' +
            ' files will be placed in mods load '
          
            'order. Files with lower priority number will be higher in load o' +
            'rder. You may change destination path and priority from context ' +
            'menu or by selecting file in list end then press left mouse butt' +
            'on again on it, just like you rename '
          'files in Windows.'
          '2.2.2. Conditions.'
          
            'If you are making FOMOD installation with multiple steps and con' +
            'ditions you must set the conditions.'
          
            '2.2.2.1. Condition set. When you setted variables for your plugi' +
            'ns (group options) these variables will be available in dropdown' +
            ' list. Choose one or several and choose corresponding comparison' +
            ' value. If variable is equal to '
          
            'comparison value this step will be shown in installation. If not' +
            ' then step will be skipped and hidden from user. If several cond' +
            'ition setted then all of them should be fulfilled at the same ti' +
            'me.'
          ''
          '2.3. Required installations.'
          'Files specified here will be installed under any circumstances.'
          ''
          '2.4. Conditional installations.'
          
            'Files specified here will be installed depending on conditions w' +
            'hich may be flags and/or other files. Conditional installation s' +
            'plit into patterns. Each pattern consists of a set of dependenci' +
            'es, logic operator between it, and set '
          'of files that will be installed if result condition is true.'
          ''
          '2.5. Finalization.'
          
            'Choose FOMOD->Save menu when you set everything you wanted. '#39'inf' +
            'o.xml'#39' and '#39'ModuleConfig.xml'#39' files will be created in '#39'fomod'#39' d' +
            'irectory. Now you can pack you mod in archive and test it before' +
            ' uploading anywhere.'
          ' '
          '3. Language files.'
          
            'FOMOD CT from version 1.5 support multi language interface and u' +
            'se language files for this. Language file is a simple text file ' +
            'in unicode UTF-16 Little Endian encoding. It consist of list of ' +
            'pairs key = "value". Users are free '
          'to make their own language, for this follow this instruction:'
          '1.       Copy any existing language file in '#39'Language'#39' catalog.'
          
            '2.       Set name of this copy to correspond language you are ab' +
            'out to translate.'
          '3.       Open it any text editor you prefer, select all and cut.'
          
            '4.       Open any translator that support whole text translation' +
            '. For example google translator. Past text to it. Don'#39't forget t' +
            'o specify languages from and to which you are translating.'
          
            '5.       Check the result. Keys should not be translated, file s' +
            'hould save it structure key = "value" where only value should be' +
            ' translated. Manually edit translation if needed.'
          
            '6.       Copy your translation and past in copied file, save it.' +
            ' Now you can choose this language file from settings window in F' +
            'OMOD CT.'
          ''
          
            'Redacted by Valyn81. Nexus: https://rd.nexusmods.com/fallout4/us' +
            'ers/2283611')
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object SaveConfirmationPanel: TPanel
    Left = 1014
    Top = -12
    Width = 427
    Height = 79
    TabOrder = 1
    Visible = False
    object SavingInfoLabel: TLabel
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
    object SavingConfigLabel: TLabel
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
      Left = 336
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
      Left = 336
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
  object FilePriorityEdit: TEdit
    Left = 916
    Top = 664
    Width = 52
    Height = 21
    Enabled = False
    NumbersOnly = True
    TabOrder = 2
    Text = '0'
    Visible = False
    OnExit = FilePriorityEditExit
    OnKeyPress = FilePriorityEditKeyPress
  end
  object EditGroupTypeComboBox: TComboBox
    Left = 96
    Top = 247
    Width = 105
    Height = 21
    Enabled = False
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 3
    Text = 'SelectExactlyOne'
    Visible = False
    OnExit = EditGroupTypeComboBoxExit
    OnKeyPress = EditGroupTypeComboBoxKeyPress
    Items.Strings = (
      'SelectExactlyOne'
      'SelectAny'
      'SelectAtMostOne'
      'SelectAtLeastOne'
      'SelectAll')
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofEnableSizing, ofDontAddToRecent]
    Left = 496
    Top = 24
  end
  object OpenFolderDialog: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoPathMustExist]
    Left = 576
    Top = 24
  end
  object MainMenu: TMainMenu
    Left = 416
    Top = 24
    object FOMODMenu: TMenuItem
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
      object RecentMenu: TMenuItem
        Caption = 'Recent'
        object RecentFileTemplate: TMenuItem
          Caption = '-'
          Enabled = False
          OnClick = RecentFileTemplateClick
        end
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
    object OptionsMenu: TMenuItem
      Caption = 'Options'
      object SettingsMenu: TMenuItem
        Caption = 'Settings'
        OnClick = SettingsMenuClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
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
    Left = 328
    Top = 24
  end
  object PopupMenu: TPopupMenu
    OnPopup = PopupMenuPopup
    Left = 656
    Top = 24
    object EditListElementCMenu: TMenuItem
      Caption = 'Edit'
      OnClick = EditListElementCMenuClick
    end
  end
  object PopupMenu2: TPopupMenu
    OnPopup = PopupMenu2Popup
    Left = 720
    Top = 24
    object EditListElementCMenu2: TMenuItem
      Caption = 'Edit name'
      OnClick = EditListElementCMenu2Click
    end
    object EditGroupTypeCMenu2: TMenuItem
      Caption = 'Edit type'
      OnClick = EditGroupTypeCMenu2Click
    end
  end
  object PopupMenuFiles: TPopupMenu
    OnPopup = PopupMenuFilesPopup
    Left = 792
    Top = 24
    object EditPathCMenu: TMenuItem
      Caption = 'Edit path'
      OnClick = EditPathCMenuClick
    end
    object EditPriorityCMenu: TMenuItem
      Caption = 'Edit priority'
      OnClick = EditPriorityCMenuClick
    end
  end
end
