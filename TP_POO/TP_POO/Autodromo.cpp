#include "Autodromo.h"
#include "Pista.h"
#include "Piloto.h"
#include "Carro.h"
#include "Garagem.h"
#include "Corrida.h"
#include "Consola.h"


Autodromo::Autodromo(int N, double comprimento,  const string n):nome(n) 
{
	
	p = new Pista(N, comprimento);
	gar = nullptr;
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
	oss << "Autodromo " << nome << p->getAsString();
	return oss.str();
}

void Autodromo::obterInfo() const
{
	int i = 1;
	Consola::gotoxy(76, i);
	cout << "Corrida em " << nome << " (" << p->getComprimento() << "m): ";
	if (p->getComecou() == NAO_COMECOU) {
		Consola::gotoxy(76, i++);
		cout << "Corrida nao iniciada";
	}
	else{
		for (int n = 1; n <= p->nParticipantes(); n++) {
			for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++) {
				if ((*ptr)->getLugar() == n) {
					Consola::gotoxy(76, i++);
					cout << n << ". " << (*ptr)->getCarro()->getID() << " " << (*ptr)->getCarro()->getMarca() << " / " << (*ptr)->getParticipante()->getNome()
						<< " (" << (*ptr)->getParticipante()->getTipo() << ")";
					Consola::gotoxy(77, i++);
					cout << (*ptr)->getCarro()->getEnergia() << "mAh, " << (*ptr)->getCarro()->getCapacidadeMaxima()
						<< "mAh - " << (*ptr)->getPosicao() + 1 << "m - " << (*ptr)->getCarro()->getVelocidade() << "m/s" << endl;
				}
			}
		}
	}
}

void Autodromo::carregaCarros()
{
	for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++)
		(*ptr)->getCarro()->setEnergia((*ptr)->getCarro()->getCapacidadeMaxima());
	if(gar!=nullptr)
		for (auto ptr = gar->getCarros().begin(); ptr != gar->getCarros().end(); ptr++)
			(*ptr)->setEnergia((*ptr)->getCapacidadeMaxima());
}

bool Autodromo::acrescentaCarroPista(Carro* carro)
{
	if (carro->getMovimento() == false && carro->getCondutor() == false)
		return p->adicionarCarro(carro);
	return false;
}

bool Autodromo::acrescentaCarroGaragem(Carro* carro)		
{
	for (int i = 0; i < p->nParticipantes(); i++)
		if (p->getCorridaN(i)->getCarro()== carro)
			return false;
	return gar->adicionaCarro(carro);
}


Autodromo::~Autodromo()
{
	delete p;
}
