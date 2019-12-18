#pragma once

#include "Piloto.h"

class CrazyDriver : public Piloto
{
	const double prob;
	const int segundo;
	
public:

	CrazyDriver(const string nome, const string t);

	int passouTempo(int s) override;
	string getProbAsString()const;

	virtual bool acidente() override;
	virtual int verificaLugar(int lugar, int max) override;
	virtual void perdeuLugar() override;

	CrazyDriver* duplica()const override;

	~CrazyDriver();
};

