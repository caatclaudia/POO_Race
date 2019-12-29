#include "Menus.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Pista.h"
#include "Piloto.h"
#include "Corrida.h"
#include "Garagem.h"

using namespace std;

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Consola.h"
#include <time.h>

Menus::Menus()
{
}

void Menus::base()const 
{
	Consola::setTextColor(Consola::VERMELHO);
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
	Consola::setTextColor(Consola::BRANCO);
}

void Menus::limpaPista() const 
{
	for (int i = 1; i < 74; i++) {
		for (int j = 1; j < 19; j++) {
			Consola::gotoxy(i, j);
			cout << " ";
		}
	}
}

void Menus::carregaP(DVG& controlo, string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		string tipo, linha;
		while (getline(ficheiro, linha)) {
			string nome;
			istringstream buffer(linha);
			if (buffer >> tipo) {
				if (getline(buffer, nome)) {
					nome=nome.substr(1);
					controlo.novoPiloto(nome, tipo);
				}
			}
		}
		Consola::gotoxy(76, 1);
		cout << "Carregado com sucesso!";
	}
}

void Menus::carregaC(DVG& controlo, string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		float capI, capM;
		int vel;
		string marca, modelo, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> vel && buffer >> capI && buffer >> capM && buffer >> marca && capI <= capM) {
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

void Menus::carregaA(Simulacao *simulacao, string nome)
{
	ifstream ficheiro(nome);
	if (ficheiro) {
		int n;
		double comp;
		string nome, linha;
		while (getline(ficheiro, linha)) {
			istringstream buffer(linha);
			if (buffer >> n && buffer >> comp && buffer >> nome)
				simulacao->addAutodromos(n, comp, nome);
		}
		Consola::gotoxy(76, 1);
		cout << "Carregado com sucesso!";
	}
}

void Menus::addMensagem(vector<string>* listaMensagens, string s)
{
	listaMensagens->insert(listaMensagens->begin(), s);
	if ((int)listaMensagens->size() > 17)
		listaMensagens->pop_back();
}

void Menus::addMensagemAcidente(vector<string>* listaMensagens, Corrida* c)
{
	bool ACIDENTE = false;
	ostringstream os;

	if (c->getCarro()->getAcidente() != CARRO_BOMESTADO) {
		os << "Acidente do piloto " << c->getParticipante()->getNome() << " (" << c->getCarro()->getID() << ")" << endl;
		addMensagem(listaMensagens, os.str());
		os.str("");
		ACIDENTE = true;
	}

	if (c->getCarro()->getEmergencia() == EMERGENCIA_ON) {
		os << "Piloto " << c->getParticipante()->getNome() << " (" << c->getCarro()->getID() << ") - emergencia ativa" << endl;
		addMensagem(listaMensagens, os.str());
		os.str("");
		ACIDENTE = true;
	}
	// FAZER a prob do piloto surpresa
	if (!ACIDENTE)
	{
		os << "Ronda sem acontecimentos!" << endl;
		addMensagem(listaMensagens, os.str());
		os.str("");
	}
}

void Menus::getAsStringPontCompeticao(DVG *controlo)
{
	int i = 1, max, indiceMax, l, total = 0;
	vector<int> indiceUsado;
	for (int j = 0; j != controlo->getNPilotos(); j++)
		if (controlo->procuraPilotoN(j)->getCompeticao())
			total++;

	for (int j = 0; (int)indiceUsado.size() != total; ) {
		max = 0;
		for (l = 0; l < controlo->getNPilotos(); l++) {
			bool EXISTE = false;
			if (controlo->procuraPilotoN(l)->getCompeticao() == true && controlo->procuraPilotoN(l)->getPontuacao() >= max) {
				for (int k = 0; k < (int)indiceUsado.size(); k++) {
					if (l == indiceUsado[k])
						EXISTE = true;
				}
				if (!EXISTE) {
					indiceMax = l;
					max = controlo->procuraPilotoN(l)->getPontuacao();
				}
			}
		}
		indiceUsado.push_back(indiceMax);

		Consola::gotoxy(76, i++);
		cout << (int)indiceUsado.size() << ": Piloto " << controlo->procuraPilotoN(indiceMax)->getNome() << " com " << controlo->procuraPilotoN(indiceMax)->getPontuacao() << " pontos!";
	}
}

void Menus::listaCarrosPista(Pista* pista)
{
	int x = 1;
	for (int i = 0; i < (int)pista->getCorridas().size(); i++) {
		Consola::gotoxy(76, x++);
		cout << pista->getCorridaN(i)->getParticipante()->getAsString();
	}
}

void Menus::getAsStringPontPilotos(DVG* controlo)
{
	int i = 1, max, indiceMax, l;
	vector<int> indiceUsado;

	for (int j = 0; (int)indiceUsado.size() != controlo->getNPilotos(); ) {
		max = 0;
		for (l = 0; l < controlo->getNPilotos(); l++) {
			bool EXISTE = false;
			if (controlo->procuraPilotoN(l)->getPontuacao() >= max) {
				for (int k = 0; k < (int)indiceUsado.size(); k++) {
					if (l == indiceUsado[k])
						EXISTE = true;
				}
				if (!EXISTE) {
					indiceMax = l;
					max = controlo->procuraPilotoN(l)->getPontuacao();
				}
			}
		}
		indiceUsado.push_back(indiceMax);

		Consola::gotoxy(76, i++);
		cout << (int)indiceUsado.size() << ": Piloto " << controlo->procuraPilotoN(indiceMax)->getNome() << " com " << controlo->procuraPilotoN(indiceMax)->getPontuacao() << " pontos!";
	}
}

void Menus::obterInfo(Autodromo *autodromo) 
{
	int i = 1;
	Consola::gotoxy(76, i);
	cout << "Corrida em " << autodromo->getNome() << " (" << autodromo->getPista()->getComprimento() << "m): ";
	if (autodromo->getPista()->getComecou() == NAO_COMECOU) {
		Consola::gotoxy(76, i++);
		cout << "Corrida nao iniciada";
	}
	else {
		for (int n = 1; n <= autodromo->getPista()->nParticipantes(); n++) {
			for (auto ptr = autodromo->getPista()->getCorridas().begin(); ptr != autodromo->getPista()->getCorridas().end(); ptr++) {
				if ((*ptr)->getLugar() == n) {
					Consola::gotoxy(76, i++);
					cout << n << ". " << (*ptr)->getCarro()->getID() << " " << (*ptr)->getCarro()->getMarca() << " / " << (*ptr)->getParticipante()->getNome()
						<< " (" << (*ptr)->getParticipante()->getTipo() << ")";
					Consola::gotoxy(77, i++);
					cout << (*ptr)->getCarro()->getEnergia() << "mAh, " << (*ptr)->getCarro()->getCapacidadeMaxima()
						<< "mAh - " << (*ptr)->getPosicao() + 1 << "m - " << (*ptr)->getCarro()->getVelocidade() << "m/s" << endl;
				}
			}
		}
	}
}

void Menus::getAsStringPontPilotosPista(Autodromo *autodromo)
{
	int i = 1, max, indiceMax, l;
	vector<int> indiceUsado;

	for (int j = 0; (int)indiceUsado.size() != (int)autodromo->getPista()->getCorridas().size(); ) {
		max = 0;
		for (l = 0; l < (int)autodromo->getPista()->getCorridas().size(); l++) {
			bool EXISTE = false;
			if (autodromo->getPista()->getCorridaN(l)->getParticipante()->getPontuacao() >= max) {
				for (int k = 0; k < (int)indiceUsado.size(); k++) {
					if (l == indiceUsado[k])
						EXISTE = true;
				}
				if (!EXISTE) {
					indiceMax = l;
					max = autodromo->getPista()->getCorridaN(l)->getParticipante()->getPontuacao();
				}
			}
		}
		indiceUsado.push_back(indiceMax);

		Consola::gotoxy(76, i++);
		cout << (int)indiceUsado.size() << ": Piloto " << (autodromo->getPista()->getCorridaN(indiceMax)->getParticipante()->getNome()) 
			<< " com " << (autodromo->getPista()->getCorridaN(indiceMax)->getParticipante()->getPontuacao()) << " pontos!";
	}
}

void Menus::mostraGaragem(Autodromo* autodromo, DVG* controlo) const
{
	if ((int)autodromo->getGaragem()->getCarros().size() > 0) {
		Consola::gotoxy(2, 17);
		cout << "Garagem: ";
		Consola::gotoxy(2, 18);
		for (auto ptr = autodromo->getGaragem()->getCarros().begin(); ptr != autodromo->getGaragem()->getCarros().end(); ptr++)
		{
			Consola::setTextColor(controlo->procuraCarro((*ptr)->getID())->getCor());
			cout << (*ptr)->getID() << "    ";
			Consola::setTextColor(Consola::BRANCO);
		}
	}
}

void Menus::mostraGrelha(Autodromo* autodromo, DVG *controlo)
{
	int inicio;
	if (autodromo->getPista()->getCorridas().size() > 0)
		inicio = 16 / ((int)autodromo->getPista()->getCorridas().size() * 2);
	else
		inicio = 16;
	for (int i = 0; i < (int)autodromo->getPista()->getCorridas().size() * 2; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			Consola::gotoxy(2 + j, inicio + i);
			if (autodromo->getPista()->getGrelha()[i][j] != ' ' && autodromo->getPista()->getGrelha()[i][j] != '-') {
				Consola::setTextColor(controlo->procuraCarro(tolower(autodromo->getPista()->getGrelha()[i][j]))->getCor());
				cout << autodromo->getPista()->getGrelha()[i][j];
				Consola::setTextColor(Consola::BRANCO);
			}else
				cout << autodromo->getPista()->getGrelha()[i][j];
		}
	}
}

int Menus::modo2(vector<Autodromo*> campeonato, DVG *controlo)
{
	vector<string> listaMensagens;

	string comando, comando1;
	bool PARAMETRO_INVALIDO;
	int indice = 0;
	campeonato[indice]->getPista()->setComecou(NAO_COMECOU);
	Consola::gotoxy(76, 1);
	cout << "Autodromo " << campeonato[indice]->getNome();
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
				listaCarrosPista(campeonato[indice]->getPista());
			}
			else if (comando1 == "carregabat") {
				char letra;
				float num;
				if (buffer >> letra && buffer >> num && num > 0) {
					Consola::gotoxy(76, 1);
					cout << "Comando " << comando1 << " " << letra << " " << num;
					campeonato[indice]->carregaEnergia(letra, num);
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "carregatudo") {
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1;
				campeonato[indice]->carregaEnergiaM();
			}
			else if (comando1 == "corrida") {
				listaMensagens.clear();
				Consola::gotoxy(76, 1);
				if (indice < (int)campeonato.size() - 1) {
					indice++;
					if (campeonato[indice]->paresPista() >= 2) {
						cout << "Autodromo " << campeonato[indice]->getNome();
						campeonato[indice]->getPista()->setComecou(NAO_COMECOU);
					}
					else
						cout << "Autodromo " << campeonato[indice]->getNome() << " nao tem participantes!";
				}
				else
					cout << "Campeonato terminou!";
			}
			else if (comando1 == "acidente") {
				char letra;
				if (buffer >> letra) {
					Consola::gotoxy(76, 1);
					for (int i = 0; i < (int)campeonato[indice]->getPista()->getCorridas().size(); i++)
						if (campeonato[indice]->getPista()->getCorridaN(i)->getCarro()->getID() == letra) {
							cout << "Carro " << letra << " teve acidente!";
							campeonato[indice]->getPista()->getCorridaN(i)->getCarro()->acidenteDanoIrreparavel(campeonato[indice]->getPista()->getCorridaN(i)->getParticipante());
							campeonato[indice]->getPista()->removerCarro(letra);
							controlo->removeCarro(controlo->procuraCarro(letra));
							limpaPista();
							if (campeonato[indice]->paresPista() < 2)
								campeonato[indice]->terminarCorrida();
						}
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "stop") {
				string nome;
				if (getline(buffer, nome)) {
					nome = nome.substr(1);
					Consola::gotoxy(76, 1);
					cout << "Stop " << nome << "!";
					for (int i = 0; i < (int)campeonato[indice]->getPista()->getCorridas().size(); i++)
						if (campeonato[indice]->getPista()->getCorridaN(i)->getParticipante()->getNome() == nome)
							campeonato[indice]->getPista()->getCorridaN(i)->setTravar(true);
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "destroi") {
				char letra;
				if (buffer >> letra) {
					Consola::gotoxy(76, 1);
					cout << "Destruido carro " << letra << "!";
					campeonato[indice]->getPista()->removerCarro(letra);
					controlo->removeCarro(controlo->procuraCarro(letra));
					limpaPista();
					if (campeonato[indice]->paresPista() < 2)
						campeonato[indice]->terminarCorrida();
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "passatempo") {
				limpaPista();
				int n;
				if (buffer >> n && n > 0) {
					if (campeonato[indice]->getPista()->getComecou() == JA_TERMINOU) {
						Consola::gotoxy(76, 1);
						cout << "Corrida ja terminada!";
					}
					if (campeonato[indice]->getPista()->getComecou() == NAO_COMECOU && campeonato[indice]->paresPista() >= 2) {
						int res=campeonato[indice]->comecarCorrida();
						if (res == 0) {
							Consola::gotoxy(76, 2);
							cout << "Existem carros vazios!" << endl;
						}
						else if(res==-1){
							Consola::gotoxy(76, 2);
							cout << "Nao tem carros suficientes!" << endl;
						}
					}
					if (campeonato[indice]->getPista()->getComecou() == JA_COMECOU) {
						movimentoCarros(campeonato[indice], n, &listaMensagens,controlo);
					}
					Consola::gotoxy(2, 21);
					cout << "Passou " << n << " segundos!";
				}
				else
					PARAMETRO_INVALIDO = true;
			}
			else if (comando1 == "log") {
				int pos = 2;
				if (listaMensagens.size() > 0) {
					for (int i = 0; i < (int)listaMensagens.size(); i++) {
						Consola::gotoxy(76, pos++);
						cout << listaMensagens[i] << endl;
					}
				}
				else {
					Consola::gotoxy(76, pos);
					cout << "Campeonato sem acontecimentos!";
				}
			}
			else if (comando1 == "pontuacao") {
				getAsStringPontCompeticao(controlo);
			}
			else if(comando1=="obterinfo")
				obterInfo(campeonato[indice]);
			else if (comando1 == "voltar") {
				Consola::gotoxy(76, 1);
				cout << "Voltando...";
				limpaPista();
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

	for (int i = 0; i <= indice; i++)
		campeonato[i]->limpaGaragem();

	return 1;
}


int Menus::modo1(Simulacao* simulacao, string comando)
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
				carregaP(simulacao->getControlo(), nome);
			else 
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregaC") {
			string nome;
			if (buffer >> nome) 
				carregaC(simulacao->getControlo(), nome);
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregaA") {
			string nome;
			if (buffer >> nome) 
				carregaA(simulacao, nome);
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "carregatudo") {
			string nomeP, nomeC, nomeA;
			if (buffer >> nomeP && buffer >> nomeC && buffer >> nomeA) {
				carregaP(simulacao->getControlo(), nomeP);
				carregaC(simulacao->getControlo(), nomeC);
				carregaA(simulacao, nomeA);
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "cria") {
			string tipo;
			if (buffer >> tipo) {
				if (tipo == "p") {
					string tipoP, nomeP;
					if (buffer >> tipoP) {
						if (getline(buffer, nomeP)) {
							nomeP = nomeP.substr(1);
							Consola::gotoxy(76, 1);
							cout << "Criado piloto " << nomeP;
							simulacao->getControlo().novoPiloto(nomeP, tipoP);
						}
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "c") {
					float capI, capM;
					int vel;
					string marcaC, modeloC;
					if (buffer >> vel && buffer >> capI && buffer >> capM && buffer >> marcaC && capI <= capM) {
						Consola::gotoxy(76, 1);
						cout << "Criado carro";
						if (buffer >> modeloC)
							simulacao->getControlo().novoCarro(marcaC, capI, capM, vel, modeloC);
						else
							simulacao->getControlo().novoCarro(marcaC, capI, capM, vel);
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "a") {
					int n;
					double comp;
					string nomeA;
					if (buffer >> n && buffer >> comp && buffer >> nomeA) {
						simulacao->addAutodromos(n, comp, nomeA);
						Consola::gotoxy(76, 1);
						cout << "Criado autodromo " << simulacao->getAutodromoN(simulacao->getAutodromosSize()-1)->getNome();
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
					if (getline(buffer, nomeP)) {
						nomeP = nomeP.substr(1);
						if (simulacao->getControlo().procuraPiloto(nomeP) == nullptr)
							PARAMETRO_INVALIDO = true;
						else {
							Consola::gotoxy(76, 1);
							cout << "Eliminado piloto " << nomeP;
							if (simulacao->getControlo().procuraPiloto(nomeP)->getCarro() != nullptr)
								simulacao->getControlo().procuraPiloto(nomeP)->saiCarro();
							simulacao->getControlo().removePiloto(simulacao->getControlo().procuraPiloto(nomeP));
						}
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "c") {
					char id;
					if (buffer >> id) {
						if (simulacao->getControlo().procuraCarro(id) == nullptr)
							PARAMETRO_INVALIDO = true;
						else {
							Consola::gotoxy(76, 1);
							cout << "Eliminado carro " << id;
							for (auto ptr = simulacao->getControlo().getPiloto().begin(); ptr != simulacao->getControlo().getPiloto().end(); ptr++)
								if ((*ptr)->getCarro() != nullptr && (*ptr)->getCarro()->getID() == id)
									(*ptr)->saiCarro();
							simulacao->getControlo().removeCarro(simulacao->getControlo().procuraCarro(id));
						}
					}
					else
						PARAMETRO_INVALIDO = true;
				}
				else if (tipo == "a") {
					string nomeA;
					if (buffer >> nomeA) {
						if (simulacao->eliminaAutodromos(nomeA)) {
							Consola::gotoxy(76, 1);
							cout << "Eliminado autodromo " << nomeA;
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
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "entranocarro") {
			char letra;
			string	nomeP;
			if (buffer >> letra) {
				if (getline(buffer, nomeP)) {
					nomeP = nomeP.substr(1);
					if (simulacao->getControlo().procuraPiloto(nomeP) == nullptr || simulacao->getControlo().procuraCarro(letra) == nullptr)
						PARAMETRO_INVALIDO = true;
					else if (!simulacao->getControlo().procuraCarro(letra)->disponivel()) {
						Consola::gotoxy(76, 1);
						cout << "Carro " << letra << " nao esta disponivel!";
					}
					else if (simulacao->getControlo().procuraPiloto(nomeP)->getCarro() == nullptr && simulacao->getControlo().procuraCarro(letra)->getCondutor() == false) {
						Consola::gotoxy(76, 1);
						cout << "Piloto " << nomeP << " entrou no carro " << letra;
						simulacao->getControlo().procuraPiloto(nomeP)->entraCarro(simulacao->getControlo().procuraCarro(letra));
						simulacao->addAuxiliarCorrida(new Corrida(simulacao->getControlo().procuraCarro(letra), simulacao->getControlo().procuraPiloto(nomeP)));
					}
				}
			}
		}
		else if (comando1 == "saidocarro") {
			char letra;
			if (buffer >> letra) {
				if (simulacao->getControlo().procuraCarro(letra) == nullptr)
					PARAMETRO_INVALIDO = true;
				else if (simulacao->getControlo().procuraCarro(letra) != nullptr && simulacao->getControlo().procuraCarro(letra)->getCondutor()) {
					Consola::gotoxy(76, 1);
					cout << "Piloto " << simulacao->getControlo().pilotoNoCarro(letra)->getNome() << " saiu do carro " << letra;
					simulacao->getControlo().pilotoNoCarro(letra)->saiCarro();
				}
			}
		}
		else if (comando1 == "lista") {
			simulacao->getAsStringPilotos();
			Consola::getch();
			base();
			fflush(stdout);
			simulacao->getAsStringCarros();
			Consola::getch();
			base();
			fflush(stdout);
			int i = 1;
			if (simulacao->getAutodromos().empty()) {
				Consola::gotoxy(76, i);
				cout << "Nao existe carros!";
			}
			else {
				for (int x = 0; x < simulacao->getAutodromosSize(); x++) {
					Consola::gotoxy(76, i);
					cout << simulacao->getAutodromoN(x)->getAsString();
					i++;
				}
			}
		}
		else if (comando1 == "savedgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				cout << "Copia de DVG para " << nome;

				DVG copia = simulacao->getControlo();

				copia.setNomeDVG(nome);
				simulacao->addDVG(copia);
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "loaddgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				if (simulacao->loaddgv(nome))
					cout << "Recupera DVG " << nome;
				else
					cout << "Nao existe DVG " << nome;
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "deldgv") {
			string nome;
			if (buffer >> nome) {
				Consola::gotoxy(76, 1);
				if(simulacao->deldgv(nome))
					cout << "Apaga DVG " << nome;
				else
					cout << "Nao existe DVG " << nome;
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
			bool CERTO = false;
			while (buffer >> nome) {
				simulacao->atualizaAuxiliarCorrida();
				if (simulacao->getAuxiliarCorridaSize() < 2) {
					Consola::gotoxy(76, 1);
					cout << "Falta participantes!";
				}
				else {
					for (int x = 0; x < simulacao->getAutodromosSize(); x++) {
						if (simulacao->getAutodromoN(x)->getNome() == nome && simulacao->getAuxiliarCorridaSize() >= 2) {
							int i, j, num;
							bool NOVO;
							CERTO = true;
							for (i = 0; i < simulacao->getAutodromoN(x)->getPista()->getNMax() && i < simulacao->getAuxiliarCorridaSize(); i++) {
								do {
									num = rand() % simulacao->getAuxiliarCorridaSize();
									NOVO = true;
									for (j = 0; j < (int)simulacao->getAutodromoN(x)->getPista()->getCorridas().size(); j++)
										if (simulacao->getAutodromoN(x)->getPista()->getCorridaN(j)->getCarro()->getID() == simulacao->getAuxiliarCorridaN(num)->getCarro()->getID())
											NOVO = false;
								} while (!NOVO);
								simulacao->getAutodromoN(x)->getPista()->adicionaCorrida(simulacao->getAuxiliarCorridaN(num));
							}
							simulacao->addCampeonato(simulacao->getAutodromoN(x));
							break;
						}
					}
				}
			}
			if (CERTO) {
				modo2(simulacao->getCampeonato(), &simulacao->getControlo());
				simulacao->getControlo().terminaCompeticao();
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "aleatorio") {
			int num;
			if (buffer >> num && num > 0) {
				associaCarros(simulacao, num);
				Consola::gotoxy(76, 1);
				cout << "Comando " << comando1 << "!";
			}
			else
				PARAMETRO_INVALIDO = true;
		}
		else if (comando1 == "pontuacao") {
			getAsStringPontPilotos(&simulacao->getControlo());
		}
		else {
			Consola::gotoxy(76, 1);
			cout << "Comando errado!";
		}
		if (PARAMETRO_INVALIDO) {
			Consola::gotoxy(76, 1);
			cout << "Parametro invalido!";
		}
		simulacao->atualizaDVG();
	}
	return 1;
}

void Menus::movimentoCarros(Autodromo* autodromo, int seg, vector<string>* listaMensagens, DVG *controlo)
{
	ostringstream os;
	for (int i = 0; i < seg && autodromo->getPista()->getComecou() == JA_COMECOU && autodromo->paresPista() >=2; i++) {
		autodromo->avancaTempo();
		mostraGrelha(autodromo,controlo);
		mostraGaragem(autodromo, controlo);
		if (i == seg - 1) {
			for (auto ptr = autodromo->getPista()->getCorridas().begin(); ptr != autodromo->getPista()->getCorridas().end(); ptr++) {
				if ((*ptr)->getCarro()->getAcidente() != CARRO_BOMESTADO || (*ptr)->getCarro()->getEmergencia() == EMERGENCIA_ON) {
					addMensagemAcidente(listaMensagens, (*ptr));
				}
			}
		}
		Sleep(10);
	}
	if (autodromo->paresPista() < 2) 
		autodromo->terminarCorrida();
	autodromo->reverCarros();
	if (autodromo->getPista()->getComecou() == JA_TERMINOU) {
		getAsStringPontPilotosPista(autodromo);
		autodromo->tudoGaragem();
		mostraGaragem(autodromo, controlo);
	}
}

void Menus::associaCarros(Simulacao* simulacao, int num)
{
	bool existeC, existeP;
	int max = num, num1, num2;
	srand((unsigned)time(NULL));

	if (num > simulacao->getControlo().getNCarrosDisponiveis() || num > simulacao->getControlo().getNPilotosDisponiveis()) {
		if (simulacao->getControlo().getNCarrosDisponiveis() >= simulacao->getControlo().getNPilotosDisponiveis())
			max = simulacao->getControlo().getNPilotosDisponiveis();
		else
			max = simulacao->getControlo().getNCarrosDisponiveis();
	}
	int ncar = simulacao->getControlo().getNCarros();
	int npil = simulacao->getControlo().getNPilotos();
	for (int i = 0; i < max; i++) {
		do {
			existeC = false;
			num1 = rand() % ncar;
			for (int j = 0; j < simulacao->getAuxiliarCorridaSize(); j++) {
				if (simulacao->getControlo().procuraCarroN(num1) == simulacao->getAuxiliarCorridaN(j)->getCarro())
					existeC = true;
			}
		} while (existeC || simulacao->getControlo().procuraCarroN(num1)->disponivel()==false || simulacao->getControlo().procuraCarroN(num1)->getCondutor()!= CARRO_SEM_CONDUTOR);
		do {
			existeP = false;
			num2 = rand() % npil;
			for (int j = 0; j < simulacao->getAuxiliarCorridaSize(); j++) {
				if (simulacao->getControlo().procuraPilotoN(num2) == simulacao->getAuxiliarCorridaN(j)->getParticipante())
					existeP = true;
			}
		} while (existeP || simulacao->getControlo().procuraPilotoN(num2)->getCarro()!=nullptr);
		
		simulacao->getControlo().procuraPilotoN(num2)->entraCarro(simulacao->getControlo().procuraCarroN(num1));
		simulacao->addAuxiliarCorrida(new Corrida(simulacao->getControlo().procuraCarroN(num1), simulacao->getControlo().procuraPilotoN(num2)));
	}
}

Menus::~Menus()
{
}
