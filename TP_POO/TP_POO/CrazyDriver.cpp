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

	if (getCarro()->getEnergia() == 0)
		getCarro()->setEmergencia(EMERGENCIA_ON);
	
	return getCarro()->getVelocidade() * 1;
}

bool CrazyDriver::acidente() {
	if ((rand() % 100) < 5) {
		getCarro()->acidenteDanoIrreparavel(this);
		return true;
	}
	return false;
}

string CrazyDriver::getProbAsString()const 
{
	ostringstream oss;
	oss << Piloto::getProbAsString() << " tem " << prob << " probabilidade de danificar irremidiavelmente o carro!" << endl;
	return oss.str();
}

int CrazyDriver::verificaLugar(int lugar, int max)
{
	if (lugar == max)
		travarCarro();
	else if (lugar != 1)
		acelararCarro();

	Piloto::setSegundos(Piloto::getSegundos() + 1);

	return getCarro()->getVelocidade() * 1;
}

void CrazyDriver::perdeuLugar()
{
	for(int i=0; i<2; i++)
		acelararCarro();
}

CrazyDriver* CrazyDriver::duplica() const
{
	return new CrazyDriver(*this);
}

CrazyDriver::~CrazyDriver()
{
}
