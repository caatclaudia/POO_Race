#pragma once

#include "Piloto.h"

class PilotoSurpresa : public Piloto
{
	const double prob;
	
public:
	PilotoSurpresa(const string nome, const string t);

	int passouTempo(Pista* pista) override;

	PilotoSurpresa* duplica()const override;

	~PilotoSurpresa();
};

