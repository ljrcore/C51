VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmDemo 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "给力者W25Q16编程器上位机软件V1.0"
   ClientHeight    =   9345
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   10620
   Icon            =   "frmDemo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   9345
   ScaleWidth      =   10620
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton Command12 
      Caption         =   "第31块区中第15扇区擦除"
      Height          =   285
      Left            =   6795
      TabIndex        =   80
      Top             =   5490
      Width           =   3660
   End
   Begin VB.CommandButton Command11 
      Caption         =   "第31块区擦除"
      Height          =   285
      Left            =   6795
      TabIndex        =   79
      Top             =   5130
      Width           =   3660
   End
   Begin VB.CommandButton Command10 
      Caption         =   "整片擦除"
      Height          =   285
      Left            =   6795
      TabIndex        =   78
      Top             =   4770
      Width           =   3660
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page15】256"
      Height          =   240
      Index           =   15
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   75
      Top             =   5085
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page14】256"
      Height          =   240
      Index           =   14
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   74
      Top             =   5310
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page13】256"
      Height          =   240
      Index           =   13
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   73
      Top             =   5535
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page12】256"
      Height          =   240
      Index           =   12
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   72
      Top             =   5760
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page11】256"
      Height          =   240
      Index           =   11
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   71
      Top             =   5985
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page10】256"
      Height          =   240
      Index           =   10
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   70
      Top             =   6210
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page09】256"
      Height          =   240
      Index           =   9
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   69
      Top             =   6435
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page08】256"
      Height          =   240
      Index           =   8
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   68
      Top             =   6660
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page07】256"
      Height          =   240
      Index           =   7
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   67
      Top             =   6885
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page06】256"
      Height          =   240
      Index           =   6
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   66
      Top             =   7110
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page05】256"
      Height          =   240
      Index           =   5
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   65
      Top             =   7335
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page04】256"
      Height          =   240
      Index           =   4
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   64
      Top             =   7560
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page03】256"
      Height          =   240
      Index           =   3
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   63
      Top             =   7785
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page02】256"
      Height          =   240
      Index           =   2
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   62
      Top             =   8010
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page01】256"
      Height          =   240
      Index           =   1
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   61
      Top             =   8235
      Width           =   1590
   End
   Begin VB.CommandButton Command3 
      Caption         =   "【Page00】256"
      Height          =   240
      Index           =   0
      Left            =   4770
      Style           =   1  'Graphical
      TabIndex        =   60
      Top             =   8460
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector15】4096"
      Height          =   240
      Index           =   15
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   58
      Top             =   5085
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector14】4096"
      Height          =   240
      Index           =   14
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   57
      Top             =   5310
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector13】4096"
      Height          =   240
      Index           =   13
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   56
      Top             =   5535
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector12】4096"
      Height          =   240
      Index           =   12
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   55
      Top             =   5760
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector11】4096"
      Height          =   240
      Index           =   11
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   54
      Top             =   5985
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector10】4096"
      Height          =   240
      Index           =   10
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   53
      Top             =   6210
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector09】4096"
      Height          =   240
      Index           =   9
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   52
      Top             =   6435
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector08】4096"
      Height          =   240
      Index           =   8
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   51
      Top             =   6660
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector07】4096"
      Height          =   240
      Index           =   7
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   50
      Top             =   6885
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector06】4096"
      Height          =   240
      Index           =   6
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   49
      Top             =   7110
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector05】4096"
      Height          =   240
      Index           =   5
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   48
      Top             =   7335
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector04】4096"
      Height          =   240
      Index           =   4
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   47
      Top             =   7560
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector03】4096"
      Height          =   240
      Index           =   3
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   46
      Top             =   7785
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector02】4096"
      Height          =   240
      Index           =   2
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   45
      Top             =   8010
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector01】4096"
      Height          =   240
      Index           =   1
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   44
      Top             =   8235
      Width           =   1590
   End
   Begin VB.CommandButton Command2 
      Caption         =   "【Sector00】4096"
      Height          =   240
      Index           =   0
      Left            =   2565
      Style           =   1  'Graphical
      TabIndex        =   43
      Top             =   8460
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block31】65536"
      Height          =   240
      Index           =   31
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   42
      Top             =   1485
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block30】65536"
      Height          =   240
      Index           =   30
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   41
      Top             =   1710
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block29】65536"
      Height          =   240
      Index           =   29
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   40
      Top             =   1935
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block28】65536"
      Height          =   240
      Index           =   28
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   39
      Top             =   2160
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block27】65536"
      Height          =   240
      Index           =   27
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   38
      Top             =   2385
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block26】65536"
      Height          =   240
      Index           =   26
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   37
      Top             =   2610
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block25】65536"
      Height          =   240
      Index           =   25
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   36
      Top             =   2835
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block24】65536"
      Height          =   240
      Index           =   24
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   35
      Top             =   3060
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block23】65536"
      Height          =   240
      Index           =   23
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   34
      Top             =   3285
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block22】65536"
      Height          =   240
      Index           =   22
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   33
      Top             =   3510
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block21】65536"
      Height          =   240
      Index           =   21
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   32
      Top             =   3735
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block20】65536"
      Height          =   240
      Index           =   20
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   31
      Top             =   3960
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block19】65536"
      Height          =   240
      Index           =   19
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   30
      Top             =   4185
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block18】65536"
      Height          =   240
      Index           =   18
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   29
      Top             =   4410
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block17】65536"
      Height          =   240
      Index           =   17
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   4635
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block16】65536"
      Height          =   240
      Index           =   16
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   27
      Top             =   4860
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block15】65536"
      Height          =   240
      Index           =   15
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   26
      Top             =   5085
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block14】65536"
      Height          =   240
      Index           =   14
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   25
      Top             =   5310
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block13】65536"
      Height          =   240
      Index           =   13
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   24
      Top             =   5535
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block12】65536"
      Height          =   240
      Index           =   12
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   23
      Top             =   5760
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block11】65536"
      Height          =   240
      Index           =   11
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   22
      Top             =   5985
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block10】65536"
      Height          =   240
      Index           =   10
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   21
      Top             =   6210
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block09】65536"
      Height          =   240
      Index           =   9
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   20
      Top             =   6435
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block08】65536"
      Height          =   240
      Index           =   8
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   19
      Top             =   6660
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block07】65536"
      Height          =   240
      Index           =   7
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   6885
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block06】65536"
      Height          =   240
      Index           =   6
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   7110
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block05】65536"
      Height          =   240
      Index           =   5
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   7335
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block04】65536"
      Height          =   240
      Index           =   4
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   7560
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block03】65536"
      Height          =   240
      Index           =   3
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   7785
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block02】65536"
      Height          =   240
      Index           =   2
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   8010
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block01】65536"
      Height          =   240
      Index           =   1
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   8235
      Width           =   1590
   End
   Begin VB.CommandButton Command1 
      Caption         =   "【Block00】65536"
      Height          =   240
      Index           =   0
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   8460
      Width           =   1590
   End
   Begin VB.CommandButton Command13 
      Caption         =   "第31块区第15扇区第15页写"
      Height          =   285
      Left            =   6795
      MaskColor       =   &H000000FF&
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   5850
      Width           =   3660
   End
   Begin VB.CommandButton Command14 
      BackColor       =   &H000000FF&
      Caption         =   "第31块区第15扇区第15页读"
      Height          =   285
      Left            =   6795
      MaskColor       =   &H000000FF&
      TabIndex        =   7
      Top             =   6210
      Width           =   3660
   End
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   210
      Left            =   45
      TabIndex        =   6
      Top             =   9090
      Visible         =   0   'False
      Width           =   7635
      _ExtentX        =   13467
      _ExtentY        =   370
      _Version        =   393216
      Appearance      =   0
      Max             =   255
      Scrolling       =   1
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   6975
      Top             =   3240
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   57600
   End
   Begin VB.Frame Frame1 
      Caption         =   "信息提示："
      Height          =   1560
      Left            =   6750
      TabIndex        =   3
      Top             =   7335
      Width           =   3735
      Begin VB.TextBox Text1 
         BackColor       =   &H00FFFFFF&
         Height          =   1200
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   4
         TabStop         =   0   'False
         ToolTipText     =   "信息提示栏"
         Top             =   225
         Width           =   3465
      End
   End
   Begin VB.Frame fraResult 
      Caption         =   "第0块区中第0扇区中第0页中包含256个字节："
      Height          =   4485
      Left            =   2340
      TabIndex        =   1
      Top             =   135
      Width           =   8145
      Begin VB.Timer Timer1 
         Interval        =   1000
         Left            =   6120
         Top             =   3330
      End
      Begin MSFlexGridLib.MSFlexGrid DisplayGrid 
         Height          =   4050
         Left            =   120
         TabIndex        =   2
         TabStop         =   0   'False
         ToolTipText     =   "数据缓冲区"
         Top             =   315
         Width           =   7875
         _ExtentX        =   13891
         _ExtentY        =   7144
         _Version        =   393216
         Rows            =   100
         Cols            =   15
         RowHeightMin    =   360
         BackColor       =   16777152
         BackColorFixed  =   -2147483637
         BackColorBkg    =   16777215
         AllowBigSelection=   0   'False
         ScrollTrack     =   -1  'True
         ScrollBars      =   0
         FormatString    =   " "
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "宋体"
            Size            =   9
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
   End
   Begin VB.Frame fraMenu 
      Caption         =   "串口选择："
      Height          =   870
      Left            =   135
      TabIndex        =   0
      Top             =   135
      Width           =   2040
      Begin VB.ComboBox Combo1 
         Height          =   300
         Left            =   450
         TabIndex        =   9
         Text            =   "Combo1"
         Top             =   360
         Width           =   1095
      End
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   5
      Top             =   9030
      Width           =   10620
      _ExtentX        =   18733
      _ExtentY        =   556
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   13547
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
            TextSave        =   "15:00"
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Command6"
      Height          =   420
      Left            =   6435
      TabIndex        =   77
      Top             =   1800
      Width           =   735
   End
   Begin VB.Label Label3 
      BackColor       =   &H00008000&
      Caption         =   "第15扇区中含16个页"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   4770
      TabIndex        =   76
      Top             =   4860
      Width           =   1680
   End
   Begin VB.Label Label2 
      BackColor       =   &H000000FF&
      Caption         =   "第31块包中含16个扇区"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   2475
      TabIndex        =   59
      Top             =   4860
      Width           =   1815
   End
   Begin VB.Label Label1 
      BackColor       =   &H00808000&
      Caption         =   "W25Q16包含32个块"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   405
      TabIndex        =   11
      Top             =   1260
      Width           =   1455
   End
   Begin VB.Shape Shape2 
      BorderColor     =   &H00404040&
      BorderStyle     =   6  'Inside Solid
      FillColor       =   &H00808000&
      FillStyle       =   0  'Solid
      Height          =   7710
      Left            =   135
      Top             =   1170
      Width           =   2040
   End
   Begin VB.Shape Shape3 
      FillColor       =   &H00008000&
      FillStyle       =   0  'Solid
      Height          =   4110
      Left            =   4545
      Top             =   4770
      Width           =   2040
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   4110
      Left            =   2340
      Top             =   4770
      Width           =   2040
   End
   Begin VB.Image Image2 
      Height          =   600
      Left            =   7155
      MouseIcon       =   "frmDemo.frx":0CCA
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":0E1C
      Top             =   6615
      Width           =   2910
   End
   Begin VB.Image Image1 
      Height          =   600
      Left            =   7155
      MouseIcon       =   "frmDemo.frx":699E
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":6AF0
      Top             =   6615
      Width           =   2910
   End
   Begin VB.Image Image4 
      Height          =   600
      Left            =   7155
      MouseIcon       =   "frmDemo.frx":C672
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":C7C4
      Top             =   6615
      Width           =   2910
   End
   Begin VB.Image Image3 
      Height          =   600
      Left            =   7155
      MouseIcon       =   "frmDemo.frx":12346
      MousePointer    =   99  'Custom
      Picture         =   "frmDemo.frx":12498
      Top             =   6615
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
    Dim n As Integer
    For n = 0 To 31 Step 1
        Command1(n).BackColor = &H8000000F
    Next n
    Command1(Index).BackColor = &HFF&
    If OldBlock <> Index Then
        OldBlock = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页"
        Call writetext1
        Call IniGrid
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
        Command11.Caption = "第" & OldBlock & "块区擦除"
        Command12.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区擦除"
        Command13.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页写"
        Command14.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页读"
    End If
    Command6.SetFocus
End Sub
Private Sub Command2_Click(Index As Integer)
    Dim n As Integer
    For n = 0 To 15 Step 1
        Command2(n).BackColor = &H8000000F
    Next n
    Command2(Index).BackColor = &H8000&
    If OldSector <> Index Then
        OldSector = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页"
        Call writetext1
        Call IniGrid
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)："
        Command11.Caption = "第" & OldBlock & "块区擦除"
        Command12.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区擦除"
        Command13.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页写"
        Command14.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页读"
    End If
    Command6.SetFocus
End Sub
Private Sub Command3_click(Index As Integer)
    Dim n As Integer
    For n = 0 To 15 Step 1
        Command3(n).BackColor = &H8000000F
    Next n
    Command3(Index).BackColor = &HFFFFC0
    If OldPage <> Index Then
        OldPage = Index
        Textbuf = "缓冲区为:第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页"
        Call writetext1
        Call IniGrid
        Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
        Label3.Caption = "第" & OldSector & "扇区包含16个页"
        fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
        Command11.Caption = "第" & OldBlock & "块区擦除"
        Command12.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区擦除"
        Command13.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页写"
        Command14.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页读"
    End If
    Command6.SetFocus
End Sub
Private Sub Command10_Click() '整片擦除
    Dim i As Long
    HEAD_DATA(0) = &H4
    HEAD_DATA(2) = "&H" & Hex(OldBlock)
    HEAD_DATA(3) = "&H" & Hex(OldSector * 16 + OldPage)
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
    HEAD_DATA(2) = "&H" & Hex(OldBlock)
    HEAD_DATA(3) = "&H" & Hex(OldSector * 16 + OldPage)
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
Private Sub Command14_Click()
    Call readdata
    Command6.SetFocus
End Sub

Private Sub DisplayGrid_DblClick()
    grow = DisplayGrid.Row
    gCol = DisplayGrid.Col
    data = DisplayGrid.Text
    If gCol > 16 Or gCol < 1 Or grow < 1 Then
        Exit Sub
    End If
    Form1.Show vbModal, Me
    DisplayGrid.Text = data
    Call Asciicode
End Sub
Private Sub DisplayGrid_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim ii As Integer
    If Button = 2 Then
        'Form2.Left = x + Form1.Width - 400
        'Form2.Top = y + Form1.Height
        editok = False
        Form2.Show vbModal, Me
        If editok = True Then
            For ii = STARTADDR To STOPADDR Step 1
                DisplayGrid.TextMatrix(ii \ 16 + 1, ii Mod 16 + 1) = ADDRDATA
            Next ii
            Call Asciicode
        End If
    Else
        Form2.Hide
    End If
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
    Call IniGrid
    Textbuf = "欢迎使用--[GL9型51单片机开发学习系统]"
    Call writetext1
    Textbuf = "给力者单片机开发学习系统，开发、学习都给力！"
    Call writetext1
    Call firstlink
    Textbuf = "缓冲区为:第" & OldBlock & "块中第" & OldSector & "扇区中第" & OldPage & "页"
    Call writetext1
    Label2.Caption = "第" & OldBlock & "块区包含16个扇区"
    Label3.Caption = "第" & OldSector & "扇区包含16个页"
    fraResult.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页：(256字节)"
    Command11.Caption = "第" & OldBlock & "块区擦除"
    Command12.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区擦除"
    Command13.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页写"
    Command14.Caption = "第" & OldBlock & "块区中第" & OldSector & "扇区中第" & OldPage & "页读"
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

Private Sub readdata()
    Dim Str As String
    Dim i As Long
    Dim v, x As Integer

    HEAD_DATA(0) = &H3
    HEAD_DATA(2) = "&H" & Hex(OldBlock)
    HEAD_DATA(3) = "&H" & Hex(OldSector * 16 + OldPage)
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "3" Then
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
 '经过沟通，可以读了，进行读操作
    ProgressBar1.Min = 0
    ProgressBar1.Max = 15
    ProgressBar1.Visible = True
    For x = 0 To 15 Step 1 '接收16次
        ProgressBar1.Value = x
        HEAD_DATA(1) = &H1
        HEAD_DATA(18) = "&H" & Hex(OldBlock)
        HEAD_DATA(19) = "&H" & Hex(OldSector * 16 + OldPage)
        HEAD_DATA(20) = "&H" & Hex(x * 16)
        MSComm1.Output = HEAD_DATA
        For i = 0 To 80000 Step 1
            If MSComm1.InBufferCount > 20 Then
                com_buf = MSComm1.Input
                For v = 2 To 17 Step 1
                    Str = Hex(com_buf(v))
                    Str = Trim(Str)
                    If Len(Str) = 1 Then Str = "0" & Str
                    DisplayGrid.TextMatrix(x + 1, v - 1) = Str
                Next v
                Exit For
            End If
            If i > 79900 Then
                Textbuf = "通讯超时"
                Call writetext1
                ProgressBar1.Visible = False
                Exit Sub
             End If
        Next i
    Next x
    HEAD_DATA(1) = &H0
    MSComm1.Output = HEAD_DATA
    Textbuf = "读W25Q16数据成功"
    ProgressBar1.Visible = False
    Call writetext1
    Call Asciicode
End Sub

Private Sub writedata()
    Dim Str As String
    Dim i As Long
    Dim x, y As Integer
    
    HEAD_DATA(0) = &H2
    HEAD_DATA(2) = "&H" & Hex(OldBlock)
    HEAD_DATA(3) = "&H" & Hex(OldSector * 16 + OldPage)
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
            Textbuf = "通讯超时，请检查开发板电源开关、数据线！"
            Call writetext1
            Exit Sub
        End If
    Next i
 '===============================================
    ProgressBar1.Min = 0
    ProgressBar1.Max = 15
    ProgressBar1.Visible = True
    For x = 0 To 15 Step 1  '接收16次
        ProgressBar1.Value = x
        For y = 2 To 17 Step 1
            HEAD_DATA(y) = "&H" & DisplayGrid.TextMatrix(x + 1, y - 1)
        Next y
        HEAD_DATA(1) = &H1
        HEAD_DATA(18) = "&H" & Hex(OldBlock)
        HEAD_DATA(19) = "&H" & Hex(OldSector * 16 + OldPage)
        HEAD_DATA(20) = "&H" & Hex(x * 16)
        MSComm1.InputLen = 0
        MSComm1.Output = HEAD_DATA
        For i = 0 To 80000 Step 1
            If MSComm1.InBufferCount > 20 Then
                com_buf = MSComm1.Input
                Exit For
            End If
            If i > 79900 Then
                Textbuf = "通讯超时"
                Call writetext1
                ProgressBar1.Visible = False
                Exit Sub
            End If
        Next i
    Next x
    HEAD_DATA(1) = &H0
    MSComm1.Output = HEAD_DATA
    Textbuf = "写W25Q16数据成功"
    Call writetext1
    ProgressBar1.Visible = False
End Sub
Private Sub IniGrid()
    Dim n, i As Integer
    Dim k As String
    k = Hex(OldBlock)
    If Len(k) = 1 Then k = "0" & k
    With DisplayGrid
        .Cols = 17
        .Rows = 17
        .FormatString = " |^0|^1|^2|^3|^4|^5|^6|^7|^8|^9|^A|^B|^C|^D|^E|^F|^  ASCII "
        .ColWidth(0) = 900
        For i = .FixedCols To .Cols - 1
           .ColWidth(i) = 300
           .ColWidth(17) = 2050
        Next i
        For n = 1 To 16
           .RowHeight(n) = 220
           .TextMatrix(n, 0) = " " & k & Hex(OldSector) & Hex(OldPage) & Trim(Hex(n - 1)) & "0H "
            For i = 1 To 16 Step 1
                .TextMatrix(n, i) = "FF"
            Next
        Next
        Call Asciicode
        Exit Sub
    End With
ERRCOM:
    Beep
    Beep
End Sub
Private Sub Asciicode()
    Dim x, y As Integer
    Dim H, L, A As Integer
    Dim Str1, Str As String
    With DisplayGrid
        For x = 1 To 16 Step 1 '1-16行，逐行处理
            Str1 = ""
            For y = 1 To 16 Step 1  '逐列处理
                Str = Left(.TextMatrix(x, y), 1)
                If Str = "0" Then H = 0
                If Str = "1" Then H = 1
                If Str = "2" Then H = 2
                If Str = "3" Then H = 3
                If Str = "4" Then H = 4
                If Str = "5" Then H = 5
                If Str = "6" Then H = 6
                If Str = "7" Then H = 7
                If Str = "8" Then H = 8
                If Str = "9" Then H = 9
                If Str = "A" Then H = 10
                If Str = "B" Then H = 11
                If Str = "C" Then H = 12
                If Str = "D" Then H = 13
                If Str = "E" Then H = 14
                If Str = "F" Then H = 15
          
                Str = Right(.TextMatrix(x, y), 1)
                If Str = "0" Then L = 0
                If Str = "1" Then L = 1
                If Str = "2" Then L = 2
                If Str = "3" Then L = 3
                If Str = "4" Then L = 4
                If Str = "5" Then L = 5
                If Str = "6" Then L = 6
                If Str = "7" Then L = 7
                If Str = "8" Then L = 8
                If Str = "9" Then L = 9
                If Str = "A" Then L = 10
                If Str = "B" Then L = 11
                If Str = "C" Then L = 12
                If Str = "D" Then L = 13
                If Str = "E" Then L = 14
                If Str = "F" Then L = 15
          
                A = H * 16 + L
                If A < 30 Then
                    Str = "."
                ElseIf A > 127 Then
                    Str = "."
                Else
                    Str = Chr(A)
                End If
                Str1 = Str1 & Str
            Next y
            .TextMatrix(x, 17) = Str1
        Next x
    End With
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
