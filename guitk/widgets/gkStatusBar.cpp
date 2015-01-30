#include "gkStatusBar.h"
#include "gkException.h"
#include "gkRect.h"

#include <CommCtrl.h>
#include <ciso646>

namespace guitk {

namespace {

	const int kCellPadding = 5;
	const int kSizeGripWidth = 16;

} // anonymous

void
StatusBar::init(HWND parent)
{
	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
		WS_VISIBLE | WS_CHILD,
		0, 0, 0, 0,
		parent, NULL, GetHINSTANCE(parent), 0);
	
	if (hStatus == NULL) {
		throw FatalError(_T("StatusBar window creation failed"));
	}

	HFONT hFont = (HFONT)SendMessage(parent, WM_GETFONT, 0, 0);
	if (hFont != NULL) {
		SendMessage(hStatus, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	}
	Control::init(hStatus);
}

StatusBar::~StatusBar()
{
}

void
StatusBar::updatePartSize()
{
	int variableWidth = 0;
	int fixedWidth = 0;
	for (size_t i = 0; i < mParts.size(); ++i) {
		if (mParts[i].isFixed()) {
			fixedWidth += mParts[i].getWidth();
		}
		else {
			variableWidth += mParts[i].getWidth();
		}
	}
	Rect cRect = clientRect();
	int spaceAvailable = cRect.width() - kSizeGripWidth - fixedWidth;
	double factor =  spaceAvailable / double(variableWidth);
	std::vector<int> aWidths;
	aWidths.reserve(mParts.size());

	int pos = 0;
	for (size_t i = 0; i < mParts.size(); ++i) {
		pos += mParts[i].isFixed() ? mParts[i].getWidth() : static_cast<int>(mParts[i].getWidth() * factor);
		aWidths.push_back(pos);
	}
	aWidths.back() = -1;
	SendMessage(hWnd(), SB_SETPARTS, mParts.size(), (LPARAM)&aWidths[0]);
	for (int i = 0; i < (int)mParts.size(); ++i) {
		Control::Pointer control = mParts[i].getControl();
		if (control) {
			SendMessage(hWnd(), SB_SETTEXT, SBT_OWNERDRAW | i, NULL);
			int startPos = i > 0 ? aWidths[i - 1] : 0;
			Rect rect = control->frameRect();
			control->moveTo(startPos + kCellPadding, rect.top);
			if (not mParts[i].isFixed()) {
				int endPos = i < int(mParts.size()) - 1 ? aWidths[i] : cRect.width() - kSizeGripWidth;
				control->resize(endPos - startPos - kCellPadding * 2, rect.height());
			}
		}
	}
}

int
StatusBar::addPart(int width, bool fixed)
{
	if (width <= 0) return -1;
	mParts.push_back(Part(width, fixed));
	updatePartSize();
	return mParts.size() - 1;
}

int
StatusBar::addPart(Control::Pointer control, bool fixed)
{
	Rect rect = control->frameRect();
	mParts.push_back(Part(rect.width() + kCellPadding * 2, fixed));
	mParts.back().setControl(control);
	updatePartSize();
	return mParts.size() - 1;
}

void
StatusBar::setPart(int part, const String &text)
{
	String textCopy = text;
	if (part >= 0 && part < (int)mParts.size()) {
		textCopy = _T("  ") + text;
		SendMessage(hWnd(), SB_SETTEXT, part, (LPARAM)&textCopy[0]);
	}
}

void
StatusBar::setFrameRect(const Rect &)
{
	SendMessage(hWnd(), WM_SIZE, 0, 0);
}

void
StatusBar::resize(int, int)
{
	SendMessage(hWnd(), WM_SIZE, 0, 0);
	updatePartSize();
}

void
StatusBar::move(int, int)
{
	SendMessage(hWnd(), WM_SIZE, 0, 0);
}

void
StatusBar::moveTo(int, int)
{
	SendMessage(hWnd(), WM_SIZE, 0, 0);
}

LRESULT
StatusBar::processOwnerMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DRAWITEM) {
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
		if (mParts.at(lpDrawItem->itemID).getControl()) {
			mParts[lpDrawItem->itemID].getControl()->invalidateRect();
		}
	}
	return 0;
}

} // guitk