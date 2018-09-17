#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

int size(std::fstream &file);

int comparearr(int array1[256], int array2[][256], int alpha, int limit);
 
int main(int argc, char const *argv[])
{   
    unsigned char *code;
    int codep[256][256];
    int compare[256];
    int ordered[256];
    int newc = 0;
    std::memset(&codep, -1, 256*256*4);
    std::memset(&ordered,-1,256*4);
    std::memset(&compare,-1, 256*4);
    
    
    std::fstream code_bmp("/home/luiz/Desktop/BMP/code.txt", std::fstream::app | std::fstream::in | std::fstream::out | std::fstream::binary);
    std::fstream compress_bmp("/home/luiz/Desktop/BMP/compress.txt", std::fstream::app | std::fstream::in | std::fstream::out | std::fstream::binary);
    std::fstream descompress_bmp("/home/luiz/Desktop/BMP/extract/eita.bmp", std::fstream::app | std::fstream::in | std::fstream::out | std::fstream::binary);
    int sizev = size(code_bmp) + 1;
    code = new unsigned char[sizev]; 
    
    code_bmp.seekg(0, code_bmp.beg);
    code_bmp.read((char*)code, sizev- 1);
    ordered[0] = +code[0];
    int contordered = 1;
    
    for(int i = 0; i < sizev - 2; i++){
            if(+code[i] == 10){
                ordered[contordered] = +code[i + 1];
                contordered++;
            }
    }
    
    int counter = 0, ord = 0;
   
    for(int c = 1; c < sizev - 2; c++){
        if(+code[c] == 10){
            c = c + 2;
            ord++;
            counter = 0;
        }
        codep[ordered[ord]][counter] = +code[c];
        counter++;
    }
    for(int i = 0; i < contordered; i++){
        cout << endl;
        cout << ordered[i] << ":";
        for(int m = 0; codep[ordered[i]][m] != -1; m++){
            cout << codep[ordered[i]][m];
        }
    }
    cout << endl << endl;
    int i = 0;
    sizev = size(compress_bmp) + 1;
    char *compressarch = new char [sizev];
    compress_bmp.seekg(0, compress_bmp.beg);
    compress_bmp.read((char*)compressarch, sizev- 1);
    int auxcounter = 0;

    for(i = 0; i < sizev - 1; i++ ){
        
        if(compressarch[i] == 1){
            while(compressarch[i] == 1){
                compare[auxcounter] = compressarch[i];
                //cout << compare[auxcounter];
                if(compressarch[i + 1] == 0){
                    compare[auxcounter + 1] = compressarch[i + 1];
                    //cout << compare[auxcounter + 1];
                    break;
                }
                auxcounter++;
                i++;
            }
            auxcounter++;
            i++;
        }
        else{

            do{
                compare[auxcounter] = compressarch[i];
                //cout << compare[auxcounter];

                if(compressarch[i + 1] == 0){
                    compare[auxcounter + 1] = compressarch[i + 1];
                    //cout << compare[auxcounter + 1];
                    break;
                }
                auxcounter++;
                i++;

            }while(compressarch[i] == 1);
            auxcounter++;
            i++;
        }
        if( i == sizev - 2) break;
        auxcounter++;
        //cout << ":" << auxcounter << ":";
        //cout << comparearr(compare, codep, 102, auxcounter) << endl;
        //for(int b = 0; compare[b] != -1; b++)
            //cout << compare[b] << endl;
        //for(int c = 0; c < contordered; c++)
          //  cout << ordered[c] << endl;
        for(int c = 0; c < contordered; c++){
            if(comparearr(compare, codep, ordered[c], auxcounter))
                descompress_bmp << (char)ordered[c];
            
                //cout << ordered[c] << " ";
        }
        for(int c = auxcounter - 1; auxcounter == 0; auxcounter--)
            compare[auxcounter] = -1;
        auxcounter = 0;

        //cout << auxcounter; 
    }
    
    
    //cout << i;    
    
    delete [] compressarch;
    delete [] code;
    code_bmp.close();
    compress_bmp.close();

    return 0;
}

int comparearr(int array1[256], int array2[][256], int alpha, int limit){
    int counter = 0;
    for(int i = 0; i < limit; i++){
        if(array1[i] == array2[alpha][i])
            counter++;
        else
            break;
    }
    return counter == limit ? 1 : 0 ;
}


int size(std::fstream &file){
    
    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0, file.beg);
    //file.close();
    return size;
}
