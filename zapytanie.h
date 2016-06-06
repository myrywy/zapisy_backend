#ifndef ZAPYTANIE_HPP
#define ZAPYTANIE_HPP

#include <vector>
#include <string>

using std::string;
using std::vector;
using std::initializer_list;

class Tabela;
/**
 * @brief Klasa reprezentująca zapytanie typu SELECT kolumny FROM tabela WHERE warunki[1], warunki[2]...; przy czym tabela może być połączeniem kilku tabel w bazie patrz klasa Tabela
 */
class Zapytanie {
public:
    Zapytanie(const Tabela *_tabela, vector<string> _kolumny);
    /**
     * @brief dodaje warunek do wektora warunków
     * @param warunek dowolny warunek w postaci łańcucha znaków. Powinien być zgodny ze składnią MySQL
     * @return  referencja do obiektu, na rzecz którego metoda została wywołana
     */
    Zapytanie& where(string warunek);
    /**
     * @brief whereEqual dodaje warunek kol1 = kol2. kol1 i kol2 mogą być nazwami kolumny lub wartościami, jeśli są wartościami to powinny zaczynać się i kończyć znakiem ' lub ", jeśli są nazwami kolumn to w niektórych przypadkach powinny zaczynać się i kończyć znakiem ` (jeśli nazwa kolumny koliduje ze słowem kluczowym MySQL np. index, select).
     * @param kol1 lewa strona równości w warunku.
     * @param kol2 prawa strona rózności w warunku
     * @return referencja do obiektu, na rzecz którego metoda została wywołana
     */
    Zapytanie& whereEqual(string kol1, string kol2);
    /**
     * @brief Tworzy zapytanie MySQL w formie łańcucha znaków: SELECT kolumny FROM tabela WHERE warunki[1], warunki[2]...;
     */
    string stworzSql() const;
    /**
     * @brief wykonuje zapytanie SELECT kolumny FROM tabela WHERE warunki[1], warunki[2]...; Zapisuje wiersze zwrócone przez bazę w wektorze wyniki.
     */
    void wykonaj();
    /**
     * @brief operator konwersji na typ string. Zwraca wynik zapytania. Jeśli zapytanie nie było wcześniej wykonane to wykonuje zapytanie.
     */
    operator string();
    unsigned liczbaWynikow(){return wyniki.size();}
private:
    const Tabela* tabela;
    vector<string> warunki;
    vector<string> kolumny;
    vector< vector< string > > wyniki;
    bool aktualne{false};

};

#endif // ZAPYTANIE_HPP
