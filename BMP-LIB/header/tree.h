#ifndef _TREE_
#define _TREE_

#include "/home/luiz/Desktop/BMP/header/readbmp.h"

typedef unsigned char uchar;
typedef uint32_t uint32;

struct node{
    uint32 frequency;
    uchar data;
    struct node *left, *right;
};



class tree_instance{
    private:
        struct node tree_bmp;
        std::fstream compress_bmp;
        std::fstream code_bmp;
        //int **huffcodes;
        uint32 *array_frequency; // A FREQUENCIA DE CADA LEDRA O ARRAY VAI DE 0 A 255
        int32_t *array_ordered; // CONTEM OS ELEMTNOS EM ORDEM DO MAIS FREQUENTE AO MENOS FREQUENTE;
        uint32 nbytes;
        int size;
        int hcode[256][256];
        static int allocate_in_tree(struct node *tree, int value, int freq, tree_instance *instance_tree, int secounter);
    public:
        tree_instance();
        //int hcode[256][256];
        static int start_huff_tree(tree_instance *instance_tree, libmp_instance *obj);
        static int create_huff_tree( tree_instance *instance_tree, int counter );
        static int order_bmp_data( tree_instance *instance_tree, int start, int counter );
        static int receive_bmp_data( tree_instance *instance_tree, libmp_instance *obj, int start, int size );
        static int return_bmp_data( tree_instance *instance_tree, int start );
        static int add_frequency(tree_instance *instance_tree, int start);
        static int print_code_tree(tree_instance *instance_tree, int nalpha);
        static int gen_bin_code(tree_instance *instance_tree, struct node *tree, int alpha, int counter);
        static int bin_file(tree_instance *instance_tree, libmp_instance *obj);
        //static int run_huff_tree(struct node *tree,int secounter);
        ~tree_instance();
};

#endif