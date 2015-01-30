#include "gkComboBox.h"
#include "gkRect.h"
#include "gkException.h"

namespace guitk {

static const unsigned MESSAGE_EDIT_DONE = WM_USER + 1;

class ComboBox::EditControl : public Control
{
public:
	EditControl(HWND hwnd, HWND parent) {
		init(hwnd);
		mParent = parent;
	}

protected:
	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override {
		if (msg == WM_CHAR) {
			if (wParam == VK_RETURN || wParam == VK_ESCAPE || wParam == VK_TAB) {
				return SendMessage(mParent, MESSAGE_EDIT_DONE, wParam, lParam);
			}
		}
		return Control::wndProc(hwnd, msg, wParam, lParam);
	}

	HWND mParent;
};

ComboBox::~ComboBox() {
}

ComboBox::ComboBox(HWND parent, const Rect &bounds, const std::vector<String> &entries, const String &text)
{
	init(parent, bounds, entries, true);
	SetWindowText(hWnd(), text.c_str());
	SendMessage(hWnd(), CB_SHOWDROPDOWN, TRUE, 0);
}

ComboBox::ComboBox(HWND parent, const Rect &bounds, const std::vector<String> &entries, int curSel, bool editable)
{
	init(parent, bounds, entries, editable);
	setCurSelect(curSel);
	SendMessage(hWnd(), CB_SHOWDROPDOWN, TRUE, 0);
}

void
ComboBox::init(HWND parent, const Rect &bounds, const std::vector<String> &entries, bool editable)
{
	HWND hComboBox = CreateWindow(_T("COMBOBOX"), NULL, WS_VISIBLE | WS_CHILD | CBS_AUTOHSCROLL | (editable ? CBS_DROPDOWN : CBS_DROPDOWNLIST),
		bounds.left, bounds.top, bounds.width(), bounds.height(),
		parent, NULL, GetHINSTANCE(parent), 0);

	if (hComboBox == NULL) {
		throw FatalError(_T("ComboBox window creation failed"));
	}
	HFONT hFont = (HFONT)SendMessage(parent, WM_GETFONT, 0, 0);
	if (hFont != NULL) {
		SendMessage(hComboBox, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	}
	for (size_t i=0; i<entries.size(); ++i) {
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)entries[i].c_str());
	}
	if (editable) {
		POINT pt;
		pt.x = 5;
		pt.y = 5;
		HWND hwndEdit = ChildWindowFromPoint(hComboBox, pt);
		if (hwndEdit != hComboBox) {
			mEditControl.reset(new EditControl(hwndEdit, hComboBox));
		}
	}
	Control::init(hComboBox);
}

int
ComboBox::getCurSelect() const
{
	return SendMessage(hWnd(), CB_GETCURSEL, 0, 0);
}

void
ComboBox::setCurSelect(int index)
{
	SendMessage(hWnd(), CB_SETCURSEL, index, 0);
}

//LRESULT
//ComboBox::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	if (msg == MESSAGE_EDIT_DONE) {
//		if (owner() == NULL) return false;
//		if (wParam == VK_RETURN) {
//			owner()->takeFocus();
//		}
//		else if (wParam == VK_ESCAPE) {
//			PostMessage(owner()->hWnd(), msg, wParam, lParam);
//		}
//		else if (wParam == VK_TAB) {
//			PostMessage(owner()->hWnd(), WM_USER_2, wParam, lParam);
//		}
//		return 0;
//	}
//	return Control::wndProc(hwnd, msg, wParam, lParam);
//}

} // guitk