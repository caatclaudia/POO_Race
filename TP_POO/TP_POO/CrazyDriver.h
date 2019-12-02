#pragma once

#include "Piloto.h"

class CrazyDriver : public Piloto
{
	const double prob;
	int comeca;
	
public:
	static int segundos;

	CrazyDriver(const string nome, const string t);

	int passouTempo(int s) override;

	~CrazyDriver();
};

