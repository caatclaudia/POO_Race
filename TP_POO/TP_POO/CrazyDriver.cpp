#include "CrazyDriver.h"
#include "Carro.h"

CrazyDriver::CrazyDriver(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
	comeca = rand() % 5 + 1;
}

int CrazyDriver::passouTempo(int s)
{
	if (comeca > 0) {	//SO COMECA A CORRER NO XºSEGUNDO(ALEATORIO ENTRE 1 E 5)
		comeca--;
		return 0;
	}
	else if (comeca == 0) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
		comeca--;
	}

	/*A CADA SEGUNDO PERGUNTA A PISTA QUAL O SEU LUGAR
		SE FOR !=1 OU !=ULTIMO ACELERA
		SE FOR 1 MANTEM
		SE FOR ULTIMO TRAVA

	SE NOTAR QUE PERDEU LUGARES AUMENTA VELOCIDADE EM 2m/s */

	if (getCarro()->getEnergia() == 0)	//SE FICAR SEM ENERGIA, ACENDE SINAL DE EMERGENCIA
		getCarro()->setEmergencia(EMERGENCIA_ON);

	//PROBABILIDADE DE 5% DE DANIFICAR IRREMEDIAVELMENTE E O CARRO DE TRAS TB
	
	return getCarro()->getVelocidade() * s;
}

CrazyDriver::~CrazyDriver()
{
}
