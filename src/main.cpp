#include <iostream> 
#include "BMP.hpp"

using namespace std;

void createBWImage(int, int);
void extractMatrixFromImage(string);

// Main program
int main() 
{
	try 
	{
		// BMP::Image image;
		// BMP::read(image, "../bmps/img.bmp");
		// BMP::debug(image);
		// createBlackWhiteImage(32, 16); // width x height
		extractMatrixFromImage("../bmps/new.bmp");
	} 
	catch(const char* e) 
	{
		cerr << "Error: " << e << endl;
	}

	return 0;
}

// Extract matrix from image
void extractMatrixFromImage(string filename) {
	BMP::Image image;
	BMP::read(image, filename);

	int width = image.width;
	int height = image.height;
	int matrix[height][width];

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = (int)((image.pixelData[i][j].r + image.pixelData[i][j].g + image.pixelData[i][j].b) / 3) > 0;
			cout << matrix[i][j] << " \n"[j == width - 1];
		}
	}
}

// Black and white image from matrix
void createBWImage(int width, int height) {
	uint8_t color[2] = { 255, 0 };

	uint8_t input[16][32] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	vector<vector<BMP::Pixel>> matrix(height, vector<BMP::Pixel>(width));

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (input[i][j]) { matrix[i][j] = (BMP::Pixel){ .r = color[0], .g = color[0], .b = color[0] }; }
			else { matrix[i][j] = (BMP::Pixel){ .r = color[1], .g = color[1], .b = color[1] }; }
		}
	}

	BMP::write("../bmps/new.bmp", matrix, width, height);
}
