#include <stdio.h>
#include "mapa.h"

char desenhoparede[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char desenhofantasma[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char desenhoheroi[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char desenhopilula[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char desenhovazio[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void imprimeparte(char desenho[4][7], int parte) {
	printf("%s", desenho[parte]);
}

void imprimemapa(MAPA* m) {
	for(int i = 0; i < m->linhas; i++) {//precisamos então de mais um loop contado, de 1 até 4 (ou 0 a 3), que imprimirá a linha 
		//certa de todos os desenhos. Veja o código abaixo. Temos a linha em i, a coluna em j e a parte do desenho a ser impressa em 
		//parte:

		for(int parte = 0; parte < 4; parte++) {
		
			for(int j = 0; j < m->colunas; j++) { //a função imprimemapa() invocar a função imprimeparte() de acordo com o caractere que estiver em m->matriz[i][j] e o número 
		//da parte a ser impressa.

				switch(m->matriz[i][j]) {
					case FANTASMA:
						imprimeparte(desenhofantasma, parte);
						break;
					case HEROI:
						imprimeparte(desenhoheroi, parte);
						break;
					case PILULA:
						imprimeparte(desenhopilula, parte);
						break;
					case PAREDE_VERTICAL://PAREDE_VERTICAL e PAREDE_HORIZONTAL. Como em ambos os casos queremos imprimir o desenho
					// desenhoparede, podemos colocar um case embaixo do outro, e dessa forma, ambos terão o mesmo comportamento:
					case PAREDE_HORIZONTAL:
						imprimeparte(desenhoparede, parte);
						break;
					case VAZIO:
						imprimeparte(desenhovazio, parte);
						break;
				}
				
			}
			printf("\n");
		}

	}
}
