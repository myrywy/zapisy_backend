#include "bazadanych.h"
#include <iostream>
#include "zapytanie.h"

BazaDanych* BazaDanych::bd=0;

using std::string;
using std::cerr;
using std::endl;

BazaDanych::BazaDanych()
{

    try{
    driver = get_driver_instance();
    //con = driver->connect("tcp://127.0.0.1:3306", "root", "admin");
    con = driver->connect("tcp://192.168.0.13:3306", "root", "admin");
    }catch(...){
        std::cout << "Blad\n" << con << std::endl;
    }

    con->setSchema("zapisy");
    std::cout << "baza ok\n" << con << std::endl;
    std::cout << "test";
    Tabela t("dupa");
    std::cout << "e1" << endl;
    std::cout << "Autozapytanie: \n" << endl;
    t.join("innatabela","id","inneid");
    t.join("jeszczeinna", "dupa=cycki");
    vector<string> kolsy{"hmpf"};
    Zapytanie z{t.select(kolsy)};
    z.where("cos=cos_innege");
    z.whereEqual("cla","dla");
    std::cout << "e2" <<endl;
    std::cout << z.stworzSql() << endl;
    //cerr<<Tabela("t1").join("t2","id_z_t2_w_t1","id").select("k1").whereEqual("k3","g4")<<endl;
}

BazaDanych* BazaDanych::instancja()
{
    if(!bd){
        bd=new BazaDanych;
    }
    return bd;
}

bool BazaDanych::dodajProjekt(std::string przedmiotID, z1__temat t)
{
    std::cerr << "dodawanie projektu do bazy" << std::endl;
    StatementPtr stmt(con->createStatement());
    try{
    	stmt->execute(string("call dodajProjekt("+przedmiotID+",'")+t.temat+string("','")+t.opis+string("',")+string(t.miejsca)+string(",")+t.wolneMiejsca+string(")"));
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    std::cerr << "Dodano" << endl;
    return true;
}

bool BazaDanych::dodajTermin(std::string przedmiotID, std::string salaID, z1__termin t)
{
    std::cerr << "dodawanie terminu do bazy" << std::endl;
    StatementPtr stmt(con->createStatement());
    try{
    	stmt->execute(
				string("call dodajTermin("+przedmiotID+",'")
				+t.dzien+string("','")
				+t.godzinaOd+string("',")
				+t.godzinaDo+string(",")
				+std::to_string(t.miejsca)+string(",")
				+salaID+string(")")
			);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    std::cerr << "Dodano" << endl;
    return true;
}

bool BazaDanych::zapiszNaProjekt(Id studentId, Id projektId)
{
    try{
        procedura("zapiszProjekt",studentId, projektId);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    return true;
}

bool BazaDanych::zapiszNaTermin(Id studentId, Id terminId)
{
    try{
        procedura("zapiszTermin",studentId, terminId);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    return true;
}

bool BazaDanych::dodajProwadzacego(z1__prowadzacy *p)
{
    try{
        procedura("dodajProwadzacego",p->email, p->haslo,p->imie,p->nazwisko);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }catch(...){
        cerr << "Nierozpoznany wyjatek. " << endl;
    }

    return true;
}

bool BazaDanych::dodajStudenta(string przedmiotId, z1__student *s)
{
    try{
        procedura("dodajStudenta",s->imie,s->nazwisko,s->index);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
    }
    try{
        string studentId=Tabela("student").select("id").whereEqual("`index`",s->index);
        procedura("dodajStudentaDoPrzedmiotu",studentId,przedmiotId);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
    }
    return true;
}

string BazaDanych::pobierzProjekt(int id)
{
    return "";
}

string BazaDanych::pobierzTermin(int id)
{
    return "";
}

string BazaDanych::pobierzPrzedmiot(int id)
{
    return "";
}
int BazaDanych::szukajProjekt(z1__temat projekt)
{
    return 0;
}

int BazaDanych::szukajTermin(z1__termin termin)
{
    return 0;
}

bool BazaDanych::szukajProjektStudenta(std::string idStudenta, std::string idPrzedmiotu, std::string *idProjektu)
{
    std::cerr << "Sprawdzanie czy student " << idStudenta << " nie ma tematu na przedmiocie " << idPrzedmiotu << ". " << std::endl;
    string tmpIdProjektu=Tabela("student_temat").join("temat","id_temat","id").select("id_temat").whereEqual("id_student",idStudenta).whereEqual("przedmiot_id",idPrzedmiotu);
    std::cerr << "tmpIdProjektu: " << tmpIdProjektu << endl;
    if(tmpIdProjektu.size()==0 || tmpIdProjektu==" "){
        return false;
    }else{
        if(idProjektu){
            *idProjektu=tmpIdProjektu;
        }
        return true;
    }
}

int BazaDanych::wolneMiejscaProjekt(int projektId)
{
    return 0;
}

int BazaDanych::wolneMiejscaTermin(int terminId)
{
    return 0;
}

StatementPtr BazaDanych::usun(string tabela, string kolumna, string wartosc)
{
    return wykonaj(
                "DELETE FROM `zapisy`.`"+tabela+"` WHERE `"+kolumna+"`='"+wartosc+"';"
                );
}

StatementPtr BazaDanych::wykonaj(string polecenieSql)
{
    StatementPtr stmt=StatementPtr(con->createStatement());
    cerr << " Wykonywanie polecenia \n" << polecenieSql << endl;
    stmt->execute(polecenieSql);
    return stmt;
}

