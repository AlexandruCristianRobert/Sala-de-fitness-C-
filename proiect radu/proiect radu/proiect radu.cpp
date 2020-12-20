#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


class Instructor;
class Programare
{
	friend class Instructor;
private:
	int NrParticipanti;
	string DataProgramare;
	int Durata;

public:
	Programare() {};

	friend istream& operator>>(istream&, Programare&);
	friend ostream& operator<<(ostream& os, Programare& p)
	{
		os << "\nNr participanti: " << p.NrParticipanti << endl;
		os << "\nData programarii:" << p.DataProgramare << endl;
		os << "\nDurata sedinta:" << p.Durata << endl;
		return os;
	}
};


class Instructor
{
	friend class Programare;
private:
	int Id;
	static int IdCurent;
	static int gradMaxim;
	static int GradMinim;
	int gradProgramare;
	char* Nume;
	Programare* Prog = nullptr;
	int NrProgramari;

	void SetareGradOcupare()
	{
		for (int i = 0;i < NrProgramari;i++)
		{
			if (Prog[i].NrParticipanti > gradMaxim)
				gradMaxim = Prog[i].NrParticipanti;
			if (Prog[i].NrParticipanti < GradMinim)
				GradMinim = Prog[i].NrParticipanti;

		}
	}
	void AfisareGradOcupareSedinta(Programare p, int i)
	{
		cout << endl;
		if (p.NrParticipanti == gradMaxim)
			cout << "Sedinta " << (i + 1) << " are are cel mai mare grad de ocupare" << endl;
		else
			if (p.NrParticipanti == GradMinim)
				cout << "Sedinta " << (i + 1) << " are are cel mai mic grad de ocupare" << endl;
			else
				cout << "Sedinta " << (i + 1) << " are un grad normal de ocupare" << endl;
	}
public:

	Instructor(const char* iNume, int iNrProgramari):Id(IdCurent++)
	{
		Prog = new Programare[iNrProgramari];
		NrProgramari = iNrProgramari;
		this->Nume = new char[strlen(iNume) + 1];
		strcpy_s(this->Nume, strlen(iNume) + 1, iNume);
		SetProgramari();

	};
	void AfisareInstructor()
	{
		cout << "\nNume: " << Nume << endl;
		cout << "Id: " << Id << endl;
		cout << "Nr sedinte: " <<NrProgramari<< endl;
	}
	void SetProgramari()
	{
		for (int i = 0;i < NrProgramari;i++)
		{
			cin >> Prog[i];
		}
	}
	void afisareProgramari()
	{
		SetareGradOcupare();
		for (int i = 0;i < NrProgramari;i++)
		{
			cout << "----------------------------------------";
			cout << Prog[i];
			AfisareGradOcupareSedinta(Prog[i], i);
		}
	}
	Instructor(const char* iNume = "Anonim") :NrProgramari(0), Id(IdCurent++)
	{
		this->Nume = new char[strlen(iNume) + 1];
		strcpy_s(this->Nume, strlen(iNume) + 1, iNume);

	};
	void set_NrProgramari(int iNrProgramari)
	{
		NrProgramari = iNrProgramari;
	}


	friend istream& operator>>(istream& is, Programare& p)
	{
		cout << "----------------------------------------" << endl;
		cout << "Nr participanti: ";
		is >> p.NrParticipanti;
		cout << "Data programarii (DD.MM.YYYY):";
		is >> p.DataProgramare;
		cout << "Durata sedinta (ore):";
		is >> p.Durata;
		return is;
	}


};
int Instructor::IdCurent;
int Instructor::gradMaxim = 0;
int Instructor::GradMinim = 1000; // se poate inbunatati aici
int main()
{
	int Optiune;
	int NrSedinte;
	string Nume;
	cout << "-----------------Meniu------------------" << endl;
	cout << "\nIntroduceti numele instructorului: ";
	getline(cin, Nume);
	int lungimeNume = Nume.length() + 1;
	char* Numechar = new char(lungimeNume);
	strcpy(Numechar, Nume.c_str());
	cout << "\nIntroduceti nr de sedinte:";
	cin >> NrSedinte;
	Instructor inst(Numechar, NrSedinte);
	cout << endl;
	cout << "Doriti sa vedeti detaliile instructorului??\nTastati 1 pentru a accesa datele\n";
	cin >> Optiune;
	if (Optiune == 1)
	{
		system("CLS"); //curata consola
		cout << flush;
		inst.AfisareInstructor();
	}
	cout << endl;
	cout << "Doriti sa vedeti detaliile sedintelor?\nTastati 1 pentru a accesa datele\n";
	cin >> Optiune;
	if (Optiune == 1)
	{
		system("CLS");
		cout << flush;
		inst.afisareProgramari();
	}

	return 0;
}

