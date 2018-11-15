//
// Created by lm on 18-10-9.
//

#ifndef PROJECT_STBFCELL_H
#define PROJECT_STBFCELL_H
#define MASK 0x7
#define SHIFT 3

class STBFCell {
public:
    STBFCell(int psize, int rsize);
    void write(bool first, char* fingerprint, char* raptor);
    bool readFirst();
    char* readFingerPrint();
    char* readRaptor();
    void allSetTo0();
    ~STBFCell();

    int state;   //empty - 0, singleton - 1  collided - 2
private:
    bool readBit(char* bits, int location);
    void writeBitTo1(char* bits, int location);
    int psize;
    int rsize;
    int bytes;
    char* bitsArray;
};


#endif //PROJECT_STBFCELL_H
