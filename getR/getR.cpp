#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    if (argc < 7) {
        return -1;
    }
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    int k = atoi(argv[3]);
    int l = atoi(argv[4]);
    int Tth = atoi(argv[5]);
    int m = atoi(argv[6]);

    float kk = 1.01;

    float r = 1.0 * ((1.0 *kk * l)/Tth)*pow((1 - 1.0 / m), (-1.0 * k * N)/T);
    printf("%f\n", r);
}
