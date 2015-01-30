#pragma once
#include <memory>
#include <Windows.h>

namespace guitk {

class Point;
class Rect;

class Window
{
public:
	//static const unsigned WM_USER_1 = WM_USER + 50;
	//const UINT WM_USER_2 = WM_USER_1 + 1;
	//const UINT WM_USER_3 = WM_USER_2 + 1;
	//const UINT WM_USER_4 = WM_USER_3 + 1;
	//const UINT WM_USER_5 = WM_USER_4 + 1;
	//const UINT WM_USER_6 = WM_USER_5 + 1;
	//const UINT WM_USER_7 = WM_USER_6 + 1;
	//const UINT WM_USER_8 = WM_USER_7 + 1;
	//const UINT WM_USER_9 = WM_USER_8 + 1;
	//const UINT WM_USER_QUIT = WM_USER_9 + 1; // QuitMessage

	typedef std::shared_ptr<Window> Pointer;

	enum Anchor {
		AnchorLeft		= 0x01,
		AnchorTop		= 0x02,
		AnchorRight		= 0x04,
		AnchorBottom	= 0x08,
		AnchorAllAround = 0x0F,
	};

	virtual ~Window();

	//HWND hWnd() const {
	//	return mHandle;
	//}

	virtual void takeFocus();

	virtual void show();

	virtual void hide();

	virtual void invalidateRect(const Rect *rect = nullptr, bool erase = false) const;

	int height() const;
	int width() const;

	//Size getSize() const {
	//	Rect b;
	//	getBounds(b);
	//	return b.GetSize();
	//}

	Rect frameRect() const;
	virtual void getFrameRect(Rect &result) const;
	virtual void setFrameRect(const Rect &rect);

	Rect clientRect() const;
	virtual void getClientRect(Rect &result) const;

	virtual void resize(int width, int height);
	virtual void resizeClientRect(int width, int height);
	virtual void move(int dx, int dy);
	virtual void moveTo(int left, int top);

	virtual Point screenToClient(const Point &pos) const;
	virtual Point clientToScreen(const Point &pos) const;

	/*const Size & minSize() const {
		return mMinSize;
	}*/

	virtual void setMinSize(int w, int h);
	int minWidth() const						{ return mMinWidth; }
	int minHeight() const						{ return mMinHeight; }

	//Point screenToClient(const Point &p) const {
	//	POINT result = screenToClient(p.X, p.Y);
	//	return Point(result.x, result.y);
	//}
	//Point clientToScreen(const Point &p) const {
	//	POINT result = clientToScreen(p.X, p.Y);
	//	return Point(result.x, result.y);
	//}

	//virtual Point screenToClient(int x, LONG y) const;
	//virtual Point clientToScreen(LONG x, LONG y) const;

	//Window * owner() const {
	//	return mOwner;
	//}

	//void setOwner(Window *control) {
	//	mOwner = control;
	//}

	//virtual String getText() const;

	//virtual void setText(const String &text) {
	//	SetWindowText(hWnd(), text.c_str());
	//}

	unsigned int flags() const					{ return mFlags; }

	void addFlags(unsigned int f)				{ mFlags |= f; }

	void removeFlags(unsigned int f)			{ mFlags &= ~f; }

	//void addStyle(DWORD style);
	//void removeStyle(DWORD style);
	//void addExStyle(DWORD exStyle);
	//void removeExStyle(DWORD exStyle);
		
	HINSTANCE hInstance() const {
		return GetHINSTANCE(mHandle);
	}

	//void * getUserData(const String &index) const;

	//void addUserData(const String &index, void *data) {
	//	mUserData[index] = data;
	//}

	//void addTooltip(int id, const Rect &toolRect, const String &text = String());
	//void updateTooltip(int id, const String &text);
	//void updateTooltip(int id, const Rect &toolRect);

	void drawDragRectangle(const Rect *prevRect, const Rect *newRect) const;

	//void addTooltip(const String &text = String()) {
	//	addTooltip(-1, Rect(), text);
	//}
	//
	//void updateTooltip(const String &text) {
	//	updateTooltip(-1, text);
	//}

	HWND hWnd() const { return mHandle; }

	
	virtual void onMouseWheel(WPARAM wParam, LPARAM lParam);

	static WNDCLASSEX & GetWindowClass(HINSTANCE hInstance);

	static HINSTANCE GetHINSTANCE(HWND wnd);

	//boost::signal<void (const String &msg)> postStatusMsg;

protected:
	Window() : mHandle(nullptr), mFlags(0) {}
	Window(HWND hwnd) { init(hwnd); }
	void init(HWND hwnd);

	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT processOwnerMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT processMenuCommand(HMENU hMenu, int command, bool isShortcut);

	static LRESULT CALLBACK WindowsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND mHandle;
	//Window *mOwner;
	unsigned int mFlags;
	//std::map<String, void *> mUserData;
	//Size mMinSize;
	//HWND mTooltip;
	int mMinWidth;
	int mMinHeight;
};

} // guitk
