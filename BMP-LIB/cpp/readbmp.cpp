#include "/home/luiz/Desktop/BMP/header/readbmp.h"

libmp_instance::libmp_instance()
{   
    std::memset(&bmpheader, 0, sizeof(bmpheader));
    std::memset(&buffer, 0, sizeof(buffer));
}

int libmp_instance::open_bmp(libmp_instance *instance_bmp, char const **argv)
{   
    instance_bmp->bmp_file.open(argv[1], std::fstream::in | std::fstream::binary);
    
    return instance_bmp->bmp_file.is_open() == 1 ? 1 : 0 ;
}

int libmp_instance::get_size(libmp_instance *instance_bmp)
{
    instance_bmp->bmp_file.seekg(0, instance_bmp->bmp_file.end);
    int lenght = instance_bmp->bmp_file.tellg();
    instance_bmp->bmp_file.seekg(0, instance_bmp->bmp_file.beg);
    
    return lenght;
}

int libmp_instance::read_file(libmp_instance *instance_bmp)
{
    instance_bmp->buffer = new uchar[get_size(instance_bmp)];
    instance_bmp->buffer[0] = 0;
    instance_bmp->bmp_file.read((char*)instance_bmp->buffer, get_size(instance_bmp));
    return instance_bmp->buffer[0] == 0 ? 0 : 1;
}

libmp_instance::~libmp_instance()
{
    delete[] buffer;
    bmp_file.close();
}



