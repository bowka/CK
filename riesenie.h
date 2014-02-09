#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
#include <vector>
class ZAKAZNIK{
	string meno;
	string priezvisko;
	string cisloOB;
	bool spravneSlovo(const string &slovo);
public:
	void setCeleMeno(const string priezviskoMeno);
	const string getCeleMeno();
	string getCisloOB(){ return cisloOB; };

};
class POBYT{
	ZAKAZNIK host;
	bool obsadeny;
	bool ohodnoteny;
	string typ;   //apartman,stan,vila
	string ham;//AI-all inclusive,polopenzia,plnopenzia
	string dop;//bus,vlak,letecky
	unsigned int Hod;//bodovanie vyletu
public:
	POBYT();
	POBYT(const string typ0, unsigned int hod, const string Ham, const string Dop);
	bool getObsadeny() { return obsadeny; };
	bool ubytujZakaznika(const string priezviskoMeno, const string typ0);
	bool odubytujZakaznika();
	const string getZakaznik();
	void nastavTypIzby(const string typ0, unsigned int hod, const string Ham, const string Dop);
	const string getTypIzby();
	const string getTypHam();
	const string getTypDop();
	bool getHodnotenie();
	int hodnotenie();
};
class MESTO{
	//POBYT zajazd;
	//int pocetPobytovMesta;
	string mesto;
	vector<POBYT> pobyty; // je to PRIVATE...mam to dat do PUBLIC alebo urobit getPobyty()? ak by sa to dalo do public nemohli by nastat problemy?
	//ze by k tomu mohol pristupovat hocikto? tak urobime getPobyty
public:
	MESTO(const string NazovMesta, vector<POBYT> &zoznamPobytov);
	vector<POBYT> & getPobyty();
	const string getNazov();
};

class STAT{
	string nazov;
	vector<MESTO> mesta;
	//unsigned int pocetMiest; mesta.size() 
	//vector<vector<POBYT*> > krajina;
	//MESTO city;
public:
	STAT(const string NazovStatu, vector<MESTO> &zoznamMiest);
	int pocetVsetkychPobytov();
	int pocetPobytov(const string typ, const string dop, const string str);
	int pocetVolnychPobytov(const string typ, const string dop, const string str);
	bool ubytujZakaznika(const string PriezviskoMeno, const string typPobytu, const string typDopravy, const string typStravy);
	bool ubytujZakaznika(const string PriezviskoMeno, const string Mesto, const string typPobytu, const string typDopravy, const string typStravy);
	const string zoznamMien();
	bool odhlasHosta(const string priezviskoMeno);
	int ohodnoteniePobytu();
};
#endif