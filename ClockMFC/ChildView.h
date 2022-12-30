////////////////////////////////////////////////////////////////////////////////////
//
//			www.interestprograms.ru - программы, игры и их исходные коды
//
/////////////////////////////////////////////////////////////////////////////////////

// ChildView.h : interface of the CChildView class
//

#pragma once


// CChildView window
// Класс окна вида приложения,
// функции: отображение и обработка графической информации приложения
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
	// Пользовательские функции

	// Высчитывает размеры и положение циферблата,
	// рисует метки, цифры, надписи.
	void DrawDial(CDC* pDC, int x, int y, int radius);

	// Высчитывает положение и рисует стрелки на циферблате,
	// стрелки, секундную, минутную, часовую.
	void DrawArrow(CDC* pDC, int x, int y, int radius);


};

