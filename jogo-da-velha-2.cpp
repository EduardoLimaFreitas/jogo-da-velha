#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

//vari�veis globais
char jogo[3][3];
int l, c, first = 0, escolhaMenu;

//Menu do jogo
void menu(){
	setlocale(0, "portuguese");
	if(first == 0){
		escolhaMenu = 0;
		printf("===================JOGO DA VELHA===================\nBoas vindas ao jogo da velha feito em linguagem C.\nIndique o que deseja realizar com os respectivos n�meros abaixo.\n");
		printf("\n\n1. Jogar PvP\n2. Jogar contra o computador\n3. Cr�ditos\n4. Ranking de vit�rias\n5. Sair do jogo\n\nDigite: ");
		scanf("%d", &escolhaMenu);
		getchar();
		first++;
	}
	else{
		printf("\nIndique o que deseja realizar com os respectivos n�meros abaixo\n");
		printf("\n\n1. Jogar PvP\n2. Jogar contra o computador\n3. Cr�ditos\n4. Ranking de vit�rias\n5. Sair\n\nDigite: ");
		scanf("%d", &escolhaMenu);
		getchar();
	}
}
// cr�ditos
void creditos(){
	setlocale(0, "portuguese");
	printf("\nEsses s�o os cr�ditos para os desenvolvedores do jogo:\n\nL�der de equipe:\nEduardo Lima Freitas\n\nDesenvolvimento do jogo:\nEduardo Lima Freitas\nVin�cius Vieira de Lima\nJos� Roberto de Souza Filho\nMarcos Pereira Matias Neto\nMaria Eduarda de Melo Gomes\n");
}

// Fun��o para a jogada do computador
void movimentoComputador() {
    int l, c;
    do {
        l = rand() % 3;
        c = rand() % 3;
    } while (jogo[l][c] != ' ');

    jogo[l][c] = 'O';
}

//inicializar A matriz
void inicializarMatriz(){
	for(l = 0; l < 3; l++){
		for(c = 0; c < 3; c++){
			jogo[l][c] = ' ';
		}
	}
}

//imprimir o jogo
void imprimir(){
	printf("\n\n\t 0   1   2\n\n");
	for(l = 0; l < 3; l++){
		for(c = 0; c < 3; c++){
			if(c == 0){
			printf("\t");
			}
			printf(" %c ", jogo[l][c]);
			if (c < 2){
				printf("|");
			}
			if(c == 2){
				printf("  %d", l);
			}
		}
		if(l < 2){
			printf("\n\t-----------");
		}
		printf("\n");
	}
}
// fun��o para verificar vit�ria por linha
int verificarLinha(int l, char c){
	if(jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c){
		return 1;
	}
	else{
		return 0;
	}
}

int verificarLinhas(char c){
	int ganhou = 0;
	for(l = 0; l < 3; l++){
		ganhou += verificarLinha(l, c);
	}
	return ganhou;
}

// fun��o para verificar vit�ria por coluna
int verificarColuna(int c, char j){
	if(jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j){
		return 1;
	}
	else{
		return 0;
	}
}
int verificarColunas(char j){
	int ganhou = 0;
	for(c = 0; c < 3; c++){
		ganhou += verificarColuna(c, j);
	}
	return ganhou;
}
//fun��o para verificar vit�ria por diagonal principal
int verificarDiagPrin(char c){
	if(jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c){
		return 1;
	}
	else{
		return 0;
	}
}
//fun��o para verificar vit�ria por diagonal secund�ria
int verificarDiagSec(char c){
	if(jogo[2][0] == c && jogo[1][1] == c && jogo[0][2] == c){
		return 1;
	}
	else{
		return 0;
	}
}
//fun��o de valida��o de coordenada
int ehValida(int l, int c){
	if(l >= 0 && l < 3 &&  c >= 0 && c < 3 && jogo[l][c] == ' '){
		return 1;
	}
	else{
		return 0;
	}
}
//ler coordenadas
void lerCoordenadas(char j){
	int linha, coluna;
	
	printf("digite a linha e a coluna: ");
	scanf("%d%d", &linha, &coluna);
	
	while(ehValida(linha, coluna) == 0){
		printf("Coordenada inv�lida! digite outra linha e coluna: ");
		scanf("%d%d", &linha, &coluna);
	}
	jogo[linha][coluna] = j;
}
// retorna posi��es vazias
int quantVazias(){
	int quantidade = 0;
	for(l = 0; l < 3; l++){
		for(c = 0; c < 3; c++){
			if(jogo[l][c] == ' '){
				quantidade++;
			}	
		}
	}
	return quantidade;
}

// estrutura de ranking
struct{
	int vitoriasO = 0;
	int vitoriasX = 0;
}ranking;

// loop principal do jogo
void jogar(){
	int jogador = 1, vitoriaX = 0, vitoriaO = 0;
	char jogador1 = 'X', jogador2 = 'O';
	do{
		imprimir();
		if(jogador == 1){
			printf("jogador 1 (X): ");
			lerCoordenadas('X');
			jogador++;
			vitoriaX += verificarLinhas(jogador1);
			vitoriaX += verificarColunas(jogador1);
			vitoriaX += verificarDiagPrin(jogador1);
			vitoriaX += verificarDiagSec(jogador1);
		}
		else{
			printf("jogador 2 (O): ");
			lerCoordenadas('O');
			jogador = 1;
			vitoriaO += verificarLinhas(jogador2);
			vitoriaO += verificarColunas(jogador2);
			vitoriaO += verificarDiagPrin(jogador2);
			vitoriaO += verificarDiagSec(jogador2);
		}
	}while(vitoriaX == 0 && vitoriaO == 0 && quantVazias() > 0);
	
	if(vitoriaO == 1){
		imprimir();
		ranking.vitoriasO += 1;
		printf("\nParab�ns jogador 2 ('O') voc� ganhou!!\n");
	}
	else if(vitoriaX == 1){
		imprimir();
		ranking.vitoriasX += 1;
		printf("\nParab�ns jogador 1 ('X') voc� ganhou!!\n");
	}
	else{
		imprimir();
		printf("\nO jogo deu velha\n");
	}
}

// fun��o contra robo
void jogarContraMaquina(){
	int jogador = 1, vitoriaX = 0, vitoriaO = 0;
	char jogador1 = 'X', jogador2 = 'O';
	do{
		imprimir();
		if(jogador == 1){
			printf("jogador 1 (X): ");
			lerCoordenadas('X');
			jogador++;
			vitoriaX += verificarLinhas(jogador1);
			vitoriaX += verificarColunas(jogador1);
			vitoriaX += verificarDiagPrin(jogador1);
			vitoriaX += verificarDiagSec(jogador1);
		}
		else{
			movimentoComputador();
			jogador = 1;
			vitoriaO += verificarLinhas(jogador2);
			vitoriaO += verificarColunas(jogador2);
			vitoriaO += verificarDiagPrin(jogador2);
			vitoriaO += verificarDiagSec(jogador2);
		}
	}while(vitoriaX == 0 && vitoriaO == 0 && quantVazias() > 0);
	
	if(vitoriaO == 1){	
		imprimir();
		ranking.vitoriasO += 1;
		printf("\nQue pena, voc� perdeu. Boa sorte na pr�xima!!\n");
	}
	else if(vitoriaX == 1){
		imprimir();
		ranking.vitoriasX += 1;
		printf("\nParab�ns jogador 1 ('X') voc� ganhou!!\n");
	}
	else{
		imprimir();
		printf("\nO jogo deu velha!\n");
	}
}


//fun��o para rodar o jogo
int main(){
	setlocale(0, "portuguese");
	while(escolhaMenu != 5){
		menu();
		switch(escolhaMenu){
			case 1:
				inicializarMatriz();
				jogar();
				break;
			case 2:
				inicializarMatriz();
				jogarContraMaquina();
				break;
			case 3:
				creditos();
				break;
			case 4:
				printf("\nRanking de vit�rias: \n\nJogador 'X': %d\nJogador 'O': %d\n\n", ranking.vitoriasX, ranking.vitoriasO);
				system("pause");
				break;
			case 5:
				printf("\nObrigado por jogar, volte sempre :)");
				break;
			default:
				printf("\nvalor inv�lido, tente novamente.\n\n");
				system("pause");
			}
		}
	return 0;
}
