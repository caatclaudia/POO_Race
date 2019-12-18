#include "PilotoRapido.h"
#include "Carro.h"

PilotoRapido::PilotoRapido(const string nome, const string t) : Piloto(nome, t), prob(0.1)
{
	contador = 0;
}

int PilotoRapido::passouTempo(int s)
{
	if (Piloto::getSegundos() == 1) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
	}
	else {
		/*ACELERA ATE VER QUE ENERGIA = MAXIMA/2,
		DPS DISSO SO ACELERA 1m/s POR CADA 3SEG */
		if (Piloto::getCarro()->getEnergia() >= Piloto::getCarro()->getCapacidadeMaxima() / 2) {
			acelararCarro();
			if (Piloto::getCarro()->getEnergia() == Piloto::getCarro()->getCapacidadeMaxima() / 2)
				contador++;
		}
		else {
			if ((contador % 3) == 0)
				acelararCarro();
			contador++;
		}
	}

	//A cada 10seg: 
	if((Piloto::getSegundos() % 10) == 0 && (rand() % 100) < 10) //A CADA 10SEG TEM PROBABILIDADE DE 10% DE ATIVAR BOTAO DE EMERGENCIA
		getCarro()->setEmergencia(EMERGENCIA_ON);

	Piloto::setSegundos(Piloto::getSegundos() + 1);
	
	return getCarro()->getVelocidade() * s;
}

string PilotoRapido::getProbAsString() const
{
	ostringstream oss;
	oss << Piloto::getProbAsString() << " tem " << prob << " probabilidade de sofrer ataque de panico!" << endl;
	return oss.str();
}

PilotoRapido* PilotoRapido::duplica() const
{
	return new PilotoRapido(*this);
}

PilotoRapido::~PilotoRapido()
{
}
