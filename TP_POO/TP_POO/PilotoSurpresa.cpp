#include "PilotoSurpresa.h"
#include "Carro.h"

PilotoSurpresa::PilotoSurpresa(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
}

int PilotoSurpresa::passouTempo(int s)
{
	if (Piloto::getSegundos() == 1) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
	}
	//ACELARAR/DESACELARAR A CADA SEGUNDO ALEATORIAMENTE

	if ((rand() % 100) < 5)	//A PROBABILIDADE DE DANIFICAR CARRO É DE 5%
		getCarro()->setEmergencia(CARRO_DANIFICADO);

	Piloto::setSegundos(Piloto::getSegundos() + 1);		//VERIFICAR ESTA CHAMADA, SE É 1SEG OU MAIS

	return getCarro()->getVelocidade() * s;
}

string PilotoSurpresa::getProbAsString() const
{
	ostringstream oss;
	oss <<Piloto::getProbAsString()<< " tem " << prob << " probabilidade de explodir o carro!" << endl;
	return oss.str();
}

bool PilotoSurpresa::acidente()
{
	return false;
}

int PilotoSurpresa::verificaLugar(int lugar, int max)
{
	return 0;
}

void PilotoSurpresa::perdeuLugar()
{
}

PilotoSurpresa* PilotoSurpresa::duplica() const
{
	return new PilotoSurpresa(*this);
}

PilotoSurpresa::~PilotoSurpresa()
{
}
