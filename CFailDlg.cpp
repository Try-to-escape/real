// CFailDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CFailDlg.h"
#include "CStartDlg.h"


// CFailDlg 대화 상자

IMPLEMENT_DYNAMIC(CFailDlg, CDialogEx)

CFailDlg::CFailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FAIL_DIALOG, pParent)
{

}

CFailDlg::~CFailDlg()
{
}

void CFailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFailDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RETRY_BUTTON, &CFailDlg::OnClickedRetryButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CFailDlg::OnClickedExitButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFailDlg 메시지 처리기

BOOL CFailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bmpFailImage.Load(L"res/image/EscapeFail.bmp");

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFailDlg::OnClickedRetryButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pMain = AfxGetMainWnd();
	if (pMain && pMain != this) {
		pMain->PostMessageW(WM_CLOSE);
	}
	EndDialog(IDOK);
	CStartDlg startDlg;
	startDlg.DoModal();
}

void CFailDlg::OnClickedExitButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 종료 버튼 : F받기 누르면 프로그램 종료
	::PostQuitMessage(0);
}

void CFailDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_bmpFailImage.IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_bmpFailImage.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}
}
