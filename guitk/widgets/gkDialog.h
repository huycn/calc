#pragma once
#include "gkWindow.h"

namespace guitk {

class Dialog : public Window
{
public:
	virtual ~Dialog();

	virtual void show();
	virtual int getResult() const;

protected:
	Dialog();

	void createDialog(HWND parent, INT resId);
	int runModalDialog(HWND parent, INT resId);
	virtual INT_PTR dialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool mIsModal;

	static INT_PTR CALLBACK sDialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
};


} // guitk
