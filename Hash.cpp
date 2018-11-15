#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <Random.h>
#include "Hash.h"

void RandomOption::initRandom() {
    srandom(time(NULL));
}

int RandomOption::genRandomInt(int rangeStart, int rangeEnd) {
//    printf("hhhhh\n");
    assert(rangeStart <= rangeEnd);
    int r;
    r = rangeStart + (int)((rangeEnd - rangeStart + 1.0) * random() / (RAND_MAX + 1.0));
    assert(r >= rangeStart && r <= rangeEnd);
    return r;
}

HashFunction::HashFunction(int dimission) {
    this->dimission = dimission;
    int i;
    this->a = (int *)malloc(dimission * sizeof(int));
    assert(this->a != NULL);
    for (i = 0; i < dimission; ++i) {
        this->a[i] = RandomOption::genRandomInt(1, 10000);
//        printf("a %d : %d\n", i, this->a[i]);
    }
//    printf("\n");
//    int b;
//    scanf("%d", &b);
//    this->funcs[11] = { RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash, DJBHash, DEKHash, BPHash, FNVHash,
//                APHash};
    this->prime = 131313131313;
}
//
unsigned int HashFunction::hash(char *data) {
    //old method
    unsigned int value = 0;
    unsigned int nLen = strlen((char*)data);
    assert(nLen <= this->dimission);
    int i;
    for (i = 0; i < nLen; ++i) {
        value += this->a[i] * pow(data[i], i);
    }
    value = value % this->prime;
    return value;

    //new method
//    unsigned int value = 0;
//    value = this->funcs[index](std::string(data));
//    return value % this->prime;
}

unsigned int HashFunction1::hash(char *data, int index) {
    unsigned int value = 0;
    value = HashFunction1::funcs[10 - index](std::string(data));
    return value % HashFunction1::prime;
}

HashPrint::HashPrint(int dimission) {
    this->dimission = dimission;
    int i;
    this->a = (int *)malloc(dimission * sizeof(int));
    assert(this->a != NULL);
    for (i = 0; i < dimission; ++i) {
        this->a[i] = RandomOption::genRandomInt(0, 1000000);
    }
    this->prime = 13131313131;
}

char* HashPrint::getHashPrint(char *data, int length) {
    char* print = (char*)malloc((length / 8 + (length % 8 == 0 ? 0 : 1) + 1) * sizeof(char));
    unsigned int value = 0;
    //unsigned int nLen = strlen((char*)data);
    //assert(nLen <= this->dimission);
    //int i;
    //for (i = 0; i < nLen; ++i) {
    //    value += this->a[i] * pow(data[i], i);
    //}

    value = HashFunction1::hash(data, 10);

//    printf("value0 : %u\n", value);
    value = value % this->prime;
//    printf("value1 : %u\n", value);
//    printf("1 << length : %d\n", 1 << length);
    value = value % (1 << length);
//    printf("value2 : %u\n", value);
    int b, j;
    j = 0;
    while(value != 0) {
        b = value % 2;
        value = value / 2;
        if (b == 1) {
//            printf("1");
            print[j >> SHIFT] |= (1 << (j & MASK));
        } else {
//            printf("0");
        }
        ++j;
    }
//    printf("\n");
    print[(length / 8 + (length % 8 == 0 ? 0 : 1))] = '\0';
    return print;
}

HashFunction::~HashFunction() {
    free(this->a);
}

HashPrint::~HashPrint() {
    free(this->a);
}
