VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "给力者测温软件V1.0"
   ClientHeight    =   6735
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10845
   FillColor       =   &H00FFFFFF&
   BeginProperty Font 
      Name            =   "宋体"
      Size            =   10.5
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "给力者温度测试.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6735
   ScaleWidth      =   10845
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  '屏幕中心
   Begin MSCommLib.MSComm MSComm1 
      Left            =   6525
      Top             =   1440
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Timer Timer1 
      Interval        =   500
      Left            =   8460
      Top             =   2565
   End
   Begin VB.Frame Frame2 
      Caption         =   "温度曲线"
      Height          =   5445
      Left            =   135
      TabIndex        =   2
      Top             =   1170
      Width           =   10560
      Begin VB.PictureBox Picture1 
         AutoRedraw      =   -1  'True
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         FillColor       =   &H00FFFFFF&
         FillStyle       =   0  'Solid
         ForeColor       =   &H8000000E&
         Height          =   5000
         Left            =   405
         ScaleHeight     =   4995
         ScaleMode       =   0  'User
         ScaleWidth      =   9680.697
         TabIndex        =   3
         Top             =   270
         Width           =   10000
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "90"
         Height          =   210
         Index           =   6
         Left            =   135
         TabIndex        =   14
         Top             =   630
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "80"
         Height          =   210
         Index           =   5
         Left            =   135
         TabIndex        =   13
         Top             =   1170
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "70"
         Height          =   210
         Index           =   4
         Left            =   135
         TabIndex        =   12
         Top             =   1665
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "60"
         Height          =   210
         Index           =   3
         Left            =   135
         TabIndex        =   11
         Top             =   2160
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "50"
         Height          =   210
         Index           =   2
         Left            =   135
         TabIndex        =   10
         Top             =   2655
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "40"
         Height          =   210
         Index           =   1
         Left            =   135
         TabIndex        =   9
         Top             =   3150
         Width           =   210
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "30"
         Height          =   210
         Left            =   135
         TabIndex        =   8
         Top             =   3645
         Width           =   210
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "20"
         Height          =   210
         Left            =   135
         TabIndex        =   7
         Top             =   4140
         Width           =   210
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "10"
         Height          =   210
         Index           =   0
         Left            =   135
         TabIndex        =   6
         Top             =   4635
         Width           =   210
      End
   End
   Begin VB.ComboBox Combo1 
      Height          =   330
      Left            =   1125
      TabIndex        =   1
      Text            =   "Combo1"
      Top             =   360
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "打开串口"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3060
      TabIndex        =   0
      Top             =   360
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "黑体"
         Size            =   26.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   585
      Left            =   5130
      TabIndex        =   5
      Top             =   225
      Width           =   1980
   End
   Begin VB.Label Label9 
      Caption         =   "端口"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   495
      TabIndex        =   4
      Top             =   405
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim TimeCount As Integer
Dim NEWdata As Integer
Dim OLDdata As Integer

Private Sub Combo1_Click()
    If MSComm1.PortOpen = True Then
        MSComm1.PortOpen = False
    End If
    MSComm1.CommPort = Combo1.ListIndex + 1 '
End Sub

Private Sub Command1_Click()
    On Error GoTo uerror
    If Command1.Caption = "关闭串口" Then
        MSComm1.PortOpen = False
        Command1.Caption = "打开串口"
        Label1.BackColor = &HC0C0C0
        Picture1.BackColor = &HC0C0C0
        Timer1.Enabled = False
    Else
       MSComm1.PortOpen = True
       Command1.Caption = "关闭串口"
       Label1.BackColor = &HFFFFC0
       Picture1.BackColor = &HFFFFC0
       Timer1.Enabled = True
       TimeCount = 0
       Picture1.Cls
       TimeCount = 0
       Picture1.Line (0, 4500)-(10000, 4500), &HC0C0C0
       Picture1.Line (0, 4000)-(10000, 4000), &HC0C0C0
       Picture1.Line (0, 3500)-(10000, 3500), &HC0C0C0
       Picture1.Line (0, 3000)-(10000, 3000), &HC0C0C0
       Picture1.Line (0, 2500)-(10000, 2500), &HC0C0C0
       Picture1.Line (0, 2000)-(10000, 2000), &HC0C0C0
       Picture1.Line (0, 1500)-(10000, 1500), &HC0C0C0
       Picture1.Line (0, 1000)-(10000, 1000), &HC0C0C0
       Picture1.Line (0, 500)-(10000, 500), &HC0C0C0
    End If
    Exit Sub
uerror:
    MsgBox "通讯异常，请检查串口设置"
End Sub
Private Sub Form_Load()
    Timer1.Enabled = False
    If MSComm1.PortOpen = True Then
        MSComm1.PortOpen = False
    End If
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
    Combo1.AddItem "COM17"
    Combo1.AddItem "COM18"
    Combo1.AddItem "COM19"
    Combo1.AddItem "COM20"
    Combo1.ListIndex = 0

    MSComm1.CommPort = Combo1.ListIndex + 1
    MSComm1.Settings = "9600,n,8,1"
    Command1.Caption = "打开串口"
End Sub

Private Sub Comlink()
    Dim HEAD_DATA(0) As Byte
    Dim com_buf() As Byte
    Dim i, j As Long
    Dim Response
    MSComm1.OutBufferCount = 0
    If MSComm1.PortOpen = False Then MSComm1.PortOpen = True
    HEAD_DATA(0) = &H89
    MSComm1.Output = HEAD_DATA
    MSComm1.InputLen = 0
    MSComm1.InputMode = comInputModeBinary
    For i = 0 To 90000 Step 1
        If MSComm1.InBufferCount > 2 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "90" Then
                Label1.Caption = com_buf(1) & "." & com_buf(2) & "℃"
                NEWdata = com_buf(1) * 10 + com_buf(2)
            End If
            Exit Sub
        End If
    Next i
    Exit Sub
End Sub

Private Sub Timer1_Timer()
    Call Comlink
    TimeCount = TimeCount + 1
    Picture1.Line ((TimeCount - 1) * 100, 5000 - OLDdata * 5)-(TimeCount * 100, 5000 - NEWdata * 5), &HFF&
    OLDdata = NEWdata
    If TimeCount > 95 Then
        Picture1.Cls
        TimeCount = 0
        Picture1.Line (0, 4500)-(10000, 4500), &HC0C0C0
        Picture1.Line (0, 4000)-(10000, 4000), &HC0C0C0
        Picture1.Line (0, 3500)-(10000, 3500), &HC0C0C0
        Picture1.Line (0, 3000)-(10000, 3000), &HC0C0C0
        Picture1.Line (0, 2500)-(10000, 2500), &HC0C0C0
        Picture1.Line (0, 2000)-(10000, 2000), &HC0C0C0
        Picture1.Line (0, 1500)-(10000, 1500), &HC0C0C0
        Picture1.Line (0, 1000)-(10000, 1000), &HC0C0C0
        Picture1.Line (0, 500)-(10000, 500), &HC0C0C0
    End If
End Sub

