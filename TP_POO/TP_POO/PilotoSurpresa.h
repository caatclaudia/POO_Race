#pragma once

#include "Piloto.h"

class PilotoSurpresa : public Piloto
{
	const double prob;
	
public:
	PilotoSurpresa(const string nome, const string t);

	int passouTempo(int s) override;
	string getProbAsString()const;

	PilotoSurpresa* duplica()const override;

	~PilotoSurpresa();
};

