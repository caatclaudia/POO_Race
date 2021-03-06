#include "Piloto.h"
#include "Carro.h"
#include "Pista.h"


Piloto::Piloto(const string nome, const string t):nome(nome), tipo(t)
{
	carro = nullptr;
	pontuacao = 0;
	segundos = 0;
	vivo = true;
	competicao = false;
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

int Piloto::getSegundos() const
{
	return segundos;
}

void Piloto::setSegundos(int n)
{
	segundos = n;
}

bool Piloto::getVivo() const
{
	return vivo;
}

void Piloto::morreu()
{
	vivo = false;
}

bool Piloto::getCompeticao() const
{
	return competicao;
}

void Piloto::terminaCompeticao()
{
	competicao = false;
}

void Piloto::iniciaCompeticao()
{
	competicao = true;
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
	if(carro!=nullptr)
		carro->travar();
}

void Piloto::acelararCarro()
{
	if (carro != nullptr)
		carro->acelarar();
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

