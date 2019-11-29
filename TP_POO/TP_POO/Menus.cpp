#include "Menus.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Pista.h"
#include "Piloto.h"
#include "Corrida.h"

using namespace std;

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Consola.h"

Menus::Menus()
{
}

void Menus::acrescentaAutodromo(int N, double comp, string nome) 
{
	bool igual = false;
	for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ++ptr) {
		if ((*ptr)->getNome() == nome)
			igual = true;
	}
	if (igual) {
		nome = nome + to_string(NomeAutodromos);
		autodromos.push_back(new Autodromo(N, comp, nome));
	}
	else {
		autodromos.push_back(new Autodromo(N, comp, nome));
	}
}

void Menus::base()const 
{
	int i;
	for (i = 0; i <= LINHAS_BASE; i++) {
		if (i == 0 || i == LINHAS_BASE) {
			for (int j = 0; j <= COLUNAS_BASE; j++) {
				Consola::gotoxy(j, i);
				cout << "+";
			}
		}
		Consola::gotoxy(0, i);
		cout << "+";
		Consola::gotoxy(COLUNAS_BASE, i);
		cout << "+";
	}
	for (i = 0; i <= COLUNAS_BASE; i++) {
		Consola::gotoxy(i, 19);
		cout << "+";
	}
	for (i = 1; i <= 18; i++) {
		Consola::gotoxy(74, i);
		cout << "+";
	}
	for (i = 76; i < COLUNAS_BASE; i++) {
		for (int j = 1; j < 19; j++) {
			Consola::gotoxy(i, j);
			cout << " ";
		}
	}
	for (int i = 1; i < COLUNAS_BASE; i++) {
		if (i >= 24) {
			Consola::gotoxy(i, 20);
			cout << " ";
		}
		Consola::gotoxy(i, 21);
		cout << " ";
	}

}

void Menus::carregaP(string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		string tipo, nome, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> tipo && buffer >> nome)
				controlo.novoPiloto(nome, tipo);
		}
		Consola::gotoxy(76, 1);
		cout << "Carregado com sucesso!";
	}
}

void Menus::carregaC(string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		int capI, capM, vel;
		string marca, modelo, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> vel && buffer >> capI && buffer >> capM && buffer >> marca) {
				if(buffer >> modelo)
					controlo.novoCarro(marca, capI, capM, vel, modelo);
				else
					controlo.novoCarro(marca, capI, capM, vel);
			}
		}
		Consola::gotoxy(76, 1);
		cout << "Carregado com sucesso!";
	}
}

void Menus::carregaA(string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		int n;
		double comp;
		string nome, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> n && buffer >> comp && buffer >> nome)
				acrescentaAutodromo(n, comp, nome);
		}
		Consola::gotoxy(76, 1);
		cout << "Carregado com sucesso!";
	}
}

int Menus::modo2(Autodromo* autodromo)
{
	string comando, comando1;
	bool PARAMETRO_INVALIDO;

	Consola::gotoxy(76, 1);
	cout << "Autodromo " << autodromo->getNome();
	do {
		PARAMETRO_INVALIDO = false;
		Consola::getch();
		base();
		fflush(stdout);
		Consola::gotoxy(2, 20);
		cout << "Introduza um comando: ";
		getline(cin, comando);
		stringstream buffer(comando);
		if (buffer >> comando1)
		{
			if (comando1 == "listacarros") {
				autodromo->getPista()->listaCarros();
			}
			else if (comando1 == "carregabat") {
				char letra;
				double num;
				if (buffer >> letra && buffer >> num && num > 0) {
					Consola::gotoxy(76, 1);
					cout << "Comando " << comando1 << " " << letra << " " << num;
					for (int i = 0; i < (int)autodromo->getPista()->getCorridas().size(); i++)
						if (autodromo->getPista()->getCorridaN(i)->getCarro()->getID() == letra) 
							autodromo->getPista()->getCorridaN(i)->getCarro()->carregaEnergia(num);
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "carregatudo") {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1;
				for (int i = 0; i < (int)autodromo->getPista()->getCorridas().size(); i++)
					autodromo->getPista()->getCorridaN(i)->getCarro()->carregaEnergiaM();
			}
			else if (comando1 == "corrida") {

				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1;

			}
			else if (comando1 == "acidente") {
				char letra;
				if (buffer >> letra) {
					Consola::gotoxy(76, 1);
					cout << "Comando " << comando1 << " " << letra;
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "stop") {
				string nome;
				if (buffer >> nome) {
					Consola::gotoxy(76, 1);
					cout << "Comando " << comando1 << " " << nome;
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "destroi") {
				char letra;
				if (buffer >> letra) {
					Consola::gotoxy(76, 1);
					cout << "Comando " << comando1 << " " << letra;
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "passatempo") {
				int n;
				if (buffer >> n && n > 0) {
					Consola::gotoxy(2, 21);
					cout << "Passou " << n << " segundos!";
					if (autodromo->getPista()->getComecou() == JA_TERMINOU) {
						Consola::gotoxy(76, 1);
						cout << "Corrida ja terminada!";
					}
					if (autodromo->getPista()->getComecou() == NAO_COMECOU) 
						autodromo->getPista()->comecarCorrida();
					if (autodromo->getPista()->getComecou() == JA_COMECOU) 
						movimentoCarros(autodromo, n);
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "log") {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1;

			}
			else if (comando1 == "pontuacao") {
				autodromo->getPista()->atualizaPontuacao();
				controlo.getAsStringPontPilotos();
			}
			else if (comando1 == "voltar") {
				Consola::gotoxy(76, 1);
				cout << "Voltando...";
			}
			else {
				Consola::gotoxy(76, 1);
				cout << "Comando errado!";
			}
			if (PARAMETRO_INVALIDO) {
				Consola::gotoxy(76, 1);
				cout << "Parametro invalido!";
			}
		}
	} while (comando1 != "voltar");
	return 1;
}

int Menus::modo1(string comando)
{
	string comando1;
	bool PARAMETRO_INVALIDO;
	stringstream buffer(comando);
	if (buffer >> comando1)
	{
		PARAMETRO_INVALIDO = false;
		if (comando1 == "carregaP") {
			string nome;
			if (buffer >> nome) 
				carregaP(nome);
			else 
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregaC") {
			string nome;
			if (buffer >> nome) 
				carregaC(nome);
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregaA") {
			string nome;
			if (buffer >> nome) 
				carregaA(nome);
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregatudo") {
			string nomeP, nomeC, nomeA;
			if (buffer >> nomeP && buffer >> nomeC && buffer >> nomeA) {
				carregaP(nomeP);
				carregaC(nomeC);
				carregaA(nomeA);
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "cria") {
			string tipo;
			if (buffer >> tipo) {
				if (tipo == "p") {
					string tipoP, nomeP;
					if (buffer >> tipoP && buffer >> nomeP) {
						Consola::gotoxy(76, 1);
						cout << "Criado piloto " << nomeP;
						controlo.novoPiloto(nomeP, tipoP);
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "c") {
					int capI, capM, vel;
					string marcaC, modeloC;
					if (buffer >> vel && buffer >> capI && buffer >> capM && buffer >> marcaC) {
						Consola::gotoxy(76, 1);
						cout << "Criado carro";
						if (buffer >> modeloC)
							controlo.novoCarro(marcaC, capI, capM, vel, modeloC);
						else
							controlo.novoCarro(marcaC, capI, capM, vel);
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "a") {
					int n;
					double comp;
					string nomeA;
					if (buffer >> n && buffer >> comp && buffer >> nomeA) {
						acrescentaAutodromo(n, comp, nomeA);
						Consola::gotoxy(76, 1);
						cout << "Criado autodromo " << autodromos[(int)autodromos.size()-1]->getNome();
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "apaga") {
			string tipo;
			if (buffer >> tipo) {
				if (tipo == "p") {
					string nomeP;
					if (buffer >> nomeP) {
						Consola::gotoxy(76, 1);
						cout << "Eliminado piloto " << nomeP;
						if(controlo.procuraPiloto(nomeP)->getCarro()!=nullptr)
							controlo.procuraPiloto(nomeP)->saiCarro();
						controlo.removePiloto(controlo.procuraPiloto(nomeP));
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "c") {
					char id;
					if (buffer >> id) {
						Consola::gotoxy(76, 1);
						cout << "Eliminado carro " << id;
						for (auto ptr = controlo.getPiloto().begin(); ptr != controlo.getPiloto().end(); ptr++)
							if ((*ptr)->getCarro()!=nullptr && (*ptr)->getCarro()->getID() == id)
								(*ptr)->saiCarro();
						controlo.removeCarro(controlo.procuraCarro(id));
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "a") {
					string nomeA;
					if (buffer >> nomeA) {
						for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ptr++)
							if ((*ptr)->getNome() == nomeA) {
								Consola::gotoxy(76, 1);
								cout << "Eliminado autodromo " << nomeA;
								ptr = autodromos.erase(ptr);
							}
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "entranocarro") {
			char letra;
			string	nomeP;
			if (buffer >> letra && buffer >> nomeP) {
				if (controlo.procuraPiloto(nomeP)->getCarro() == nullptr && controlo.procuraCarro(letra)->getCondutor() == false) {
					Consola::gotoxy(76, 1);
					cout << "Piloto " << nomeP << " entrou no carro " << letra;
					controlo.procuraPiloto(nomeP)->entraCarro(controlo.procuraCarro(letra));
					auxiliarCorrida.push_back(new Corrida(controlo.procuraCarro(letra), controlo.procuraPiloto(nomeP)));
				}
			}
		}
		else if (comando1 == "saidocarro") {
			char letra;
			if (buffer >> letra) {
				if (controlo.procuraCarro(letra)->getCondutor()) {
					Consola::gotoxy(76, 1);
					cout << "Piloto " << controlo.pilotoNoCarro(letra)->getNome() << " saiu do carro " << letra;
					controlo.pilotoNoCarro(letra)->saiCarro();
				}
			}
		}
		else if (comando1 == "lista") {
			int i=controlo.getAsString();
			for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ptr++) {
				Consola::gotoxy(76, i);
				cout << (*ptr)->getAsString();
				i++;
			}
		}
		else if (comando1 == "savedgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1 << " " << nome;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "loaddgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1 << " " << nome;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "deldgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1 << " " << nome;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "sair") {
			Consola::clrscr();
			return 0;
		}
		else if (comando1 == "campeonato") {
			string nome;
			if (buffer >> nome) {
				for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ptr++) {
					if ((*ptr)->getNome() == nome && (int)auxiliarCorrida.size()>=2) {
						int i, j, num;
						bool NOVO;
						for (i = 0; i < (*ptr)->getPista()->getNMax() && i < (int)auxiliarCorrida.size(); i++) {
							do {
								num = rand() % auxiliarCorrida.size();
								NOVO = true;
								for (j = 0; j < (int)(*ptr)->getPista()->getCorridas().size(); j++)
									if ((*ptr)->getPista()->getCorridaN(j)->getCarro()->getID() == auxiliarCorrida[num]->getCarro()->getID())
										NOVO = false;
							} while (!NOVO);
							(*ptr)->getPista()->adicionaCorrida(auxiliarCorrida[num]);
						}
						modo2(*ptr);
						break;
					}
				}
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "aleatorio") {
			int num;
			if (buffer >> num && num > 0) {
				associaCarros(num);
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1 << "!";
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else {
			Consola::gotoxy(76, 1);
			cout << "Comando errado!";
		}
		if (PARAMETRO_INVALIDO) {
			Consola::gotoxy(76, 1);
			cout << "Parametro invalido!";
		}
	}
	return 1;
}

void Menus::movimentoCarros(Autodromo* autodromo, int seg)
{
	for (int i = 0; i < seg && autodromo->getPista()->getComecou() == JA_COMECOU; i++) {
		autodromo->getPista()->avancaTempo();
		autodromo->getPista()->carregaGrelha();
		autodromo->getPista()->mostraGrelha();
		Sleep(10);
	}
	if (autodromo->getPista()->getComecou() == JA_TERMINOU) {
		autodromo->obterInfo();
	}
}

void Menus::associaCarros(int num)
{
	bool existeC, existeP;
	int max = num;

	if (num > controlo.getNCarrosDisponiveis() || num > controlo.getNPilotosDisponiveis()) {
		if (controlo.getNCarrosDisponiveis() > controlo.getNPilotosDisponiveis())
			max = controlo.getNPilotosDisponiveis();
		else
			max = controlo.getNCarrosDisponiveis();
	}
	int ncar = controlo.getNCarros();
	int npil = controlo.getNPilotos();
	for (int i = 0; i < max; ) {
		existeC = false;
		existeP = false;
		int num1 = rand() % ncar;
		for (int j = 0; j < (int)auxiliarCorrida.size(); j++) {
			if (controlo.procuraCarroN(num1) == auxiliarCorrida[j]->getCarro())
				existeC = true;
		}
		int num2 = rand() % npil;
		for (int j = 0; j < (int)auxiliarCorrida.size(); j++){
			if (controlo.procuraPilotoN(num2) == auxiliarCorrida[j]->getParticipante())
				existeP = true;
		}
		
		if (existeP == false && existeC == false) {
			controlo.procuraPilotoN(num2)->entraCarro(controlo.procuraCarroN(num1));
			auxiliarCorrida.push_back(new Corrida(controlo.procuraCarroN(num1), controlo.procuraPilotoN(num2)));
			i++;
		}
	}
}

Menus::~Menus()
{
	for (auto p : autodromos)
		delete p;
	for (auto p : auxiliarCorrida)
		delete p;
}
