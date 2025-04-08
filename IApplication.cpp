/**
 * An abstract class implements basic
 * features of game application, including
 * window handling etc.
 */

#include "IApplication.h"

IApplication::IApplication(void)
{
	// initialise the members
	m_hWnd = NULL;
	m_bActive = FALSE;
	m_bWindowed = FALSE;

	::memset(&m_rcScreen, 0, sizeof(RECT));
	::memset(&m_rcWindow, 0, sizeof(RECT));

	// seed the random number generator
	::srand( ::GetTickCount() );
}

IApplication::~IApplication(void)
{
}


HRESULT IApplication::Create(	int iWidth,
								int iHeight,
								int iBPP,
								BOOL bWindowed,
								LPCTSTR strTitle,
								DWORD dwFlags)
{
	// create application window
	if(!CreateAppWindow(	iWidth,
							iHeight,
							bWindowed,
							strTitle))
	{
		return E_FAIL;
	}

	// initialise the timer
	m_Timer.Create();

	// call pure virtual OnCreate
	HRESULT hres;
	hres = OnCreate();
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	SetActive(TRUE);
	return S_OK;
}


void IApplication::Release(void)
{
	if(m_hWnd)
	{
		// call pure virtual OnRelease
		OnRelease();

		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	// release the timer
	m_Timer.Release();
}


BOOL IApplication::CreateAppWindow(	int iWidth,
									int iHeight,
									BOOL bWindowed,
									LPCTSTR strTitle)
{
	HINSTANCE		hInstance = ::GetModuleHandle(NULL);
	DWORD			dwStyle = 0;
	HMENU			hMenu = NULL;
	int				iWindowWidth = 0;
	int				iWindowHeight = 0;

	m_bWindowed = bWindowed;

	// create window
	if(IsWindowed())
	{
		// init normal overlapping window
		dwStyle = WS_OVERLAPPEDWINDOW;

		// compute overall window size
		// width and height parameters are window client
		// area size, we need to compute total window size
		iWindowWidth = iWidth +
			::GetSystemMetrics(SM_CXSIZEFRAME) * 2;
		iWindowHeight = iHeight +
			::GetSystemMetrics(SM_CYSIZEFRAME) * 2 +
			::GetSystemMetrics(SM_CYMENU);
	}
	else
	{
		// init fullscreen mode window
		// WS_POPUP is a borderless no-titlebar window
		dwStyle = WS_POPUP;
		iWindowWidth = iWidth;
		iWindowHeight = iHeight;
	}

	// register window class
	const wchar_t strClassName[] = L"GameEngineWC";
	WNDCLASSEX		wc;

	::memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = ::LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = strTitle;
	wc.lpszClassName = strClassName;
	wc.cbWndExtra = sizeof(IApplication*);

	::RegisterClassEx(&wc);

	// create window
	m_hWnd = ::CreateWindowEx(	0,
								strClassName,
								strTitle,
								dwStyle,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								iWindowWidth,
								iWindowHeight,
								NULL,
								hMenu,
								hInstance,
								NULL);
	if(m_hWnd == NULL)
	{
		return FALSE;
	}

	::SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG_PTR)this);

	// update & show the window
	::UpdateWindow(m_hWnd);
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateRectangles();
	return TRUE;
}


BOOL IApplication::OnMessage(	UINT iMessage, 
								WPARAM wParam,
								LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CLOSE:
		SetActive(FALSE);
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
		break;

	case WM_DESTROY:
		Release();
		::PostQuitMessage(0);
		break;

	case WM_ACTIVATEAPP:
		if(wParam == 0)
		{
			// application de-activating
			if(!IsWindowed())
			{
				SetActive(FALSE);
			}
		}
		else
		{
			// application is activating
			SetActive(TRUE);
		}
		break;

	case WM_SIZE:
		OnSize((DWORD)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOVE:
		OnMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_GETMINMAXINFO:
		if(IsActive() && IsWindowed())
		{
			// fix minimum size of the window
			MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
			pInfo->ptMinTrackSize.x = 100;
			pInfo->ptMinTrackSize.y = 50;
		}
		break;

	case WM_SETCURSOR:
		if(IsActive() && !IsWindowed())
		{
			::SetCursor(NULL);
			return TRUE;
		}
		break;

	case WM_KEYDOWN:
		OnKeyDown((DWORD)wParam);
		break;

	case WM_KEYUP:
		OnKeyUp((DWORD)wParam);
		break;

	case WM_CHAR:
		OnChar( (TCHAR)wParam);
		break;

	case WM_EXITSIZEMOVE:
		m_Timer.BeginTimer();
		break;
	}

	return FALSE;
}


long WINAPI IApplication::WndProc(	HWND hWnd,
									UINT iMessage,
									WPARAM wParam,
									LPARAM lParam)
{
	IApplication* pApplication = 
		(IApplication*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

	// handle WM_CREATE message. This message is received
	// before window is created, so we don't have valid pointer
	// yet.
	if(iMessage == WM_CREATE)
	{
		::SetForegroundWindow(hWnd);
		return 0;
	}

	if(pApplication == NULL)
	{
		return (long)::DefWindowProc(hWnd, iMessage, wParam, lParam);
	}

	// call virtual message handler
	if(pApplication->OnMessage(iMessage, wParam, lParam) == FALSE)
	{
		return (long)::DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
	else
	{
		return 0;
	}
}


void IApplication::SetActive(BOOL bSet)
{
	m_bActive = bSet;
	m_Timer.BeginTimer();
}


int IApplication::Run(void)
{
	MSG		msg;
	BOOL	bGotMessage = FALSE;

	::memset(&msg, 0, sizeof(MSG));

	// loop until WM_QUIT message
	while (msg.message != WM_QUIT)
	{
		if(IsActive())
		{
			// we are active and want to update screen as fast as
			// possible. Use PeekMessage to get the windows messages.
			// PeekMessage returns immediately if there are no
			// messages pending in windows message queue.
			bGotMessage = ::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE);
		}
		else
		{
			bGotMessage = ::GetMessage(&msg, m_hWnd, 0, 0);
		}

		if(bGotMessage)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			// no windows messages pending, perform
			// screen update
			DoFlip();
		}
	}

	return (int)msg.wParam;
}


void IApplication::OnSize(DWORD dwType, int iWidth, int iHeight)
{
	if(dwType == SIZE_MINIMIZED)
	{
		SetActive(FALSE);
	}
	else
	{
		if(IsWindowed())
		{
			UpdateRectangles();
		}
		SetActive(TRUE);
	}
}

void IApplication::OnMove(int iX, int iY)
{
	if(IsWindowed())
	{
		UpdateRectangles();
	}
}


void IApplication::UpdateRectangles(void)
{
	// get the window client area
	::GetClientRect(m_hWnd, &m_rcWindow);

	// copy window rectangle to screen rectangle
	::memcpy(&m_rcScreen, &m_rcWindow, sizeof(RECT));

	// convert viewport coordinates to screen
	::ClientToScreen(m_hWnd, (POINT*)&m_rcScreen.left);
	::ClientToScreen(m_hWnd, (POINT*)&m_rcScreen.right);
}


void IApplication::Close(void)
{
	if(m_hWnd)
	{
		::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
}


void IApplication::DoFlip(void)
{
	if(!IsActive())
	{
		return;
	}

	// compute the frame time
	m_Timer.EndTimer();
	m_Timer.BeginTimer();

	// call pure virtual OnFlip
	OnFlip();
}


void IApplication::OnKeyDown(DWORD dwKey)
{
	// no implementation required
}


void IApplication::OnKeyUp(DWORD dwKey)
{
	// no implementation required
}


void IApplication::OnChar(TCHAR c)
{
	// no implementation required
}


int IApplication::RandInt(int iLow, int iHigh)
{
	return (::rand() % ((iHigh + 1) - iLow) + iLow);
}

float IApplication::RandFloat(float fLow, float fHigh)
{
	return ((fHigh - fLow) * (float)(::rand() / (float)RAND_MAX)) + fLow;
}