#pragma once
#include <msxml.h>

class Autodromo;
class Carro;
class Corrida;
class Piloto;
class Pista;


class Corrida
{	
	int posicao, lugar;
	Piloto* participante;
	Carro* carro;
	
	
public:
	Corrida(Carro *part);
	Corrida(Carro* part, Piloto* pil);

	int getPosicao()const;
	void setPosicao(int pos);
	void avancaPosicao(int pos);

	int getLugar()const;
	void setLugar(int lug);

	Piloto* getParticipante()const;
	void setParticipante(Piloto* pil);

	Carro* getCarro()const;
	void setCarro(Carro* car);

	bool continuaDisponivel() const;

	bool getMovimento()const;
	
	~Corrida();
};

