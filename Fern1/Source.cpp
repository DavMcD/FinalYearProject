#include <windows.h>
#include <ctime>
#include <string>

const int BMP_SIZE = 600, ITERATIONS = static_cast<int>(15e5);

class myBitmap {
public:
	myBitmap() : pen(NULL), brush(NULL), clr(0), wid(1) {}
	~myBitmap() {
		DeleteObject(pen); DeleteObject(brush);
		DeleteDC(hdc); DeleteObject(bmp);
	}
	bool create(int w, int h) {
		BITMAPINFO bi;
		ZeroMemory(&bi, sizeof(bi));
		bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
		bi.bmiHeader.biBitCount = sizeof(DWORD) * 8;
		bi.bmiHeader.biCompression = BI_RGB;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biWidth = w;
		bi.bmiHeader.biHeight = -h;
		HDC dc = GetDC(GetConsoleWindow());
		bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &pBits, NULL, 0);
		if (!bmp) return false;
		hdc = CreateCompatibleDC(dc);
		SelectObject(hdc, bmp);
		ReleaseDC(GetConsoleWindow(), dc);
		width = w; height = h;
		return true;
	}
	void clear(BYTE clr = 0) {
		memset(pBits, clr, width * height * sizeof(DWORD));
	}
	void setBrushColor(DWORD bClr) {
		if (brush) DeleteObject(brush);
		brush = CreateSolidBrush(bClr);
		SelectObject(hdc, brush);
	}
	void setPenColor(DWORD c) {
		clr = c; createPen();
	}
	void setPenWidth(int w) {
		wid = w; createPen();
	}
	void saveBitmap(std::string path) {
		BITMAPFILEHEADER fileheader;
		BITMAPINFO       infoheader;
		BITMAP           bitmap;
		DWORD            wb;
		GetObject(bmp, sizeof(bitmap), &bitmap);
		DWORD* dwpBits = new DWORD[bitmap.bmWidth * bitmap.bmHeight];
		ZeroMemory(dwpBits, bitmap.bmWidth * bitmap.bmHeight * sizeof(DWORD));
		ZeroMemory(&infoheader, sizeof(BITMAPINFO));
		ZeroMemory(&fileheader, sizeof(BITMAPFILEHEADER));
		infoheader.bmiHeader.biBitCount = sizeof(DWORD) * 8;
		infoheader.bmiHeader.biCompression = BI_RGB;
		infoheader.bmiHeader.biPlanes = 1;
		infoheader.bmiHeader.biSize = sizeof(infoheader.bmiHeader);
		infoheader.bmiHeader.biHeight = bitmap.bmHeight;
		infoheader.bmiHeader.biWidth = bitmap.bmWidth;
		infoheader.bmiHeader.biSizeImage = bitmap.bmWidth * bitmap.bmHeight * sizeof(DWORD);
		fileheader.bfType = 0x4D42;
		fileheader.bfOffBits = sizeof(infoheader.bmiHeader) + sizeof(BITMAPFILEHEADER);
		fileheader.bfSize = fileheader.bfOffBits + infoheader.bmiHeader.biSizeImage;
		GetDIBits(hdc, bmp, 0, height, (LPVOID)dwpBits, &infoheader, DIB_RGB_COLORS);
		HANDLE file = CreateFile(path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, &fileheader, sizeof(BITMAPFILEHEADER), &wb, NULL);
		WriteFile(file, &infoheader.bmiHeader, sizeof(infoheader.bmiHeader), &wb, NULL);
		WriteFile(file, dwpBits, bitmap.bmWidth * bitmap.bmHeight * 4, &wb, NULL);
		CloseHandle(file);
		delete[] dwpBits;
	}
	HDC getDC() const { return hdc; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
private:
	void createPen() {
		if (pen) DeleteObject(pen);
		pen = CreatePen(PS_SOLID, wid, clr);
		SelectObject(hdc, pen);
	}
	HBITMAP bmp; HDC    hdc;
	HPEN    pen; HBRUSH brush;
	void    *pBits; int    width, height, wid;
	DWORD    clr;
};
class fern {
public:
	void draw() 
	{
		for (int i = 0; i < 6; i++)
		{
			bmp.create(BMP_SIZE, BMP_SIZE);
			float x = 0, y = 0; HDC dc = bmp.getDC();
			int hs = BMP_SIZE >> 1;
			for (int f = 0; f < ITERATIONS; f++) {
				SetPixel(dc, hs + static_cast<int>(x * 55.f),
					BMP_SIZE - 15 - static_cast<int>(y * 55.f),
					RGB(static_cast<int>(rnd() * 80.f) + 20,
						static_cast<int>(rnd() * 128.f) + 128,
						static_cast<int>(rnd() * 80.f) + 30));
				getXY(x, y);
			}
			bmp.saveBitmap("./bf" + std::to_string(i) + ".bmp");
		}
	}
private:
	
	void getXY(float& x, float& y) 
	{
		srand(time(NULL));
		float LeftLeafCurve = 0.2f + (((rand() % 20) - 10) / 100.0f);
		float RightLeafCurve = .15f + (((rand() % 20) - 10) / 100.0f);
		float LeftLeafSize = .26f + (((rand() % 20) - 10) / 100.0f);
		float RightLeafSize = .26f + (((rand() % 20) - 10) / 100.0f);
		float LeftLeafThinness = .23f + (((rand() % 20) - 10) / 100.0f);
		float RightLeafThickness = .28f + (((rand() % 20) - 10) / 100.0f);
		float LeftAngleWithStem = .22f;
		float RightAngleWithStem = .24f;
		float LeftLeafSpawnPosition = 1.6f;
		float RightLeafSpawnPosition = .44f;
		float Spikiness = .85f;
		float Curviness = .04f;
		float Gravity = .04f;
		float Aggressiveness = .85f;
		float Size = 1.6f;


		float g, xl, yl;
		g = rnd();
		if (g < .01f) { xl = 0; yl = .16f * y; }
		else if (g < .07f) {
			xl = LeftLeafCurve * x - LeftLeafSize * y;
			yl = LeftLeafThinness * x + LeftAngleWithStem * y + LeftLeafSpawnPosition;
		}
		else if (g < .14f) {
			xl = -RightLeafCurve * x + RightLeafThickness* y;
			yl = RightLeafSize * x + RightAngleWithStem * y + RightLeafSpawnPosition;
		}
		else {
			xl = Spikiness * x + Curviness * y;
			yl = -Gravity * x + Aggressiveness * y + Size;
		}
		x = xl; y = yl;
	}
	float rnd() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
	myBitmap bmp;
};
int main(int argc, char* argv[]) {
	srand(static_cast<unsigned>(time(0)));
	fern f; f.draw(); 
	return 0;
}