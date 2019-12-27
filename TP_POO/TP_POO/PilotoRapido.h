#pragma once

#include "Piloto.h"

class PilotoRapido : public Piloto
{
	const double prob;
	int contador;

public:
	PilotoRapido(const string nome, const string t);

	int passouTempo(Pista* pista) override;

	PilotoRapido* duplica()const override;

	~PilotoRapido();
};

