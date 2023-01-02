#include <bits/stdc++.h> 

using namespace std;

#pragma pack( push, 1 )

// 14 bytes
struct FileHeader {
	uint16_t type;
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
};

// 40 bytes
struct ImageHeader {
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bits_per_pixel;
	uint32_t compression;
	uint32_t image_size;
	uint32_t x_resolution;
	uint32_t y_resolution;
	uint32_t colors_used;
	uint32_t important_colors;
};

// Main BMP image structure
struct BMPImage {
	FileHeader fileHeader;
	ImageHeader imageHeader;
	vector<uint8_t> pixelData;
};

#pragma pack( pop )

// Debugging
void printImageInfo(BMPImage image) 
{
	cout << "---" << endl;
	cout << "File Header" << endl;
	cout << "---" << endl;
	cout << "Type = " << image.fileHeader.type << (image.fileHeader.type >> 8) << endl;
	cout << "Size = " << image.fileHeader.size << endl;
	cout << "Reserved1 = " << image.fileHeader.reserved1 << endl;
	cout << "Reserved2 = " << image.fileHeader.reserved2 << endl;
	cout << "Offset = " << image.fileHeader.offset << endl;
	cout << endl;
	cout << "---" << endl;
	cout << "Image Header" << endl;
	cout << "---" << endl;
	cout << "Header size = " << image.imageHeader.size << endl;
	cout << "Width = " << image.imageHeader.width << endl;
	cout << "Height = " << image.imageHeader.height << endl;
	cout << "Color planes = " << image.imageHeader.planes << endl;
	cout << "Bits per pixel = " << image.imageHeader.bits_per_pixel << endl;
	cout << "Compression = " << image.imageHeader.compression << endl;
	cout << "Image size = " << image.imageHeader.image_size << endl;
	cout << "Horizontal resolution = " << image.imageHeader.x_resolution << endl;
	cout << "Vertical resolution = " << image.imageHeader.y_resolution << endl;
	cout << "Colors used = " << image.imageHeader.colors_used << endl;
	cout << "Important colors = " << image.imageHeader.important_colors << endl;
	cout << endl;
	cout << "---" << endl;
	cout << "BMP pixel array" << endl;
	cout << "---" << endl;
	for (size_t i = 0; i < image.pixelData.size(); i += 3) {
		int r = image.pixelData[i];
		int g = image.pixelData[i + 1];
		int b = image.pixelData[i + 2];
		cout << setw(3) << r;
		cout << ", ";
		cout << setw(3) << g;
		cout << ", ";
		cout << setw(3) << b;
		cout << endl;
	}
}

// Main program
int main() 
{
	try {
		ifstream file("../bmps/img.bmp", ios::binary);
		
		if (!file) { throw "Cannot open file"; }

		BMPImage image;

		file.read(reinterpret_cast<char*>(&image.fileHeader), sizeof(FileHeader));
		file.read(reinterpret_cast<char*>(&image.imageHeader), sizeof(ImageHeader));

		if (image.fileHeader.type != 0x4d42) { throw "Not a BMP file"; }

		int data_size = image.imageHeader.width * image.imageHeader.height * 3;
		image.pixelData.resize(data_size);
		file.read(reinterpret_cast<char*>(image.pixelData.data()), data_size);
		file.close();

		printImageInfo(image);
	} catch(const char* e) {
		cerr << "Error: " << e << endl;
	}

	return 0;
}
