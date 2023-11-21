/* 2254298 ������ ���� */
#pragma once
#include<Windows.h>

/* ������Ҫ�����Լ��Ķ��� */
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
    /* ������Ҫ�����Լ��Ķ��� */
    int _beg_pos;//10-13�ֽ�
    int _width;//18-21�ֽ�
    int _height;//22-25�ֽ�
    unsigned short _bit_per_pixel;//28-29�ֽ�
    int bit_per_row;
    int byte_per_row;
    char* _filename;
    
public:
    bitmap_image(const char*filename);
    int width() const;	//����ͼƬ�Ŀ��
    int height() const; //����ͼƬ�ĸ߶�
    unsigned int get_pixel(int row, int col) const; //����ָ�����RGB��ɫ

    /* ������Ҫ�����Լ��Ķ��� */

};