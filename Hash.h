//
// Created by lm on 18-10-9.
//

#ifndef PROJECT_HASHFUNCTION_H
#define PROJECT_HASHFUNCTION_H
#define MASK 0x7
#define SHIFT 3

#include "GeneralHashFunctions.h"

class RandomOption {
public:
    static void initRandom();
    static int genRandomInt(int rangeStart, int rangeEnd);
};


class HashFunction {
public:
    HashFunction(int dimission);
    unsigned int hash(char* data);
    ~HashFunction();

private:
    int prime;
    int dimission;
    int* a;
};
class HashFunction1 {
public:
    //HashFunction(int dimission);
    static unsigned int hash(char* data, int index);
//    ~HashFunction();

    static HashFunctionF funcs[11];
    static int prime;

private:

    //int dimission;
    //int* a;
};

class HashPrint {
public:
    HashPrint(int dimission);
    char* getHashPrint(char* data, int length);
    ~HashPrint();

private:
    int prime;
    int dimission;
    int* a;
};

#endif //PROJECT_HASHFUNCTION_H
