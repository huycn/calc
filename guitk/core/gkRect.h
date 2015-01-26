#pragma once
#include <Windows.h>

namespace guitk {

class Rect : public RECT
{

public:
	Rect()									{ left = top = right = bottom = 0; }
	Rect(const RECT &r)						{ left = r.left; top = r.top; right = r.right; bottom = r.bottom; }

	int width() const						{ return right - left; }
	int height() const						{ return bottom - top; }
	
	Rect & operator=(const RECT &other)		{ RECT::operator=(other); return *this; }


/*	
	RectT(const PointT<T> &location, const SizeT<T> &size) {
		X = location.X;
		Y = location.Y;
		Width = size.Width;
		Height = size.Height;
	}

	RectT(const RECT *rect) {
		FromRECT(rect);
	}

	void FromRECT(const RECT *rect) {
		X = static_cast<T>(rect->left);
		Y = static_cast<T>(rect->top);
		Width = static_cast<T>(rect->right - rect->left);
		Height = static_cast<T>(rect->bottom - rect->top);
	}

	void ToRECT(RECT *rect) const {
		rect->left = X;
		rect->top = Y;
		rect->right = GetRight();
		rect->bottom = GetBottom();
	}

	void GetLocation(PointT<T> &point) const {
		point.X = X;
		point.Y = Y;
	}

	void GetSize(SizeT<T> &size) const {
		size.Width = Width;
		size.Height = Height;
	}

	SizeT<T> GetSize() const {
		SizeT<T> result;
		result.Width = Width;
		result.Height = Height;
		return result;
	}

	T GetLeft() const {
		return X;
	}

	T GetTop() const {
		return Y;
	}

	T GetRight() const {
		return X + Width;
	}

	T GetBottom() const	{
		return Y + Height;
	}

	T GetWidth() const {
		return Width;
	}

	T GetHeight() const {
		return Height;
	}

	PointT<T> LeftTop() const {
		return PointT<T>(X, Y);
	}

	PointT<T> LeftBottom() const {
		return PointT<T>(X, GetBottom());
	}

	PointT<T> RightTop() const {
		return PointT<T>(GetRight(), Y);
	}

	PointT<T> RightBottom() const {
		return PointT<T>(GetRight(), GetBottom());
	}

	bool IsEmptyArea() const {
		return Width <= numeric_limits<T>::epsilon() || Width <= numeric_limits<T>::epsilon();
	}

	bool Equals(const RectT & rect) const {
		return X == rect.X && Y == rect.Y && Width == rect.Width && Height == rect.Height;
	}

	bool Contains(T x, T y) const {
		return x >= X && x < X+Width && y >= Y && y < Y+Height;
	}

	bool Contains(const PointT<T> &pt) const {
		return Contains(pt.X, pt.Y);
	}

	bool Contains(const RectT &rect) const {
		return (X <= rect.X) && (rect.GetRight() <= GetRight()) &&
			   (Y <= rect.Y) && (rect.GetBottom() <= GetBottom());
	}

	void Inflate(T dx, T dy) {
		X -= dx;
		Y -= dy;
		Width += 2*dx;
		Height += 2*dy;
	}

	void Inflate(const PointT<T> &point) {
		Inflate(point.X, point.Y);
	}

	bool Intersect(const RectT &rect) {
		return Intersect(*this, *this, rect);
	}

	static bool Intersect(RectT &c, const RectT &a, const RectT &b) {
		T right = min(a.GetRight(), b.GetRight());
		T bottom = min(a.GetBottom(), b.GetBottom());
		T left = max(a.GetLeft(), b.GetLeft());
		T top = max(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	bool IntersectsWith(const RectT &rect) const {
		return (GetLeft() < rect.GetRight() &&
				GetTop() < rect.GetBottom() &&
				GetRight() > rect.GetLeft() &&
				GetBottom() > rect.GetTop());
	}

	static bool Union(RectT &c, const RectT &a, const RectT &b) {
		T right = max(a.GetRight(), b.GetRight());
		T bottom = max(a.GetBottom(), b.GetBottom());
		T left = min(a.GetLeft(), b.GetLeft());
		T top = min(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	void Offset(const PointT<T> &point) {
		Offset(point.X, point.Y);
	}

	void Offset(T dx, T dy) {
		X += dx;
		Y += dy;
	}

	RectT Scale(double f) const {
		return RectT(static_cast<T>(X * f), static_cast<T>(Y * f), static_cast<T>(Width * f), static_cast<T>(Height * f));
	}

	RectT Scale(double fx, double fy) const {
		return RectT(static_cast<T>(X * fx), static_cast<T>(Y * fy), static_cast<T>(Width * fx), static_cast<T>(Height * fy));
	}

	Gdiplus::Rect ToDdiplusRect() const {
		return Gdiplus::Rect(INT(X), INT(Y), INT(Width), INT(Height));
	}
	Gdiplus::RectF ToDdiplusRectF() const {
		return Gdiplus::RectF(Gdiplus::REAL(X), Gdiplus::REAL(Y), Gdiplus::REAL(Width), Gdiplus::REAL(Height));
	}*/

};

} // guitk

