#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;//Struct MAPA apelido m, o mesmo funciona para variaveis globais..//
POSICAO heroi;//Struct POSICAO apelido heroi../
int tempilula = 0;// tempilula variável global


int acabou() {
	POSICAO pos;

	int perdeu = !encontramapa(&m, &pos, HEROI);
	int ganhou = !encontramapa(&m, &pos, FANTASMA);

	return ganhou || perdeu;
		
}
//A primeira coisa que podemos fazer é levar esse if que verifica se a letra digitada é uma direção, que é grande, para uma função
// própria. A função se chamará ehdirecao(char) e nos retornará um inteiro 0 ou 1. Repare que precisamos inverter todo o if, pois 
//agora a função nos retornará verdadeiro se o caractere é uma direção:
int ehdirecao(char direcao) {
	return
		direcao == ESQUERDA || 
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == DIREITA;
}

void move(char direcao) { //precisamos fazer com que a função move() localize o mapa fogefoge, faça uso agora dos X e Y que estão dentro do heroi. Além disso, 
//precisamos também atualizar essa variável sempre que o herói andar..O faremos dentro de cada opção do switch.../


	int proximox = heroi.x;//proximox deve ser menor do que a quantidade de linhas da matriz, 
	int proximoy = heroi.y;//proximoy deve ser menor do que a quantidade de colunas


	switch(direcao) {
		case ESQUERDA:
			proximoy--;// proximoy aponta para casa bacman tem que andar.Se o jogador andou pra esquerda,
		break;
			break;
		case CIMA:
			proximox--;//proximox aponta para casa bacman tem que andar Se andou para cima, vai para linha-1
		break;
			break;
		case BAIXO:
			proximox++;//S coluna, e se andou para baixo, vai para linha+1, coluna
			break;
		case DIREITA:
			proximoy++;//Se ele andou para direita, o herói vai para linha, coluna+1
			break;
	}

	if(!podeandar(&m, HEROI, proximox, proximoy))
		return;

	if(ehpersonagem(&m, PILULA, proximox, proximoy)) {
		tempilula=1;
	}

	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;
}



int praondefantasmavai(int xatual, int yatual, 
	int* xdestino, int* ydestino) { // Essa funcao recebera dois ponteiros de inteiros para receber dois numeros../


	int opcoes[4][2] = {// Matriz 4 X 2, matriz 4 possibilidades com dois numeros dentro dela.../ 
		{ xatual   , yatual+1 },// indo para direita 
		{ xatual+1 , yatual   },// indo pra baixo  
		{ xatual   , yatual-1 },// indo para esquerda
		{ xatual-1 , yatual   },// indo pra cima
};

	srand(time(0));
	for(int i = 0; i < 10; i++) {
		int posicao = rand() % 4; //Em seguida, criamos nosso loop de no máximo 10 iterações onde, dentro dele, sorteamos um número 
		//de 0 a 3 (a quantidade de linhas da matriz), e testamos essa direção. Se ela for válida, devolvemos a direção (repare que 
		//aqui precisamos receber ponteiros, pois queremos que a função devolva dois números), e fazemos a função retornar verdadeiro. 
		//Caso contrário, se as 10 tentativas falharem, retornamos falso

		if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			return 1;
		}
	}

	return 0;
}


//Veja, por exemplo, o fantasma que está em (3,3) do mapa. Nosso algoritmo o encontrará quando i for igual a 3, e j for também igual 
//a 3. A próxima posição, (3,4) é vazia, e portanto movemos o fantasma. Até então, tudo funcionando de acordo. Entretanto, quando
// nosso loop iterar (ou seja, i é igual a 3, e j é igual a 4), encontraremos o mesmo fantasma novamente. A posição à direita estará
// vazia, e o fantasma será movido para lá. O loop iterará novamente, j será igual a 5, e o mesmo fantasma está lá novamente.Perceba 
//então que empurramos o mesmo fantasma várias vezes para a direita. Precisamos encontrar uma maneira de saber se já empurramos 
//aquele fantasma ou não. Podemos pensar em diversos algoritmos para isso, mas nossa solução será criar uma cópia do mapa. Com uma 
//cópia, poderemos iterar em uma, e mover na outra. Assim, não encontraremos o mesmo fantasma duas vezes

void fantasmas() {//A função fantasmas() agora, ao começar, fará uma cópia do mapa m. Em seguida, varrerá cada caractere do mapa 
	//copia. Sempre que achar um fantasma, sabemos que ele também existe em m. Se for possível movê-lo (ou seja, ehvalida() e 
	//ehvazia() retorna verdadeiro para (i, j+1) no mapa m), o fazemos somente no mapa m. 
	
	MAPA copia;//criamos uma cópia do mapa para conseguirmos ter os valores originais mesmo após modificá-los.

	copiamapa(&copia, &m);

	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {
			if(copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}

	liberamapa(&copia);
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {
	// se acabou o numero de vezes,
    // entao acaba a função
	if(qtd == 0) return; //Ou seja, uma variável qtd (de "quantidade"), que quando for 0, significa que a função deve parar de 
	//chamar a si própria. E como fazemos esse número ser zero? Na invocação recursiva, passamos qtd-1

	int novox = x+somax;
	int novoy = y+somay;

	if(!ehvalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	// dessa vez, passamos qtd-1, pois
    // já rodamos uma vez a função
	explodepilula2(novox, novoy, somax, somay, qtd-1);
}

void explodepilula() {
	if(!tempilula) return;
	
	explodepilula2(heroi.x, heroi.y, 0, 1, 3);//Para a direita, somamos 0,1
	explodepilula2(heroi.x, heroi.y, 0, -1, 3);//Para a esquerda, somaríamos 0,-1
	explodepilula2(heroi.x, heroi.y, 1, 0, 3);//Para cima, -1, 0
	explodepilula2(heroi.x, heroi.y, -1, 0, 3);//Para cima, -1, 0

	
	tempilula = 0;
}

int main() {
	
	lemapa(&m);// precisamos agora passar o endereço de memória da variável de PONTERIO M para as funções (usando &)
	encontramapa(&m, &heroi, HEROI);//Funcao encontra mapa busca a posicao aonde encontra o heroi representado pelo @../


	do {
		printf("Pílula: %s\n", (tempilula ? "SIM" : "NÃO"));
		imprimemapa(&m);//A funcao loop irá imprimir o mapa, espera o scanf lê do teclado e apos executara a função MOVE();.../

		char comando;
		scanf(" %c", &comando);

		if(ehdirecao(comando)) move(comando);
		if(comando == BOMBA) explodepilula();

		fantasmas();

	} while (!acabou());

	liberamapa(&m);
}
