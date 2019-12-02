#pragma once

#include "Piloto.h"

class PilotoRapido : public Piloto
{
	const double prob;
	int comeca;

public:
	PilotoRapido(const string nome, const string t);

	int passouTempo(int s) override;

	~PilotoRapido();
};

