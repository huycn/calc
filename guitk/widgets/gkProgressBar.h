#pragma once
#include "gkControl.h"
#include "gkString.h"

namespace guitk {

class ProgressBar : public Control
{
public:
	ProgressBar(HWND parent, const Rect &bounds, const String &label = String());
	virtual ~ProgressBar();

	virtual void setRange(double minVal, double maxVal);
	virtual void setStep(double step);
	virtual void setPos(double pos);
	virtual void nextStep();

	virtual double getPos() const;

protected:
	double mOffset;
	double mFac;
	double mStep;
};

} // guitk
