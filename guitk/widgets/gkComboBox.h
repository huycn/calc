#pragma once
#include "gkControl.h"
#include "gkString.h"

#include <vector>

namespace guitk {

class ComboBox : public Control
{
public:
	ComboBox(HWND parent, const Rect &bounds, const std::vector<String> &entries, const String &text);
	ComboBox(HWND parent, const Rect &bounds, const std::vector<String> &entries, int curSel, bool editable = false);
	virtual ~ComboBox();

	int getCurSelect() const;
	void setCurSelect(int index);

protected:
	void init(HWND parent, const Rect &bounds, const std::vector<String> &entries, bool editable);
	
	//virtual LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	class EditControl;
	std::unique_ptr<EditControl> mEditControl;
};

} // guitk
