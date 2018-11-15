//
// Created by lm on 18-9-25.
//
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return -1;
    }

//    char * paramFile = argv[1];
//    char * dataFile = argv[2];
//    char * resFile = argv[3];
//    char * resFile2 = argv[4];
//    int startline = atoi(argv[5]);
//    char * exactfile = argv[6];
////    int N = atoi(argv[7]);
////    int T = atoi(argv[8]);
//    int is = atoi(argv[7]);
//
//    int numOfAgain = atoi(argv[8]);
//    int Pfp = atoi(argv[9]);
//    int Pfn = atoi(argv[10]);
//    int startL = atoi(argv[11]);
//    int startm = atoi(argv[12]);
    char* testParam = argv[1];
    FILE* testParamFile = fopen(testParam, "r");
    assert(testParamFile != NULL);

    //read params
    char buffer[50];
    char paramFile[50];
    char dataFile[50];
    char resFile[50];
//    char resFile2[40];
    int startline;
    char exactFileName[50];
//    int isExact;
    int numOfAgain;
    float pfp;
    float pfn;
    int startP, endP;
    int startm, endm;
    int allItemNum;

    int n;
    int T;
    int c;
    int R;

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%s", paramFile);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%s", dataFile);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%s", resFile);


    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &startline);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%s", exactFileName);

//    fscanf(testParamFile, "%s", buffer);
//    fscanf(testParamFile, "%d", &isExact);
//    printf("%d\n", isExact);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &numOfAgain);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%f", &pfp);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%f", &pfn);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &startP);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &startm);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &endP);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &endm);

    fscanf(testParamFile, "%s", buffer);
    fscanf(testParamFile, "%d", &allItemNum);

    fclose(testParamFile);
//
//    testParamFile = fopen(paramFile, "r");
//    fscanf(testParamFile, "%s", buffer);
//    fscanf(testParamFile, "%d", &n);
//
//    fscanf(testParamFile, "%s", buffer);
//    fscanf(testParamFile, "%d", &T);
//
//    fscanf(testParamFile, "%s", buffer);
//    fscanf(testParamFile, "%d", &c);
//
//    fscanf(testParamFile, "%s", buffer);
//    fscanf(testParamFile, "%d", &R);
//    fclose(testParamFile);

    printf("readParamEnd\n");
    //read param end

    //do cmd
    char cmd[200];
    int all_per;
    int correct;
    int wrong;
    int P, m;
    float Pfp, Pfn;
    P = startP;
    m = startm;
    Pfp = 1;
    Pfn = 1;
    FILE * cmdfp;
    int all_allper, all_correct, all_wrong;
    int i;
	all_allper = all_correct = all_wrong = 0;
	for (i = 0; i < numOfAgain; ++i) {
                sprintf(cmd, "./do.sh %s %s %s %d %s %d %d", paramFile, dataFile, resFile,
                        startline, exactFileName, m, P);
		printf("%s\n", cmd);
                cmdfp = popen(cmd, "r");
                assert(cmdfp != NULL);
                fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
                pclose(cmdfp);
                all_allper += all_per;
                all_correct += correct;
                all_wrong += wrong;
            }
            printf("angin num : %d   all_allper: %d     all_correct: %d     all_wrong: %d\n",
                   numOfAgain, all_allper, all_correct, all_wrong);
            Pfn = 1.0 *(all_allper - all_correct) / all_allper;
	    Pfp = 1.0 * all_wrong / (numOfAgain*allItemNum - all_allper);
            printf("trace Pfn: %f    Pfp : %f\n", Pfn, Pfp);
    if (Pfn <= pfn && Pfp <= pfp) {
        while (Pfn <= pfn && Pfp <= pfp) {
            all_allper = all_correct = all_wrong = 0;
            m-=100;
            printf("trace m for Pfn: %d\n", m);
            for (i = 0; i < numOfAgain; ++i) {
                sprintf(cmd, "./do.sh %s %s %s %d %s %d %d", paramFile, dataFile, resFile,
                        startline, exactFileName, m, P);
                cmdfp = popen(cmd, "r");
                assert(cmdfp != NULL);
                fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
                pclose(cmdfp);
                all_allper += all_per;
                all_correct += correct;
                all_wrong += wrong;
            }
            printf("angin num : %d   all_allper: %d     all_correct: %d     all_wrong: %d\n",
                   numOfAgain, all_allper, all_correct, all_wrong);
            Pfn = 1.0 *(all_allper - all_correct) / all_allper;
	    Pfp = 1.0 * all_wrong / (numOfAgain*allItemNum - all_allper);
            printf("trace Pfn: %f   Pfp: %f\n", Pfn, Pfp);
        }
        m+=100;
    } else if (Pfn > pfn || Pfp > pfp){
        while (Pfn > pfn || Pfp > pfp) {
            all_allper = all_correct = all_wrong = 0;
            m+=100;
            printf("trace m for Pfn: %d\n", m);
            for (i = 0; i < numOfAgain; ++i) {
                sprintf(cmd, "./do.sh %s %s %s %d %s %d %d", paramFile, dataFile, resFile,
                        startline, exactFileName, m, P);
                printf("%s\n", cmd);
                cmdfp = popen(cmd, "r");
                assert(cmdfp != NULL);
                fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
                pclose(cmdfp);
                all_allper += all_per;
                all_correct += correct;
                all_wrong += wrong;
            }
            printf("angin num : %d   all_allper: %d     all_correct: %d     all_wrong: %d\n",
                   numOfAgain, all_allper, all_correct, all_wrong);
            Pfn = 1.0 *(all_allper - all_correct) / all_allper;
	    Pfp = 1.0 * all_wrong / (numOfAgain*allItemNum - all_allper);
            printf("trace Pfn: %f    Pfp : %f\n", Pfn, Pfp);
        }
    }
/*
    while (Pfn <= pfn && m > endm) {
        all_allper = all_correct = all_wrong = 0;
        m-=100;
        printf("trace m for Pfn: %d\n", m);
        for (i = 0; i < numOfAgain; ++i) {
            sprintf(cmd, "./do.sh %s %s %s %d %s %d %d", paramFile, dataFile, resFile,
                    startline, exactFileName, m, P);
            cmdfp = popen(cmd, "r");
            assert(cmdfp != NULL);
            fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
            pclose(cmdfp);
            all_allper += all_per;
            all_correct += correct;
            all_wrong += wrong;
//            printf("all_per : %d    correct : %d    wrong : %d\n", all_per, correct, wrong);
        }
        printf("angin num : %d   all_allper: %d     all_correct: %d     all_wrong: %d\n",
               numOfAgain, all_allper, all_correct, all_wrong);
        Pfn = 1.0 *(all_allper - all_correct) / all_allper;
        printf("trace Pfn: %f\n", Pfn);
    }
    m+=100;
*/

    printf("-------------------\n");
    printf("Pfn  met\n");
    printf("-------------------\n");

    Pfp =  1.0 * all_wrong / (numOfAgain*allItemNum - all_allper);

/*
    while (Pfp > pfp) {
        all_allper = all_correct = all_wrong = 0;
        m += 50;
        printf("trace m for Pfp: %d\n", m);
        for (i = 0; i < numOfAgain; ++i) {
            sprintf(cmd, "./do.sh %s %s %s %d %s %d %d", paramFile, dataFile, resFile,
                    startline, exactFileName, m, P);
            cmdfp = popen(cmd, "r");
            assert(cmdfp != NULL);
            fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
            pclose(cmdfp);
            all_allper += all_per;
            all_correct += correct;
            all_wrong += wrong;
        }
        printf("angin num : %d   all_allper: %d     all_correct: %d     all_wrong: %d\n",
               numOfAgain, all_allper, all_correct, all_wrong);
        Pfp = 1.0 * all_wrong / (numOfAgain*allItemNum - all_allper);
        printf("trace Pfp: %f\n", Pfp);
    }
*/


//    printf("trace m : %d\n", m);
//    sprintf(cmd, "./algorithm.sh %s %s %s %s %d %s %d %d %d %d", paramFile, dataFile, resFile, resFile2,
//            startline, exactFileName, n, T, L, m);
//    cmdfp = popen(cmd, "r");
//    assert(cmdfp != NULL);
//    fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
//    pclose(cmdfp);
//    printf("all_per : %d    correct : %d    wrong : %d\n", all_per, correct, wrong);
//    Pfn = 1.0 *(all_per - correct) / all_per;
//    printf("trace Pfn: %f\n", Pfn);
//
//    if (Pfn > pfn) {
//        while (Pfn > pfn) {
//            L += 100;
//            printf("trace L  : %d\n", L);
//            sprintf(cmd, "./algorithm.sh %s %s %s %s %d %s %d %d %d %d", paramFile, dataFile, resFile, resFile2,
//                    startline, exactFileName, n, T, L, m);
//            cmdfp = popen(cmd, "r");
//            assert(cmdfp != NULL);
//            fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
//            pclose(cmdfp);
//            printf("all_per : %d    correct : %d    wrong : %d\n", all_per, correct, wrong);
//            Pfn = 1.0 *(all_per - correct) / all_per;
//            printf("trace Pfn: %f\n", Pfn);
//        }
//
//    }
//    while (Pfn <= pfn) {
//        --m;
//        printf("trace m : %d\n", m);
//        sprintf(cmd, "./algorithm.sh %s %s %s %s %d %s %d %d %d %d", paramFile, dataFile, resFile, resFile2,
//                startline, exactFileName, n, T, L, m);
//        cmdfp = popen(cmd, "r");
//        assert(cmdfp != NULL);
//        fscanf(cmdfp, "%d %d %d", &all_per, &correct, &wrong);
//        pclose(cmdfp);
//        printf("all_per : %d    correct : %d    wrong : %d\n", all_per, correct, wrong);
//        Pfn = 1.0 *(all_per - correct) / all_per;
//        printf("trace Pfn: %f\n", Pfn);
//    }
//    ++m;

    float mem;


    int rsize = 2;
    mem = 1.0 * ((1 + rsize + P) * m) / 8;

    printf("P : %d   m : %d  mem : %f\n", P, m, mem);
//    sprintf(cmd, "./computeMemory/a.out %d %d %d %d", c, R, L, m);
//    cmdfp = popen(cmd, "r");
//    assert(cmdfp != NULL);
//    fscanf(cmdfp, "%f", &mem);
//    printf("mem : %f\n", mem);
//    pclose(cmdfp);




    return 0;
}
