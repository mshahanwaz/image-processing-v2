#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#pragma pack( push, 1 )

// 14 bytes
struct FileHeader 
{
	uint16_t type{ 0x4d42 };
	uint32_t size{ 0 };
	uint16_t reserved1{ 0 };
	uint16_t reserved2{ 0 };
	uint32_t offset{ 0 };
};

// 40 bytes
struct ImageHeader 
{
	uint32_t size{ 0 };
	uint32_t width{ 0 };
	uint32_t height{ 0 };
	uint16_t planes{ 1 };
	uint16_t bits_per_pixel{ 0 };
	uint32_t compression{ 0 };
	uint32_t image_size{ 0 };
	uint32_t x_resolution{ 0 };
	uint32_t y_resolution{ 0 };
	uint32_t colors_used{ 0 };
	uint32_t important_colors{ 0 };
};

// RGB format
struct Pixel
{
	uint8_t r{ 0 };
	uint8_t g{ 0 };
	uint8_t b{ 0 };
};

// Main BMP image structure
struct BMPImage 
{
	FileHeader fileHeader;
	ImageHeader imageHeader;
	int width;
	int height;
	vector<vector<Pixel>> pixelData;
};

#pragma pack( pop )

// Debugging
void printImageInfo(BMPImage image) 
{
	cout << "---" << endl;
	cout << "File Header" << endl;
	cout << "---" << endl;
	cout << "Type = " << (char)image.fileHeader.type << (char)(image.fileHeader.type >> 8) << endl;
	cout << "Size = " << image.fileHeader.size << endl;
	cout << "Reserved1 = " << image.fileHeader.reserved1 << endl;
	cout << "Reserved2 = " << image.fileHeader.reserved2 << endl;
	cout << "Offset = " << image.fileHeader.offset << endl;
	cout << endl;
	cout << "---" << endl;
	cout << "Image Header" << endl;
	cout << "---" << endl;
	cout << "Header size = " << image.imageHeader.size << endl;
	cout << "Width = " << image.width << endl;
	cout << "Height = " << image.height << endl;
	cout << "Color planes = " << image.imageHeader.planes << endl;
	cout << "Bits per pixel = " << image.imageHeader.bits_per_pixel << endl;
	cout << "Compression = " << image.imageHeader.compression << endl;
	cout << "Image size = " << image.imageHeader.image_size << endl;
	cout << "Horizontal resolution = " << image.imageHeader.x_resolution << endl;
	cout << "Vertical resolution = " << image.imageHeader.y_resolution << endl;
	cout << "Colors used = " << image.imageHeader.colors_used << endl;
	cout << "Important colors = " << image.imageHeader.important_colors << endl;
	cout << endl;

	int ans = 0;
	cout << "Print pixel array? - ";
	cin >> ans;
	if (ans == 0) return;

	cout << "---" << endl;
	cout << "BMP pixel array" << endl;
	cout << "---" << endl;
	for (size_t i = 0; i < image.height; ++i) {
		for (size_t j = 0; j < image.width; ++j) {
			int r = image.pixelData[i][j].r;
			int g = image.pixelData[i][j].g;
			int b = image.pixelData[i][j].b;
			cout << "(";
			cout << setw(3) << r;
			cout << ", ";
			cout << setw(3) << g;
			cout << ", ";
			cout << setw(3) << b;
			cout << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

// Reading a BMP image file
BMPImage readBMP(const string& filename) 
{
	ifstream file(filename, ios::binary);

	if (!file) { throw "Cannot open file"; }

	BMPImage image;

	file.read(reinterpret_cast<char*>(&image.fileHeader), sizeof(FileHeader));
	file.read(reinterpret_cast<char*>(&image.imageHeader), sizeof(ImageHeader));

	if (image.fileHeader.type != 0x4d42) { throw "Not a BMP file"; }

	image.width = image.imageHeader.width;
	image.height = image.imageHeader.height;

	int row_size = ((image.imageHeader.bits_per_pixel * image.width + 31) / 32) * 4;
	int pixelArraySize = row_size * image.height;

	image.pixelData.resize(image.height);

	for (int i = image.pixelData.size() - 1; i >= 0; --i) {
		image.pixelData[i].resize(row_size);
		file.read(reinterpret_cast<char*>(image.pixelData[i].data()), row_size);
	}

	file.close();

	return image;
}

// Writing a BMP image file
void writeBMP(const string& filename, vector<vector<Pixel>>& pixelData, int width, int height)
{
	ofstream file(filename, ios::binary);
	
	if (!file) { throw "Unable to create file"; }

	FileHeader fileHeader;
	ImageHeader imageHeader;

	int row_size = ((width * 24 + 31) / 32) * 4;

	fileHeader = (FileHeader){
		.type = 0x4d42,
		.size = (uint32_t)(54 + row_size * height),
		.reserved1 = 0,
		.reserved2 = 0,
		.offset = 54
	};

	imageHeader = (ImageHeader){
		.size = 40,
		.width = (uint32_t)width,
		.height = (uint32_t)height,
		.planes = 1,
		.bits_per_pixel = 24,
		.compression = 0,
		.image_size = (uint32_t)(row_size * height),
		.x_resolution = 0,
		.y_resolution = 0,
		.colors_used = 0,
		.important_colors = 0
	};

	file.write(reinterpret_cast<char*>(&fileHeader), sizeof(FileHeader));
	file.write(reinterpret_cast<char*>(&imageHeader), sizeof(ImageHeader));

	for (int i = pixelData.size() - 1; i >= 0; --i) {
		file.write(reinterpret_cast<char*>(pixelData[i].data()), row_size);
	}

	file.close();
}

// Main program
int main() 
{
	try {
		BMPImage image = readBMP("../bmps/test1.bmp");
		printImageInfo(image);
		writeBMP("../bmps/new.bmp", image.pixelData, image.width, image.height);
	} catch(const char* e) {
		cerr << "Error: " << e << endl;
	}

	return 0;
}
