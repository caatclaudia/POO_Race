// TP_POO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Piloto.h"
#include "Carro.h"
#include "Autodromo.h"
#include "Corrida.h"
#include "Garagem.h"
#include "Pista.h"
#include "DVG.h"
#include <string>
#include <sstream>
#include <fstream>
char Carro::identificacao = 'a';
int DVG::Nome = 1;

void carregaP(DVG &controlo, string nome) {
	ifstream ficheiro(nome);
	if (ficheiro) {
		string tipo, nome, linha;
		while(getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> tipo && buffer >> nome)
				controlo.novoPiloto(nome,tipo);
		}
	}
}

void carregaC(DVG& controlo, string nome) {
	ifstream ficheiro(nome);
	if (ficheiro) {
		int capI, capM;
		string marca, modelo, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> capI && buffer >> capM && buffer >> marca && buffer >> modelo)
				controlo.novoCarro(marca, capI, capM, 200, modelo);			//VelocidadeMaxima
		}
	}
}

void carregaA(vector<Autodromo *> & autodromos, string nome) {
	ifstream ficheiro(nome);
	if (ficheiro) {
		int n;
		double comp;
		string nome, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> n && buffer >> comp && buffer >> nome)
				autodromos.push_back(new Autodromo(n, comp, nome));
		}
	}
}
int modo2(DVG& controlo, Autodromo *autodromos) {
	string comando, comando1;
	stringstream buffer(comando);
	if (buffer >> comando1)
	{
		if (comando1 == "campeonato") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
				//CONTINUAR
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "listacarros") {
			cout << "Comando " << comando1 << endl;

		}
		else if (comando1 == "carregabat") {
			char letra;
			double num;
			if (buffer >> letra && buffer >> num) {
				cout << "Comando " << comando1 << " " << letra << " " << num << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "carregatudo") {
			cout << "Comando " << comando1 << endl;

		}
		else if (comando1 == "corrida") {
			cout << "Comando " << comando1 << endl;

		}
		else if (comando1 == "acidente") {
			char letra;
			if (buffer >> letra) {
				cout << "Comando " << comando1 << " " << letra << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "stop") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "destroi") {
			char letra;
			if (buffer >> letra) {
				cout << "Comando " << comando1 << " " << letra << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "passatempo") {
			int n;
			if (buffer >> n) {
				cout << "Comando " << comando1 << " " << n << endl;
				autodromos->getPista()->avancaTempo(n);
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "log") {
			cout << "Comando " << comando1 << endl;

		}
		else
			cout << "Comando errado!" << endl;
	}
	return 1;
}

int modo1(DVG& controlo, vector<Autodromo*>& autodromos, string comando) {
	string comando1;
	stringstream buffer(comando);
	if (buffer >> comando1)
	{
		if (comando1 == "carregaP") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
				carregaP(controlo, nome);
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "carregaC") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
				carregaC(controlo, nome);
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "carregaA") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
				carregaA(autodromos, nome);
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "cria") {
			string tipo;
			if (buffer >> tipo) {
				cout << "Comando " << comando1 << " " << tipo << endl;
				if (tipo == "p") {
					string tipoP, nomeP;
					if (buffer >> tipoP && buffer >> nomeP)
						controlo.novoPiloto(nomeP, tipoP);
				}
				else if (tipo == "c") {
					int capI, capM;
					string marcaC, modeloC;
					if (buffer >> capI && buffer >> capM && buffer >> marcaC && buffer >> modeloC)
						controlo.novoCarro(marcaC, capI, capM, 200, modeloC);
				}
				else if (tipo == "a") {
					int n;
					double comp;
					string nomeA;
					if (buffer >> n && buffer >> comp && buffer >> nomeA)
						autodromos.push_back(new Autodromo(n, comp, nomeA));
				}
				else
					cout << "Parametro invalido!" << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "apaga") {
			string tipo;
			if (buffer >> tipo) {
				cout << "Comando " << comando1 << " " << tipo << endl;
				if (tipo == "p") {
					string tipoP, nomeP;
					if (buffer >> tipoP && buffer >> nomeP)
						controlo.removePiloto(controlo.procuraPiloto(nomeP));
				}
				else if (tipo == "c") {
					char id;
					if (buffer >> id)
						controlo.removeCarro(controlo.procuraCarro(id));
				}
				else if (tipo == "a") {
					string nomeA;
					if (buffer >> nomeA) {
						for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ++ptr) {
							if ((*ptr)->getNome() == nomeA)
								*autodromos.erase(ptr);
						}
					}
				}
				else
					cout << "Parametro invalido!" << endl;
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "entranocarro") {
			char letra;
			string	nomeP;
			if (buffer >> letra && buffer >> nomeP) {
				cout << "Comando " << comando1 << " " << letra << " " << nomeP << endl;
				controlo.procuraPiloto(nomeP)->entraCarro(controlo.procuraCarro(letra));
			}
		}
		else if (comando1 == "saidocarro") {
			char letra;
			if (buffer >> letra) {
				cout << "Comando " << comando1 << " " << letra << endl;
				if (controlo.pilotoNoCarro(letra) != nullptr)
					controlo.pilotoNoCarro(letra)->saiCarro();
			}
		}
		else if (comando1 == "lista") {
			cout << "Comando " << comando1 << endl;
			cout << controlo.getAsString() << endl;
			for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ptr++)
				cout << (*ptr)->getAsString() << endl;
		}
		else if (comando1 == "savedgv") {
			string nome;
			if (buffer >> nome)
				cout << "Comando " << comando1 << " " << nome << endl;
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "loaddgv") {
			string nome;
			if (buffer >> nome)
				cout << "Comando " << comando1 << " " << nome << endl;
			else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "deldgv") {
			string nome;
			if (buffer >> nome)
				cout << "Comando " << comando1 << " " << nome << endl;
				else
				cout << "Parametro invalido!" << endl;
		}
		else if (comando1 == "sair") {
			return 0;
		}
		else if (comando1 == "campeonato") {
			string nome;
			if (buffer >> nome) {
				cout << "Comando " << comando1 << " " << nome << endl;
				modo2(controlo, autodromos[0]);
			}
			else
				cout << "Parametro invalido!" << endl;
		}
		else
			cout << "Comando errado!" << endl;
	}
	return 1;
}

int main()
{
	string comando;
	DVG controlo;
	vector<Autodromo*> autodromos;

	do {
		fflush(stdout);
		cout << "introduza um comando: ";
		getline(cin, comando);
	} while (modo1(controlo,autodromos,comando));
	
	return EXIT_SUCCESS;
}

