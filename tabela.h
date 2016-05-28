#ifndef TABELA_HPP
#define TABELA_HPP

#include "zapytanie.h"

#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::initializer_list;
struct Join {
    Join(string _tabela):tabela(_tabela){;}
    Join(string _tabela,string _on)
        :tabela(_tabela),
          on(_on){;}
    string tabela;
    string on;
};

class Tabela
{
public:
    Tabela(const Tabela&) = delete;
    Tabela& operator=(const Tabela&) = delete;
    //Tworzy obiekt reprezentujący tabelę o nazwie _nazwa
    Tabela(string _nazwa);
    //Łączy z tabelą o nazwie _tabela przy warunku łączenia _on
    Tabela& join(string _tabela, string _on);
    //Łączy z tabelą o nazwie _tabela przy warunku łączenia: wartość kolumny kolumna_this z tabeli this->nazwa jest równa wartości kolumny kolumna_oth z _tabela
    Tabela& join(string _tabela, string kolumna_this, string kolumna_oth);
    //template<typename... Arg> Zapytanie<Arg...> select(Arg... arg);
    //template<typename Kolumny, typename Typy> Zapytanie<Typy...> select(int... kolumny);
    Zapytanie select(initializer_list<string> kolumny);
    Zapytanie select(vector<string> kolumny);
    Zapytanie select(string kolumna);
    string stworzSql() const;
    string getNazwa() const{return nazwa;}
private:
    string nazwa;
    vector<Join> polaczenia;
};
/*
template<typename... Arg> Zapytanie<Arg...> Tabela::select(Arg... arg)
{
    std::cout << "bu" << std::endl;
}
template<int... kolumny> Zapytanie<int> Tabela::select(int kolumny...)
{
    std::cout << "bu" << std::endl;
}
*/
#endif // TABELA_HPP
