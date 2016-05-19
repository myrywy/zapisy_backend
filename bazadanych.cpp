#include "bazadanych.h"
#include <iostream>
BazaDanych* BazaDanych::bd=0;
using std::string;
BazaDanych::BazaDanych()
{

    try{
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "admin");
    }catch(...){
        std::cout << "Blad\n" << con << std::endl;
    }

    con->setSchema("zapisy");
    std::cout << "baza ok\n" << con << std::endl;
}

BazaDanych* BazaDanych::instancja()
{
    if(!bd){
        bd=new BazaDanych;
    }
    return bd;
}

bool BazaDanych::dodajProjekt(z1__temat t)
{
    std::cout << "dodawanie in progress" << std::endl;
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::cout << "a" << std::endl;
    stmt->execute(string("call dodajProjekt(2,'")+t.temat+string("',')")+t.opis+string("',")+string(t.miejsca)+string(",")+t.wolneMiejsca+string(")"));
    std::cout << "b" << std::endl;
    return false;
}

bool BazaDanych::dodajTermin(z1__termin)
{
    return false;
}

bool BazaDanych::zapiszNaProjekt(z1__student student, int projektId)
{
    return false;
}

bool BazaDanych::zapiszNaTermin(z1__student student, int terminId)
{
    return false;
}

string BazaDanych::pobierzProjekt(int id)
{
    return "";
}

string BazaDanych::pobierzTermin(int id)
{
    return "";
}

string BazaDanych::pobierzPrzedmiot(int id)
{
    return "";
}
/*
z1__temat BazaDanych::infoProjekt(int projektId)
{

}

z1__termin BazaDanych::infoTermin(int terminId)
{

}
*/
int BazaDanych::szukajProjekt(z1__temat projekt)
{
    return 0;
}

int BazaDanych::szukajTermin(z1__termin termin)
{
    return 0;
}

int BazaDanych::wolneMiejscaProjekt(int projektId)
{
    return 0;
}

int BazaDanych::wolneMiejscaTermin(int terminId)
{
    return 0;
}

