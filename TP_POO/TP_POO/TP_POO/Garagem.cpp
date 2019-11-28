#include "Garagem.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Piloto.h"


Garagem::Garagem()
{
}

void Garagem::adicionaCarro(Carro *car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if ((*ptr)->getID() == car->getID())
			return;
	}
	carros.push_back(car);
}

void Garagem::removeCarro(Carro* car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if (*(ptr) == car)
			*carros.erase(ptr);
	}
}


Garagem::~Garagem()
{
	for (Carro* p : carros)
		delete p;
}
