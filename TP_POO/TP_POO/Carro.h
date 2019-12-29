#pragma once

#define CARRO_MOVIMENTO true
#define CARRO_PARADO false
#define EMERGENCIA_ON true
#define EMERGENCIA_OFF false
#define CARRO_BOMESTADO 1
#define CARRO_DANIFICADO 0
#define CARRO_IRREPARAVEL -1
#define CARRO_CONDUTOR true
#define CARRO_SEM_CONDUTOR false

#include <string>
using namespace std;
class Piloto;

class Carro
{
	const string marca, modelo;			
	char ID;						
	const float capacidadeMaxima;
	float energia;
	int velocidade;
	const int velocidadeMaxima;			
	bool movimento;
	bool emergencia;
	bool condutor;
	int acidente;
	int cor;

public:
	 static char identificacao;

	Carro(const string marca, float cInicial, const float cMaxima, const int vMaxima, const string modelo="modelo base");
	
	string getMarca()const;
	string getModelo()const;
	char getID()const;
	float getCapacidadeMaxima()const;
	float getEnergia()const;
	void setEnergia(float ene);
	int getVelocidade()const;
	void setVelocidade(int v);
	int getVelocidadeMaxima()const;
	bool getMovimento()const;
	void setMovimento(bool mov);
	bool getEmergencia()const;
	void setEmergencia(bool emer);
	bool getCondutor()const;
	void setCondutor(bool v);
	int getAcidente()const;
	void setAcidente(int aci);
	int getCor()const;

	bool operator==(const Carro &ob)const;

	bool carregaEnergia(float ene);
	void carregaEnergiaM();
	void descarregaEnergia(float ene);
	
	void acelarar();
	void travar();

	void acidenteDanoIrreparavel(Piloto* ob);
	bool disponivel() const;

	string getAsString()const;

	Carro* duplica()const;
	
	~Carro();
};



