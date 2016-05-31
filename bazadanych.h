#ifndef BAZADANYCH_H
#define BAZADANYCH_H

#include "soapzapisyService.h"
#include "tabela.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <iostream>

using namespace std;

using StatementPtr = std::unique_ptr<sql::Statement>;
using ResultsPtr = std::unique_ptr<sql::ResultSet>;
using Id = std::string;

class BazaDanych
{
public:
    BazaDanych();
    static BazaDanych* instancja();
    bool dodajProjekt(std::string przedmiotID, z1__temat t);
    bool dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t);
    bool zapiszNaProjekt(Id studentId, Id projektId);
    bool zapiszNaTermin(Id studentId, Id terminId);
    bool dodajProwadzacego(z1__prowadzacy *p);
    bool dodajStudenta(string przedmiotId, z1__student *s);
    //Pobiera z bazy informacje o zapisanych na projekt studentach i zwraca ich listę w formacie csv
    string pobierzProjekt(string id);
    //Pobiera z bazy informacje o zapisanych na termin studentach i zwraca ich listę w formacie csv
    string pobierzTermin(string id);
    //Pobiera z bazy informacje o zapisanych na przedmiot studentach i zwraca ich listę w formacie csv
    string pobierzPrzedmiot(string id);
    bool dodajPrzedmiot(z1__przedmiot *przedmiot);
    //z1__temat infoProjekt(int projektId);
    //z1__termin infoTermin(int terminId);
    int szukajProjekt(z1__temat projekt);
    int szukajTermin(z1__termin termin);
    bool szukajProjektStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu=nullptr);
    bool szukajTerminStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu=nullptr);
    int wolneMiejscaProjekt(int projektId);
    int wolneMiejscaTermin(int terminId);
    template<typename... Args> StatementPtr procedura(std::string nazwaProcedury, Args... argumenty){
        StatementPtr stmt(con->createStatement());
        std::cout << stworzWywolanieProcedury(nazwaProcedury,argumenty...) << std::endl;
        stmt->execute(stworzWywolanieProcedury(nazwaProcedury,argumenty...));
        return stmt;
    }
    template<typename... Args> std::string stworzWywolanieProcedury(std::string nazwaProcedury, Args... argumenty){
        return "call "+nazwaProcedury+"("+argumentyProcedury(argumenty...)+")";
    }
    template<typename T> std::string argumentyProcedury(T latter){
        return "\""+std::string(latter)+"\"";
    }
    template<typename T, typename... Args> std::string argumentyProcedury(T firstArg, Args... rest){
        return "\""+string(firstArg)+"\","+argumentyProcedury(rest...);
    }
    //usuwa z "tabela" wiersz, w ktorym "kolumna" ma "wartowsc"
    StatementPtr usun(string tabela, string kolumna, string wartosc);
    StatementPtr wykonaj(string polecenieSql);
private:
    sql::Driver *driver;
    sql::Connection *con;
	 sql::ResultSet  *res;
    static BazaDanych* bd;
};

#endif // BAZADANYCH_H
