#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class ExceptionWrongSyntax {};

class Coloana {
	string tip;
	int dimensiune;
	string valoareImplicita;
public:
	Coloana() {
		this->tip = "number";
		this->dimensiune = 7;
		this->valoareImplicita = "100";
	}
	Coloana(string tip, int dimensiune, string valoareImplicita) {
		this->tip = tip;
		this->dimensiune = dimensiune;
		this->valoareImplicita = valoareImplicita;
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

};

class Linie {
	int nrColoane;
	Coloana* listaColoane;
public:
	Linie(int nrColoane, Coloana* listaColoane) {
		this->nrColoane = nrColoane;
		this->listaColoane = new Coloana[this->nrColoane];
		for (int i = 0; i < this->nrColoane; i++) {
			this->listaColoane[i] = listaColoane[i];
		}
	}

};

class Tabel {
public:
	string numeTabel;
	Linie* linii;
	Coloana* coloane;
public:

	Tabel() {
		this->numeTabel = "Tabel_Default";
	}
	Tabel(string numeTabel, string tip, int dimensiune, string valoareImplicita) {
		this->numeTabel = numeTabel;
		this->coloane = new Coloana(tip, dimensiune, valoareImplicita);
	}
};

class BazaDate {
private:
	char* numeBazaDate;
	string comanda;
	int nrCaractereInstructiuni;
	int nrInstructiuni;
	string* instructiuniSintaxa;
	int nrTabele;
	Tabel* tabele;

	void transformareStringInVector() {
		int j = 0;
		string temp;
		this->instructiuniSintaxa = new string[this->nrCaractereInstructiuni];
		for (int i = 0; i < this->nrCaractereInstructiuni; i++) {
			if (this->comanda.at(i) != ' ' && this->comanda.at(i) != '(' && this->comanda.at(i) != ')' && this->comanda.at(i) != ',') {
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
	BazaDate() {
		this->numeBazaDate = new char[strlen("Default") + 1];
		strcpy(this->numeBazaDate, "Default");
		this->comanda = ' ';
		this->nrCaractereInstructiuni = 0;
		this->nrTabele = 0;
	}

	BazaDate(char* nume) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = ' ';
		this->nrCaractereInstructiuni = 0;
		this->nrTabele = 0;
	}

	BazaDate (char* nume, string comanda) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = comanda;
		this->nrCaractereInstructiuni = comanda.length();
		this->nrTabele = 0;
		this->transformareStringInVector();
	}

	

	void citireComanda() {
		cout << "Comanda: ";
		if (this->nrInstructiuni == 0) {
			cin.get();
		}
		getline(cin, this->comanda);
		this->nrCaractereInstructiuni = this->comanda.length();
		this->transformareStringInVector();
	}

	void afisareInstructiune() {
		int poz;
		cout << "Introduceti pozitia cuvantului in sirul de caractere: ";
		cin >> poz;
		cout << this->instructiuniSintaxa[poz - 1] << endl;
	}

	void afisareInstricutiuni() {
		for (int i = 0; i < this->nrInstructiuni; i++) {
			cout << this->instructiuniSintaxa[i] << endl;
		}
	}

	string getInstructiunePoz(int poz) {
		return this->instructiuniSintaxa[poz];
	}

	void creareTabel() {
		this->tabele = new Tabel[this->nrTabele + 1];
		if (this->instructiuniSintaxa[0]=="create" && this->instructiuniSintaxa[1]=="table") {
			string* numeTabele = new string[this->nrInstructiuni / 12 + 1];
			string* tip = new string[this->nrInstructiuni / 12 + 1];
			int* dimensiune = new int[this->nrInstructiuni / 12 + 1];
			string* valoareImplicita = new string[this->nrInstructiuni / 12 + 1];
			int j = 0;
			if (this->nrInstructiuni > 12) {
				for (int i = 5; i < this->nrInstructiuni; i = i + 10) {
					numeTabele[j] = this->instructiuniSintaxa[i];
					tip[j] = this->instructiuniSintaxa[i + 2];
					dimensiune[j] = stoi(this->instructiuniSintaxa[i + 4]);
					valoareImplicita[j] = this->instructiuniSintaxa[i + 6];
					j++;
				}
			}
			else {
				numeTabele[j] = this->instructiuniSintaxa[4];
				tip[j] = this->instructiuniSintaxa[6];
				dimensiune[j] = stoi(this->instructiuniSintaxa[8]);
				valoareImplicita[j] = this->instructiuniSintaxa[10];
				j++;
			}
			this->nrTabele = j;
			for (int i=0; i<j; i++) {
				this->tabele[i] = Tabel(numeTabele[i], tip[i], dimensiune[i], valoareImplicita[i]);
			}
		}
		else {
			throw ExceptionWrongSyntax();
		}
	}

	void afisareStructuraTabele() {
		for (int i = 0; i < this->nrTabele; i++) {
			cout << this->tabele[i].numeTabel << " " << this->tabele[i].coloane->getTip() << " " << this->tabele[i].coloane->getDimensiune()<< " " << this->tabele[i].coloane->getValoareImplicita() << endl;
		}
	}

	void afisareTabel(string numeTabel) {
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].numeTabel == numeTabel) {
				cout << this->tabele[i].numeTabel << endl;
				cout << this->tabele[i].linii << endl;
				cout << this->tabele[i].coloane << endl;
				break;
			}
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
		bd.afisareInstricutiuni();
		bd.creareTabel();
		bd.afisareStructuraTabele();
	}
}