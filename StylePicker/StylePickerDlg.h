
// StylePickerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "StylePickerClass.h"


// CStylePickerDlg dialog
class CStylePickerDlg : public CDialogEx
{
// Construction
public:
	CStylePickerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STYLEPICKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void _GetSelStyleStringList(std::list<CString>& list);
	void _GetSelFakeStyleStringList(std::list<CString>& list);
	void _GetSelExStyleStringList(std::list<CString>& list);
	void _GetSelFakeExStyleStringList(std::list<CString>& list);

	VOID _OnEnterStyleValue();
	VOID _OnEnterExStyleValue();
	VOID _OnStyleChanged();
	VOID _CalculateTestWndPos(CRect& rect);
public:
	CListBox m_StyleListBox;
	CListBox m_fakeStyleListBox;
	CListBox m_ExStyleListBox;
	CListBox m_fakeExStyleListBox;
	CEdit m_styleEdit;
	CEdit m_exStyleEdit;
	CStylePicker m_stylePicker;
	CStylePicker m_exStylePicker;
	CString m_changingString;
	HWND m_hTestWnd;
	CStatusBar m_statusBar;
	afx_msg void OnEnChangeEditStyle();
	afx_msg void OnSelchangeListStyle();
	afx_msg void OnSelchangeListFakestyle();
	afx_msg void OnSelchangeListExstyle();
	afx_msg void OnSelchangeListFakeexstyle();
	afx_msg void OnChangeEditExstyle();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMove(int x, int y);
};
