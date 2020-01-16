#include "header.hpp"
#include "functions.hpp"

void borduraGrafica(int j,int k) {
    int i,r=10;
    for(i=10; i<getmaxx(); i++)
    {
        setcolor(j);
        circle(10,i,r);
        circle(getmaxx()-r,i,r);
        setcolor(k);
        circle(i,10,r);
        circle(i,getmaxy()-r,r);
        delay(1);
    }
}

void meniuInitial() {
     int gdriver=0, gmode;
    int value;
    char cmnd[5];
    initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
    borduraGrafica(10,5); // este o functie prin care avem un meniu dinamic cand incepem rularea proiectului,
                          // iar cei doi parametri sunt culorile pe care le alegem pentru cele 2 borduri si meniu
    cleardevice();        //curata ecranul, il readuce la starea initiala
    setbkcolor(0);        // seteaza culoarea 0=negru pentru noul ecran
    settextstyle(1,0,6);   //seteaza stilul textului pentru urmatorul mesaj
    outtextxy(130,110,"WELCOME"); // afisam Bun Venit de cele 2 dimnesiuni . ale primilor 2 paramtri
    settextstyle(2,1,8);
    outtextxy(100,200,"INTO THE PORTAL");
    settextstyle(2,1,8);
    delay(2500);          //decide cat timp este afisat mesajul de intaminare
    cleardevice();
    setbkcolor(6);
    midx=getmaxx()/2;
}

void deseneazaCerc(Nod *arbore,int centrux, int centruy, int raza, int adancime, int lungime,int directie) {
    char aux[11];
//    aux = arbore->value;
    strcpy(aux,arbore->value.c_str());
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,1);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setbkcolor(BLACK) ;
    outtextxy(centrux,centruy,aux);
    circle(centrux,centruy,raza);
    if(directie)
    {
        if(directie == 1)
        {
            line(centrux,centruy-raza,centrux+2*lungime+raza,centruy-adancime);
        }
        else
        {
            line(centrux,centruy-raza,centrux-2*lungime-raza,centruy-adancime);
        }
    }
}

void deseneazaArbore(Nod *arbore, int centrux, int centruy, int raza, int adancime, int lungime, int directie) {
    if(arbore->left != NULL)
        deseneazaArbore(arbore->left,centrux-raza-lungime,centruy+raza+adancime,raza,adancime,lungime/2,1);

    deseneazaCerc(arbore,centrux,centruy,raza,adancime,lungime,directie);
    if(arbore->right != NULL)
        deseneazaArbore(arbore->right,centrux+raza+lungime,centruy+raza+adancime,raza,adancime,lungime/2,2);
}
