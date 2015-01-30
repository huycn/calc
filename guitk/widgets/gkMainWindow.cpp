#include "gkMainWindow.h"
#include "gkResource.h"
#include "gkException.h"
#include "gkStatusBar.h"
#include "gkRect.h"

namespace guitk {

MainWindow::MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine)
{
	HWND hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, GetWindowClass(hInstance).lpszClassName, MAKEINTRESOURCE(IDS_APP_NAME),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAIN_MENU)),
		hInstance, 0);
	if (hwnd == NULL) throw FatalError(_T("Can't create main window"));
	init(hwnd);

	//mPref.reset(new SfavPreferences(APP_REGISTRY_KEY_NAME));
	//if (not mPref->windowPos.IsEmptyArea()) {
	//	setBounds(mPref->windowPos);
	//}

	// Create statusbar
	mStatusBar.reset(new StatusBar(hwnd));
	mStatusBar->addFlags(Window::AnchorLeft | Window::AnchorBottom | Window::AnchorRight);
	mStatusBar->addPart(1);
	//if (mPref->viewStatusBar) {
	addChild(mStatusBar);
	//	mStatusBarHeight = mStatusBar->getHeight();
	//}
	//else {
	//	mStatusBar->hide();
	//	mStatusBarHeight = 0;
	//}

	Rect cRect = clientRect();
	cRect.bottom -= mStatusBar->height();

	//mImage.reset(new SelectionablePictureBox(hwnd, cRect));
	//mImage->addFlags(Window::fAnchorAll);
	//addChild(mImage);

	//CheckMenuItem(GetMenu(hwnd), ID_VIEW_IMAGEINFO, MF_BYCOMMAND | mPref->viewStatusBar ? MF_CHECKED : MF_UNCHECKED);


	// Parse command line
	//LPWSTR *szArglist;
	//int nArgs;
	//szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	//if (NULL != szArglist && nArgs > 1) {
	//	loadFile(szArglist[1]);
	//}
	//LocalFree(szArglist);

	onStatusMsg(_T("Ready"));
}

MainWindow::~MainWindow()
{
}

void
MainWindow::setContent(Window::Pointer view)
{
	Rect cRect = clientRect();
	if (mStatusBar != nullptr) {
		cRect.bottom -= mStatusBar->height();
	}
	view->addFlags(Window::AnchorAllAround);
	view->setFrameRect(cRect);
	addChild(view);
}

void
MainWindow::show(int nCmdShow)
{
	ShowWindow(hWnd(), nCmdShow);
	UpdateWindow(hWnd());
}

void
MainWindow::onStatusMsg(const String &msg)
{
	mStatusBar->setPart(0, msg);
}

void
MainWindow::close()
{
	PostQuitMessage(0);
}

bool
MainWindow::translateShorcuts(HACCEL hAccel, MSG *msg)
{
	return TranslateAccelerator(hWnd(), hAccel, msg) != 0;
}

LRESULT
MainWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		SetFocus(hwnd);
		break;
	}
	case WM_CLOSE:
	{
		close();
		break;
	}
	case WM_MOUSEWHEEL:
	{
		onMouseWheel(wParam, lParam);
		break;
	}
	case WM_COMMAND:
	{
		int noCode = HIWORD(wParam);
		if (lParam == NULL && (noCode == 0 || noCode == 1)) {
			return processMenuCommand(GetMenu(hwnd), LOWORD(wParam), noCode == 1);
		}
	}
	//case WM_INITMENU:
	//{
	//	ClipBoard cb(hwnd);
	//	EnableMenuItem(GetMenu(hwnd), ID_EDIT_PASTE_, MF_BYCOMMAND | (cb.isBitmapAvailable() ? MF_ENABLED : MF_GRAYED));
	//	break;
	//}
	//case WM_DROPFILES:
	//{
	//	HDROP hDropFiles = (HDROP)wParam;
	//	unsigned nFiles = DragQueryFile(hDropFiles, 0xFFFFFFFF, NULL, 0);
	//	if (nFiles > 0) {
	//		String buffer;
	//		buffer.resize(MAX_PATH);
	//		unsigned bufferSize = DragQueryFile(hDropFiles, 0, &buffer[0], buffer.size());
	//		buffer.resize(bufferSize);
	//		if (loadFile(buffer)) {
	//			updateFileList(buffer);
	//		}
	//	}
	//	break;
	//}
	default:
		return FrameWindow::wndProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT
MainWindow::processMenuCommand(HMENU hMenu, int command, bool isShortcut)
{
	switch (command) {
		case ID_FILE_EXIT:
			close();
			break;
	}

	return FrameWindow::processMenuCommand(hMenu, command, isShortcut);
}

} // guitk