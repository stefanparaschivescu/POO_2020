#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class ExceptionWrongSyntax {};

class Linie {

};

class Coloana {
	string tip;
	int dimensiune;
	string valoareImplicita;
public:
	Coloana(string tip, int dimensiune, string valoareImplicita) {
		this->tip = tip;
		this->dimensiune = dimensiune;
		this->valoareImplicita = valoareImplicita;
	}

};

class Tabel {
	string numeTabel;
	Linie* linii;
	Coloana* coloane;
public:

	Tabel() {
		this->numeTabel = "Tabel_Default";
	}
	Tabel(string numeTabele, string tip, int dimensiune, string valoareImplicita) {
		this->numeTabel = numeTabel;
		this->coloane = new Coloana(tip, dimensiune, valoareImplicita);
	}
};

class BazaDate {
private:
	char* numeBazaDate;
	string comanda;
	int nrInstructiuni;
	string* instructiuniSintaxa;
	int nrTabele;
	Tabel* tabele;

public:
	void transformareStringInVector() {
		int j = 0;
		string temp;
		this->instructiuniSintaxa = new string[this->nrInstructiuni];
		for (int i = 0; i < this->nrInstructiuni; i++) {
			
			if (this->comanda.at(i) != ' ' && this->comanda.at(i) != '(' && this->comanda.at(i) != ')' && this->comanda.at(i) != ',') {
				temp.push_back(this->comanda.at(i));
			}
			else if (this->comanda.at(i) == '(') {
				this->instructiuniSintaxa[j] = "(";
				j++;
			}
			else if (this->comanda.at(i) == ')') {
				this->instructiuniSintaxa[j] = ")";
				j++;
			}
			else if (this->comanda.at(i) == ',') {
				this->instructiuniSintaxa[j] = ",";
				j++;
			}
			else {
				this->instructiuniSintaxa[j] = temp;
				j++;
				temp.clear();
			}
		}
	}

	BazaDate() {
		this->numeBazaDate = new char[strlen("Default") + 1];
		strcpy(this->numeBazaDate, "Default");
		this->comanda = ' ';
		this->nrInstructiuni = 0;
		this->nrTabele = 0;
	}

	BazaDate(char* nume) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = ' ';
		this->nrInstructiuni = 0;
		this->nrTabele = 0;
	}

	BazaDate (char* nume, string comanda) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = comanda;
		this->nrInstructiuni = comanda.length();
		this->nrTabele = 0;
		this->transformareStringInVector();
	}

	

	void citireComanda() {
		cout << "Comanda: ";
		cin.get();
		getline(cin, this->comanda);
		this->nrInstructiuni = this->comanda.length();
		this->transformareStringInVector();		
	}

	void afisareInstructiune() {
		int poz;
		cout << "Introduceti pozitia cuvantului in sirul de caractere: ";
		cin >> poz;
		cout << this->instructiuniSintaxa[poz - 1] << endl;
	}

	string getInstructiunePoz(int poz) {
		return this->instructiuniSintaxa[poz];
	}

	void creareTabel() {
		this->tabele = new Tabel[this->nrTabele + 1];
		if ((this->instructiuniSintaxa[3] == "DACA" || this->instructiuniSintaxa[3] == "(") && this->instructiuniSintaxa[this->nrInstructiuni] == ")" && this->instructiuniSintaxa[this->nrInstructiuni-1] == ")") {
			string* numeTabele;
			string* tip;
			int* dimensiune;
			string* valoareImplicita;
			int j = 0;
			for (int i = 8; i < this->nrInstructiuni; i = i + 10) {
				numeTabele[j] = this->instructiuniSintaxa[i];
				tip[j] = this->instructiuniSintaxa[i + 2];
				dimensiune[j] = atol((char*) &this->instructiuniSintaxa[i + 4]);
				valoareImplicita[j] = this->instructiuniSintaxa[i + 6];
				j++;
			}
			for (int i=0; i<j; i++) {
				this->tabele[i] = Tabel(numeTabele[j], tip[j], dimensiune[j], valoareImplicita[j]);
			}
		}
		else {
			throw ExceptionWrongSyntax();
		}
	}

	friend istream& operator>>(istream&, BazaDate&);
};

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
	cin >> bd;
	bool i = true;
	while (i) {
		bd.citireComanda();
		bd.afisareInstructiune();
	}
}