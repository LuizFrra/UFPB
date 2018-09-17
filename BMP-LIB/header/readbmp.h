#ifndef _READ_BMP_
#define _READ_BMP_

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

typedef unsigned char uchar;
typedef uint32_t uint32;

typedef struct {
    //BMP HEADER
    uchar id_bmp[2];
    uchar size_bmp[4];
    uchar unused_bmp[4];
    uchar position_array_pixels_bmp[4];
    //BMP DIB HEADER
    uchar bytes_dib_header_bmp[4];
    uchar width_bmp[4];
    uchar height_bmp[4];
    uchar color_planes_bmp[2];
    uchar bits_per_pixels_bmp[2];
    uchar compression_bmp[4];
    uchar size_array_pixels_bmp[4];
    uchar pixel_m_horizontal_bmp[4];
    uchar pixel_m_vertical_bmp[4];
    uchar color_palette_bmp[4];
    uchar important_color_bmp[4];
} HEADER;

class libmp_instance{
    private:
        HEADER bmpheader;
        std::fstream bmp_file;
    public:
        libmp_instance();
        static int get_size(libmp_instance *instance_bmp);
        static int open_bmp(libmp_instance *instance_bmp, char const **argv);
        static int read_file(libmp_instance *instance_bmp);
        uchar *buffer;
        ~libmp_instance();

};



#endif
