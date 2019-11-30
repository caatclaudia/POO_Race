// TP_POO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Piloto.h"
#include "Carro.h"
#include "Autodromo.h"
#include "Corrida.h"
#include "Garagem.h"
#include "Pista.h"
#include "Menus.h"
#include "DVG.h"
#include "Consola.h"
#include "Simulacao.h"



char Carro::identificacao = 'a';
int DVG::Nome = 1;
int Menus::NomeAutodromos = 1;
int Simulacao::NomeAutodromos = 1;

void inicio() {
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	Consola::gotoxy(0,5);
	
	cout << "         (                       *" << endl;
	cout << "	 )\\ )                  (  `" << endl;
	cout << "	(()/(    )        (    )\\))(      )        (      )" << endl;
	cout << "	 /(_))( /(   (   ))\\  ((_)()\\  ( /(   (    )\\  ( /(" << endl;
	cout << "	(_))  )(_))  )\\ / ((_)(_()((_) )(_))  )\\ )((_) )(_))" << endl;
	cout << "	| _ \\((_)_  ((_)(_))  |  \\/  |((_)_  _(_ /((_)((_)_" << endl;
	cout << "	|   // _` |/ _| / -_) | |\\/| |/ _` || ' \\))| |/ _` | " << endl;
	cout << "	|_|_\\\\__,_|\\__| \\___| |_|  |_|\\__,_||_||_| |_|\\__,_|\n" << endl;

	cout << "           Pressione uma tecla para continuar..." << endl;
	Consola::getch();
	Consola::clrscr();
}

int main()
{
	string comando;
	Menus menu;
	Simulacao simulacao;
	bool FLAG_INICIO = true;

	Consola::setScreenSize(COLUNAS_BASE, LINHAS_BASE);
	inicio();

	Consola::setTextColor(Consola::BRANCO);
	do {
		if(!FLAG_INICIO)
			Consola::getch();
		menu.base();

		fflush(stdout);
		Consola::gotoxy(2,20);
		cout << "Introduza um comando: ";
		getline(cin, comando);
		FLAG_INICIO = false;
	} while (menu.modo1(&simulacao, comando));

	
	return EXIT_SUCCESS;
}

