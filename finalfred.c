
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

#define LNOM 25
#define LPREN 25
#define LVILLE 45
#define CARACTERES 100

typedef struct data
{
  char nom[CARACTERES];
  double dist;
} Data;

typedef struct d2arbre
{
  struct d2arbre *fr;
  struct d2arbre *fl;
  struct d2arbre *parent;
  Data *camioneur;
} DataTree;

DataTree *
makeTree (Data * tetelle)
{
  if (tetelle == NULL)
    {
      printf ("exit 3");
      exit (3);
    }
  DataTree *branche = malloc (sizeof(DataTree));
  if (branche == NULL)
    {
      printf ("exit 4");
      exit (4);
    }
  branche->fr = NULL;
  branche->fl = NULL;
  branche->camioneur = tetelle;
  /*
     if(branche->camioneur == NULL){
     printf("exit 5");
     exit(5);
     }
     branche->camioneur->dist = tetelle->dist;
     strncpy(branche->camioneur->nom, tetelle->nom, sizeof(branche->camioneur->nom));
   */
  return branche;
}



int
getHeight (DataTree * noeud)
{
  if (noeud == NULL)
    {
      return 0;
    }

  int a = getHeight (noeud->fl);
  int b = getHeight (noeud->fr);
  if (a < b)
    {
      a = b;
    }

  return 1 + a;
}

int
getBalance (DataTree * noeud)
{
  if (noeud == NULL)
    {
      return 0;
    }
  return getHeight (noeud->fl) - getHeight (noeud->fr);
}


DataTree *
rotationD (DataTree * y)
{
  DataTree *x = y->fl;
  DataTree *temp = x->fr;
  x->fr = y;
  y->fl = temp;

  return x;
}

DataTree *
rotationL (DataTree * x)
{
  DataTree *y = x->fr;
  DataTree *temp = y->fl;
  y->fl = x;
  x->fr = temp;

  return y;
}


DataTree *balanceTree (DataTree * noeud)
{
  int balanceFactor = getBalance (noeud);

  // Cas de dC)sC)quilibre C  gauche
  if (balanceFactor > 1)
    {
      if (getBalance (noeud->fl) >= 0)
	{
	  return rotationD (noeud);
	}
      else
	{
	  noeud->fl = rotationL (noeud->fl);
	  return rotationD (noeud);
	}
    }
  // Cas de dC)sC)quilibre C  droite
  else if (balanceFactor < -1)
    {
      if (getBalance (noeud->fr) <= 0)
	{
	  return rotationL (noeud);
	}
      else
	{
	  noeud->fr = rotationD (noeud->fr);
	  return rotationL (noeud);
	}
    }

  return noeud;
}

DataTree *reBalanceTree (DataTree * racine)
{
  if (racine->fl != NULL)
    {
      reBalanceTree (racine->fl);
    }
  if (racine->fr != NULL)
    {
      reBalanceTree (racine->fr);
    }
  balanceTree (racine);
}


DataTree *
addNoeud (DataTree * racine, Data * tetelle)
{
  if (tetelle == NULL)
    {
      printf ("exit 6");
      exit (6);
    }
  if (racine == NULL)
    {

      return makeTree (tetelle);

    }

  int a = strcmp (racine->camioneur->nom, tetelle->nom);
  if (0 < a)
    {
      racine->fl = addNoeud (racine->fl, tetelle);
    }
  else if (0 > a)
    {
      racine->fr = addNoeud (racine->fr, tetelle);
    }
    else{
    racine->camioneur->dist = tetelle->dist + racine->camioneur->dist;
    }
  return racine;


}

DataTree *
getData (FILE * cutFile, DataTree * root)
{

  char ligne[LNOM + LPREN];
  Data *tetelle = NULL;

  while (fgets (ligne, sizeof (ligne), cutFile) != NULL)
    {

      char *token = strtok(ligne, ";");
      tetelle = malloc (sizeof (Data));
      tetelle->dist = atof(token);
      if (token == NULL)
	{
	  continue;
	}

      token = strtok (NULL, ",");

      if (token == NULL)
	{
	  continue;
	}

      strncpy (tetelle->nom, token, sizeof(tetelle->nom));
      //tetelle->nom[sizeof (tetelle->nom) - 1] = '\0';



      root = addNoeud(root, tetelle);
      //root = reBalanceTree(root);

    }

  return root;
}


int
nbNeu (DataTree * root)
{
  if (root == NULL)
    {
      printf ("exit 7");
      return 0;
    }
  int a = 0, b = 0;
  if (root->fl != NULL)
    {
      a = nbNeu (root->fl);
    }
  if (root->fr != NULL)
    {
      b = nbNeu (root->fr);
    }
  return a + b + 1;
}

DataTree *
D2tris (FILE * cutFile)
{
  Data *tetelle = NULL;
  DataTree *camTree = NULL;
  char line[LNOM + LPREN];
  do
    {
      printf ("%s\n", line);
    }
  while (fgets (line, sizeof (line), cutFile) != NULL);	//temps que on a pas fini de lire le fichier

  return camTree;
}

void
parcoursPrefixe (DataTree * OK)
{
  if (OK != NULL)
    {
      printf ("%s", OK->camioneur->nom);
      parcoursPrefixe (OK->fr);
      parcoursPrefixe (OK->fl);
    }
}



void swap(Data **a, Data* *b) {
    Data* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Data* arr[], int low, int high) {
    Data* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->dist < pivot->dist) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(Data* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}


Data** distMax(DataTree* camTree, Data** longuer){
    if(camTree == NULL){
    	printf("exit 8");
    	exit(8);
    }
    
    if(camTree->fl != NULL){
        distMax(camTree->fl,longuer);
    }
    if(camTree->fr != NULL){
        distMax(camTree->fr,longuer);
    }
   
    if(camTree->camioneur->dist > longuer[0]->dist){
        longuer[0] = camTree->camioneur;
        Data* temp = NULL;
        quicksort(longuer,0,9);
        
    }
    return longuer;
    
}


void fatman(DataTree* root){
	if(root->fl != NULL){
		fatman(root->fl);
	}
	if(root->fr != NULL){
		fatman(root->fr);
	}
	free(root->camioneur);
	free(root);
}

void littleboy(Data** tab){
	for(int i = 0; i<10;i++){
		free(tab[i]);
	}
	free(tab);
}
int main ()
{
  const char *nameFile = "temp.txt";
  FILE *cutFile = fopen (nameFile, "r");
  if (!cutFile)
    {
      printf ("foirage de l'ouverture");
      exit (EXIT_FAILURE);
    }


  DataTree *OK = getData (cutFile, NULL);
  //printf("%d\n", nbNeu(OK));
  
  Data** camTab = malloc(sizeof(Data*)*10);
  for(int i=0;i<10;i++){
  	camTab[i] = malloc(sizeof(Data));
  	camTab[i]->dist = 0;
  }
  
  camTab = distMax(OK, camTab);
  for(int i = 0;i<10;i++){
     printf("%f;%s",camTab[i]->dist, camTab[i]->nom);
  }
   
  fclose (cutFile);
  
  fatman(OK);
  littleboy(camTab);
  
  return 0;
}
