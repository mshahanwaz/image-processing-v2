#include <iostream> 
#include <vector>
#include "BMP.hpp"

using namespace std;

void createBWImage(int, int);
vector<vector<int>> extractMatrixFromImage(string);
vector<vector<int>> compressMatrix(vector<vector<int>>);

// Main program
int main() 
{
	try 
	{
		// BMP::Image image;
		// BMP::read(image, "../bmps/img.bmp");
		// BMP::debug(image);
		// createBlackWhiteImage(32, 16); // width x height
		vector<vector<int>> matrix = compressMatrix(extractMatrixFromImage("../bmps/new.bmp"));
	} 
	catch(const char* e) 
	{
		cerr << "Error: " << e << endl;
	}

	return 0;
}

// Compress matrix to coordinate matrix
vector<vector<int>> compressMatrix(vector<vector<int>> matrix) 
{
	vector<vector<int>> compressed;
	for (int i = 0; i < (int)matrix.size(); ++i) {
		for (int j = 0; j < (int)matrix[i].size(); ++j) {
			if (matrix[i][j]) { compressed.push_back({ i, j }); }
		}
	}

	cout << "{";
	for (int i = 0; i < (int)compressed.size(); ++i) {
		cout << "{" << compressed[i][0] << ", " << compressed[i][1] << "}";
		if (i < (int)compressed.size() - 1) { cout << ", "; }
	}
	cout << "}" << endl;

	return compressed;
}

// Extract matrix from image
vector<vector<int>> extractMatrixFromImage(string filename) 
{
	BMP::Image image;
	BMP::read(image, filename);

	int width = image.width;
	int height = image.height;
	vector<vector<int>> matrix(image.height, vector<int>(image.width));

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = (int)((image.pixelData[i][j].r + image.pixelData[i][j].g + image.pixelData[i][j].b) / 3) > 0;
		}
	}

	return matrix;
}

// Black and white image from matrix
void createBWImage(int width, int height) 
{
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
			if (input[i][j]) { 
				matrix[i][j] = (BMP::Pixel){ .r = color[0], .g = color[0], .b = color[0] }; 
			} else { 
				matrix[i][j] = (BMP::Pixel){ .r = color[1], .g = color[1], .b = color[1] }; 
			}
		}
	}

	BMP::write("../bmps/new.bmp", matrix, width, height);
}
