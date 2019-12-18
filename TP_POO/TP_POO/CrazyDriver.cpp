#include "CrazyDriver.h"
#include "Carro.h"

CrazyDriver::CrazyDriver(const string nome, const string t) : Piloto(nome, t), prob(0.05), segundo(rand() % 5 + 1)
{
}

int CrazyDriver::passouTempo(int s)
{
	if (Piloto::getSegundos() < segundo) {
		Piloto::setSegundos(Piloto::getSegundos() + 1);
		return 0;
	}
	else if (Piloto::getSegundos() == segundo) {
		getCarro()->setMovimento(CARRO_MOVIMENTO);
		acelararCarro();
	}

	/*A CADA SEGUNDO PERGUNTA A PISTA QUAL O SEU LUGAR
		SE FOR !=1 OU !=ULTIMO ACELERA
		SE FOR 1 MANTEM
		SE FOR ULTIMO TRAVA

	SE NOTAR QUE PERDEU LUGARES AUMENTA VELOCIDADE EM 2m/s */

	if (getCarro()->getEnergia() == 0)	//SE FICAR SEM ENERGIA, ACENDE SINAL DE EMERGENCIA
		getCarro()->setEmergencia(EMERGENCIA_ON);

	Piloto::setSegundos(Piloto::getSegundos()+1);		//VERIFICAR ESTA CHAMADA, SE É 1SEG OU MAIS

	//PROBABILIDADE DE 5% DE DANIFICAR IRREMEDIAVELMENTE E O CARRO DE TRAS TB
	
	return getCarro()->getVelocidade() * s;
}

string CrazyDriver::getProbAsString()const 
{
	ostringstream oss;
	oss << Piloto::getProbAsString() << " tem " << prob << " probabilidade de danificar irremidiavelmente o carro!" << endl;
	return oss.str();
}

CrazyDriver* CrazyDriver::duplica() const
{
	return new CrazyDriver(*this);
}

CrazyDriver::~CrazyDriver()
{
}
