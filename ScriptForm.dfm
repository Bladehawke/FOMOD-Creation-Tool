object ScriptForm1: TScriptForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'ScriptForm1'
  ClientHeight = 333
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 175
    Width = 591
    Height = 146
    AutoSize = False
    WordWrap = True
  end
  object ScriptMemo: TMemo
    Left = 8
    Top = 8
    Width = 591
    Height = 161
    TabOrder = 0
  end
  object SaveButton: TButton
    Left = 605
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    ModalResult = 1
    TabOrder = 1
  end
  object CancelButton: TButton
    Left = 605
    Top = 39
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
