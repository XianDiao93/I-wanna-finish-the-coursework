#pragma once
#include "SimpleImage.h"
#include <vector>
class Utilities
{
public:
	typedef struct
	{
		int x;
		int y;
	}coordinate;
	static std::vector<SimpleImage> objectImages;
	static std::vector<SimpleImage> objectImages2;
	static void addAllimages();
	static bool isPointInTriangleInt(int x1, int y1,
		int x2, int y2,
		int x3, int y3,
		int px, int py);
};

