#include "header.hpp"
#include "functions.hpp"
#include "structures.hpp"
/*********| VARIABLES |*********/
int stiva[255];
int nrElementeStiva;
int contorFormaPostfixata = 0;
char FormaPostFixata[caractereMaximeExpresie];
/******| END - VARIABLES |******/

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
    return 0;
}
void ConversieFormaPoloneza(char expresie[]) {
    for(int i=0;i<strlen(expresie);i++)
    {
        if(strchr(NUMBERS, expresie[i]))
            FormaPostFixata[contorFormaPostfixata++] = expresie[i];

        else if(expresie[i] == '(')
            push(stiva, ParantezaStanga, nrElementeStiva);

        else if(expresie[i] == ')')
        {
            while(primulElement(stiva) != ParantezaStanga)
            {
                FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(primulElement(stiva));
                pop(stiva,nrElementeStiva);
            }
            pop(stiva, nrElementeStiva);
        }

        else if(strchr(OPERATORI, expresie[i]))
        {
            while(!isEmpty(stiva, nrElementeStiva) && primulElement(stiva) != ConversieIntOperatori(ParantezaStanga) && ConversieIntOperatori(expresie[i]) <= primulElement(stiva))
                FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
            push(stiva, ConversieIntOperatori(expresie[i]), nrElementeStiva);
        }
    }
    while(!isEmpty(stiva,nrElementeStiva))
        FormaPostFixata[contorFormaPostfixata++] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
    contorFormaPostfixata--;
}
Nod* CreareArbore()
{
    int LungimeString = strlen(FormaPostFixata) - 1;
    if(LungimeString == 0)
        return NULL;
    Nod* cap = new Nod;
    if(strchr(NUMBERS, FormaPostFixata[LungimeString]))
    {
        cap->value = FormaPostFixata[LungimeString];
        strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
        return cap;
    }
    cap->value = FormaPostFixata[LungimeString];
    strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
    cap->left = CreareArbore();
    cap->right = CreareArbore();
}
int main()
{
    char expresie[caractereMaximeExpresie];
    cin.getline(expresie, 255);
    ConversieFormaPoloneza(expresie);
    cout<<FormaPostFixata<<endl;
    CreareArbore();
    cout<<strlen(FormaPostFixata);
    return 0;
}
