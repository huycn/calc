#pragma once
#include "gkWindow.h"

#include <vector>

namespace guitk {

class FrameWindow : public Window
{
public:
	FrameWindow(HWND parent, const Rect &rect);
	
	void addChild(Window::Pointer win);
	void removeChild(Window::Pointer win);

protected:
	FrameWindow();

	void init(HWND hwnd);
	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	virtual void onMouseWheel(WPARAM wParam, LPARAM lParam) override;

private:
	std::vector<Window::Pointer> mChildren;
	int mOldWidth;
	int mOldHeight;
};

} // guitk
