#include "CrazyDriver.h"
#include "Carro.h"
#include "Pista.h"
#include "Corrida.h"

CrazyDriver::CrazyDriver(const string nome, const string t) : Piloto(nome, t), prob(0.05), segundo(rand() % 5 + 1)
{
}

int CrazyDriver::passouTempo(int s, Pista* pista)
{
	if (Piloto::getCarro() != nullptr) {
		int n = 0;
		if (Piloto::getSegundos() < segundo) {
			Piloto::setSegundos(Piloto::getSegundos() + 1);
			return 0;
		}
		else if (Piloto::getSegundos() == segundo) {
			getCarro()->setMovimento(CARRO_MOVIMENTO);
			acelararCarro();
		}
		else {
			for (int i = 0; i < (int)pista->getCorridas().size(); i++) {
				if (pista->getCorridaN(i)->getParticipante()->getNome() == Piloto::getNome()) {
					n = pista->getCorridaN(i)->getLugar();
					if (pista->getCorridaN(i)->getLugar() == (int)pista->getCorridas().size() && getCarro()->getVelocidade() != 0)
						travarCarro();
					else if (pista->getCorridaN(i)->getLugar() != 1)
						acelararCarro();
				}
			}
		}

		if (getCarro()->getEnergia() == 0) {
			getCarro()->setEmergencia(EMERGENCIA_ON);
			saiCarro();
			for (auto ptr = pista->getCorridas().begin(); ptr != pista->getCorridas().end(); ptr++) {
				if ((*ptr)->getParticipante()->getNome() == getNome())
					(*ptr)->setTravar(true);
			}
		}

		Piloto::setSegundos(Piloto::getSegundos() + 1);

		if ((rand() % 100) < 5) {
			getCarro()->acidenteDanoIrreparavel(this);
			for (int i = 0; i < (int)pista->getCorridas().size(); i++) {
				if (pista->getCorridaN(i)->getLugar() == (n + 1)) {
					pista->getCorridaN(i)->getCarro()->acidenteDanoIrreparavel(pista->getCorridaN(i)->getParticipante());

				}
			}
		}

		pista->verificaLugar();
		for (int j = 0; j < (int)pista->getCorridas().size(); j++) {
			if (pista->getCorridaN(j)->getParticipante()->getNome() == Piloto::getNome()) {
				if (pista->getCorridaN(j)->getLugar() > n&& n != (int)pista->getCorridas().size()) {
					for (int i = 0; i < 2; i++)
						acelararCarro();
				}
			}
		}

		if (getCarro() == nullptr) {/*
			for (auto ptr = pista->getCorridas().begin(); ptr != pista->getCorridas().end(); ptr++) {
				if ((*ptr)->getParticipante()->getNome() == getNome())
					(*ptr)->setTravar(true);
			}*/
			return 0;
		}
		return Piloto::getCarro()->getVelocidade() * 1;
	}
	return 0;
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
