#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arvore {  // Criacao da struct arvore genealogica
       char *dado;
       struct arvore * esq;
       struct arvore * dir;
};

struct arvore *procurado = NULL;

struct arvore* criaArvore(){
       return NULL; // cria uma arvore com nenhum elemento        
}

void menu(){
    // Montagem do menu
    printf("MENU \n");
    printf("1 Insecao \n"); // opcao 1
    printf("2 Imprimir antepassados de um individuo\n"); // opcao 2
    printf("3 Imprimir arvore genalogica em Labelled Bracketing\n"); // opcao 3
}

void busca(struct arvore **no, char *s){  
   if(*no != NULL){
          if(strcmp((*no)->dado,s) == 0){
             if((*no)->esq == NULL && (*no)->dir == NULL){
                procurado = *no;
             } else {
                printf("Ja possui pai e mae");
             }
         } else {
             if((*no)->esq != NULL){
                 busca(&((*no)->esq), s); 
             }
             if((*no)->dir != NULL){
                 busca(&((*no)->dir), s);
             }
         }
    } 
}

// Função que insere um dado na árvore de forma recursiva
void insercao(struct arvore **no, char *filho, char *pai, char *mae){ // Opcao 1
  struct arvore *noPai = (struct arvore*)malloc(sizeof(struct arvore)); // Aloca memória para a struct
  noPai->dado = pai;
  noPai->esq = NULL; 
  noPai->dir = NULL;      
         
  struct arvore *noMae = (struct arvore*)malloc(sizeof(struct arvore)); // Aloca memória para a struct
  noMae->dado = mae;
  noMae->esq = NULL; 
  noMae->dir = NULL; 
  
  if(*no == NULL){ // é raiz
    *no = (struct arvore*)malloc(sizeof(struct arvore)); // Aloca memória para a struct
    (*no)->dado = filho;
    (*no)->esq = noPai; 
    (*no)->dir = noMae;
  } else {    
     struct arvore ** atual = no;
     
     busca(no, filho);
     
     if(procurado != NULL){                         
        *no = procurado;
        (*no)->esq = noPai;
        (*no)->dir = noMae; 
        procurado = NULL;            
  }
}
}

void impressaoLabelledBracketing(struct arvore * no){  // Opcao 3
     printf("[");
     if(no!=NULL)
     {
        printf("%s ", no->dado); 
        impressaoLabelledBracketing(no->esq); 
        impressaoLabelledBracketing(no->dir); 
     }
     printf("]");
}

void imprimirAntepassados(struct arvore **no, char *s){  // Opcao 2
   if(*no != NULL){
        if(strcmp((*no)->dado,s) == 0){
             impressaoLabelledBracketing(*no);
             
         } else {
             if((*no)->esq != NULL){
                 imprimirAntepassados(&((*no)->esq), s); 
             }
             if((*no)->dir != NULL){
                 imprimirAntepassados(&((*no)->dir), s);
             }
         }
    } else {
       printf("Arvore vazia");
    }
}

int main(){
  int opcao, chave, dado, quantidade, i;
  struct arvore *raiz = criaArvore(); // cria uma arvore com nenhum dado
  char *filho = (char*)calloc(50,sizeof(char));
  char *pai = (char*)calloc(50,sizeof(char));
  char *mae = (char*)calloc(50,sizeof(char));
  
  printf("Forneca o numero de 3 enuplas que deseja adicionar\n");
  scanf("%d", &quantidade);
  for(i = 0 ; i < quantidade ; i++){
     printf("\nForneca o nome do filho %do\n", i+1);
     scanf("%s", filho);
     printf("Forneca o nome do pai %do\n", i+1);
     scanf("%s", pai);
     printf("Forneca o nome da mae %do\n", i+1);
     scanf("%s", mae);
     insercao(&raiz, filho, pai, mae);
  }
  
  menu(); // Cria o menu para o usuario escolher a opcao
  scanf("%d", &opcao);

  while (opcao >= 1 && opcao <= 5){     
      char *filho = (char*)calloc(50,sizeof(char));
      char *pai = (char*)calloc(50,sizeof(char));
      char *mae = (char*)calloc(50,sizeof(char));
      switch(opcao){
          case 1: 
               printf("\nForneca o numero de 3 enuplas que deseja adicionar\n");
               scanf("%d", &quantidade);
               for(i = 0 ; i < quantidade ; i++){
                   printf("\nForneca o nome do filho %do\n", i+1);
                   scanf("%s", filho);
                   printf("Forneca o nome do pai %do\n", i+1);
                   scanf("%s", pai);
                   printf("Forneca o nome da mae %do\n", i+1);
                   scanf("%s", mae);
                   printf("insercao\n");
                   insercao(&raiz, filho, pai, mae);
               }
               printf("\n\n");
               break;
          case 2:
               printf("Forneca o nome do individuo que deseje ver os antepassados\n");
               scanf("%s", filho);
               imprimirAntepassados(&raiz, filho);
               printf("\n\n");
               break;
          case 3:
               printf("\nImpressao da arvore genealocica em Labelled Bracketing \n");
               impressaoLabelledBracketing(raiz);
               printf("\n\n");
               break;
      }
      
      menu();
      scanf("%d", &opcao);
  }
  return 0;
  system("PAUSE");	
}
 

