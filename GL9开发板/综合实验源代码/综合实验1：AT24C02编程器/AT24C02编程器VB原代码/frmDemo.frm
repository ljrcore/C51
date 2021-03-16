VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmDemo 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "给力者AT24C02编程器上位机软件V1.0"
   ClientHeight    =   6525
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   7935
   Icon            =   "frmDemo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6525
   ScaleWidth      =   7935
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton Command2 
      Caption         =   "写入"
      Height          =   375
      Left            =   7020
      TabIndex        =   8
      Top             =   5715
      Width           =   780
   End
   Begin VB.CommandButton Command1 
      Caption         =   "读出"
      Height          =   375
      Left            =   6075
      TabIndex        =   7
      Top             =   5715
      Width           =   780
   End
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   210
      Left            =   0
      TabIndex        =   6
      Top             =   6300
      Visible         =   0   'False
      Width           =   5025
      _ExtentX        =   8864
      _ExtentY        =   370
      _Version        =   393216
      Appearance      =   0
      Max             =   255
      Scrolling       =   1
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   2880
      Top             =   2700
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   57600
   End
   Begin VB.Frame Frame1 
      Caption         =   "信息提示："
      Height          =   1650
      Left            =   90
      TabIndex        =   3
      Top             =   4500
      Width           =   5805
      Begin VB.TextBox Text1 
         BackColor       =   &H00FFFFC0&
         Height          =   1200
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   4
         TabStop         =   0   'False
         ToolTipText     =   "信息提示栏"
         Top             =   270
         Width           =   5535
      End
   End
   Begin VB.Frame fraResult 
      Height          =   4350
      Left            =   90
      TabIndex        =   1
      Top             =   45
      Width           =   7740
      Begin MSFlexGridLib.MSFlexGrid DisplayGrid 
         Height          =   4050
         Left            =   120
         TabIndex        =   2
         TabStop         =   0   'False
         ToolTipText     =   "数据缓冲区"
         Top             =   180
         Width           =   7485
         _ExtentX        =   13203
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
      Height          =   1005
      Left            =   6030
      TabIndex        =   0
      Top             =   4500
      Width           =   1815
      Begin VB.ComboBox Combo1 
         Height          =   300
         Left            =   360
         TabIndex        =   9
         Text            =   "Combo1"
         Top             =   405
         Width           =   1095
      End
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   5
      Top             =   6255
      Width           =   7935
      _ExtentX        =   13996
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   8811
            Text            =   "宁波芯动电子有限公司  www.MovingChip.com"
            TextSave        =   "宁波芯动电子有限公司  www.MovingChip.com"
            Object.ToolTipText     =   "创中国开发板第一品牌"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "2012-10-16"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "15:38"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmDemo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim com_buf() As Byte
Dim E As Integer
Dim Textbuf As String
Dim lstr1, lstr2, lstr3, lstr4, lstr5, lstr6 As String
Dim HEAD_DATA(17) As Byte
Dim OldPort As String
Dim Port As Integer


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


Private Sub Command1_Click()
    Call readdata
End Sub

Private Sub Command2_Click()
    Call writedata
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
    Call IniGrid
    Textbuf = "欢迎使用--[GL9型51单片机开发学习系统]"
    Call writetext1
    Textbuf = "给力者单片机开发学习系统，开发、学习都给力！"
    Call writetext1
    Call firstlink
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
        If MSComm1.InBufferCount > 17 Then
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
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    ok = False
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 17 Then
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
        MSComm1.Output = HEAD_DATA
        For i = 0 To 80000 Step 1
            If MSComm1.InBufferCount > 17 Then
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
    Textbuf = "读AT24C02数据成功"
    ProgressBar1.Visible = False
    Call writetext1
    Call Asciicode
End Sub

Private Sub writedata()
    Dim Str As String
    Dim i As Long
    Dim x, y As Integer
    
    HEAD_DATA(0) = &H2
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 800000 Step 1
        If MSComm1.InBufferCount > 17 Then
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
        MSComm1.InputLen = 0
        MSComm1.Output = HEAD_DATA
        For i = 0 To 80000 Step 1
            If MSComm1.InBufferCount > 17 Then
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
    Textbuf = "写AT24C02数据成功"
    Call writetext1
    ProgressBar1.Visible = False
End Sub
Private Sub IniGrid()
    Dim n, i As Integer
    With DisplayGrid
        .Cols = 17
        .Rows = 17
        .FormatString = " |^0|^1|^2|^3|^4|^5|^6|^7|^8|^9|^A" _
            & "|^B|^C|^D|^E|^F|^  ASCII ;地 址"
        For i = .FixedCols To .Cols - 1
           .ColWidth(i) = 300
           .ColWidth(17) = 2050
        Next i
        For n = 1 To 16
           .RowHeight(n) = 220
           .TextMatrix(n, 0) = " " & Trim(Hex(n - 1)) & "0H "
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
