/* 2254298 大数据 范潇 */
#include"15-b6-bmp.h"
#include <fstream>
#include<iostream>
using namespace std;
bitmap_image::bitmap_image(const char* filename)
{
	ifstream bmp(filename, ios::in | ios::binary);
	if (!bmp) {
		bmp.close();
	}
	else {
		bmp.seekg(10, ios::beg);
		bmp.read((char*)(&_beg_pos), 4);
		bmp.seekg(18, ios::beg);
		bmp.read((char*)(&_width), 4);
		bmp.seekg(22, ios::beg);
		bmp.read((char*)(&_height), 4);
		bmp.seekg(28, ios::beg);
		bmp.read((char*)(&_bit_per_pixel), 2);
		_filename = (char*)filename;
	}
}
int bitmap_image::width() const
{
	return _width;
}
int bitmap_image::height() const
{
	return _height;
}
unsigned int bitmap_image::get_pixel(int row, int col) const
{
	ifstream bmp(_filename, ios::in | ios::binary);
	if (!bmp)
		return -1;
	bmp.seekg(_beg_pos, ios::beg);
	int bit_per_row = _width * _bit_per_pixel;
	if (bit_per_row % 32) {//每行填充至4字节的倍数
		bit_per_row += 32;
		bit_per_row /= 32;
		bit_per_row *= 32;
	}
	int byte_per_row = bit_per_row / 8;
	bmp.seekg(byte_per_row * (_height - 1 - row), ios::cur);
	char ind = 0;
	palette _RGB;
	long long now = 0;
	switch (_bit_per_pixel) {
		case 1:
			bmp.seekg(col / 8, ios::cur);
			bmp.read(&ind, 1);
			ind >>= (7 - col % 8);
			ind &= 1;
			bmp.seekg(PALLETE_POS, ios::beg);
			bmp.seekg(ind * 4, ios::cur);
			bmp.read((char*)&_RGB, 4);
			//BGR!!!
			return RGB(_RGB.R, _RGB.G, _RGB.B);
			break;

		case 4:
			bmp.seekg(col / 2, ios::cur);
			bmp.read(&ind, 1);
			ind >>= ((!(col % 2)) * 4);
			ind &= 15;
			bmp.seekg(PALLETE_POS, ios::beg);
			bmp.seekg(ind * 4, ios::cur);
			bmp.read((char*)&_RGB, 4);
			return RGB(_RGB.R, _RGB.G, _RGB.B);
			break;
		case 8:
			bmp.seekg(col, ios::cur);
			bmp.read(&ind, 1);
			bmp.seekg(PALLETE_POS, ios::beg);
			bmp.seekg(((unsigned char)ind) * 4, ios::cur);
			bmp.read((char*)&_RGB, 4);
			return RGB(_RGB.R, _RGB.G, _RGB.B);
			break;
		case 24:
			bmp.seekg(3 * col, ios::cur);
			bmp.read((char*)&_RGB, 4);
			return RGB(_RGB.R, _RGB.G, _RGB.B);
			break;
		default:
			break;
	}
	bmp.close();
	return -1;
}