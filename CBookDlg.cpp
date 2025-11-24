// CBookDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CBookDlg.h"


// CBookDlg 대화 상자

IMPLEMENT_DYNAMIC(CBookDlg, CDialogEx)

CBookDlg::CBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
	, m_nBookType(0)
{

}

CBookDlg::~CBookDlg()
{
}

void CBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBookDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBookDlg 메시지 처리기

BOOL CBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_imgFBook.Load(L"res/image/EscapeBook.bmp");
	m_imgWBook.Load(L"res/image/EscapeBookFake.bmp");

	if (m_nBookType == 0)
		m_pBookImage = &m_imgFBook;
	else
		m_pBookImage = &m_imgWBook;

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBookDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_pBookImage && !m_pBookImage->IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_pBookImage->Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}
}