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
  long id;
  double min;
  double max;
  double moy;
  int step;
  int minus;
} Data;

typedef struct d2arbre
{
  struct d2arbre *fr;
  struct d2arbre *fl;
  int h;
  Data *camioneur;
} DataTree;

DataTree *makeTree (Data * tetelle)
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
  branche->h = 1;
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


void moyMaker(DataTree * OK)
{
  if (OK != NULL)
    {
      OK->camioneur->moy = OK->camioneur->moy / OK->camioneur->step;
      moyMaker(OK->fr);
      moyMaker(OK->fl);
    }
}


// Fonction pour obtenir la hauteur d'un noeud
int height(DataTree* node) {
    if (node == NULL)
        return 0;
    return node->h;
}

// Fonction pour calculer l'équilibre d'un noeud
int getBalance(DataTree* node) {
    if (node == NULL)
        return 0;
    return height(node->fl) - height(node->fr);
}

// Fonction pour effectuer une rotation simple à droite
DataTree* rightRotate(DataTree* y) {
    DataTree* x = y->fl;
    DataTree* T2 = x->fr;

    // Rotation
    x->fr = y;
    y->fl = T2;

    // Mise à jour des hauteurs
    y->h = 1 + (height(y->fl) > height(y->fr) ? height(y->fl) : height(y->fr));
    x->h = 1 + (height(x->fl) > height(x->fr) ? height(x->fl) : height(x->fr));

    return x;
}

// Fonction pour effectuer une rotation simple à gauche
DataTree* leftRotate(DataTree* x) {
    DataTree* y = x->fr;
    DataTree* T2 = y->fl;

    // Rotation
    y->fl = x;
    x->fr = T2;

    // Mise à jour des hauteurs
    x->h = 1 + (height(x->fl) > height(x->fr) ? height(x->fl) : height(x->fr));
    y->h = 1 + (height(y->fl) > height(y->fr) ? height(y->fl) : height(y->fr));

    return y;
}
/*
// Fonction pour insérer un noeud dans un AVL
struct DataTree* insert(struct Node* node, int key) {
    if(node == NULL)
        return newNode(key);

    if(key < node->key){
        node->left = insert(node->left, key);
    }
    else if(key > node->key){
        node->right = insert(node->right, key);
    }
    else{
        return node;
    }
    // Mise à jour de la hauteur du noeud actuel
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Obtenir le facteur d'équilibre du noeud pour savoir si l'équilibrage est nécessaire
    int balance = getBalance(node);

    // Rééquilibrage
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
*/
DataTree *addNoeud (DataTree * racine, Data * tetelle)
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
    
  
  if (tetelle->id < racine->camioneur->id)
    {
      racine->fl = addNoeud(racine->fl, tetelle);
    }
  else if (tetelle->id > racine->camioneur->id)
    {
      racine->fr = addNoeud(racine->fr, tetelle);
    }
  else{
    racine->camioneur->step++;
    racine->camioneur->moy = tetelle->moy + racine->camioneur->moy;
    if(tetelle->min < racine->camioneur->min){
    	racine->camioneur->min = tetelle->min;
    }
    if(tetelle->max > racine->camioneur->max){
    	racine->camioneur->max = tetelle->max;
    }
    return racine;
  }
 
  racine->h = 1 + (height(racine->fl) > height(racine->fr) ? height(racine->fl) : height(racine->fr));
  
  int balance = getBalance(racine);
  
  
  if (balance > 1 && tetelle->id < racine->fl->camioneur->id){
        return rightRotate(racine);
  }
  if (balance < -1 && tetelle->id > racine->fr->camioneur->id){
        return leftRotate(racine);
  }
  if (balance > 1 && tetelle->id > racine->fl->camioneur->id) {
        racine->fl = leftRotate(racine->fl);
        return rightRotate(racine);
  }
  if (balance < -1 && tetelle->id < racine->fr->camioneur->id) {
        racine->fr = rightRotate(racine->fr);
        return leftRotate(racine);
  }  
  
  
  return racine;


}

DataTree * getData (FILE * cutFile, DataTree * root)
{

  char ligne[LNOM + LPREN];
  Data *tetelle = NULL;

  while (fgets (ligne, sizeof (ligne), cutFile) != NULL)
    {

      char *token = strtok(ligne, ";");
      tetelle = malloc (sizeof (Data));
      
      if (token == NULL)
	{
	  continue;
	}
	tetelle->id = atof(token);
      token = strtok (NULL, ",");

      if (token == NULL)
	{
	  continue;
	}

      
      tetelle->moy = atof(token);
      tetelle->min = tetelle->moy;
      tetelle->max = tetelle->moy;
      tetelle->step = 1;
      
      //tetelle->nom[sizeof (tetelle->nom) - 1] = '\0';



      root = addNoeud(root, tetelle);
      

    }
	//root = reBalanceTree(root);
	moyMaker(root);
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



void swap(Data **a, Data* *b) {
    Data* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Data* arr[], int low, int high) {
    Data* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->minus < pivot->minus) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void qwicksort(Data* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        qwicksort(arr, low, pi - 1);
        qwicksort(arr, pi + 1, high);
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
   
    if(camTree->camioneur->moy > longuer[0]->moy){
        longuer[0] = camTree->camioneur;
        Data* temp = NULL;
        qwicksort(longuer,0,9);
        
    }
    return longuer;
    
}



void parcoursInfixe (DataTree * OK)
{
  if (OK != NULL)
    {
      parcoursInfixe (OK->fl);
      printf ("%d;%f;%f;%f;%d\n", OK->camioneur->id, OK->camioneur->min, OK->camioneur->max, OK->camioneur->moy, OK->camioneur->step);
      parcoursInfixe (OK->fr);
    }
}

void finishdata(DataTree* OK, Data** endtab){
	if(OK != NULL){
		finishdata(OK->fl, endtab);
		finishdata(OK->fr, endtab);
		int minmax = OK->camioneur->max - OK->camioneur->min;
		if(endtab[0]->minus < minmax){
			endtab[0] = OK->camioneur;
			endtab[0]->minus = minmax;
			qwicksort(endtab,0,49);
		}
	}
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
	for(int i = 0; i<50;i++){
		free(tab[i]);
	}
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

	Data * endtab[50];
	for(int i = 0; i<50; i++){
		endtab[i] = malloc(sizeof(Data));
		endtab[i]->minus = 0;
	}
  DataTree *OK = getData (cutFile, NULL);
  fclose (cutFile);
  
  finishdata(OK, endtab);
  for(int i = 49; i>=0; i--){
		printf("%f %f %f %d\n", endtab[i]->min, endtab[i]->max, endtab[i]->moy, endtab[i]->id);
	}
  
  
  fatman(OK);
  littleboy(endtab);
  return 0;
}
