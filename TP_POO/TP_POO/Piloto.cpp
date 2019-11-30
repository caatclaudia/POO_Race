#include "Piloto.h"
#include "Carro.h"


Piloto::Piloto(const string nome, const string t):nome(nome), tipo(t)
{
	carro = nullptr;
	pontuacao = 0;
}


string Piloto::getNome() const
{
	return nome;
}

string Piloto::getTipo() const
{
	return tipo;
}

Carro* Piloto::getCarro()const
{
	return carro;
}

void Piloto::setCarro(Carro *ob)
{
	carro = ob;
}

int Piloto::getPontuacao() const
{
	return pontuacao;
}

void Piloto::acrescentaPontuacao(int n)
{
	pontuacao = pontuacao + n;
}

bool Piloto::entraCarro(Carro *ob) 
{
	if (carro!=nullptr)
		return false;
	carro = ob;
	ob->setCondutor(true);
	return true;
}

bool Piloto::saiCarro() {
	if (carro==nullptr)
		return false;
	carro->setCondutor(false);
	carro = nullptr;
	return true;
}

void Piloto::travarCarro()
{
	carro->travar();
}

void Piloto::acelararCarro()
{
	carro->acelarar();
}

int Piloto::passouTempo(int s)
{
	if (carro->getMovimento() == CARRO_MOVIMENTO) {
		return carro->getVelocidade() * s;
	}
	else
		return 0;
}

string Piloto::getAsString() const
{
	ostringstream oss;
	oss << "Piloto " << nome;
	if (carro == nullptr)
		oss << " e nao tem carro" << endl;
	else
		oss << " esta no carro " << carro->getID() << endl;
	return oss.str();
}

bool Piloto::operator==(const Piloto& ob) const
{
	if (strcmp(nome.c_str(),ob.nome.c_str())==0)			
		return true;
	return false;
}

Piloto::~Piloto()
{
}

