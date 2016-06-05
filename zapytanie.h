#ifndef ZAPYTANIE_HPP
#define ZAPYTANIE_HPP

#include <vector>
#include <string>

using std::string;
using std::vector;
using std::initializer_list;

class Tabela;

class Zapytanie {
public:
    //Zapytanie(const Tabela& _tabela, initializer_list<string> _kolumny);
    Zapytanie(const Tabela *_tabela, vector<string> _kolumny);
    Zapytanie& where(string warunek);
    Zapytanie& whereEqual(string kol1, string kol2);
    string stworzSql() const;
    void wykonaj();
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
