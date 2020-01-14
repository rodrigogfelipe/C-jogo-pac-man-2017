///o ifdef e o ifndef. Como o próprio nome diz, o que eles fazem são ifs. Mas são ifs diferentes: eles acontecem em tempo de 
//compilação. O restante do nome, o "def", é porque o condicional é feito em cima de um "define". 
#ifndef _UI_H_
#define _UI_H_

#include "mapa.h"

void imprimeparte(char desenho[4][7], int parte);
void imprimemapa(MAPA* m);

#endif