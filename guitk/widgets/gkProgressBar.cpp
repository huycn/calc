#include "gkProgressBar.h"
#include "gkRect.h"

#include <CommCtrl.h>

namespace guitk {

ProgressBar::ProgressBar(HWND parent, const Rect &bounds, const String &label)
{
	HWND hProgBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_VISIBLE | WS_CHILDWINDOW,
		bounds.left, bounds.top, bounds.width(), bounds.height(),
		parent, NULL, GetHINSTANCE(parent), NULL);

	Control::init(hProgBar);
	mOffset = 0.0;
	mFac = 1.0;
	mStep = 10;
}

ProgressBar::~ProgressBar()
{
}

void
ProgressBar::setRange(double minVal, double maxVal)
{
	mFac = 100 / (maxVal - minVal);
	mOffset = minVal;
}

void
ProgressBar::setStep(double step)
{
	int nStepInc = static_cast<int>(step * mFac);
	PostMessage(hWnd(), PBM_SETSTEP, (WPARAM)nStepInc, 0);
}

void
ProgressBar::setPos(double pos)
{
	int nNewPos = static_cast<int>((pos - mOffset) * mFac);
	PostMessage(hWnd(), PBM_SETPOS, nNewPos, 0);
}

void
ProgressBar::nextStep()
{
	PostMessage(hWnd(), PBM_STEPIT, 0, 0);
}

double
ProgressBar::getPos() const
{
	UINT nPos = SendMessage(hWnd(), PBM_GETPOS, 0, 0);
	return nPos / mFac + mOffset;
}

} // guitk