#include <iostream>

#include "testovacieFunkcie.h"
#include "riesenie.h"

using namespace std;

void  testyPobytu() {
	nastavSledovanieSkupiny("Testy Pobytu");

	ZAKAZNIK host;
	testEqual("", host.getCeleMeno(), "Meno zakaznika");
	host.setCeleMeno("Achbergerova Katarina");
	testEqual("Katarina Achbergerova", host.getCeleMeno(), "Meno zakaznika");
	host.setCeleMeno(",Katarina");
	testEqual("", host.getCeleMeno(), "Meno zakaznika");
	host.setCeleMeno("Achbergerova,");//pokial je zadane iba krstne bez priezviska a naopak
	testEqual("", host.getCeleMeno(), "Meno zakaznika");//meno nebude zadane vobec
	host.setCeleMeno("Miklosko Fero");
	testEqual("Fero Miklosko", host.getCeleMeno(), "Meno zakaznika");
	host.setCeleMeno("Miklosko fero");//pokial je nevyhovujuco zadane meno s malym pismenom
	testEqual("", host.getCeleMeno(), "Meno zakaznika");
	host.setCeleMeno("miklosko fero");//pokial je nevyhovujuco zadane meno s malym pismenom
	testEqual("", host.getCeleMeno(), "Meno zakaznika");

	POBYT zajazd;
	testFalse(zajazd.getObsadeny(), "Obsadenost");
	testFalse(zajazd.odubytujZakaznika(), "Obsadenost");
	testEqual("", zajazd.getZakaznik(), "Meno zakaznika");
	testTrue(zajazd.ubytujZakaznika("Achbergerova Marta","vila"), "Nastahovanie");
	testFalse(zajazd.ubytujZakaznika("Bihari Mario","apartman"), "Nastahovanie");
	testTrue(zajazd.getObsadeny(), "Test obsadenosti");
	testEqual("Marta Achbergerova", zajazd.getZakaznik(), "Meno zakaznika");
	testTrue(zajazd.odubytujZakaznika(), "Obsadenost");
	testFalse(zajazd.odubytujZakaznika(), "Obsadenost");
	testEqual("", zajazd.getZakaznik(), "Meno zakaznika");
	testFalse(zajazd.getObsadeny(), "Obsadenost");

	zhodnotenieVysledkov();
}
void testyHodnotenia(){
	nastavSledovanieSkupiny("Testy hodnotenia");

	POBYT stan;
	stan.nastavTypIzby("stan", 3, "polopenzia", "bus");
	testEqual("stan", stan.getTypIzby(), "Typ ubytovania");
	testEqual(stan.hodnotenie(), 0, "nehodnotene");
	testTrue(stan.ubytujZakaznika("Achbergerova Katarina","stan"), "Nastahovanie");
	testEqual("Katarina Achbergerova", stan.getZakaznik(), "Meno zakaznika");
	testTrue(stan.odubytujZakaznika(), "Odubytovanie");
	testEqual(stan.hodnotenie(), 3, "hodnotenie zakaznika");
	testTrue(stan.ubytujZakaznika("Misklosko Fero","stan"), "Nastahovanie");
	testEqual("Fero Misklosko", stan.getZakaznik(), "Meno zakaznika");
	testTrue(stan.odubytujZakaznika(), "Vystahovanie");
	testEqual(stan.hodnotenie(), 3, "hodnotenie neutral");

	POBYT apartman;
	apartman.nastavTypIzby("Apartman", 4, "plnopenzia", "vlak");
	testTrue(apartman.ubytujZakaznika("Javorcsikova Janka","apartman"), "Nastahovanie");
	testEqual("Janka Javorcsikova", apartman.getZakaznik(), "Meno zakaznika");
	testEqual(apartman.hodnotenie(), 0, "nehodnotene");
	testTrue(apartman.odubytujZakaznika(), "Vystahovanie");
	testEqual(apartman.hodnotenie(), 4, "Ohodnotena izba");
	testEqual("Apartman", apartman.getTypIzby(), "Typ ubytovania");


	POBYT vila;
	apartman.nastavTypIzby("vila", 5, "all inclusive", "letecky");
	testEqual("vila", vila.getTypIzby(), "Typ ubytovania");
	testTrue(vila.ubytujZakaznika("Javorcsikova Danka","vila"), "Nastahovanie");
	testEqual("Danka Javorcsikova", vila.getZakaznik(), "Meno zakaznika");
	testEqual(vila.hodnotenie(), 0, "nehodnotene");
	testTrue(vila.odubytujZakaznika(), "Odubytovanie");
	testEqual(apartman.hodnotenie(), 0, "Ohodnotenie apartmanu pri pobyte vo vile(nezmysel)");

	zhodnotenieVysledkov();
}
void testyStatu(){
	nastavSledovanieSkupiny("testovanie statov");
	int SR[] = { 2, 3, 4, 1, 2, 2 };
	STAT Slovensko(SR, 6);
	testEqual(Slovensko.pocetVsetkychPobytov(), 14, "SLOVENSKO=Vsetky pobyty");
	testEqual(Slovensko.pocetPobytov("stan", "bus", "polopenzia"), 3, "stany");
	testEqual(Slovensko.pocetPobytov("Apartman", "vlak", "plnopenzia"), 5, "Apartmany");
	testEqual(Slovensko.pocetPobytov("vila", "letecky", "all inclusive"), 6, "vila");

	testTrue(Slovensko.ubytujZakaznika("Bednarova Majka", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Slovensko.ubytujZakaznika("Drobna Maria", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Slovensko.ubytujZakaznika("Malkova Iveta", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Slovensko.ubytujZakaznika("Stastna Katka", "stan", "bus", "polopenzia"), "ubytovanie do stanu");
	testTrue(Slovensko.ubytujZakaznika("Bednarova Karolina", "Apartman", "vlak", "plnopenzia"), "ubytovanie do apartnam");
	testEqual(Slovensko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 2, "Volne stany");
	testEqual(Slovensko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 4, "Volne apartmany");
	testEqual(Slovensko.pocetVolnychPobytov("vila", "letecky", "all inclusive"), 3, "Volne vily");
	

	int GB[] = { 1,2,3,4,5,6,7};
	STAT Anglicko(GB, 7);
	testEqual(Anglicko.pocetVsetkychPobytov(), 28, "ANGLICKO======Vsetky pobyty");
	testEqual(Anglicko.pocetPobytov("stan", "bus", "polopenzia"), 15, "stany");
	testEqual(Anglicko.pocetPobytov("Apartman", "vlak", "plnopenzia"), 6, "Apartmany");
	testEqual(Anglicko.pocetPobytov("vila", "letecky", "all inclusive"), 7, "vila");
	testTrue(Anglicko.ubytujZakaznika("Dikosova Veronika", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Anglicko.ubytujZakaznika("Drakna Maria", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Anglicko.ubytujZakaznika("Majkova Ivetka", "vila", "letecky", "all inclusive"), "ubytovanie do vily");
	testTrue(Anglicko.ubytujZakaznika("Stastny Peter", "stan", "bus", "polopenzia"), "ubytovanie do stanu");
	testTrue(Anglicko.ubytujZakaznika("Bednar Karol", "Apartman", "vlak", "plnopenzia"), "ubytovanie do apartnam");
	testTrue(Anglicko.ubytujZakaznika("Bednar Michael", "Apartman", "vlak", "plnopenzia"), "ubytovanie do apartnam");
	testTrue(Anglicko.ubytujZakaznika("Bednar Dusan", "Apartman", "vlak", "plnopenzia"), "ubytovanie do apartnam");

	testEqual(Anglicko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 14, "Volne stany");
	testEqual(Anglicko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 3, "Volne apartmany");
	testEqual(Anglicko.pocetVolnychPobytov("vila", "letecky", "all inclusive"), 4, "Volne vily");

	int HR[] = { 2, 6 };
	STAT Chorvatsko(HR, 2);
	testEqual(Chorvatsko.pocetVsetkychPobytov(), 8, "CHORVATSKO======Vsetky pobyty");
	testEqual(Chorvatsko.pocetPobytov("stan", "bus", "polopenzia"), 4, "stany");
	testEqual(Chorvatsko.pocetPobytov("Apartman", "vlak", "plnopenzia"),2, "Apartmany");
	testEqual(Chorvatsko.pocetPobytov("vila", "letecky", "all inclusive"), 2, "vila");
	testTrue(Chorvatsko.ubytujZakaznika("Bednar Dusanko", "Apartman", "vlak", "plnopenzia"), "ubytovanie do apartmanu");
	testEqual(Chorvatsko.pocetVolnychPobytov("vila", "letecky", "all inclusive"), 2, "Volne vilu");
	testEqual(Chorvatsko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 4, "Volne stany");
	testEqual(Chorvatsko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 1, "Volne apartmany");

	int Evil[] = { 1 };
	STAT Peklo(Evil, 1);
	testEqual(Peklo.pocetVolnychPobytov("vila", "letecky", "all inclusive"), 1, "PEKLO======Volne vily");
	testTrue(Peklo.ubytujZakaznika("Javorcsikova Danka", "vila", "letecky", "all inclusive"), "PEKLO---------");
	testEqual(Peklo.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 0, "PEKLO=Volne apartmany");
	
	zhodnotenieVysledkov();

}
void testyUbytovania(){
	nastavSledovanieSkupiny("Testy ubytovania v state");

	int BG[] = { 2, 3, 4, 1, 2, 2 };
	STAT Belgicko(BG, 6);
	testEqual(Belgicko.zoznamMien(), "", "Mena hosti");
	testEqual(Belgicko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 3, "Volne izby");
	testEqual(Belgicko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 5, "Volne apartman");
	testEqual(Belgicko.pocetVolnychPobytov("vila", "letecky", "all inclusive"), 6, "Volne vily");
	testTrue(Belgicko.ubytujZakaznika("To John", "stan", "bus", "polopenzia"), "Ubytovanie");
	testEqual(Belgicko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 2, "Volne izby");
	testEqual(Belgicko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 5, "Volne apartman");
	testTrue(Belgicko.ubytujZakaznika("To Adam", "Apartman", "vlak", "plnopenzia"), "Ubytovanie");
	testEqual(Belgicko.zoznamMien(), "Adam To, John To", "Mena hosti");
	testTrue(Belgicko.ubytujZakaznika("To Iveta", "Apartman", "vlak", "plnopenzia"), "Ubytovanie");
	testEqual(Belgicko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 2, "Volne izby");
	testEqual(Belgicko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 3, "Volne apartman");
	testTrue(Belgicko.ubytujZakaznika("To Eva", "Apartman", "vlak", "plnopenzia"), "Ubytovanie");
	testEqual(Belgicko.zoznamMien(), "Adam To, Iveta To, John To, Eva To", "Mena hosti");
	

	zhodnotenieVysledkov();
}
void testyOdhlaseniaAHodnotenia(){
	nastavSledovanieSkupiny("Testy ubytovania v State");

	int SR[] = { 2, 3, 4, 1, 2, 2 };
	STAT Slovensko(SR, 6);
	testTrue(Slovensko.ubytujZakaznika("Smith John", "stan", "bus", "polopenzia"), "Ubytovanie");
	testTrue(Slovensko.ubytujZakaznika("Smith Adam", "Apartman", "vlak", "plnopenzia"), "Ubytovanie");
	testTrue(Slovensko.ubytujZakaznika("Smith Peter", "stan", "bus", "polopenzia"), "Ubytovanie");
	testTrue(Slovensko.ubytujZakaznika("Smith Dave", "Apartman", "vlak", "plnopenzia"), "Ubytovanie");
	testTrue(Slovensko.ubytujZakaznika("Smith Eva", "stan", "bus", "polopenzia"), "Ubytovanie");

	testEqual(Slovensko.zoznamMien(), "Adam Smith, Dave Smith, John Smith, Peter Smith, Eva Smith", "Test mien");
	testEqual(Slovensko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 0, "Volne izby");
	testEqual(Slovensko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 3, "Volne apartman");
	testTrue(Slovensko.odhlasHosta("Smith Peter"), "Odhlasenie");
	testEqual(Slovensko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 1, "Volne izby");
	testEqual(Slovensko.zoznamMien(), "Adam Smith, Dave Smith, John Smith, Eva Smith", "Test mien");
	testTrue(Slovensko.odhlasHosta("Smith Adam"), "Odhlasenie");
	testEqual(Slovensko.pocetVolnychPobytov("stan", "bus", "polopenzia"), 1, "Volne izby");
	testEqual(Slovensko.zoznamMien(), "Dave Smith, John Smith, Eva Smith", "Test mien");
	testTrue(Slovensko.odhlasHosta("Smith John"), "Odhlasenie");
	testEqual(Slovensko.pocetVolnychPobytov("Apartman", "vlak", "plnopenzia"), 4, "Volne apartman");
	testEqual(Slovensko.ohodnoteniePobytu(), 0, "neohodnoteny pobyt");

	zhodnotenieVysledkov();
}
