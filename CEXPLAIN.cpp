// CEXPLAIN.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CEXPLAIN.h"


// CEXPLAIN 대화 상자

IMPLEMENT_DYNAMIC(CExplainDlg, CDialogEx)

CExplainDlg::CExplainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPLAIN, pParent)
{

}

CExplainDlg::~CExplainDlg()
{
}

void CExplainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExplainDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEXPLAIN 메시지 처리기

BOOL CExplainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_imgBg.Load(L"res/image/EscapeexplainPage.bmp");

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;
}
void CExplainDlg::OnPaint()
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