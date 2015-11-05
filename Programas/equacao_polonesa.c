#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct equacao{
	char* dado;
	struct equacao* dir;
	struct equacao* esq;
};

char* substring(char* str, int posicao, int tamanho){ // Retorna uma parte da string original
	char* resultado = (char*)calloc(tamanho, sizeof(char));
	int i = 0;
	for(;i < tamanho-1 && str[i+posicao] != '\0'; ++i){
		resultado[i] = str[i+posicao];
	}
	resultado[tamanho-1] = '\0';
	return resultado;
}	

struct equacao* geraArvore(char* string, int tamanho){ // gera a arvore de operadores com o numeros
	struct equacao* no = (struct equacao*)calloc(1, sizeof(struct equacao));
	if(string[0] >= '0' && string[0] <= '9'){
		no->dado = string;
		return no;
	}
	no->dado = (char*) malloc (2*sizeof(char));
	no->dado[0] = string[0];
	no->dado[1] = '\0';
	
	int posicao = tamanho-1; // a posicao se inicia no ultimo caracter
	int espaco = 0;
	while(espaco != 2){
		if(espaco == 0){
			if((string[posicao] >= '0' && string[posicao] <= '9') || string[posicao] == ' '){
				posicao --;
			} else {
				espaco ++ ;
			}
		} else if(espaco == 1){
			if((!(string[posicao] >= '0' && string[posicao] <= '9') || string[posicao] == ' ') && posicao > 0){
				posicao--;
			} else {
				espaco++; 
			}
		}
	}
	if(posicao == 0){
		int diferenca = 0;
		while(string[tamanho - diferenca] != ' '){ // pega a diferenca entre os caracteres e os espacos
			diferenca++;
		}
		no->dir = geraArvore(substring(string, tamanho - diferenca + 1, diferenca), diferenca - 1);
		no->esq = geraArvore(substring(string, 2, tamanho - diferenca - 1), tamanho - diferenca - 2);
	} else {
		no->dir = geraArvore(substring(string, tamanho - posicao + 1, posicao), posicao - 1);
		no->esq = geraArvore(substring(string, 2, tamanho - posicao - 1), tamanho - posicao - 2);
	}
	return no;
}

void rpn(struct equacao * no){  // Notacao Polonesa Reversa
	if(no != NULL){
		rpn(no->esq);
		rpn(no->dir);
		printf("%s ", no->dado);
	}
}

void infixa(struct equacao* no){ // Notacao Infixa
	if(no != NULL){
		if(no->esq != NULL){
			printf("(");
        }
		infixa(no->esq);
		printf(" %s ", no->dado);
		infixa(no->dir);
		
		if(no->esq != NULL)
			printf(")");
	}
}

int strlen(char* str){
	int i;
	for(i=0; str[i]!= '\0' ; ++i){}
	return i;
}
 
char* getExpressao(){
	int tam = 0, i;
	char str[128], c;
	
	while(tam == 0){
		while((c = getchar()) != '\n' && c != EOF){
			str[tam] = c;
			tam++;
		}
	}
	str[tam] = '\0';
	char* result = (char*)malloc((tam+1)*sizeof(char));
	
	for(i = 0; i < tam+1; i++){
		result[i] = str[i];
	}
	return result;
}

struct equacao* criaEquacao(){
       return NULL; // cria uma arvore com nenhum elemento        
}

void menu(){
    // Montagem do menu
    printf("\nMENU \n");
    printf("1 RPN \n");
    printf("2 Notacao INFIXA \n");
}

int main(){
    int opcao;
    
    struct equacao* raiz = criaEquacao();
    char* expressao = (char*)calloc(100, sizeof(char));
	printf("Insira a expressao matematica em equacao polonesa\n");
    printf("Separe os numeros e operadores com 1 espaco apenas\n");
	expressao = getExpressao(); // pega a expressao que o usuario escrever
	raiz = geraArvore(expressao, strlen(expressao));
    
    menu(); // Cria o menu para o usuario escolher a opcao
    scanf("%d", &opcao);
    while (opcao >= 1 && opcao <= 2){
      switch(opcao){
          case 1: 
               printf("RPN\n");
	           rpn(raiz);
	           printf("\n\n");
               break;
          case 2: 
               printf("Notacao INFIXA\n");
         	   infixa(raiz);
	           printf("\n\n");
               break;
      }
      
      menu();
      scanf("%d", &opcao);
    }
    system("PAUSE");
    return 0;
}
