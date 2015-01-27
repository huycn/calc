#include "gkFrameWindow.h"
#include "gkRect.h"
#include "gkWindowUtil.h"
#include "gkPoint.h"

#include <algorithm>
#include <ciso646>

namespace guitk {

FrameWindow::FrameWindow()
{
}

FrameWindow::FrameWindow(HWND parent, const Rect &rect)
{
	HINSTANCE hInstance = GetHINSTANCE(parent);
	HWND hwnd = CreateWindowEx(0, GetWindowClass(hInstance).lpszClassName, 0,
								WS_CHILDWINDOW | WS_VISIBLE,
								rect.left, rect.top, rect.width(), rect.height(),
								parent, NULL, hInstance, NULL);
	init(hwnd);
}

void
FrameWindow::addChild(Window::Pointer win)
{
	if (std::find(mChildren.begin(), mChildren.end(), win) == mChildren.end()) {
		mChildren.push_back(win);
	}
}

void
FrameWindow::removeChild(Window::Pointer win)
{
	mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), win), mChildren.end());
}

void
FrameWindow::init(HWND hwnd)
{
	Window::init(hwnd);
	Rect r = clientRect();
	mOldWidth = r.width();
	mOldHeight = r.height();
}

LRESULT
FrameWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_SIZE:
		{
			if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED) {
				int newWidth = LOWORD(lParam);
				int newHeight = HIWORD(lParam);
				int dx = newWidth - mOldWidth;
				int dy = newHeight - mOldHeight;
				if (dx != 0) {
					for (const Window::Pointer& child : mChildren) {
						unsigned f = child->flags();
						if (f & Window::AnchorRight) {
							if (f & Window::AnchorLeft) {
								Rect rect = child->frameRect();
								child->resize(rect.width() + dx, rect.height());
							}
							else {
								child->move(dx, 0);
							}
						}
					}
				}
				if (dy != 0) {
					for (const Window::Pointer& child : mChildren) {
						unsigned f = child->flags();
						if (f & Window::AnchorBottom) {
							if (f & Window::AnchorTop) {
								Rect rect = child->frameRect();
								child->resize(rect.width(), rect.height() + dy);
							}
							else {
								child->move(0, dy);
							}
						}
					}
				}
				mOldWidth = newWidth;
				mOldHeight = newHeight;
			}
			break;
		}
		default:
			return Window::wndProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void
FrameWindow::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
	Point mousePos = screenToClient(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	HWND child = ChildWindowFromPoint(hWnd(), mousePos);
	if (child != NULL && child != hWnd()) {
		Window *win = reinterpret_cast<Window *>(GetWindowLongPtr(child, GWLP_USERDATA));
		if (win != NULL) {
			win->onMouseWheel(wParam, lParam);
		}
	}
}

} // guitk