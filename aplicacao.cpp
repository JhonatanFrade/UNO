/*
	PROGRAMADORES: JHONATAN FRADE e MARLON DIETRICH
	DATA: 23/06/2018
	VERSION: 2.0.0
	BUILD: 0.0.1
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM 100 //QUANTIDADE DE CARTAS
#define QTDE 11 //Quantidade maxima de caracter por cada vetor de string

struct BARALHO{
	char carta[TAM][QTDE];
};

typedef struct
{
    char nome[30];
    float potenciaMotor;
    int pontos;
}USUARIO;

FILE* abreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g':
            arquivo = fopen(caminho,"wt"); //Escrever no arquivo, apaga conteudo anterior.
            break;
        case 'l':
            arquivo = fopen(caminho,"rt"); //modo leitura.
            break;
        case 'a':
            arquivo = fopen(caminho,"a"); //Modo Anexar vai anexar ao fim evitando apagar conteudo.
            break;
        case 'w':
        	arquivo = fopen(caminho, "wb"); //Escrever modo binario. Para o struct.
        	break;
        case 'r':
        	arquivo = fopen(caminho, "rb"); //Ler modo binario. Para o struct.
        	break;
    }
    if(arquivo==NULL){      //Se houver algum erro, o ponteiro apontará para NULL
        printf("\n\n\tNao foi possivel abrir o arquivo!");
        exit(0);
    }
    return arquivo;
}

void fecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void criarCartasNormais(char corDaCarta[10], int *indice, BARALHO *cartas){
	int key = *indice;
	char number[5];
	char aux[10];
	strcpy(aux, corDaCarta);
	int valor = 0;
	for(int num = 1; num<20; num++){
		itoa(valor,number,10);
		strcat(corDaCarta, number);
		strcpy(cartas->carta[key], corDaCarta);
		key++;
		valor++;
		if(valor==10){
			valor=1;
		}
		strcpy(corDaCarta, aux);
	}
	*indice = key;
}

void criarCartasEspeciais(char acaoDaCarta[10], int *indice, BARALHO *cartas){
	int key = *indice;
	char number[5];
	char aux[10];
	strcpy(aux, acaoDaCarta);
	char corDaCarta[10];
	for(int cor = 0; cor<4; cor++){
		for(int num = 1; num<3; num++){
			if(cor==0){
				strcpy(corDaCarta, "az-");
			}else if(cor==1){
				strcpy(corDaCarta, "vr-");
			}else if(cor==2){
				strcpy(corDaCarta, "vm-");
			}else if(cor==3){
				strcpy(corDaCarta, "am-");
			}
			itoa(num,number,10);
			strcat(corDaCarta, number);
			strcat(acaoDaCarta, corDaCarta);
			strcpy(cartas->carta[key], acaoDaCarta);
			key++;
			strcpy(acaoDaCarta, aux);	
		}
	}
	*indice = key;
}

void criarCartasCoringa(char acaoDaCarta[10], int *indice, BARALHO *cartas){
	int key = *indice;
	char corDaCarta[10];
	char aux[10];
	strcpy(aux, acaoDaCarta);
	char number[5];
	for(int tipo = 0; tipo<2; tipo++){
		for(int num = 1; num<5; num++){
			if(tipo==0){
				strcpy(corDaCarta, "n");
			}else if(tipo==1){
				strcpy(corDaCarta, "+");
			}
			itoa(num,number,10);
			strcat(corDaCarta, number);
			strcat(acaoDaCarta, corDaCarta);
			strcpy(cartas->carta[key], acaoDaCarta);
			key++;
			strcpy(acaoDaCarta, aux);	
		}
	}
	*indice = key;
}

void criarCartas(){
	FILE *arq;
	arq = abreArquivo('w', "cartas.txt");
	
	struct BARALHO cartas;
	
	char corDaCarta[10];
	char acaoDaCarta[10];
	
	int indice = 0;
	
	//****** CARTAS NORMAIS ******	
	//CARTAS AZUL
	strcpy(corDaCarta, "az-");
	criarCartasNormais(corDaCarta, &indice, &cartas);
	//CARTAS VERDE
	strcpy(corDaCarta, "vr-");
	criarCartasNormais(corDaCarta, &indice, &cartas);
	//CARTAS VERMELHO
	strcpy(corDaCarta, "vm-");
	criarCartasNormais(corDaCarta, &indice, &cartas);
	//CARTAS AMARELO
	strcpy(corDaCarta, "am-");
	criarCartasNormais(corDaCarta, &indice, &cartas);

	//****** CARTAS ESPECIAIS ******	
	//CARTAS "pular"
	strcpy(acaoDaCarta, "bloc-");
	criarCartasEspeciais(acaoDaCarta, &indice, &cartas);
	
	//CARTAS "pescar 2"
	strcpy(acaoDaCarta, "pesc-"); 
	criarCartasEspeciais(acaoDaCarta, &indice, &cartas);
	//CARTAS "coringas que mudar de cor" e "coringas pescar quatro"
	strcpy(acaoDaCarta, "joker-"); 
	criarCartasCoringa(acaoDaCarta, &indice, &cartas);
	
	fwrite(&cartas, sizeof(struct BARALHO), 1, arq);
	fecharArquivo(arq);
	printf("\n Criou com sucesso!\n");
	getch();
}
	
void mostrarCartas(){
	FILE *arq;
	arq = abreArquivo('r', "cartas.txt");
	
	struct BARALHO mesa;
	
	fread(&mesa, sizeof(struct BARALHO), 1, arq);
	
	for(int i=0; i<TAM; i++){
		printf(" Carta = %s \tPosicao [%i] \n\n",mesa.carta[i],i);
		getch();
	}
	
	fecharArquivo(arq);
}	

void criarUsuario(){
	
}

void executa(int opcao){
	switch(opcao){
		case 2:{
//			criarUsuario();
			break;
		}
		case 3:{
//			apresentarUsuarios();
			break;
		}
		case 4:{
//			deletarUsuario();
			break;
		}
	}
}

void menu(){
	int opcao;
	do{
		system("cls");
		fflush(stdin);
		printf("\n\n\t\tBem Vindo ao programa UNO\n");
		printf("\nMENU");
		printf("\n 1 - JOGAR.");
		printf("\n 2 - CRIAR UMA CONTA.");
		printf("\n 4 - DELETAR UM USUARIO.");
		printf("\n 5 - CLASSIFICACAO DOS USUARIOS.");
		printf("\n 0 - SAIR.\n");
		
		printf("\nDigite uma opcao: ");
		scanf("%d",&opcao);
		system("cls");
		
		executa(opcao);
		getch();
	}while(opcao!=0);
}



int main(){
	printf("\n *--- criando baralho ---*\n");
	criarCartas();
	printf("\n *--- fim da criacao do baralho ---*\n");
	mostrarCartas();
	getch();
	menu();
	getch();
}
