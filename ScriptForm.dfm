object ScriptForm1: TScriptForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'ScriptForm1'
  ClientHeight = 391
  ClientWidth = 706
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
  object macroLabel0: TLabel
    Left = 8
    Top = 175
    Width = 591
    Height = 66
    AutoSize = False
    Caption = 
      'Type there windows console commands (cmd). Those will be execute' +
      'd befor/after project save. You can use macro defined in FOMOD C' +
      'reation Tool like:'
    WordWrap = True
  end
  object macroLabel1: TLabel
    Left = 8
    Top = 231
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$MODNAME$ - will be replaced with your mod name'
    WordWrap = True
  end
  object macroLabel2: TLabel
    Left = 8
    Top = 247
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$MODAUTHOR$ - will be replaced with mod author name'
    WordWrap = True
  end
  object macroLabel3: TLabel
    Left = 8
    Top = 263
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$MODVERSION$ - will be replaced with your mod version'
    WordWrap = True
  end
  object macroLabel4: TLabel
    Left = 8
    Top = 279
    Width = 591
    Height = 18
    AutoSize = False
    Caption = 
      '$MODROOT$ - will be replaced with mod root directory you specifi' +
      'ed'
    WordWrap = True
  end
  object macroLabel5: TLabel
    Left = 8
    Top = 295
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$DATE$ - will be replaced with current date'
    WordWrap = True
  end
  object macroLabel6: TLabel
    Left = 8
    Top = 311
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$TIME$ - will be replaced with current time'
    WordWrap = True
  end
  object macroLabel7: TLabel
    Left = 8
    Top = 327
    Width = 591
    Height = 18
    AutoSize = False
    Caption = '$RANDOM$ - will be replaced with random number from 0 to 32767'
    WordWrap = True
  end
  object macroLabel8: TLabel
    Left = 8
    Top = 351
    Width = 591
    Height = 42
    AutoSize = False
    Caption = 
      'Don'#39't forget about quotes as you likely will need them so cmd wi' +
      'll understand commands in right way.'
    WordWrap = True
  end
  object ScriptMemo: TMemo
    Left = 8
    Top = 8
    Width = 591
    Height = 161
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object SaveButton: TButton
    Left = 605
    Top = 8
    Width = 92
    Height = 25
    Caption = 'Save'
    ModalResult = 1
    TabOrder = 1
  end
  object CancelButton: TButton
    Left = 605
    Top = 39
    Width = 92
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
