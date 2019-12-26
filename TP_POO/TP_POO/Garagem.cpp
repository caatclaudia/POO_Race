#include "Garagem.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Piloto.h"
#include "Pista.h"
#include "Corrida.h"
#include <sstream>
#include <iostream>


Garagem::Garagem()
{
}

bool Garagem::adicionaCarro(Carro* car)
{
	for(int i=0;i<(int)carros.size();i++){
		if (carros[i]->getID() == car->getID())
			return false;
	}
	carros.push_back(car);	
	return true;
}

void Garagem::removeCarro(Carro* car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if ((*ptr)->getID() == car->getID())
			carros.erase(ptr);
	}
}

vector<Carro*>& Garagem::getCarros()
{
	return carros;
}

void Garagem::limpaCarros()
{
	carros.clear();
}


Garagem::~Garagem()
{
	carros.clear();
}
