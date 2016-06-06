#ifndef TABELA_HPP
#define TABELA_HPP

#include "zapytanie.h"

#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::initializer_list;
/**
 * @brief Struktura Join reprezentuje łączenie tabeli
 */
struct Join {
    Join(string _tabela):tabela(_tabela){;}
    Join(string _tabela,string _on)
        :tabela(_tabela),
          on(_on){;}
    /**
     * @brief nazwa tabeli, z którą ma nastąpić łączenie (część zapytania między JOIN, a ON)
     */
    string tabela;
    /**
     * @brief warunek łączenia (część zapytania po ON)
     */
    string on;
};

/**
 * @brief Klasa Tabela reprezentuje lub połączenie tabel, z któych można tworzyć zaputania SELECT. Obiekt klasy musi zawierać nazwę. Tylko dla tabeli z prawidłową nazwą tabeli istniejącej w bazie danych można tworzyć poprawne zapytania. Opcjonalnie można do niego dodawać obiekty typu Join z nazwami innych tabel.
 */
class Tabela
{
public:
    Tabela(const Tabela&) = delete;
    Tabela& operator=(const Tabela&) = delete;
    /*
     * Tworzy obiekt reprezentujący tabelę o nazwie _nazwa
     */
    Tabela(string _nazwa);
    /**
     * @brief Łączy z tabelą o nazwie _tabela przy warunku łączenia _on
     * @param _on warunek łączenia. Nazwa tabeli w zapytaniu sql przyjmie postać "nazwa JOIN _tabela ON _on"
     * @return referencja do obiektu tabela, na rzecz którego jest wykonywana. Umożliwia składanie zapytań Tabela("nazwa").join(...).join(...).join(...)....
     */
    Tabela& join(string _tabela, string _on);
    /**
     * @brief Łączy z tabelą o nazwie _tabela przy warunku łączenia: wartość kolumny kolumna_this z tabeli this->nazwa jest równa wartości kolumny kolumna_oth z _tabela. W zapytaniu nazwa tabeli przyjmie postać "nazwa JOIN _tabela ON kolumna_this = kolumna_oth"
     * @param _tabela nazwa tabeli, z którą ma być połączona bieżąca tabela
     * @param kolumna_this nazwa kolumny w tabeli reprezentowanej przez obiekt, na rzecz którego metoda jest wywoływana, której wartość ma być równa wartowści w kolumnie kolumna_oth tabeli o nazwie_tabela
     * @param kolumna_oth nazwa kolumny w tabeli o nazwie _tabela, której wartość ma być równa kolumnie kolumna_this
     * @return referencja do obiektu tabela, na rzecz którego jest wykonywana. Umożliwia składanie zapytań Tabela("nazwa").join(...).join(...).join(...)....
     */
    Tabela& join(string _tabela, string kolumna_this, string kolumna_oth);
    /**
     * @brief Umożliwia tworzenie zapytania o wartości kolumn tabeli (lub połączonych tabel). Zwraca obiekt klasy Zapytanie umożliwiający specyfikacje warunków, które mają być spełnione przez wiersze zwracane w wyniku zapytania.
     * @param kolumny nazwy kolumn, których wartości mają być zwrócone
     * @return obiekt klasy Zapytanie reprezentujący zapytanie SQL typu SELECT o wartości kolumn kolumny tabeli (lub połączonych tabel) reprezentowanej przez dany obiekt klasy Tabela
     */
    Zapytanie select(initializer_list<string> kolumny);
    /**
     * @brief Umożliwia tworzenie zapytania o wartości kolumn tabeli (lub połączonych tabel). Zwraca obiekt klasy Zapytanie umożliwiający specyfikacje warunków, które mają być spełnione przez wiersze zwracane w wyniku zapytania.
     * @param kolumny nazwy kolumn (oddzielone spacjami), których wartości mają być zwrócone
     * @return obiekt klasy Zapytanie reprezentujący zapytanie SQL typu SELECT o wartości kolumn kolumny tabeli (lub połączonych tabel) reprezentowanej przez dany obiekt klasy Tabela
     */
    Zapytanie select(vector<string> kolumny);
    /**
     * @brief Umożliwia tworzenie zapytania o wartości kolumn ytabeli (lub połączonych tabel). Zwraca obiekt klasy Zapytanie umożliwiający specyfikacje warunków, które mają być spełnione przez wiersze zwracane w wyniku zapytania.
     * @param kolumna nazwy kolumn, której wartości mają być zwrócone
     * @return obiekt klasy Zapytanie reprezentujący zapytanie SQL typu SELECT o wartości kolumn kolumny tabeli (lub połączonych tabel) reprezentowanej przez dany obiekt klasy Tabela
     */
    Zapytanie select(string kolumna);
    /**
     * @brief funkcja pomocnicza wykorzystywana przez Zapytanie, zwraca nazwę tabeli wraz z połączeniami z innymi tabelami np. "nazwa_tabeli JOIN nazwa2 ON k1=k2..."
     */
    string stworzSql() const;
    string getNazwa() const{return nazwa;}
private:
    string nazwa;
    vector<Join> polaczenia;
};
#endif // TABELA_HPP
