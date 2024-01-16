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
  char* name;
  long start;
  long nbtraj;
} CityData;


typedef struct Carbre
{
  struct Carbre *fr;
  struct Carbre *fl;
  int h;
  CityData *city;
} CityTree;


int height(CityTree* node){
    if (node == NULL)
        return 0;
    return node->h;
}

// Fonction pour calculer l'équilibre d'un noeud
int getBalance(CityTree* node){
    if (node == NULL)
        return 0;
    return height(node->fl) - height(node->fr);
}

// Fonction pour effectuer une rotation simple à droite
CityTree* rightRotate(CityTree* y){
    CityTree* x = y->fl;
    CityTree* T2 = x->fr;

    // Rotation
    x->fr = y;
    y->fl = T2;

    // Mise à jour des hauteurs
    y->h = 1 + (height(y->fl) > height(y->fr) ? height(y->fl) : height(y->fr));
    x->h = 1 + (height(x->fl) > height(x->fr) ? height(x->fl) : height(x->fr));

    return x;
}

// Fonction pour effectuer une rotation simple à gauche
CityTree* leftRotate(CityTree* x){
    CityTree* y = x->fr;
    CityTree* T2 = y->fl;

    // Rotation
    y->fl = x;
    x->fr = T2;

    // Mise à jour des hauteurs
    x->h = 1 + (height(x->fl) > height(x->fr) ? height(x->fl) : height(x->fr));
    y->h = 1 + (height(y->fl) > height(y->fr) ? height(y->fl) : height(y->fr));

    return y;
}


CityData* Citymaker(char* Cname){
	CityData* ville = malloc(sizeof(CityData));
	ville->name = Cname;
	ville->start = 0;
	ville->nbtraj = 1;
	return ville;
}

CityTree* CityTreeMaker(char* Cname){
	CityTree* branche = malloc(sizeof(CityTree));
	branche->city = Citymaker(Cname);
	branche->fl = NULL;
	branche->fr = NULL;
	branche->h = 1;
	
	return branche;
}


CityTree* CityAdder(CityTree* racine, char* Cname){
	if(Cname == NULL){
		printf("exit 7");
		exit(7);
	}
	
	if(racine == NULL){
		racine = CityTreeMaker(Cname);
		return racine;
	}
	int a = strcmp(Cname, racine->city->name);
	//printf("|%s , %s|",Cname,racine->city->name);
	//printf("%d",a);
	if (a < 0)
    	{
      		racine->fl = CityAdder(racine->fl, Cname);
    	}
  	else if (a > 0)
    	{
      		racine->fr = CityAdder(racine->fr, Cname);
    	}
    	
	else{
		racine->city->nbtraj++;
		free(Cname);
		return racine;
	}
	/*
	racine->h = 1 + (height(racine->fl) > height(racine->fr) ? height(racine->fl) : height(racine->fr));
	
 
  printf("start rebalancing\n");
  int balance = getBalance(racine);
  int b = 0;
  
  if(racine->fl != NULL){
  	b = strcmp(Cname, racine->fl->city->name);
  }
  
  printf("t\n", balance);
 
  int c = 0;
  if(racine->fr != NULL){
  	printf("%p\n", racine->fr->city);
  	c = strcmp(Cname, racine->fr->city->name);
  }
  
  printf("end of comparaison\n");
  if (balance > 1 && b < 0){
        return rightRotate(racine);
  }
  if (balance < -1 && c < 0){
        return leftRotate(racine);
  }
  if (balance > 1 && b > 0) {
        racine->fl = leftRotate(racine->fl);
        return rightRotate(racine);
  }
  if (balance < -1 && c > 0) {
        racine->fr = rightRotate(racine->fr);
        return leftRotate(racine);
  }  
printf("end of rebalancing\n");
*/
	
  return racine;

}


CityTree * getData(FILE * cutFile, CityTree * root)
{
  char ligne[LNOM + LPREN];
  printf("\rcollecting data   \n");
  fgets (ligne, sizeof (ligne), cutFile);//skip la 1er ligne
  while (fgets (ligne, sizeof (ligne), cutFile) != NULL)
    {
	char* laputa = malloc(sizeof(char)*100);
      char *token = strtok(ligne, ",");
	strncpy(laputa, token, strlen(token));
	laputa[strlen(laputa) - 1] = '\0';//remouv le caractère de fin de ligne (en téhorie)
	
      root = CityAdder(root, laputa);
      
      
    }

  return root;
}



void prossess1(CityTree* root, char* Cname){
	if(root != NULL){
		int a = strcmp(root->city->name, Cname);
		if(a == 0){
			root->city->start++;
		}
		else if(a>0){
			prossess1(root->fl, Cname);
		}
		else if(a<0){
			prossess1(root->fr, Cname);
		}
	}
}


void prossessData(FILE * cutFile, CityTree * root)
{
  char ligne[LNOM + LPREN];
  //char* laputa = malloc(sizeof(char)*(100));//nom du camioneur
  printf("prossesing data   \n");
  
  while (fgets (ligne, sizeof (ligne), cutFile) != NULL)
    {

      char *laputa = strtok(ligne, ",");

	laputa[strlen(laputa) - 1] = '\0';//remouv le caractère de fin de ligne (en téhorie)
	
	prossess1(root, laputa);
      
    }
}

int
nbNeu (CityTree * root)
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


void swap(CityData **a, CityData* *b) {
    CityData* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(CityData* arr[], int low, int high) {
    CityData* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->nbtraj < pivot->nbtraj) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(CityData* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}



CityData** tenBest(CityTree* listVille, CityData** finaltab){
    if(listVille == NULL){
    	printf("exit 8");
    	exit(8);
    }
    
    if(listVille->fl != NULL){
        tenBest(listVille->fl,finaltab);
    }
    if(listVille->fr != NULL){
        tenBest(listVille->fr,finaltab);
    }
   
    if(listVille->city->nbtraj > finaltab[0]->nbtraj	){
        finaltab[0] = listVille->city;
        CityData* temp = NULL;
        quicksort(finaltab,0,9);
        
    }
    return finaltab;
    
}



int main ()
{
  const char *nameFile = "temp.txt";
  const char *nameFile2 = "depart.txt";
  FILE *cutFile = fopen (nameFile, "r");
  if (!cutFile)
    {
      printf ("foirage de l'ouverture");
      exit (EXIT_FAILURE);
    }

  printf("start\n");

  CityTree *OK = getData(cutFile, NULL);
  printf("end collecting\n");
  printf("%d\n", nbNeu(OK));
  
  printf("end collecting\n");
  
  fclose (cutFile);
  
  cutFile = fopen (nameFile2, "r");
  if (!cutFile)
    {
      printf ("foirage de l'ouverture");
      exit (EXIT_FAILURE);
    }
  
  prossessData(cutFile, OK);
  
  fclose(cutFile);
  
  CityData** finalTab = malloc(sizeof(CityData*)*10);
  
  for(int i = 0; i<10; i++){
  	finalTab[i] = Citymaker(NULL);
  }
  
  finalTab = tenBest(OK,finalTab);
  
  
  for(int i = 0; i<10; i++){
  	printf("%s;%d;%d\n", finalTab[i]->name, finalTab[i]->nbtraj, finalTab[i]->start);
  }
  
  

  
  //parcoursInfixe(OK);
  
  

  
  return 0;
}


