// CStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CStartDlg.h"
#include "EscapeDlg.h"
#include "CEXPLAIN.h"


// CStartDlg 대화 상자

IMPLEMENT_DYNAMIC(CStartDlg, CDialogEx)

CStartDlg::CStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_START, pParent)
{

}

CStartDlg::~CStartDlg()
{
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CStartDlg 메시지 처리기

BOOL CStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_imgBg.Load(L"res/image/EscapeStartPage.bmp");

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStartDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 DC

	if (!m_imgBg.IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_imgBg.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


void CStartDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 시작 버튼 영역
	CRect startButtonRect(345, 264, 746, 360);
	// 게임 설명 버튼 영역
	CRect gameDescRect(342, 384, 742, 474);

	if (startButtonRect.PtInRect(point))
	{
		CEscapeDlg dlg; 
		dlg.DoModal();
	}
	else if (gameDescRect.PtInRect(point))
	{
		CExplainDlg dlg;
		dlg.DoModal();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}