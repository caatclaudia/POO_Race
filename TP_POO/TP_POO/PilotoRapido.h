#pragma once

#include "Piloto.h"

class PilotoRapido : public Piloto
{
	const double prob;
	int contador;

public:
	PilotoRapido(const string nome, const string t);

	int passouTempo(int s, Pista* pista) override;
	string getProbAsString()const;

	PilotoRapido* duplica()const override;

	~PilotoRapido();
};

