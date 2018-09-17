#include "/home/luiz/Desktop/BMP/header/libmp.h"



int main(int argc, char const **argv)
{   
    tree_instance t;
    libmp_instance p;
    //int size = libmp_instance::get_size(&p);
    libmp_instance::open_bmp(&p, argv);
    libmp_instance::read_file(&p);
    int size = libmp_instance::get_size(&p);
    tree_instance::receive_bmp_data(&t, &p, 0, size);
    tree_instance::return_bmp_data(&t, 0);
    tree_instance::order_bmp_data(&t, 0, 0);
    tree_instance::start_huff_tree(&t, &p);
    tree_instance::create_huff_tree(&t, 0);
    tree_instance::print_code_tree(&t, 0);
    tree_instance::bin_file(&t, &p);
    //system("read -p 'Press Enter to continue...' var");

    return 0;
}

