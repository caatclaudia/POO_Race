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
	const double capacidadeMaxima;		
	double energia;
	int velocidade;
	const int velocidadeMaxima;			
	bool movimento;
	bool emergencia;
	bool condutor;
	int acidente;


public:
	 static char identificacao;

	Carro(const string marca, double cInicial, const double cMaxima, const int vMaxima, const string modelo="modelo base");
	
	string getMarca()const;
	string getModelo()const;
	char getID()const;
	double getCapacidadeMaxima()const;
	double getEnergia()const;
	void setEnergia(double ene);
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

	bool operator==(const Carro &ob)const;

	bool carregaEnergia(double ene);
	void carregaEnergiaM();
	void descarregaEnergia(double ene);
	
	void acelarar();
	void travar();

	void acidenteDanifica();
	void acidenteDanoInevitavel(Piloto* ob);

	string getAsString()const;

	int passouTempo(int s);
	
	~Carro();
};



