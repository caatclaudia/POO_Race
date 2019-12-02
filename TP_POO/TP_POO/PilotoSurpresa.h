#pragma once

#include "Piloto.h"

class PilotoSurpresa : public Piloto
{
	const double prob;
	int comeca;
	
public:
	PilotoSurpresa(const string nome, const string t);

	int passouTempo(int s) override;

	~PilotoSurpresa();
};

