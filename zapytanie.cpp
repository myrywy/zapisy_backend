#include "zapytanie.h"
#include "tabela.h"
#include "bazadanych.h"

using std::cerr;
using std::endl;

Zapytanie::Zapytanie(const Tabela* _tabela, vector<string> _kolumny)
    :tabela{_tabela},
      kolumny{_kolumny}
{
}

string Zapytanie::stworzSql() const
{
    string tmp="SELECT ";
    if(kolumny.size()!=0){
        for(unsigned i=0; i<kolumny.size()-1; i++){
            tmp+=kolumny[i]+", ";
        }
        tmp+=kolumny[kolumny.size()-1];
    }
    tmp += " FROM ";
    tmp+=tabela->stworzSql();
    if(warunki.size()!=0){
        tmp += " WHERE ";
        for(unsigned i=0; i<warunki.size()-1; i++){
            tmp+=warunki[i]+" AND ";
        }
        tmp+=warunki[warunki.size()-1];
    }
    tmp+=";";
    return tmp;
}

void Zapytanie::wykonaj()
{
    StatementPtr stmt;
    string tmpSql=stworzSql();
    wyniki.resize(kolumny.size());
    std::cout << "Zapytanie: " << tmpSql << endl;
    try{
        stmt=BazaDanych::instancja()->wykonaj(tmpSql);
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL przy przetwarzaniu zapytania\n";
        std::cout << tmpSql << endl;
        std::cout << err.what() << endl;
        throw;
    }
    ResultsPtr res(stmt->getResultSet());
    if(kolumny.size()>0){
        while(res->next()){
            vector<string> w(kolumny.size());
            for(unsigned i=0; i<kolumny.size(); i++){
                try{
                    string s=kolumny[i];
                    // Oczyszczanie nazwy tabeli ze znakow "`". Bez nich, w niektorych przypadkach baza danych nie odpowie na zapytanie. Z nimi ResultSet nie rozpozna nazwy kolumny
                    size_t pos;
                    while( (pos=s.find_first_of('`'))!=string::npos){
                        s.erase(pos,1);
                    }
                    // Wyciąganie substringa po ostatniej kropce. Bez częsci przed kropką zapytanie może być niejednoznaczne. W ResultSet jest bez kropki.
                    size_t dotPos{};
                    while( (dotPos=s.find_first_of('.'))!=string::npos ){
                        s=s.substr(++dotPos);
                    }
                    w[i]=res->getString(s);
                    std::cout << "wynik " << kolumny[i] << "=" << w[i] << endl;
                }catch(sql::InvalidArgumentException err){
                    std::cout<< "Blad. Nie znaleziono pozycji " << kolumny[i] << ". Liczba wynikow: " << res->getRow() <<endl;
                }
            }
            wyniki.push_back(w);
        }
    }else{
        wyniki.clear();
    }
    aktualne=true;
}

Zapytanie::operator string()
{
    if(!aktualne){
        wykonaj();
    }
    for(vector<string> v : wyniki){
        for(string s : v){
            cout << s << endl;
        }
    }
    string tmp;
    if(wyniki.empty()){
        return "";
    }
    for(unsigned i=0; i<wyniki.size()-1; i++){
        cerr << tmp << endl;
        if(wyniki[i].empty()){
            continue;
        }
        for(unsigned j=0; j<wyniki[i].size()-1; j++){
            cerr << tmp << endl;
            tmp+=wyniki[i][j]+",";
        }
        tmp+=wyniki[i][wyniki[i].size()-1]+";";
    }

    if(wyniki[wyniki.size()-1].empty()){
        return tmp;
    }
    for(unsigned j=0; j<wyniki[wyniki.size()-1].size()-1; j++){
        tmp+=wyniki[wyniki.size()-1][j]+",";
    }
    tmp+=wyniki[wyniki.size()-1][wyniki[wyniki.size()-1].size()-1];
    return tmp;
}

Zapytanie& Zapytanie::where(string warunek){
    aktualne=false;
    warunki.push_back(warunek);
    return *this;
}

Zapytanie& Zapytanie::whereEqual(string kol1, string kol2){
    aktualne=false;
    warunki.push_back(kol1+"="+kol2);
    return *this;
}
