#pragma once
#include "gkWindow.h"

namespace guitk {

class Control : public Window
{
public:
	typedef std::shared_ptr<Control> Pointer;

	virtual ~Control();

	static WNDCLASSEX & GetWindowClass(HINSTANCE hInstance);

protected:
	Control(HWND hwnd) { init(hwnd); }
	Control() {}

	void init(HWND hwnd);

	// return false to call previous proc
	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	LRESULT callPrevProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	WNDPROC mPrevWndFunc;
};

} // guitk
