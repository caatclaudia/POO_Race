#include "PilotoSurpresa.h"
#include "Carro.h"

PilotoSurpresa::PilotoSurpresa(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
	comeca = 1;
}

/*
	A CADA SEGUNDO ACELERA/DESACELERA (numero aleatorio)

	A PROBABILIDADE DE DANIFICAR CARRO É DE 5%
*/

int PilotoSurpresa::passouTempo(int s)
{
	if (comeca > 0) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
		comeca--;
	}
	//ACELARAR/DESACELARAR A CADA SEGUNDO ALEATORIAMENTE
	return getCarro()->getVelocidade() * s;
}

PilotoSurpresa::~PilotoSurpresa()
{
}
