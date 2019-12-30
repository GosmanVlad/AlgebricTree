#include "header.hpp"
#include "variables.hpp"

int contorFormaPostfixata = 0;
int nrElementeStiva = 0;
int stiva[100];
char FormaPostFixata[caractereMaximeExpresie];

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

char ConversieCharOperatori(int operatorScrisInNumar) {


    switch(operatorScrisInNumar)
    {
        case PLUS:
            return '+';
            break;
        case MINUS:
            return '-';
            break;
        case MULTIPLICATION:
            return '*';
            break;
        case DIV:
            return '/';
            break;
        case power:
            return '^';
            break;
    }
}
int ConversieIntOperatori(char operatorDeConvertit){
    switch(operatorDeConvertit)
    {
        case '+':
            return PLUS;
            break;
        case '-':
            return MINUS;
            break;
        case '*':
            return MULTIPLICATION;
            break;
        case '/':
            return DIV;
            break;
        case '^':
            return power;
            break;
    }
}

void AnalizeazaExpresie(char expresie[])
{
    for(int i=0;i<strlen(expresie);i++)
    {
        if(strchr(NUMBERS, expresie[i]))
            FormaPostFixata[contorFormaPostfixata++] = expresie[i];

        else if(expresie[i] == '(')
            push(stiva, ParantezaStanga, nrElementeStiva);

        else if(expresie[i] == ')')
            while(primulElement(stiva) != ParantezaStanga)
                FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(pop(stiva,nrElementeStiva));

        else if(strchr(OPERATORI, expresie[i]))
        {
            while(!isEmpty(stiva, nrElementeStiva) && primulElement(stiva) != ConversieIntOperatori(ParantezaStanga) && ConversieIntOperatori(expresie[i]) <= primulElement(stiva))
                FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
            push(stiva, ConversieIntOperatori(expresie[i]), nrElementeStiva);
        }
    }
    for(int i=1;i<=nrElementeStiva;i++)
        FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
    contorFormaPostfixata--;
}
int main()
{
    char expresie[caractereMaximeExpresie];
    cin.getline(expresie, 255);
    AnalizeazaExpresie(expresie);
    cout<<FormaPostFixata;
    return 0;
}
