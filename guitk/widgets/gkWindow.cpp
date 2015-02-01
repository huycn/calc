#include "gkWindow.h"
#include "gkString.h"
#include "gkRect.h"
#include "gkPoint.h"
#include "gkResource.h"
#include "gkException.h"
#include "gkLogger.h"

#include <ciso646>
#include <algorithm>

namespace guitk {

void
Window::init(HWND hwnd)
{
	mHandle = hwnd;
	mFlags = 0;
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

Window::~Window()
{
	//DestroyWindow(mTooltip);
	DestroyWindow(mHandle);
}

void
Window::takeFocus()
{
	SetFocus(mHandle);
}

void
Window::show()
{
	ShowWindow(mHandle, SW_SHOW);
}

void
Window::hide()
{
	ShowWindow(mHandle, SW_HIDE);
}

int
Window::height() const
{
	return frameRect().height();
}

int
Window::width() const
{
	return frameRect().width();
}

//Size getSize() const {
//	Rect b;
//	getBounds(b);
//	return b.GetSize();
//}

//void *
//	Window::getUserData(const String &index) const
//{
//	std::map<String, void *>::const_iterator it = mUserData.find(index);
//	if (it != mUserData.end()) {
//		return it->second;
//	}
//	return NULL;
//}
//
//String
//	Window::getText() const
//{
//	String result(1024, String::value_type());
//	int textLength = GetWindowText(hWnd(), &result[0], static_cast<int>(result.size()));
//	result.resize(textLength);
//	return result;
//}

LRESULT CALLBACK
Window::WindowsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window *win = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (win != NULL) {
		try {
			return win->wndProc(hwnd, msg, wParam, lParam);
		}
		catch (...) {
			MessageBox(NULL, _T("Something unexpected occurred!?!"), _T("Unexpected Error"), MB_OK | MB_ICONERROR);
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT
Window::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (msg == WM_NOTIFY) {
	//	LPNMHDR notify = (LPNMHDR)lParam;
	//	Window *control = reinterpret_cast<Window *>(GetWindowLongPtr(notify->hwndFrom, GWLP_USERDATA));
	//	if (control != NULL) {
	//		return control->processNotifyMsg(notify->hwndFrom, notify->code, wParam, lParam);
	//	}
	//}
	if (msg == WM_DRAWITEM) {
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
		Window *control = reinterpret_cast<Window *>(GetWindowLongPtr(lpDrawItem->hwndItem, GWLP_USERDATA));
		if (control != NULL) {
			return control->processOwnerMsg(lpDrawItem->hwndItem, msg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT
Window::processOwnerMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT
Window::processMenuCommand(HMENU hMenu, int command, bool isShortcut)
{
	return 0;
}

void
Window::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
}

WNDCLASSEX &
Window::GetWindowClass(HINSTANCE hInstance)
{
	static WNDCLASSEX wc;
	static bool classRegistered = false;
	if (not classRegistered) {
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = Window::WindowsProc;
		wc.hInstance = hInstance;
		wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wc.lpszClassName = MAKEINTRESOURCE(IDS_WINDOWCLASS);
		wc.hIcon = (HICON)LoadImage(wc.hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, LR_SHARED);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		if (!RegisterClassEx(&wc)) throw FatalError(_T("Can't register window class"));

		classRegistered = true;
	}
	return wc;
}

HINSTANCE
Window::GetHINSTANCE(HWND wnd)
{
	return (HINSTANCE)GetWindowLongPtr(wnd, GWLP_HINSTANCE);
}

//
//void
//	Window::addStyle(DWORD style)
//{
//	LONG curStyle = GetWindowLong(hWnd(), GWL_STYLE);
//	curStyle |= style;
//	SetWindowLong(hWnd(), GWL_STYLE, curStyle);
//}
//
//void
//	Window::removeStyle(DWORD style)
//{
//	LONG curStyle = GetWindowLong(hWnd(), GWL_STYLE);
//	curStyle &= ~style;
//	SetWindowLong(hWnd(), GWL_STYLE, curStyle);
//}
//
//void
//	Window::addExStyle(DWORD exStyle)
//{
//	LONG curStyle = GetWindowLong(hWnd(), GWL_EXSTYLE);
//	curStyle |= exStyle;
//	SetWindowLong(hWnd(), GWL_EXSTYLE, curStyle);
//}
//
//void
//	Window::removeExStyle(DWORD exStyle)
//{
//	LONG curStyle = GetWindowLong(hWnd(), GWL_EXSTYLE);
//	curStyle &= ~exStyle;
//	SetWindowLong(hWnd(), GWL_EXSTYLE, curStyle);
//}

Rect
Window::frameRect() const
{
	Rect r;
	getFrameRect(r);
	return r;
}

void
Window::getFrameRect(Rect &result) const
{
	WINDOWPLACEMENT wndPlace;
	if (GetWindowPlacement(mHandle, &wndPlace)) {
		result = wndPlace.rcNormalPosition;
	}
}

void
Window::setFrameRect(const Rect &rect)
{
	SetWindowPos(mHandle, 0, rect.left, rect.top, rect.width(), rect.height(),
		SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

Rect
Window::clientRect() const
{
	Rect r;
	getClientRect(r);
	return r;
}

void
Window::getClientRect(Rect &result) const
{
	GetClientRect(mHandle, &result);
}

Point
Window::screenToClient(const Point &pos) const
{
	Point result = pos;
	ScreenToClient(mHandle, &result);
	return result;
}

Point
Window::clientToScreen(const Point &pos) const
{
	POINT result = pos;
	ClientToScreen(mHandle, &result);
	return result;
}

void
Window::resize(int width, int height)
{
	LOGE("Resize %dx%d", width, height);
	width = std::max(width, mMinWidth);
	height = std::max(height, mMinHeight);
	SetWindowPos(mHandle, 0, 0, 0, width, height,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void
Window::resizeClientRect(int width, int height)
{
	Rect bounds = frameRect();
	Rect cRect = clientRect();
	resize(bounds.width() + width - cRect.width(), bounds.height() + height - cRect.height());
}

void
Window::moveTo(int left, int top)
{
	SetWindowPos(mHandle, 0, left, top, 0, 0,
		SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
}

void
Window::move(int dx, int dy)
{
	if (dx != 0 || dy != 0) {
		Rect bounding = frameRect();
		moveTo(bounding.left + dx, bounding.top + dy);
	}
}

void
Window::setMinSize(int w, int h)
{
	mMinWidth = w;
	mMinHeight = h;
	Rect rect = frameRect();
	if (rect.width() < mMinWidth || rect.height() < mMinHeight) {
		resize(std::max(rect.width(), mMinWidth), std::max(rect.height(), mMinHeight));
	}
}

/*
void
	Window::addTooltip(int id, const Rect &toolRect, const String &text)
{
	if (mTooltip == NULL) {
		// create tooltip
		mTooltip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
			WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hWnd(), NULL, hInstance(), NULL);
		SetWindowPos(mTooltip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	TOOLINFO ti;
	memset(&ti, 0, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_SUBCLASS | (id == -1 ? TTF_IDISHWND : 0);
	ti.hwnd = hWnd();
	ti.hinst = NULL;
	ti.uId = (id == -1 ? int(hWnd()) : id);
	ti.lpszText = const_cast<LPTSTR>(text.c_str());
	toolRect.ToRECT(&ti.rect);
	SendMessage(mTooltip, TTM_ADDTOOL, 0, LPARAM(&ti));
}

void
	Window::updateTooltip(int id, const String &text)
{
	TOOLINFO ti;
	memset(&ti, 0, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_SUBCLASS | (id == -1 ? TTF_IDISHWND : 0);
	ti.hwnd = hWnd();
	ti.uId = (id == -1 ? int(hWnd()) : id);
	ti.hinst = NULL;
	ti.lpszText = const_cast<LPTSTR>(text.c_str());
	SendMessage(mTooltip, TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
}

void
	Window::updateTooltip(int id, const Rect &toolRect)
{
	assert(id != -1); // no sense
	TOOLINFO ti;
	ti.cbSize = sizeof(ti);
	ti.hwnd = hWnd();
	ti.uId = id;
	toolRect.ToRECT(&ti.rect);
	SendMessage(mTooltip, TTM_NEWTOOLRECT, 0, (LPARAM)&ti);
}
*/

void
Window::drawDragRectangle(const Rect *prevRect, const Rect *newRect) const
{
	static HPEN hpenDot = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	HDC hdc = GetDC(mHandle);
	SetROP2(hdc, R2_NOTXORPEN);
	SelectObject(hdc, hpenDot);
	if (prevRect != NULL)
	{
		Rectangle(hdc, prevRect->left, prevRect->top, prevRect->right, prevRect->bottom);
	}
	if (newRect != NULL)
	{
		Rectangle(hdc, newRect->left, newRect->top, newRect->right, newRect->bottom);
	}
	ReleaseDC(mHandle, hdc);
}

void
Window::invalidateRect(const Rect *in_rect, bool erase) const
{
	InvalidateRect(mHandle, in_rect, erase);
}

} // namespace guitk