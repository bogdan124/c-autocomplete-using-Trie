#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct TreeNODE{
  char data;
  int final_string;
  struct TreeNODE * next[26];
};
typedef struct TreeNODE T__NODE;

struct ADDRESS_INT{
  T__NODE * adrressWhereRemain;
  int isLastNode;
};
typedef struct ADDRESS_INT ADDRESS_INT;

char * alocSpace(int n);
T__NODE * alocSpaceT__NODE(int n);
T__NODE initTRIE(char firstletter,int final_string);
void createNodesChains(T__NODE rootTR,char * whatWordsToPut);
ADDRESS_INT lookForWord(T__NODE rootTR,char * word);
void showALL(T__NODE * rootTR,char * stiva);
void fileDict(char * filename,T__NODE rootTR);
void push(char * stiva,char add);
void pop(char * stiva);

int main(int a,char ** filename){
  char * cunvantPrime;
  int final_string;
  T__NODE rootTR;
  ADDRESS_INT adress;
  char * stiva;
  stiva=alocSpace(100);

  if(filename[1]==NULL){
    printf("Please provide a dictionary of words as an argument!!!\n" );
    exit(1);
  }


  cunvantPrime=alocSpace(100);
  printf("Dati un cuvant:");
  scanf("%s",cunvantPrime);
  rootTR=initTRIE(cunvantPrime[0],final_string);
  fileDict(filename[1],rootTR);
  printf("\n");
  adress=lookForWord(rootTR,cunvantPrime);
  if(adress.isLastNode!=1){
    printf("Este corect %s sau vrei sa scrii?\n",cunvantPrime);
    if(strlen(cunvantPrime)>1){
      for(int i=0;i<strlen(cunvantPrime)-1;i++){
        push(stiva,cunvantPrime[i]);
      }
    }
    showALL(adress.adrressWhereRemain,stiva);
    printf("\n");
  }else{
    printf("Nu am gasit ceva asemanator in dictionarul furnizat!!!\n");
  }

}


T__NODE initTRIE(char firstletter,int final_string){
  T__NODE rootTR;
  T__NODE * nextNode;
  rootTR.data=firstletter;
  rootTR.final_string=final_string;
  //o sa initializez fiecare node din array cu un alt TreeNODE
  //dar tree fiecare din cele 26 de tree noduri va corespunde unei litere din alfabetul englez
  for(int i=0;i<26;i++){

    nextNode=alocSpaceT__NODE(1);
    nextNode->data=(char)(97+i);//97 este codul ascii lui a ,o sa folosesc doar literele mici ,fara cele mari.
    nextNode->final_string=1;
    rootTR.next[i]=nextNode;
  }
  return rootTR;
}

void createNodesChains(T__NODE rootTR,char * whatWordsToPut){
  T__NODE * adresaUndeSunt;
  T__NODE * auxADDR;
  T__NODE * auxNOW;
  auxADDR=&rootTR;



    for(int j=0;j<strlen(whatWordsToPut)-1;j++){
      for(int y=0;y<26;y++){
        if(auxADDR->next[y]!=NULL && auxADDR->next[y]->data==whatWordsToPut[j]){

              adresaUndeSunt=auxADDR->next[y];
              auxADDR=adresaUndeSunt;
              break;
            }else  if(auxADDR->next[y]==NULL){
              auxADDR->final_string=0;
              auxNOW=alocSpaceT__NODE(1);
              auxNOW->final_string=1;
              auxNOW->data=whatWordsToPut[j];
              auxADDR->next[y]=auxNOW;
              auxADDR=auxNOW;
              break;
        }
      }
    }

}
/* cauta un cuvant si returneza adresa unde a ramas*/
ADDRESS_INT lookForWord(T__NODE rootTR,char * word){

  T__NODE * auxNOW;
  ADDRESS_INT adress;

  auxNOW=&rootTR;
  for(int j=0;j<strlen(word);j++){

    for(int y=0;y<26;y++){
        if(auxNOW->next[y]!=NULL){
          if(auxNOW->next[y]->data==word[j]){
            auxNOW=auxNOW->next[y];
            break;
          }
      }
    }

  }
  adress.isLastNode=auxNOW->final_string;
  adress.adrressWhereRemain=auxNOW;
  return adress;
}


/*aici incarci dictionarul*/
void fileDict(char * filename,T__NODE rootTR){

FILE * f;
char * store;
size_t st=90;
int lineZ=1;
store=alocSpace(100);
f=fopen(filename,"r");
while(lineZ>=0){
  lineZ=getline(&store,&st,f);
  createNodesChains(rootTR,store);
}

fclose(f);
}

void push(char * stiva,char add){

  stiva[strlen(stiva)]=add;

  stiva[strlen(stiva)+1]='\0';

}

void pop(char * stiva){


  if(strlen(stiva)!=0)
  {
      stiva[strlen(stiva)-1]='\0';
  }


}

void showALL(T__NODE * rootTR,char * stiva){


      if(rootTR->final_string==1){
        printf("%s",stiva );
        printf("%c",rootTR->data);
        printf("\n");
      }
    for(int y=0;y<26;y++){
      if(rootTR->next[y]){
        push(stiva,rootTR->data );
        if(rootTR->final_string==1){
            push(stiva,rootTR->data );
        }
        showALL(rootTR->next[y],stiva);

          pop(stiva);


      }
    }



}


/*
void deleteWord(T__NODE * rootT,char * stiva){

  for(int i=0;i<strlen(stiva);i++){
       lookForWord(T__NODE rootTR,stiva[i]);
  }


}
*/


char * alocSpace(int n){

  char * aloc;
  aloc=(char *)malloc(n*sizeof(char));
  if(aloc==NULL){
    exit(1);
  }

  return aloc;
}

T__NODE * alocSpaceT__NODE(int n){

  T__NODE * aloc;
  aloc=(T__NODE *)malloc(n*sizeof(T__NODE));
  if(aloc==NULL){
    exit(1);
  }

  return aloc;
}
