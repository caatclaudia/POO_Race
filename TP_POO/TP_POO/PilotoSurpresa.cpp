#include "PilotoSurpresa.h"
#include "Carro.h"
#include "Pista.h"
#include "Corrida.h"

PilotoSurpresa::PilotoSurpresa(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
}

int PilotoSurpresa::passouTempo(int s, Pista* pista)
{
	if (Piloto::getCarro() != nullptr) {
		if (Piloto::getSegundos() == 1) {
			getCarro()->setMovimento(CARRO_MOVIMENTO);
			acelararCarro();
		}
		else {
			if ((rand() % 100) < 20)
				travarCarro();
			else if ((rand() % 100) < 50) {
				for (int i = 0; i < 2; i++)
					acelararCarro();
			}
		}

		if ((rand() % 100) < 5) {
			getCarro()->setEmergencia(EMERGENCIA_ON);
			saiCarro();
		}

		Piloto::setSegundos(Piloto::getSegundos() + 1);

		if (getCarro() == nullptr) {/*
			for (auto ptr = pista->getCorridas().begin(); ptr != pista->getCorridas().end(); ptr++) {
				if ((*ptr)->getParticipante()->getNome() == getNome())
					(*ptr)->setTravar(true);
			}*/
			return 0;
		}
		return getCarro()->getVelocidade() * s;
	}
	return 0;
}

string PilotoSurpresa::getProbAsString() const
{
	ostringstream oss;
	oss <<Piloto::getProbAsString()<< " tem " << prob << " probabilidade de explodir o carro!" << endl;
	return oss.str();
}

PilotoSurpresa* PilotoSurpresa::duplica() const
{
	return new PilotoSurpresa(*this);
}

PilotoSurpresa::~PilotoSurpresa()
{
}
