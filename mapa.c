#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include <string.h>

// Todas as funcoes declaradas no mapa. c recebera ponteiros MAPA* M, POSICAO* p../

//Essa função receberá então dois mapas: o destino e a origem. Precisamos copiar os dois inteiros, linhas e colunas, alocar a matriz, 
//e copiar linha a linha da matriz origem. 


void lemapa(MAPA* m) {
	FILE* f;
	f = fopen("mapa.txt", "r");// nome do arquivo mapa.txt//
	if(f == 0) {// se for igual zero imprima prinff
		printf("Erro na leitura do mapa");
		exit(1);// exit abri o arquivo../
	}

	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));//fscanf lê linhas e colunas...
	alocamapa(m);// Funcao
	
	for(int i = 0; i < m->linhas; i++) { //podemos agora fazer o loop para capturar as linhas do arquivo. Apontamos mapa[i] como o lugar onde os caracteres devem ser colocados:
		fscanf(f, "%s", m->matriz[i]);// %s lê s string inteira, matriz[i] devolver um array de char...
	}

	fclose(f);//precisamos fechar o arquivo:
}
//A função alocamapa() deve receber um ponteiro de mapa, para que suas alterações sejam feitas sempre na posição de memória da variável original. Ou seja, passagem por referência:
void alocamapa(MAPA* m) {//Usaremos esses números para então alocar o tamanho do mapa de maneira dinâmica, que será feito na função alocamapa():
	
	// alocando espaço para as linhas,//
	// que guardam ponteiro de char...
	m->matriz = malloc(sizeof(char*) * m->linhas);

	// agora, para cada linha, alocamos
	// espaço para um array com ("colunas") posições.
	for(int i = 0; i < m->linhas; i++) {
		m->matriz[i] = malloc(sizeof(char) * m->colunas + 1);
	}
}
//Essa função receberá então dois mapas: o destino e a origem. Precisamos copiar os dois inteiros, linhas e colunas, alocar a matriz, 
//e copiar linha a linha da matriz origem. 

void copiamapa(MAPA* destino, MAPA* origem) {
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;
	alocamapa(destino);
	for(int i = 0; i < origem->linhas; i++) {
		strcpy(destino->matriz[i], origem->matriz[i]);//Para copiar uma linha, usaremos a função strcpy(). O nome já diz o que ela 
		//faz: copia uma string em outra. A função recebe dois parâmetros, "destino" e "origem". Essa função nada mais faz do que 
		//varrer o array e copiar o conteúdo na posição original na destino, e parar quando encontrar um NULL (\0).
	}
}


void liberamapa(MAPA* m) {// a função liberamapa(), que navega pela matriz, liberando cada um dos arrays alocados dinamicamente. Ao final, libera também a matriz como um todo:
	for(int i = 0; i < m->linhas; i++) {
		free(m->matriz[i]);
	}

	free(m->matriz);//a função free libera a matriz de cada linhas ....
}

//e algum fantasma passar por cima do herói, então ao final do turno, não haverá herói no mapa. Já temos uma função que nos ajuda a 
//encontrar algum personagem no mapa: a função encontramapa()
int encontramapa(MAPA* m, POSICAO* p, char c) {

	for(int i = 0; i < m->linhas; i++) {
		for(int j = 0; j < m->colunas; j++) {
			if(m->matriz[i][j] == c) {// se matriz[i] == [j] encontramos o fogefoge../
				p->x = i;// O ponterio POSICAO* p->X guardara a posicao das linhas[i].../
				p->y = j;// O PONTEIRO POSICAO* p->Y guardara a posicao das colunas[j]../
				return 1;
			}
		}
	}

	return 0;
}

int podeandar(MAPA* m, char personagem, int x, int y) {
	return 
		ehvalida(m, x, y) && 
		!ehparede(m, x, y) &&
		!ehpersonagem(m, personagem, x, y);
}

//Mas os dois próximos ifs podem ir para dentro das funções de mapa; eles nos dizem se uma determinada posição do mapa é válida ou
// não. Aqui, nossa estratégia será retornar 0, caso alguma das posições seja inválida ou, no fim, retornar 1, dizendo que x e y
// estão dentro dos limites do mapa.../
int ehvalida(MAPA* m, int x, int y) {
	if(x >= m->linhas) 
		return 0;
	if(y >= m->colunas) 
		return 0;

	return 1;// Se os dois IF for falsos, return 1...	
}

int ehpersonagem(MAPA* m, char personagem, int x, int y) {
	return
		m->matriz[x][y] == personagem;
}

int ehparede(MAPA* m, int x, int y) {
	return 
		m->matriz[x][y] == PAREDE_VERTICAL ||
		m->matriz[x][y] == PAREDE_HORIZONTAL;
}

//A função andanomapa() receberá 5 argumentos: um ponteiro de mapa, X e Y de origem, e X e Y de destino. Ela é bem simples: 
//primeiro, ela armazena o personagem (ou qualquer coisa) que estava na posição antiga. Em seguida, ela faz a troca: coloca o
// personagem na posição de destino, e troca por vazio a posição antiga.../
void andanomapa(MAPA* m, int xorigem, int yorigem, 
	int xdestino, int ydestino) {

	char personagem = m->matriz[xorigem][yorigem];
	m->matriz[xdestino][ydestino] = personagem;
	m->matriz[xorigem][yorigem] = VAZIO;

}
