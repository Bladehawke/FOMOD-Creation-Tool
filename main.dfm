object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'FOMOD Creation Tool'
  ClientHeight = 773
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
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 1087
    Height = 773
    ActivePage = ModInfoTabSheet
    Align = alClient
    TabOrder = 0
    object ModInfoTabSheet: TTabSheet
      Caption = 'Mod info'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 1079
        Height = 433
        Align = alTop
        Caption = 'Mod infornation'
        TabOrder = 0
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
          Height = 262
          Align = alClient
          BevelOuter = bvNone
          Caption = 'Panel6'
          Padding.Left = 14
          Padding.Right = 14
          Padding.Bottom = 14
          TabOrder = 1
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
            Height = 224
            Align = alClient
            TabOrder = 0
            OnChange = ModDesccriptionMemoChange
          end
        end
      end
      object WorkSpaceGroupBox: TGroupBox
        Left = 0
        Top = 433
        Width = 1079
        Height = 64
        Align = alTop
        Caption = 'Workspace'
        TabOrder = 1
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
        Top = 697
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
      ImageIndex = 1
      TabVisible = False
      object Panel1: TPanel
        Left = 0
        Top = 704
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
        Height = 677
        ActivePage = GroupsFileTabSheet
        Align = alClient
        TabOrder = 1
        object GroupsFileTabSheet: TTabSheet
          Caption = 'Groups and Files'
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 1071
            Height = 649
            HorzScrollBar.Range = 1066
            VertScrollBar.Range = 617
            Align = alClient
            AutoScroll = False
            TabOrder = 0
            object FilesGroupBox: TGroupBox
              Left = 0
              Top = 481
              Width = 1067
              Height = 140
              Align = alTop
              Caption = 'Files'
              TabOrder = 0
              object Label8: TLabel
                Left = 18
                Top = 23
                Width = 45
                Height = 13
                Caption = 'Copy this'
              end
              object Label9: TLabel
                Left = 525
                Top = 22
                Width = 31
                Height = 13
                Caption = 'DATA\'
              end
              object SrcFilesListView: TListView
                Left = 16
                Top = 42
                Width = 503
                Height = 86
                Columns = <
                  item
                    Caption = 'File/Folder'
                    Width = 70
                  end
                  item
                    Caption = 'Source path'
                    Width = 425
                  end>
                ColumnClick = False
                GridLines = True
                ReadOnly = True
                RowSelect = True
                TabOrder = 0
                ViewStyle = vsReport
                OnChange = SrcFilesListViewChange
                OnClick = SrcFilesListViewClick
              end
              object AddFileButton: TButton
                Left = 969
                Top = 40
                Width = 75
                Height = 25
                Caption = 'Add file'
                Enabled = False
                TabOrder = 1
                OnClick = AddFileButtonClick
              end
              object AddFolderButton: TButton
                Left = 969
                Top = 71
                Width = 75
                Height = 25
                Caption = 'Add folder'
                Enabled = False
                TabOrder = 2
                OnClick = AddFolderButtonClick
              end
              object RemoveFileFolderButton: TButton
                Left = 969
                Top = 102
                Width = 75
                Height = 25
                Caption = 'Remove'
                Enabled = False
                TabOrder = 3
                OnClick = RemoveFileFolderButtonClick
              end
              object DstFilesListView: TListView
                Left = 525
                Top = 41
                Width = 438
                Height = 86
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
                TabOrder = 4
                ViewStyle = vsReport
                OnChange = DstFilesListViewChange
                OnClick = DstFilesListViewClick
                OnEdited = DstFilesListViewEdited
              end
            end
            object GroupsGroupBox: TGroupBox
              Left = 0
              Top = 49
              Width = 1067
              Height = 432
              Align = alTop
              Caption = 'Groups && plugins'
              TabOrder = 1
              object Shape3: TShape
                Left = 485
                Top = 288
                Width = 196
                Height = 133
              end
              object Label4: TLabel
                Left = 223
                Top = 21
                Width = 22
                Height = 13
                Caption = 'type'
              end
              object Label5: TLabel
                Left = 18
                Top = 169
                Width = 83
                Height = 13
                Caption = 'Plugin description'
              end
              object Label20: TLabel
                Left = 485
                Top = 346
                Width = 196
                Height = 13
                Align = alCustom
                Alignment = taCenter
                AutoSize = False
                Caption = '[No image]'
              end
              object PluginImage: TImage
                Left = 485
                Top = 288
                Width = 196
                Height = 133
                Stretch = True
              end
              object GroupNameEdit: TLabeledEdit
                Left = 80
                Top = 18
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
                Left = 251
                Top = 18
                Width = 112
                Height = 21
                Style = csDropDownList
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
              object AddGroupButton: TButton
                Left = 223
                Top = 45
                Width = 75
                Height = 25
                Caption = 'Add'
                TabOrder = 2
                OnClick = AddGroupButtonClick
              end
              object RemoveGroupButton: TButton
                Left = 223
                Top = 76
                Width = 75
                Height = 25
                Caption = 'Remove'
                Enabled = False
                TabOrder = 3
                OnClick = RemoveGroupButtonClick
              end
              object PluginNameEdit: TLabeledEdit
                Left = 473
                Top = 18
                Width = 137
                Height = 21
                AutoSize = False
                EditLabel.Width = 57
                EditLabel.Height = 13
                EditLabel.Caption = 'Plugin name'
                LabelPosition = lpLeft
                TabOrder = 4
              end
              object RemovePluginButton: TButton
                Left = 616
                Top = 45
                Width = 75
                Height = 25
                Caption = 'Remove'
                Enabled = False
                TabOrder = 5
                OnClick = RemovePluginButtonClick
              end
              object AddPluginButton: TButton
                Left = 616
                Top = 18
                Width = 75
                Height = 25
                Caption = 'Add'
                Enabled = False
                TabOrder = 6
                OnClick = AddPluginButtonClick
              end
              object PluginDescriptionMemo: TMemo
                Left = 18
                Top = 188
                Width = 673
                Height = 94
                Enabled = False
                TabOrder = 7
                OnChange = PluginDescriptionMemoChange
              end
              object ChoosePluginImageButton: TButton
                Left = 323
                Top = 288
                Width = 75
                Height = 25
                Caption = 'Choose'
                Enabled = False
                TabOrder = 8
                OnClick = ChoosePluginImageButtonClick
              end
              object ClearPluginImageButton: TButton
                Left = 404
                Top = 288
                Width = 75
                Height = 25
                Caption = 'Clear'
                Enabled = False
                TabOrder = 9
                OnClick = ClearPluginImageButtonClick
              end
              object PluginImageEdit: TLabeledEdit
                Left = 80
                Top = 290
                Width = 237
                Height = 21
                AutoSize = False
                EditLabel.Width = 59
                EditLabel.Height = 13
                EditLabel.Caption = 'Plugin image'
                Enabled = False
                LabelPosition = lpLeft
                ReadOnly = True
                TabOrder = 10
              end
              object GroupListView: TListView
                Left = 18
                Top = 45
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
                    AutoSize = True
                    Caption = 'Type'
                  end>
                ColumnClick = False
                GridLines = True
                RowSelect = True
                ParentShowHint = False
                PopupMenu = PopupMenu
                ShowHint = True
                TabOrder = 11
                ViewStyle = vsReport
                OnChange = GroupListViewChange
                OnClick = GroupListViewClick
                OnEdited = GroupListViewEdited
              end
              object GroupUpButton: TButton
                Left = 223
                Top = 107
                Width = 75
                Height = 25
                Caption = 'Move up'
                Enabled = False
                TabOrder = 12
                OnClick = GroupUpButtonClick
              end
              object GroupDownButton: TButton
                Left = 223
                Top = 138
                Width = 75
                Height = 25
                Caption = 'Move down'
                Enabled = False
                TabOrder = 13
                OnClick = GroupDownButtonClick
              end
              object PluginUpButton: TButton
                Left = 616
                Top = 107
                Width = 75
                Height = 25
                Caption = 'Move up'
                Enabled = False
                TabOrder = 14
                OnClick = PluginUpButtonClick
              end
              object PluginDownButton: TButton
                Left = 616
                Top = 138
                Width = 75
                Height = 25
                Caption = 'Move down'
                Enabled = False
                TabOrder = 15
                OnClick = PluginDownButtonClick
              end
              object PluginListView: TListView
                Left = 411
                Top = 45
                Width = 199
                Height = 118
                Hint = 
                  'To edit: select destination path and then click on it again. It'#39 +
                  's like you rename files in Windows.'
                Columns = <
                  item
                    AutoSize = True
                    Caption = 'Name'
                  end>
                ColumnClick = False
                GridLines = True
                RowSelect = True
                ParentShowHint = False
                PopupMenu = PopupMenu
                ShowHint = True
                TabOrder = 16
                ViewStyle = vsReport
                OnChange = PluginListViewChange
                OnClick = PluginListViewClick
                OnEdited = PluginListViewEdited
              end
              object PageControl2: TPageControl
                Left = 697
                Top = 18
                Width = 367
                Height = 407
                ActivePage = VariableSetTabSheet
                TabOrder = 17
                object VariableSetTabSheet: TTabSheet
                  Caption = 'Variable set'
                  object Label6: TLabel
                    Left = 4
                    Top = 5
                    Width = 121
                    Height = 13
                    Alignment = taCenter
                    AutoSize = False
                    Caption = 'variable'
                  end
                  object Label7: TLabel
                    Left = 185
                    Top = 25
                    Width = 34
                    Height = 13
                    AutoSize = False
                    Caption = 'set'
                  end
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
                  object VaribleComboBox: TComboBox
                    Left = 3
                    Top = 24
                    Width = 176
                    Height = 21
                    ItemHeight = 13
                    TabOrder = 2
                  end
                  object VaribleSetListView: TListView
                    Left = 3
                    Top = 51
                    Width = 272
                    Height = 326
                    Columns = <
                      item
                        Caption = 'Variable'
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
                    TabOrder = 3
                    ViewStyle = vsReport
                    OnChange = VaribleSetListViewChange
                    OnClick = VaribleSetListViewClick
                  end
                  object VaribleValueComboBox: TComboBox
                    Left = 225
                    Top = 24
                    Width = 50
                    Height = 21
                    ItemHeight = 13
                    ItemIndex = 0
                    TabOrder = 4
                    Text = 'On'
                    Items.Strings = (
                      'On'
                      'Off')
                  end
                end
                object PluginDependenciesTabSheet: TTabSheet
                  Caption = 'Plugin dependencies'
                  ImageIndex = 1
                  object Label12: TLabel
                    Left = 3
                    Top = 205
                    Width = 26
                    Height = 13
                    Caption = 'State'
                  end
                  object Label13: TLabel
                    Left = 3
                    Top = 151
                    Width = 85
                    Height = 13
                    Alignment = taCenter
                    Caption = 'Dependency type'
                  end
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
                  object Shape2: TShape
                    Left = 3
                    Top = 137
                    Width = 353
                    Height = 1
                  end
                  object Label17: TLabel
                    Left = 3
                    Top = 108
                    Width = 53
                    Height = 13
                    Alignment = taCenter
                    Caption = 'Type name'
                  end
                  object PluginDependenciesListView: TListView
                    Left = 3
                    Top = 232
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
                    TabOrder = 0
                    ViewStyle = vsReport
                    OnChange = PluginDependenciesListViewChange
                    OnClick = PluginDependenciesListViewClick
                  end
                  object pdStateValueComboBox: TComboBox
                    Left = 97
                    Top = 202
                    Width = 120
                    Height = 21
                    ItemHeight = 13
                    TabOrder = 1
                    Items.Strings = (
                      'Active'
                      'Inactive'
                      'Missing')
                  end
                  object pdAddButton: TButton
                    Left = 281
                    Top = 172
                    Width = 75
                    Height = 25
                    Caption = 'Add'
                    Enabled = False
                    TabOrder = 2
                    OnClick = pdAddButtonClick
                  end
                  object pdDeleteButton: TButton
                    Left = 281
                    Top = 201
                    Width = 75
                    Height = 25
                    Caption = 'Delete'
                    Enabled = False
                    TabOrder = 3
                    OnClick = pdDeleteButtonClick
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
                    TabOrder = 4
                    Text = 'file'
                    OnChange = pdDependencyTypeComboBoxChange
                    Items.Strings = (
                      'file'
                      'flag')
                  end
                  object pdFileFlagNameEdit: TEdit
                    Left = 96
                    Top = 175
                    Width = 179
                    Height = 21
                    TabOrder = 5
                  end
                  object pdOperatorComboBox: TComboBox
                    Left = 96
                    Top = 78
                    Width = 51
                    Height = 21
                    Enabled = False
                    ItemHeight = 13
                    ItemIndex = 0
                    TabOrder = 6
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
                    TabOrder = 7
                    Text = 'Optional'
                    OnChange = pdDefTypeComboBoxChange
                    Items.Strings = (
                      'Optional'
                      'Required'
                      'Recommended'
                      'CouldBeUsable'
                      'NotUsable')
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
                  object pdDeletePatternButton: TButton
                    Left = 273
                    Top = 105
                    Width = 83
                    Height = 25
                    Caption = 'Delete pattern'
                    Enabled = False
                    TabOrder = 10
                    OnClick = pdDeletePatternButtonClick
                  end
                  object pdNewPatternButton: TButton
                    Left = 272
                    Top = 78
                    Width = 84
                    Height = 25
                    Caption = 'New pattern'
                    Enabled = False
                    TabOrder = 11
                    OnClick = pdNewPatternButtonClick
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
            Height = 649
            Align = alClient
            TabOrder = 0
            object GroupBox4: TGroupBox
              Left = 0
              Top = 0
              Width = 1067
              Height = 645
              Align = alClient
              Caption = 'Condition set'
              TabOrder = 0
              object Label1: TLabel
                Left = 16
                Top = 40
                Width = 6
                Height = 13
                Caption = 'if'
              end
              object Label2: TLabel
                Left = 40
                Top = 21
                Width = 225
                Height = 13
                Alignment = taCenter
                AutoSize = False
                Caption = 'variable'
              end
              object Label3: TLabel
                Left = 271
                Top = 40
                Width = 34
                Height = 13
                AutoSize = False
                Caption = 'equals'
              end
              object ConditionComboBox: TComboBox
                Left = 40
                Top = 40
                Width = 225
                Height = 21
                Style = csDropDownList
                ItemHeight = 13
                TabOrder = 0
              end
              object ConditionValueComboBox: TComboBox
                Left = 311
                Top = 40
                Width = 50
                Height = 21
                Style = csDropDownList
                ItemHeight = 13
                ItemIndex = 0
                TabOrder = 1
                Text = 'On'
                Items.Strings = (
                  'On'
                  'Off')
              end
              object ConditionListView: TListView
                Left = 16
                Top = 67
                Width = 417
                Height = 262
                Columns = <
                  item
                    Caption = 'Variable'
                    Width = 250
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
                Left = 439
                Top = 36
                Width = 75
                Height = 25
                Caption = 'Add'
                TabOrder = 3
                OnClick = AddConditionButtonClick
              end
              object DeleteConditionButton: TButton
                Left = 439
                Top = 67
                Width = 75
                Height = 25
                Caption = 'Delete'
                TabOrder = 4
                OnClick = DeleteConditionButtonClick
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
    object InfoTabSheet: TTabSheet
      Caption = 'Info'
      ImageIndex = 2
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 1079
        Height = 745
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
          
            '1.1.2. Open. Opens existing fomod .xml files. You should specify' +
            ' root folder that contains '#39'fomod'#39' folder. FOMOD Creation Tool s' +
            'ince 1.2 version support unicode text only in UTF-16 (UCS-2) Lit' +
            'tle Endian encoding. If '
          
            'fomod that you willing to open in other that this encoding you s' +
            'hould convert it manually. To do this open .xml'#39's file in Window' +
            ' Notepad, choose '#39'File->Save as'#39' menu, in save window choose enc' +
            'oding '#39'Unicode'#39', save file '
          
            'with same name, replace existing one. If you using Notepad++ ope' +
            'n .xml file, choose '#39'Encoding->Encode in UCS-2 Little Endian'#39', s' +
            'ave file.'
          
            '1.1.3. Save. Saves fomod .xml files. FOMOD Creation Tool since 1' +
            '.2 version support unicode text only in UTF-16 (UCS-2) Little En' +
            'dian encoding and will save files in this encoding.'
          '1.1.4. Exit. Exits from program.'
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
          '2.3. Finalization.'
          
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
    Left = 259
    Top = -10
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
      Left = 288
      Top = 45
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
      Left = 288
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
        Caption = 'Open'
        ShortCut = 16463
        OnClick = OpenMenuClick
      end
      object SaveMenu: TMenuItem
        Caption = 'Save'
        Enabled = False
        ShortCut = 16467
        OnClick = SaveMenuClick
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
