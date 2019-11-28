#include "Garagem.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Piloto.h"


Garagem::Garagem()
{
}

bool Garagem::adicionaCarro(Carro *car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if ((*ptr)->getID() == car->getID())
			return false;
	}
	carros.push_back(car);
	return true;
}

void Garagem::removeCarro(Carro* car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if (*(ptr) == car)
			*carros.erase(ptr);
	}
}

vector<Carro*>& Garagem::getCarros()
{
	return carros;
}


Garagem::~Garagem()
{
	for (Carro* p : carros)
		delete p;
}
