#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

class ExceptionWrongSyntax {};
class ExceptionTableNotExisting {};
class ExceptionNoTablesFound {};
class ExceptionNoInstruction {};
class ExceptionPositionNotExisting {};				
class ExceptionInvalidCommand {};
class ExceptionProgramStopped {};
class ExceptionTableAlreadyExists {};
class ExceptionWrongParameteres {};
class NullPointerException {};


class Coloana {										/*COLOANELE*/
	string numeColoana;
	string tip;
	int dimensiune;
	string valoareImplicita;
public:
	Coloana() {
		this->numeColoana = "COL1";
		this->tip = "NUMBER";
		this->dimensiune = 7;
		this->valoareImplicita = "100";
	}
	Coloana(string parametruComanda) {
		this->valoareImplicita = parametruComanda;
	}
	Coloana(string numeColoana, string tip, int dimensiune, string valoareImplicita) {
		this->numeColoana = numeColoana;
		this->tip = tip;
		this->dimensiune = dimensiune;
		this->valoareImplicita = valoareImplicita;
	}
	Coloana(const Coloana& c) {
		this->numeColoana = c.numeColoana;
		this->tip = c.tip;
		this->dimensiune = c.dimensiune;
		this->valoareImplicita = c.valoareImplicita;
	}

	Coloana& operator=(const Coloana& c) {
		this->numeColoana = c.numeColoana;
		this->tip = c.tip;
		this->dimensiune = c.dimensiune;
		this->valoareImplicita = c.valoareImplicita;
		return *this;
	}

	string getNumeColoana() {
		return this->numeColoana;
	}

	string getTip() {
		return this->tip;
	}

	int getDimensiune() {
		return this->dimensiune;
	}

	string getValoareImplicita() {
		return this->valoareImplicita;
	}

	void setTip(string tip) {
		this->tip = tip;
	}

	void setNumeColoana(string numeColoana) {
		this->numeColoana = numeColoana;
	}

	void setDimensiune(int dimensiune) {
		this->dimensiune = dimensiune;
	}

	void setValoareImplicita(string valoareImplicita) {
		this->valoareImplicita = valoareImplicita;

	}

	friend ostream& operator<<(ostream& out, const Coloana& c);
};

ostream& operator<<(ostream& out, const Coloana& c) {
	out << c.valoareImplicita;
	return out;
}

class Linie {							/*LINIILE*/
	int nrColoane;
	Coloana* listaColoane;
public:

	Linie() {
		this->nrColoane = 0;
		this->listaColoane = NULL;
	}

	Linie(int nrColoane, Coloana* listaColoane) {
		this->nrColoane = nrColoane;
		this->listaColoane = new Coloana[this->nrColoane];
		for (int i = 0; i < this->nrColoane; i++) {
			this->listaColoane[i] = listaColoane[i];
		}
	}

	Linie(const Linie& l) {
		this->nrColoane = l.nrColoane;
		this->listaColoane = new Coloana[l.nrColoane];
		for (int i = 0; i < this->nrColoane; i++) {
			this->listaColoane = l.listaColoane;
		}
	}

	Linie& operator=(const Linie& l) {
		this->nrColoane = l.nrColoane;
		if (this->listaColoane != NULL) {
			delete[] this->listaColoane;
		}
		this->listaColoane = new Coloana[l.nrColoane];
		for (int i = 0; i < this->nrColoane; i++) {
			this->listaColoane = l.listaColoane;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Linie& l);


	void setNrCol(int newNrCol) {
		this->nrColoane = newNrCol;
	}

	int getNrCol() {
		return this->nrColoane;
	}

	void setListaColoane(Coloana* newColumns) {
		for (int i = 0; i < this->getNrCol(); i++)
		{
			this->listaColoane[i].setNumeColoana(newColumns->getNumeColoana());
			this->listaColoane[i].setTip(newColumns->getTip());
			this->listaColoane[i].setDimensiune(newColumns->getDimensiune());
			this->listaColoane[i].setValoareImplicita(newColumns->getValoareImplicita());
		}
	}

	Coloana* getListaColoane() {
		return this->listaColoane;
	}

};

ostream& operator<<(ostream& out, const Linie& l) {
	for (int i = 0; i < l.nrColoane; i++) {
		out << l.listaColoane[i].getValoareImplicita() << " ";
	}
	return out;
}

class Tabel {								/*TABELUL*/
private:
	string numeTabel;
	int nrLinii;
	Linie* linii;
	int nrColoane;
	Coloana* coloane;
public:

	Tabel() {
		this->numeTabel = "Tabel_Default";
		this->nrColoane = 0;
		this->coloane = new Coloana("COL1", "NUMBER", 10, "0");
	}
	Tabel(string numeTabel, int nrColoane, Coloana* coloane) {
		this->numeTabel = numeTabel;
		this->nrColoane = nrColoane;
		this->coloane = new Coloana[nrColoane];
		for (int i = 0; i < nrColoane; i++) {
			this->coloane[i] = Coloana(coloane[i]);
		}
		this->nrLinii = 0;

		this->linii = new Linie[nrLinii];
	}

	Tabel(string numeTabel, int nrColoane, Coloana* coloane, int nrLinii, Linie* linii) {
		this->numeTabel = numeTabel;
		this->nrColoane = nrColoane;
		this->coloane = new Coloana[nrColoane];
		for (int i = 0; i < nrColoane; i++) {
			this->coloane[i] = coloane[i];
		}
		this->nrLinii = nrLinii;
		this->linii = new Linie[this->nrLinii];
		for (int i = 0; i < this->nrLinii; i++) {
			this->linii[i] = linii[i];
		}
	}

	Tabel(const Tabel& t) {
		this->numeTabel = t.numeTabel;
		this->nrLinii = t.nrLinii;
		this->linii = new Linie[this->nrLinii];
		for (int i = 0; i < this->nrLinii; i++) {
			this->linii[i] = t.linii[i];
		}
		this->nrColoane = t.nrColoane;
		this->coloane = new Coloana[this->nrColoane];
		for (int i = 0; i < this->nrLinii; i++) {
			this->coloane[i] = t.coloane[i];
		}
	}

	void addLineToTable(Linie l) {
		this->nrLinii++;
		this->linii[nrLinii].setListaColoane(l.getListaColoane());
		this->linii[nrLinii].setNrCol(l.getNrCol());
	}

	int getNrLinii() {
		return this->nrLinii;
	}

	void setNrLinii(int nrLinii) {
		this->nrLinii = nrLinii;
	}

	Linie* getLinii() {
		return this->linii;
	}

	void setLinii(Linie* linii) {
		this->linii = linii;
	}

	int getNrColoane() {
		return this->nrColoane;
	}

	void setNrColoane(int nrColoane) {
		this->nrColoane = nrColoane;
	}

	Coloana* getColoane() {
		return this->coloane;
	}

	void setColoane(Coloana* coloane) {
		this->coloane = coloane;
	}

	string getNumeTabel() {
		return this->numeTabel;
	}

	void setNumeTabel(string numeTabel) {
		this->numeTabel = numeTabel;
	}

	/*Tabel& operator=(const Tabel& t) {				
		this->numeTabel = t.numeTabel;
		this->nrLinii = t.nrLinii;
		if (this->linii != NULL) {
			delete[] this->linii;
		}
		this->linii = new Linie[this->nrLinii];
		for (int i = 0; i < this->nrLinii; i++) {
			this->linii[i] = t.linii[i];
		}
		this->nrColoane = t.nrColoane;
		if (this->nrColoane != NULL) {
			delete[] this->coloane;
		}
		this->coloane = new Coloana[this->nrColoane];
		for (int i = 0; i < this->nrLinii; i++) {
			this->coloane[i] = t.coloane[i];
		}
		return *this;
	}*/
};


class Comanda {						
private:
	string comanda;
	string* instructiuniSintaxa;
	int nrInstructiuni;
	int nrCaractereInstructiuni;

	void transformareStringInVector() {
		int j = 0;
		string temp;
		this->instructiuniSintaxa = new string[this->nrCaractereInstructiuni / 2]; //vom avea aproximativ (nrCaractereInstructiuni / 2) instructiuni
		for (int i = 0; i < this->nrCaractereInstructiuni; i++) {
			if (this->comanda.at(i) != ' ' && this->comanda.at(i) != '(' && this->comanda.at(i) != ')' && this->comanda.at(i) != ',' && this->comanda.at(i) != ';') {
				temp.push_back(this->comanda.at(i));
			}
			else {
				if (temp != "") {
					this->instructiuniSintaxa[j] = temp;
					j++;
				}
				temp.clear();
			}
			if (this->comanda.at(i) == '(') {
				this->instructiuniSintaxa[j] = "(";
				j++;
			}
			if (this->comanda.at(i) == ')') {
				this->instructiuniSintaxa[j] = ")";
				j++;
			}
			if (this->comanda.at(i) == ',') {
				this->instructiuniSintaxa[j] = ",";
				j++;
			}
			if (i == this->nrCaractereInstructiuni - 1) {
				this->instructiuniSintaxa[j] = temp;
				j++;
			}
		}
		this->nrInstructiuni = j - 1;
	}

public:
	Comanda() {
		this->comanda = "Default_Command";
		this->instructiuniSintaxa = NULL;
		this->nrInstructiuni = 0;
		this->nrCaractereInstructiuni = 0;
	}

	Comanda(string comanda, string* instructiuniSintaxa, int nrInstructiuni, int nrCaractereInstructiuni) {
		this->comanda = comanda;
		this->nrInstructiuni = nrInstructiuni;
		this->instructiuniSintaxa = new string[this->nrInstructiuni];
		for (int i = 0; i < this->nrInstructiuni; i++) {
			this->instructiuniSintaxa[i] = instructiuniSintaxa[i];
		}
		this->nrCaractereInstructiuni = nrCaractereInstructiuni;
	}

	Comanda(const Comanda& t) {
		this->comanda = t.comanda;
		this->nrInstructiuni = t.nrInstructiuni;
		this->instructiuniSintaxa = new string[t.nrInstructiuni];
		for (int i = 0; i < t.nrInstructiuni; i++) {
			this->instructiuniSintaxa[i] = t.instructiuniSintaxa[i];
		}
		this->nrCaractereInstructiuni = t.nrCaractereInstructiuni;
	}

	Comanda& operator=(const Comanda& t) {
		this->comanda = t.comanda;
		this->nrInstructiuni = t.nrInstructiuni;
		if (this->instructiuniSintaxa != NULL) {
			delete[] this->instructiuniSintaxa;
		}
		this->instructiuniSintaxa = new string[t.nrInstructiuni];
		for (int i = 0; i < t.nrInstructiuni; i++) {
			this->instructiuniSintaxa[i] = t.instructiuniSintaxa[i];
		}
		this->nrCaractereInstructiuni = t.nrCaractereInstructiuni;
		return *this;
	}

	string getComanda() {
		return this->comanda;
	}

	string* getInstructiuniSintaxa() {
		return this->instructiuniSintaxa;
	}

	int getNrInstructiuni() {
		return this->nrInstructiuni;
	}

	void setComanda(string comanda) {
		this->comanda = comanda;
	}

	void setInstructiuniSintaxa(string* instructiuniSintaxa) {
		if (instructiuniSintaxa != NULL) {
			if (this->instructiuniSintaxa != NULL) {
				delete[] this->instructiuniSintaxa;
			}
			this->instructiuniSintaxa = new string[this->nrInstructiuni];
			for (int i = 0; i < this->nrInstructiuni; i++) {
				this->instructiuniSintaxa[i] = instructiuniSintaxa[i];
			}
		}
	}


	void citireComanda() {
		cout << "Comanda: ";
		if (this->nrInstructiuni == 0) {
			cin.get();
		}
		getline(cin, this->comanda);
		this->nrCaractereInstructiuni = this->comanda.length();
		if (this->comanda != "") {
			transform(this->comanda.begin(), this->comanda.end(), this->comanda.begin(), ::toupper);
			this->transformareStringInVector();
		}
		else {
			throw ExceptionNoInstruction();
		}
	}

	void citireComandaDinFisier(string comanda) {
		this->nrCaractereInstructiuni = comanda.length();
		if (comanda != "") {
			this->comanda = comanda;
			transform(this->comanda.begin(), this->comanda.end(), this->comanda.begin(), ::toupper);
			this->transformareStringInVector();
		}
		else {
			throw ExceptionNoInstruction();
		}
	}


};


class BazaDate {
private:
	char* numeBazaDate;
	static int nrTabele;
	Tabel* tabele;
	Comanda command;

public:
	void creareTabel(string nume, int nrColoane, string* numeColoane, string* tipuri, int* dimensiuni, string* valoriImplicite) {

		string* numeColoana = new string[nrColoane];
		string* tip = new string[nrColoane];
		int* dimensiune = new int[nrColoane];
		string* valoareImplicita = new string[nrColoane];

		numeColoana = numeColoane;
		tip = tipuri;
		dimensiune = dimensiuni;
		valoareImplicita = valoriImplicite;

		this->nrTabele++; //aici se incrementeaza numarul tabelelor


		Tabel* temp = new Tabel[this->nrTabele];
		for (int i = 0; i < this->nrTabele - 1; i++) {
			temp[i] = this->tabele[i];
		}

		//if (this->tabele != NULL) { de testat cum merge
		delete[] this->tabele;
		//}

		this->tabele = new Tabel[this->nrTabele];
		for (int i = 0; i < this->nrTabele - 1; i++) {
			this->tabele[i] = temp[i];
		}
		delete[] temp;
		Coloana* coloane = new Coloana[nrColoane];
		for (int i = 0; i < nrColoane; i++) {
			coloane[i] = Coloana(numeColoana[i], tip[i], dimensiune[i], valoareImplicita[i]);
		}

		this->tabele[this->nrTabele - 1] = Tabel(nume, nrColoane, coloane);

		delete[] coloane;
		delete[] numeColoana;
		delete[] tip;
		delete[] dimensiune;
		delete[] valoareImplicita;
	}

	void creareTabel() {
		if (this->nrTabele > 0) {
			bool existaTabelul;
			for (int i = 0; i < this->nrTabele; i++) {
				if (this->tabele[i].getNumeTabel() == command.getInstructiuniSintaxa()[2]) {
					existaTabelul = true;
					throw ExceptionTableAlreadyExists();
				}
			}
		}
		if (command.getInstructiuniSintaxa()[0] == "CREATE" && command.getInstructiuniSintaxa()[1] == "TABLE" && command.getInstructiuniSintaxa()[3] == "(" && command.getInstructiuniSintaxa()[command.getNrInstructiuni() - 1] == ")") {
			string* numeColoana = new string[command.getNrInstructiuni() / 12 + 1];
			string* tip = new string[command.getNrInstructiuni() / 12 + 1];
			int* dimensiune = new int[command.getNrInstructiuni() / 12 + 1];
			string* valoareImplicita = new string[command.getNrInstructiuni() / 12 + 1];
			int nrColoane = 0;
			if (command.getNrInstructiuni() > 12) {
				for (int i = 5; i < command.getNrInstructiuni(); i = i + 10) {
					numeColoana[nrColoane] = command.getInstructiuniSintaxa()[i];
					tip[nrColoane] = command.getInstructiuniSintaxa()[i + 2];
					dimensiune[nrColoane] = stoi(command.getInstructiuniSintaxa()[i + 4]);
					valoareImplicita[nrColoane] = command.getInstructiuniSintaxa()[i + 6];
					nrColoane++;
				}
			}
			else {
				numeColoana[nrColoane] = command.getInstructiuniSintaxa()[4];
				tip[nrColoane] = command.getInstructiuniSintaxa()[6];
				dimensiune[nrColoane] = stoi(command.getInstructiuniSintaxa()[8]);
				valoareImplicita[nrColoane] = command.getInstructiuniSintaxa()[10];
				nrColoane++;
			}
			this->nrTabele++; //aici se incrementeaza numarul tabelelor

			Tabel* temp = new Tabel[this->nrTabele];
			for (int i = 0; i < this->nrTabele - 1; i++) {
				temp[i] = this->tabele[i];
			}

			if (this->tabele != NULL) {
				delete[] this->tabele;
			}

			this->tabele = new Tabel[this->nrTabele];
			for (int i = 0; i < this->nrTabele - 1; i++) {
				this->tabele[i] = temp[i];
			}
			delete[] temp;
			Coloana* coloane = new Coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++) {
				coloane[i] = Coloana(numeColoana[i], tip[i], dimensiune[i], valoareImplicita[i]);
			}

			this->tabele[this->nrTabele - 1] = Tabel(command.getInstructiuniSintaxa()[2], nrColoane, coloane);

			delete[] coloane;
			delete[] numeColoana;
			delete[] tip;
			delete[] dimensiune;
			delete[] valoareImplicita;
			cout << "Table/Tables created." << endl;
		}
		else {
			throw ExceptionWrongSyntax();
		}
	}

	//aici am adaugat append-urile pentru ca sa poata si returna structura tabelului
	//astfel poate fi folosita la operatiile de scriere in fisier

	string afisareStructuraTabele() {
		string cod = "";
		if (this->nrTabele > 0) {
			for (int i = 0; i < this->nrTabele; i++) {
				cod.append(this->tabele[i].getNumeTabel());
				cod.append("\n");
				cout << this->tabele[i].getNumeTabel() << endl;
				for (int j = 0; j < this->tabele[i].getNrColoane(); j++) {
					cod.append(this->tabele[i].getColoane()[j].getNumeColoana());
					cod.append(" ");
					cod.append(tabele[i].getColoane()[j].getTip());
					cod.append(" ");
					cod.append(to_string(tabele[i].getColoane()[j].getDimensiune()));
					cod.append(" ");
					cod.append(tabele[i].getColoane()[j].getValoareImplicita());
					cod.append(" \n");
					cout << this->tabele[i].getColoane()[j].getNumeColoana() << " " << tabele[i].getColoane()[j].getTip() << " " << tabele[i].getColoane()[j].getDimensiune() << " " << tabele[i].getColoane()[j].getValoareImplicita() << endl;
				}
			}
		}
		else {
			throw ExceptionNoTablesFound();
		}
		return cod;
	}

	void afisareStructuraTabel(string numeTabel) {
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == numeTabel) {
				cout << this->tabele[i].getNumeTabel() << endl;
				for (int j = 0; j < this->tabele[i].getNrColoane(); j++)
				{
					//cout << this->tabele[i].getColoane()[j].getNumeColoana() << " " << this->tabele[i].getColoane()[j].getTip() << " " << this->tabele[i].getColoane()[j].getDimensiune() << " " << this->tabele[i].getColoane()[j].getValoareImplicita() << endl;
					cout << this->tabele[i].getColoane()[j].getNumeColoana() << "    ";
				}

				cout << endl;
				verificare = true;
			}
		}
		if (!verificare) {
			throw ExceptionTableNotExisting();
		}
	}

private:
	void afisareTabel_OLD(string numeTabel) { 
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == numeTabel) {
				cout << this->tabele[i].getColoane() << endl;
				for (int j = 0; j < this->tabele[i].getNrColoane(); j++) {
					cout << this->tabele[i].getColoane()[j].getValoareImplicita() << endl;
				}
				verificare = true;
				break;

			}
		}
		if (!verificare) {
			throw ExceptionTableNotExisting();
		}
	}

public:
	void afisareTabel(string numeTabel) { 
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == numeTabel) {
				//cout << this->tabele[i].getColoane() << endl;

				/*for (int j = 0; j < this->tabele[i].getNrColoane(); j++) {
					cout << this->tabele[i].getColoane()[j].getValoareImplicita() << endl;
				}*/
				for (int nrLinii = 0; nrLinii < this->tabele[i].getNrLinii(); nrLinii++)
				{
					//for (int j = 0; j < this->tabele[i].getNrColoane(); j++) {
					cout << this->tabele[i].getLinii()[nrLinii] << endl;;
					//}
				}

				verificare = true;
				break;


			}
		}
		if (!verificare) {
			throw ExceptionTableNotExisting();
		}
	}

	void stergereTabel(string numeTabel) {
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == numeTabel) {
				verificare = true;
			}
		}
		if (verificare) {
			Tabel* temp = new Tabel[this->nrTabele];
			for (int i = 0; i < this->nrTabele; i++) {
				temp[i] = this->tabele[i];
			}
			delete[] this->tabele;

			if (this->nrTabele - 1 > 0) {
				int j = 0;
				this->tabele = new Tabel[this->nrTabele - 1];
				for (int i = 0; i < this->nrTabele; i++) {
					if (temp[i].getNumeTabel() != numeTabel) {
						this->tabele[j] = temp[i];
						j++;
					}
				}
			}
			this->nrTabele--;
			delete[] temp;
			cout << "Table " << numeTabel << " deleted." << endl;
		}
		else {
			throw ExceptionTableNotExisting();
		}
	}

private:
	void inserareInTabel_old(int pozNumeTabel, int pozInceput, int pozFinal, int pozInceputInserabile, int pozFinalInserabile) { //TBD

		for (int i = pozInceput; i < pozFinal; i++) {
			cout << command.getInstructiuniSintaxa()[i];
		}
		cout << endl;
		int semafor = -1;

		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == command.getInstructiuniSintaxa()[pozNumeTabel]) {
				semafor = i;
			}
		}

		if (semafor == -1) {
			cout << command.getInstructiuniSintaxa()[pozNumeTabel];
			throw ExceptionTableNotExisting();
		}
		cout << "Se insereaza in tabela: " << command.getInstructiuniSintaxa()[pozNumeTabel] << endl << " linia: " << endl;
		for (int i = 0; i < tabele[semafor].getNrColoane(); i++)
		{
			cout << this->tabele[semafor].getColoane()[i].getNumeColoana() << " ";
		}
		cout << endl;
		this->tabele[semafor].setNrLinii(this->tabele[semafor].getNrLinii() + 1);
		Coloana* listaCol = new Coloana[this->tabele[semafor].getNrColoane()];
		int newNrColoane = 0;
		for (int i = pozInceputInserabile; i <= pozFinalInserabile; i++) {
			if (command.getInstructiuniSintaxa()[i] != "(" && command.getInstructiuniSintaxa()[i] != ")" && command.getInstructiuniSintaxa()[i] != " " && command.getInstructiuniSintaxa()[i] != ",") {
				cout << command.getInstructiuniSintaxa()[i] << " ";
				listaCol[newNrColoane++].setValoareImplicita(command.getInstructiuniSintaxa()[i]); //populez listaCol pt a fi folosit in constructorul clasei Linie

			}

		}

		//for(int i=0)
		for (int i = 0; i < this->tabele[semafor].getNrColoane(); i++) { //populez listaCol pt a fi folosit in constructorul clasei Linie

		}
		Linie temp(this->tabele[semafor].getNrColoane(), listaCol); //creez linie
		//cout << temp.getNrCol();
		//this->tabele[semafor].setNrLinii(this->tabele[semafor].getNrLinii() + 1); //incrementez nr de linii
		//temporar - setez toate liniile intr-un obiect, ca sa le parsez la setter-ul pt linii
		Linie* liniiTemp = this->tabele[semafor].getLinii();
		cout << liniiTemp[1];

		/*	this->tabele[semafor].setLinii();*/


		/*for (int i = pozInceputInserabile; i < pozFinalInserabile; i++) {
			this->tabele[semafor].linii[this->tabele[semafor].nrLinii];
		}*/
		cout << endl;



	}

public:
	void inserareInTabel(int pozNumeTabel, int pozInceput, int pozFinal, int pozInceputInserabile, int pozFinalInserabile, string* instructiuniSintaxa) {


		int semafor = -1;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].getNumeTabel() == command.getInstructiuniSintaxa()[pozNumeTabel]) {
				semafor = i;
			}
		}

		if (semafor == -1) {
			cout << command.getInstructiuniSintaxa()[pozNumeTabel];
			throw ExceptionTableNotExisting();
		}
		Coloana* listaCol = new Coloana[this->tabele[semafor].getNrColoane() + 1];
		int newNrColoane = 0;


		for (int i = pozInceputInserabile; i < pozFinalInserabile && instructiuniSintaxa[i] != ")"; i++) {
			int nrCol = 0;
			if (instructiuniSintaxa[i] != "(" && instructiuniSintaxa[i] != ")" && instructiuniSintaxa[i] != "," && instructiuniSintaxa[i] != ";") {
				nrCol++;
				listaCol[newNrColoane].setValoareImplicita(instructiuniSintaxa[i]);
				listaCol[newNrColoane].setDimensiune(this->tabele[semafor].getColoane()[nrCol].getDimensiune());
				listaCol[newNrColoane].setNumeColoana(this->tabele[semafor].getColoane()[nrCol].getNumeColoana());
				listaCol[newNrColoane].setTip(this->tabele[semafor].getColoane()[nrCol].getTip());
				cout << instructiuniSintaxa[i] << endl;

			}
		}

		Linie temp(this->tabele[semafor].getNrColoane(), listaCol);
		//cout << temp;

		//cout << temp.getNrCol();
		//this->tabele[semafor].setNrLinii(this->tabele[semafor].getNrLinii() + 1); //incrementez nr de linii




		this->tabele[semafor].addLineToTable(temp);
		cout << "tabelul are " << this->tabele[semafor].getNrLinii() << " linii" << endl;
		//temporar - setez toate liniile intr-un obiect, ca sa le parsez la setter-ul pt linii
		//

		/*Linie* liniiTemp = new Linie[this->tabele[semafor].getNrLinii() + 1]();
		liniiTemp = this->tabele[semafor].getLinii();*/

		/*	for (int i = 0; i < this->tabele[semafor].getNrLinii(); i++) {
				cout << liniiTemp[i];
			}*/



			/*liniiTemp[this->tabele[semafor].getNrLinii()].setListaColoane(temp.getListaColoane());
			this->tabele[semafor].setLinii(liniiTemp);*/



	}


	void stergereDinTabel(int pozNumeTabel, int pozConditie) {
		cout << "Se sterg din tabelul " << command.getInstructiuniSintaxa()[pozNumeTabel] << " liniile unde " << command.getInstructiuniSintaxa()[pozConditie] << endl;
	}


	BazaDate() {
		this->numeBazaDate = new char[strlen("Default") + 1];
		strcpy(this->numeBazaDate, "Default");
		this->tabele = NULL;
		this->command = Comanda();
	}

	BazaDate(char* nume) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->tabele = NULL;
		this->command = Comanda();
	}

	BazaDate(char* nume, Tabel* tabele, Comanda command) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->tabele = new Tabel[this->nrTabele];
		for (int i = 0; i < this->nrTabele; i++) {
			this->tabele[i] = tabele[i];
		}
		this->command = command;
	}

	BazaDate(const BazaDate& b) {
		this->numeBazaDate = new char[strlen(b.numeBazaDate) + 1];
		strcpy(this->numeBazaDate, b.numeBazaDate);
		this->tabele = new Tabel[this->nrTabele];
		for (int i = 0; i < this->nrTabele; i++) {
			this->tabele[i] = b.tabele[i];
		}
		this->command = b.command;
	}

	BazaDate& operator=(const BazaDate& b) {
		if (this->numeBazaDate != NULL) {
			delete[] this->numeBazaDate;
		}
		this->numeBazaDate = new char[strlen(b.numeBazaDate) + 1];
		strcpy(this->numeBazaDate, b.numeBazaDate);
		if (this->tabele != NULL) {
			delete[] this->tabele;
		}
		this->tabele = new Tabel[this->nrTabele];
		for (int i = 0; i < this->nrTabele; i++) {
			this->tabele[i] = b.tabele[i];
		}
		this->command = b.command;
		return *this;
	}

	Comanda getCommand() {
		return this->command;
	}

	void setCommand(Comanda command) {
		this->command = command;
	}

	Tabel* getTabele() {
		return this->tabele;
	}

	int getNrTabele() {
		return this->nrTabele;
	}

	void afisareInstructiune() {
		int poz;
		cout << "Introduceti pozitia cuvantului in sirul de caractere: ";
		cin >> poz;
		if (poz < command.getNrInstructiuni()) {
			cout << command.getInstructiuniSintaxa()[poz - 1] << endl;
		}
		else {
			throw ExceptionPositionNotExisting();
		}
	}

	void afisareInstricutiuni() {
		for (int i = 0; i < command.getNrInstructiuni(); i++) {
			cout << command.getInstructiuniSintaxa()[i] << endl;
		}
	}

	string getInstructiuneInFunctieDePozitie(int poz) {
		return command.getInstructiuniSintaxa()[poz];
	}

	friend istream& operator>>(istream&, BazaDate&);
};

class Fisier {
private:
	string nume;
	string extensie;
	int nrLinii;

public:
	Fisier() {
		this->nume = "Default_Name";
		this->extensie = ".txt";
		this->nrLinii = 0;
	}

	Fisier(string nume) {
		this->nume = nume;
		this->extensie = ".txt";
		this->nrLinii = 0;
	}

	Fisier(string nume, string extensie) {
		this->nume = nume;
		this->extensie = extensie;
		this->nrLinii = 0;
	}

	Fisier(string nume, string extensie, int nrLinii) {
		this->nume = nume;
		this->extensie = extensie;
		this->nrLinii = nrLinii;
	}

	Fisier(const Fisier& f) {
		this->nume = f.nume;
		this->extensie = f.extensie;
		this->nrLinii = f.nrLinii;
	}

	Fisier& operator=(const Fisier& f) {
		this->nume = f.nume;
		this->extensie = f.extensie;
		this->nrLinii = f.nrLinii;
		return *this;
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	string getExtensie() {
		return this->extensie;
	}

	void setExtensie(string extensie) {
		this->extensie = extensie;
	}

	int getNrLinii() {
		return this->nrLinii;
	}

	void setNrLinii(int nrLinii) {
		this->nrLinii = nrLinii;
	}

	friend ifstream& operator>>(ifstream& input, Fisier& f);

};

ifstream& operator>>(ifstream& input, Fisier& f)
{
	input >> f.nume;
	input >> f.extensie;
	return input;
}


//Clasa SaveData prin metoda save() salveaza intr-un fisier txt (am incercat binar insa nu merge)
//structura tabelelor, pentru ca data viitoare cand utilizaztorul va porni aplicatia
//clasa FetchData va putea prelua structura tabelelor si va construi tabelele

class SaveData {
private:
	BazaDate bd;
	char* codStructuraTabele;
	int nrCaractere;


public:
	void save() {
		ofstream myFile("configure.txt", ios::out);
		myFile.write(this->codStructuraTabele, this->nrCaractere);
		myFile.close();
		cout << "All data commited/saved." << endl;
	}

	SaveData() {
		this->bd = BazaDate();
		this->nrCaractere = strlen("Default_Code");
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		strcpy(this->codStructuraTabele, "Default_Code");
	}

	SaveData(BazaDate bd) {
		this->bd = bd;
		string cod = bd.afisareStructuraTabele();
		this->nrCaractere = cod.length();
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		strcpy(this->codStructuraTabele, (char*)&cod);
	}

	SaveData(BazaDate bd, char* codStructuraTabele) {
		this->bd = bd;
		this->nrCaractere = strlen(codStructuraTabele);
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		strcpy(this->codStructuraTabele, codStructuraTabele);
	}

	SaveData(const SaveData& sv) {
		this->bd = sv.bd;
		this->nrCaractere = sv.nrCaractere;
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		strcpy(this->codStructuraTabele, sv.codStructuraTabele);
	}

	SaveData& operator=(const SaveData& sv) {
		this->bd = sv.bd;
		if (this->codStructuraTabele != NULL) {
			delete[] this->codStructuraTabele;
		}
		this->nrCaractere = strlen(sv.codStructuraTabele);
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		strcpy(this->codStructuraTabele, sv.codStructuraTabele);
		return *this;
	}

	void setBd(BazaDate bd) {
		this->bd = bd;
	}

	void setCodStructuraTabele(string cod) {
		this->nrCaractere = cod.length();
		this->codStructuraTabele = new char[this->nrCaractere + 1];
		for (int i = 0; i < this->nrCaractere; i++) {
			this->codStructuraTabele[i] = cod.at(i);
		}
	}

	void setCodStructuraTabele(char* cod) {
		if (cod != NULL) {
			if (this->codStructuraTabele != NULL) {
				delete[] this->codStructuraTabele;
			}
			this->nrCaractere = strlen(cod);
			this->codStructuraTabele = new char[this->nrCaractere + 1];
			strcpy(this->codStructuraTabele, cod);

		}
		else {
			throw NullPointerException();
		}
	}
};

class FetchData { //fetches data from the files and update the database
private:
	BazaDate bd;
	bool isDataFetched;

public:
	BazaDate fetch() {
		this->isDataFetched = true;
		string line;
		string* linii = new string[1];
		linii[0] = "Default";
		ifstream fileInput("configure.txt", ios::in);
		if (!fileInput.is_open()) {
			return this->bd;
		}
		int nrColoane = 0;
		while (getline(fileInput, line)) {
			if (line.find(" ") == string::npos) {
				if (nrColoane > 0) {
					string nume = linii[0];
					string* numeColoana = new string[nrColoane];
					string* tip = new string[nrColoane];
					int* dimensiune = new int[nrColoane];
					string* valoareImplicita = new string[nrColoane];
					for (int i = 0; i < nrColoane; i++) {

						istringstream buf(linii[i + 1]);
						istream_iterator<std::string> beg(buf), end;
						vector<std::string> tokens(beg, end);

						numeColoana[i] = tokens[0];
						tip[i] = tokens[1];
						dimensiune[i] = stoi(tokens[2]);
						valoareImplicita[i] = tokens[3];
					}
					bd.creareTabel(nume, nrColoane, numeColoana, tip, dimensiune, valoareImplicita);
				}
				nrColoane = 0;
				if (linii != NULL) {
					delete[] linii;
				}
				linii = new string[1];
				linii[0] = line;
			}
			else {
				nrColoane++;

				string* temp = new string[nrColoane];
				for (int i = 0; i < nrColoane; i++) {
					temp[i] = linii[i];
				}

				delete[] linii;

				linii = new string[nrColoane + 1];
				for (int i = 0; i < nrColoane; i++) {
					linii[i] = temp[i];
				}
				linii[nrColoane] = line;
				delete[] temp;

			}

		}


		string nume = linii[0];
		string* numeColoana = new string[nrColoane];
		string* tip = new string[nrColoane];
		int* dimensiune = new int[nrColoane];
		string* valoareImplicita = new string[nrColoane];
		for (int i = 0; i < nrColoane; i++) {

			istringstream buf(linii[i + 1]);
			istream_iterator<std::string> beg(buf), end;
			vector<std::string> tokens(beg, end);

			numeColoana[i] = tokens[0];
			tip[i] = tokens[1];
			dimensiune[i] = stoi(tokens[2]);
			valoareImplicita[i] = tokens[3];
		}
		bd.creareTabel(nume, nrColoane, numeColoana, tip, dimensiune, valoareImplicita);


		fileInput.close();
		return bd;
	}

	FetchData() {
		this->bd = BazaDate();
		this->isDataFetched = false;
	}

	FetchData(BazaDate bd) {
		this->bd = bd;
		this->isDataFetched = false;
	}

	FetchData(const FetchData& fd) {
		this->bd = fd.bd;
	}

	FetchData& operator=(const FetchData& fd) {
		this->bd = fd.bd;
		return *this;
	}

	void setBd(BazaDate bd) {
		this->bd = bd;
	}

	void setIsDataFetched(bool isDataFetched) {
		this->isDataFetched = isDataFetched;
	}

	bool getIsDataFetched() {
		return this->isDataFetched;
	}
};

//Clasa asta am facut-o mai mult ca sa citeasca comenziile din fisiere txt 
//Spre exemplu daca scrii in consola poo_proiect.exe fisier1.txt; (foarte importanta ;   daca nu o pui nu ti va lua fisierul/toate fisierele)  
//Va lua toate liniile din fisier si va trece prin metoda cazuri() din ConsoleApplication

//Practic, e ca si cum ar citi de la consola o comanda, doar ca in fisier poate citi mai mutle comenzi
//Le ia pe fiecare in parte si isi face treaba
//Daca primele comenzi sunt gresite va arunca Eroare, si atunci nu va mai citi restul fisierului, chiar daca poate celelalte comenzi erau bune


class LucruFisiere {

private:
	int nrFisiere;
	Fisier* fisiere;
	Comanda command;

public:

	string numeCompletFisier(Fisier f) {
		string nume = f.getNume();
		nume.append(".");
		nume.append(f.getExtensie());
		return nume;
	}

	Fisier* atribuieNumeleFisierelor() {
		int i = 0;
		this->nrFisiere = command.getNrInstructiuni() - 1;
		this->fisiere = new Fisier[this->nrFisiere];
		while (i < this->nrFisiere) {
			size_t pos = command.getInstructiuniSintaxa()[i + 1].find('.');
			string extensie = command.getInstructiuniSintaxa()[i + 1].substr(pos + 1);
			string numeFisier = command.getInstructiuniSintaxa()[i + 1].substr(0, pos);
			this->fisiere[i] = Fisier(numeFisier, extensie);
			i++;
		}
		return fisiere;
	}

	int getNrTotalLiniiDinFisiere() {
		int nrTotalLinii = 0;
		for (int i = 0; i < this->nrFisiere; i++) {
			string nume = numeCompletFisier(fisiere[i]);
			transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
			ifstream fileInput(nume);
			int count = 0;
			string line;
			while (getline(fileInput, line))
				count++;
			fisiere[i].setNrLinii(count);
			nrTotalLinii += count;
			fileInput.close();
		}
		return nrTotalLinii;
	}

	string* citireDinFisiere() {
		int nrTotalLinii = getNrTotalLiniiDinFisiere();
		string* comenzi = new string[nrTotalLinii];
		int j = 0;
		for (int i = 0; i < this->nrFisiere; i++) {
			string nume = numeCompletFisier(fisiere[i]);
			ifstream fileInput(nume, ios::out);
			string comanda;
			while (getline(fileInput, comanda)) {
				comenzi[j] = comanda;
				j++;
			}
			fileInput.close();
		}
		return comenzi;
	}


public:
	LucruFisiere() {
		this->nrFisiere = 0;
		this->fisiere = NULL;
	}

	LucruFisiere(int nrFisiere, Fisier* fisiere) {
		this->nrFisiere = nrFisiere;
		this->fisiere = new Fisier[this->nrFisiere];
		for (int i = 0; i < this->nrFisiere; i++) {
			this->fisiere[i] = fisiere[i];
		}
		this->command = Comanda();
	}

	LucruFisiere(int nrFisiere, Fisier* fisiere, Comanda command) {
		this->nrFisiere = nrFisiere;
		this->fisiere = new Fisier[this->nrFisiere];
		for (int i = 0; i < this->nrFisiere; i++) {
			this->fisiere[i] = fisiere[i];
		}
		this->command = command;
	}

	LucruFisiere(const LucruFisiere& lc) {
		this->nrFisiere = lc.nrFisiere;
		this->fisiere = new Fisier[lc.nrFisiere];
		for (int i = 0; i < lc.nrFisiere; i++) {
			this->fisiere[i] = lc.fisiere[i];
		}
		this->command = lc.command;
	}

	LucruFisiere& operator=(const LucruFisiere& lc) {
		this->nrFisiere = lc.nrFisiere;
		if (this->fisiere != NULL) {
			delete[] this->fisiere;
		}
		this->fisiere = new Fisier[lc.nrFisiere];
		for (int i = 0; i < lc.nrFisiere; i++) {
			this->fisiere[i] = lc.fisiere[i];
		}
		this->command = lc.command;
		return *this;
	}

	int getNrFisiere() {
		return this->nrFisiere;
	}

	Comanda getCommand() {
		return this->command;
	}

	void setCommand(Comanda command) {
		this->command = command;
	}

	void setNrFisiere(int nrFisiere) {
		this->nrFisiere = nrFisiere;
	}

	void setFisiere(int nrFisiere, Fisier* fisiere) {
		if (fisiere != NULL) {
			if (this->fisiere != NULL) {
				delete[] this->fisiere;
			}
			this->fisiere = new Fisier[nrFisiere];
			for (int i = 0; i < nrFisiere; i++) {
				this->fisiere[i] = fisiere[i];
			}
			this->nrFisiere = nrFisiere;
		}
		else {
			throw ExceptionWrongParameteres();
		}
	}

};


class ConsoleApplication {

private:
	BazaDate bd;
	LucruFisiere lc;
	Comanda c;
	SaveData sv;
	FetchData fd;


	void cazuri() {				/* aici se fac cazurile atat pentru comenzile din consola cat si pentru comenzile primite din fisiere*/
		bd.setCommand(c);
		lc.setCommand(c);
		if (c.getInstructiuniSintaxa()[0] == "STOP") {
			throw ExceptionProgramStopped();
		}
		if (c.getInstructiuniSintaxa()[0] == "CREATE" && c.getInstructiuniSintaxa()[1] == "TABLE") {
			bd.creareTabel();
			bd.afisareStructuraTabel(c.getInstructiuniSintaxa()[2]); 
		}
		else if (c.getInstructiuniSintaxa()[0] == "POO_PROIECT.EXE") {
			if (c.getNrInstructiuni() > 1) {
				lc.setCommand(c);
				lc.setNrFisiere(c.getNrInstructiuni() - 1);
				lc.atribuieNumeleFisierelor();
				string* comenzi = new string[lc.getNrTotalLiniiDinFisiere()];
				comenzi = lc.citireDinFisiere();

				for (int i = 0; i < lc.getNrTotalLiniiDinFisiere(); i++) {
					this->program(comenzi[i]);
				}

			}
			else {
				throw ExceptionWrongSyntax();
			}
		}
		else if (c.getInstructiuniSintaxa()[0] == "DISPLAY" && c.getInstructiuniSintaxa()[1] == "TABLE") {
			bd.afisareStructuraTabel(c.getInstructiuniSintaxa()[2]);
			cout << "\n";
			bd.afisareTabel(c.getInstructiuniSintaxa()[2]);
		}
		else if (c.getInstructiuniSintaxa()[0] == "DISPLAY" && c.getInstructiuniSintaxa()[1] == "TABLES") {
			bd.afisareStructuraTabele();
		}
		else if ((c.getInstructiuniSintaxa()[0] == "DELETE" || c.getInstructiuniSintaxa()[0] == "DROP") && c.getInstructiuniSintaxa()[1] == "TABLE") {
			bd.stergereTabel(c.getInstructiuniSintaxa()[2]);
			bd.afisareStructuraTabele();
		}
		else if (c.getInstructiuniSintaxa()[0] == "SAVE" || c.getInstructiuniSintaxa()[0] == "COMMIT") {
			sv.setBd(bd);
			sv.setCodStructuraTabele(bd.afisareStructuraTabele());
			sv.save();
		}
		else if (c.getInstructiuniSintaxa()[0] == "SELECT") {
			//int i = 1;
			int pozInceput = 1, pozFinal = pozInceput;
			while (c.getInstructiuniSintaxa()[pozFinal] != "FROM" && pozFinal < c.getNrInstructiuni()) {
				//cout << this->instructiuniSintaxa[i] << endl;
				pozFinal++;
			}

			if (c.getInstructiuniSintaxa()[pozFinal] != "FROM") {
				throw ExceptionInvalidCommand();
			}
			cout << "Se selecteaza campurile: ";
			for (int i = pozInceput; i < pozFinal; i++) {
				cout << c.getInstructiuniSintaxa()[i];
			}
			cout << " din tabelul " << this->bd.getTabele()[pozFinal + 1].getNumeTabel();

			//if (pozInceput = pozFinal - 1) { //Select all
			//	afisareTabel(this->instructiuniSintaxa[pozFinal + 1]);
			//}

		}
		else if (c.getInstructiuniSintaxa()[0] == "INSERT" && c.getInstructiuniSintaxa()[1] == "INTO") {
			int pozNumeTabel = 2;
			int inceputColoaneTemplate = 3, finalColoaneTemplate = inceputColoaneTemplate;
			while (finalColoaneTemplate < c.getNrInstructiuni() && c.getInstructiuniSintaxa()[finalColoaneTemplate] != "VALUES") {
				finalColoaneTemplate++;
			}

			int inceputColoaneInserabile = finalColoaneTemplate + 1;
			int finalColoaneInserabile = inceputColoaneInserabile;
			while (finalColoaneInserabile < c.getNrInstructiuni()) {
				finalColoaneInserabile++;
			}

			/*for (int i = 0; i < finalColoaneInserabile; i++) {
				cout << c.getInstructiuniSintaxa()[i];
			}
			cout << endl;*/
			/*string* paramComanda = c.getInstructiuniSintaxa();
			for (int i = 0; i < finalColoaneInserabile; i++)
			{
				cout << paramComanda[i];
			}*/
			string* paramComanda = c.getInstructiuniSintaxa();
			bd.inserareInTabel(pozNumeTabel, inceputColoaneTemplate, finalColoaneTemplate, inceputColoaneInserabile, finalColoaneInserabile, paramComanda);
		}
		else if (c.getInstructiuniSintaxa()[0] == "DELETE" && c.getInstructiuniSintaxa()[1] == "FROM" && c.getInstructiuniSintaxa()[3] == "WHERE") {
			int pozNumeTabel = 2;
			int pozConditie = 4;
			bd.stergereDinTabel(pozNumeTabel, pozConditie);
		}
		else {
			throw ExceptionInvalidCommand();
		}
	}


	//Metoda asta am folosit-o pentru a trece prin cazuri fiecare comanda din fisiere (atunci cand bagi in consola poo_proiect.exe fisier1.txt;)
	//De mentionat este ca mereu trebuie sa pui ; la finalul unor comenzi fiindca altfel nu iti ia bine
	//In special trebuie sa pui cand faci poo_proiect.exe fisier1.txt;

	void program(string comanda) {
		if (comanda != "") {
			c.citireComandaDinFisier(comanda);
			bd.setCommand(c);
			lc.setCommand(c);
			cazuri();
		}
		else {
			throw ExceptionInvalidCommand();
		}
	}

public:
	void program() {
		fd.setBd(bd);
		if (fd.getIsDataFetched() == false) {
			this->bd = fd.fetch();
		}
		c.citireComanda();
		cazuri();
	}

	ConsoleApplication() {
		this->bd = BazaDate();
		this->lc = LucruFisiere();
		this->c = Comanda();
		this->sv = SaveData();
		this->fd = FetchData();
	}

	ConsoleApplication(BazaDate bd, LucruFisiere lc, Comanda c, SaveData sv, FetchData fd) {
		this->bd = bd;
		this->lc = lc;
		this->c = c;
		this->sv = sv;
		this->fd = fd;
	}

	ConsoleApplication(const ConsoleApplication& ca) {
		this->bd = ca.bd;
		this->lc = ca.lc;
		this->c = ca.c;
		this->sv = ca.sv;
		this->fd = ca.fd;
	}

	ConsoleApplication& operator=(const ConsoleApplication& ca) {
		this->bd = ca.bd;
		this->lc = ca.lc;
		this->c = ca.c;
		this->sv = ca.sv;
		this->fd = ca.fd;
		return *this;
	}

};

int BazaDate::nrTabele = 0;

istream& operator>>(istream& intrare, BazaDate& bd) {
	cout << "Numele bazei de date: ";
	char numeBD[20];
	intrare >> numeBD;
	if (bd.numeBazaDate != NULL) {
		delete[] bd.numeBazaDate;
	}
	bd.numeBazaDate = new char[strlen(numeBD) + 1];
	strcpy(bd.numeBazaDate, numeBD);
	cout << endl;
	return intrare;
}



void main() {
	BazaDate bd;
	Comanda c;
	LucruFisiere lc;
	SaveData sv;
	FetchData fd;
	cin >> bd;
	ConsoleApplication ca(bd, lc, c, sv, fd);
	bool i = true;
	while (i) {
		try {
			ca.program();
		}
		catch (ExceptionProgramStopped) {
			i = false;
			cout << "Programul s-a oprit" << endl;
		}
		catch (ExceptionWrongSyntax) {
			cout << "Sintaxa gresita, incearca din nou." << endl;
		}
		catch (ExceptionTableAlreadyExists) {
			cout << "Tabelul este deja existent in baza de date. Incearca alt nume de tabel" << endl;
		}
		catch (ExceptionTableNotExisting) {
			cout << "Tabelul nu exista, incearca din nou." << endl;
		}
		catch (ExceptionNoTablesFound) {
			cout << "Nu s-a gasit niciun tabel." << endl;
		}
		catch (ExceptionNoInstruction) {
			cout << "Nu ai introdus nicio comanda. Incearca din nou." << endl;
		}
		catch (ExceptionPositionNotExisting) {
			cout << "Pozitia introdusa nu exista." << endl;
		}
		catch (ExceptionInvalidCommand) {
			cout << "Comanda invalida, incearca din nou." << endl;
		}
		catch (ExceptionWrongParameteres) {
			cout << "Parametri incorecti." << endl;
		}
		catch (NullPointerException) {
			cout << "Pointer null. Te rog verifica valoarea introdusa ca argument.";
		}
	}
}