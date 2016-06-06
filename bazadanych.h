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

/**
 * @brief ZlaLiczbaKolumn - klasa wyjątków zgłaszanych jeśli liczba kolumn zwróconych przez bazę nie zgadza się z liczbą kolumn w zapytaniu.
 */
class ZlaLiczbaKolumn : public std::exception {const char* what() const noexcept{return "Zla liczba kolumn\n";}};


/**
 * @brief Klasa BazaDanych służy do wykonywania operacji na bazie danych zapisy. Udostępnia metody do wykonywania specyficznych czynności jak dodawanie, usuwanie, modyfikowanie prowadzących/temtów/terminów itp. oraz ogólne metody ułatwiające korzystanie z najbardziej podstawowych funkcji SQL: dodawanie, usuwanie, aktualizowanie rekordu w tabeli, wywoływanie zdefiniowanej w bazie procedury.
 */
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
     * Dodaje temat projektu do bazy danych, przypisuje go do przedmiotu o id przedmiotID
     */
    bool dodajProjekt(std::string przedmiotID, z1__temat t);
    /**
     * Dodaje termin do bazy danych, przypusuje go do przedmiotu o id przedmiotID
     */
    bool dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t);
    /**
     * Zmienia dane projektu o id projektId w bazie
     */
    bool edytujProjekt(string projektId, z1__temat t);
    /**
     * Zmienia dane projektu o id projektId w bazie
     */
    bool edytujTermin(string terminId, z1__termin t);
    /**
     * @brief zapiszNaProjekt zapisuje studenta na projekt, zmniejsza liczbę miejsc w projekcie
     * @param studentId id studenta (w tabeli student w bazie danych), który będzie zapisany na projekt
     * @param projektId id projetku (w tabeli projekt w bazie danych), do którego będzie zapisany student
     * @return true jeśli operacja zapisania się powiodła, false w przeciwnym wypadku
     */
    bool zapiszNaProjekt(Id studentId, Id projektId);
    /**
     * @brief zapiszNaTermin zapisuje studenta na termin, zmniejsza liczbę wolnych miejsc w terminie
     * @param studentId id studenta (w tabeli student w bazie danych), który będzie zapisany na termin
     * @param terminId id terminu (w tabeli termin w bazie danych), do którego będzie zapisany student
     * @return true jeśli operacja zapisania się powiodła, false w przeciwnym wypadku
     */
    bool zapiszNaTermin(Id studentId, Id terminId);
    /**
     * @brief wypiszZProjektu wypisuje studenta z projektu, zwiększa liczbę miejsc w projekcie
     * @param studentId id studenta (w tabeli student w bazie danych), który będzie wypisany z projekt
     * @param projektId id projetku (w tabeli projekt w bazie danych), do którego będzie zapisany student
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool wypiszZProjektu(Id studentId, Id projektId);
    /**
     * @brief wypiszZTerminu wypisuje studenta z terminu, zwiększa liczbę miejsc w terminie
     * @param studentId id studenta (w tabeli student w bazie danych), który będzie wypisany z terminu
     * @param terminId id terminu (w tabeli termin w bazie danych), do którego będzie zapisany student
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool wypiszZTerminu(Id studentId, Id terminId);
    /**
     * @brief importujProjekty importuje projekty do przedmiotu
     * @param przedmiotId id przedmiotu, do którego będą przypisane projektu
     * @param dane łańcuch znaków z danymi w formacie temat;opis;liczba_miejsc\\n
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool importujProjekty(Id przedmiotId, string dane);
    /**
     * @brief importujTerminy importuje terminy do projektu
     * @param przedmiotId id przedmiotu, do którego będą przypusane terminy
     * @param dane łańcuch znaków z danymi w formacie dzień;godzina_od;godzina_do;liczba_miejsc;sala\\n
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool importujTerminy(Id przedmiotId, string dane);
    /**
     * @brief importujStudentow importuje studentów do przedmiotu. Nie usuwa studentów, którzy wcześniej byli zapisani do przedmiotu. Nie zapisuje nowego studenta jeśli jest już student o takim samym numerze indeksu zapisany na przedmiot.
     * @param przedmiotId id przedmiotu, do którego będą przypisani studenci
     * @param dane łańcuch znaków z danymi studentów w formacie imie;nazwisko;nr_indeksu\\n
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool importujStudentow(Id przedmiotId, string dane);
    /**
     * @brief dodaje prowadzącego do bazy danych
     * @param p dane prowadzącego
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool dodajProwadzacego(z1__prowadzacy *p);
    /**
     * @brief Zmienia dane prowadzącego o danym id
     * @param idProwadzacego id prowadzącego w tabeli prowadzacy w bazie danych
     * @param daneProwadzacego nowe dane prowadzacego
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool zmienProwadzacego(string idProwadzacego, z1__prowadzacy *daneProwadzacego);
    /**
     * @brief dodaje studenta do danego przedmiotu. Student nie może istniec nieprzypisany do żadnego przedmiotu. Jeśli student o danym numerze indeksu już istnieje to tworzone jest tylko nowe przypisanie do przedmiotu.
     * @param przedmiotId id przedmiotu, na który jest zapisywany student
     * @param s dane studenta
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool dodajStudenta(string przedmiotId, z1__student *s);
    /**
     * @brief Zmienia dane studenta
     * @param studentId id studenta, którego dane mają zostać zmienione
     * @param s nowe dane studneta
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool edytujStudenta(Id studentId, z1__student s);
    /**
     * @brief zmienia wartość opcji w bazie danych. Opcja o danej nazwie musi istnieć w bazie.
     * @param opcja obiekt zawierający nazwę i nową wartość opcji
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool zmienOpcje(z1__opcja opcja);
    /**
     * @brief usuwa studenta z przedmiotu. Usuwa wszystkie przypisania studenta do projektów i tematów tego przedmiotu. Jeśli student nie jest przypisany do żadnego innego przedmiotu to usuwa studenta z bazy.
     * @param studentId id studenta, który ma być wypisany z przedmiotu
     * @param przedmiotId id przedmiotu, z którego student ma być wypisany
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool usunStudentaZPrzedmiotu(Id studentId, Id przedmiotId);
    /**
     * @brief usuwa wszystkich studentów z przedmiotu. Wykorzystywana jest przy tym funkcja usunStudentaZPrzedmiotu, usuwane są także przypisania do projektów i terminów oraz ci studenci, którzy nie są przypisani do żadnego innego przedmiotu.
     * @param przedmiotId id przedmiotu, z którego mają zostać usunięci wszyscy studenci
     * @return true jeśli uda się usunąć się wszystkich studentów, false w przeciwnym wypadku
     */
    bool usunWszystkichZPrzedmiotu(Id przedmiotId);
    /**
     * @brief usuwa przedmiot, wszystkie projekty i terminy przypisane do tego projektu oraz wywołuje usunWszystkichZPrzedmiotu(przedmiotId).
     * @param przedmiotId przedmiot, który ma zostać usunięty
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool usunPrzedmiot(Id przedmiotId);
    /**
     * @brief usuwa z bazy prowadzącego oraz wszystkie jego przedmioty
     * @param prowadzacyId id prowadzącego, który ma zostać usunięty
     * @return true jeśli operacja się powiodła, false w przeciwnym wypadku
     */
    bool usunProwadzacego(Id prowadzacyId);
    /**
     * Pobiera z bazy informacje o zapisanych na projekt studentach i zwraca ich listę w formacie csv
     */
    string pobierzProjekt(string id);
    /**
     * Pobiera z bazy informacje o zapisanych na termin studentach i zwraca ich listę w formacie csv
     */
    string pobierzTermin(string id);
    /**
     * Pobiera z bazy informacje o zapisanych na przedmiot studentach i zwraca ich listę w formacie csv
     */
    string pobierzPrzedmiot(string id);
    /**
     * Dodaje przedmiot do bazy danych, dodaje przypisanie przedmiotu do prowadzącego o emailu emailProwadzacego
     */
    bool dodajPrzedmiot(z1__przedmiot *przedmiot, string emailProwadzacego);
    /**
     * @brief sprawdza, czy student jest zapisany do jakiegoś projektu w danym przedmiocie
     * @param idStudenta id studenta
     * @param idPrzedmiotu id przedmiotu
     * @param idProjektu jeśli nie nullptr to we wskazywanym obiekcie std::string jest zapisywane id projektu, na który student jest zapisany (z danego przedmiotu). Jeśli nie ma takiego przedmiotu to pusty string ("")
     * @return true jeśli student jest zapisany na projkt z tego przedmiotu, false w przeciwnym wypadku
     */
    bool szukajProjektStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu=nullptr);
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

/**
 * @brief enq pomocnicza funkcja otaczająca zawartość łańcucha znaków znakami "
 * @param s - łańcuch znaków
 * @return "\""+s+"\""
 */
inline string enq(string s){return "\""+s+"\"";}

#endif // BAZADANYCH_H
