#include "gkControl.h"
#include "gkWindowUtil.h"
#include "gkResource.h"
#include "gkException.h"

#include <ciso646>

namespace guitk {

void
Control::init(HWND hwnd)
{
	mPrevWndFunc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)Window::WindowsProc);
	Window::init(hwnd);
}

Control::~Control()
{
}

LRESULT
Control::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEWHEEL) {
		RECT myRect;
		GetWindowRect(hwnd, &myRect);
		int mouseX = GET_X_LPARAM(lParam);
		int mouseY = GET_Y_LPARAM(lParam);
		if (mouseX < myRect.left || mouseX > myRect.right || mouseY < myRect.top || mouseY > myRect.bottom) {
			// don't process, call default proc to propagate
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return callPrevProc(hwnd, msg, wParam, lParam);
}

LRESULT
Control::callPrevProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProc(mPrevWndFunc, hwnd, msg, wParam, lParam);
}

WNDCLASSEX &
Control::GetWindowClass(HINSTANCE hInstance)
{
	static WNDCLASSEX wc;
	static bool classRegistered = false;
	if (not classRegistered) {
		memset(&wc, 0, sizeof(wc));
		wc.cbSize        = sizeof(wc);
		wc.lpfnWndProc   = &DefWindowProc;
		wc.hInstance     = hInstance;
		wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wc.lpszClassName = MAKEINTRESOURCE(IDS_CONTROLCLASS);
		wc.hIcon		 = NULL;
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

		if (!RegisterClassEx(&wc)) throw FatalError(_T("Can't register control class"));
		
		classRegistered = true;
	}
	return wc;
}

} // guitk