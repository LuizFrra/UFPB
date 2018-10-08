#include "prim.h"

int main(int argc, char const *argv[])
{
    Prim *Object = new Prim;
    Prim::OpenFile(Object, argv[1]);
    Prim::PrintMatrix(Object);

    
    return 0;
}
