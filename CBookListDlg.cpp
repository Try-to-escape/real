// CBookListDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CBookListDlg.h"


// CBookListDlg 대화 상자

IMPLEMENT_DYNAMIC(CBookListDlg, CDialogEx)

CBookListDlg::CBookListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOKLIST, pParent)
{

}

CBookListDlg::~CBookListDlg()
{
}

void CBookListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FBOOK, m_btnFBook);
	DDX_Control(pDX, IDC_BUTTON_WBOOK, m_btnWBook);
}


BEGIN_MESSAGE_MAP(CBookListDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FBOOK, &CBookListDlg::OnClickedButtonFbook)
	ON_BN_CLICKED(IDC_BUTTON_WBOOK, &CBookListDlg::OnClickedButtonWbook)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CBookListDlg 메시지 처리기

void CBookListDlg::OnClickedButtonFbook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CBookDlg dlg;
	dlg.m_nBookType = 0;
	dlg.DoModal();
}

void CBookListDlg::OnClickedButtonWbook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CBookDlg dlg;
	dlg.m_nBookType = 1;
	dlg.DoModal();
}

BOOL CBookListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_imgBg.Load(L"res/image/EscapeBookList.bmp");

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	m_btnFBook.EnableWindowsTheming(FALSE);
	m_btnFBook.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_btnFBook.m_bTransparent = TRUE;
	m_btnFBook.m_bDrawFocus = FALSE;
	m_btnFBook.SetMouseCursorHand();

	m_btnWBook.EnableWindowsTheming(FALSE);
	m_btnWBook.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_btnWBook.m_bTransparent = TRUE;
	m_btnWBook.m_bDrawFocus = FALSE;
	m_btnWBook.SetMouseCursorHand();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBookListDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (!m_imgBg.IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_imgBg.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}
}

void CBookListDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDCtl == IDC_BUTTON_FBOOK || nIDCtl == IDC_BUTTON_WBOOK)
	{
		return;
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CBookListDlg::OnCancel()
{
	DestroyWindow();  
}

void CBookListDlg::OnOK()
{
	DestroyWindow();  
}

void CBookListDlg::PostNcDestroy()
{
	delete this;  
}