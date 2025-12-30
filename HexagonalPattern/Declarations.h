#pragma once
#include <vector>

struct Dimensions
{
	int width	= 0	;
	int height	= 0	;
};

struct BitmapImageData {
	std::vector<unsigned char> pixelData;
	int bitmapRowSize = 0;
	Dimensions imageSize = { 640, 360 };
};

struct Point
{
	const double x, y;
	Point(double x_, double y_) : x(x_), y(y_) {}
};

struct Orientation
{
	const double f0, f1, f2, f3, b0, b1, b2, b3, start_angle;
	Orientation(double f0_, double f1_, double f2_, double f3_, double b0_, double b1_, double b2_, double b3_, double start_angle_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), b0(b0_), b1(b1_), b2(b2_), b3(b3_), start_angle(start_angle_) {}
};

struct Layout
{
	Orientation orientation;
	const Point size, origin;
	Layout(Orientation orientation_, Point size_, Point origin_) : orientation(orientation_), size(size_), origin(origin_) {}
};

struct Hex
{
	int q, r, s;
	Hex(int q_, int r_, int s_) : q(q_), r(r_), s(s_) {
		if (q + r + s != 0) throw "q + r + s must be 0";
	}
};