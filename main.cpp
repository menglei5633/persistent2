#include <stdio.h>
#include <assert.h>
#include <set>
#include "STBF.h"
using namespace std;

STBFParams readParams(FILE* fp) {
    STBFParams stbfParams;
    char buffer[40];

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.T);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.N);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.m);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.k);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.rsize);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.psize);

    fscanf(fp, "%s", buffer);
    fscanf(fp, "%d", &stbfParams.dimission);

    return stbfParams;

}
void printParams(STBFParams stbfParams) {
    printf("T : %d\n", stbfParams.T);
    printf("N : %d\n", stbfParams.N);
    printf("m : %d\n", stbfParams.m);
    printf("k : %d\n", stbfParams.k);
    printf("rsize : %d\n", stbfParams.rsize);
    printf("psize : %d\n", stbfParams.psize);
    printf("dimission : %d\n", stbfParams.dimission);
}

HashFunctionF HashFunction1::funcs[11] = { RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash, DJBHash,
                                        DEKHash, BPHash, FNVHash, APHash};
int HashFunction1::prime = 1313131313;

int main(int argc, char* argv[]) {
    printf("start...\n");
    if (argc < 7) {
        return -1;
    }
    RandomOption::initRandom();

    char* paramfilename = argv[1];
    int m = atoi(argv[5]);
    int psize = atoi(argv[6]);
//    printf("bbb\n");
//    printf("%s\n", paramfilename);
    FILE* paramfile = fopen(paramfilename, "r");
    assert(paramfile != NULL);
    STBFParams stbfParams = readParams(paramfile);
    fclose(paramfile);
//    printf("ccc\n");
    if (m != 0) {
        stbfParams.m = m;
    }
    if (psize != 0) {
        stbfParams.psize = psize;
    }

    printParams(stbfParams);

    char* datafilename = argv[2];
    FILE* datafile = fopen(datafilename, "r");

    HashPrint hashPrint = HashPrint(4);

    STBF stbf = STBF(stbfParams);

    int startline = atoi(argv[4]);


    int i, j;
    char buffer[150];

    for (i = 0; i < startline; ++i) {
        fscanf(datafile, "%s", buffer);
    }

    for (i = 0; i < stbfParams.T; ++i) {
        stbf.clear();
//        printf("T : %d\n", i);
        for (j = 0; j < stbfParams.N; ++j) {
//            printf("j : %d\n", j);
            fscanf(datafile, "%s", buffer);
            stbf.insert(buffer);
//            printf("%s\n", buffer);
//            char * print = hashPrint.getHashPrint(buffer, 16);
//            for (int k = 0; k < 16; ++k) {
//                bool bit = print[k >> SHIFT] & (1 << (k & MASK));
//                printf("%d", bit);
//            }
//            printf("\n");

        }
//        stbf.printCells();
        stbf.createGroup();
    }

//    printf("%f\n", (1.0 * stbfParams.dimission * 8 / stbfParams.rsize));

    char* writefilename = argv[3];
    char filename[60];
    FILE * writefile;
    FILE * fp;
    
//    map<char*, int, ptrCmp> counter;
//    map<char*, int, ptrCmp> result;
    map<std::string, int> counter;
    set<std::string> result;
    int c1 = 0, c2 = 0;
//    for (std::string print01 : stbf.printsSet) {
//        counter.clear();
//        map<std::string, int>(counter).swap(counter);
//        sprintf(filename, "./tmp/%s.txt", print01.c_str());
//        fp = fopen(filename, "r");
//        if (fp == NULL) {
//            continue;
//        }
//        while(!feof(fp)) {
//            fscanf(fp, "%s", buffer);
//            std::string buffer_str = std::string(buffer);
//            if (counter.count(buffer_str)) {
//                counter[buffer_str] ++;
//            } else {
//                counter[buffer_str] = 1;
//            }
//        }
//        fclose(fp);
//
//        //(1.0 * stbfParams.dimission * 8 / stbfParams.rsize)
//        if (counter.size() > 2) {
////            printf("======================\n");
//            continue;
//        } else if (counter.size() == 2){
//            int min =100000;
//            for (auto raptor : counter) {
//                min = counter[raptor.first] < min ? counter[raptor.first] : min;
//            }
//            if (min > 2) {
////                printf("______________________\n");
//                continue;
//            }
//        }
//        for (auto raptor : counter) {
//            if (counter[raptor.first] >= (1.0 * stbfParams.dimission * 8 / stbfParams.rsize)) {
//                //fprintf(writefile, "%s\n", raptor.first);
////                printf("before insert : %s\n", raptor.first.c_str());
//                c1++;
//		        result.insert(raptor.first);
//            }
//
//        }
////        printf("___________________\n");
//    }
    for (auto print : stbf.groups) {
        counter.clear();
        map<std::string, int>(counter).swap(counter);
        std::vector<std::string> vec = stbf.groups[print.first];
        for (std::string raptor : vec) {
            if (counter.count(raptor)) {
                counter[raptor] ++;
            } else {
                counter[raptor] = 1;
            }
        }
/*
        if (counter.size() > 2) {
//            printf("======================\n");
            continue;
        } else if (counter.size() == 2){
            int min =100000;
            for (auto raptor : counter) {
                min = counter[raptor.first] < min ? counter[raptor.first] : min;
            }
            if (min > 2) {
//                printf("______________________\n");
                continue;
            }
        }
*/
	int max_count = 0;
	std:string max_str;
        for (auto raptor : counter) {
	    if (counter[raptor.first] > max_count) {
		max_count = counter[raptor.first];
		max_str = raptor.first;
	    }
        }
	if (max_count >= (1.0 * stbfParams.dimission * 8 / stbfParams.rsize)) {
                //fprintf(writefile, "%s\n", raptor.first);
//                printf("before insert : %s\n", raptor.first.c_str());
            c1++;
	    result.insert(max_str);
        }
    }
    writefile = fopen(writefilename, "w");
    assert(writefile != NULL);
    for (auto id : result) {
        c2++;
//        printf("after insert : %s\n", id.c_str());
        fprintf(writefile, "%s\n", id.c_str());
    }
//    printf("c1 :%d    c2 :%d\n", c1, c2);
    fclose(writefile);

    stbf.clear();

    fclose(datafile);

    return 0;

}


