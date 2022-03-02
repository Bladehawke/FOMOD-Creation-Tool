object SplashForm: TSplashForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'SplashForm'
  ClientHeight = 166
  ClientWidth = 168
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LogoImage: TImage
    Left = 0
    Top = 0
    Width = 105
    Height = 105
    AutoSize = True
  end
  object Label1: TLabel
    Left = 0
    Top = 153
    Width = 168
    Height = 13
    Align = alBottom
    Alignment = taCenter
    Caption = 'Initializing...'
    ExplicitWidth = 59
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 128
    Top = 16
  end
end
