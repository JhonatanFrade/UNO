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

typedef struct{
	char carta[TAM][QTDE];
	int quant = 0;
}BARALHO;

typedef struct{
    char nome[30];
    BARALHO mao;
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
	char aux[10];
	strcpy(aux, acaoDaCarta);
	char number[5];
	for(int num = 1; num<5; num++){
		itoa(num,number,10);
		strcat(acaoDaCarta, number);
		strcpy(cartas->carta[key], acaoDaCarta);
		key++;
		strcpy(acaoDaCarta, aux);	
	}
	*indice = key;
}

void criarCartas(){
	FILE *arq;
	arq = abreArquivo('w', "cartas.txt");
	
	BARALHO cartas;
	
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
	//CARTAS "coringas que mudar de cor"
	strcpy(acaoDaCarta, "joker-"); 
	criarCartasCoringa(acaoDaCarta, &indice, &cartas);
	//CARTAS "coringas pescar quatro"
	strcpy(acaoDaCarta, "joker+-"); 
	criarCartasCoringa(acaoDaCarta, &indice, &cartas);
	
	cartas.quant = 100;
	
	fwrite(&cartas, sizeof(BARALHO), 1, arq);
	fecharArquivo(arq);
	printf("\n Criou com sucesso!\n");
	getch();
}
	
void mostrarCartas(){
	FILE *arq;
	arq = abreArquivo('r', "cartas.txt");
	
	BARALHO mesa;
	
	fread(&mesa, sizeof(BARALHO), 1, arq);
	
	for(int i=0; i<TAM; i++){
		printf(" Carta = %s \tPosicao [%i] \n\n",mesa.carta[i],i);
		getch();
	}
	
	printf(" A quantidade = %i\n",mesa.quant);
	
	fecharArquivo(arq);
}

BARALHO getBaralho(){
	FILE *arq;
	arq = abreArquivo('r', "cartas.txt");
	
	BARALHO cartas;
	
	fread(&cartas, sizeof(BARALHO), 1, arq);	
	
	fecharArquivo(arq);
	
	return cartas;
}	

void criarUsuario(){
	
}

void qualEhACarta(char str[10]){
	char * pch;
	pch = strtok (str, "-" );
    while ( pch != NULL ) {
    	if( strcmp( pch, "joker") == 0 ){
    		printf("\n Eh um coringa que muda de cor.");
		}
		
		if( strcmp( pch, "joker+") == 0 ){
    		printf("\n Eh um coringa pescar quatro.");
		}
		
		if ( strcmp( pch, "az" ) == 0 ){
            printf("\n Eh azul\n");
        }else if( strcmp( pch, "vr" ) == 0 ){
        	printf("\n Eh verde\n");
		}else if( strcmp( pch, "vm" ) == 0 ){
			printf("\n Eh vermelho\n");
		}else if( strcmp( pch, "am" ) == 0 ){
			printf("\n Eh amarelo\n");
		}
		
		if( strcmp( pch, "bloc") == 0 ){
    		printf("\n Eh um block");
    		pch = strtok ( NULL, "-" );
    		if ( strcmp( pch, "az" ) == 0 ){
	            printf(" azul\n");
	        }else if( strcmp( pch, "vr" ) == 0 ){
	        	printf(" verde\n");
			}else if( strcmp( pch, "vm" ) == 0 ){
				printf(" vermelho\n");
			}else if( strcmp( pch, "am" ) == 0 ){
				printf(" amarelo\n");
			}else{
				printf("\n Erro na cor!");
			}
		}
		
		if( strcmp( pch, "pesc") == 0 ){
    		printf("\n Eh um pecar 2");
    		pch = strtok ( NULL, "-" );
    		if ( strcmp( pch, "az" ) == 0 ){
	            printf(" da cor azul\n");
	        }else if( strcmp( pch, "vr" ) == 0 ){
	        	printf(" da cor verde\n");
			}else if( strcmp( pch, "vm" ) == 0 ){
				printf(" da cor vermelho\n");
			}else if( strcmp( pch, "am" ) == 0 ){
				printf(" da cor amarelo\n");
			}else{
				printf("\n Erro na cor!");
			}
		}
        pch = strtok ( NULL, "-" );
    }
}

void jogar(){
	USUARIO jogador[2];
	BARALHO monte = getBaralho();
	strcpy(jogador[0].nome, "jhonatan");
	printf("\n Nome do jogador 1 = %s",jogador[0].nome);
	strcpy(jogador[1].nome, "fulano");
	printf("\n Nome do jogador 2 = %s",jogador[1].nome);
	int ind = 0;
	for(int i=0; i<7; i++){
		ind = rand()%100;
		strcpy(jogador[0].mao.carta[i], monte.carta[ind]);
		jogador[0].mao.quant++;
	}
	for(int i=0; i<7; i++){
		printf("\n Carta do jogador 1 [%i] = %s",i,jogador[0].mao.carta[i]);
	}
	printf("\n Quantidade = %i",jogador[0].mao.quant);
	
	ind = 0;
	for(int i=0; i<7; i++){
		ind = rand()%100;
		strcpy(jogador[1].mao.carta[i], monte.carta[ind]);
		jogador[1].mao.quant++;
	}
	for(int i=0; i<7; i++){
		printf("\n Carta do jogador 2 [%i] = %s",i,jogador[1].mao.carta[i]);
	}
	printf("\n Quantidade = %i",jogador[1].mao.quant);
	
	ind = rand()%100;
	printf("\n Carta aleatoria do monte = %s \n\n",monte.carta[ind]);
	qualEhACarta(monte.carta[ind]);
}

void executa(int opcao){
	switch(opcao){
		case 1:{
			jogar();
			break;
		}
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
	return 0;
}
