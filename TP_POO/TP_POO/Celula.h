#pragma once
class Celula
{
	int x, y;
	char valor;

public:
	Celula();
	Celula(const Celula& t);
	
	char GetValor() const;
	void SetValor(char val=' ');
	int GetX() const;
	void SetX(int x);
	int GetY() const;
	void SetY(int y);

	virtual ~Celula();

	Celula& operator=(const Celula& t);
};

