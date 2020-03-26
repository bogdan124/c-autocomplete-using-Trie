#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Intai de toate pot sa zic ca m-am complicat putin
deoarece puteam sa pun adresele cu literele noi care vin in
locul lor predestinat in alfabet .
In schimb eu le-am pus in primul loc gasit liber.


*/

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
void showALL(T__NODE * rootTR,char * cunvantPrime,int swicth,int firstPrint);
void fileDict(char * filename,T__NODE rootTR);


int main(int a,char ** filename){
  char * cunvantPrime;
  int final_string;
  T__NODE rootTR;
  ADDRESS_INT adress;

  cunvantPrime=alocSpace(100);
  printf("Dati un cuvant:");
  scanf("%s",cunvantPrime);
  rootTR=initTRIE(cunvantPrime[0],final_string);
  fileDict(filename[1],rootTR);
  printf("\n");
  adress=lookForWord(rootTR,cunvantPrime);
  if(adress.isLastNode!=1){
    printf("Vrei sa scrii?\n" );
    showALL(adress.adrressWhereRemain,cunvantPrime,1,1);
    printf("\n");
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
ADDRESS_INT lookForWord(T__NODE rootTR,char * word){

  T__NODE * auxNOW;
  ADDRESS_INT adress;

  auxNOW=&rootTR;
  for(int j=0;j<strlen(word);j++){

    for(int y=0;y<26;y++){
        if(auxNOW->next[y]!=NULL){
          if(auxNOW->next[y]->data==word[j]){
        //    printf("%c%d",auxNOW->next[y]->data ,auxNOW->next[y]->final_string);
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



void showALL(T__NODE * rootTR,char * cunvantPrime,int swicth,int firstPrint){


  if(rootTR){
    if(rootTR->final_string==1){
        swicth=1;
    }

    if(firstPrint==1){
    
      firstPrint=0;
    }else{
      printf("%c",rootTR->data );
    }
    if(swicth==1){
      printf("\n%s",cunvantPrime);
      swicth=0;
    }
    for(int y=0;y<26;y++){
      showALL(rootTR->next[y],cunvantPrime,swicth,firstPrint);
    }

  }

}




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
