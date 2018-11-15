//
// Created by lm on 18-10-9.
//

#ifndef project_STBF_H
#define project_STBF_H

#include <map>
#include <set>
#include <vector>
#include <string.h>
#include <assert.h>
#include "STBFCell.h"
#include "Hash.h"
using namespace std;

struct ptrCmp
{
    bool operator()(const char  *a, const char *b) const
    {
        return strcmp(a, b) < 0;
    }
};

class STBFParams{
public:
    int T;
    int N;
    int m;
    int k;
    int rsize;
    int psize;
    int dimission;
};

class STBF {
public:
    STBF(STBFParams stbfParams);
    void insert(char *data);
    void clear();
    void printCells();
    void createGroup();
    void findPersistents();
    ~STBF();

//    set<std::string> printsSet;
    map<std::string, std::vector<std::string>> groups;

private:
    int m;        // number of cells
    int k;        // number of hashfunctions
    int rsize;
    int psize;
    int dimission;
    STBFCell ** cells;
    HashFunction** hashFunctions;
    HashPrint* hashPrint;
    char* raptor(char* data, int rsize);
    bool bitArrayCmp(char* bits1, char* bits2, int length);
    char* bitsTo01String(char* bits, int length);
    int prime;
};

#endif project_STBF_H
