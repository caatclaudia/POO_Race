#include "Celula.h"
#include "Celula.h"


Celula::Celula()
{
}

Celula::Celula(const Celula& t)
{
	*this = t;
}

char Celula::GetValor() const
{
	return valor;
}

void Celula::SetValor(char val)
{
	valor = val;
}

int Celula::GetX() const
{
	return x;
}

void Celula::SetX(int x)
{
	this->x = x;
}

int Celula::GetY() const
{
	return y;
}

void Celula::SetY(int y)
{
	this->y = y;
}

Celula::~Celula() {
}

Celula& Celula::operator=(const Celula& ob) {
	if (this != &ob) {
		x = ob.x;
		y = ob.y;
		valor = ob.valor;
	}
	return *this;
}