#ifndef  __BINARYCODE__
#define __BINARYCODE__
#define MAX=256  

typedef enum{0,1} Bit;

typedef struct{
    Bit bits[MAX];
    int length;
}BinaryCode;

BinaryCode binaryCode();
void addBit(BinaryCode* bc, Bit b);
int getLength(BinaryCode bc);
Bit getBit(BinaryCode bc, int pos);
void concatenate(BinaryCode* bc1, BinaryCode bc2);

#endif