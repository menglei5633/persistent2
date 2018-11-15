#include <assert.h>
#include <stdlib.h>
#include "STBFCell.h"

STBFCell::STBFCell(int psize, int rsize) {
    this->bytes = (1 + psize +rsize) / 8 + ((1 + psize +rsize) % 8 > 0 ? 1 : 0);
    this->bitsArray = (char*)malloc(bytes * sizeof(char));
    assert(this->bitsArray != NULL);
    this->psize = psize;
    this->rsize = rsize;
    this->state = 0;
}

void STBFCell::write(bool first, char *fingerprint, char *raptor) {
    this->allSetTo0();
    if (first) {
        this->writeBitTo1(this->bitsArray, 0);
    }
    int i;
    for (i = 1; i < this->rsize + 1; ++i) {
        if (readBit(raptor, i - 1)) {
            writeBitTo1(this->bitsArray, i);
        }
    }
    for (i = rsize + 1; i < this->rsize + this->psize + 1; ++i) {
        if (readBit(fingerprint, i - 1 - rsize)) {
            writeBitTo1(this->bitsArray, i);
        }

    }
}

bool STBFCell::readBit(char *bits, int location) {
    return bits[location >> SHIFT] & (1 << (location & MASK));
}

void STBFCell::writeBitTo1(char *bits, int location) {
    bits[location >> SHIFT] |= (1 << (location & MASK));
}

void STBFCell::allSetTo0() {
    int i;
    for (i = 0; i < this->bytes; ++i) {
        this->bitsArray[i] &= 0x00;
    }
}

bool STBFCell::readFirst() {
    if (readBit(this->bitsArray, 0)) {
        return true;
    } else {
        return false;
    }
}

char* STBFCell::readRaptor() {
    char* raptor = (char*)malloc((this->rsize / 8 + (this->rsize % 8 == 0? 0 : 1) + 1) * sizeof(char));
    int i;
    for (i = 1; i < this->rsize + 1; ++i) {
        if (readBit(this->bitsArray, i)) {
            writeBitTo1(raptor, i - 1);
        }
    }
    raptor[this->rsize / 8 + (this->rsize % 8 == 0? 0 : 1)] = '\0';
    return raptor;
}
char* STBFCell::readFingerPrint() {
    char* print = (char*)malloc((this->psize / 8 + (this->psize % 8 == 0? 0 : 1) + 1) * sizeof(char));
    int i;
    for (i = this->rsize + 1; i < this->psize + this->rsize + 1; ++i) {
        if (readBit(this->bitsArray, i)) {
            writeBitTo1(print, i - 1 - this->rsize);
        }
    }
    print[this->psize / 8 + (this->psize % 8 == 0? 0 : 1)] = '\0';
    return print;
}

STBFCell::~STBFCell() {
    free(this->bitsArray);
}