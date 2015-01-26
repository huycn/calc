#pragma once
#include "gkControl.h"
#include "gkString.h"

namespace guitk {

class TextEdit : public Control
{
public:
	TextEdit(HWND parent, const Rect &frame, const String &text = String(), bool isNumber = false);
	
	virtual ~TextEdit();

protected:
	//virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
};

} // guitk
