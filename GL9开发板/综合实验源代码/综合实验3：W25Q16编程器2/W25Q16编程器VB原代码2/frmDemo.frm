VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmDemo 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "给力者W25Q16编程器上位机软件V1.0"
   ClientHeight    =   8295
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   9210
   Icon            =   "frmDemo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8295
   ScaleWidth      =   9210
   StartUpPosition =   2  '屏幕中心
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   5085
      Top             =   5220
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   6030
      Top             =   4500
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame2 
      Caption         =   "操作："
      Height          =   5595
      Left            =   6750
      TabIndex        =   72
      Top             =   135
      Width           =   2310
      Begin VB.CommandButton Command4 
         BackColor       =   &H000000FF&
         Caption         =   "打开bin文件"
         Height          =   600
         Left            =   135
         MaskColor       =   &H000000FF&
         TabIndex        =   79
         Top             =   1260
         Width           =   2040
      End
      Begin VB.CommandButton Command13 
         Caption         =   "从31块区15扇区15页写"
         Height          =   600
         Left            =   135
         MaskColor       =   &H000000FF&
         Style           =   1  'Graphical
         TabIndex        =   78
         Top             =   4680
         Width           =   2040
      End
      Begin VB.CommandButton Command12 
         Caption         =   "31块区15扇区擦除"
         Height          =   600
         Left            =   135
         TabIndex        =   77
         Top             =   3825
         Width           =   2040
      End
      Begin VB.CommandButton Command11 
         Caption         =   "31块区擦除"
         Height          =   600
         Left            =   135
         TabIndex        =   76
         Top             =   2970
         Width           =   2040
      End
      Begin VB.CommandButton Command10 
         Caption         =   "整片擦除"
         Height          =   600
         Left            =   135
         TabIndex        =   75
         Top             =   2115
         Width           =   2040
      End
      Begin VB.Frame fraMenu 
         Caption         =   "串口选择："
         Height          =   735
         Left            =   135
         TabIndex        =   73
         Top             =   270
         Width           =   2040
         Begin VB.ComboBox Combo1 
            Height          =   300
            Left            =   495
            TabIndex        =   74
            Text            =   "Combo1"
            Top             =   270
            Width           =   1095
         End
      End
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page15】256"
      Height          =   240
      Index           =   15
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   69
      Top             =   450
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page14】256"
      Height          =   240
      Index           =   14
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   68
      Top             =   675
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page13】256"
      Height          =   240
      Index           =   13
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   67
      Top             =   900
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page12】256"
      Height          =   240
      Index           =   12
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   66
      Top             =   1125
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page11】256"
      Height          =   240
      Index           =   11
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   65
      Top             =   1350
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page10】256"
      Height          =   240
      Index           =   10
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   64
      Top             =   1575
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page09】256"
      Height          =   240
      Index           =   9
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   63
      Top             =   1800
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page08】256"
      Height          =   240
      Index           =   8
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   62
      Top             =   2025
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page07】256"
      Height          =   240
      Index           =   7
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   61
      Top             =   2250
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page06】256"
      Height          =   240
      Index           =   6
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   60
      Top             =   2475
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page05】256"
      Height          =   240
      Index           =   5
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   59
      Top             =   2700
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page04】256"
      Height          =   240
      Index           =   4
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   58
      Top             =   2925
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page03】256"
      Height          =   240
      Index           =   3
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   57
      Top             =   3150
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page02】256"
      Height          =   240
      Index           =   2
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   56
      Top             =   3375
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page01】256"
      Height          =   240
      Index           =   1
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   55
      Top             =   3600
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page00】256"
      Height          =   240
      Index           =   0
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   54
      Top             =   3825
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector15】4096"
      Height          =   240
      Index           =   15
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   52
      Top             =   450
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector14】4096"
      Height          =   240
      Index           =   14
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   51
      Top             =   675
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector13】4096"
      Height          =   240
      Index           =   13
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   50
      Top             =   900
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector12】4096"
      Height          =   240
      Index           =   12
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   49
      Top             =   1125
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector11】4096"
      Height          =   240
      Index           =   11
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   48
      Top             =   1350
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector10】4096"
      Height          =   240
      Index           =   10
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   47
      Top             =   1575
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector09】4096"
      Height          =   240
      Index           =   9
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   46
      Top             =   1800
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector08】4096"
      Height          =   240
      Index           =   8
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   45
      Top             =   2025
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector07】4096"
      Height          =   240
      Index           =   7
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   44
      Top             =   2250
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector06】4096"
      Height          =   240
      Index           =   6
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   43
      Top             =   2475
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector05】4096"
      Height          =   240
      Index           =   5
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   42
      Top             =   2700
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector04】4096"
      Height          =   240
      Index           =   4
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   41
      Top             =   2925
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector03】4096"
      Height          =   240
      Index           =   3
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   40
      Top             =   3150
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector02】4096"
      Height          =   240
      Index           =   2
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   39
      Top             =   3375
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector01】4096"
      Height          =   240
      Index           =   1
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   38
      Top             =   3600
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector00】4096"
      Height          =   240
      Index           =   0
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   37
      Top             =   3825
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block31】65536"
      Height          =   240
      Index           =   31
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   36
      Top             =   450
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block30】65536"
      Height          =   240
      Index           =   30
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   35
      Top             =   675
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block29】65536"
      Height          =   240
      Index           =   29
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   34
      Top             =   900
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block28】65536"
      Height          =   240
      Index           =   28
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   33
      Top             =   1125
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block27】65536"
      Height          =   240
      Index           =   27
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   32
      Top             =   1350
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block26】65536"
      Height          =   240
      Index           =   26
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   31
      Top             =   1575
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block25】65536"
      Height          =   240
      Index           =   25
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   30
      Top             =   1800
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block24】65536"
      Height          =   240
      Index           =   24
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   29
      Top             =   2025
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block23】65536"
      Height          =   240
      Index           =   23
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   2250
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block22】65536"
      Height          =   240
      Index           =   22
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   27
      Top             =   2475
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block21】65536"
      Height          =   240
      Index           =   21
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   26
      Top             =   2700
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block20】65536"
      Height          =   240
      Index           =   20
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   25
      Top             =   2925
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block19】65536"
      Height          =   240
      Index           =   19
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   24
      Top             =   3150
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block18】65536"
      Height          =   240
      Index           =   18
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   23
      Top             =   3375
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block17】65536"
      Height          =   240
      Index           =   17
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   22
      Top             =   3600
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block16】65536"
      Height          =   240
      Index           =   16
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   21
      Top             =   3825
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block15】65536"
      Height          =   240
      Index           =   15
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   20
      Top             =   4050
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block14】65536"
      Height          =   240
      Index           =   14
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   19
      Top             =   4275
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block13】65536"
      Height          =   240
      Index           =   13
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   4500
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block12】65536"
      Height          =   240
      Index           =   12
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   4725
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block11】65536"
      Height          =   240
      Index           =   11
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   4950
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block10】65536"
      Height          =   240
      Index           =   10
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   5175
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block09】65536"
      Height          =   240
      Index           =   9
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   5400
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block08】65536"
      Height          =   240
      Index           =   8
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   5625
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block07】65536"
      Height          =   240
      Index           =   7
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   5850
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block06】65536"
      Height          =   240
      Index           =   6
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   6075
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block05】65536"
      Height          =   240
      Index           =   5
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   6300
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block04】65536"
      Height          =   240
      Index           =   4
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   6525
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block03】65536"
      Height          =   240
      Index           =   3
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   6750
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block02】65536"
      Height          =   240
      Index           =   2
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   6975
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block01】65536"
      Height          =   240
      Index           =   1
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   7200
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block00】65536"
      Height          =   240
      Index           =   0
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   7425
      Width           =   1590
   End
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   210
      Left            =   45
      TabIndex        =   3
      Top             =   8055
      Visible         =   0   'False
      Width           =   6195
      _ExtentX        =   10927
      _ExtentY        =   370
      _Version        =   393216
      Appearance      =   0
      Max             =   255
      Scrolling       =   1
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   2025
      Top             =   2340
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   57600
   End
   Begin VB.Frame Frame1 
      Caption         =   "信息提示："
      Height          =   2010
      Left            =   2295
      TabIndex        =   0
      Top             =   5850
      Width           =   6750
      Begin VB.TextBox Text1 
         BackColor       =   &H00FFFFFF&
         Height          =   1650
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   1
         TabStop         =   0   'False
         ToolTipText     =   "信息提示栏"
         Top             =   225
         Width           =   6480
      End
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   2
      Top             =   7980
      Width           =   9210
      _ExtentX        =   16245
      _ExtentY        =   556
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   11060
            Text            =   "宁波芯动电子有限公司  www.MovingChip.com"
            TextSave        =   "宁波芯动电子有限公司  www.MovingChip.com"
            Object.ToolTipText     =   "创中国开发板第一品牌"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "2012-10-15"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "15:28"
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Command6"
      Height          =   420
      Left            =   5625
      TabIndex        =   71
      Top             =   1395
      Width           =   735
   End
   Begin VB.Label Label3 
      BackColor       =   &H00008000&
      Caption         =   "第15扇区中含16个页"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   4770
      TabIndex        =   70
      Top             =   225
      Width           =   1680
   End
   Begin VB.Label Label2 
      BackColor       =   &H000000FF&
      Caption         =   "第31块包中含16个扇区"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   2475
      TabIndex        =   53
      Top             =   225
      Width           =   1815
   End
   Begin VB.Label Label1 
      BackColor       =   &H00808000&
      Caption         =   "W25Q16包含32个块"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   405
      TabIndex        =   5
      Top             =   225
      Width           =   1455
   End
   Begin VB.Shape Shape2 
      BorderColor     =   &H00404040&
      BorderStyle     =   6  'Inside Solid
      FillColor       =   &H00808000&
      FillStyle       =   0  'Solid
      Height          =   7710
      Left            =   135
      Top             =   135
      Width           =   2040
   End
   Begin VB.Shape Shape3 
      FillColor       =   &H00008000&
      FillStyle       =   0  'Solid
      Height          =   4110
      Left            =   4545
      Top             =   135
      Width           =   2040
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   4110
      Left            =   2340
      Top             =   135
      Width           =   2040
   End
   Begin VB.Image Image2 
      Height          =   600
      Left            =   2970
      MouseIcon       =   "frmDemo.frx":0CCA
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":0E1C
      Top             =   4770
      Width           =   2910
   End
   Begin VB.Image Image1 
      Height          =   600
      Left            =   2970
      MouseIcon       =   "frmDemo.frx":699E
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":6AF0
      Top             =   4770
      Width           =   2910
   End
   Begin VB.Image Image4 
      Height          =   600
      Left            =   2970
      MouseIcon       =   "frmDemo.frx":C672
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":C7C4
      Top             =   4770
      Width           =   2910
   End
   Begin VB.Image Image3 
      Height          =   600
      Left            =   2970
      MouseIcon       =   "frmDemo.frx":12346
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":12498
      Top             =   4770
      Width           =   2910
   End
End
Attribute VB_Name = "frmDemo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long

Dim com_buf() As Byte
Dim E As Integer
Dim Textbuf As String
Dim lstr1, lstr2, lstr3, lstr4, lstr5, lstr6 As String
Dim HEAD_DATA(20) As Byte
Dim OldPort As String
Dim Port As Integer
Dim OldBlock As Integer
Dim OldSector As Integer
Dim OldPage As Integer
Dim P As Integer
Dim LinStr
Dim L As Long
Dim FileBuf() As Byte
Dim FileStrBuf(2097152) As Byte

Private Sub Gotoweb()
Const URL = "http://www.movingchip.com"
Const SW_SHOWNORMAL = 1
Dim Success As Long
Success = ShellExecute(Me.hwnd, "open", URL, vbNullString, vbNullString, SW_SHOWNORMAL)
End Sub

Private Sub Combo1_Click()
    If OldPort <> Combo1.Text Then
        If MSComm1.PortOpen = True Then MSComm1.PortOpen = False
        OldPort = Combo1.Text
        If OldPort = "COM1" Then
            Port = 1
        ElseIf OldPort = "COM2" Then
            Port = 2
        ElseIf OldPort = "COM3" Then
            Port = 3
        ElseIf OldPort = "COM4" Then
            Port = 4
        ElseIf OldPort = "COM5" Then
            Port = 5
        ElseIf OldPort = "COM6" Then
            Port = 6
        ElseIf OldPort = "COM7" Then
            Port = 7
        ElseIf OldPort = "COM8" Then
            Port = 8
        ElseIf OldPort = "COM9" Then
            Port = 9
        ElseIf OldPort = "COM10" Then
            Port = 10
        ElseIf OldPort = "COM11" Then
            Port = 11
        ElseIf OldPort = "COM12" Then
            Port = 12
        ElseIf OldPort = "COM13" Then
            Port = 13
        ElseIf OldPort = "COM14" Then
            Port = 14
        ElseIf OldPort = "COM15" Then
            Port = 15
        Else
            Port = 16
        End If
        MSComm1.CommPort = Port
        Call firstlink
    End If
End Sub
Private Sub Command1_Click(Index As Integer)
    Dim N As Integer
    For N = 0 To 31 Step 1
        Command1(N).BackColor = &H8000000F
    Next N
    Command1(Index).BackColor = &HFF&
    If OldBlock <> Index Then
        OldBlock = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区第" & OldSector & "扇区第" & OldPage & "页"
        Call writetext1
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        'fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
        Command11.Caption = OldBlock & "块区擦除"
        Command12.Caption = OldBlock & "块区" & OldSector & "扇区擦除"
        Command13.Caption = "从" & OldBlock & "块区" & OldSector & "扇区" & OldPage & "页写"
    End If
    Command6.SetFocus
End Sub
Private Sub Command2_Click(Index As Integer)
    Dim N As Integer
    For N = 0 To 15 Step 1
        Command2(N).BackColor = &H8000000F
    Next N
    Command2(Index).BackColor = &H8000&
    If OldSector <> Index Then
        OldSector = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区第" & OldSector & "扇区第" & OldPage & "页"
        Call writetext1
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        'fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)："
        Command11.Caption = OldBlock & "块区擦除"
        Command12.Caption = OldBlock & "块区" & OldSector & "扇区擦除"
        Command13.Caption = "从" & OldBlock & "块区" & OldSector & "扇区" & OldPage & "页写"
    End If
    Command6.SetFocus
End Sub
Private Sub Command3_click(Index As Integer)
    Dim N As Integer
    For N = 0 To 15 Step 1
        Command3(N).BackColor = &H8000000F
    Next N
    Command3(Index).BackColor = &HFFFFC0
    If OldPage <> Index Then
        OldPage = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区第" & OldSector & "扇区第" & OldPage & "页"
        Call writetext1
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        'fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
        Command11.Caption = OldBlock & "块区擦除"
        Command12.Caption = OldBlock & "块区" & OldSector & "扇区擦除"
        Command13.Caption = "从" & OldBlock & "块区" & OldSector & "扇区" & OldPage & "页写"
    End If
    Command6.SetFocus
End Sub
Private Sub Command10_Click() '整片擦除
    Dim i As Long
    HEAD_DATA(0) = &H4
    HEAD_DATA(18) = "&H" & Hex(OldBlock)
    HEAD_DATA(19) = "&H" & Hex(OldSector * 16 + OldPage)
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "4" Then
                Exit For
            Else
                Textbuf = "开发板未准备好"
                Call writetext1
                Exit Sub
            End If
        End If
        If i > 799900 Then
            Textbuf = "通讯超时"
            Call writetext1
            Exit Sub
        End If
    Next i
    Textbuf = "整片成功擦除"
    Call writetext1
    Command6.SetFocus
End Sub

Private Sub Command11_Click() '块区擦除
    Dim i As Long
    HEAD_DATA(0) = &H5
    HEAD_DATA(18) = "&H" & Hex(OldBlock)
    HEAD_DATA(19) = "&H" & Hex(OldSector * 16 + OldPage)
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "5" Then
                Exit For
            Else
                Textbuf = "开发板未准备好"
                Call writetext1
                Exit Sub
            End If
        End If
        If i > 799900 Then
            Textbuf = "通讯超时"
            Call writetext1
            Exit Sub
        End If
    Next i
    Textbuf = "第" & OldBlock & "块区成功擦除"
    Call writetext1
    Command6.SetFocus
End Sub

Private Sub Command12_Click() '扇区擦除
    Dim i As Long
    HEAD_DATA(0) = &H6
    HEAD_DATA(2) = "&H" & Hex(OldBlock)
    HEAD_DATA(3) = "&H" & Hex(OldSector * 16 + OldPage)
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "6" Then
                Exit For
            Else
                Textbuf = "开发板未准备好"
                Call writetext1
                Exit Sub
            End If
        End If
        If i > 799900 Then
            Textbuf = "通讯超时"
            Call writetext1
            Exit Sub
        End If
    Next i
    Textbuf = "第" & OldBlock & "块区中第" & OldSector & "扇区成功擦除"
    Call writetext1
    Command6.SetFocus
End Sub
Private Sub Command13_Click()
    Call writedata
    Command6.SetFocus
End Sub
Private Sub Form_Load()
    Port = 4
    MSComm1.CommPort = Port
    ProgressBar1.Visible = False
    Combo1.Text = "COM4"
    OldPort = "COM4"
    Combo1.AddItem "COM1"
    Combo1.AddItem "COM2"
    Combo1.AddItem "COM3"
    Combo1.AddItem "COM4"
    Combo1.AddItem "COM5"
    Combo1.AddItem "COM6"
    Combo1.AddItem "COM7"
    Combo1.AddItem "COM8"
    Combo1.AddItem "COM9"
    Combo1.AddItem "COM10"
    Combo1.AddItem "COM11"
    Combo1.AddItem "COM12"
    Combo1.AddItem "COM13"
    Combo1.AddItem "COM14"
    Combo1.AddItem "COM15"
    Combo1.AddItem "COM16"
    Command1(0).BackColor = &HFF&
    Command2(0).BackColor = &H8000&
    Command3(Index).BackColor = &HFFFFC0
    OldBlock = 0
    OldSector = 0
    OldPage = 0

    Textbuf = "欢迎使用--[GL9型51单片机开发学习系统]"
    Call writetext1
    Textbuf = "给力者单片机开发学习系统，开发、学习都给力！"
    Call writetext1
    Call firstlink
    Textbuf = "缓冲区为:第" & OldBlock & "块第" & OldSector & "扇区第" & OldPage & "页"
    Call writetext1
    Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
    Label3.Caption = "第" & OldSector & "扇区包含16个页"
    'fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
    Command11.Caption = OldBlock & "块区擦除"
    Command12.Caption = OldBlock & "块区" & OldSector & "扇区擦除"
    Command13.Caption = "从" & OldBlock & "块区" & OldSector & "扇区" & OldPage & "页写"
    Command13.Enabled = False
    
End Sub
Private Sub firstlink()
    Dim i As Long
    Dim Response
    HEAD_DATA(0) = &H1
    On Error GoTo merror1
    MSComm1.Settings = "57600,N,8,1"  '设定波特率和置校验和位为空57600
    MSComm1.OutBufferCount = 0
    If MSComm1.PortOpen = False Then MSComm1.PortOpen = True
    MSComm1.Output = HEAD_DATA
    MSComm1.InputLen = 0
    MSComm1.InputMode = comInputModeBinary
    For i = 0 To 90000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "1" And Hex(com_buf(2)) = "6" And Hex(com_buf(3)) = "2" And Hex(com_buf(4)) = "4" Then
                Textbuf = "检测到--[GL9型51单片机开发学习系统]"
                Call writetext1
                Exit Sub
            End If
        End If
    Next i
    Textbuf = "未检测到--[GL9型51单片机开发学习系统]"
    Call writetext1
    Exit Sub
merror1:
    Response = MsgBox("端口无效或不可用！请更改端口。", 16, "给力者提示")
    Textbuf = "未检测到--[GL9型51单片机开发学习系统]"
    Call writetext1
End Sub

Private Sub writedata()
    Dim Str As String
    Dim i As Long
    Dim x, y As Integer
    Dim Temp8 As String
    Dim L2 As Long
    HEAD_DATA(0) = &H2
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "2" Then
                Exit For
            Else
                Textbuf = "开发板未准备好"
                Call writetext1
                Exit Sub
            End If
        End If
        If i > 799900 Then
            Textbuf = "通讯超时"
            Call writetext1
            Exit Sub
        End If
    Next i
 '===============================================
    
    ProgressBar1.Min = 0
    ProgressBar1.Max = L \ 16
    ProgressBar1.Visible = True
    For x = 0 To (L \ 16) - 1 Step 1 '发送L/16次
        ProgressBar1.Value = x
        For y = 0 To 15 Step 1
            HEAD_DATA(y + 2) = "&H" & Hex(FileStrBuf(x * 16 + y))
        Next y
        L2 = OldBlock * 65536 + (lodsector * 16 + OldPage) * 256 + x * 16
        L2 = Trim(L2)
        Temp8 = Hex(L2)
        If Len(Temp8) = 1 Then Temp8 = "00000" + Temp8
        If Len(Temp8) = 2 Then Temp8 = "0000" + Temp8
        If Len(Temp8) = 3 Then Temp8 = "000" + Temp8
        If Len(Temp8) = 4 Then Temp8 = "00" + Temp8
        If Len(Temp8) = 5 Then Temp8 = "0" + Temp8
        HEAD_DATA(1) = &H1
        HEAD_DATA(18) = "&H" & Mid(Temp8, 1, 2)
        HEAD_DATA(19) = "&H" & Mid(Temp8, 3, 2)
        HEAD_DATA(20) = "&H" & Mid(Temp8, 5, 2)
        MSComm1.InputLen = 0
        MSComm1.Output = HEAD_DATA
        For i = 0 To 800000 Step 1
            If MSComm1.InBufferCount > 20 Then
                com_buf = MSComm1.Input
                Exit For
            End If
            If i > 799000 Then
                Textbuf = "通讯超时"
                Call writetext1
                ProgressBar1.Visible = False
                Exit Sub
            End If
        Next i
    Next x
    If L Mod 16 > 0 Then
        For y = 0 To 15 Step 1
            HEAD_DATA(y + 2) = "&H" & Hex(FileStrBuf((L \ 16) * 16 + y))
        Next y
        L2 = OldBlock * 65536 + (lodsector * 16 + OldPage) * 256 + (L \ 16) * 16
        L2 = Trim(L2)
        Temp8 = Hex(L2)
        If Len(Temp8) = 1 Then Temp8 = "00000" + Temp8
        If Len(Temp8) = 2 Then Temp8 = "0000" + Temp8
        If Len(Temp8) = 3 Then Temp8 = "000" + Temp8
        If Len(Temp8) = 4 Then Temp8 = "00" + Temp8
        If Len(Temp8) = 5 Then Temp8 = "0" + Temp8
        HEAD_DATA(1) = &H1
        HEAD_DATA(18) = "&H" & Mid(Temp8, 1, 2)
        HEAD_DATA(19) = "&H" & Mid(Temp8, 3, 2)
        HEAD_DATA(20) = "&H" & Mid(Temp8, 5, 2)
        MSComm1.InputLen = 0
        MSComm1.Output = HEAD_DATA
        For i = 0 To 800000 Step 1
            If MSComm1.InBufferCount > 20 Then
                com_buf = MSComm1.Input
                Exit For
            End If
            If i > 799000 Then
                Textbuf = "通讯超时"
                Call writetext1
                ProgressBar1.Visible = False
                Exit Sub
            End If
        Next i
    End If
    HEAD_DATA(1) = &H0
    MSComm1.Output = HEAD_DATA
    Textbuf = "写W25Q16数据成功"
    Call writetext1
    ProgressBar1.Visible = False
End Sub
Public Function ByteLoad(ByVal N As String) As Byte() '读取文件二进制数据
On Error GoTo Over
Dim Dat() As Byte, FileSize As Long '二进制数组,文件长度
FileSize = FileLen(N) '获取文件长度
ReDim Dat(FileSize - 1) As Byte '定义二进制数组长度
Open N For Binary As #65 '打开读取
    Get #65, , Dat
Close
ByteLoad = Dat '赋值
Over:
End Function
Private Sub Command4_Click()
    Dim i As Long
    Dim intHighHex As Byte
    Dim intLowHex As Byte
    Dim LinStr1 As String
    frmDemo.CommonDialog1.ShowOpen
    If frmDemo.CommonDialog1.FileName = "" Or frmDemo.CommonDialog1.FileName = "*.bin" Then Exit Sub
    On Err GoTo error
    LinStr1 = frmDemo.CommonDialog1.FileName
    FileBuf() = ByteLoad(LinStr1)
    'L = 256
    L = FileLen(frmDemo.CommonDialog1.FileName)
    For i = 0 To L - 1 Step 1
        intHighHex = FileBuf(i) \ 16
        intLowHex = FileBuf(i) Mod 16
        If intHighHex < 10 Then
            intHighHex = intHighHex + 48
        Else
            intHighHex = intHighHex + 55
        End If
        If intLowHex < 10 Then
            intLowHex = intLowHex + 48
        Else
            intLowHex = intLowHex + 55
        End If
        FileStrBuf(i) = "&H" & Chr$(intHighHex) + Chr$(intLowHex)
    Next i
    frmDemo.CommonDialog1.FileName = "*.bin"
    Textbuf = "打开BIN文件成功,位置:" & LinStr1
    Call writetext1
    Textbuf = "文件大小:" & L & "字节"
    Call writetext1
    Command13.Enabled = True
    Exit Sub
error:
    Close #1
    frmDemo.CommonDialog1.FileName = "*.bin"
    Textbuf = "打开BIN文件失败"
    Call writetext1
End Sub
Private Sub writetext1()
    E = E + 1
    If E = 1 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr1 = Textbuf + Chr(13) + Chr(10)
    ElseIf E = 2 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr2 = Textbuf + Chr(13) + Chr(10)
    ElseIf E = 3 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr3 = Textbuf + Chr(13) + Chr(10)
    ElseIf E = 4 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr4 = Textbuf + Chr(13) + Chr(10)
    ElseIf E = 5 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr5 = Textbuf + Chr(13) + Chr(10)
    ElseIf E = 6 Then
        Text1.Text = Text1.Text + Textbuf + Chr(13) + Chr(10)
        lstr6 = Textbuf + Chr(13) + Chr(10)
    Else
        lstr1 = lstr2
        lstr2 = lstr3
        lstr3 = lstr4
        lstr4 = lstr5
        lstr5 = lstr6
        lstr6 = Textbuf + Chr(13) + Chr(10)
        Text1.Text = lstr1 + lstr2 + lstr3 + lstr4 + lstr5 + lstr6
    End If
End Sub
Private Sub Image1_Click()
    Call Gotoweb
End Sub
Private Sub Image2_Click()
    Call Gotoweb
End Sub
Private Sub Image3_Click()
    Call Gotoweb
End Sub
Private Sub Image4_Click()
    Call Gotoweb
End Sub
Private Sub Timer1_Timer()
    If P = 0 Then
        P = 1
        Image1.Visible = True
        Image2.Visible = False
        Image3.Visible = False
        Image4.Visible = False
    ElseIf P = 1 Then
        P = 2
        Image1.Visible = False
        Image2.Visible = True
        Image3.Visible = False
        Image4.Visible = False
    ElseIf P = 2 Then
        P = 3
        Image1.Visible = False
        Image2.Visible = False
        Image3.Visible = True
        Image4.Visible = False
    Else
        P = 0
        Image1.Visible = False
        Image2.Visible = False
        Image3.Visible = False
        Image4.Visible = True
    End If
End Sub
