#include "header.hpp"
#include "functions.hpp"
extern int stiva[255];
extern int nrElementeStiva;

bool isEmpty(int stiva2[], int &nrElementeStiva2) {
    if(nrElementeStiva == 0)
        return 1;
    return 0;
}

void push(int stiva[],int numar, int &nrElementeStiva) {
    nrElementeStiva ++;
    stiva[nrElementeStiva] = numar;
}

int primulElement(int stiva[]) {
    return stiva[nrElementeStiva];
}

int pop(int stiva[], int &nrElementeStiva) {
    if(isEmpty(stiva, nrElementeStiva))
        cout<<"Stiva goala";
    else {
        int rezultat = primulElement(stiva);
        nrElementeStiva--;
        return rezultat;
    }
    return 0;
}
