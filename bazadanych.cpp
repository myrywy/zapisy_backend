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

bool BazaDanych::dodajProjekt(std::string przedmiotID, z1__temat t)
{
    std::cerr << "dodawanie projektu do bazy" << std::endl;
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    try{
    	stmt->execute(string("call dodajProjekt("+przedmiotID+",'")+t.temat+string("','")+t.opis+string("',")+string(t.miejsca)+string(",")+t.wolneMiejsca+string(")"));
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    std::cerr << "Dodano" << endl;
    return true;
}

bool BazaDanych::dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t)
{
    std::cerr << "dodawanie terminu do bazy" << std::endl;
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    try{
    	stmt->execute(
				string("call dodajTermin("+przedmiotID+",'")
				+t.dzien+string("','")
				+t.godzinaOd+string("',")
				+t.godzinaDo+string(",")
				+std::to_string(t.miejsca)+string(",")
				+salaID+string(")")
			);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    std::cerr << "Dodano" << endl;
    return true;
}

bool BazaDanych::zapiszNaProjekt(int studentId, int projektId)
{
    return false;
}

bool BazaDanych::zapiszNaTermin(int studentId, int terminId)
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

