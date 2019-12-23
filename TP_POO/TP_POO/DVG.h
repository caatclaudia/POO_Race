#ifndef DVG_H
#define DVG_H


class Carro;
class Piloto;

#include <vector>
#include <string>
using namespace std;

class DVG
{
	string nomeDVG;
	vector<Piloto *> pilotos;
	vector<Carro*> carros;
public:
	static int Nome;
	DVG(string nomeDVG = "default");
	DVG(const DVG &outro);
	void setNomeDVG(string nome);
	string getNomeDVG() const;

	vector<Carro*> & getCarro();
	int getNCarros()const;
	void novoCarro(string marca, float cInicial, float cMaxima, int vMaxima, string modelo="modelo base");
	void removeCarro(Carro* car);
	vector<Piloto*> & getPiloto();
	int getNPilotos()const;
	void novoPiloto(string nome, string t);
	void removePiloto(Piloto *pil);

	int getNCarrosDisponiveis();
	int getNPilotosDisponiveis();

	Carro* procuraCarro(char id)const;
	Piloto* procuraPiloto(string nome)const;
	Carro* procuraCarroN(int n)const;
	Piloto* procuraPilotoN(int n)const;
	Piloto* pilotoNoCarro(char id)const;

	void terminaCompeticao();

	void removeMortos();
	void removeIrreparaveis();

	DVG& operator=(const DVG &outro);

	~DVG();
};
#endif