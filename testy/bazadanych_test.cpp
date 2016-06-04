#define BOOST_TEST_MODULE BazaDanych_test
#include <boost/test/included/unit_test.hpp>
#include "../bazadanych.h"
#include "test_utils.hpp"
#include <iostream>
#include "../zapisy.nsmap"        // XML namespace mapping table (only needed once at the global level)

BOOST_AUTO_TEST_SUITE (baza)

BOOST_AUTO_TEST_CASE (parseCsv_test)
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

BOOST_AUTO_TEST_CASE (dodajStudenta)
{
    auto baza=BazaDanych::instancja();
    z1__student s;
    s.imie="Imie";
    s.nazwisko="Nazwisko";
    s.index="999999";
    string przedmiotId="1";
    baza->dodajStudenta(przedmiotId,&s);
    string studentId=Tabela("student").select("id").whereEqual("`index`",s.index);
    BOOST_REQUIRE(! studentId.empty());
    string b_przedmiotId=Tabela("student_przedmiot").select("przedmiot_id").whereEqual("student_id",studentId);
    BOOST_CHECK_MESSAGE(przedmiotId==b_przedmiotId,"Nie odnaleziono przypisania studenta do przedmiotu");
    BOOST_CHECK_MESSAGE(baza->usun("student_przedmiot","student_id",studentId),"Nie udało się usunąć relacji studenta z przedmiotem");
    BOOST_CHECK_MESSAGE(baza->usun("student","id",studentId),"Nie udało się usunąć studenta");
}

BOOST_AUTO_TEST_SUITE_END( )
