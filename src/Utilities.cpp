#include "header.h"
#include "Utilities.h"
#include "ImageManager.h"

std::vector<SimpleImage> Utilities::objectImages;
std::vector<SimpleImage> Utilities::objectImages2;
void Utilities::addAllimages()
{
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/warp.png"));					// 0
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/warp.png"));					// 1
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/blue1.png"));	// 2
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/cyan1.png"));	// 3
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/green1.png"));	// 4
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/grey1.png"));	// 5
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/orange1.png"));	// 6
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/pink1.png"));	// 7
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/red1.png"));	// 8
	objectImages.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/yellow1.png"));	// 9

	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/warp.png"));					// 0
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/warp.png"));					// 1
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/blue2.png"));	// 2
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/cyan2.png"));	// 3
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/green2.png"));	// 4
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/grey2.png"));	// 5
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/orange2.png"));// 6
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/pink2.png"));	// 7
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/red2.png"));	// 8
	objectImages2.push_back(ImageManager::loadImage("resources/img/Object/DeliciousFriut/yellow2.png"));// 9
}

bool Utilities::isPointInTriangleInt(int x1, int y1, int x2, int y2, int x3, int y3, int px, int py)
{
	int denominator = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);

	if (denominator == 0)
		return false;

	int a_numer = (y2 - y3) * (px - x3) + (x3 - x2) * (py - y3);
	int b_numer = (y3 - y1) * (px - x3) + (x1 - x3) * (py - y3);
	int c_numer = denominator - a_numer - b_numer;

	bool sameSign = (denominator > 0);

	return (sameSign ?
		(a_numer >= 0 && b_numer >= 0 && c_numer >= 0 &&
			a_numer <= denominator && b_numer <= denominator && c_numer <= denominator)
		:
		(a_numer <= 0 && b_numer <= 0 && c_numer <= 0 &&
			a_numer >= denominator && b_numer >= denominator && c_numer >= denominator));
}
