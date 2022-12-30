////////////////////////////////////////////////////////////////////////////////////
//
//			www.interestprograms.ru - программы, игры и их исходные коды
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



// Макросы обработки сообщений
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CChildView message handlers

// Вызывается непосредственно перед созданием окна CChildView.
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		// Кисть окна делаем нулевой, чтобы не было мерцания экрана.
		::LoadCursor(NULL, IDC_ARROW), NULL/*reinterpret_cast<HBRUSH>(COLOR_WINDOW+1)*/, NULL);

	return TRUE;
}

// Функция рисования в окне вида CChildView.
void CChildView::OnPaint() 
{
	// Получаем контекст устройства для рисования на дисплее
	// в пределах окна CChildView.
	CPaintDC dc(this); // device context for painting
	
	
	// Для устранения мерцания сначала создадим битовый массив (картинку)
	// в памяти компьютера, затем функцией BitBlt() мгновенно скопируем в контекст устройства,
	// принадлежащий окну вида CChildView.

	// Создадим контекст устройства в памяти, совместимый с рабочим контекстом (dc).
	CDC dcMemory;
    dcMemory.CreateCompatibleDC(&dc);

	// Получим размеры клиентской области окна CChildView.
	CRect rc;
	GetClientRect(&rc);


	// Создадим битовый массив совместимый с полученным контестом устройства окна вида CChildView(dc).
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

    // Выберем созданный битовый массив в контекст устройства находящийся в памяти,
	// запомним старый битовый массив для возвращения к прежним настройкам.
    CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

	// Создим кисть для общего фона окна серого цвета.
	CBrush brush(RGB(240, 240, 240));
	CBrush* pDefaultBrush = dcMemory.SelectObject(&brush);
 
	// Нарисуем прямоугольник на всю площадь окна вида CChildView
	dcMemory.Rectangle(-1, -1, rc.Width() + 2, rc.Height() + 2);

	
    // Вычислим радиус циферблата часов такой чтобы,
	int radius;
	// когда ширина больше высоты радиус был чуть меньше высоты окна,
	// если высота больше ширины, радиус был чуть меньше ширины.
	if(rc.Width() > rc.Height())
		radius = rc.Height()/2 - rc.Height()/8;
	else
		radius = rc.Width()/2 - rc.Width()/8;

	
	// Рисуем циферблат.
	DrawDial(&dcMemory, rc.Width()/2, rc.Height()/2, radius);
	// Рисуем стрелки.
	DrawArrow(&dcMemory, rc.Width()/2, rc.Height()/2, radius);


	// Мгновенно, блоками копируем из памяти в контекст окна (dc).
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &dcMemory, 
         0, 0, SRCCOPY);

	// Возвращаем прежние настройки (по умолчанию).
	dcMemory.SelectObject(pDefaultBrush);
    dcMemory.SelectObject(pOldBitmap);   
	
	
	// Do not call CWnd::OnPaint() for painting messages
}


// Рисует циферблат (метки, цифры, надписи).
// Для наглядного использования переменных GDI, 
// функциональные блоки отделяются друг от друга фигурными скобками.
void CChildView::DrawDial(CDC* pDC, int x, int y, int radius)
{
	CRect rc;
	GetClientRect(&rc);

	// Рисуем серый фон "бумажного" круга циферблата.
	{ 
		// Создаем перо серого цвета, чуть темнее чем круг циферблата,
		// для обеспечения видимости окантовки.
		CPen pen(0, 1, RGB(200, 200, 200));
		// Назначаем созданное перо текущим и одновременно запоминаем перо по умолчанию.
		CPen* pDefaultPen = pDC->SelectObject(&pen);

		// Создаем кисть для закраски циферблата.
		CBrush brush(RGB(240, 240, 230));
		// Назначаем созданную кисть текущей в контексте устройства дисплея для отображения окна CChildView,
		// для возврата к установкам по умолчанию, запоминаем старую кисть.
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);

		// Рисуем круг циферблата, используя созданные перо и кисть.
		// Круг всегда располагается в центре окна и увеличивается и уменьшается одновременно с окном
		pDC->Ellipse(rc.Width()/2 - radius, rc.Height()/2 - radius, rc.Width()/2 + radius, rc.Height()/2+radius);
		
		// Возвращаем в контекст прежние настройки кисти и пера.
		pDC->SelectObject(pDefaultBrush);
		pDC->SelectObject(pDefaultPen);
	}


	// Пишем надписи на циферблате.
	{
		// Фон надписей делаем прозрачным.
		pDC->SetBkMode(TRANSPARENT);

		// Создаем шрифт для надписей на циферблате (имя шрифта - Times New Roman),
		// размер шрифта пропорционален радиусу циферблата.
		CFont font;
		font.CreatePointFont((int)(radius*0.8), "Times New Roman");
		CFont* pDefaultFont = pDC->SelectObject(&font);

		// Пишем две надписи, вверху и внизу циферблата,
		// размеры надписей и коррекция размеров подбираются опытным путем.
		int correct = radius/4;
		pDC->DrawText("\"Заря\"", CRect(x - correct, y - correct*2, x + correct, y), DT_CENTER);
		pDC->DrawText("Кварцевые", CRect(x - (int)(correct*1.5), y + correct*2, x + (int)(correct*1.5), y + correct*3), DT_CENTER);
		
		// Возвращаем настройки шрифта по умолчанию.
		pDC->SelectObject(pDefaultFont);
	}
	

	
	// Рисуем мелкие деления по кругу - 60 штук,
	// по 6 градусов на одно деление.
	// Размер меток и коррекция размеров подбираются опытным путем.
	for(int i = 0; i < 360; i+= 6)
	{
		// Смещаем положение меток на 90 назад, чтобы начало было
		// точно вверху циферблата.
		float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
		float pos_x = radius*cos(rad) + x;
		float pos_y = radius*sin(rad) + y;
		int correct = radius/70;
		pDC->Ellipse((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
	}
	

	// Рисуем цифры и крупные деления по кругу - 12 штук,
	// по 30 градусов на одно деление.
	{
		// Создаем шрифт для надписей на циферблате (имя шрифта - Arial Black),
		// размер шрифта пропорционален радиусу циферблата.
		CFont font;
		font.CreatePointFont((int)(radius*1.6), "Arial Black");
		CFont* pDefaultFont = pDC->SelectObject(&font);

		// Аналогичные операции проводились выше
		CPen pen(0, 2, RGB(0,0,0));
		CPen* pDefaultPen = pDC->SelectObject(&pen);

		// Крупные метки будут синего цвета
		CBrush brush(RGB(0,255,255));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		
		// Рисуем по кругу циферблата 12 круглых меток,
		// Коррекция размеров подбираются опытным путем.
		for(int i = 0; i < 360; i+= 30)
		{
			// Крупные метки располагаем по кругу через 30 градусов,
			// смещаем цифры назад на 90 градусов, чтобы "12" было точно вверху циферблата
			float rad = (i * 3.14f) / 180 - (90 * 3.14f) / 180;
			float pos_x = radius*cos(rad) + x;
			float pos_y = radius*sin(rad) + y;
			
			// Коррекция размеров, положение кружочков подбирается экспериментальным путем.
			int correct;
			if(radius > 200)
				correct = radius/30;
			else
				correct = 5;
			pDC->Ellipse((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
			

			// Пишем цифры по окружности циферблата,
			// положение цифр корректируются пропорционально изменению радиуса циферблата
			pos_x = (radius + radius/4)*cos(rad) + x;
			pos_y = (radius + radius/4)*sin(rad) + y;
			
			CRect rc;
			correct = radius/7;
			rc.SetRect((int)(pos_x - correct), (int)(pos_y - correct), (int)(pos_x + correct), (int)(pos_y + correct));
			CString s;
			// Первое число "12", а не "0",
			// затем все по порядку (1-2-3-4-...).
			if(i == 0)
				s.Format("%d", 12);
			else
				s.Format("%d", i/30);
			// Непосредственно рисуем числа циферблата
			pDC->DrawText(s, &rc, DT_CENTER|DT_SINGLELINE|DT_VCENTER);

		}

		// Возврат настроек по умолчанию.
		pDC->SelectObject(pDefaultBrush);
		pDC->SelectObject(pDefaultFont);
		pDC->SelectObject(pDefaultPen);
	}

	


}


// Высчитывает положение и рисует стрелки на циферблате,
// стрелки, секундную, минутную, часовую.
void CChildView::DrawArrow(CDC* pDC, int x, int y, int radius)
{
	// Вычисляем положения стрелок.
	CTime t = CTime::GetCurrentTime();
	int m_Second = t.GetSecond() * 6;
	int m_Minute = t.GetMinute() * 6 + t.GetSecond()/10/*плюс от 0 до 6 градусов*/;
	int m_Hour = t.GetHour() * 30 + t.GetMinute()/2/*плюс от 0 до 30 градусов */;

	
	// Создаем перо для обрамления стрелок.
	CPen pen(0, 1, RGB(0,0,0));
	CPen* pDefaultPen = pDC->SelectObject(&pen);

	// Все стрелки рисуем применяя функцию рисования полигонов Polygon().

	// Самая нижняя стрелка часовая, ее рисуем первой.
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

	// Второй, в Z-положении, рисуем минутную стрелку.
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

	// Самой верхней рисуем секундную стрелку.
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

		// Стрелка будет красной.
		CBrush brush(RGB(255,0,0));
		CBrush* pDefaultBrush = pDC->SelectObject(&brush);
		pDC->Polygon(pt, 4);
		pDC->SelectObject(pDefaultBrush);
	}


	// Рисуем шляпку винтика оси на которой вращаются все стрелки.
	int correct = radius/20;
	pDC->Ellipse(x - correct, y - correct, x + correct, y + correct);
	
	// Возврат к настройкам по умолчанию.
	pDC->SelectObject(pDefaultPen);
	
}

// Таймер нужен только для возбуждения события OnPaint(), для перерисовки окна
// и всего что в нем находится.
void CChildView::OnTimer(UINT nIDEvent)
{

	Invalidate();
	
	CWnd::OnTimer(nIDEvent);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Запускаем таймер с периодичностью 100 мс
	SetTimer(10, 100, NULL);

	return 0;
}


// События двойного кликания мышью для разворачивания 
// окна на весь экран и возврат к оконному режиму.
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
		
		// Если перед перед выводом на полный экран приложение было в развернутом виде,
		// возвращаем его в нормальное состояние (когда пользователь может произвольно изменять размеры окна),
		// если не было в развернутом виде эти строчки кода не повлияют на работу приложения.
		wp.showCmd = SW_SHOWNORMAL;
		AfxGetMainWnd()->SetWindowPlacement(&wp);


		fullscreen = false;
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
