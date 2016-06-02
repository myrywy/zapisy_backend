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

bool BazaDanych::edytujProjekt(string projektId, z1__temat t)
{
    std::cout << "edutuj projetk: " << endl;
    try{
        Tabela st("student_temat");
        Zapytanie studentTemat = st.select("id");
        studentTemat.whereEqual("id_temat",projektId);
        std::cout<< "sql: " << studentTemat.stworzSql() << endl;
        studentTemat.wykonaj();
        int wolne=std::stoi(t.miejsca)-studentTemat.liczbaWynikow();
        std::cout << "wolne: " << wolne << endl;
        if(wolne<0){
            return false;
        }
        std::cout << "edytowanie" << endl;
        aktualizuj("temat",projektId,{"temat","miejsca","opis","wolne_miejsca"},{t.temat, t.miejsca, t.opis, std::to_string(wolne)});
        std::cout << "ok.";
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL \n";
        std::cerr << err.what() << endl;
        return false;
    }catch(std::exception err){
        std::cerr << "Nieznany blad. Zignorowano \n";
        std::cerr << err.what() << endl;
        return false;
    }catch(...){
        cout << "Nieznany blad. Zignorowano."<<endl;
        return false;
    }
    return true;
}

bool BazaDanych::edytujTermin(string terminId, z1__termin t)
{
    try{
        string salaId=Tabela("sala").select("id").whereEqual("numer",t.nrSali);
        if(salaId.empty()){
            dodaj("sala",{"numer"},{t.nrSali});
            salaId=Tabela("sala").select("id").whereEqual("numer",t.nrSali);
            if(salaId.empty()){
                return false;
            }
        }
        aktualizuj("termin",terminId,{"dzien","godzina_od","godzina_do","miejsca","sala_id"},{t.dzien, t.godzinaDo, t.godzinaOd, std::to_string(t.miejsca), salaId});
     }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL \n";
        std::cerr << err.what() << endl;
        return false;
    }catch(std::exception err){
        std::cerr << "Nieznany blad. Zignorowano \n";
        std::cerr << err.what() << endl;
        return false;
    }catch(...){
        cout << "Nieznany blad. Zignorowano."<<endl;
        return false;
    }
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

bool BazaDanych::wypiszZProjektu(Id studentId, Id projektId)
{
    try{
        procedura("wypiszZProjektu",studentId, projektId);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    return true;
}

bool BazaDanych::wypiszZTerminu(Id studentId, Id terminId)
{
    try{
        procedura("wypiszZTerminu",studentId, terminId);
    }catch(sql::SQLException err){
        std::cerr << "Przechwycono wyjatek SQL\n";
        std::cerr << err.what() << endl;
        return false;
    }
    return true;
}

bool BazaDanych::dodajProwadzacego(z1__prowadzacy *p)
{
    cerr << "DODAJ PROWADZACEGO " << endl;
    try{
        procedura("dodajProwadzacego",p->email, p->haslo,p->imie,p->nazwisko);
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return false;
    }

    try{
        string pid=Tabela("prowadzacy").select("id").whereEqual("email","\""+p->email+"\"");
        cout << "pid: " << pid << endl;
        string rid;
        if(p->admin){
            rid=Tabela("rola").select("id").where("opis='ROLE_ADMIN'");
            cout << "rid: " << rid << endl;
            procedura("dodajRoleProwadzacego",pid,rid);
        }
/*
        rid=Tabela("rola").select("id").where("opis='ROLE_USER'");
        cout << "ridu: " << rid << endl;
        procedura("dodajRoleProwadzacego",pid,rid);*/
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return false;
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

string BazaDanych::pobierzProjekt(string id)
{

    try{
       string s=Tabela("student_temat").join("student","id_student","id").join("temat","id_temat","id").select({"imie","nazwisko","`index`","temat"}).whereEqual("przedmiot_id",id);
        return s;
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return "";
    }
}

string BazaDanych::pobierzTermin(string id)
{

    try{
       string s=Tabela("student_termin").join("student","id_student","id").join("termin","id_termin","id").join("sala","sala_id=sala.id").select({"imie","nazwisko","`index`","dzien","godzina_od","godzina_do","numer"}).whereEqual("przedmiot_id",id);
        return s;
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return "";
    }
}

string BazaDanych::pobierzPrzedmiot(string id)
{
    try{
       string s=Tabela("student_przedmiot").join("student","student_id","id").select({"imie","nazwisko","`index`"}).whereEqual("przedmiot_id",id);
        return s;
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return "";
    }
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

StatementPtr BazaDanych::dodaj(string tabela, initializer_list<string> kolumny, initializer_list<string> wartosci)
{
    string sqlInsert="INSERT INTO `zapisy`.`"
            +tabela
            +"`(";
    for(string s : kolumny){
        sqlInsert+="`"+s+"`,";
    }
    //Na końcu stringa jest niepotrzebny przecinek, chyba że lista kolumn jest pusta
    if(sqlInsert[sqlInsert.size()-1]==','){
        sqlInsert.erase(sqlInsert.size()-1,1);
    }
    sqlInsert+=")VALUES(";

    for(string s : wartosci){
        sqlInsert+="'"+s+"',";
    }
    //Na końcu stringa jest niepotrzebny przecinek, chyba że lista wartosci jest pusta
    if(sqlInsert[sqlInsert.size()-1]==','){
        sqlInsert.erase(sqlInsert.size()-1,1);
    }
    sqlInsert+=");";
    return wykonaj(sqlInsert);
}

StatementPtr BazaDanych::aktualizuj(string tabela, string id, initializer_list<string> kolumny, initializer_list<string> wartosci)
{
    string sqlUpdate="UPDATE `zapisy`.`"
            +tabela
            +"` SET ";
    vector<string> col(kolumny);
    vector<string> val(wartosci);
    if(col.size()!=val.size()){
        std::cout << "Liczba kolumn i wartosci sie nie zgadzaja." << endl;
        throw ZlaLiczbaKolumn();
    }
    for(unsigned i=0; i<col.size();i++){
        std::cout << sqlUpdate << endl;
        sqlUpdate+="`"+col[i]+"`"
                +"='"+val[i]
                +((i==(col.size()-1))?"'":"', ");
    }
    sqlUpdate+=" WHERE `id`='"+id+"';";
    std::cout << sqlUpdate << endl;
    return wykonaj(sqlUpdate);
}

StatementPtr BazaDanych::wykonaj(string polecenieSql)
{
    StatementPtr stmt=StatementPtr(con->createStatement());
    std::cout << " Wykonywanie polecenia \n" << polecenieSql << endl;
    stmt->execute(polecenieSql);
    return stmt;
}

vector<string> BazaDanych::splitString(const string &str, char c)
{
    vector<string> res;
    string::const_iterator p=str.cbegin();
    string::const_iterator k=str.cbegin();
    string::const_iterator begin=str.cbegin();
    string::const_iterator end=str.cend();
    for( ; k!=end; k++){
        if(*k==c ){
            res.push_back(str.substr(p-begin,k-p));
            p=k+1;
        }
    }
    res.push_back(str.substr(p-begin,k-p));
    return res;
}

vector<vector<string> > BazaDanych::parseCsv(const string &str, char col, char row)
{
    vector<vector<string> > res;
    vector<string> tmp=splitString(str,row);
    for(string& s : tmp){
        res.push_back(splitString(s,col));
    }
    return res;
}



bool BazaDanych::dodajPrzedmiot(z1__przedmiot *przedmiot)
{
    try{
        procedura("dodajPrzedmiot",przedmiot->nazwa,przedmiot->typ);
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return false;
    }
    return true;
}


bool BazaDanych::zmienProwadzacego(string idProwadzacego, z1__prowadzacy *daneProwadzacego)
{
    string rolaAdminId=Tabela("prowadzacy_rola").join("rola","rola_id","id").select("prowadzacy_rola.id").whereEqual("prowadzacy_id",idProwadzacego).whereEqual("opis","'ROLE_ADMIN'");
    if(rolaAdminId.empty()){
        if(daneProwadzacego->admin){
            try{
                string adminId=Tabela("rola").select("id").whereEqual("opis","'ROLE_ADMIN'");
                dodaj("prowadzacy_rola",{"prowadzacy_id","rola_id"},{idProwadzacego,adminId});
            }catch(...){
                cout << "Nieznany blad. Zignorowano."<<endl;
                return false;
            }
        }
    }else{
        if(! daneProwadzacego->admin){
            try{
                usun("prowadzacy_rola","id",rolaAdminId);
            }catch(...){
                cout << "Nieznany blad. Zignorowano."<<endl;
                return false;
            }
        }
    }
    try{
        aktualizuj("prowadzacy",idProwadzacego,{"email","haslo","imie","nazwisko"},{daneProwadzacego->email,daneProwadzacego->haslo,daneProwadzacego->imie,daneProwadzacego->nazwisko});
    }catch(...){
        cout << "Nieznany blad. Zignorowano."<<endl;
        return false;
    }
    return true;
}


bool BazaDanych::importujProjekty(Id przedmiotId, string dane)
{
    try{
        auto wiersze=parseCsv(dane,';','\n');
        for(vector<string>& w : wiersze){
            if(w.size()<3){
                continue;
            }
            string& temat=w[0];
            string& opis=w[1];
            string& miejsca=w[2];
            dodaj("temat",{"przedmiot_id","temat","opis","miejsca","wolne_miejsca"},{przedmiotId,temat,opis,miejsca,miejsca});
        }
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return false;
    }catch(...){
        return false;
    }

    return true;
}

bool BazaDanych::importujTerminy(Id przedmiotId, string dane)
{
    try{
        auto wiersze=parseCsv(dane,';','\n');
        std::cout << dane << endl;
        for(vector<string>& w : wiersze){
            if(w.size()<5){
                continue;
            }
            string& dzien=w[0];
            string& godzinaOd=w[1];
            string& godzinaDo=w[2];
            string& miejsca=w[3];
            string& nrSali=w[4];
            std::cout << dzien << " " << godzinaOd << " " << godzinaDo << " " << miejsca << " " << nrSali << " " << endl;
            Zapytanie z=Tabela("sala").select("id").whereEqual("numer",nrSali);
            string salaId=parseCsv(z,',',';')[0][0];
            std::cout << salaId << endl;
            if(salaId.empty()){
                dodaj("sala",{"numer"},{nrSali});
                salaId=parseCsv(z,',',';')[0][0];
                std::cout << salaId << endl;
            }
            dodaj("termin",{"przedmiot_id","dzien","godzina_od","godzina_do","miejsca","sala_id"},{przedmiotId,dzien,godzinaOd,godzinaDo,miejsca,salaId});
        }
    }catch(sql::SQLException err){
        std::cout << "Przechwycono wyjatek SQL\n";
        std::cout << err.what() << endl;
        return false;
    }catch(...){
        return false;
    }
    return true;
}


bool BazaDanych::importujStudentow(Id przedmiotId, string dane)
{
    auto wiersze = parseCsv(dane, ';', '\n');
    for(vector<string> w : wiersze){
        if(w.size()<3){
            continue;
        }
        string& imie=w[0];
        string& nazwisko=w[1];
        string& indeks=w[2];
        try{
            dodaj("student",{"imie","nazwisko","index"},{imie,nazwisko,indeks});
            string id=Tabela("student").select("id").whereEqual("`index`",indeks);
            dodaj("student_przedmiot",{"student_id","przedmiot_id"},{id,przedmiotId});
        }catch(sql::SQLException err){
            std::cout << "Przechwycono wyjatek SQL\n";
            std::cout << err.what() << endl;
            return false;
        }catch(...){
            return false;
        }
    }
    return true;
}
