#include "gkDialog.h"
#include "gkException.h"

namespace guitk {

Dialog::Dialog() : mIsModal(false)
{
}

Dialog::~Dialog()
{
	if (mIsModal) {
		// ~Window will cancel DestroyWindow on this handle because it's destroyed by EndDialog()
		//mHandle = NULL;
	}
}

int
Dialog::getResult() const
{
	return 0;
}

void
Dialog::createDialog(HWND parent, INT resId)
{
	HWND hDdlg = CreateDialogParam(GetHINSTANCE(parent), MAKEINTRESOURCE(resId), parent, &Dialog::sDialogProc, NULL);
	if (hDdlg == NULL) {
		throw FatalError(_T("Can't create dialog"));
	}
	Window::init(hDdlg);
}

int
Dialog::runModalDialog(HWND parent, INT resId)
{
	return DialogBoxParam(GetHINSTANCE(parent), MAKEINTRESOURCE(resId), parent, &Dialog::sDialogProc, (LPARAM)this);
}

void
Dialog::show()
{
	Window::show();
	SetForegroundWindow(hWnd());
}

INT_PTR
Dialog::dialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return msg == WM_INITDIALOG;
}

INT_PTR CALLBACK
Dialog::sDialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Dialog *dial = reinterpret_cast<Dialog *>(GetWindowLongPtr(hwndDlg, GWLP_USERDATA));
	if (dial != NULL) {
		return dial->dialogProc(hwndDlg, msg, wParam, lParam);
	}
	else if (msg == WM_INITDIALOG && lParam != NULL) {
		Dialog *dial = reinterpret_cast<Dialog *>(lParam);
		dial->Window::init(hwndDlg);
		dial->mIsModal = true;
		return dial->dialogProc(hwndDlg, msg, wParam, lParam);
	}
	return FALSE;
}

} // guitk