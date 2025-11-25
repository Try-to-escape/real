#pragma once
#include "afxdialogex.h"
#include "CFailDlg.h"


// CLockerDlg 대화 상자

class CLockerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLockerDlg)

public:
	CLockerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLockerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOCKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnCancel();
	virtual void OnOK();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//컨트롤 변수
	CButton m_btnLocker0;
	CButton m_btnLocker1;
	CButton m_btnLocker2;
	CButton m_btnLocker3;
	CButton m_btnLocker4;
	CButton m_btnLocker5;
	CButton m_btnLocker6;
	CButton m_btnLocker7;
	CButton m_btnLocker8;
	CButton m_btnLocker9;
	CEdit m_editLockerInput;
	CButton m_btnTakeTestpaper;
	CButton m_btnTakeGold;
	//사용자 변수
	CImage* m_pCurrentImage;
	CImage m_imgLocker;
	CImage m_imgLockerOpen;
	CImage m_imgTestPaper;
	afx_msg void OnBnClickedButtonLocker(UINT nID);
	CString m_strPassword;
	afx_msg void OnBnClickedButtonTakeTestpaper();
	afx_msg void OnLockerButton();
	afx_msg void OnBnClickedButtonTakeGold();
	bool m_bSuccess;
};
