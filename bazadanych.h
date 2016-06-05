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

class ZlaLiczbaKolumn : public std::exception {const char* what() const noexcept{return "Zla liczba kolumn\n";}};

class BazaDanych
{
public:
    BazaDanych();
    /**
     * Zwraca wskaźnik do jedynego obiektu klasy BazaDanych. Jeśli obiekt taki nie istnieje to jest tworzony.
     * @return wskaźnik do obiektu klasy BazaDanych
     */
    static BazaDanych* instancja();
    /**
     * Dodaje temat projektu do bazy danych
     *
     */
    bool dodajProjekt(std::string przedmiotID, z1__temat t);
    bool dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t);
    bool edytujProjekt(string projektId, z1__temat t);
    bool edytujTermin(string terminId, z1__termin t);
    bool zapiszNaProjekt(Id studentId, Id projektId);
    bool zapiszNaTermin(Id studentId, Id terminId);
    bool wypiszZProjektu(Id studentId, Id projektId);
    bool wypiszZTerminu(Id studentId, Id terminId);
    bool importujProjekty(Id przedmiotId, string dane);
    bool importujTerminy(Id przedmiotId, string dane);
    bool importujStudentow(Id przedmiotId, string dane);
    bool dodajProwadzacego(z1__prowadzacy *p);
    bool zmienProwadzacego(string idProwadzacego, z1__prowadzacy *daneProwadzacego);
    bool dodajStudenta(string przedmiotId, z1__student *s);
    bool edytujStudenta(Id studentId, z1__student s);
    bool zmienOpcje(z1__opcja opcja);
    //Pobiera z bazy informacje o zapisanych na projekt studentach i zwraca ich listę w formacie csv
    string pobierzProjekt(string id);
    //Pobiera z bazy informacje o zapisanych na termin studentach i zwraca ich listę w formacie csv
    string pobierzTermin(string id);
    //Pobiera z bazy informacje o zapisanych na przedmiot studentach i zwraca ich listę w formacie csv
    string pobierzPrzedmiot(string id);
    bool dodajPrzedmiot(z1__przedmiot *przedmiot, string emailProwadzacego);
    //z1__temat infoProjekt(int projektId);
    //z1__termin infoTermin(int terminId);
    int szukajProjekt(z1__temat projekt);
    int szukajTermin(z1__termin termin);
    bool szukajProjektStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu=nullptr);
    bool szukajTerminStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu=nullptr);
    int wolneMiejscaProjekt(int projektId);
    int wolneMiejscaTermin(int terminId);
    /**
     * Funckja wywołująca procedurę o zdefiniowaną w bazie danych.
     * \param nazwaProcedury nazwa procedury taka jaką zdefiniowano w bazie
     * \param argumenty argumenty zdefiniowanej procedury. Ich liczba powinna być zgodna z liczbą argumentów procedury w bazie. W przeciwnym razie wywołanie zakończy się zgłoszeniem wyjątku sql::SQLException. Argumenty są konwertowane do std::string zatem muszą być typu o zdefiniowanej konwersji do std::string.
     *  \return inteligenty wskaźnik do obiektu sql::Statement (po wywołaniu procedury).
     */
    template<typename... Args> StatementPtr procedura(std::string nazwaProcedury, Args... argumenty){
        StatementPtr stmt(con->createStatement());
        std::cout << stworzWywolanieProcedury(nazwaProcedury,argumenty...) << std::endl;
        stmt->execute(stworzWywolanieProcedury(nazwaProcedury,argumenty...));
        return stmt;
    }
    /**
     *  Funckja tworząca zapytanie MySQL wywołujące procedurę o nazwie nazwaProcedury z argumentmi takimi jak kolejne argumnety funkcji
     * \return String zawierający zapytanie MySQL wywołujące procedurę CALL nazwaProcedury(argiment1, argumen2 ...);
     */
    template<typename... Args> std::string stworzWywolanieProcedury(std::string nazwaProcedury, Args... argumenty){
        return "call "+nazwaProcedury+"("+argumentyProcedury(argumenty...)+")";
    }
    /**
     *  Jednoargumentowa ("brzegowa") wersja szablonowej funkcji pomocniczej do łączenia argumentów w łańcuch.
     */
    template<typename T> std::string argumentyProcedury(T latter){
        return "\""+std::string(latter)+"\"";
    }
    /**
     *  Funkcja pomocnicza łacząca argumenty w łańcuch, oddzielonych przecinkami argumentów w cudzysłowach. Funkcja konwertuje argumenty do obiektów std::string.
     */
    template<typename T, typename... Args> std::string argumentyProcedury(T firstArg, Args... rest){
        return "\""+string(firstArg)+"\","+argumentyProcedury(rest...);
    }
    /**
     * Usuwa wiersz z tabeli w bazie danych. Umożliwia wyłącznie proste operacje usuwania, w których usunięte zostają wszystkie wiersze, dla których odpowiedania kolumna ma ustaloną wartość.
     * \param tabela nazwa tabeli, z której ma zostać usunięty wiersz
     * \param kolumna nazwa kolumny, której wartości decydują o usunięciu wiersza
     * \param wartosc wartość, z którą porównywana jest zawartość kolunmny kolumna w danym wierszu; jeśli wartości te są równe to wiersz zostanie usunięty
     * \return inteligentny wskaźnik do obiektu sql::Statement zapytania usuwającego (zapytanie to przed zwróceniem jest już wykonane w bazie)
     */
    StatementPtr usun(string tabela, string kolumna, string wartosc);
    /**
     * Funkcja dodająca wiersz do tabeli. Na przykład dodaj("nazwa_tabeli",{"nazwa_kolumny1","nazwa_kolumny2},{"wartosc1","wartosc2"}) wykona zapytanie INSERT INTO `nazwa_tabeli` (`nazwa_kolumny1`,`nazwa_kolumny2`)VALUES('wartosc1','wartosc2')
     * \param tabela nazwa tabeli w bazie, do której zostanie dodany wiersz
     * \param kolumny lista nazw kolumn, których wartości są definiowane w kolejnym argumncie
     * \param wartosci lista wartości kolumn w dodawanym wierszu. Ich kolejność odpowiada kolejności nazw kolumn w poprzednim argumencie
     * \return inteligentny wskaźnik do obiektu sql::Statement zapytania usuwającego (zapytanie to przed zwróceniem jest już wykonane w bazie)
     */
    StatementPtr dodaj(string tabela, initializer_list<string> kolumny, initializer_list<string> wartosci);
    /**
     * Funkcja aktualizująca wiersz w tabeli.
     * \param tabela nazwa tabeli w bazie, w której zostanie zmieniony wiersz
     * \param kolumny lista nazw kolumn, których wartości są definiowane w kolejnym argumncie
     * \param wartosci lista wartości kolumn w zmienianym wierszu. Ich kolejność odpowiada kolejności nazw kolumn w poprzednim argumencie
     * \return inteligentny wskaźnik do obiektu sql::Statement zapytania usuwającego (zapytanie to przed zwróceniem jest już wykonane w bazie)
     */
    StatementPtr aktualizuj(string tabela, string id, initializer_list<string> kolumny, initializer_list<string> wartosci);
    /**
     * Wykonuje polecenie MySQL
     * @param polecenieSql łańcuch z poleceniem MySQL w formie tekstowej.
     * @return inteligentny wskaźnik do obiektu sql::Statement zapytania usuwającego (zapytanie to przed zwróceniem jest już wykonane w bazie)
     */
    StatementPtr wykonaj(string polecenieSql);
    /**
     * Dzieli łańcuch znaków na podłańcuchy.
     * \param str dzielony łańcuch znaków
     * \param c znak będący punktem podziału
     * \return wektor łańcuchów powstałych w wyniku podziału bez punktów podziału (tj. bez znaku c)
     */
    static vector<string> splitString(const string& str, char c);
    /**
     * parsuje łańcuch znaków w formacie csv
     * @param str parsowany łańcuch
     * @param col znak oddzielający od siebie kolumny
     * @param row znak oddzielający od siebie wiersze
     * @return wektor wierszy, gdzie wiersz to wektor łańcuchów zawierających wartości kolejnych kolumn w tym wierszu
     */
    static vector< vector< string > > parseCsv(const string& str, char col, char row);
private:
    sql::Driver *driver;
    sql::Connection *con;
	 sql::ResultSet  *res;
    static BazaDanych* bd;
};

inline string enq(string s){return "\""+s+"\"";}

#endif // BAZADANYCH_H
