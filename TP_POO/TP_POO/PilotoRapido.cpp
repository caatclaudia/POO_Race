#include "PilotoRapido.h"
#include "Carro.h"
#include "Pista.h"
#include "Corrida.h"

PilotoRapido::PilotoRapido(const string nome, const string t) : Piloto(nome, t), prob(0.1)
{
	contador = 0;
}

int PilotoRapido::passouTempo(int s, Pista* pista)
{
	if (Piloto::getCarro() != nullptr) {
		if (Piloto::getSegundos() == 1) {
			getCarro()->setMovimento(CARRO_MOVIMENTO);
			acelararCarro();
		}
		else {
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

		if ((Piloto::getSegundos() % 10) == 0 && (rand() % 100) < 10) {
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
