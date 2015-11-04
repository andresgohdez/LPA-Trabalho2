#include <stdio.h>
#include <stdlib.h>

struct arvore {  // Criacao da struct arvore
       int chave;
       struct arvore * esq;
       struct arvore * dir;
};

// Função que insere um dado na árvore de forma recursiva
void insercao(struct arvore **no, int chave){ // Opcao 1
  if(*no == NULL) // é raiz
  {
    *no = (struct arvore*)malloc(sizeof(struct arvore)); // Aloca memória para a struct
    (*no)->chave = chave;
    (*no)->esq = NULL; 
    (*no)->dir = NULL; 
  } else {
    if(chave < (*no)->chave){ // Se o número for menor então vai pra esquerda
       insercao(&(*no)->esq, chave);
    } else if(chave > (*no)->chave){ // Se o número for maior então vai pra direita
       insercao(&(*no)->dir, chave);
    } else {
       printf("Chave já existente");       
    }
  }
}

void remocao(struct arvore * no, int chave){ // Opcao 2
    struct arvore *atual = no;
    if(atual != NULL){
        struct arvore *anterior = NULL;
        while(atual != NULL && atual->chave != chave){  // Aponta para o no da arvore que possui a chave desejada
            anterior = atual;
            if (atual->chave >= chave){
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if(atual == NULL) {
             printf("Chave nao existente, impossivel remove-lo");
        } else {
             struct arvore *prox = atual->dir; 
             while(prox != NULL && prox->esq != NULL){ // pega o proximo numero ao atual
                 prox = prox->esq;
             }
             struct arvore *n; 
             if(prox != NULL){ // define o elemento que o anterior apontará
                 prox->esq = atual->esq;
                 n = atual->dir;
             } else {
                 n = atual->esq;
             }
             if(anterior->chave < chave) { // define-se se o anterior apontará pela esquerda ou pela direita
                 anterior->dir = n;
             } else {
                 anterior->esq = n;
             } 
             printf("A chave %d foi removido com sucesso", chave);
        }  
    }                         
}

void busca(struct arvore * no, int chave){ // Opcao 3
       if(no == NULL){
             printf("Chave nao encontrada\n");
       } else if(no->chave == chave){
              printf("Chave encontrada");
       } else if(no->chave < chave){
              busca(no->dir, chave);
       } else { 
              busca(no->esq, chave);
       }
}


void preOrdem(struct arvore * no){
     if(no!=NULL)
     {
        printf("%d ", no->chave); 
        preOrdem(no->esq); 
        preOrdem(no->dir); 
     }
}

void posOrdem(struct arvore * no){
     if(no!=NULL)
     {
        posOrdem(no->esq); 
        posOrdem(no->dir); 
        printf("%d ", no->chave); 
     }
}

void emOrdem(struct arvore * no){
     if(no!=NULL)
     {
        emOrdem(no->esq); 
        printf("%d ", no->chave); 
        emOrdem(no->dir); 
     }
}

void impressao(struct arvore * no){ // Opcao 4
    // Imprime os elementos de forma recursiva
    printf("Pre Ordem\n");
    preOrdem(no);
    printf("\nPos Ordem\n");
    posOrdem(no);
    printf("\nEm Ordem\n");
    emOrdem(no);
}  

void impressaoLabelledBracketing(struct arvore * no){ // Opcao 5
     printf("[");
     if(no!=NULL)
     {
        printf("%d ", no->chave); 
        impressaoLabelledBracketing(no->esq); 
        impressaoLabelledBracketing(no->dir); 
     }
     printf("]");
}

struct arvore* criaArvore(){
       return NULL; // cria uma arvore com nenhum elemento        
}

void menu(){
    // Montagem do menu
    printf("MENU \n");
    printf("1 Insecao \n");
    printf("2 Remocao \n");
    printf("3 Busca \n");
    printf("4 Impressao da arvore em Pre Ordem, Pos Ordem e Em Ordem \n");
    printf("5 Impressao da arvore em Labelled Bracketing \n");
}

int main(){
  int opcao, chave, dado, tamanho, i;
  
  menu(); // Cria o menu para o usuario escolher a opcao
  scanf("%d", &opcao);
  
  struct arvore *raiz = criaArvore(); // cria uma arvore com nenhum dado
  
  while (opcao >= 1 && opcao <= 5){
      switch(opcao){
          case 1: 
               printf("\nForneca o numero de chaves que deseja adicionar\n");
               scanf("%d", &tamanho);
               for(i = 0 ; i<tamanho ; i++){
                   printf("\nForneca a chave do %do elemento\n", i+1);
                   scanf("%d", &chave);
                   insercao(&raiz, chave);
               }  
               printf("\n\n");
               break;
          case 2: 
               printf("\nForneca a chave a ser removido\n");
               scanf("%d", &chave);
               remocao(raiz, chave);  
               printf("\n\n");
               break;
          case 3: 
               printf("\nForneca a chave que deseja buscar\n");
               scanf("%d", &chave);
               busca(raiz, chave);
               printf("\n\n");
               break;
          case 4: 
               printf("\nImpressao\n");
               impressao(raiz);
               printf("\n\n");
               break;
          case 5: 
               printf("\nImpressao em Labelled Bracketing \n");
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
