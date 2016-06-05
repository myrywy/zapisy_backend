#include "tabela.h"

using std::cerr;
using std::endl;

Tabela::Tabela(string _nazwa)
    :nazwa(_nazwa),
      polaczenia{}
{
}

Tabela &Tabela::join(string _tabela, string _on)
{
    polaczenia.push_back({_tabela,_on});
    return *this;
}

Tabela &Tabela::join(string _tabela, string kolumna_this, string kolumna_oth)
{
    polaczenia.push_back({
                          _tabela,
                          nazwa+"."+kolumna_this+"="+_tabela+"."+kolumna_oth
                         });
    return *this;
}

Zapytanie Tabela::select(initializer_list<string> kolumny)
{
    return select(vector<string>(kolumny));
}

Zapytanie Tabela::select(vector<string> kolumny)
{
    return Zapytanie(this, kolumny);
}

Zapytanie Tabela::select(string kolumna)
{
    return select(vector<string>(1,kolumna));
}

string Tabela::stworzSql() const
{
    string tmp(nazwa);
    tmp+=" ";
    for(Join j : polaczenia){
        cerr<<endl<<"tmp: "<<endl;
        tmp+= " JOIN ";
        tmp+=j.tabela;
        tmp+=" ON ";
        tmp+=j.on;
        tmp+=" ";
        cerr<<endl<<tmp<<endl;
    }
    return tmp;
}
