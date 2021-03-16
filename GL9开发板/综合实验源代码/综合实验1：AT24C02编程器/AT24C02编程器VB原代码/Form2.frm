VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "编辑缓冲区"
   ClientHeight    =   2250
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3105
   Icon            =   "Form2.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2250
   ScaleWidth      =   3105
   StartUpPosition =   2  '屏幕中心
   Begin VB.TextBox Text3 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   1920
      MaxLength       =   2
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   1080
      Width           =   915
   End
   Begin VB.TextBox Text2 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   1920
      MaxLength       =   2
      TabIndex        =   7
      Text            =   "Text1"
      Top             =   660
      Width           =   915
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   1920
      MaxLength       =   2
      TabIndex        =   6
      Text            =   "Text1"
      Top             =   240
      Width           =   915
   End
   Begin VB.CommandButton Command2 
      Caption         =   "退出"
      Height          =   375
      Left            =   1740
      TabIndex        =   5
      Top             =   1620
      Width           =   915
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   480
      TabIndex        =   4
      Top             =   1620
      Width           =   915
   End
   Begin VB.Label Label3 
      Caption         =   "填充数据(HEX):"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1140
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "结束地址(HEX):"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   1515
   End
   Begin VB.Label Label1 
      Caption         =   "起始地址(HEX):"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   300
      Width           =   1575
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Outchar1 As Byte

Private Sub Command1_Click()
    Dim Aa1, Aa2, Aa3, Aa4 As Long
    Dim L1, L2 As Long
    Dim Response
    Dim buf1 As String
    If Text1.Text = "" Then
        Beep
        Response = MsgBox("起始地址不能为空！", 16, "错误提示")
        Exit Sub
    End If
    If Text2.Text = "" Then
        Beep
        Response = MsgBox("结束地址不能为空！", 16, "错误提示")
        Exit Sub
    End If
    If Text3.Text = "" Then
        Beep
        Response = MsgBox("填充数据不能为空！", 16, "错误提示")
        Exit Sub
    End If

    If Len(Trim(Text1.Text)) = 1 Then Text1.Text = "0" & Text1.Text
    If Len(Trim(Text2.Text)) = 1 Then Text2.Text = "0" & Text2.Text
    If Len(Trim(Text3.Text)) = 1 Then Text3.Text = "0" & Text3.Text


    Call CharToNumn(Mid(Trim(Text1.Text), 1, 1))
    Aa1 = Outchar1
    Call CharToNumn(Mid(Trim(Text1.Text), 2, 1))
    Aa2 = Outchar1
    L1 = Aa1 * 16 + Aa2

    Call CharToNumn(Mid(Trim(Text2.Text), 1, 1))
    Aa1 = Outchar1
    Call CharToNumn(Mid(Trim(Text2.Text), 2, 1))
    Aa2 = Outchar1
    L2 = Aa1 * 16 + Aa2

    If L1 > L2 Then
        Response = MsgBox("起始地址大于结束地址！", 16, "错误提示")
        Exit Sub
    End If
    If L1 > 255 Or L2 > 255 Then
        Response = MsgBox("结束地址大于缓冲区地址！", 16, "错误提示")
        Exit Sub
    End If
    ADDRDATA = Text3.Text
    STARTADDR = L1
    STOPADDR = L2
    editok = True
    Unload Me
End Sub

Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Text1.Text = "00"
    Text2.Text = "FF"
    Text3.Text = "FF"
End Sub

Private Sub Text3_GotFocus()
    Text3.SelStart = 0
    Text3.SelLength = Len(Text2)
End Sub

Private Sub CharToNumn(inChar1 As String)
    Select Case inChar1
        Case "0": Outchar1 = 0
        Case "1": Outchar1 = 1
        Case "2": Outchar1 = 2
        Case "3": Outchar1 = 3
        Case "4": Outchar1 = 4
        Case "5": Outchar1 = 5
        Case "6": Outchar1 = 6
        Case "7": Outchar1 = 7
        Case "8": Outchar1 = 8
        Case "9": Outchar1 = 9
        Case "A": Outchar1 = 10
        Case "B": Outchar1 = 11
        Case "C": Outchar1 = 12
        Case "D": Outchar1 = 13
        Case "E": Outchar1 = 14
        Case "F": Outchar1 = 15
        Case Else:       Outchar1 = 0
    End Select
End Sub

Private Sub Text3_KeyPress(KeyAscii As Integer)
    Dim Response
    If KeyAscii = 13 Then
       If Len(Trim(Text3.Text)) = 1 Then Text3.Text = "0" & Text2.Text
       Unload Me
       KeyAscii = 0
       Exit Sub
    End If
    If KeyAscii <> 8 And KeyAscii < 48 Or KeyAscii > 102 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 57 And KeyAscii < 65 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 70 And KeyAscii < 97 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii >= 97 And KeyAscii <= 122 Then
        KeyAscii = KeyAscii - 32
    End If
End Sub
Private Sub Text2_KeyPress(KeyAscii As Integer)
    Dim Response
    If KeyAscii = 13 Then
       If Len(Trim(Text2.Text)) = 1 Then Text2.Text = "0" & Text2.Text
       Unload Me
       KeyAscii = 0
       Exit Sub
    End If
    If KeyAscii <> 8 And KeyAscii < 48 Or KeyAscii > 102 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 57 And KeyAscii < 65 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 70 And KeyAscii < 97 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii >= 97 And KeyAscii <= 122 Then
        KeyAscii = KeyAscii - 32
    End If
End Sub
Private Sub Text1_KeyPress(KeyAscii As Integer)
    Dim Response
    If KeyAscii = 13 Then
       If Len(Trim(Text1.Text)) = 1 Then Text1.Text = "0" & Text2.Text
       Unload Me
       KeyAscii = 0
       Exit Sub
    End If
    If KeyAscii <> 8 And KeyAscii < 48 Or KeyAscii > 102 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 57 And KeyAscii < 65 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii > 70 And KeyAscii < 97 Then
        Beep
        KeyAscii = 0
        Response = MsgBox("只能输入0123456789ABCDEF", 16, "系统提示")
    End If
    If KeyAscii >= 97 And KeyAscii <= 122 Then
        KeyAscii = KeyAscii - 32
    End If
End Sub


