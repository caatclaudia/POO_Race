#ifndef DVG_H
#define DVG_H


class Carro;
class Piloto;

#include <vector>
#include <string>
using namespace std;

class DVG
{
	vector<Piloto *> pilotos;
	vector<Carro*> carros;
public:
	static int Nome;
	DVG();

	vector<Carro*> & getCarro();
	int getNCarros()const;
	void novoCarro(string marca, double cInicial, double cMaxima, int vMaxima, string modelo="modelo base");
	void removeCarro(Carro* car);
	vector<Piloto*> & getPiloto();
	int getNPilotos()const;
	void novoPiloto(string nome, string t);
	void removePiloto(Piloto *pil);


	Carro* procuraCarro(char id)const;
	Piloto* procuraPiloto(string nome)const;
	Piloto* pilotoNoCarro(char id)const;

	string getAsString()const;


	~DVG();
};
#endif