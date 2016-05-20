#ifndef BAZADANYCH_H
#define BAZADANYCH_H

#include "soapzapisyService.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class BazaDanych
{
public:
    BazaDanych();
    static BazaDanych* instancja();
    bool dodajProjekt(std::string przedmiotID, z1__temat t);
    bool dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t);
    bool zapiszNaProjekt(int studentId, int projektId);
    bool zapiszNaTermin(int studentId, int terminId);
    //Pobiera z bazy informacje o zapisanych na projekt studentach i zwraca ich listę w formacie csv
    string pobierzProjekt(int id);
    //Pobiera z bazy informacje o zapisanych na termin studentach i zwraca ich listę w formacie csv
    string pobierzTermin(int id);
    //Pobiera z bazy informacje o zapisanych na przedmiot studentach i zwraca ich listę w formacie csv
    string pobierzPrzedmiot(int id);
    //z1__temat infoProjekt(int projektId);
    //z1__termin infoTermin(int terminId);
    int szukajProjekt(z1__temat projekt);
    int szukajTermin(z1__termin termin);
    int wolneMiejscaProjekt(int projektId);
    int wolneMiejscaTermin(int terminId);
private:
    sql::Driver *driver;
    sql::Connection *con;
	 sql::ResultSet  *res;
    static BazaDanych* bd;
};

#endif // BAZADANYCH_H
