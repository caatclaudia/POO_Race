#pragma once

class Autodromo;
class Carro;
class Piloto;
#include <string>
#include <vector>
using namespace std;

class Garagem
{
	vector<Carro *> carros;

public:
	Garagem();

	bool adicionaCarro(Carro* car);
	void removeCarro(Carro* car);
	vector<Carro*>& getCarros();

	~Garagem();
};

