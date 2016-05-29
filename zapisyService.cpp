#include "soapzapisyService.h"
#include "bazadanych.h"
#include <iostream>
#include "tabela.h"

int zapisyService::zapiszProjekt(std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1){
	BazaDanych* baza=BazaDanych::instancja();
    string przedmiotId=Tabela("temat").select("przedmiot_id").whereEqual("id",projektID);
    if(przedmiotId.empty()){
        _param_1.rezultat="error";// nie ma takiego temtu :C
        return SOAP_OK;
    }
    bool zapisany=baza->szukajProjektStudenta(zapisywanyID,przedmiotId);
    std::cerr << "Zapisany: " << zapisany<< std::endl;
     if( !zapisany && baza->zapiszNaProjekt(zapisywanyID,projektID) ){
         _param_1.rezultat="ok";
     }else{
         _param_1.rezultat="error";
     }
     return SOAP_OK;
}

int zapisyService::zapiszTermin(std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3){
	BazaDanych* baza=BazaDanych::instancja();
     if( baza->zapiszNaTermin(projektID, zapisywanyID) ){
         _param_3.rezultat="ok";
     }else{
         _param_3.rezultat="error";
     }
     return SOAP_OK;
}

 int zapisyService::dodajProjekt(std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2) {
     BazaDanych* baza=BazaDanych::instancja();
     std::cout << projekt->temat << endl;
     std::cout << _param_2.rezultat << endl;
     std::cout << "zapis" << endl;
     if( baza->dodajProjekt(przedmiotID, *projekt) ){
         _param_2.rezultat="ok";
     }else{
         _param_2.rezultat="error";
     }
     return SOAP_OK;
 }
 
 int zapisyService::dodajTermin(std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajTermin(przedmiotID, salaID, *termin) ){
         _param_4.rezultat="ok";
     }else{
         _param_4.rezultat="error";
     }
     return SOAP_OK;
}
 
 int zapisyService::eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5) {return 0;}
 
 int zapisyService::eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6) {return 0;}
 
 int zapisyService::eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7) {return 0;}

 int zapisyService::dodajPrzedmiot(std::string importowanyPrzedmiot, z1__temat *projekt, struct z1__dodajPrzedmiotResponse &_param_8) {

     return 0;
 }

 int zapisyService::dodajProwadzacego(z1__prowadzacy *daneProwadzacego, struct z1__dodajProwadzacegoResponse &_param_9) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajProwadzacego(daneProwadzacego) ){
         _param_9.rezultat="ok";
     }else{
         _param_9.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::zmienDaneProwadzacego(z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10) {return 0;}

 int zapisyService::usunProwadzacego(std::string ID, struct z1__usunProwadzacegoResponse &_param_11) {return 0;}

 int zapisyService::dodajStudenta(std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12) {return 0;}

 int zapisyService::usunStudentaZPrzedmiotu(std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13) {return 0;}

 int zapisyService::usunWszystkichZPrzedmiotu(std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14) {return 0;}

 int zapisyService::usunPrzedmiot(std::string ID, struct z1__usunPrzedmiotResponse &_param_15) {return 0;}

 int zapisyService::edytujProjekt(std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16) {return 0;}

 int zapisyService::edytujTermin(std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17) {return 0;}
