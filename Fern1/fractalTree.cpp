#include "fractalTree.h"



fractalTree::fractalTree()
{
	_ang = DegToRadian(24.0f);
}

void fractalTree::create(Bitmap * bmp)
{
	_bmp = bmp;
	float line_len = 130.0f;

	vector2Helper sp(_bmp->getWidth() / 2, _bmp->getHeight() - 1);
	MoveToEx(_bmp->getDC(), sp.x, sp.y, NULL);
	sp.y -= static_cast<int>(line_len);
	LineTo(_bmp->getDC(), sp.x, sp.y);

	drawRL(&sp, line_len, 0, true);
	drawRL(&sp, line_len, 0, false);
}

float fractalTree::DegToRadian(float degree)
{
	return degree * (PI / 180.0f);
}

void fractalTree::render()
{
	std::ofstream fernDataFile("TreeData.txt");


	//this essentially "deselects" the previous generation by resetting the bools that determine which values will be chosen
	for (int i = 0; i < 20; i++)
	{
		fernDataFile << "0 ";
	}
	fernDataFile << std::endl;

	bmp.create(640, 512);
	bmp.setPenColor(RGB(255, 255, 0));


	for (int i = 0; i < 20; i++)
	{

		create(&bmp);
		bmp.saveBitmap("./tree" + std::to_string(i) + ".bmp");
		bmp.clear();
		//TODO write data to file
		std::cout << std::to_string((i * 5)) << "% Complete" << std::endl;
	}
	BitBlt(GetDC(GetConsoleWindow()), 0, 20, 648, 512, bmp.getDC(), 0, 0, SRCCOPY);
	system("PAUSE");
}

void fractalTree::drawRL(vector2Helper* sp, float line_len, float a, bool rg)
{
	float left_line = line_len;
	line_len *= (0.75f - (std::rand() % 4) / 10.0f);
	left_line *= 0.75f;

	if (line_len < 2.0f) return;

	MoveToEx(_bmp->getDC(), sp->x, sp->y, NULL);
	vector2Helper r(0, static_cast<int>(line_len));

	if (rg) a -= _ang;
	else a += _ang;

	r.rotate(a);
	r.x += sp->x; r.y = sp->y - r.y;

	LineTo(_bmp->getDC(), r.x, r.y);

	drawRL(&r, line_len, a, true);
	drawRL(&r, left_line, a, false);
}


fractalTree::~fractalTree()
{
}
