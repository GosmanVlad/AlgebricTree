//GRAFICA: CLAUDIU
//BACK-END: VLAD

#include "header.hpp"
#include <math.h>
#include <cstring>
#include <graphics.h>//biblioteca pentru grafica
#include <winbgim.h>//biblioteca pentru grafica
#include "functions.hpp"
#include "structures.hpp"
/*********| VARIABLES |*********/
int stiva[255],midx,anim;
char cmnd;
int nrElementeStiva;
int contorFormaPostfixata = 1;
char FormaPostFixata[caractereMaximeExpresie];
char StringAjutator[256];
int LungimeStringAjutator;
char expresie[caractereMaximeExpresie];
/******| END - VARIABLES |******/

char ConversieCharOperatori(int operatorScrisInNumar) //VLAD
{
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

int ConversieIntOperatori(char operatorDeConvertit) //VLAD
{
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

void ConversieFormaPoloneza() //VLAD
{
    for(int i=0; i<strlen(expresie); i++)
    {
        if(strchr(NUMBERS, expresie[i]) || strchr(ALFABET, expresie[i]))
        {
            while(strchr(NUMBERS, expresie[i]) || strchr(ALFABET, expresie[i]))
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

void InverseazaStringAjutator() //VLAD
{
    char c[255];
    strcpy(c, StringAjutator);
    int j = 0;
    for(int i = strlen(StringAjutator) - 1; i>=0; i--)
        c[j++] = StringAjutator[i];
    j--;
    strcpy(StringAjutator, c);
}
Nod* CreareArbore()   //Vlad
{
    int LungimeString = strlen(FormaPostFixata) - 1;
    LungimeStringAjutator = 0;
    if(LungimeString == -1)
        return NULL;
    Nod* cap = new Nod;
    if(strchr(NUMBERS, FormaPostFixata[LungimeString]) || strchr(ALFABET, FormaPostFixata[LungimeString])|| FormaPostFixata[LungimeString] == ',')
    {
        if(FormaPostFixata[LungimeString] == ',')
        {
            strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
            LungimeString = strlen(FormaPostFixata) - 1;
        }
        if(strchr(NUMBERS, FormaPostFixata[LungimeString-1]))
        {
            while(strchr(NUMBERS, FormaPostFixata[LungimeString]))
            {
                StringAjutator[LungimeStringAjutator++] = FormaPostFixata[LungimeString];
                strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
                LungimeString = strlen(FormaPostFixata) - 1;
            }
            InverseazaStringAjutator();
            cap->value = StringAjutator;
            LungimeStringAjutator = 0;
        }
        else
        {
            cap->value = FormaPostFixata[LungimeString];
            strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
        }
        cap->left = NULL;
        cap->right = NULL;
        return cap;
    }
    cap->value = FormaPostFixata[LungimeString];
    strcpy(FormaPostFixata + LungimeString, FormaPostFixata + LungimeString + 1);
    cap->left = CreareArbore();
    cap->right = CreareArbore();
    return cap;
}
void borduraGrafica(int culoare_j,int culoare_k) // Claudiu
{
    int coordonata_i,raza=10;
    for(coordonata_i=10; coordonata_i<getmaxx(); coordonata_i++)
    {
        setcolor(culoare_j);
        circle(10,coordonata_i,raza);
        circle(getmaxx()-raza,coordonata_i,raza);
        setcolor(culoare_k);
        circle(coordonata_i,10,raza);
        circle(coordonata_i,getmaxy()-raza,raza);
        delay(0.9);//determina cat de mult apare bordura grafica
    }
}
void meniuInitial() // Claudiu
{
    char cmnd[5];
    initwindow(1300,900);
    borduraGrafica(10,5); // este o functie prin care avem un meniu dinamic cand incepem rularea proiectului,
    // iar cei doi parametri sunt culorile pe care le alegem pentru cele 2 borduri si meniu
    cleardevice();        //curata ecranul, il readuce la starea initiala
    setbkcolor(0);        // seteaza culoarea 0=negru pentru noul ecran
    settextstyle(1,0,6);   //seteaza stilul textului pentru urmatorul mesaj
    outtextxy(130,110,"WELCOME"); // afisam un mejas de preintampinare de cele 2 dimnesiuni . ale primilor 2 paramtri
    settextstyle(2,1,8);
    outtextxy(100,200,"to our project");
    settextstyle(2,1,8);
    delay(2500);          //decide cat timp este afisat mesajul de intaminare
    cleardevice();
    setbkcolor(6);
}
void deseneazaCerc(Nod *arbore,int centrux, int centruy, int raza, int adancime, int lungime,int directie) //Claudiu
{
    // functia primeste ca parametrii arborele, coordonatele centrului cercului, lungimea razei,
    // o lungime care in functie de raza si centru va determina si lungimea liniei , si directia(stanga sau dreapta)
    // care la inceput va fi 0, pentru ca primul nod nu va fi radacina arborelui si va fi pozitionat in centru
    char aux[11];
    strcpy(aux,arbore->value.c_str()); // copiem valorile din stringul arbore in sirul de tip char aux
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,1);//stilul textului
    settextjustify(CENTER_TEXT,CENTER_TEXT); // alinierea textului
    setbkcolor(BLACK) ;
    outtextxy(centrux,centruy,aux);
    circle(centrux,centruy,raza);
    if(directie)
    {
        if(directie == 1) //daca directia este 1, adica spre stanga, setam paramterii astfel incat
            //sa putem desena arborele corespunzator
            line(centrux,centruy-raza,centrux+2*lungime+raza,centruy-adancime);
        else // sau spre dreapta in celalalt caz
            line(centrux,centruy-raza,centrux-2*lungime-raza,centruy-adancime);
    }
}
void deseneazaArbore(Nod *arbore, int centrux, int centruy, int raza, int adancime, int lungime, int directie) //CLAUDIU
{
    // primeste ca parametrii arborele, coordonatele mijlocului de sus ale graficului
    // adancimea si lungimea influenteaza modul in care vom trasa liniile , iar directia va fi cea care va decide
    //unde plasam nodul
    if(arbore->left != NULL)
        deseneazaArbore(arbore->left,centrux-raza-lungime,centruy+raza+adancime,raza,adancime,lungime/2,1);
    deseneazaCerc(arbore,centrux,centruy,raza,adancime,lungime,directie);
    if(arbore->right != NULL)
        deseneazaArbore(arbore->right,centrux+raza+lungime,centruy+raza+adancime,raza,adancime,lungime/2,2);
    //functia este recursiva si astfel incepe sa deseneze cu cel mai din stanga elemene al arborelui
    // ca in parcurgerea inordine
}
void arboreRandom(int numar_random) //CLAUDIU
{
    if(numar_random==1)
        strcpy(expresie, "1+2");
    if(numar_random==2)
        strcpy( expresie,"1*2");
    if(numar_random==3)
        strcpy( expresie, "1/2");
    if(numar_random==4)
        strcpy( expresie, "1^2");
    if(numar_random==5)
        strcpy( expresie, "1+2*3+5/6");
    if(numar_random==6)
        strcpy( expresie, "1+2/6*4+3");
    if(numar_random==7)
        strcpy( expresie, "1+2+36/45*4");
    if(numar_random==8)
        strcpy( expresie, "9+6/34*3^2");
    if(numar_random==9)
        strcpy( expresie, "22+23/54-35");
    if(numar_random==10)
        strcpy(expresie, "1+2+43-34");
}

int main()
{
    int afis=0; // arata daca vrem sa citim sau sa afisam o expresie random
start:
    meniuInitial();// un mic intro de bun venit
    int x,y;
    FormaPostFixata[0] = ',';
    if(afis==0)
        cin.getline(expresie, 255);
    ConversieFormaPoloneza();
    Nod* arbore = CreareArbore();
    setcolor(WHITE);
    for(int i=1; i<=5; i++) //construim un buton
        rectangle(10+i,10+i,190-i,70-i);
    outtextxy(20,30,"NEW TREE");
    setcolor(WHITE);
    for(int i=1; i<=5; i++) //construim alt buton
        rectangle(10+i,80+i,190-i,120-i);
    outtextxy(20,90,"Example");
    deseneazaArbore(arbore,770,70,25,60,300,0);

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            //daca am apasat click
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(x >10 && x<190 && y>10 && y<70) // daca suntem in butonul de New Tree
            {
                afis=0;
                cleardevice();
                clearmouseclick(WM_LBUTTONDOWN);
                goto start;
            }
        }
        if (ismouseclick(WM_LBUTTONDOWN))
        {

            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(x >10 && x<190 && y>80 && y<120) // daca suntem in butonul de Example
            {
                cleardevice();
                clearmouseclick(WM_LBUTTONDOWN);
                int numar_random = rand()%10;//luam random una din cele 10 expresii scrise mai jos
                afis = 1;//spunem programului ca va afisa arborele pentru o expresie data de noi, nu citita
                arboreRandom(numar_random);
                goto start;
            }

        }
    }

    delay(10000);
    return 0;
}
