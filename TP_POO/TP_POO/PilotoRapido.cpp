#include "PilotoRapido.h"
#include "Carro.h"

PilotoRapido::PilotoRapido(const string nome, const string t) : Piloto(nome, t), prob(0.1)
{
}

int PilotoRapido::passouTempo(int s)
{
	if (Piloto::getSegundos() == 1) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
	}
	/*ACELERA ATE VER QUE ENERGIA = MAXIMA/2,
	DPS DISSO SO ACELERA 1m/s POR CADA 3SEG */

	//A cada 10seg: 
	//if((rand() % 100) < 10) //A CADA 10SEG TEM PROBABILIDADE DE 10% DE ATIVAR BOTAO DE EMERGENCIA
	//	getCarro()->setEmergencia(EMERGENCIA_ON);

	Piloto::setSegundos(Piloto::getSegundos() + 1);		//VERIFICAR ESTA CHAMADA, SE � 1SEG OU MAIS
	
	return getCarro()->getVelocidade() * s;
}

PilotoRapido::~PilotoRapido()
{
}
