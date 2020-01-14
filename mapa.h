//As constantes dizem respeito aos mapas, vão para o mapa.h:
#ifndef _MAPA_H_
#define _MAPA_H_


#define HEROI '@'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define FANTASMA 'F'
#define PILULA 'P'

//Para tal, usaremos uma struct. Estruturas (ou, em C, struct) são uma maneira que temos para agrupar variáveis. Ou seja, 
//definiremos que a estrutura "mapa" contém uma matriz (o ponteiro de ponteiro de char), uma variável para guardar a quantidade 
//de linhas (int) e outra para guardar a quantidade de coluncas (também int). Com essa estrutura definida, podemos declarar 
//variáveis que a seguem Dessa forma, garantiremos sempre que mapas tem uma matriz, e a quantidade de linhas e colunas......

struct mapa {
	char** matriz;// char** matriz é um ponteiro de ponteiro
	int linhas;// Quantidade de linhas no mapa.txt...
	int colunas;// Qunatidade de colunas no mapa.txt.. 
};

typedef struct mapa MAPA;//instrução typedef. Essa instrução nos possibilita dar um outro nome a algum tipo já existente.Por exemplo, 
//vamos apelidar struct mapa de MAPA..Graças ao typedef,agora podemos declarar variáveis do tipo MAPA sem a palavra struct.....


void alocamapa(MAPA* m);
void lemapa(MAPA* m);
void liberamapa(MAPA* m);

struct posicao {//Precisamos agora declarar uma POSICAO que guardará a posição do nosso herói, e invocar a função encontramapa()
	int x;
	int y;
};

typedef struct posicao POSICAO;

int encontramapa(MAPA* m, POSICAO* p, char c);

int ehvalida(MAPA* m, int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);

void andanomapa(MAPA* m, int xorigem, int yorigem, 
	int xdestino, int ydestino);

void copiamapa(MAPA* destino, MAPA* origem);

int podeandar(MAPA* m, char personagem, int x, int y);

#endif