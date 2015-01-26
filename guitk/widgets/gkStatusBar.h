#pragma once
#include "gkControl.h"
#include "gkString.h"
#include <vector>

namespace guitk {

class StatusBar : public Control
{
public:
	StatusBar(HWND parent)							{ init(parent); }
	virtual ~StatusBar();

	int partCount() const							{ return mParts.size(); }
	
	virtual int addPart(int width, bool fixed = false);
	virtual int addPart(Control::Pointer control, bool fixed = true);
	
	virtual void setPart(int part, const String &text);

	virtual void setFrameRect(const Rect &rect) override;
	virtual void resize(int width, int height) override;
	virtual void move(int dx, int dy) override;
	virtual void moveTo(int left, int top) override;

protected:
	StatusBar() {}
	
	void updatePartSize();

	void init(HWND parent);
	
	virtual LRESULT processOwnerMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	
	class Part {
	public:
		Part(int width, bool fixed)					{ mWidth = width; mFixed = fixed; }
		int getWidth() const						{ return mWidth; }
		bool isFixed() const						{ return mFixed; }
		Control::Pointer getControl() const			{ return mControl; }
		void setControl(Control::Pointer control)	{ mControl = control; }

	private:
		int mWidth;
		bool mFixed;
		Control::Pointer mControl;
	};

	std::vector<Part> mParts;
};

} // guitk
