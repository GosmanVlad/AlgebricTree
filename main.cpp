#include "header.hpp"
#include "functions.hpp"
#include "structures.hpp"
/*********| VARIABLES |*********/
int stiva[255];
int nrElementeStiva;
int contorFormaPostfixata = 1;
char FormaPostFixata[caractereMaximeExpresie];
char StringAjutator[256];
int LungimeStringAjutator;
char expresie[caractereMaximeExpresie];
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

void ConversieFormaPoloneza()
{
    for(int i=0;i<strlen(expresie);i++)
    {
        if(strchr(NUMBERS, expresie[i]))
        {
            while(strchr(NUMBERS, expresie[i]))
            {
                FormaPostFixata[strlen(FormaPostFixata)] = expresie[i];
                i++;
            }
            FormaPostFixata[strlen(FormaPostFixata)] = ',';
            i--;
        }
        else if(expresie[i] == '(')
            push(stiva, ParantezaStanga, nrElementeStiva);

        else if(expresie[i] == ')')
        {
            while(primulElement(stiva) != ParantezaStanga)
            {
                FormaPostFixata[strlen(FormaPostFixata)] = ConversieCharOperatori(primulElement(stiva));
                pop(stiva,nrElementeStiva);
            }
            pop(stiva, nrElementeStiva);
        }
        else if(strchr(OPERATORI, expresie[i]))
        {
            while(!isEmpty(stiva, nrElementeStiva) && primulElement(stiva) != ParantezaStanga && ConversieIntOperatori(expresie[i]) <= primulElement(stiva))
                FormaPostFixata[strlen(FormaPostFixata)] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
            push(stiva, ConversieIntOperatori(expresie[i]), nrElementeStiva);

        }
    }
    while(!isEmpty(stiva,nrElementeStiva))
        FormaPostFixata[strlen(FormaPostFixata)] = ConversieCharOperatori(pop(stiva, nrElementeStiva));
    contorFormaPostfixata--;
}

void InverseazaStringAjutator()
{
    char c[255];
    strcpy(c, StringAjutator);
    int j = 0;
    for(int i = strlen(StringAjutator) - 1;i>=0;i--)
        c[j++] = StringAjutator[i];
    j--;
    strcpy(StringAjutator, c);
}
Nod* CreareArbore()
{
    int LungimeString = strlen(FormaPostFixata) - 1;
    LungimeStringAjutator = 0;
    if(LungimeString == -1)
        return NULL;
    Nod* cap = new Nod;
    if(strchr(NUMBERS, FormaPostFixata[LungimeString]) || FormaPostFixata[LungimeString] == ',')
    {
        if(FormaPostFixata[LungimeString] == ',')
        {
            strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
            LungimeString = strlen(FormaPostFixata) - 1;
        }
        if(FormaPostFixata[LungimeString - 1] != ',')
        {
            while(FormaPostFixata[LungimeString] != ',')
            {
                StringAjutator[LungimeStringAjutator++] = FormaPostFixata[LungimeString];
                strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
                LungimeString = strlen(FormaPostFixata) - 1;
            }
            InverseazaStringAjutator();
            cap->value = StringAjutator;
            LungimeStringAjutator = 0;
        }
        else cap->value = FormaPostFixata[LungimeString];
        cap->left = NULL;
        cap->right = NULL;
        strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
        return cap;
    }
    cap->value = FormaPostFixata[LungimeString];
    strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
    cap->left = CreareArbore();
    cap->right = CreareArbore();
    return cap;
}

void svd(Nod *c) {
    if(c)
    {
        svd(c->left);
        cout<<c->value<<" ";
        svd(c->right);
    }
}
int main()
{
    FormaPostFixata[0] = ',';
    cin.getline(expresie, 255);
    ConversieFormaPoloneza();
    cout<<FormaPostFixata<<endl;
    Nod* arbore = CreareArbore();
    svd(arbore);
    return 0;
}
