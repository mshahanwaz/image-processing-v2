#include <bits/stdc++.h> 

using namespace std;

#define BMP_HEADER_SIZE 54

struct BMPImage {
	int width;
	int height;
	vector<unsigned char> pixels;
};

BMPImage readBMP(string filename) {
	ifstream file(filename, ios::binary);
	
	if (!file) { cerr << "Error: not able to open file" << endl; exit(1); }

	char header[BMP_HEADER_SIZE];
	file.read(header, BMP_HEADER_SIZE);

	int width = *(int*)&header[18];
	int height = *(int*)&header[22];

	vector<unsigned char> pixels(width * height * 3);
	file.read((char*)pixels.data(), pixels.size());

	file.close();

	return { width, height, pixels };
}

int main()
{
	BMPImage image = readBMP("../bmps/img.bmp");
	cout << "Width = " << image.width << endl;
	cout << "Height = " << image.height << endl;

	for (int i = 0; i < image.pixels.size(); i += 3) {
		unsigned char r = image.pixels[i];
		unsigned char g = image.pixels[i + 1];
		unsigned char b = image.pixels[i + 2];
		cout << "Pixel " << setw(2) << i / 3 << ": (" << setw(3) << (int)r << ", " << setw(3) << (int)g << ", " << setw(3) << (int)b << ")" << endl;
	}

	return 0;
}
