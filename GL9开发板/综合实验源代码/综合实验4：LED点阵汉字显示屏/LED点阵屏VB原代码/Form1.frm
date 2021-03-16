VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BorderStyle     =   1  'Fixed Single
   Caption         =   "给力者GL9中文电子显示屏软件"
   ClientHeight    =   3075
   ClientLeft      =   45
   ClientTop       =   405
   ClientWidth     =   5790
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3075
   ScaleWidth      =   5790
   StartUpPosition =   2  '屏幕中心
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   3510
      Top             =   1350
   End
   Begin VB.Frame Frame1 
      Caption         =   "串口选择："
      Height          =   645
      Left            =   3285
      TabIndex        =   4
      Top             =   1935
      Width           =   1320
      Begin VB.ComboBox Combo1 
         Height          =   300
         Left            =   225
         TabIndex        =   5
         Text            =   "Combo1"
         Top             =   225
         Width           =   870
      End
   End
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   285
      Left            =   0
      TabIndex        =   3
      Top             =   2745
      Width           =   5790
      _ExtentX        =   10213
      _ExtentY        =   503
      _Version        =   327682
      Appearance      =   0
   End
   Begin ComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   2
      Top             =   2700
      Width           =   5790
      _ExtentX        =   10213
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   10231
            MinWidth        =   10231
            Text            =   "宁波芯动电子有限公司"
            TextSave        =   "宁波芯动电子有限公司"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   3360
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   1515
      Left            =   120
      TabIndex        =   1
      Top             =   225
      Width           =   5535
      _ExtentX        =   9763
      _ExtentY        =   2672
      _Version        =   393217
      BackColor       =   16777088
      Enabled         =   -1  'True
      ScrollBars      =   2
      DisableNoScroll =   -1  'True
      TextRTF         =   $"Form1.frx":0CCA
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "微软雅黑"
         Size            =   12
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton Command1 
      Caption         =   "下 载"
      Height          =   400
      Left            =   4770
      TabIndex        =   0
      Top             =   2115
      Width           =   765
   End
   Begin VB.Image Image1 
      Height          =   600
      Left            =   180
      MouseIcon       =   "Form1.frx":0E5C
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":0FAE
      Top             =   1980
      Width           =   2910
   End
   Begin VB.Image Image4 
      Height          =   600
      Left            =   180
      MouseIcon       =   "Form1.frx":6B30
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":6C82
      Top             =   1980
      Width           =   2910
   End
   Begin VB.Image Image3 
      Height          =   600
      Left            =   180
      MouseIcon       =   "Form1.frx":C804
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":C956
      Top             =   1980
      Width           =   2910
   End
   Begin VB.Image Image2 
      Height          =   600
      Left            =   180
      MouseIcon       =   "Form1.frx":124D8
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":1262A
      Top             =   1980
      Width           =   2910
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Dim com_buf() As Byte
Dim HEAD_DATA(20) As Byte
Dim i As Long
Dim TempHL(255) As String
Dim OldPort As String
Dim Port As Integer
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

Private Sub Command1_Click()
    Dim x, y As Integer
    Dim Temp8 As String
    Dim temp9(15) As String
    Dim L2 As Long
    Dim m1 As String
    m1 = ""
    RichTextBox1.Text = Trim(RichTextBox1.Text)
    For i = 1 To Len(RichTextBox1.Text)
        If Asc(Mid(RichTextBox1.Text, i, 1)) <> 13 And Asc(Mid(RichTextBox1.Text, i, 1)) <> 10 Then m1 = m1 & Mid(RichTextBox1.Text, i, 1)
    Next
    RichTextBox1.Text = m1
    RichTextBox1.Text = StrConv(RichTextBox1.Text, 4)
    If Len(RichTextBox1.Text) > 32 Then
        MsgBox "文字数量超过32！多余字符将舍弃", vbOKOnly, "警告！"
        RichTextBox1.Text = Left(RichTextBox1.Text, 32)
    End If
    For i = 0 To 255 Step 1
        TempHL(i) = &HFF
    Next i
    For i = 1 To Len(RichTextBox1.Text)
        TempHL((i - 1) * 2) = AscB(MidB(StrConv(Mid(RichTextBox1.Text, i, 1), vbFromUnicode), 1, 1))
        TempHL((i - 1) * 2 + 1) = AscB(MidB(StrConv(Mid(RichTextBox1.Text, i, 1), vbFromUnicode), 2, 1))
    Next i
    TempHL(250) = &H6
    TempHL(251) = &H24
    TempHL(252) = "&H" & Hex(Len(RichTextBox1.Text))
    If Len(RichTextBox1.Text) = 0 Then
        MsgBox "发送区内无文字!", vbOKOnly, "给力者提醒："
        Exit Sub
    End If
    If Len(RichTextBox1.Text) > 32 Then
        MsgBox "发送区内文字大于32字!", vbOKOnly, "给力者提醒："
        Exit Sub
    End If
    HEAD_DATA(0) = &H2
    MSComm1.InputLen = 0
    MSComm1.Output = HEAD_DATA
    For i = 0 To 1000000 Step 1
        If MSComm1.InBufferCount > 20 Then
            com_buf = MSComm1.Input
            If Hex(com_buf(0)) = "2" Then
                Exit For
            Else
                StatusBar1.Panels(1).Text = "开发板未准备好"
                Exit Sub
            End If
        End If
        If i > 999900 Then
            StatusBar1.Panels(1).Text = "通讯超时"
            Exit Sub
        End If
    Next i
    ProgressBar1.Min = 0
    ProgressBar1.Max = 16
    ProgressBar1.Visible = True
    For x = 0 To 15 Step 1 '发送L/16次
        ProgressBar1.Value = x
        For y = 0 To 15 Step 1
            HEAD_DATA(y + 2) = TempHL(x * 16 + y)
        Next y
        L2 = 2096896 + x * 16
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
                StatusBar1.Panels(1).Text = "通讯超时"
                ProgressBar1.Visible = False
                Exit Sub
            End If
        Next i
    Next x
    HEAD_DATA(1) = &H0
    MSComm1.Output = HEAD_DATA
    StatusBar1.Panels(1).Text = "下载数据成功"
    ProgressBar1.Visible = False
End Sub
Private Sub Form_Load()
    Port = 4
    MSComm1.CommPort = Port
    ProgressBar1.Visible = False
    Combo1.Text = "COM4"
    OldPort = "COM4"
    For i = 0 To 255 Step 1
        TempHL(i) = &HFF
    Next i
    Call firstlink
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
    With RichTextBox1
        .SelStart = 0
        .SelLength = Len(RichTextBox1.Text)
    End With
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
                StatusBar1.Panels(1).Text = "检测到--[GL9型51单片机开发学习系统]"
                Exit Sub
            End If
        End If
    Next i
    StatusBar1.Panels(1).Text = "未检测到--[GL9型51单片机开发学习系统]"
    
    Exit Sub
merror1:
    Response = MsgBox("端口无效或不可用！请更改端口。", 16, "给力者提示")
    StatusBar1.Panels(1).Text = "未检测到--[GL9型51单片机开发学习系统]"
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

Private Sub RichTextBox1_Change()
    If Len(RichTextBox1.Text) < 33 Then
        StatusBar1.Panels(1).Text = "总字数为32字,当前字数为" & Len(RichTextBox1.Text) & "字,还可写入" & 32 - Len(RichTextBox1.Text) & "字"
    Else
        StatusBar1.Panels(1).Text = "总字数为32字,当前字数为" & Len(RichTextBox1.Text) & "字,多余的" & Len(RichTextBox1.Text) - 32 & "字将被舍弃。"
    End If
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
