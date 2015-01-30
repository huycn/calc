#include "gkString.h"
#include "gkResource.h"
#include "gkMainWindow.h"
#include "gkTextEdit.h"
#include "gkRect.h"

#include <Windows.h>
#include <CommCtrl.h>

#include <ciso646>


#define WITH_GDI_PLUS 0

using namespace guitk;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//lconv
	//string localName = setlocale(LC_ALL, "");
	//_wsetlocale(LC_ALL, L"");
	//locale oldLocal = std::locale::global(std::locale(localName.c_str()));

	// Directories location
	//String currentDir;
	//currentDir.resize(MAX_PATH);
	//DWORD size = GetCurrentDirectory(currentDir.size(), &currentDir[0]);
	//if (size > currentDir.size()) {
	//	currentDir.resize(size);
	//	size = GetCurrentDirectory(currentDir.size(), &currentDir[0]);
	//}
	//currentDir.resize(size);
	//MainWindow::setCurrentDir(currentDir);

#if WITH_GDI_PLUS
	// Initialize GDI+.
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
#endif

	INITCOMMONCONTROLSEX initCommCtrl;
	memset(&initCommCtrl, 0, sizeof(initCommCtrl));
	initCommCtrl.dwSize = sizeof(initCommCtrl);
	initCommCtrl.dwICC = ICC_WIN95_CLASSES | ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&initCommCtrl);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MAIN_SHORCUTS));
	MSG msg;
	{
		MainWindow mainWnd(hInstance, hPrevInstance, lpCmdLine);
		mainWnd.setContent(std::make_shared<TextEdit>(mainWnd.hWnd(), Rect(), String(), true));
		mainWnd.show(nCmdShow);

		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			if (not mainWnd.translateShorcuts(hAccel, &msg)) {
				TranslateMessage(&msg);
			}
			DispatchMessage(&msg);
		}
	}

#if WITH_GDI_PLUS
	Gdiplus::GdiplusShutdown(gdiplusToken);
#endif

	//std::locale::global(oldLocal);
	return msg.wParam;
}
