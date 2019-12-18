#pragma once

#include "Piloto.h"

class PilotoRapido : public Piloto
{
	const double prob;
	int contador;

public:
	PilotoRapido(const string nome, const string t);

	int passouTempo(int s) override;
	string getProbAsString()const;

	virtual bool acidente() ;
	virtual int verificaLugar(int lugar, int max);
	virtual void perdeuLugar();

	PilotoRapido* duplica()const override;

	~PilotoRapido();
};

