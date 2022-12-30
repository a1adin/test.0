////////////////////////////////////////////////////////////////////////////////////
//
//			www.interestprograms.ru - ���������, ���� � �� �������� ����
//
/////////////////////////////////////////////////////////////////////////////////////

// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ClockMFC.h"
#include "ChildView.h"
#include <math.h>
#include ".\childview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}



// ������� ��������� ���������
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CChildView message handlers

// ���������� ��������������� ����� ��������� ���� CChildView.
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		// ����� ���� ������ �������, ����� �� ���� �������� ������.
		::LoadCursor(NULL, IDC_ARROW), NULL/*reinterpret_cast<HBRUSH>(COLOR_WINDOW+1)*/, NULL);

	return TRUE;
}

// ������� ��������� � ���� ���� CChildView.
void CChildView::OnPaint() 
{
	// �������� �������� ���������� ��� ��������� �� �������
	// � �������� ���� CChildView.
	CPaintDC dc(this); // device context for painting
	
	
	// ��� ���������� �������� ������� �������� ������� ������ (��������)
	// � ������ ����������, ����� �������� BitBlt() ��������� ��������� � �������� ����������,
	// ������������� ���� ���� CChildView.

	// �������� �������� ���������� � ������, ����������� � ������� ���������� (dc).
	CDC dcMemory;
    dcMemory.CreateCompatibleDC(&dc);

	// ������� ������� ���������� ������� ���� CChildView.
	CRect rc;
	GetClientRect(&rc);


	// �������� ������� ������ ����������� � ���������� ��������� ���������� ���� ���� CChildView(dc).
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

    // ������� ��������� ������� ������ � �������� ���������� ����������� � ������,
	// �������� ������ ������� ������ ��� ����������� � ������� ����������.
    CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

	// ������ ����� ��� ������ ���� ���� ������ �����.
	CBrush brush(RGB(240, 240, 240));
	CBrush* pDefaultBrush = dcMemory.SelectObject(&brush);
 
	// �������� ������������� �� ��� ������� ���� ���� CChildView
	dcMemory.Rectangle(-1, -1, rc.Width() + 2, rc.Height() + 2);

	
    // �������� ������ ���������� ����� ����� �����,
	int radius;
	// ����� ������ ������ ������ ������ ��� ���� ������ ������ ����,
	// ���� ������ ������ ������, ������ ��� ���� ������ ������.
	if(rc.Width() > rc.Height())
		radius = rc.Height()/2 - rc.Height()/8;
	else
		radius = rc.Width()/2 - rc.Width()/8;

	
	// ������ ���������.
	DrawDial(&dcMemory, rc.Width()/2, rc.Height()/2, radius);
	// ������ �������.
	DrawArrow(&dcMemory, rc.Width()/2, rc.Height()/2, radius);


	// ���������, ������� �������� �� ������ � �������� ���� (dc).
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &dcMemory, 
         0, 0, SRCCOPY);

	// ���������� ������� ��������� (�� ���������).
	dcMemory.SelectObject(pDefaultBrush);
    dcMemory.SelectObject(pOldBitmap);   
	
	
	// Do not call CWnd::OnPaint() for painting messages
}


// ������ ��������� (�����, �����, �������).
// ��� ���������� ������������� ���������� GDI, 
// �������������� ����� ���������� ���� �� ����� ��������� ��������.
void CChildView::DrawDial(CDC* pDC, int x, int y, int radius)
{
	CRect rc;
	GetClientRect(&rc);

	// ������ ����� ��� "���������" ����� ����������.
	{ 
		// ������� ���� ������ �����, ���� ������ ��� ���� ����������,
		// ��� ����������� ��������� ���������.
		CPen pen(0, 1, RGB(200, 200, 200));
		// ��������� ��������� ���� ������� � ������������ ���������� ���� �� ���������.
		CPen* pDefaultPen = pDC->SelectObject(&pen);

		// ������� ����� ��� �������� ����������.
		CBrush brush(RGB(240, 240, 230));
		// ��������� ��������� ����� ������� � ��������� ���������� ������� ��� ����������� ���� CChildView,
		// ��� �������� � ���������� �� ���������, ���������� ������ �����.
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);

		// ������ ���� ����������, ��������� ��������� ���� � �����.
		// ���� ������ ������������� � ������ ���� � ������������� � ����������� ������������ � �����
		pDC->Ellipse(rc.Width()/2 - radius, rc.Height()/2 - radius, rc.Width()/2 + radius, rc.Height()/2+radius);
		
		// ���������� � �������� ������� ��������� ����� � ����.
		pDC->SelectObject(pDefaultBrush);
		pDC->SelectObject(pDefaultPen);
	}


	// ����� ������� �� ����������.
	{
		// ��� �������� ������ ����������.
		pDC->SetBkMode(TRANSPARENT);

		// ������� ����� ��� �������� �� ���������� (��� ������ - Times New Roman),
		// ������ ������ �������������� ������� ����������.
		CFont font;
		font.CreatePointFont((int)(radius*0.8), "Times New Roman");
		CFont* pDefaultFont = pDC->SelectObject(&font);

		// ����� ��� �������, ������ � ����� ����������,
		// ������� �������� � ��������� �������� ����������� ������� �����.
		int correct = radius/4;
		pDC->DrawText("\"����\"", CRect(x - correct, y - correct*2, x + correct, y), DT_CENTER);
		pDC->DrawText("���������", CRect(x - (int)(correct*1.5), y + correct*2, x + (int)(correct*1.5), y + correct*3), DT_CENTER);
		
		// ���������� ��������� ������ �� ���������.
		pDC->SelectObject(pDefaultFont);
	}
	

	
	// ������ ������ ������� �� ����� - 60 ����,
	// �� 6 �������� �� ���� �������.
	// ������ ����� � ��������� �������� ����������� ������� �����.
	for(int i = 0; i < 360; i+= 6)
	{
		// ������� ��������� ����� �� 90 �����, ����� ������ ����
		// ����� ������ ����������.
		float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
		float pos_x = radius*cos(rad) + x;
		float pos_y = radius*sin(rad) + y;
		int correct = radius/70;
		pDC->Ellipse((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
	}
	

	// ������ ����� � ������� ������� �� ����� - 12 ����,
	// �� 30 �������� �� ���� �������.
	{
		// ������� ����� ��� �������� �� ���������� (��� ������ - Arial Black),
		// ������ ������ �������������� ������� ����������.
		CFont font;
		font.CreatePointFont((int)(radius*1.6), "Arial Black");
		CFont* pDefaultFont = pDC->SelectObject(&font);

		// ����������� �������� ����������� ����
		CPen pen(0, 2, RGB(0,0,0));
		CPen* pDefaultPen = pDC->SelectObject(&pen);

		// ������� ����� ����� ������ �����
		CBrush brush(RGB(0,255,255));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		
		// ������ �� ����� ���������� 12 ������� �����,
		// ��������� �������� ����������� ������� �����.
		for(int i = 0; i < 360; i+= 30)
		{
			// ������� ����� ����������� �� ����� ����� 30 ��������,
			// ������� ����� ����� �� 90 ��������, ����� "12" ���� ����� ������ ����������
			float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
			float pos_x = radius*cos(rad) + x;
			float pos_y = radius*sin(rad) + y;
			
			// ��������� ��������, ��������� ��������� ����������� ����������������� �����.
			int correct;
			if(radius > 200)
				correct = radius/30;
			else
				correct = 5;
			pDC->Ellipse((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
			

			// ����� ����� �� ���������� ����������,
			// ��������� ���� �������������� ��������������� ��������� ������� ����������
			pos_x = (radius + radius/4)*cos(rad) + x;
			pos_y = (radius + radius/4)*sin(rad) + y;
			
			CRect rc;
			correct = radius/7;
			rc.SetRect((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
			CString s;
			// ������ ����� "12", � �� "0",
			// ����� ��� �� ������� (1-2-3-4-...).
			if(i == 0)
				s.Format("%d", 12);
			else
				s.Format("%d", i/30);
			// ��������������� ������ ����� ����������
			pDC->DrawText(s, &rc, DT_CENTER|DT_SINGLELINE|DT_VCENTER);

		}

		// ������� �������� �� ���������.
		pDC->SelectObject(pDefaultBrush);
		pDC->SelectObject(pDefaultFont);
		pDC->SelectObject(pDefaultPen);
	}

	


}


// ����������� ��������� � ������ ������� �� ����������,
// �������, ���������, ��������, �������.
void CChildView::DrawArrow(CDC* pDC, int x, int y, int radius)
{
	// ��������� ��������� �������.
	CTime t = CTime::GetCurrentTime();
	int m_Second = t.GetSecond() * 6;
	int m_Minute = t.GetMinute() * 6 + t.GetSecond()/10/*���� �� 0 �� 6 ��������*/;
	int m_Hour = t.GetHour() * 30 + t.GetMinute()/2/*���� �� 0 �� 30 �������� */;

	
	// ������� ���� ��� ���������� �������.
	CPen pen(0, 1, RGB(0,0,0));
	CPen* pDefaultPen = pDC->SelectObject(&pen);

	// ��� ������� ������ �������� ������� ��������� ��������� Polygon().

	// ����� ������ ������� �������, �� ������ ������.
	{	
		int radius1 = radius/1.2;
		int i = m_Hour;
		float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
		float pos_x = (-radius1/9)*cos(rad) + x;
		float pos_y = (-radius1/9)*sin(rad) + y;
		
		CRect rc;
		int correct = radius/10;
		POINT pt[4];
		pt[0].x = (LONG)pos_x;
		pt[0].y = (LONG)pos_y;
		pos_x = (-radius1/10)*cos(rad+0.8f) + x;
		pos_y = (-radius1/10)*sin(rad+0.8f) + y;
		pt[1].x = (LONG)pos_x;
		pt[1].y = (LONG)pos_y;
		pos_x = radius1*cos(rad) + x;
		pos_y = radius1*sin(rad) + y;
		pt[2].x = (LONG)pos_x;
		pt[2].y = (LONG)pos_y;
		pos_x = (-radius1/10)*cos(rad-0.8f) + x;
		pos_y = (-radius1/10)*sin(rad-0.8f) + y;
		pt[3].x = (LONG)pos_x;
		pt[3].y = (LONG)pos_y;
		CBrush brush(RGB(0,220,150));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		pDC->Polygon(pt, 4);
		pDC->SelectObject(pDefaultBrush);
		
	}

	// ������, � Z-���������, ������ �������� �������.
	{	
		int i = m_Minute;
		float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
		float pos_x = (-radius/9)*cos(rad) + x;
		float pos_y = (-radius/9)*sin(rad) + y;
		
		CRect rc;
		rc.SetRect(pos_x-20, pos_y-20, pos_x+20, pos_y+20);
		POINT pt[4];
		pt[0].x = (LONG)pos_x;
		pt[0].y = (LONG)pos_y;
		pos_x = (float)((-radius/10)*cos(rad+0.6) + x);
		pos_y = (float)((-radius/10)*sin(rad+0.6) + y);
		pt[1].x = (LONG)pos_x;
		pt[1].y = (LONG)pos_y;
		pos_x = radius*cos(rad) + x;
		pos_y = radius*sin(rad) + y;
		pt[2].x = (LONG)pos_x;
		pt[2].y = (LONG)pos_y;
		pos_x = (float)((-radius/10)*cos(rad-0.5) + x);
		pos_y = (float)((-radius/10)*sin(rad-0.5) + y);
		pt[3].x = (LONG)pos_x;
		pt[3].y = (LONG)pos_y;
		CBrush brush(RGB(0,220,150));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		pDC->Polygon(pt, 4);
		pDC->SelectObject(pDefaultBrush);
	}

	// ����� ������� ������ ��������� �������.
	{   int i = m_Second;
		float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
		float pos_x = (-radius/10)*cos(rad) + x;
		float pos_y = (-radius/10)*sin(rad) + y;
		
		CRect rc;
		rc.SetRect(pos_x-20, pos_y-20, pos_x+20, pos_y+20);
		POINT pt[4];
		pt[0].x = (LONG)pos_x;
		pt[0].y = (LONG)pos_y;
		pos_x = (float)((-radius/10)*cos(rad+0.2) + x);
		pos_y = (float)((-radius/10)*sin(rad+0.2) + y);
		pt[1].x = (LONG)pos_x;
		pt[1].y = (LONG)pos_y;
		pos_x = radius*cos(rad) + x;
		pos_y = radius*sin(rad) + y;
		pt[2].x = (LONG)pos_x;
		pt[2].y = (LONG)pos_y;
		pos_x = (float)((-radius/10)*cos(rad-0.2) + x);
		pos_y = (float)((-radius/10)*sin(rad-0.2) + y);
		pt[3].x = (LONG)pos_x;
		pt[3].y = (LONG)pos_y;

		// ������� ����� �������.
		CBrush brush(RGB(255,0,0));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		pDC->Polygon(pt, 4);
		pDC->SelectObject(pDefaultBrush);
	}


	// ������ ������ ������� ��� �� ������� ��������� ��� �������.
	int correct = radius/20;
	pDC->Ellipse(x - correct, y - correct, x + correct, y + correct);
	
	// ������� � ���������� �� ���������.
	pDC->SelectObject(pDefaultPen);
	
}

// ������ ����� ������ ��� ����������� ������� OnPaint(), ��� ����������� ����
// � ����� ��� � ��� ���������.
void CChildView::OnTimer(UINT nIDEvent)
{

	Invalidate();
	
	CWnd::OnTimer(nIDEvent);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ��������� ������ � �������������� 100 ��
	SetTimer(10, 100, NULL);

	return 0;
}


// ������� �������� �������� ����� ��� �������������� 
// ���� �� ���� ����� � ������� � �������� ������.
void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int width_screen  = GetSystemMetrics(SM_CXSCREEN);
	int height_screen = GetSystemMetrics(SM_CYSCREEN);

	static bool fullscreen = 0;

	static WINDOWPLACEMENT wp;
	if(fullscreen == false)
	{
		AfxGetMainWnd()->GetWindowPlacement(&wp);
		AfxGetMainWnd()->ModifyStyle(WS_OVERLAPPEDWINDOW, 0);
		AfxGetMainWnd()->SetWindowPos(&wndTopMost, 0, 0, width_screen, height_screen, 0);
		fullscreen = true;
	}
	else
	{
		AfxGetMainWnd()->ModifyStyle(0, WS_OVERLAPPEDWINDOW);
		AfxGetMainWnd()->SetWindowPos(&wndNoTopMost, width_screen/2 - 640/2, height_screen/2 - 480/2, 640, 480, 0);
		
		// ���� ����� ����� ������� �� ������ ����� ���������� ���� � ����������� ����,
		// ���������� ��� � ���������� ��������� (����� ������������ ����� ����������� �������� ������� ����),
		// ���� �� ���� � ����������� ���� ��� ������� ���� �� �������� �� ������ ����������.
		wp.showCmd = SW_SHOWNORMAL;
		AfxGetMainWnd()->SetWindowPlacement(&wp);


		fullscreen = false;
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
