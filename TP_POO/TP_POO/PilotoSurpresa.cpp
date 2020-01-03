#include "PilotoSurpresa.h"
#include "Carro.h"
#include "Pista.h"
#include "Corrida.h"
#include <time.h>

PilotoSurpresa::PilotoSurpresa(const string nome, const string t) : Piloto(nome, t), prob(0.05)
{
}

int PilotoSurpresa::passouTempo(Pista* pista)
{
	srand((unsigned)time(NULL));
	if (Piloto::getCarro() != nullptr) {
		int p = 0;
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
		if (getCarro()->getEnergia() == 0) {
			getCarro()->setEmergencia(EMERGENCIA_ON);
			saiCarro();
			for (auto ptr = pista->getCorridas().begin(); ptr != pista->getCorridas().end(); ptr++) {
				if ((*ptr)->getParticipante()->getNome() == getNome())
					(*ptr)->setTravar(true);
			}
		}

		if ((rand() % 100) < 5 && getCarro() != nullptr) {
			getCarro()->acidenteDanoIrreparavel(this);
			for (int i = 0; i < (int)pista->getCorridas().size(); i++) 
				if (pista->getCorridaN(i)->getParticipante()->getNome() == Piloto::getNome()) 
					p = pista->getCorridaN(i)->getPosicao();
			for ( int i = 0; i < (int)pista->getCorridas().size(); i++) {
				if ((pista->getCorridaN(i)->getPosicao()>=(p - 10) && pista->getCorridaN(i)->getPosicao()<=(p + 10)) && pista->getCorridaN(i)->getParticipante()->getNome() != Piloto::getNome()) {
					pista->getCorridaN(i)->getCarro()->setEmergencia(EMERGENCIA_ON);
					pista->getCorridaN(i)->getParticipante()->saiCarro();
					pista->getCorridaN(i)->setTravar(true);
				}
			}
		}

		Piloto::setSegundos(Piloto::getSegundos() + 1);

		if (getCarro() == nullptr)
			return 0;
		return getCarro()->getVelocidade();
	}
	return 0;
}

PilotoSurpresa* PilotoSurpresa::duplica() const
{
	return new PilotoSurpresa(*this);
}

PilotoSurpresa::~PilotoSurpresa()
{
}
