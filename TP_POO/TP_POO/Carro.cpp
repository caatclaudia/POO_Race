#include "Carro.h"
#include "Piloto.h"



Carro::Carro(const string marca, float cInicial, const float cMaxima, const int vMaxima, const string modelo): capacidadeMaxima(cMaxima), velocidadeMaxima(vMaxima), marca(marca),modelo(modelo), ID(identificacao)
{
	
	if (identificacao == 'z' || identificacao == '?')
		identificacao = '?';
	else
		identificacao++;
	
	movimento = CARRO_PARADO;
	energia = cInicial;
	velocidade = 0;
	emergencia = EMERGENCIA_OFF;
	acidente = CARRO_BOMESTADO;
	condutor = CARRO_SEM_CONDUTOR;
}

string Carro::getMarca()const
{
	return marca;
}

string Carro::getModelo()const
{
	return modelo;
}

char Carro::getID()const
{
	return ID;
}

float Carro::getCapacidadeMaxima()const
{
	return capacidadeMaxima;
}

float Carro::getEnergia()const
{
	return energia;
}

void Carro::setEnergia(float ene)
{
	energia = ene;
}

int Carro::getVelocidade()const
{
	return velocidade;
}

void Carro::setVelocidade(int v)
{
	velocidade = v;
}

int Carro::getVelocidadeMaxima()const
{
	return velocidadeMaxima;
}

bool Carro::getMovimento()const
{
	return movimento;
}

void Carro::setMovimento(bool mov)
{
	movimento = mov;
}

bool Carro::getEmergencia()const
{
	return emergencia;
}

void Carro::setEmergencia(bool emer)
{
	emergencia = emer;
}

bool Carro::getCondutor()const 
{
	return condutor;
}

void Carro::setCondutor(bool v)
{
	if (v)
		condutor = CARRO_CONDUTOR;
	else
		condutor = CARRO_SEM_CONDUTOR;
}

int Carro::getAcidente()const
{
	return acidente;
}

void Carro::setAcidente(int aci)
{
	acidente = aci;
}

bool Carro::operator==(const Carro& ob) const
{
	if (ID == ob.ID)
		return true;
	return false;
}

bool Carro::carregaEnergia(float ene) {
	if (ene > 0 && movimento == CARRO_PARADO) {
		energia = energia + ene;
		if (energia > capacidadeMaxima)
			energia = capacidadeMaxima;
		return true;
	}
	return false;
}

void Carro::carregaEnergiaM()
{
	energia = capacidadeMaxima;
}


void Carro::descarregaEnergia(float ene)
{
	if (ene > 0 && movimento == CARRO_MOVIMENTO) {
		energia = energia - ene;
		if (energia <= 0) {
			energia = 0;
			do{
				travar();
			} while (velocidade > 0);
			movimento = CARRO_PARADO;
		}
	}
}

void Carro::acelarar() 
{
	if (condutor == CARRO_CONDUTOR) {
		if (velocidade == 0) {
			movimento = CARRO_MOVIMENTO;
			velocidade++;
		}
		else if (velocidade < velocidadeMaxima)
			velocidade++;
		descarregaEnergia(0.1f);
	}
}

void Carro::travar() 
{
	if (condutor == CARRO_CONDUTOR) {
		if (velocidade > 0)
			velocidade--;
	}
	if(velocidade==0)
		movimento = CARRO_PARADO;
}

void Carro::acidenteDanifica() 
{
	do {
		travar();
	} while (velocidade > 0);
	acidente = CARRO_DANIFICADO;
}

void Carro::acidenteDanoIrreparavel(Piloto* ob)
{
	acidente = CARRO_IRREPARAVEL;
	ob->saiCarro();
	ob->morreu();
}

string Carro::getAsString() const
{
	ostringstream oss;
	oss << "Carro " << ID << " -> "<<marca << " " <<modelo<< endl;
	return oss.str();
}

Carro* Carro::duplica() const
{
	return new Carro(*this);
}

Carro::~Carro()
{
}
