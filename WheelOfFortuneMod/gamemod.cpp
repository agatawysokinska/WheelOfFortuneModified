#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<cstring>
#include <cstdio>
#include <cctype>
#include <algorithm> 
#include <fstream>

using namespace std;

const int wielkosc = 10;
const int wielkosc2 = 20;	//stale wielkosci tablic
const int wielkosc3 = 5;
const int wielkosc4 = 3;
const int rozmiar_spolgloski = 1;
const int ile_hasel = 5;
ofstream temporary_file("hasla.temp.txt", ios::out);
ofstream reset_base("hasla.reset.txt", ios::out);
ifstream new_base("hasla.nowe.txt");
ifstream myfile;



class Licznik {

public:
	string kategoria;
	int ile_razy_uzyte = 0;
	int suma_hasel_z_kategorii = 0;		//dane do liczenia ilosci hasel i wykorzystanych hasel
	int dlugosc = 0;
	double procent;
	Licznik() {
	}
	Licznik(string kat, int ile_razy, int suma, int dl, double proc) {
		this->kategoria = kat;
		this->ile_razy_uzyte = ile_razy;
		this->suma_hasel_z_kategorii = suma;
		this->dlugosc = dl;
		this->procent = proc;
	}
};
struct dane_kategorii
{
	string nazwa_kategorii;
	int suma = 0;			//dane do obliczania procent
	int uzyte = 0;
};
class Haslo {
public:
	string tresc;
	string kategoria;
};

class Kolo_Fortuny
{
public:

	struct gracz
	{
		string imie;
		int miejsce_w_tablicy;
		int losowanie_kolejnosci;
		string nagroda_gracza[wielkosc];
		int min_miejsca_w_tablicy_ng = 0;
		int max_miejsca_w_tablicy_ng = 1;
		int wartosc_nagrody_gracza = 0;
		int wygrana_kwota = 0;
		int calkowita_wygrana_kwota = 0;
		char kupione_samogloski[wielkosc];
		int kupione = 0;	//ilosc kupionych samoglosek
		int min_zakupionych = 0;
		int max_zakupionych = 1;
	};
	gracz* dane[4];
	void losuj_kolejnosc(gracz* dane, dane_kategorii* Dane);
	void losuj_haslo(gracz* dane, dane_kategorii* Dane);
	void rysuj_pole(gracz* dane, dane_kategorii* Dane);
	void zakrec_kolem(gracz* dane, dane_kategorii* Dane);
	void wykorzystales_spolgloske(gracz* dane, dane_kategorii* Dane);
	void nieudana_proba(gracz* dane, dane_kategorii* Dane);
	void zgadywanie(gracz* dane, dane_kategorii* Dane);
	void zakup(gracz* dane, dane_kategorii* Dane);
	void uzyj_samogloski(gracz* dane, dane_kategorii* Dane);
	void znam_haslo(gracz* dane, dane_kategorii* Dane);
	void przejscie(gracz* dane, dane_kategorii* Dane);
	void nowa_runda(gracz* dane, dane_kategorii* Dane);
	void koniec(gracz* dane, dane_kategorii* Dane);
	void init_ile_razy_uzyto(dane_kategorii* Dane);
	bool ile_uzyto(string slowo, dane_kategorii* Dane);
	void reset_hasel(string slowo, dane_kategorii* Dane);
	void nowa_baza(string slowo, dane_kategorii* Dane);
private:
	int length = myfile.tellg();
	Haslo haslo_z_pliku;
	Licznik licznik_hasel[1000];
	int elementy_tablicy = 0;
	char samogloski[wielkosc] = { 'a','i','e','o','u','y' };
	int ile_osob;
	int miejsce_w_tablicy_gracza;		//miejsce w tablicy aktualnego gracza
	string Kategoria;
	unsigned int los;
	int tablica_pol[wielkosc2];
	string haslo;
	string zaszyfrowane_haslo;
	string tab[wielkosc4];
	int min_miejsce_nagrod = 0;
	int max_miejsce_nagrod = 1;
	char spolgloska1[rozmiar_spolgloski];
	char spolgloska2[rozmiar_spolgloski];
	char ktora_spolgloska;
	char uzyte_spolgloski[wielkosc2];
	int uzyte_spolgloski_min = 0;
	int uzyte_spolgloski_max = 1;
	string nagroda;
	int wartosc; //wartosc nagrody
	int tury = 0;
	int rundy = 1;
	unsigned char sign;
	char opcja[wielkosc4]; //wybor tak/nie w funkcji "uzyj samogloski"
	char zakupiona[2];  //zakupiona samogloska
	int odgadniete_pole = 0;
	string zgaduje;
	int polozenie = 0;
	int suma = 0;
	int kolejnosc = 1;
	int poczatek = 0;
};

void Kolo_Fortuny::losuj_kolejnosc(gracz* dane, dane_kategorii* Dane)
{
	cout << " WITAJ W GRZE KOLO FORTUNY " << endl;
	cout << endl;
	cout << "W ile osob chcesz zagrac?" << endl;
	cout << "wybierz: 1 / 2 / 3 / 4" << endl;
	cin >> ile_osob;							//wczytywanie ilosci graczy
	for (int i = 0; i < ile_osob; i++)
	{
		cout << "Podaj swoje imie: ";		//kazdy gracz podaje swoje imie i otrzymuje odpowiednie miejce w tablicy
		cin >> dane[i].imie;
		dane[i].miejsce_w_tablicy = i;
	}
	cout << endl;
	if (ile_osob == 1)		//jezeli jest tylko 1 osoba to rozpoczyna gre bez losowania
	{
		cout << dane[0].imie << " " << " rozpoczynasz gre, powodzenia!" << endl;
		miejsce_w_tablicy_gracza = 0;		//gracz otrzymuje 0 miejsce w tablicy
		losuj_haslo(dane, Dane);
	}
	else {
		int suma = 25;			//dla wiekszej ilosci graczy generowana jest pula liczb, z ktorej beda losowac kolejnosc gry
		for (int i = 0; i < 16; i++)
		{
			tablica_pol[i] = suma * (i + 1);
		}
		tablica_pol[16] = 500;

		for (int i = 0; i < ile_osob; i++)
		{
			cin.get();
			cout << "zakrec kolem  " << dane[i].imie << ": ";
			cin.get();
			los = (rand() % 16);		//losowanie pola z liczba
			cout << tablica_pol[los] << endl;
			dane[i].losowanie_kolejnosci = tablica_pol[los];  //kolejnym graczom przypisywana jest wartosc wylosowanej liczby
		}

		int max = 0;
		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci > max)
				max = dane[i].losowanie_kolejnosci;		//wyznaczenie najwiekszej wylosowanej liczby
		}

		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci == max)
				miejsce_w_tablicy_gracza = dane[i].miejsce_w_tablicy;		//osoba, ktora wylosowala najwieksza liczbe zacznie gre
		}

		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci == max)
				cout << dane[i].imie << " " << " rozpoczynasz gre, powodzenia!" << endl;
		}
		cout << endl;
		losuj_haslo(dane, Dane);
		//init_ile_razy_uzyto(Dane);
	}
};

char* znajdz_haslo(string slowo)
{
	char* tablica = new char[100];
	int i = 1;
	for (; i < slowo.size(); i++)
	{
		if (slowo[i] == '(')
		{
			break;
		}
		tablica[i - 1] = slowo[i];
	}
	tablica[i - 1] = '\0';
	return tablica;
}
char* znajdz_kategorie(string slowo)
{
	char* tablica = new char[100];
	int j = 0;
	bool nawias = false;
	for (int i = 0; i < slowo.size(); i++)
	{
		if (i == (slowo.size() - 2))
		{
			break;
		}
		if (slowo[i] == '(')
		{
			nawias = true;
		}
		if (nawias == true)
		{
			tablica[j] = slowo[i + 1];
			if (slowo[i + 1] == ')')
			{
				break;
			}
			j++;
		}
	}
	tablica[j] = '\0';
	return tablica;
}
bool znajdz_uzyte(string slowo)
{
	string used = "<used>";

	if (slowo.find(used) != -1)
	{
		return true;
	}
	return false;
}
bool sprawdzone_z_bledem(string slowo)
{
	string err = "<err>";
	if (slowo.find(err) != -1)
	{
		return false;
	}
	return true;

}
bool znajdz_blad(string slowo)
{
	int i = 1;
	for (; i < slowo.size(); i++)
	{
		if ((slowo[i] < 32) || (slowo[i] > 32 && slowo[i] < 61) || (slowo[i] > 61 && slowo[i] < 63) || (slowo[i] > 62 && slowo[i] < 65) || (slowo[i] > 90 && slowo[i] < 97) || (slowo[i] > 122))
		{
			return true;
		}
	}
	return false;
}
void Kolo_Fortuny::init_ile_razy_uzyto(dane_kategorii* Dane)
{
	string used = "<used>";
	string slowo;
	int uzyte = 0;
	bool nowa_kat = false;
	int licznik;
	myfile = ifstream("hasla.txt");
	myfile.seekg(0, myfile.beg);
	//wczytywanie kategorii i hasel, sumowanie hasel nalzeacych do danej kategorii, sprawdzanie czy jakies hasla byly wczesniej wykorzystane
	for (int i = 0; i < ile_hasel; i++)
	{
		getline(myfile, slowo);

		licznik_hasel[i].dlugosc = slowo.size();
		licznik = 0;
		string kategoria = znajdz_kategorie(slowo);
		for (int j = 0; j < elementy_tablicy; j++)
		{
			if (licznik_hasel[j].kategoria == kategoria)
			{
				licznik = 1;
				nowa_kat = true;
				licznik_hasel[j].suma_hasel_z_kategorii++;
				if (slowo.find(used) != -1)
				{
					licznik_hasel[j].ile_razy_uzyte++;
				}
			}
			if (licznik_hasel[j].kategoria != kategoria)
			{
				nowa_kat = false;
			}

		}
		if (nowa_kat == false && licznik != 1)
		{

			licznik_hasel[elementy_tablicy] = Licznik(kategoria, 0, 1, licznik_hasel[i].dlugosc, 0);
			if (slowo.find(used) != -1)
			{
				licznik_hasel[elementy_tablicy].ile_razy_uzyte++;
			}

			for (poczatek; poczatek < kolejnosc; poczatek++)
			{
				Dane[poczatek].nazwa_kategorii = kategoria;
			}
			kolejnosc++;

		}
		elementy_tablicy++;

	}

	for (int a = 0; a < kolejnosc; a++)
	{
		Dane[a].uzyte = licznik_hasel[a].ile_razy_uzyte;
		Dane[a].suma = licznik_hasel[a].suma_hasel_z_kategorii;
	}

}
bool Kolo_Fortuny::ile_uzyto(string slowo, dane_kategorii* Dane)
{
	bool znajdz = znajdz_uzyte(slowo);
	string used = "<used>";
	string kategoria = znajdz_kategorie(slowo);
	bool ile_procent = true;

	for (int i = 0; i < kolejnosc; i++)
	{
		if (licznik_hasel[i].kategoria == kategoria)		//sprawdzanie uzytych hasel
		{
			if (znajdz == true)
			{
				Dane[i].uzyte++;
			}
		}
	}

	for (int i = 0; i < kolejnosc; i++)
	{

		double uzyte = Dane[i].uzyte;
		double ile = Dane[i].suma;
		double procent = (uzyte / ile);		//obliczanie ile procent hasel zostalo uzytych z danej kategorii
		licznik_hasel[i].procent = procent;
	}
	int licznik = 0;
	for (int i = 0; i < kolejnosc; i++)
	{
		if (licznik_hasel[i].procent >= 0.9)
		{
			licznik = 1;
			ile_procent = true;
		}
	}

	if (licznik == 1 && ile_procent == true)
	{
		return true;
	}
	else return false;
}

char* zresetuj_haslo(string slowo)
{

	char* tablica = new char[100];
	string used = "<used>";
	int i = 0;
	for (; i < slowo.size(); i++)
	{
		if (slowo[i] == '<')
		{
			break;
		}
		tablica[i] = slowo[i];
	}
	tablica[i] = '\0';
	return tablica;
};

void Kolo_Fortuny::reset_hasel(string slowo, dane_kategorii* Dane) //1 metoda resetowania hasel
{
	myfile = ifstream("hasla.txt");
	myfile.seekg(0, myfile.beg);
	string used = "<used>";
	string err = "<err>";
	for (int i = 0; i < ile_hasel; i++)
	{
		getline(myfile, slowo);
		if (slowo.find(used) != -1) // w pliku myfile szukamy oznaczen<used> i przepisujemy do pliku posredniego tresc przed sprawdzeniem
		{
			string slowo_nowe = zresetuj_haslo(slowo);
			reset_base << slowo_nowe << endl;
		}
	}
	myfile.close();
	reset_base.close();
	remove("hasla.txt");
	rename("hasla.reset.txt", "hasla.txt");

	for (int i = 0; i < kolejnosc; i++)
	{
		Dane[i].uzyte = 0;
		Dane[i].suma = 0;
	}
	init_ile_razy_uzyto(Dane);
}

void Kolo_Fortuny::nowa_baza(string slowo, dane_kategorii* Dane)//2 metoda resetowania hasel
{
	myfile = ifstream("hasla.txt");
	myfile.seekg(0, myfile.beg);

	myfile.close();
	new_base.close();			//zaladowanie nowej bazy hasel
	remove("hasla.txt");
	rename("hasla.nowe.txt", "hasla.txt");

	for (int i = 0; i < kolejnosc; i++)
	{
		Dane[i].uzyte = 0;
		Dane[i].suma = 0;

	}
	init_ile_razy_uzyto(Dane);
}
void Kolo_Fortuny::losuj_haslo(gracz* dane, dane_kategorii* Dane)
{
	string line;
	int opcja = cin.get();;
	string used = "<used>";
	myfile = ifstream("hasla.txt");

	if (myfile.is_open())
	{

		bool check = ile_uzyto(line, Dane);	//sprawdzanie ile procent hasel z danej kategorii zostalo wykorzystane
		polozenie++;
		if (check)
		{
			cout << "wykorzystales 90% hasel z danej kategorii" << endl;
			cout << "aby zresetowac baze hasel wcisnij 4, aby zaladowac nowa baze wcisnij 5" << endl;
			cin >> opcja;

			if (opcja == 4)
			{
				reset_hasel(line, Dane);
			}
			else if (opcja == 5)
			{
				nowa_baza(line, Dane);
			}
		}
		if (polozenie == 1)
		{
			myfile = ifstream("hasla.txt");
			myfile.seekg(0, myfile.beg);
			getline(myfile, line);		//odczytywanie danych z pliku od poczatku
			cout << line << '\n';
		}
		else
		{
			suma += licznik_hasel[polozenie - 2].dlugosc; //odczytywanie danych z pliku z poprzedniej pozycji
			myfile.seekg(suma + 2 * (polozenie - 1));
			getline(myfile, line);
			cout << line << endl;
		}


		haslo_z_pliku.tresc = znajdz_haslo(line);
		haslo_z_pliku.kategoria = znajdz_kategorie(line);
		haslo = haslo_z_pliku.tresc;


		bool notfound = sprawdzone_z_bledem(line);	//sprawdzanie czy dane haslo zawieralo wczeniej blad
		bool err = znajdz_blad(haslo_z_pliku.tresc);
		bool used = znajdz_uzyte(line);


		if (used)
		{
			temporary_file << line << endl;
			losuj_haslo(dane, Dane);
		}
		if (notfound)
		{
			if (err)
			{
				cout << "BLEDNE HASLO" << endl;
				temporary_file << line + "<err>" + "<used>" << endl;
				losuj_haslo(dane, Dane);
			}
			temporary_file << line + "<used>" << endl;
		}
		else  temporary_file << line + "<used>" << endl;


	}
	else
	{
		cout << "nie ma takiego pliku" << endl;
		exit(0);
	}
	rysuj_pole(dane, Dane);

};
void Kolo_Fortuny::rysuj_pole(gracz* dane, dane_kategorii* Dane)
{
	cout << "Haslo: " << endl;
	for (int i = 0; i < haslo.size(); ++i)
	{
		zaszyfrowane_haslo += "_";	//w miejcu hasla wyswietla sie puste pola
	}
	cout << zaszyfrowane_haslo << endl;
	cout << endl;
	zakrec_kolem(dane, Dane);
};
void Kolo_Fortuny::zakrec_kolem(gracz* dane, dane_kategorii* Dane)
{

	string tablica[wielkosc] = { "wakacje" ,"samochod","pralka","zmywarka","odkurzacz","smartfon","telewizor" };
	string wylosowane[wielkosc];	//tablica wylosowanych nagrod
	int wartosci_nagrod[wielkosc] = { 4000, 25000, 2300, 2700, 1200, 2000,3000 };

	int suma = 25;

	tab[0] = "NAGRODA";
	tab[1] = "BANKRUT";		//tablica z polami typu string
	tab[2] = "STOP";

	for (int i = 0; i < 16; i++)		//tablica z polami typu int
	{
		tablica_pol[i] = suma * (i + 1);
	}
	if (rundy == 1)
	{
		tablica_pol[16] = 500;
	}
	else if (rundy == 2)
	{
		tablica_pol[16] = 1400;
	}
	else if (rundy == 2)
	{
		tablica_pol[16] = 2000;
	}


	if (tury == 10 || odgadniete_pole == haslo.size())
	{
		przejscie(dane, Dane);
	}
	else
	{
		cout << "wcisnij  i zakrec kolem" << endl;
		sign = cin.get();
		sign = cin.get();
		if (sign != '0' && sign != '9' && sign != '8' && sign != '6')
		{
			int wybortab = (rand() % 6);		//losowanie tablicy int lub string
			if (wybortab != 1)
			{
				los = (rand() % 16);	//losowanie pola z tablicy int
				int a;
				int b;
				if (los == 0)	//dla wylosowanego pola "0" poprzednie pole wyswietli sie jako koncowe "16"
				{
					a = 16;
					b = los + 1;
				}
				else if (los == 16)		//dla wylosowanego pola "16" nastepne pole wyswietli sie jako poczatkowe "0"
				{
					b = 0;
					a = los - 1;
				}
				else
				{
					a = los - 1;
					b = los + 1;
				}
				tury++;
				cout << "runda: " << rundy << " " << "tura: " << tury << endl;
				cout << endl;
				cout << "--------" << "***********" << "--------" << endl;
				cout << "|" << tablica_pol[a] << " 	*   " << tablica_pol[los] << "   *    " << tablica_pol[b] << "|" << endl;
				cout << "--------" << "***********" << "--------" << endl;

				cout << dane[miejsce_w_tablicy_gracza].imie << " podaj spolgloske" << endl;
				cin >> spolgloska1;			//wczytywanie spolgloski
				ktora_spolgloska = *spolgloska1;

				for (int i = 0; i < 6; i++)
				{
					if (samogloski[i] == spolgloska1[0])	//sprawdzanie czy podana litera nie jest samogloska
					{
						cout << "to jest samogloska!!" << endl;
						nieudana_proba(dane, Dane);
					}
				}
				wykorzystales_spolgloske(dane, Dane);
			}
			else
			{
				los = (rand() % 2);
				cout << endl;
				int c;
				int d;
				if (los == 0)		//dla wylosowanego pola "0" poprzednie pole wyswietli sie jako koncowe "2"
				{
					c = 2;
					d = los + 1;
				}
				else if (los == 2)		//dla wylosowanego pola "2" nastepne pole wyswietli sie jako poczatkowe "0"
				{
					d = 0;
					c = los - 1;
				}
				else
				{
					c = los - 1;
					d = los + 1;
				}
				tury++;
				cout << "runda: " << rundy << " " << "tura: " << tury << endl;
				cout << endl;
				cout << "---------------" << "***************" << "---------------" << endl;
				cout << "|" << tab[c] << "		*  " << tab[los] << "    *    " << tab[d] << "|" << endl;
				cout << "---------------" << "***************" << "---------------" << endl;

				if (tab[los] == tab[0])
				{
					los = (rand() % 6);

					for (int i = 0; i < 7; i++) {

						if (tablica[los] != wylosowane[i])	//sprawdzanie czy dana nagroda nie zostala wczesniej wylosowana
						{
							for (min_miejsce_nagrod; min_miejsce_nagrod < max_miejsce_nagrod; min_miejsce_nagrod++)
							{
								wylosowane[min_miejsce_nagrod] = tablica[los];	//wpisanie nagrody do tablicy wylosowanych
							}
							nagroda = wylosowane[min_miejsce_nagrod];		//aktualna nagroda
							wartosc = wartosci_nagrod[los];	//wartosc wylosowanej nagrody
						}
						else los = (rand() % 6);
					}
					max_miejsce_nagrod++;
					cout << "nagroda: " << nagroda << " o wartosci " << wartosc << endl;
					cout << endl;

					cout << dane[miejsce_w_tablicy_gracza].imie << " podaj spolgloske" << endl;
					cin >> spolgloska2;
					ktora_spolgloska = *spolgloska2;

					for (int i = 0; i < 6; i++)
					{
						if (samogloski[i] == spolgloska2[0])	//sprawdzanie czy podana litera nie jest samogloska
						{
							cout << "to jest samogloska!!" << endl;
							nieudana_proba(dane, Dane);
						}
					}
					wykorzystales_spolgloske(dane, Dane);
				}
				else if (tab[los] == tab[1])
				{
					dane[miejsce_w_tablicy_gracza].wygrana_kwota = 0;	//wyzerowanie wygranych pieniedzy w danej rundzie
					cout << "Zostales bankrutem!" << endl;

					nieudana_proba(dane, Dane);

				}
				else if (tab[los] == tab[2])
				{
					nieudana_proba(dane, Dane);

				}
			}
		}
		else if (sign == '0')
		{
			zakup(dane, Dane);
		}
		else if (sign == '9')
		{
			uzyj_samogloski(dane, Dane);

		}
		else if (sign == '8')
		{
			znam_haslo(dane, Dane);
		}
		else if (sign == '6')
		{
			koniec(dane, Dane);
		}

	}
};
void Kolo_Fortuny::wykorzystales_spolgloske(gracz* dane, dane_kategorii* Dane)
{
	if (ktora_spolgloska == spolgloska1[0])	//jezeli spolgloska byla pobrana przy wygranej z tablicy int
	{
		bool prawda = 1;

		for (int i = 0; i < uzyte_spolgloski_max; i++)
			if (uzyte_spolgloski[i] == spolgloska1[0])	//sprawdzenie czy spolgloska nie zostala wczesniej wykorzystana
				prawda = 0;

		if (prawda == 0)
		{
			cout << dane[miejsce_w_tablicy_gracza].imie << " ta spolgloska zostala juz uzyta" << endl;
			nieudana_proba(dane, Dane);
		}
		else if (prawda == 1)
			for (uzyte_spolgloski_min; uzyte_spolgloski_min < uzyte_spolgloski_max; uzyte_spolgloski_min++)
			{
				uzyte_spolgloski[uzyte_spolgloski_min] = spolgloska1[0];		//wpisanie spolgloski do tablicy wylosowanych spolglosek
			}
		uzyte_spolgloski_max++;		//zwiekszanie miejsca w tablicy wylosowanych spolglosek
	}
	else if (ktora_spolgloska == *spolgloska2)	//jezeli spolgloska byla pobrana przy wygranej z tablicy string
	{
		bool prawda1 = 1;
		for (int i = 0; i < uzyte_spolgloski_max; i++)
		{
			if (uzyte_spolgloski[i] == spolgloska2[0])	//sprawdzenie czy spolgloska nie zostala wczesniej wykorzystana
				prawda1 = 0;
		}

		if (prawda1 == 0)
		{
			cout << dane[miejsce_w_tablicy_gracza].imie << " ta spolgloska zostala juz uzyta" << endl;
			nieudana_proba(dane, Dane);
		}
		else if (prawda1 == 1)
			for (uzyte_spolgloski_min; uzyte_spolgloski_min < uzyte_spolgloski_max; uzyte_spolgloski_min++)
			{
				uzyte_spolgloski[uzyte_spolgloski_min] = spolgloska2[0];	//wpisanie spolgloski do tablicy wylosowanych spolglosek
			}
		uzyte_spolgloski_max++;	//zwiekszanie miejsca w tablicy wylosowanych spolglosek
		zgadywanie(dane, Dane);
	}
	zgadywanie(dane, Dane);
};
void Kolo_Fortuny::nieudana_proba(gracz* dane, dane_kategorii* Dane)
{
	if (ile_osob == 1)	//jezeli 1 gracz nie odgadl pola lub hasla
	{
		cout << "sproboj jeszcze raz" << endl;
		zakrec_kolem(dane, Dane);
	}
	else
	{
		miejsce_w_tablicy_gracza = (miejsce_w_tablicy_gracza + 1) % ile_osob;	//wybor nastepnego gracza
		cout << "Tracisz kolejke, teraz Twoj ruch : " << dane[miejsce_w_tablicy_gracza].imie << endl;
		sign = cin.get();
		zakrec_kolem(dane, Dane);
	}
}

void Kolo_Fortuny::zgadywanie(gracz* dane, dane_kategorii* Dane)
{
	char wylosowana[wielkosc2] = { 'b','c','d','f','g','h','j','k','l','m','n','p','r','s','t','w','x','q','v','z' };
	int a = 0;
	int ile_razy = 0;

	for (int k = 0; k < wielkosc2; k++)
	{
		if (wylosowana[k] == spolgloska1[0])	//sprawdzanie czy litera jest spolgloska
		{

			for (int i = 0; i < haslo.size(); i++)
			{
				if (tolower(haslo[i]) == tolower(spolgloska1[0]))	//sprawdzanie czy spolgloska nalezy do hasla
				{
					ile_razy++;		//liczy ile razy spolgloska pojawia sie w hasle
					zaszyfrowane_haslo[i] = spolgloska1[0];		//wpisanie spolgloski w puste miejsce
				}
			}

			if (ile_razy != 0)	//jezeli spolgloska pojawia sie  w hasle
			{
				for (int i = 0; i < haslo.size(); i++)
				{
					cout << zaszyfrowane_haslo[i];
				}
				cout << endl;
				odgadniete_pole += ile_razy;	//ilosc odgadnietych pol
				dane[miejsce_w_tablicy_gracza].wygrana_kwota += (tablica_pol[los] * ile_razy);	//gracz otrzymuje kwote pomnozona przez ilosc miejsc, w ktorych pojawila sie spolgloska
				cout << dane[miejsce_w_tablicy_gracza].wygrana_kwota << endl;
				ile_razy = 0;
				zakrec_kolem(dane, Dane);
			}
			else
			{
				nieudana_proba(dane, Dane);
			}
		}
		else if (wylosowana[k] == spolgloska2[0])	//sprawdzanie czy litera jest spolgloska
		{
			for (int i = 0; i < haslo.size(); i++)
			{
				if (tolower(haslo[i]) == tolower(*spolgloska2))
				{
					ile_razy++;		//liczy ile razy spolgloska pojawia sie w hasle
					zaszyfrowane_haslo[i] = spolgloska2[0];		//wpisanie spolgloski w zaszyfrowane miejsce
				}
			}

			if (ile_razy != 0)	//jezeli spolgloska pojawia sie w hasle
			{
				for (int i = 0; i < haslo.size(); i++)
				{
					cout << zaszyfrowane_haslo[i];
				}
				cout << endl;
				odgadniete_pole += ile_razy;

				for (dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng; dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng < dane[miejsce_w_tablicy_gracza].max_miejsca_w_tablicy_ng; dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng++) {

					dane[miejsce_w_tablicy_gracza].nagroda_gracza[dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng] = nagroda;		//dla obecnego gracza przypisywana jest nagroda do okreslonego miejsca w tablicy nagrod
				}
				dane[miejsce_w_tablicy_gracza].max_miejsca_w_tablicy_ng++;	//zwiekszanie miejsca w tablicy nagrod

				dane[miejsce_w_tablicy_gracza].wartosc_nagrody_gracza += wartosc;	//sumowanie wartosci wygranych nagrod
				cout << dane[miejsce_w_tablicy_gracza].wartosc_nagrody_gracza << endl;

				ile_razy = 0;
				cout << endl;
				zakrec_kolem(dane, Dane);
			}
			else
			{
				nieudana_proba(dane, Dane);

			}

		}
	}

};
void Kolo_Fortuny::zakup(gracz* dane, dane_kategorii* Dane)
{

	tury++;
	cout << "suma twoich pieniedzy to: " << dane[miejsce_w_tablicy_gracza].wygrana_kwota << endl;

	if (dane[miejsce_w_tablicy_gracza].wygrana_kwota >= 200)
	{
		cout << "Jaka samogloske chcesz kupic?" << endl;
		cin >> zakupiona;
		for (int k = 0; k < 6; k++)
		{
			if (samogloski[k] == zakupiona[0])	//sprawdzanie czy litera jest samogloska
				for (dane[miejsce_w_tablicy_gracza].min_zakupionych; dane[miejsce_w_tablicy_gracza].min_zakupionych < dane[miejsce_w_tablicy_gracza].max_zakupionych; dane[miejsce_w_tablicy_gracza].min_zakupionych++)
					dane[miejsce_w_tablicy_gracza].kupione_samogloski[dane[miejsce_w_tablicy_gracza].min_zakupionych] = samogloski[k];	//wpisywanie samogloski do tablicy zakupionych samoglosek gracza
		}
		dane[miejsce_w_tablicy_gracza].max_zakupionych++;	//zwiekszanie miejsca w tablicy
		dane[miejsce_w_tablicy_gracza].kupione++;		//licznik samoglosek
		dane[miejsce_w_tablicy_gracza].wygrana_kwota - 200;	//odejmowanie kosztu jednej samogloski

		uzyj_samogloski(dane, Dane);
	}
	else cout << "nie masz pieniedzy" << endl;
	zakrec_kolem(dane, Dane);

};

void Kolo_Fortuny::uzyj_samogloski(gracz* dane, dane_kategorii* Dane)
{

	if (dane[miejsce_w_tablicy_gracza].kupione != 0)
	{
		cout << "kupione samogloski to: ";
		for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych - 1; i++)
		{
			cout << dane[miejsce_w_tablicy_gracza].kupione_samogloski[i];
		}
	}
	else
	{
		cout << "brak zakupionych samoglosek" << endl;
		zakrec_kolem(dane, Dane);
	}
	cout << endl;
	cout << "Czy chcesz wykorzystac samogloske?" << endl;
	cout << "wpisz 'tak' lub 'nie'" << endl;
	cin >> opcja;
	bool jest = 0;
	if (_stricmp(opcja, "tak") == 0)
	{
		cout << "Ktorej samogloski chcesz uzyc?" << endl;
		cin >> zakupiona;


		for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych; i++)
		{
			if (dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] == *zakupiona)		//sprawdzanie czy samogloska znajduje sie w tablicy zakupionych samoglosek danego gracza
			{
				jest = 1;
				for (int i = 0; i < haslo.size(); i++)
				{
					if (haslo[i] == *zakupiona)	//sprawdzanie czy samogloska wystepuje w hasle
						zaszyfrowane_haslo[i] = *zakupiona;	//wpisywanie samogloski do hasla
				}
				for (int i = 0; i < haslo.size(); i++)
				{
					if (haslo[i] == *zakupiona)
						odgadniete_pole++;	//zwiekszanie ilosci odgadnietych pol
				}
				for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych; i++)
				{
					if (dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] == *zakupiona)
						dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] = 0;	//zerowanie miejsca uzytej samogloski
				}
				zakrec_kolem(dane, Dane);
			}
		}

		if (jest == 0)
		{
			cout << "Nie kupiles takiej samogloski" << endl;
			zakrec_kolem(dane, Dane);
		}
	}
	else if (_stricmp(opcja, "nie") == 0)
	{
		zakrec_kolem(dane, Dane);
	}
};

void Kolo_Fortuny::znam_haslo(gracz* dane, dane_kategorii* Dane)
{
	tury++;

	cout << haslo << endl;
	cout << "podaj haslo" << endl;

	getline(cin, zgaduje);
	getline(cin, zgaduje);

	if (zgaduje == haslo)
	{
		cout << endl;
		cout << "brawo " << dane[miejsce_w_tablicy_gracza].imie << " odgadles/as haslo!" << endl;
		cout << "dostajesz bonus 1000zl" << endl;
		dane[miejsce_w_tablicy_gracza].wygrana_kwota += 1000;
		przejscie(dane, Dane);
	}
	else
	{
		cout << "To nie jest dobra odpowiedz :( " << endl;
		sign = cin.get();
		nieudana_proba(dane, Dane);
	}

};

void Kolo_Fortuny::przejscie(gracz* dane, dane_kategorii* Dane)
{
	cout << endl;
	cout << "Koniec " << rundy << " rundy" << endl;
	rundy++;
	tury = 0;

	if (rundy != 4)
	{
		nowa_runda(dane, Dane);
	}
	else
	{
		koniec(dane, Dane);
	}

};
void Kolo_Fortuny::nowa_runda(gracz* dane, dane_kategorii* Dane)

{
	int min = 0;

	if (ile_osob == 1)
	{
		cout << "w tej rundzie zdobyles " << dane[0].wygrana_kwota << "zl" << endl;
	}
	else
	{
		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].wygrana_kwota < dane[i + 1].wygrana_kwota) //ustalanie najmniejszej wygranej kwoty 
			{
				min = dane[i].wygrana_kwota;
				miejsce_w_tablicy_gracza = i;
			}
		}
		cout << endl;
		cout << dane[miejsce_w_tablicy_gracza].imie << " zdobyles/as namniej pieniedzy: " << min << " zaczynasz nastepna runde" << endl;
	}

	for (int i = 0; i < ile_osob; i++)
	{
		dane[i].calkowita_wygrana_kwota += dane[i].wygrana_kwota;	//przepisanie wygranej kwoty w danej rundzie do calkowitej wygranej kwoty gracza
		dane[i].wygrana_kwota = 0;	//zerowanie wygranej kwoty w danej rundzie
	}


	for (int i = 0; i < uzyte_spolgloski_max; i++)
	{
		uzyte_spolgloski[i] = 0;	//zerowanie tablicy wykorzystanych spolglosek
	}

	uzyte_spolgloski_max = 1;
	uzyte_spolgloski_min = 0;
	odgadniete_pole = 0;

	haslo.clear();
	zaszyfrowane_haslo.clear();

	cout << dane[miejsce_w_tablicy_gracza].imie << " wcisnij aby rozpoczac kolejna runde" << endl;
	char a;
	cin >> a;

	system("cls");
	losuj_haslo(dane, Dane);

};
void Kolo_Fortuny::koniec(gracz* dane, dane_kategorii* Dane)
{

	for (int i = 0; i < ile_osob; i++)
	{
		dane[i].calkowita_wygrana_kwota += dane[i].wygrana_kwota;	//przepisanie wygranej kwoty w danej rundzie do calkowitej wygranej kwoty gracza
	}

	int max = 0;
	for (int i = 0; i < ile_osob; i++)
	{
		if (dane[i].calkowita_wygrana_kwota > max)
			max = dane[i].calkowita_wygrana_kwota;	//ustalenie najwiekszej wygranej kwoty
	}

	for (int i = 0; i < ile_osob; i++)
	{
		if (dane[i].calkowita_wygrana_kwota == max)
			miejsce_w_tablicy_gracza = dane[i].miejsce_w_tablicy;	//ustalenie wygranego gracza
	}

	cout << "GRATULACJE! " << dane[miejsce_w_tablicy_gracza].imie << " " << "wygrywasz gre." << endl;

	cout << " gra ukonczona" << endl;
	cout << endl;
	cout << "GRACZ	| " << "KWOTA	| " << "LACZNA WARTOSC NAGROD  |" << "                 NAGRODY					" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;

	if (ile_osob == 1)
	{
		cout << dane[0].imie << setw(10) << dane[0].calkowita_wygrana_kwota << setw(13) << dane[0].wartosc_nagrody_gracza << "zl" << setw(25);

		for (int k = 0; k < dane[0].max_miejsca_w_tablicy_ng; k++)
		{
			cout << dane[0].nagroda_gracza[k] << " ";
		}

	}
	else
	{
		for (int i = 0; i < ile_osob; i++)
		{
			cout << dane[i].imie << setw(10) << dane[i].calkowita_wygrana_kwota << setw(13) << dane[i].wartosc_nagrody_gracza << "zl" << setw(25);
			for (int k = 0; k < dane[i].max_miejsca_w_tablicy_ng; k++)
			{
				cout << dane[i].nagroda_gracza[k] << " ";
			}
			cout << endl;
		}
	}


	myfile.close();
	temporary_file.close();
	remove("hasla.txt");			//usuwanie danych posrednich, koncowy zapis w pliku poczatkowym
	remove("hasla.nowe");
	remove("hasla.reset");
	rename("hasla.temp.txt", "hasla.txt");
	cout << endl;
	exit(0);
};

int main()
{
	srand(time(NULL));
	cout << "aby zakupic samogloske wcisnij 0" << endl;
	cout << "aby uzyc samogloske wcisnij 9" << endl;
	cout << "aby odgadnac haslo wcisnij 8" << endl;
	cout << endl;
	myfile = ifstream("hasla.txt");
	temporary_file = ofstream("hasla.temp.txt", ios::out);
	new_base = ifstream("hasla.nowe.txt");
	reset_base = ofstream("hasla.reset.txt", ios::out);
	Kolo_Fortuny::gracz dane[4];
	dane_kategorii Dane[10];

	Kolo_Fortuny gra;
	gra.init_ile_razy_uzyto(Dane);
	gra.losuj_kolejnosc(dane, Dane);
	return 0;
}
