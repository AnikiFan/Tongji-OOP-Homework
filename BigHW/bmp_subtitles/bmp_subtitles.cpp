/* 2254298 大数据 范潇 */
#include<iostream>
#include<fstream>
#include"../include/class_aat.h"
#include"../include/common_text.h"
using namespace std;
enum OPT_ARGS {
	OPT_ARGS_BMPFILE = 0,
	OPT_ARGS_OUTFILE,
	OPT_ARGS_TRADITIONAL,
	OPT_ARGS_SUBTITLES,
	OPT_ARGS_POSX,
	OPT_ARGS_POSY,
	OPT_ARGS_COLOR,
	OPT_ARGS_STYLE
};
enum BMP_TYPE {
	BI = 0,
	HEX,
	MUL,
	ALL
};
#define INTERVAL 5
#define BLACK "000000"
#define ALPHA_PIXEL 16
#define INFO_LEN 54
#define BIT_PER_PIXEL_OFFSET 28
#define FILE_SIZE_OFFSET 2
#define CODE_OFFSET 0xA0
#define BLOCK_SIZE 4
#define WIDTH_OFFSET 18
#define HEIGHT_OFFSET 22
#define MODERN "HZK16"
#define TRADITIONAL "HZK16F"
#define ALPHA_SIZE 32
#define ALPHA_LEN 16
struct block
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
};
void get_info(ifstream& bmpfile, char*& info, char*& palette, char*& mat, int& bmp_type, int& width, int& height, int& palette_size, int& mat_size)
{
	info = new char[INFO_LEN];
	if (!info) {
		cout << "OVERFLOW" << endl;
		getchar();
		return;
	}
	bmpfile.read(info, INFO_LEN);
	unsigned short bit_per_pixel = *((unsigned short*)(info + BIT_PER_PIXEL_OFFSET));
	switch (bit_per_pixel) {
		case 1:
			bmp_type = BMP_TYPE::BI;
			palette_size = BLOCK_SIZE * 2;
			break;
		case 4:
			bmp_type = BMP_TYPE::HEX;
			palette_size = BLOCK_SIZE * 16;
			break;
		case 8:
			bmp_type = BMP_TYPE::MUL;
			palette_size = BLOCK_SIZE * 256;
			break;
		case 24:
			bmp_type = BMP_TYPE::ALL;
			palette_size = 0;
			break;
		default:
			cout << "TYPE ERROR!" << endl;
			cout << "input type:" << bit_per_pixel << endl;
			getchar();
			return;
			break;
	}
	if (palette_size) {
		palette = new char[palette_size];
		if (!palette) {
			cout << "OVERFLOW!" << endl;
			getchar();
			return;
		}
		bmpfile.read(palette, palette_size);
	}
	int file_size = *((int*)(info + FILE_SIZE_OFFSET));
	mat = new char[file_size - INFO_LEN - palette_size];
	mat_size = file_size - INFO_LEN - palette_size;
	if (!mat) {
		cout << "OVERFLOW!" << endl;
		getchar();
		return;
	}
	bmpfile.read(mat, file_size - INFO_LEN - palette_size);
	bmpfile.get();
	if (!bmpfile.eof()) {
		cout << "READ ERROR!" << endl;
		return;
	}
	width = *((int*)(info + WIDTH_OFFSET));
	height = *((int*)(info + HEIGHT_OFFSET));
	return;
}
void get_shape(char* const shape, const unsigned char low, const unsigned char high, const int traditional)
{
	int block_code = high - CODE_OFFSET, bit_code = low - CODE_OFFSET;
	string bank(traditional ? TRADITIONAL : MODERN);
	ifstream alpha_bank(bank, ios::in | ios::binary);
	if (!alpha_bank) {
		cout << "打开文件" << bank << "失败！" << endl;
		getchar();
		return;
	}
	alpha_bank.seekg(((block_code - 1) * 94 + bit_code - 1) * ALPHA_SIZE, ios::beg);
	alpha_bank.read(shape, ALPHA_SIZE);
	alpha_bank.close();
	return;
}
void locate(const int bmp_type, const int x, const int y, const int width, const int height, int& byte_pos, int& bit_pos)
{
	int bit_per_pixel;
	switch (bmp_type) {
		case BI:
			bit_per_pixel = 1;
			break;
		case HEX:
			bit_per_pixel = 4;
			break;
		case MUL:
			bit_per_pixel = 8;
			break;
		case ALL:
			bit_per_pixel = 24;
			break;
	}
	int byte_per_row;
	if ((bit_per_pixel * width) % 32)
		byte_per_row = ((bit_per_pixel * width) / 32) * 4 + 4;
	else
		byte_per_row = ((bit_per_pixel * width) / 32) * 4;
	byte_pos = (height - y) * byte_per_row + (x * bit_per_pixel) / 8;
	bit_pos = (x * bit_per_pixel) % 8;
}
void type(char* const mat, const char* const shape, const char* const palette, const int x, const int y, const string fg, int bmp_type, int width, int height)
{
	int byte_pos, bit_pos;
	block fg_color, black;
	if (bmp_type == ALL) {
		if (fg[0] >= '0' && fg[0] <= '9')
			fg_color.R = (fg[0] - '0') * 16;
		else
			fg_color.R = (fg[0] - 'A'+10) * 16;
		if (fg[1] >= '0' && fg[1] <= '9')
			fg_color.R+= (fg[1] - '0');
		else
			fg_color.R += (fg[1] - 'A'+10);

		if (fg[2] >= '0' && fg[2] <= '9')
			fg_color.G = (fg[2] - '0') * 16;
		else
			fg_color.G = (fg[2] - 'A'+10) * 16;
		if (fg[3] >= '0' && fg[3] <= '9')
			fg_color.G += (fg[3] - '0');
		else
			fg_color.G += (fg[3] - 'A'+10);

		if (fg[4] >= '0' && fg[4] <= '9')
			fg_color.B = (fg[4] - '0') * 16;
		else
			fg_color.B = (fg[4] - 'A'+10) * 16;
		if (fg[5] >= '0' && fg[5] <= '9')
			fg_color.B += (fg[5] - '0');
		else
			fg_color.B += (fg[5] - 'A'+10);
	}
	black.B = 0;
	black.G = 0;
	black.R = 0;
	int temp;
	for (int i = 0; i < ALPHA_LEN; i++)
		for (int j = 0; j < ALPHA_LEN; j++) {
			locate(bmp_type, x + j, y + i, width, height, byte_pos, bit_pos);
			if (bmp_type == ALL)
				if ((shape[(i * ALPHA_LEN + j) / 8] >> (7-(i * ALPHA_LEN + j)%8)) % 2)
					*(block*)(mat + byte_pos) = fg_color;
				else
					//*(block*)(mat + byte_pos) = black;
					;//不改变背景色
			else if ((shape[(i * ALPHA_LEN + j) / 8] >> (7-(i * ALPHA_LEN + j)%8)) % 2)
				switch (bmp_type)
				{
					case BI:
						temp = 1;
						temp <<= (7-bit_pos);
						temp = ~temp;
						mat[byte_pos] &= temp;
						break;
					case HEX:
						if (!bit_pos)
							mat[byte_pos] &= 0xF;
						else
							mat[byte_pos] &= 0xF0;
						break;
					case MUL:
						mat[byte_pos] = 0;
						break;
					default:
						break;
				}
		}
	return;
}
int main(int argc, char** argv)
{
	const string style[] = { "horizontal","vertical","" };
	args_analyse_tools args[] = {
		args_analyse_tools("--bmpfile",ST_EXTARGS_TYPE::str,1,string("")),
		args_analyse_tools("--outfile",ST_EXTARGS_TYPE::str,1,string("")),
		args_analyse_tools("--traditional",ST_EXTARGS_TYPE::boolean,0,false),
		args_analyse_tools("--subtitle",ST_EXTARGS_TYPE::str,1,string("")),
		args_analyse_tools("--posx",ST_EXTARGS_TYPE::int_with_error,1,1,0,1919),
		args_analyse_tools("--posy",ST_EXTARGS_TYPE::int_with_error,1,1,0,1079),
		args_analyse_tools("--color",ST_EXTARGS_TYPE::str,1,string("")),
		args_analyse_tools("--style",ST_EXTARGS_TYPE::str_with_set_error,1,0,style),
		args_analyse_tools()
	};
	int cur_argc, ret = 0;
	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		return -1;
	}
	/* 进入实际的功能调用，完成相应的功能 */
	ifstream bmpfile(args[OPT_ARGS_BMPFILE].get_string(), ios::in | ios::binary);
	if (!bmpfile) {
		cout << "文件" << args[OPT_ARGS_BMPFILE].get_string() << "打开失败！" << endl;
		bmpfile.close();
		return -1;
	}
	ofstream outfile(args[OPT_ARGS_OUTFILE].get_string(), ios::out | ios::binary);
	if (!outfile) {
		cout << "文件" << args[OPT_ARGS_OUTFILE].get_string() << "打开失败！" << endl;
		bmpfile.close();
		outfile.close();
		return -1;
	}
	char* info = nullptr, * palette = nullptr, * mat = nullptr, * shape = new char[ALPHA_SIZE];
	if (!shape) {
		cout << "OVERFLOW!" << endl;
		getchar();
		return -2;
	}
	int bmp_type, width, height, palette_size, mat_size;
	get_info(bmpfile, info, palette, mat, bmp_type, width, height, palette_size, mat_size);
	string fg = args[OPT_ARGS_COLOR].get_string();
	unsigned char high, low;
	if (bmp_type != ALL)
		fg = string(BLACK);
	int dx = (args[OPT_ARGS_STYLE].get_string() == "horizontal" ? INTERVAL + ALPHA_PIXEL : 0), dy = (args[OPT_ARGS_STYLE].get_string() == "vertical" ? INTERVAL + ALPHA_PIXEL : 0);
	int x = args[OPT_ARGS_POSX].get_int(), y = args[OPT_ARGS_POSY].get_int();
	for (int i = 0; i < (int)args[OPT_ARGS_SUBTITLES].get_string().length() / 2; i++) {
		low = args[OPT_ARGS_SUBTITLES].get_string()[2 * i + 1];
		high = args[OPT_ARGS_SUBTITLES].get_string()[2 * i];
		get_shape(shape, low, high, args[OPT_ARGS_TRADITIONAL].existed());
		type(mat, shape, palette, x, y, fg, bmp_type, width, height);
		x += dx;
		y += dy;
	}
	outfile.write(info, INFO_LEN);
	outfile.write(palette, palette_size);
	outfile.write(mat, mat_size);
	bmpfile.close();
	outfile.close();
	delete[]info;
	delete[]palette;
	delete[]mat;
	delete[]shape;
	return 0;
}