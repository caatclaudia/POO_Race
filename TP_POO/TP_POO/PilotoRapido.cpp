#include "PilotoRapido.h"
#include "Carro.h"

PilotoRapido::PilotoRapido(const string nome, const string t) : Piloto(nome, t), prob(0.1)
{
	comeca = 1;
}

/*COMECA A CORRER NO 1ºSEGUNDO
	ACELERA ATE VER QUE ENERGIA = MAXIMA/2,
	DPS DISSO SO ACELERA 1m/s POR CADA 3SEG

	A CADA 10SEG TEM PROBABILIDADE DE 10% DE ATIVAR BOTAO DE EMERGENCIA
*/

int PilotoRapido::passouTempo(int s)
{
	if (comeca > 0) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
		comeca--;
	}
	return getCarro()->getVelocidade() * s;
}

PilotoRapido::~PilotoRapido()
{
}
