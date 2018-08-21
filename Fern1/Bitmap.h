#pragma once
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class Bitmap
{
public:
	Bitmap();
	~Bitmap();
	bool create(int w, int h);
	void clear(BYTE clr = 0);
	void setBrushColor(DWORD bClr);
	void setPenColor(DWORD c);
	void setPenWidth(int w);
	void saveBitmap(std::string path);
	HDC getDC() const { return hdc; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
private:
	void createPen();
	HBITMAP bmp; HDC    hdc;
	HPEN    pen; HBRUSH brush;
	void    *pBits; int    width, height, wid;
	DWORD    clr;
};

