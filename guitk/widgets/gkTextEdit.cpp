#include "gkTextEdit.h"
#include "gkString.h"
#include "gkException.h"
#include "gkRect.h"

namespace guitk {

TextEdit::TextEdit(HWND parent, const Rect &frame, const String &text, bool isNumber)
{
	HWND hEdit = CreateWindow(_T("EDIT"), text.c_str(),
		WS_VISIBLE | WS_CHILDWINDOW | ES_AUTOHSCROLL | (isNumber ? ES_NUMBER : 0),
		frame.left, frame.top, frame.width(), frame.height(),
		parent, NULL, GetHINSTANCE(parent), 0);
	
	if (hEdit == NULL) {
		throw FatalError(_T("TextEdit window creation failed"));
	}

	HFONT hFont = (HFONT)SendMessage(parent, WM_GETFONT, 0, 0);
	if (hFont != NULL) {
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	}

	Control::init(hEdit);
	SendMessage(hEdit, EM_SETSEL, 0, -1);
}

TextEdit::~TextEdit()
{
}

/*
LRESULT
TextEdit::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) {
		case WM_CHAR:
		{
			if (owner() == NULL) return false;
			if (wParam == VK_RETURN) {
				owner()->takeFocus();
				return 0;
			}
			else if (wParam == VK_ESCAPE) {
				PostMessage(owner()->hWnd(), msg, wParam, lParam);
				return 0;
			}
			else if (wParam == VK_TAB) {
				PostMessage(owner()->hWnd(), WM_USER_2, wParam, lParam);
				return 0;
			}
		}
	}
	return Control::wndProc(hwnd, msg, wParam, lParam);
}
*/

} // guitk