#include "PilotoSurpresa.h"
#include "Carro.h"

PilotoSurpresa::PilotoSurpresa(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
	comeca = 1;
}

int PilotoSurpresa::passouTempo(int s)
{
	if (comeca > 0) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
		comeca--;
	}
	//ACELARAR/DESACELARAR A CADA SEGUNDO ALEATORIAMENTE

	if ((rand() % 100) < 5)	//A PROBABILIDADE DE DANIFICAR CARRO É DE 5%
		getCarro()->setEmergencia(CARRO_DANIFICADO);

	return getCarro()->getVelocidade() * s;
}

PilotoSurpresa::~PilotoSurpresa()
{
}
