#pragma once
#include "gkFrameWindow.h"
#include "gkString.h"

namespace guitk {

class StatusBar;

class MainWindow : public FrameWindow
{
public:
	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine);
	virtual ~MainWindow();

	virtual void show(int nCmdShow);
	virtual void setContent(Window::Pointer view);
	virtual void close();
	virtual bool translateShorcuts(HACCEL hAccel, MSG *msg);

	void onStatusMsg(const String &msg);

protected:
	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	virtual LRESULT processMenuCommand(HMENU hMenu, int command, bool isShortcut) override;

private:
	std::shared_ptr<StatusBar> mStatusBar;
};

} // guitk