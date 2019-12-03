#pragma once

#include "Piloto.h"

class CrazyDriver : public Piloto
{
	const double prob;
	const int segundo;
	
public:

	CrazyDriver(const string nome, const string t);

	int passouTempo(int s) override;

	~CrazyDriver();
};

