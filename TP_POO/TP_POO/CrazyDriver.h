#pragma once

#include "Piloto.h"
class Pista;

class CrazyDriver : public Piloto
{
	const double prob;
	const int segundo;
	
public:

	CrazyDriver(const string nome, const string t);

	int passouTempo(Pista* pista) override;

	CrazyDriver* duplica()const override;

	~CrazyDriver();
};

