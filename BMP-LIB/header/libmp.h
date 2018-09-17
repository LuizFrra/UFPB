#ifndef _LIB_BMP_
#define _LIB_BMP_

/* BMP HEADER
RGB
LITTLE ENDIANESS MOST OF INFORMATIONS
BMP HEADER[0 - 51]
0 - 1 = HERE WILL BE THE "ID" OF A BMP IMAGE // 2 BYTES // BIG ENDINESS
2 - 5 =  ||   ||  ||  ||  SIZE OF A BMP IMAGE // 4 BYTES // LITTLE ENDINESS = 5 - 2
6 - 9 = UNUSED = DEFAULT VALUE 0 0 0 0 
10 - 13 = THIS IS THE LOCATION WHERE THE ARRAY OF PIXEL START, VALUE = 36HEX = 54DEC, 
    THIS MEAN THAT THE BEGIN OF THE FIRST PIXEL IS IN POSITION 52 // LITTLE ENDINESS // 4 BYTES
*/

/*DIB HEADER
14 - 17 = SIZE OF DIB HEADER = DEFAULT 28HEX = 40DEC // 4 BYTES // LITTLE ENDINESS
18 - 21 = WIDTH OF IMAGE // LITTLE ENDINESS 
22 - 25 = HEIGHT OF IMAGEM // LITTLE ENDINESS // BOTTOM TO TOP
26 - 27 = NUMBER OF COLOR PLANES BEING USED = 01 DEFAULT
28 - 29 = NUMBER OF BYTES PER PIXEL = 18HEX = 24DEC = BGR
30 - 33 = COMPREENSION = 0 0 0 0 
34 - 37 = NUMBER OF ONLY ARRAY SIZE INCLUDING THE PADDING
38 - 41 = PIXEL PER METRE HORIZONTAL 
42 - 45 = PIXEL PER METRE VERTICAL 
46 - 49 - NUMBER OF COLOR IN PALETTE = DEFAULT = 0 0 0 0 
50 - 53 - IMPORTANTE COLLOR =  0 0 0 0 = ALL COLOR ARE IMPORTANTE   
*/

#include "readbmp.h"
#include "tree.h"

#endif