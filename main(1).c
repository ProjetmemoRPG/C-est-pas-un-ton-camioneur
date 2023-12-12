    //fsetpos(cutFile, const fpos_t *pos);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define LNOM 25
#define LPREN 25
#define LVILLE 45

typedef struct camioneurD1{
    char nom[LNOM];
    char pren[LPREN];
    int nbtrajet;
}D1cam;

typedef struct camioneurD2{
    char nom[LNOM + LPREN];
    int dist;
}D2cam;

typedef struct trajetL{
    char start[LVILLE];
    char end[LVILLE];
    int dist;
}Ltraj;

typedef struct villeT{
    char ville[LVILLE];
    int prise;
}Tville;

typedef struct TrajetS{
    char ville[LVILLE];
    int min;
    int max;
    int moy;
}Sville;

typedef struct intListe{
    struct intListe next;
    int val;
}IntLane

typedef struct d2arbre{
    struct d2arbre* fr;
    struct d2arbre* fl;
    struct d2arbre* parent;
    D2cam* camioneur;
}D2tree;

D2tree* makeTree(D2cam* tetelle){
    if(D2cam == NULL){
        exit 3;
    }
    D2tree* branche = malloc(sizeof(D2tree));
    branche->fr = NULL;
    branche->fl = NULL;
    branche->camioneur = tetelle;
    
    return branche;
}

D2cam* getCamioneur(FILE* cutfile){
    D2cam* tetelle = malloc(sizeof(D2cam));
    
    //inséré ici le truc qui va permettre recup une ligne
    
    return tetelle;
}








int main()
{
    const char* nameFile = "cutcsv.txt";
    FILE* cutFile = fopen(nameFile, "r");
    if (!cutFile) exit(EXIT_FAILURE);
    
    D1cam* camTab;
    
    camTab = trisD1(cutFile);
    
    return 0;
}





