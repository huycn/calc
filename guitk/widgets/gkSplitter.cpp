#include "gkSplitter.h"
#include "gkWindowUtil.h"
#include "gkRect.h"
#include "gkString.h"
#include "gkException.h"

#include <ciso646>
#include <algorithm>

namespace guitk {

Splitter::Splitter(Window::Pointer prevWin, Window::Pointer nextWin, bool instantMove)
: mPrevWin(prevWin), mNextWin(nextWin), mInstantMove(instantMove)
{
}

Splitter::~Splitter()
{
}

LRESULT
Splitter::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_LBUTTONDOWN:
		{
			SetCapture(hwnd);
			mMousePosX = GET_X_LPARAM(lParam);
			mMousePosY = GET_Y_LPARAM(lParam);
			beginMove(mMousePosX, mMousePosY);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			if (GetCapture() == hwnd) {
				int dx = GET_X_LPARAM(lParam) - mMousePosX;
				int dy = GET_Y_LPARAM(lParam) - mMousePosY;
				doMove(dx, dy);
				mMousePosX += dx;
				mMousePosY += dy;
			}
			return 0;
		}
		case WM_LBUTTONUP:
		{
			if (GetCapture() == hwnd) {
				endMove();
				ReleaseCapture();
			}
			return 0;
		}
	}
	return Control::wndProc(hwnd, msg, wParam, lParam);
}

//------------------------------------------------------------------------

HorizontalSplitter::HorizontalSplitter(HWND parent, int width, Window::Pointer prevWin, Window::Pointer nextWin, bool instantMove)
: Splitter(prevWin, nextWin, instantMove), mDy(0)
{
	Rect rect = prevWin->frameRect();
	rect.top = rect.bottom;
	rect.bottom = rect.top + width;
	HINSTANCE hInstance = GetHINSTANCE(parent);
	HWND hwnd = CreateWindowEx(0, GetWindowClass(hInstance).lpszClassName, 0,
		WS_CHILD | WS_VISIBLE,
		rect.left, rect.top, rect.width(), rect.height(),
		parent, NULL, hInstance, NULL);
	init(hwnd);
}

HorizontalSplitter::~HorizontalSplitter()
{
}

WNDCLASSEX &
HorizontalSplitter::GetWindowClass(HINSTANCE hInstance)
{
	static WNDCLASSEX wc;
	static bool classRegistered = false;
	if (not classRegistered) {
		memset(&wc, 0, sizeof(wc));
		wc.cbSize        = sizeof(wc);
		wc.lpfnWndProc   = &DefWindowProc;
		wc.hInstance     = hInstance;
		wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wc.lpszClassName = _T("PBFitHorzSplitter");
		wc.hIcon		 = NULL;
		wc.hCursor		 = LoadCursor(NULL, IDC_SIZENS);

		if (!RegisterClassEx(&wc)) throw FatalError(_T("Can't register control class"));
		
		classRegistered = true;
	}
	return wc;
}

void
HorizontalSplitter::beginMove(int x, int y)
{
	mDy = 0;
}

void
HorizontalSplitter::doMove(int &dx, int &dy)
{
	if (dy != 0) {
		Rect rect = prevWindow()->frameRect();
		dy = std::max(dy, -rect.height() + prevWindow()->minHeight() - mDy);

		Rect rect2;
		if (nextWindow() != NULL) {
			nextWindow()->getFrameRect(rect2);
			dy = std::min(dy, rect2.height() - nextWindow()->minHeight() - mDy);
		}

		if (dy != 0) {
			if (instantMove()) {
				prevWindow()->resize(rect.width(), rect.height() + dy);
				if (nextWindow() != NULL) {
					rect2.top += dy;
					nextWindow()->setFrameRect(rect2);
				}
			}
			else {
				mDy += dy;
			}
			move(0, dy);
			dy = 0;
		}
	}
}

void
HorizontalSplitter::endMove()
{
	if (not instantMove()) {
		Rect rect = prevWindow()->frameRect();
		prevWindow()->resize(rect.width(), rect.height() + mDy);
		if (nextWindow() != NULL) {
			Rect rect2 = nextWindow()->frameRect();
			rect2.top += mDy;
			nextWindow()->setFrameRect(rect2);
		}
	}
}


//------------------------------------------------------------------------

VerticalSplitter::VerticalSplitter(HWND parent, int width, Window::Pointer prevWin, Window::Pointer nextWin, bool instantMove)
: Splitter(prevWin, nextWin, instantMove), mDx(0)
{
	Rect rect = prevWin->frameRect();
	rect.left = rect.right;
	rect.right = rect.left + width;
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
	HWND hwnd = CreateWindowEx(0, GetWindowClass(hInstance).lpszClassName, 0,
		WS_CHILD | WS_VISIBLE,
		rect.left, rect.top, rect.width(), rect.height(),
		parent, NULL, hInstance, NULL);
	init(hwnd);
}

VerticalSplitter::~VerticalSplitter()
{
}

WNDCLASSEX &
VerticalSplitter::GetWindowClass(HINSTANCE hInstance)
{
	static WNDCLASSEX wc;
	static bool classRegistered = false;
	if (not classRegistered) {
		memset(&wc, 0, sizeof(wc));
		wc.cbSize        = sizeof(wc);
		wc.lpfnWndProc   = &DefWindowProc;
		wc.hInstance     = hInstance;
		wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wc.lpszClassName = _T("PBFitVertSplitter");
		wc.hIcon		 = NULL;
		wc.hCursor		 = LoadCursor(NULL, IDC_SIZEWE);

		if (!RegisterClassEx(&wc)) throw FatalError(_T("Can't register control class"));
		
		classRegistered = true;
	}
	return wc;
}

void
VerticalSplitter::beginMove(int x, int y)
{
	mDx = 0;
}

void
VerticalSplitter::doMove(int &dx, int &dy)
{
	if (dx != 0) {
		Rect rect = prevWindow()->frameRect();
		dx = std::max(dx, -rect.width() + prevWindow()->minWidth() - mDx);
		
		Rect rect2;
		if (nextWindow() != NULL) {
			nextWindow()->getFrameRect(rect2);
			dx = std::min(dx, rect2.width() - nextWindow()->minWidth() - mDx);
		}

		if (dx != 0) {
			if (instantMove()) {
				prevWindow()->resize(rect.width() + dx, rect.height());
				if (nextWindow() != NULL) {
					rect2.left += dx;
					nextWindow()->setFrameRect(rect2);
				}
			}
			else {
				mDx += dx;
			}
			move(dx, 0);
			dx = 0;
		}
	}
}

void
VerticalSplitter::endMove()
{
	if (not instantMove()) {
		Rect rect = prevWindow()->frameRect();
		prevWindow()->resize(rect.width() + mDx, rect.height());
		if (nextWindow() != NULL) {
			Rect rect2 = nextWindow()->frameRect();
			rect2.left += mDx;
			nextWindow()->setFrameRect(rect2);
		}
	}
}

} // guitk