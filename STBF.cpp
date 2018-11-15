#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <map>
//#include <set>
#include "STBF.h"
//using namespace std;



STBF::STBF(STBFParams stbfParams) {
    this->m = stbfParams.m;
    this->k = stbfParams.k;
    this->rsize = stbfParams.dimission * 8;     //worng
    this->psize = stbfParams.psize;
    this->dimission = stbfParams.dimission;
    this->prime = this->m + 3;

    this->cells = (STBFCell**)malloc(this->m * sizeof(STBFCell*));
//    printf("aaaaa\n");
    this->hashPrint = new HashPrint(this->dimission);
//    printf("cccc\n");
    this->hashFunctions = (HashFunction**)malloc(this->k * sizeof(HashFunction*));
//    printf("bbbbb\n");
    int i;
    for (i = 0; i < this->k; ++i) {
        this->hashFunctions[i] = new HashFunction(this->dimission);
    }
    for (i = 0; i < this->m; ++i) {
        this->cells[i] = new STBFCell(this->psize, this->rsize);
    }
}

char* STBF::raptor(char *data, int rsize) {
    return data;
}

void STBF::insert(char *data) {
    char* print = this->hashPrint->getHashPrint(data, this->psize);
    char* raptor = this->raptor(data, this->rsize);
//    printf("aaaa\n");
    int i;
    for (i = 0; i < this->k; ++i) {
//        printf("_%d\n", i);
//        int position = (this->hashFunctions[i]->hash(data))% this->m;
        int position = (HashFunction1::hash(data, i))% this->m;

//        printf("position : %d\n", position);
//        printf("bbbb\n");
        if (this->cells[position]->state == 0) {
//            printf("cccc\n");
            this->cells[position]->write(true, print, raptor);
//            printf("eeeee\n");
            this->cells[position]->state = 1;
        } else if (this->cells[position]->state == 1) {
//            printf("dddd\n");
            char* print1 = this->cells[position]->readFingerPrint();
            char* raptor1 = this->cells[position]->readRaptor();
//            printf("strcmp_print  %s  %s %d\n", print, print1, bitArrayCmp(print, print1, psize));
//            printf("strcmp_raptor  %s  %s %d\n", raptor, raptor1, bitArrayCmp(raptor, raptor1, rsize));
            if (!this->bitArrayCmp(print, print1, this->psize) ||
                    !this->bitArrayCmp(raptor, raptor1, this->rsize)) {
//                printf("coill\n");
                this->cells[position]->state = 2;
            }
        }
    }
//    printf("end _all\n");
}

void STBF::clear() {
    int i;
    for (i = 0; i < this->m; ++i) {
        this->cells[i]->allSetTo0();
        this->cells[i]->state = 0;
    }
}

void STBF::printCells() {
    int i;
    for (i = 0; i < this->m; ++i) {
        printf("%d ", this->cells[i]->state);
    }
    printf("\n");
}

STBF::~STBF() {
//    free(this->cells);
    int i;
    for (i = 0; i < this->k; ++i) {
        free(this->hashFunctions[i]);
    }
    for (i = 0; i < this->m; ++i) {
        free(this-> cells[i]);
    }
    free(this->cells);
    free(this->hashPrint);
    free(this->hashFunctions);
}

bool STBF::bitArrayCmp(char *bits1, char *bits2, int length) {
    int i;
    for (i = 0; i < length; ++i) {
        bool bit1 = bits1[i >> SHIFT] & (1 << (i & MASK));
        bool bit2 = bits2[i >> SHIFT] & (1 << (i & MASK));
        if (bit1 != bit2) {
            return false;
        }
    }
    return true;
}

char* STBF::bitsTo01String(char *bits, int length) {
    int i;
    char * str = (char*)malloc((length + 1) * sizeof(char));
    for (i = 0; i < length; ++i) {
        bool bit = bits[i >> SHIFT] & (1 << (i & MASK));
        if (bit) {
            str[i] = '1';
        } else {
            str[i] = '0';
        }
    }
    str[length] = '\0';
    return str;
}

void STBF::createGroup() {
    int i;
//    FILE * fp;
//    char filename[50];
//    map<char*, set<char*, ptrCmp>, ptrCmp> printMap;
    map<std::string, set<std::string>> printMap;
    for (i = 0; i < this->m; ++i) {
        if (this->cells[i]->state == 2 || this->cells[i]->state == 0) {
            continue;
        }
        char* print = this->cells[i]->readFingerPrint();
        char* raptor = this->cells[i]->readRaptor();
        char* print01 = this->bitsTo01String(print, this->psize);
        std::string raptor_str = std::string(raptor);
        std::string print01_str = std::string(print01);
//        printf("__before insert : %s\n", raptor_str.c_str());
        if (printMap.count(print01_str)) {
            printMap[print01_str].insert(raptor_str);
        } else {
            set<std::string> set_tmp;
            set_tmp.insert(raptor_str);
            printMap[print01_str] = set_tmp;
        }
    }
//    printf("__________________\n");


    for (auto print : printMap) {
        std::string print01 = print.first;
        if (this->groups.count(print01)) {
            for (std::string raptor : printMap[print01]) {
                this->groups[print01].push_back(raptor);
            }
        } else {
            std::vector<std::string> vec;
            for (std::string raptor : printMap[print01]) {
                vec.push_back(raptor);
            }
            this->groups[print01] = vec;
        }
//        sprintf(filename, "./tmp/%s.txt", print01.c_str());
//        fp = fopen(filename, "a+");
////        if (fp == NULL) {
////            fp = fopen(filename, "w");
////        }
//        assert(fp != NULL);
//
//        for (std::string raptor : printMap[print01]) {
////            printf("__after insert : %s\n", raptor.c_str());
//            fprintf(fp, "%s ", raptor.c_str());
//        }
////        printf("__________________\n");
//
//        fclose(fp);
    }
}
