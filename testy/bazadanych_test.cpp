#define BOOST_TEST_MODULE BazaDanych_test
#include <boost/test/included/unit_test.hpp>
#include "../bazadanych.h"
#include "test_utils.hpp"
#include <iostream>
#include "../zapisy.nsmap"        // XML namespace mapping table (only needed once at the global level)

BOOST_AUTO_TEST_SUITE (baza)

struct StaleTestowe{
    StaleTestowe() : baza(BazaDanych::instancja()){
        przedmiotId="1";
        z1__prowadzacy prowadzacy;
        prowadzacy.admin=true;
        prowadzacy.email="test_email_prowadzacego_1@test.test";
        prowadzacy.haslo="test_haslo";
        prowadzacy.imie="test_imie";
        prowadzacy.nazwisko="test_nazwisko";
        BOOST_CHECK_NO_THROW(baza->dodajProwadzacego(&prowadzacy));
        prowadzacyId=Tabela("prowadzacy").select("id").whereEqual("email",enq(prowadzacy.email));
        BOOST_REQUIRE_MESSAGE(!prowadzacyId.empty(),"Błąd. Nie udało się zainicjalizować prowadzącego do testów");
        z1__przedmiot przedmiot;
        przedmiot.nazwa="test_przedmiot_1";
        przedmiot.typ="3";
        przedmiotId=Tabela("prowadzacy_przedmioty").select("przedmiot_id").whereEqual("prowdzacy_id",prowadzacyId);
        if(przedmiotId.empty()){
            baza->dodajPrzedmiot(&przedmiot,prowadzacy.email);
        }
        przedmiotId=Tabela("prowadzacy_przedmioty").select("przedmiot_id").whereEqual("prowdzacy_id",prowadzacyId);
        BOOST_REQUIRE_MESSAGE(!przedmiotId.empty(),"Nie udało się utworzyć przedmiotu testowego");
    }
    ~StaleTestowe(){
        baza->usun("prowadzacy_przedmioty","prowdzacy_id",prowadzacyId);
        baza->usun("przedmiot","id",przedmiotId);
        baza->usun("prowadzacy","id",prowadzacyId);
        baza->usun("prowadzacy_rola","prowadzacy_id",prowadzacyId);
    }
    BazaDanych* baza;
    string przedmiotId;
    string prowadzacyId;
};

BOOST_AUTO_TEST_CASE (parseCsv_split_test)
{
    string s1="a;b;c\nd;e;f";
    vector< vector<string> > v1{{"a","b","c"},{"d","e","f"}};
    vector<string> v2{"a","b","c"};
    vector<string> ev{""};
    vector< vector<string> > evv;
    BOOST_CHECK(BazaDanych::splitString("",',')==ev);
    BOOST_CHECK(BazaDanych::splitString(",",',')==(vector<string>({"",""})));
    BOOST_CHECK(BazaDanych::splitString("a,b,c",',')==v2);


    BOOST_CHECK(BazaDanych::parseCsv("",',',';')==(vector<vector<string> >({{""}})));
    BOOST_CHECK(BazaDanych::parseCsv(s1,';','\n')==v1);
}

BOOST_FIXTURE_TEST_CASE (dodajStudenta,StaleTestowe)
{
    z1__student s;
    s.imie="Imie";
    s.nazwisko="Nazwisko";
    s.index="999999";
    BOOST_CHECK(baza->dodajStudenta(przedmiotId,&s));
    //To zapytanie nie doda kolejnego studenta bo index musi być unikatowy, ale nie może rzucić wyjątku
    BOOST_CHECK_NO_THROW(baza->dodajStudenta(przedmiotId,&s));
    string studentId=Tabela("student").select("id").whereEqual("`index`",s.index);
    BOOST_REQUIRE(! studentId.empty());
    string b_przedmiotId=Tabela("student_przedmiot").select("przedmiot_id").whereEqual("student_id",studentId);
    BOOST_CHECK_MESSAGE(przedmiotId==b_przedmiotId,"Nie odnaleziono przypisania studenta do przedmiotu.");
    BOOST_CHECK_MESSAGE(baza->usun("student_przedmiot","student_id",studentId),"Nie udało się usunąć relacji studenta z przedmiotem.");
    BOOST_CHECK_MESSAGE(baza->usun("student","id",studentId),"Nie udało się usunąć studenta.");
    b_przedmiotId=Tabela("student_przedmiot").select("przedmiot_id").whereEqual("student_id",studentId);
    BOOST_CHECK_MESSAGE(b_przedmiotId.empty(),"Przypisanie studenta do przedmiotu pozostało w bazie po usunięciu.");
    studentId=Tabela("student").select("id").whereEqual("`index`",s.index);
    BOOST_CHECK_MESSAGE(studentId.empty(),"Student pozostał w bazie po usunięciu.");

}

BOOST_FIXTURE_TEST_CASE ( dodajProjekt, StaleTestowe )
{
    z1__temat t;
    BOOST_CHECK_NO_THROW(baza->dodajProjekt("",t));
    t.miejsca="2";
    t.opis="opis";
    t.wolneMiejsca="1";
    t.temat="temat";
    BOOST_REQUIRE_MESSAGE(baza->dodajProjekt(przedmiotId,t),"Nie udało się dodać projektu");
    string b_projektId=Tabela("temat").select("id").whereEqual("miejsca",t.miejsca).whereEqual("temat",t.temat).whereEqual("opis",t.opis);
    BOOST_CHECK_MESSAGE(!b_projektId.empty(),"Projektu nie ma w bazie po dodaniu.");
    string b_przedmiotId=Tabela("temat").select("przedmiot_id").whereEqual("id",b_projektId);
    BOOST_CHECK_MESSAGE(!b_przedmiotId.empty(),"Nie odnaleziono przypisania przedmiotu do tematu");
    BOOST_CHECK_MESSAGE(b_przedmiotId==przedmiotId,"Niepoprawne przypisania przedmiotu do tematu");
    BOOST_CHECK_MESSAGE(baza->usun("temat","id",b_projektId),"Nie udało się usunąć tematu");
    b_przedmiotId=Tabela("temat").select("id").whereEqual("id",b_projektId);
    BOOST_CHECK_MESSAGE(!b_projektId.empty(),"Projektu nie ma w bazie po dodaniu.");
}

BOOST_FIXTURE_TEST_CASE ( dodajTermin, StaleTestowe )
{
    z1__termin t;
    t.dzien="poniedzialek";
    t.godzinaDo="00:00";
    t.godzinaOd="00:00";
    t.miejsca=1;
    t.nrSali="000.TEST";
    BOOST_REQUIRE_MESSAGE(baza->dodajTermin(przedmiotId,"", t),"Nie udało się dodać terminu");
    string b_terminId=Tabela("termin").select("id").whereEqual("godzina_od",enq(t.godzinaOd))
            .whereEqual("godzina_do",enq(t.godzinaDo))
            .whereEqual("miejsca",to_string(t.miejsca))
            .whereEqual("dzien",enq(t.dzien));
    BOOST_CHECK_MESSAGE(!b_terminId.empty(),"Terminu nie ma w bazie po dodaniu");
    string b_termin_salaId = Tabela("termin").select("sala_id").whereEqual("id",b_terminId);
    string b_nrSali=Tabela("sala").select("numer").whereEqual("id",b_termin_salaId);
    BOOST_CHECK_MESSAGE(b_nrSali==t.nrSali,"Błąd w przypisanu sali do terminu");
    BOOST_CHECK_MESSAGE(baza->usun("termin","id",b_terminId),"Nie udało się usunąć terminu");
    BOOST_CHECK_MESSAGE(baza->usun("sala","id",b_termin_salaId),"Nie udało się usunąć sali");
}

BOOST_FIXTURE_TEST_CASE ( dodaj_usun_test , StaleTestowe )
{
    BOOST_REQUIRE_MESSAGE(isWhite(' ') && isWhite('\n') && isWhite('\t')
                          && (! isWhite('a')) && (! isWhite('X'))
                          ,"Funkcja pomocnicza isWhite nie działa zgodnie z oczekiwaniami");
    BOOST_REQUIRE(sqlCmp("",""));
    BOOST_REQUIRE(sqlCmp(" "," "));
    BOOST_REQUIRE(sqlCmp(" ","  "));
    BOOST_REQUIRE(sqlCmp(" ;"," ; "));
    BOOST_REQUIRE(sqlCmp(" ;   "," ;       "));
    BOOST_REQUIRE(sqlCmp(" select    *  \nwhere                x  =   y ; ","select * where x=y"));

    string testNumer="9999.test";
    BOOST_CHECK_NO_THROW(baza->dodaj("sala",{"numer","max_miejsc"},{testNumer,"1"}));
    string b_salaId=Tabela("sala").select("id").whereEqual("numer",enq(testNumer));
    BOOST_CHECK_MESSAGE(!b_salaId.empty(),"Brak dodanego rekordu w bazie");
    BOOST_CHECK_NO_THROW(baza->usun("sala","id",b_salaId));
    b_salaId=Tabela("sala").select("id").whereEqual("numer",enq(testNumer));
    BOOST_CHECK_MESSAGE(b_salaId.empty(),"Nie udało się usunąć rekordu z bazy");
}

BOOST_FIXTURE_TEST_CASE ( zapiszNaProjekt_test, StaleTestowe)
{

}

BOOST_AUTO_TEST_SUITE_END( )
