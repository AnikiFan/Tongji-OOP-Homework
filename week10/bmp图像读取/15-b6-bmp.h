/* 2254298 大数据 范潇 */
#pragma once
#include<Windows.h>

/* 根据需要加入自己的定义 */
#define PALLETE_POS 54
struct palette
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
    unsigned char reserved;
};
class bitmap_image
{
protected:
    /* 根据需要加入自己的定义 */
    int _beg_pos;//10-13字节
    int _width;//18-21字节
    int _height;//22-25字节
    unsigned short _bit_per_pixel;//28-29字节
    int bit_per_row;
    int byte_per_row;
    char* _filename;
    
public:
    bitmap_image(const char*filename);
    int width() const;	//返回图片的宽度
    int height() const; //返回图片的高度
    unsigned int get_pixel(int row, int col) const; //返回指定点的RGB颜色

    /* 根据需要加入自己的定义 */

};