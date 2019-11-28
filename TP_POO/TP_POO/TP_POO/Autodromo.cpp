#include "Autodromo.h"
#include "Pista.h"
#include "Piloto.h"
#include "Carro.h"
#include "Garagem.h"
#include "Corrida.h"


Autodromo::Autodromo(int N, double comprimento, string nome) {
	this->nome = nome;
	p = new Pista(N, comprimento);
}

string Autodromo::getNome() const
{
	return nome;
}

Pista* Autodromo::getPista()const
{
	return p;
}

string Autodromo::getAsString() const
{
	ostringstream oss;
	oss << "Autodromo " << nome << p->getAsString() << endl;
	return oss.str();
}

string Autodromo::obterInfo() const
{
	ostringstream oss;
	oss << "Informacão sobre a corrida no autodromo " << nome << " (" << p->getComprimento() << "): "<<endl;
	if (p->getComecou() == JA_COMECOU) {
		for (int n = 1; n <= p->nParticipantes(); n++) {
			for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++) {
				if ((*ptr)->getLugar() == n)
					oss << n << ". " << (*ptr)->getCarro()->getID() << " " << (*ptr)->getCarro()->getMarca() << " / " << (*ptr)->getParticipante()->getNome()
					<< " (" << (*ptr)->getParticipante()->getTipo() << " ) - " << (*ptr)->getCarro()->getEnergia() << "mAh, " << (*ptr)->getCarro()->getCapacidadeMaxima()
					<< "mAh - " << (*ptr)->getPosicao() << "m - " << (*ptr)->getCarro()->getVelocidade() << "m/s" << endl;
			}
		}
	}
	else
		oss << "Corrida nao iniciada" << endl;
	return oss.str();
}


Autodromo::~Autodromo()
{
	delete p;
}
