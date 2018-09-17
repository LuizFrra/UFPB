#include "/home/luiz/Desktop/BMP/header/tree.h"

tree_instance::tree_instance(){
   
    std::memset(&tree_bmp, 0, sizeof(struct node));
    tree_bmp.left = new node;
    tree_bmp.right = new node; // DESTRUIR RECURSIVAMENTE
    array_frequency = new uint32[256];
    array_ordered = new int32_t[256];
    std::memset(array_frequency, 0, 1024);
    std::memset(array_ordered, -1, 1024);
    std::memset(&hcode, -1, 262144);
    compress_bmp.open("compress.txt", std::fstream::app | std::fstream::in | std::fstream::out | std::fstream::binary);
    code_bmp.open("code.txt", std::fstream::app | std::fstream::in | std::fstream::out | std::fstream::binary);
}

int tree_instance::receive_bmp_data( tree_instance *instance_tree, libmp_instance *obj, int start, int size ){
    
    if( start == size ){
        instance_tree->size = size;
        return 0;
    }
    else{
        instance_tree->array_frequency[ (uint32)obj->buffer[start] ] ++;
        receive_bmp_data( instance_tree, obj, start = start + 1, size );
    }
}

int tree_instance::return_bmp_data(tree_instance *instance_tree, int start){
    
    if(start == 256)
        return 0;
    else{

        if( instance_tree->array_frequency[ start ] != 0 )
            instance_tree->array_ordered[start] = instance_tree->array_frequency[start];
        
        return_bmp_data(instance_tree, start =  start + 1);
    }
    return 0;
}
//FUNCAO QUE CRIA UM ARRAY ONDE O PRIMEIRO ELEMENTO É O BYTE MAIS FREQUENTE E O ULTIMO O BYTE MENOS FREQUENTE
int tree_instance::order_bmp_data( tree_instance *instance_tree, int start, int counter ){
   
    for(counter = 0; counter < 256; counter++)
        if(instance_tree->array_ordered[counter] != -1){
            instance_tree->array_ordered[start] = counter;
            start++;
            if(instance_tree->array_ordered[counter] != counter)
                instance_tree->array_ordered[counter] = -1;
        }
    
    for(counter = 0; counter < start - 1; counter++)
        for(instance_tree->nbytes = 0; instance_tree->nbytes < start; instance_tree->nbytes++)
            if(instance_tree->array_frequency[instance_tree->array_ordered[instance_tree->nbytes]] < instance_tree->array_frequency[instance_tree->array_ordered[instance_tree->nbytes + 1]]){
                int swapholder = instance_tree->array_ordered[instance_tree->nbytes+1];
                instance_tree->array_ordered[instance_tree->nbytes + 1] = instance_tree->array_ordered[instance_tree->nbytes];
                instance_tree->array_ordered[instance_tree->nbytes] = swapholder; 
            }
    
    return 0;
}
//FUCANO QUE CRIA O PRIMEIRO NO* E POE A CONFIGURAÇÃO INICIAL PADRAO DA ARVORE
int tree_instance::start_huff_tree(tree_instance *instance_tree, libmp_instance *obj){
   
    instance_tree->tree_bmp.frequency = instance_tree->size;
    instance_tree->tree_bmp.data = 0;
    instance_tree->tree_bmp.left->frequency = instance_tree->size - add_frequency(instance_tree, 1);
    instance_tree->tree_bmp.left->data = 0;
    instance_tree->tree_bmp.left->left = NULL;
    instance_tree->tree_bmp.left->right = NULL;
    instance_tree->tree_bmp.right->frequency = instance_tree->size - add_frequency(instance_tree, 0);
    instance_tree->tree_bmp.right->data = 0;
    instance_tree->tree_bmp.right->left = NULL;
    instance_tree->tree_bmp.right->right = NULL;
   
    return 0;
}
//FUNCAO RESPONSAVEL POR CRIAR A ARVORE PASSANDO AS LETRAS COMO PARAMETRO
int tree_instance::create_huff_tree( tree_instance *instance_tree, int counter ){
    
    if(counter == instance_tree->nbytes)
        return 0;
    else if( counter % 2 == 0){
        allocate_in_tree(instance_tree->tree_bmp.left, instance_tree->array_ordered[counter], instance_tree->array_frequency[instance_tree->array_ordered[counter]], instance_tree, counter);
        create_huff_tree(instance_tree, counter = counter + 1);
    }else{
        allocate_in_tree(instance_tree->tree_bmp.right, instance_tree->array_ordered[counter], instance_tree->array_frequency[instance_tree->array_ordered[counter]], instance_tree, counter);
        create_huff_tree(instance_tree, counter = counter + 1);
    }
}
// FUNCAO QUE ALOCA AS VARIAVEIS NO NO*
int tree_instance::allocate_in_tree(struct node *tree, int value, int freq, tree_instance *instance_tree, int secounter){

    if(tree->left == NULL && tree->right == NULL){
        tree->left = new node;
        tree->right = new node;
        tree->left->frequency = freq;
        tree->left->data = value;
        tree->right->frequency = add_frequency(instance_tree, secounter);
        tree->right->left = NULL;
        tree->right->right = NULL;

        return 0;

    }else{
        allocate_in_tree(tree->right, value, freq, instance_tree, secounter);
    }
}
// FUNCAO QUE ADICIONAR A FREQUENCIA DE CADA LETRA EM UM ARRAY ONDE CADA POSICAO É A LETRA
int tree_instance::add_frequency(tree_instance *instance_tree, int start){
    int add = 0;
    if(start % 2 == 0){
        for(int i = start; i <= instance_tree->nbytes; i+=2)
            add = add + instance_tree->array_frequency[instance_tree->array_ordered[i]];
        return add;
    }else if(start % 2 == 1)
        for(int i = start; i <= instance_tree->nbytes; i+=2)
            add = add + instance_tree->array_frequency[instance_tree->array_ordered[i]];       
        return add;
    
}
// FUNCAO RESPONSAVEL POR GERENCIAR AS ENTRADAS DOS NOS
int tree_instance::print_code_tree(tree_instance *instance_tree, int nalpha){
    if(nalpha >= instance_tree->nbytes)
        return 0;
    else{
        if(nalpha % 2 == 0){
            if(instance_tree->array_ordered[nalpha] != 0)
                instance_tree->code_bmp << (char*)&instance_tree->array_ordered[nalpha] << 0;
            else
                instance_tree->code_bmp << 0 << 0;

            instance_tree->hcode[instance_tree->array_ordered[nalpha]][0] = 0;
            gen_bin_code(instance_tree, instance_tree->tree_bmp.left, instance_tree->array_ordered[nalpha], 0);
            print_code_tree(instance_tree, nalpha = nalpha + 1);
        }else{
            if(instance_tree->array_ordered[nalpha] != 0)
                instance_tree->code_bmp << (char*)&instance_tree->array_ordered[nalpha] << 1;
            else
                instance_tree->code_bmp << 0 << 1;

            instance_tree->hcode[instance_tree->array_ordered[nalpha]][0] = 1;
            gen_bin_code(instance_tree, instance_tree->tree_bmp.right, instance_tree->array_ordered[nalpha], 0);
            print_code_tree(instance_tree, nalpha = nalpha + 1);
        }
    }
}
// FUNCAO RESPONSAVEL PRO GUARDAR O CODIGO DE CADA LETRA NA VARIAVEL HCODE
int tree_instance::gen_bin_code(tree_instance *instance_tree, struct node *tree, int alpha, int counter){
    counter += 1;
    if(tree->left->data == uchar(alpha)){
        instance_tree->code_bmp << 0 << "\n";
        instance_tree->hcode[alpha][counter] = 0;
        return 0;
    }
    else{
        instance_tree->code_bmp << 1;
        instance_tree->hcode[alpha][counter] = 1;
        gen_bin_code(instance_tree, tree->right, alpha, counter);
    }
}

int tree_instance::bin_file(tree_instance *instance_tree, libmp_instance *obj){
    //int newline = 0;
    for(int byteN = 0; byteN <= instance_tree->size; byteN++ )
        for(int ind = 0; instance_tree->hcode[+obj->buffer[byteN]][ind] != -1 ; ind++)
            instance_tree->compress_bmp.write((char*)&instance_tree->hcode[+obj->buffer[byteN]][ind], 1);

    uchar *b = new uchar[instance_tree->size];
    instance_tree->compress_bmp.seekg(0, instance_tree->compress_bmp.beg);

    return 0;
}

tree_instance::~tree_instance(){
    delete [] array_frequency;
    delete [] array_ordered;
    //DELETER OS NO RECURSIVAMENTE, DO MAIS PROFUNDO AO MENOS PROFUNDO
    code_bmp.close();
    compress_bmp.close();
}