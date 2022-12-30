////////////////////////////////////////////////////////////////////////////////////
//
//			www.interestprograms.ru - ���������, ���� � �� �������� ����
//
/////////////////////////////////////////////////////////////////////////////////////

// ChildView.h : interface of the CChildView class
//

#pragma once


// CChildView window
// ����� ���� ���� ����������,
// �������: ����������� � ��������� ����������� ���������� ����������
class CChildView : public CWnd
{
// Construction
public:
	CChildView();


// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);


	//////////////////////////////////////////////////////////////////////////////
	// ���������������� �������

	// ����������� ������� � ��������� ����������,
	// ������ �����, �����, �������.
	void DrawDial(CDC* pDC, int x, int y, int radius);

	// ����������� ��������� � ������ ������� �� ����������,
	// �������, ���������, ��������, �������.
	void DrawArrow(CDC* pDC, int x, int y, int radius);


};

