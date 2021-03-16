VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "编辑缓冲区"
   ClientHeight    =   1800
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2925
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1800
   ScaleWidth      =   2925
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   375
      Left            =   1980
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   900
      Width           =   675
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   1980
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   315
      Width           =   675
   End
   Begin VB.TextBox Text2 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   1080
      MaxLength       =   2
      TabIndex        =   2
      Text            =   "Text2"
      Top             =   945
      Width           =   600
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   315
      Left            =   1080
      TabIndex        =   5
      TabStop         =   0   'False
      Text            =   "Text1"
      ToolTipText     =   "缓冲区地址"
      Top             =   360
      Width           =   600
   End
   Begin VB.Label Label2 
      Caption         =   "数据(HEX):"
      Height          =   315
      Left            =   180
      TabIndex        =   4
      Top             =   1020
      Width           =   960
   End
   Begin VB.Label Label1 
      Caption         =   "地址(HEX):"
      Height          =   315
      Left            =   180
      TabIndex        =   3
      Top             =   420
      Width           =   1050
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    If Len(Trim(Text2.Text)) = 1 Then Text2.Text = "0" & Text2.Text
    data = Text2.Text
    Unload Me
End Sub

Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Text1.Text = Hex(grow - 1) & Hex(gCol - 1)
    Text2.Text = data
End Sub

Private Sub Text2_KeyPress(KeyAscii As Integer)
    Dim Response
    If KeyAscii = 13 Then
        If Len(Trim(Text2.Text)) = 1 Then Text2.Text = "0" & Text2.Text
        data = Text2.Text
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
Private Sub Text2_GotFocus()
    Text2.SelStart = 0
    Text2.SelLength = Len(Text2)
End Sub

