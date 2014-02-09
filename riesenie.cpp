#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>


using namespace std;

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
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
	POBYT zajazd;
	int pocetPobytovMesta;
	string NazovMesta;
public:
	MESTO(const string NazovMesta,int pocetPobytovMesta);
};

class STAT{
	unsigned int pocetMiest;
	vector<vector<POBYT*> > krajina;
	MESTO *city;
public:
	STAT(string nazovStatu, vector<MESTO>/*Test funkcnosti gitu zoznam miest*/);
	int pocetVsetkychPobytov();
	int pocetPobytov(const string typ, const string dop, const string str);
	int pocetVolnychPobytov(const string typ, const string dop, const string str);
	bool ubytujZakaznika(const string PriezviskoMeno, const string typPobytu, const string typDopravy, const string typStravy);
	bool ubytujZakaznika(const string PriezviskoMeno, const int Mesto, const string typPobytu, const string typDopravy, const string typStravy);
	const string zoznamMien();
	bool odhlasHosta(const string priezviskoMeno);
	int ohodnoteniePobytu();
};
#endif
bool velkePismeno(const char c) {
	if (c >= 'A' && c <= 'Z'){
		return true;
	}
	else{
		return false;
	}
}
bool malePismeno(const char c){
	if (c >= 'a' && c <= 'z'){
		return true;
	}
	else{
		return false;
	}
}
bool ibaMalePismena(const string &slovo, unsigned int odKtoreho = 1) {
	for (unsigned int i = odKtoreho - 1; i < slovo.length(); i++){
		if (!malePismeno(slovo[i])){
			return false;
		}
	}
}
bool ZAKAZNIK::spravneSlovo(const string &slovo) {
	if (!velkePismeno(slovo[0]) || !ibaMalePismena(slovo, 2)){
		return false;
	}
	return true;
}

void ZAKAZNIK::setCeleMeno(const string priezviskoMeno) {
	string P = "", M = "";
	istringstream ist(priezviskoMeno);
	ist >> P >> M;
	if (spravneSlovo(P) && spravneSlovo(M)){
		priezvisko = P;
		meno = M;
	}
	else
	{
		priezvisko = "";
		meno = "";
	}
}
const string ZAKAZNIK::getCeleMeno() {
	if ((meno == "") || (priezvisko == "")){
		return "";
	}
	return meno + ' ' + priezvisko;
}

POBYT::POBYT() {
	obsadeny = false;
	typ = "vila";
	ohodnoteny = true;
	Hod = 0;//nehodnotene. pri hodnoteni  <1, 5>
	ham = "";//strava
	dop = "";//doprava
}

POBYT::POBYT(const string typ0, unsigned int hod, const string Ham, const string Dop) {
	obsadeny = false;
	typ = typ0;
	Hod = hod;
	ham = Ham;
	dop = Dop;
}
bool POBYT::getHodnotenie() {
	return ohodnoteny;
}
bool POBYT::ubytujZakaznika(const string priezviskoMeno, const string typ0) {
	if (!obsadeny){
		host.setCeleMeno(priezviskoMeno);
		obsadeny = true;
		return true;
	}
	return false;
}
const string POBYT::getZakaznik() {
	return host.getCeleMeno();
}
bool POBYT::odubytujZakaznika() {
	if (obsadeny){
		obsadeny = false;
		ohodnoteny = false;
		host.setCeleMeno("");
		return true;
	}
	return false;
}

int POBYT::hodnotenie() {
	if (obsadeny || ohodnoteny){
		return 0;//nehodnotene
	}
	else{
		ohodnoteny = true;
	}
	return Hod;
}
const string POBYT::getTypIzby() {
	return typ;
}
const string POBYT::getTypHam() {
	return ham;
}
const string POBYT::getTypDop() {
	return dop;
}
void POBYT::nastavTypIzby(const string typ0, unsigned int hod, const string Ham, const string Dop) {
	typ = typ0;
	Hod = hod;
	ham = Ham;
	dop = Dop;
}

STAT::STAT(int pocetPobytovMesta[], int velkost) {
	pocetMiest = velkost;
	krajina.resize(pocetMiest);

	for (unsigned int i = 0; i < pocetMiest; i++) {
		for (unsigned int j = 0; j < pocetPobytovMesta[i]; j++) {
			switch (j) {
			case 0:
				krajina[i].push_back(new POBYT("vila", 0, "all inclusive", "letecky"));
				break;
			case 1:
				krajina[i].push_back(new POBYT("Apartman", 0,"plnopenzia", "vlak" ));
				break;
			case 2:
				krajina[i].push_back(new POBYT("stan", 0, "polopenzia", "bus"));
				break;
			case 3:
				krajina[i].push_back(new POBYT("stan", 0, "polopenzia", "bus"));
				break;
			case 4:
				krajina[i].push_back(new POBYT("stan", 0, "polopenzia", "bus"));
				break;
			default:
				krajina[i].push_back(new POBYT("stan", 0, "polopenzia", "bus"));
			}
		}
	}
}
int STAT::pocetVsetkychPobytov(){
	/*int a = 0;
	a=pocetPobytovMesta*pocetMiest;
	return a;*/
	int pocet = 0;
	for (int i = 0; i < krajina.size(); i++) {
		pocet += krajina[i].size();
	}
	return pocet;
}
int STAT::pocetPobytov(const string typ, const string dop, const string str){
	int pocet = 0;

	for (int i = 0; i < krajina.size(); i++) {
		for (int j = 0; j < krajina[i].size(); j++) {
			if (krajina[i][j]->getTypIzby() == typ
				/*&& krajina[i][j]->getTypHam() == str
				&& krajina[i][j]->getTypDop() == dop*/)
			{
				pocet++;
			}
		}
	}
	return pocet++;
}
int STAT::pocetVolnychPobytov(const string typ, const string dop, const string str){
int pocet = 0;
for (int i = 0; i < krajina.size(); i++) {
	for (int j = 0; j < krajina[i].size(); j++) {
		

		if (krajina[i][j]->getTypIzby() == typ
			/*&& krajina[i][j]->getTypHam() == str
			&& krajina[i][j]->getTypDop() == dop*/
			&& krajina[i][j]->getObsadeny() == false)
			//&& krajina[i][j]->hodnotenie!=0)//0 je nastavena pre nehodnotene izby aka v kt.sa byva
		{	pocet++;	}
	}
}
return pocet++;
}
bool STAT::ubytujZakaznika(const string PriezviskoMeno, const string typPobytu, const string typDopravy, const string typStravy) {
	for (int i = 0; i < krajina.size(); i++) {
		for (int j = 0; j < krajina[i].size(); j++) {
			if (krajina[i][j]->getTypIzby() == typPobytu
				&& krajina[i][j]->getTypHam() == typStravy
				&& krajina[i][j]->getTypDop() == typDopravy
				&& krajina[i][j]->getObsadeny() == false){
					krajina[i][j]->ubytujZakaznika(PriezviskoMeno, typPobytu);
					return true;
			}
		}
	}
	return false;
}//pretazovanie funkcie
bool STAT::ubytujZakaznika(const string PriezviskoMeno, const int Mesto, const string typPobytu, const string typDopravy, const string typStravy) {
	unsigned int mesto = Mesto;
	for (int j = 0; j < krajina[mesto].size(); j++) {
		if (krajina[mesto][j]->getTypIzby() == typPobytu
			&& krajina[mesto][j]->getTypHam() == typStravy
			&& krajina[mesto][j]->getTypDop() == typDopravy
			&& krajina[mesto][j]->getObsadeny() == false)
		{				
			krajina[mesto][j]->ubytujZakaznika(PriezviskoMeno, typPobytu);
			return true;
		}
	}
	return false;
}
const string STAT::zoznamMien() {
	string menaH = "";
	for (int i = 0; i < krajina.size(); i++) {
		for (int j = 0; j < krajina[i].size(); j++) {
			if (krajina[i][j]->getObsadeny() == true){
				if (menaH == ""){
					menaH = menaH + krajina[i][j]->getZakaznik();
				}
				else{
					menaH = menaH + ", " + krajina[i][j]->getZakaznik();
				}
			}
		}
	}
	return menaH;
}

bool STAT::odhlasHosta(const string priezviskoMeno){

	ZAKAZNIK host;
	host.setCeleMeno(priezviskoMeno);
	string MenoHosta = host.getCeleMeno();

	for (unsigned int i = 0; i < krajina.size(); i++){
		for (unsigned int j = 0; j < krajina[i].size(); j++){
			if (krajina[i][j]->getZakaznik() == MenoHosta){
				krajina[i][j]->odubytujZakaznika();
				return true;
			}
		}
	}

	return false;
}
int STAT::ohodnoteniePobytu(){
	int H = 0;
	for (unsigned int i = 0; i < krajina.size(); i++){
		for (unsigned int j = 0; j < krajina[i].size(); j++){
			if ((!krajina[i][j]->getObsadeny()) && (!krajina[i][j]->getHodnotenie())){
				H = H + krajina[i][j]->hodnotenie();
			}
		}
	}
	return H;
	}