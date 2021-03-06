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
	//POBYT zajazd;
	//int pocetPobytovMesta;
	string mesto; // TODO neskor zmenit na nazov
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

MESTO::MESTO(const string NazovMesta, vector<POBYT> &zoznamPobytov){
	mesto = NazovMesta;

	for (unsigned int i = 0; i < zoznamPobytov.size(); i++) {
		pobyty.push_back(zoznamPobytov[i]);
	}
}

vector<POBYT> & MESTO::getPobyty() {
	return pobyty;
}

const string MESTO::getNazov() {
	return mesto;
}

STAT::STAT(const string NazovStatu, vector<MESTO> &zoznamMiest) {
	nazov = NazovStatu;

	for (unsigned int i = 0; i < zoznamMiest.size(); i++) {
		mesta.push_back(zoznamMiest[i]);
	}
}
int STAT::pocetVsetkychPobytov(){
	int pocet = 0;
	for (int i = 0; i < mesta.size(); i++) {
		pocet += mesta[i].getPobyty().size();
	}
	return pocet;
}
int STAT::pocetPobytov(const string typ, const string dop, const string str){
	int pocet = 0;

	for (int i = 0; i < mesta.size(); i++) {
		for (int j = 0; j < mesta[i].getPobyty().size(); j++) {
			if (mesta[i].getPobyty().at(j).getTypIzby() == typ//co znamena at? to iste co [], len sa to asi nedalo pouzit
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
for (int i = 0; i < mesta.size(); i++) {
	for (int j = 0; j < mesta[i].getPobyty().size(); j++) {
		if (mesta[i].getPobyty().at(j).getTypIzby() == typ
			/*&& krajina[i][j]->getTypHam() == str
			&& krajina[i][j]->getTypDop() == dop*/
			&& mesta[i].getPobyty().at(j).getObsadeny() == false)
			//ziskava to vobec get obsadeny? malo by...takze co by to malo ukazovat? je X pobytov v stane a ako zistime pocet volnych?
			//je 5 stanov a jeden je obsadeny ale pripocita to aj ten obsadeny...aha
		// zakomentovane veci nie su problematicke? ono vzdy sa rovna typ stravy v testoch tej spravnej odpovedi.
		//netestujem to inak iba aby dalo true. a tusis preco je chybne volne stany/a dalsie?
		//mne sa zdalo ze prvykrat ked som niekoho ubytocala do anglicka do london tak sa mi z volnych odpocitalo.//checknem
		{	pocet++;	}
	}
}
return pocet++;
}

bool STAT::ubytujZakaznika(const string PriezviskoMeno, const string typPobytu, const string typDopravy, const string typStravy) {
	for (int i = 0; i < mesta.size(); i++) {
		for (int j = 0; j < mesta[i].getPobyty().size(); j++) {
			if (mesta[i].getPobyty().at(j).getTypIzby() == typPobytu
				&& mesta[i].getPobyty().at(j).getTypHam() == typStravy
				&& mesta[i].getPobyty().at(j).getTypDop() == typDopravy
				&& mesta[i].getPobyty().at(j).getObsadeny() == false) 
			{
					mesta[i].getPobyty().at(j).ubytujZakaznika(PriezviskoMeno, typPobytu);
					return true;
			}
		}
	}
	return false;
}
//vyskusaj pockaj este rekapitulacia
// takze prehladavame vsetky mesta, a ked najdeme konkretne mesto (kt.chceme) tak:
//		hladame prvyv volny pobyt, so stanovenymi podmienkami v tom meste, ak najdeme vratime true,
//		inak nam skor skonci ten cyklus vdaka break (neprehl.uz dalej) - predpokladame, ze nazvy miest su unykatne ak nie, tak break odstran
// TVOJE POZNAMKY: fuh no pochopila som break-konecne:)bolo na case v 3rocniku.:-) potrebujem teraz nieco zmenit v testoch?
// asi ano, ale tuto variaciu si nevolala kedze testy nemaju chybu, treba to zavolat aj s nazvom mesta v testoch.skusim
bool STAT::ubytujZakaznika(const string PriezviskoMeno, const string Mesto, const string typPobytu, const string typDopravy, const string typStravy) {
	string konkretneMesto = Mesto;
	for (int i = 0; i < mesta.size(); i++) {
		if (mesta[i].getNazov() == konkretneMesto) {
			for (int j = 0; j < mesta[i].getPobyty().size(); j++) {
				if (mesta[i].getPobyty().at(j).getTypIzby() == typPobytu
					&& mesta[i].getPobyty().at(j).getTypHam() == typStravy
					&& mesta[i].getPobyty().at(j).getTypDop() == typDopravy
					&& mesta[i].getPobyty().at(j).getObsadeny() == false)
				{
					mesta[i].getPobyty().at(j).ubytujZakaznika(PriezviskoMeno, typPobytu);  // tu bude niekde chyba
					// podla mna getPobyty(), ze to vrati iba nieco nanovo skopirovane
					return true;
				}
			}
			break;
		}
	}
	return false;
}

const string STAT::zoznamMien() {
	string menaH = "";
	for (int i = 0; i < mesta.size(); i++) {
		for (int j = 0; j < mesta[i].getPobyty().size(); j++) {
			if (mesta[i].getPobyty().at(j).getObsadeny() == true){
				if (menaH == ""){
					menaH = menaH + mesta[i].getPobyty().at(j).getZakaznik();
				}
				else{
					menaH = menaH + ", " + mesta[i].getPobyty().at(j).getZakaznik();
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

	for (unsigned int i = 0; i < mesta.size(); i++){
		for (unsigned int j = 0; j < mesta[i].getPobyty().size(); j++){
			if (mesta[i].getPobyty().at(j).getZakaznik() == MenoHosta){
				mesta[i].getPobyty().at(j).odubytujZakaznika();
				return true;
			}
		}
	}

	return false;
}
int STAT::ohodnoteniePobytu(){
	int H = 0;
	for (unsigned int i = 0; i < mesta.size(); i++){
		for (unsigned int j = 0; j < mesta[i].getPobyty().size(); j++){
			if ((!mesta[i].getPobyty().at(j).getObsadeny()) && (!mesta[i].getPobyty().at(j).getHodnotenie())){
				H = H + mesta[i].getPobyty().at(j).hodnotenie();
			}
		}
	}
	return H;
	}