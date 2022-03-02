object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'FOMOD Creation Tool'
  ClientHeight = 756
  ClientWidth = 1087
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 1087
    Height = 756
    ActivePage = ModInfoTabSheet
    Align = alClient
    TabOrder = 0
    object ModInfoTabSheet: TTabSheet
      Caption = 'Mod info'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 1079
        Height = 201
        Align = alTop
        Caption = 'Mod infornation'
        TabOrder = 0
        object ModNameEdit: TLabeledEdit
          Left = 112
          Top = 29
          Width = 305
          Height = 21
          AutoSize = False
          EditLabel.Width = 49
          EditLabel.Height = 13
          EditLabel.Caption = 'Mod name'
          LabelPosition = lpLeft
          LabelSpacing = 49
          TabOrder = 0
          OnChange = ModNameEditChange
        end
        object ModAuthorEdit: TLabeledEdit
          Left = 112
          Top = 56
          Width = 305
          Height = 21
          AutoSize = False
          EditLabel.Width = 55
          EditLabel.Height = 13
          EditLabel.Caption = 'Mod author'
          LabelPosition = lpLeft
          LabelSpacing = 43
          TabOrder = 1
          OnChange = ModAuthorEditChange
        end
        object ModVersionEdit: TLabeledEdit
          Left = 112
          Top = 83
          Width = 137
          Height = 21
          AutoSize = False
          EditLabel.Width = 58
          EditLabel.Height = 13
          EditLabel.Caption = 'Mod version'
          LabelPosition = lpLeft
          LabelSpacing = 40
          TabOrder = 2
          OnChange = ModVersionEditChange
        end
        object ModURLEdit: TLabeledEdit
          Left = 112
          Top = 110
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
        object ModDescEdit: TLabeledEdit
          Left = 112
          Top = 137
          Width = 305
          Height = 21
          AutoSize = False
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'Mod description'
          LabelPosition = lpLeft
          LabelSpacing = 23
          TabOrder = 4
          OnChange = ModDescEditChange
        end
        object ModCategoryEdit: TLabeledEdit
          Left = 112
          Top = 164
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
          TabOrder = 5
          OnChange = ModCategoryEditChange
        end
      end
      object WorkSpaceGroupBox: TGroupBox
        Left = 0
        Top = 201
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
        Top = 680
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
        Top = 687
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
        Height = 660
        ActivePage = GroupsFileTabSheet
        Align = alClient
        TabOrder = 1
        object GroupsFileTabSheet: TTabSheet
          Caption = 'Groups and Files'
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 1071
            Height = 632
            Align = alClient
            TabOrder = 0
            object FilesGroupBox: TGroupBox
              Left = 0
              Top = 477
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
                Columns = <
                  item
                    Caption = 'Destination path'
                    Width = 425
                  end>
                ColumnClick = False
                GridLines = True
                RowSelect = True
                TabOrder = 4
                ViewStyle = vsReport
                OnClick = DstFilesListViewClick
                OnEdited = DstFilesListViewEdited
              end
            end
            object GroupsGroupBox: TGroupBox
              Left = 0
              Top = 49
              Width = 1067
              Height = 428
              Align = alTop
              Caption = 'Groups'
              TabOrder = 1
              object Label4: TLabel
                Left = 223
                Top = 16
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
              object PluginImage: TImage
                Left = 616
                Top = 289
                Width = 196
                Height = 133
                Stretch = True
              end
              object PluginListBox: TListBox
                Left = 411
                Top = 45
                Width = 199
                Height = 113
                ItemHeight = 13
                TabOrder = 0
                OnClick = PluginListBoxClick
              end
              object GroupNameEdit: TLabeledEdit
                Left = 80
                Top = 13
                Width = 137
                Height = 21
                AutoSize = False
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.Caption = 'Group name'
                LabelPosition = lpLeft
                TabOrder = 1
              end
              object GroupTypeComboBox: TComboBox
                Left = 251
                Top = 13
                Width = 112
                Height = 21
                Style = csDropDownList
                ItemHeight = 13
                ItemIndex = 0
                TabOrder = 2
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
                Top = 40
                Width = 75
                Height = 25
                Caption = 'Add'
                TabOrder = 3
                OnClick = AddGroupButtonClick
              end
              object RemoveGroupButton: TButton
                Left = 223
                Top = 71
                Width = 75
                Height = 25
                Caption = 'Remove'
                Enabled = False
                TabOrder = 4
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
                TabOrder = 5
              end
              object RemovePluginButton: TButton
                Left = 616
                Top = 52
                Width = 75
                Height = 25
                Caption = 'Remove'
                Enabled = False
                TabOrder = 6
                OnClick = RemovePluginButtonClick
              end
              object AddPluginButton: TButton
                Left = 616
                Top = 21
                Width = 75
                Height = 25
                Caption = 'Add'
                Enabled = False
                TabOrder = 7
                OnClick = AddPluginButtonClick
              end
              object PluginDescriptionMemo: TMemo
                Left = 18
                Top = 188
                Width = 592
                Height = 94
                Enabled = False
                TabOrder = 8
                OnChange = PluginDescriptionMemoChange
              end
              object VaribleSetGroupBox: TGroupBox
                Left = 711
                Top = 16
                Width = 345
                Height = 266
                Caption = 'Variable set'
                TabOrder = 9
                object Label6: TLabel
                  Left = 16
                  Top = 29
                  Width = 121
                  Height = 13
                  Alignment = taCenter
                  AutoSize = False
                  Caption = 'variable'
                end
                object Label7: TLabel
                  Left = 159
                  Top = 48
                  Width = 34
                  Height = 13
                  AutoSize = False
                  Caption = 'set'
                end
                object VaribleComboBox: TComboBox
                  Left = 15
                  Top = 48
                  Width = 130
                  Height = 21
                  ItemHeight = 13
                  TabOrder = 0
                end
                object VaribleValueComboBox: TComboBox
                  Left = 199
                  Top = 48
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
                object VaribleSetListView: TListView
                  Left = 15
                  Top = 75
                  Width = 237
                  Height = 182
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
                  TabOrder = 2
                  ViewStyle = vsReport
                  OnClick = VaribleSetListViewClick
                end
                object AddVaribleButton: TButton
                  Left = 258
                  Top = 44
                  Width = 75
                  Height = 25
                  Caption = 'Add'
                  Enabled = False
                  TabOrder = 3
                  OnClick = AddVaribleButtonClick
                end
                object DeleteVaribleButton: TButton
                  Left = 258
                  Top = 75
                  Width = 75
                  Height = 25
                  Caption = 'Delete'
                  Enabled = False
                  TabOrder = 4
                  OnClick = DeleteVaribleButtonClick
                end
              end
              object ChoosePluginImageButton: TButton
                Left = 454
                Top = 288
                Width = 75
                Height = 25
                Caption = 'Choose'
                Enabled = False
                TabOrder = 10
                OnClick = ChoosePluginImageButtonClick
              end
              object ClearPluginImageButton: TButton
                Left = 535
                Top = 288
                Width = 75
                Height = 25
                Caption = 'Clear'
                Enabled = False
                TabOrder = 11
                OnClick = ClearPluginImageButtonClick
              end
              object PluginImageEdit: TLabeledEdit
                Left = 80
                Top = 290
                Width = 355
                Height = 21
                AutoSize = False
                EditLabel.Width = 59
                EditLabel.Height = 13
                EditLabel.Caption = 'Plugin image'
                Enabled = False
                LabelPosition = lpLeft
                ReadOnly = True
                TabOrder = 12
              end
              object GroupListView: TListView
                Left = 18
                Top = 40
                Width = 199
                Height = 118
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
                ReadOnly = True
                RowSelect = True
                TabOrder = 13
                ViewStyle = vsReport
                OnClick = GroupListViewClick
              end
              object GroupUpButton: TButton
                Left = 223
                Top = 102
                Width = 75
                Height = 25
                Caption = 'Move up'
                Enabled = False
                TabOrder = 14
                OnClick = GroupUpButtonClick
              end
              object GroupDownButton: TButton
                Left = 223
                Top = 133
                Width = 75
                Height = 25
                Caption = 'Move down'
                Enabled = False
                TabOrder = 15
                OnClick = GroupDownButtonClick
              end
              object PluginUpButton: TButton
                Left = 616
                Top = 102
                Width = 75
                Height = 25
                Caption = 'Move up'
                Enabled = False
                TabOrder = 16
                OnClick = PluginUpButtonClick
              end
              object PluginDownButton: TButton
                Left = 616
                Top = 133
                Width = 75
                Height = 25
                Caption = 'Move down'
                Enabled = False
                TabOrder = 17
                OnClick = PluginDownButtonClick
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
            Height = 632
            Align = alClient
            TabOrder = 0
            object GroupBox4: TGroupBox
              Left = 0
              Top = 0
              Width = 1067
              Height = 628
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
        Height = 728
        Align = alClient
        Lines.Strings = (
          'FOMOD Creation Tool'
          'Quick guide'
          'Preparation.'
          
            'First of first you should prepare folder where will be your mod ' +
            'files and '#39'fomod'#39' folder. it'#39's up to you how you organize struct' +
            'ure of you'#1082' mod, but keep in mind that some people may want to d' +
            'o manual installation so '
          'making this structure reasonable is good idea.'
          'Programm start'
          '1. Mod info.'
          
            'At start of programm you'#39'll see '#39'Mod info'#39' tab where you put inf' +
            'ormation about your mod.'
          '1.1. Mod information.'
          'Mod name - name of your mod.'
          'Mod author - it'#39's you, comrade.'
          'Mod version - i think it'#39's understandable.'
          
            'Mod page on Nexus - URL to your mod'#39's page on www.nexusmods.com.' +
            ' To get it create file in your account on Nexus, but not upload ' +
            'anything and not publish it, you'#39'll be able to copy URL of your ' +
            'future mod now.'
          
            'Mod description - text that will be shown in right part of NMM w' +
            'hen your mod selected.'
          'Mod category - category on Nexus your mod belong.'
          
            'Technically this fields not necessary but you want your mod look' +
            ' gleam and neat, aren'#39't you?'
          '1.2. Workspace.'
          
            'There you set root folder, which you prepare and where will be y' +
            'our mod files and '#39'fomod'#39' folder, if there no '#39'fomod'#39' folder pro' +
            'gramm will offer you to create one. After workspace is setted co' +
            'rrectly '#39'Proceed'#39' button is '
          
            'enabled. Once '#39'Proceed'#39' button hited you'#39'll see '#39'Steps'#39' tab and ' +
            'not be able to change root directory.'
          '2. Steps.'
          'Basic tab where you create your FOMOD installation.'
          '2.1. Groups and Files'
          
            '2.1.1. Step name. Sets name of step in installation, will not be' +
            ' displayed anywhere, it'#39's for your convenience but it can'#39't be e' +
            'mpty.'
          
            '2.1.2. Groups. Add at least one group to each step. Group name w' +
            'ill be displayed at left part of instalation window. Choose type' +
            ' for your groups. There is four types:'
          
            '- SelectExatlyOne - you can select only one option in group, can' +
            #39't select none or several.'
          
            '- SelectAny - you can select none, several or all options in gro' +
            'up;'
          
            '- SelectAtMostOne - you can select none or only one option in gr' +
            'oups.'
          
            '- SelectAtLeastOne - you can select one, several ar all options ' +
            'in group, can'#39't select none.'
          
            '2.1.3. Plugins. Plugins is a options under groups wich you choos' +
            'e upon instalation. At least one plugin must be in each group. G' +
            'roup must be selected in group list in order to add plugin in it' +
            '.'
          
            '2.1.4. Plugin description. Text that will be shown in right top ' +
            'part of instalation window when plugin is selected by user. Do N' +
            'OT use multiline descriptions, any text on rather then first lin' +
            'e will not be saved. New line '
          
            'means you hit enter key. Text that just wraped to next visible l' +
            'ine but not devided by enter key still considered as one line. P' +
            'lugin must be selected in order to add description.'
          
            '2.1.5. Plugin image. Image that will be shown at right bottom pa' +
            'rt of instalation window when plugin is selected by user. Use en' +
            'glish letters in image name. It will be wise to put you images i' +
            'n '#39'fomod'#39' folder, but nit '
          
            'necessary. Plugin must be selected in order to add description. ' +
            'Image must belong to root directory.'
          
            '2.1.6. Variable set. If you making FOMOD instalation with condot' +
            'ions you should operate with some variables. Every plugin may se' +
            't several variables to '#39'On'#39' or '#39'Off'#39' state. If you don'#39't need co' +
            'nditions leave it blanck. '
          'Plugin must be selected in order to add varible.'
          
            '2.1.7. Files. Each plugin may instal some files. You may add fil' +
            'es one by one to plugin or add entire folder. Plugin must be sel' +
            'ected in order to add files and/or folders. Note: path for files' +
            ' and folders is relative, but '
          
            'source path relate from root directory, place where '#39'fomod'#39' fold' +
            'er is, and destination path relates from '#39'DATA'#39' folder in game d' +
            'irectory. '
          'Example:'
          'Consider you have this file structure in mod'
          '    root/data/my_mod.esp'
          '    root/fomod/info.xml'
          '    root/fomod/ModuleConfig.xml'
          '    root/fomod/images/my_mod_image.jpg'
          'You '#39'my_mod.esp'#39' to files and it shows like thet:'
          'file   |    data/my_mod.esp   |    data/my_mod.esp'
          
            'NMM will understand that your '#39'data'#39' and game '#39'data'#39' same folder' +
            ' do things right. It'#39's also will work fine if you have this stru' +
            'ctue'
          '    root/my_mod.esp'
          '    root/fomod/info.xml'
          '    root/fomod/ModuleConfig.xml'
          '    root/fomod/images/my_mod_image.jpg'
          'But if have this structure'
          '    root/my_files/my_mod.esp'
          '    root/fomod/info.xml'
          '    root/fomod/ModuleConfig.xml'
          '    root/fomod/images/my_mod_image.jpg'
          
            'then NMM will create '#39'my_files'#39' in dame '#39'data'#39' folder and put yo' +
            'ur .esp there. Same work for folders. You may easily change dest' +
            'ination path by selecting file in list end then press left mouse' +
            ' button again on it, just like '
          'you rename files in Windows. '
          '2.2. Conditions. '
          
            'If you making FOMOD instalation with multiple steps and conditio' +
            'ns you must set this conditions. '
          
            '2.2.1. Condition set. When you setted variables for your plugins' +
            ' (group options) this variables will be available in dropdown li' +
            'st. Choose one or several and choose corresponding comparison va' +
            'lue. If variable is equal to '
          
            'comparison value this step will be shown in instalation. If not ' +
            'then step will be skiped and hiden from user. If several conditi' +
            'on setted then all of them should be fulfilled at the same time.'
          '3. Finalization.'
          
            'Choose FOMOD->Save menu when you set everithing you wnated. '#39'inf' +
            'o.xml'#39' and '#39'ModuleConfig.xml'#39' files will be created in '#39'fomod'#39' d' +
            'irectory. Now you can pack you mod in archive and test it before' +
            ' uploading anywhere.')
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
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
  object MainMenu1: TMainMenu
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
end
