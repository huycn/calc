#pragma once
#include "gkControl.h"

namespace guitk {

class Splitter : public Control
{
public:
	virtual ~Splitter();

	Window::Pointer prevWindow() const				{ return mPrevWin; }
	Window::Pointer nextWindow() const				{ return mNextWin; }
	bool instantMove() const						{ return mInstantMove; }

protected:
	Splitter(Window::Pointer prevWin, Window::Pointer nextWin, bool instantMove = true);
	
	virtual void beginMove(int mousePosX, int mousePosY) = 0;
	virtual void doMove(int &dx, int &dy) = 0;
	virtual void endMove() = 0;

	virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	Window::Pointer mPrevWin;
	Window::Pointer mNextWin;
	bool mInstantMove;
	int mMousePosX;
	int mMousePosY;
};

class HorizontalSplitter : public Splitter
{
public:
	static WNDCLASSEX & GetWindowClass(HINSTANCE hInstance);

	HorizontalSplitter(HWND parent, int width, Window::Pointer prevWin, Window::Pointer nextWin = Window::Pointer(), bool instantMove = true);
	virtual ~HorizontalSplitter();

protected:
	virtual void beginMove(int mousePosX, int mousePosY) override;
	virtual void doMove(int &dx, int &dy) override;
	virtual void endMove() override;

private:
	int mDy;
};

class VerticalSplitter : public Splitter
{
public:
	static WNDCLASSEX & GetWindowClass(HINSTANCE hInstance);

	VerticalSplitter(HWND parent, int width, Window::Pointer prevWin, Window::Pointer nextWin = Window::Pointer(), bool instantMove = true);
	virtual ~VerticalSplitter();

protected:
	virtual void beginMove(int mousePosX, int mousePosY) override;
	virtual void doMove(int &dx, int &dy) override;
	virtual void endMove() override;

private:
	int mDx;
};

} // guitk
