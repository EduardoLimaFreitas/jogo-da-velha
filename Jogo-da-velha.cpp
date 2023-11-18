#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

//variáveis globais
char jogo[3][3];
int l, c, first = 0, escolhaMenu;

//Menu do jogo
void menu(){
	setlocale(0, "portuguese");
	if(first == 0){
		escolhaMenu = 0;
		printf("\nBoas vindas ao jogo da velha feito em linguagem C\nIndique o que deseja realizar com os respectivos numeros abaixo\n");
		printf("\n\n1. Jogar\n2. Créditos\n3. Sair do jogo\n\nDigite: ");
		scanf("%d", &escolhaMenu);
		first++;
	}
	else{
		printf("\nIndique o que deseja realizar com os respectivos numeros abaixo\n");
		printf("\n\n1. Jogar\n2. Créditos\n3. Sair do jogo\n\nDigite: ");
		scanf("%d", &escolhaMenu);
	}
}
// créditos
void creditos(){
	setlocale(0, "portuguese");
	printf("\nEsses são os creditos para os desenvolvedores do jogo:\n\nLider de equipe:\nEduardo Lima Freitas\n\nDesenvolvimento do jogo:\nEduardo Lima Freitas\nVinicius Vieira deLima\nJosé Roberto de Souza Filho\nMarcos Pereira Matias Neto\nMaria Eduarda de Melo Gomes\n");
}

// Função para a jogada do computador
void movimentoComputador(char tabuleiro[3][3]) {
    int linha, coluna;
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] != ' ');

    tabuleiro[linha][coluna] = 'O';
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
// função para verificar vitória por linha
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

// função para verificar vitória por coluna
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
//função para verificar vitória por diagonal principal
int verificarDiagPrin(char c){
	if(jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c){
		return 1;
	}
	else{
		return 0;
	}
}
//função para verificar vitória por diagonal secundária
int verificarDiagSec(char c){
	if(jogo[2][0] == c && jogo[1][1] == c && jogo[0][2] == c){
		return 1;
	}
	else{
		return 0;
	}
}
//função de validação de coordenada
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
	
	printf("digite linha e coluna: ");
	scanf("%d%d", &linha, &coluna);
	
	while(ehValida(linha, coluna) == 0){
		printf("Coordenada inválida! digite outra linha e coluna: ");
		scanf("%d%d", &linha, &coluna);
	}
	jogo[linha][coluna] = j;
}
// retorna posições vazias
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
// loop principal do jogo
void jogar(){
	int jogador = 1, vitoriaX = 0, vitoriaO = 0;
	char jogador1 = 'X', jogador2 = 'O';
	do{
		imprimir();
		if(jogador == 1){
			printf("jogador1 (X): ");
			lerCoordenadas('X');
			jogador++;
			vitoriaX += verificarLinhas(jogador1);
			vitoriaX += verificarColunas(jogador1);
			vitoriaX += verificarDiagPrin(jogador1);
			vitoriaX += verificarDiagSec(jogador1);
		}
		else{
			printf("jogador2 (O): ");
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
		printf("\nParabens jogador2 ('O') voce ganhou!!\n");
	}
	else if(vitoriaX == 1){
		imprimir();
		printf("\nParabens jogador1 ('X') voce ganhou!!\n");
	}
	else{
		imprimir();
		printf("\nO jogo deu velha\n");
	}
}

// função contra robo
void jogar(){
	int jogador = 1, vitoriaX = 0, vitoriaO = 0;
	char jogador1 = 'X', jogador2 = 'O';
	do{
		imprimir();
		if(jogador == 1){
			printf("jogador1 (X): ");
			lerCoordenadas('X');
			jogador++;
			vitoriaX += verificarLinhas(jogador1);
			vitoriaX += verificarColunas(jogador1);
			vitoriaX += verificarDiagPrin(jogador1);
			vitoriaX += verificarDiagSec(jogador1);
		}
		else{
			printf("jogador2 (O): ");
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
		printf("\nParabens jogador2 ('O') voce ganhou!!\n");
	}
	else if(vitoriaX == 1){
		imprimir();
		printf("\nParabens jogador1 ('X') voce ganhou!!\n");
	}
	else{
		imprimir();
		printf("\nO jogo deu velha\n");
	}
}

int main(){
	while(escolhaMenu != 3){
		menu();
		switch(escolhaMenu){
			case 1:
				inicializarMatriz();
				jogar();
				
				break;
			case 2:
				creditos();
				menu();
				break;
			case 3:
				printf("\nObrigado por visitar o jogo, volte sempre :)");
				break;
			default:
				printf("valor invalido, tente novamente.");
				while(escolhaMenu > 3 || escolhaMenu < 1){
					menu();
					switch(escolhaMenu){
						case 1:
							inicializarMatriz();
							jogar();
							break;
						case 2:
							creditos();
							break;
						case 3:
							printf(\n"Obrigado por visitar o jogo, volte sempre :)");
							break;
						default:
							printf("\nvalor invalido, tente novamente.");
							break;
								
					}
				}
		}
	}
	printf("\nObrigado por visitar o jogo, volte sempre :)");
	return 0;
}
