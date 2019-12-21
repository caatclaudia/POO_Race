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
	gar = new Garagem();
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

Garagem* Autodromo::getGaragem() const
{
	return gar;
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

void Autodromo::getAsStringPontPilotos()
{
	int i = 1, max, indiceMax, l;
	vector<int> indiceUsado;

	for (int j = 0; (int)indiceUsado.size() != (int)p->getCorridas().size(); ) {
		max = 0;
		for (l = 0; l < (int)p->getCorridas().size(); l++) {
			bool EXISTE = false;
			if (p->getCorridaN(l)->getParticipante()->getPontuacao() >= max) {
				for (int k = 0; k < (int)indiceUsado.size(); k++) {
					if (l == indiceUsado[k])
						EXISTE = true;
				}
				if (!EXISTE) {
					indiceMax = l;
					max = p->getCorridaN(l)->getParticipante()->getPontuacao();
				}
			}
		}
		indiceUsado.push_back(indiceMax);
			
		Consola::gotoxy(76, i++);
		cout << (int)indiceUsado.size() << ": Piloto " << (p->getCorridaN(indiceMax)->getParticipante()->getNome()) << " com " << (p->getCorridaN(indiceMax)->getParticipante()->getPontuacao())<< " pontos!";
	}
}

void Autodromo::reverCarros()
{
	vector<Carro*> carrosARemover;
	for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++) {
		if ((*ptr)->getCarro()->getAcidente() != CARRO_BOMESTADO || (*ptr)->getCarro()->getEmergencia() == EMERGENCIA_ON) {
			gar->adicionaCarro((*ptr)->getCarro());
			carrosARemover.push_back((*ptr)->getCarro());
		}
	}
	for (auto pt = carrosARemover.begin(); pt!=carrosARemover.end(); pt++)
		p->removerCarro((*pt)->getID());
	for (auto p : carrosARemover)
		delete p;
}

Autodromo::~Autodromo()
{
	delete p;
	delete gar;
}
