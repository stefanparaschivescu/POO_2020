#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;

class ExceptionWrongSyntax {};
class ExceptionTableNotExisting {};
class ExceptionNoTablesFound {};
class ExceptionNoInstruction {};
class ExceptionPositionNotExisting {};
class ExceptionInvalidCommand {};
class ExceptionProgramStopped {};
class ExceptionTableAlreadyExists {};

class Coloana {
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
	Coloana(string numeColoana, string tip, int dimensiune, string valoareImplicita) {
		this->numeColoana = numeColoana;
		this->tip = tip;
		this->dimensiune = dimensiune;
		this->valoareImplicita = valoareImplicita;
	}
	Coloana(Coloana& coloana) {
		this->numeColoana = coloana.numeColoana;
		this->tip = coloana.tip;
		this->dimensiune = coloana.dimensiune;
		this->valoareImplicita = coloana.valoareImplicita;
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
		for (int i=0; i<nrColoane; i++) {
			this->coloane[i] = Coloana(coloane[i]);
		}
	}
};

class BazaDate {
private:
	char* numeBazaDate;
	string comanda;
	int nrCaractereInstructiuni;
	int nrInstructiuni;
	string* instructiuniSintaxa;
	static int nrTabele;
	Tabel* tabele;

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

	void transformareStringInVector() {
		int j = 0;
		string temp;
		this->instructiuniSintaxa = new string[this->nrCaractereInstructiuni / 2]; //vom avea aproximativ (nrCaractereInstructiuni / 2) instructiuni. Cel mai probabil alocam spatiu prea mult degeaba, dar nu mai stiu cum se face alocare dinamica
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
				this->instructiuniSintaxa[j] = temp; //aici n am idee de ce da warning poate rezolvi tu
				j++;
			}
		}
		this->nrInstructiuni = j - 1;
	}

	void creareTabel() {
		if (this->nrTabele > 0) {
			bool existaTabelul;
			for (int i = 0; i < this->nrTabele; i++) {
				if (this->tabele[i].numeTabel == this->instructiuniSintaxa[2]) {
					existaTabelul = true;
					throw ExceptionTableAlreadyExists();
				}
			}
		}
		if (this->instructiuniSintaxa[0] == "CREATE" && this->instructiuniSintaxa[1] == "TABLE" && this->instructiuniSintaxa[3] == "(" && this->instructiuniSintaxa[this->nrInstructiuni - 1] == ")") {
			string* numeColoana = new string[this->nrInstructiuni / 12 + 1];
			string* tip = new string[this->nrInstructiuni / 12 + 1];
			int* dimensiune = new int[this->nrInstructiuni / 12 + 1];
			string* valoareImplicita = new string[this->nrInstructiuni / 12 + 1];
			int nrColoane = 0;
			if (this->nrInstructiuni > 12) {
				for (int i = 5; i < this->nrInstructiuni; i = i + 10) {
					numeColoana[nrColoane] = this->instructiuniSintaxa[i];
					tip[nrColoane] = this->instructiuniSintaxa[i + 2];
					dimensiune[nrColoane] = stoi(this->instructiuniSintaxa[i + 4]);
					valoareImplicita[nrColoane] = this->instructiuniSintaxa[i + 6];
					nrColoane++;
				}
			}
			else {
				numeColoana[nrColoane] = this->instructiuniSintaxa[4];
				tip[nrColoane] = this->instructiuniSintaxa[6];
				dimensiune[nrColoane] = stoi(this->instructiuniSintaxa[8]);
				valoareImplicita[nrColoane] = this->instructiuniSintaxa[10];
				nrColoane++;
			}
			this->nrTabele++; //aici se incrementeaza numarul tabelelor
			
			// mai jos am incercat sa mai aloc memorie pentru ca sa intre inca o tabela
			//daca exista vreo functie pentru asta incearca sa o folosesti tu 
			
			Tabel* temp = new Tabel[this->nrTabele];
			for (int i = 0; i < this->nrTabele-1; i++) {
				temp[i] = this->tabele[i];
			}
			this->tabele = new Tabel[this->nrTabele + 1];
			for (int i = 0; i < this->nrTabele - 1; i++) {
				this->tabele[i] = temp[i];
			}
			delete[] temp;
			Coloana* coloane = new Coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++) {
				coloane[i] = Coloana(numeColoana[i], tip[i], dimensiune[i], valoareImplicita[i]);
			}

			this->tabele[this->nrTabele - 1] = Tabel(this->instructiuniSintaxa[2], nrColoane, coloane);
			
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

	void afisareStructuraTabele() {
		if (this->nrTabele > 0) {
			for (int i = 0; i < this->nrTabele; i++) {
				cout << this->tabele[i].numeTabel << endl;
				for (int j=0; j < this->tabele[i].nrColoane; j++) {
					cout << this->tabele[i].coloane[j].getNumeColoana() << " " << tabele[i].coloane[j].getTip() << " " << tabele[i].coloane[j].getDimensiune() << " " << tabele[i].coloane[j].getValoareImplicita() << endl;
				}
			}
		}
		else {
			throw ExceptionNoTablesFound();
		}
	}

	void afisareStructuraTabel(string numeTabel) {
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].numeTabel == numeTabel) {
				cout << this->tabele[i].numeTabel << " " << this->tabele[i].coloane->getTip() << " " << this->tabele[i].coloane->getDimensiune() << " " << this->tabele[i].coloane->getValoareImplicita() << endl;
				verificare = true;
			}
		}
		if (!verificare) {
			throw ExceptionTableNotExisting();
		}
	}

	void afisareTabel(string numeTabel) { //asta nu merge cum ar trebui, trebuie sa mai umbli tu pe la linii si sa faci in asa fel incat sa aifseze toata tabela cu datele ei 
		bool verificare = false;
		for (int i = 0; i < this->nrTabele; i++) {
			if (this->tabele[i].numeTabel == numeTabel) {
				cout << this->tabele[i].numeTabel << endl;
				for (int j=0; j<this->tabele[i].nrColoane; j++) {
					cout << this->tabele[i].coloane[j].getValoareImplicita() << endl;
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
			if (this->tabele[i].numeTabel == numeTabel) {
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
					if (temp[i].numeTabel != numeTabel) {
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

public:
	BazaDate() {
		this->numeBazaDate = new char[strlen("Default") + 1];
		strcpy(this->numeBazaDate, "Default");
		this->comanda = ' ';
		this->nrCaractereInstructiuni = 0;
	}

	BazaDate(char* nume) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = ' ';
		this->nrCaractereInstructiuni = 0;
	}

	BazaDate (char* nume, string comanda) {
		this->numeBazaDate = new char[strlen(nume) + 1];
		strcpy(this->numeBazaDate, nume);
		this->comanda = comanda;
		this->nrCaractereInstructiuni = comanda.length();
		this->transformareStringInVector();
	}

	void afisareInstructiune() {
		int poz;
		cout << "Introduceti pozitia cuvantului in sirul de caractere: ";
		cin >> poz;
		if (poz < this->nrInstructiuni) {
			cout << this->instructiuniSintaxa[poz - 1] << endl;
		}
		else {
			throw ExceptionPositionNotExisting();
		}
	}

	void afisareInstricutiuni() {
		for (int i = 0; i < this->nrInstructiuni; i++) {
			cout << this->instructiuniSintaxa[i] << endl;
		}
	}

	string getInstructiuneInFunctieDePozitie(int poz) {
		return this->instructiuniSintaxa[poz];
	}

	void program() {
		this->citireComanda();
		if (this->comanda == "STOP") {
			throw ExceptionProgramStopped();
		}
		if (this->instructiuniSintaxa[0] == "CREATE" && this->instructiuniSintaxa[1] == "TABLE") {
			this->creareTabel();
			this->afisareStructuraTabele(); //asta e doar ca sa vezi ca se creeaza obiectele de tip Tabel, deci probabil ca sa mearga afisareTabel() trebuie sa faci tu ceva la clasele Linie, Coloana etc.
		}
		else if (this->instructiuniSintaxa[0] == "DISPLAY" && this->instructiuniSintaxa[1] == "TABLE") {
			this->afisareTabel(this->instructiuniSintaxa[2]);
		}
		else if (this->instructiuniSintaxa[0] == "DELETE" && this->instructiuniSintaxa[1] == "TABLE") {
			this->stergereTabel(this->instructiuniSintaxa[2]);
			this->afisareStructuraTabele();
		}
		else {
			throw ExceptionInvalidCommand();
		}
	}

	friend istream& operator>>(istream&, BazaDate&);
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
	cin >> bd;
	bool i = true;
	while (i) {
		try {
			bd.program();
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
	}
}