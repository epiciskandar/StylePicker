
// StylePickerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StylePicker.h"
#include "StylePickerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStylePickerDlg dialog


LRESULT CALLBACK MyWNDPROC(HWND hWnd, UINT cmd, WPARAM wParam, LPARAM lParam)
{
	switch (cmd)
	{
	case WM_CLOSE:
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd,cmd,wParam,lParam);
}

LPSTR ConvertErrorCodeToString(DWORD ErrorCode)  
{  
	HLOCAL LocalAddress=NULL;  
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,  
		NULL,ErrorCode,0,(PTSTR)&LocalAddress,0,NULL);  
	return (LPSTR)LocalAddress;  
}  


CStylePickerDlg::CStylePickerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStylePickerDlg::IDD, pParent)
	, m_hTestWnd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

#define RegStyle(_style)	m_stylePicker.AddStyle( L#_style, _style);

	RegStyle(WS_OVERLAPPED);
	RegStyle(WS_POPUP);
	RegStyle(WS_CHILD);
	RegStyle(WS_MINIMIZE);
	RegStyle(WS_VISIBLE);
	RegStyle(WS_DISABLED);
	RegStyle(WS_CLIPSIBLINGS);
	RegStyle(WS_CLIPCHILDREN);
	RegStyle(WS_MAXIMIZE);
	RegStyle(WS_CAPTION);
	RegStyle(WS_BORDER);
	RegStyle(WS_DLGFRAME);
	RegStyle(WS_VSCROLL);
	RegStyle(WS_HSCROLL);
	RegStyle(WS_SYSMENU);
	RegStyle(WS_THICKFRAME);
	RegStyle(WS_GROUP);
	RegStyle(WS_TABSTOP);
	RegStyle(WS_MINIMIZEBOX);
	RegStyle(WS_MAXIMIZEBOX);

#define RegFakeStyle(_style,_realstyle) m_stylePicker.AddFakeStyle(_style,_realstyle);

	RegFakeStyle(_T("WS_CAPTION"),_T("WS_BORDER"));
	RegFakeStyle(_T("WS_CAPTION"),_T("WS_DLGFRAME"));

	RegFakeStyle(_T("WS_TILED"),_T("WS_OVERLAPPED"));
	RegFakeStyle(_T("WS_ICONIC"),_T("WS_MINIMIZE"));
	RegFakeStyle(_T("WS_SIZEBOX"),_T("WS_THICKFRAME"));

	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_OVERLAPPED"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_BORDER"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_DLGFRAME"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_SYSMENU"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_THICKFRAME"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_MINIMIZEBOX"));
	RegFakeStyle(_T("WS_TILEDWINDOW"),_T("WS_MAXIMIZEBOX"));

	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_OVERLAPPED"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_BORDER"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_DLGFRAME"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_SYSMENU"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_THICKFRAME"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_MINIMIZEBOX"));
	RegFakeStyle(_T("WS_OVERLAPPEDWINDOW"),_T("WS_MAXIMIZEBOX"));

	RegFakeStyle(_T("WS_POPUPWINDOW"),_T("WS_POPUP"));
	RegFakeStyle(_T("WS_POPUPWINDOW"),_T("WS_BORDER"));
	RegFakeStyle(_T("WS_POPUPWINDOW"),_T("WS_SYSMENU"));

	RegFakeStyle(_T("WS_CHILDWINDOW"),_T("WS_CHILD"));

#define RegExStyle(_style)	m_exStylePicker.AddStyle( L#_style, _style);

	RegExStyle(WS_EX_ACCEPTFILES);
	RegExStyle(WS_EX_APPWINDOW);
	RegExStyle(WS_EX_CLIENTEDGE);
	RegExStyle(WS_EX_COMPOSITED);
	RegExStyle(WS_EX_CONTEXTHELP);
	RegExStyle(WS_EX_CONTROLPARENT);
	RegExStyle(WS_EX_DLGMODALFRAME);
	RegExStyle(WS_EX_LAYERED);
	RegExStyle(WS_EX_LAYOUTRTL);
	RegExStyle(WS_EX_LEFT);
	RegExStyle(WS_EX_LEFTSCROLLBAR);
	RegExStyle(WS_EX_LTRREADING);
	RegExStyle(WS_EX_MDICHILD);
	RegExStyle(WS_EX_NOACTIVATE);
	RegExStyle(WS_EX_NOINHERITLAYOUT);
	RegExStyle(WS_EX_NOPARENTNOTIFY);
	RegExStyle(WS_EX_NOREDIRECTIONBITMAP);
	RegExStyle(WS_EX_RIGHT);
	RegExStyle(WS_EX_RIGHTSCROLLBAR);
	RegExStyle(WS_EX_RTLREADING);
	RegExStyle(WS_EX_STATICEDGE);
	RegExStyle(WS_EX_TOOLWINDOW);
	RegExStyle(WS_EX_TOPMOST);
	RegExStyle(WS_EX_TRANSPARENT);
	RegExStyle(WS_EX_WINDOWEDGE);

#define RegFakeExStyle(_style,_realstyle) m_exStylePicker.AddFakeStyle(_style,_realstyle);

	RegFakeExStyle(_T("WS_EX_OVERLAPPEDWINDOW"),_T("WS_EX_WINDOWEDGE"));
	RegFakeExStyle(_T("WS_EX_OVERLAPPEDWINDOW"),_T("WS_EX_CLIENTEDGE"));
	RegFakeExStyle(_T("WS_EX_PALETTEWINDOW"),_T("WS_EX_WINDOWEDGE"));
	RegFakeExStyle(_T("WS_EX_PALETTEWINDOW"),_T("WS_EX_TOOLWINDOW"));
	RegFakeExStyle(_T("WS_EX_PALETTEWINDOW"),_T("WS_EX_TOPMOST"));
}

void CStylePickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Style, m_StyleListBox);
	DDX_Control(pDX, IDC_LIST_ExStyle, m_ExStyleListBox);
	DDX_Control(pDX, IDC_EDIT_Style, m_styleEdit);
	DDX_Control(pDX, IDC_EDIT_ExStyle, m_exStyleEdit);
	DDX_Control(pDX, IDC_LIST_FakeStyle, m_fakeStyleListBox);
	DDX_Control(pDX, IDC_LIST_FakeExStyle, m_fakeExStyleListBox);
}

BEGIN_MESSAGE_MAP(CStylePickerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_Style, &CStylePickerDlg::OnSelchangeListStyle)
	ON_LBN_SELCHANGE(IDC_LIST_FakeStyle, &CStylePickerDlg::OnSelchangeListFakestyle)
	ON_LBN_SELCHANGE(IDC_LIST_ExStyle, &CStylePickerDlg::OnSelchangeListExstyle)
	ON_LBN_SELCHANGE(IDC_LIST_FakeExStyle, &CStylePickerDlg::OnSelchangeListFakeexstyle)
	ON_EN_CHANGE(IDC_EDIT_Style, &CStylePickerDlg::OnEnChangeEditStyle)
	ON_EN_CHANGE(IDC_EDIT_ExStyle, &CStylePickerDlg::OnChangeEditExstyle)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CStylePickerDlg message handlers

BOOL CStylePickerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_statusBar.Create(this);
	static UINT indicators[] =
	{
		//ID_SEPARATOR, // status line indicator
		2508,
	};
	m_statusBar.SetIndicators(indicators,_countof(indicators));
	m_statusBar.SetPaneInfo(0,2508,SBPS_STRETCH,0);
	m_statusBar.SetPaneText(0,_T("Fine"));
	CRect rect;
	GetClientRect(rect);
	rect.top = rect.bottom - 20;
	m_statusBar.MoveWindow(rect);

	WNDCLASSEX wndClsEx;
	ZeroMemory(&wndClsEx,sizeof(wndClsEx));
	wndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClsEx.cbSize = sizeof(wndClsEx);
	wndClsEx.lpszClassName = _T("testWnd_StylePicker");
	wndClsEx.lpfnWndProc = MyWNDPROC;
	RegisterClassEx(&wndClsEx);
	DWORD dw = GetLastError();
	dw = dw;

	StyleList list;
	m_stylePicker.GetStyleList(list);
	for (auto& i:list)
	{
		m_StyleListBox.AddString(i);
	}
	list.clear();
	m_stylePicker.GetFakeStyleList(list);
	for (auto& i:list)
	{
		m_fakeStyleListBox.AddString(i);
	}
	
	list.clear();
	m_exStylePicker.GetStyleList(list);
	for (auto& i:list)
	{
		m_ExStyleListBox.AddString(i);
	}
	list.clear();
	m_exStylePicker.GetFakeStyleList(list);
	for (auto& i:list)
	{
		m_fakeExStyleListBox.AddString(i);
	}

	_OnStyleChanged();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStylePickerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStylePickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStylePickerDlg::OnSelchangeListStyle()
{
	std::list<CString> list;
	_GetSelStyleStringList(list);

	for (INT n=0; n<m_fakeStyleListBox.GetCount(); ++n)
	{
		m_fakeStyleListBox.SetSel(n,FALSE);
	}
	StyleList fakeList;
	m_stylePicker.GetFitFakeStyle(list,fakeList);
	for (auto& i:fakeList)
	{
		INT pos = m_fakeStyleListBox.FindString(-1,i);
		m_fakeStyleListBox.SetSel(pos,TRUE);
	}
	
	DWORD styleValue = m_stylePicker.GetStyleValue(list);
	CString styleValueString;
	styleValueString.Format(_T("%X"),styleValue);
	m_changingString = styleValueString;
	m_styleEdit.SetWindowText(styleValueString);
}

#include <set>

void CStylePickerDlg::OnSelchangeListFakestyle()
{
	static std::set<CString> fakeStyleSelectSet;

	std::list<CString> list;
	_GetSelFakeStyleStringList(list);

	for (auto& i:list)
	{
		StyleList styleList;
		m_stylePicker.GetStyleByFakeStyle(i,styleList);
		for (auto& style:styleList)
		{
			INT pos = m_StyleListBox.FindString(-1,style);
			m_StyleListBox.SetSel(pos,TRUE);
		}
	}

	list.clear();
	_GetSelStyleStringList(list);
	DWORD styleValue = m_stylePicker.GetStyleValue(list);
	CString styleValueString;
	styleValueString.Format(_T("%X"),styleValue);
	m_styleEdit.SetWindowText(styleValueString);
}


void CStylePickerDlg::OnSelchangeListExstyle()
{
	std::list<CString> list;
	_GetSelExStyleStringList(list);

	for (INT n=0; n<m_fakeExStyleListBox.GetCount(); ++n)
	{
		m_fakeExStyleListBox.SetSel(n,FALSE);
	}
	StyleList fakeList;
	m_exStylePicker.GetFitFakeStyle(list,fakeList);
	for (auto& i:fakeList)
	{
		INT pos = m_fakeExStyleListBox.FindString(-1,i);
		m_fakeExStyleListBox.SetSel(pos,TRUE);
	}

	DWORD styleValue = m_exStylePicker.GetStyleValue(list);
	CString styleValueString;
	styleValueString.Format(_T("%X"),styleValue);
	m_changingString = styleValueString;
	m_exStyleEdit.SetWindowText(styleValueString);
}


void CStylePickerDlg::OnSelchangeListFakeexstyle()
{
	static std::set<CString> fakeStyleSelectSet;

	std::list<CString> list;
	_GetSelFakeExStyleStringList(list);

	for (auto& i:list)
	{
		StyleList styleList;
		m_exStylePicker.GetStyleByFakeStyle(i,styleList);
		for (auto& style:styleList)
		{
			INT pos = m_ExStyleListBox.FindString(-1,style);
			m_ExStyleListBox.SetSel(pos,TRUE);
		}
	}

	list.clear();
	_GetSelExStyleStringList(list);
	DWORD styleValue = m_exStylePicker.GetStyleValue(list);
	CString styleValueString;
	styleValueString.Format(_T("%X"),styleValue);
	m_exStyleEdit.SetWindowText(styleValueString);
}

void CStylePickerDlg::_GetSelStyleStringList(std::list<CString>& list)
{
	int nCount = m_StyleListBox.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	m_StyleListBox.GetSelItems(nCount, aryListBoxSel.GetData());
	for (int n=0; n<aryListBoxSel.GetCount(); ++n)
	{
		CString text;
		m_StyleListBox.GetText(aryListBoxSel.GetAt(n),text.GetBuffer(MAX_PATH));
		text.ReleaseBuffer();
		list.push_back(text);
	}
}

void CStylePickerDlg::_GetSelFakeStyleStringList( std::list<CString>& list )
{
	int nCount = m_fakeStyleListBox.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	m_fakeStyleListBox.GetSelItems(nCount, aryListBoxSel.GetData());
	for (int n=0; n<aryListBoxSel.GetCount(); ++n)
	{
		CString text;
		m_fakeStyleListBox.GetText(aryListBoxSel.GetAt(n),text.GetBuffer(MAX_PATH));
		text.ReleaseBuffer();
		list.push_back(text);
	}
}

void CStylePickerDlg::_GetSelExStyleStringList( std::list<CString>& list )
{
	int nCount = m_ExStyleListBox.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	m_ExStyleListBox.GetSelItems(nCount, aryListBoxSel.GetData());
	for (int n=0; n<aryListBoxSel.GetCount(); ++n)
	{
		CString text;
		m_ExStyleListBox.GetText(aryListBoxSel.GetAt(n),text.GetBuffer(MAX_PATH));
		text.ReleaseBuffer();
		list.push_back(text);
	}
}

void CStylePickerDlg::_GetSelFakeExStyleStringList( std::list<CString>& list )
{
	int nCount = m_fakeExStyleListBox.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	m_fakeExStyleListBox.GetSelItems(nCount, aryListBoxSel.GetData());
	for (int n=0; n<aryListBoxSel.GetCount(); ++n)
	{
		CString text;
		m_fakeExStyleListBox.GetText(aryListBoxSel.GetAt(n),text.GetBuffer(MAX_PATH));
		text.ReleaseBuffer();
		list.push_back(text);
	}
}


void CStylePickerDlg::OnEnChangeEditStyle()
{
	_OnStyleChanged();
}


void CStylePickerDlg::OnChangeEditExstyle()
{
	_OnStyleChanged();
}


BOOL CStylePickerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYFIRST)
	{
		if ((pMsg->wParam == VK_RETURN) )
		{
			int id = GetFocus()->GetDlgCtrlID();
			if (id == IDC_EDIT_Style)
			{
				_OnEnterStyleValue();
			}
			else if (id == IDC_EDIT_ExStyle)
			{
				_OnEnterExStyleValue();
			}
			return(TRUE);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

VOID CStylePickerDlg::_OnEnterStyleValue()
{
	CString strStyle;
	m_styleEdit.GetWindowText(strStyle);
	if (strStyle == m_changingString)
	{
		return;
	}
	m_changingString.Empty();
	DWORD dwValue=0;
	_stscanf_s(strStyle,_T("%X"),&dwValue);
	StyleList list;
	m_stylePicker.GetStyleByValue(dwValue,list);

	for (INT n=0; n<m_StyleListBox.GetCount(); ++n)
	{
		m_StyleListBox.SetSel(n,FALSE);
	}
	for (auto& i:list)
	{
		INT pos = m_StyleListBox.FindString(-1,i);
		m_StyleListBox.SetSel(pos,TRUE);
	}
	OnSelchangeListStyle();
}

VOID CStylePickerDlg::_OnEnterExStyleValue()
{
	CString strStyle;
	m_exStyleEdit.GetWindowText(strStyle);
	if (strStyle == m_changingString)
	{
		return;
	}
	m_changingString.Empty();
	DWORD dwValue=0;
	_stscanf_s(strStyle,_T("%X"),&dwValue);
	StyleList list;
	m_exStylePicker.GetStyleByValue(dwValue,list);

	for (INT n=0; n<m_ExStyleListBox.GetCount(); ++n)
	{
		m_ExStyleListBox.SetSel(n,FALSE);
	}
	for (auto& i:list)
	{
		INT pos = m_ExStyleListBox.FindString(-1,i);
		m_ExStyleListBox.SetSel(pos,TRUE);
	}
	OnSelchangeListExstyle();
}

VOID CStylePickerDlg::_OnStyleChanged()
{
	DWORD style;
	StyleList list;
	_GetSelStyleStringList(list);
	style = m_stylePicker.GetStyleValue(list);

	DWORD exStyle;
	list.clear();
	_GetSelExStyleStringList(list);
	exStyle = m_exStylePicker.GetStyleValue(list);

	if (m_hTestWnd)
	{
		::DestroyWindow(m_hTestWnd);
		m_hTestWnd = 0;
	}

	CRect rect;
	_CalculateTestWndPos(rect);

	HWND hParent=0;
// 	if (style & WS_CHILD)
// 	{
// 		hParent = m_hWnd;
// 	}

	m_hTestWnd = CreateWindowEx(exStyle,_T("testWnd_StylePicker"),_T(""),style,rect.left,rect.top,rect.Width(),rect.Height(),hParent,0,GetModuleHandle(nullptr),0);
	if (m_hTestWnd)
	{
		::ShowWindow(m_hTestWnd,SW_SHOW);
		DWORD dwStyle=0;
		dwStyle = GetWindowLong(m_hTestWnd,GWL_STYLE);
		dwStyle = style;
		SetWindowLong(m_hTestWnd,GWL_STYLE,dwStyle);
 		m_statusBar.SetPaneText(0,_T("Fine"));
	}
	else
	{
		DWORD dw = GetLastError();
		LPSTR errorDesc = ConvertErrorCodeToString(dw);
		m_statusBar.SetPaneText(0,CString((LPTSTR)errorDesc));
		LocalFree(errorDesc);
	}
}

VOID CStylePickerDlg::_CalculateTestWndPos( CRect& rect )
{
	GetWindowRect(rect);
	rect.OffsetRect(rect.Width(),0);
}


void CStylePickerDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	CRect rect;
	_CalculateTestWndPos(rect);
	if (m_hTestWnd)
	{
		::SetWindowPos(m_hTestWnd,0,rect.left,rect.top,rect.Width(),rect.Height(),SWP_NOACTIVATE);
	}
}
