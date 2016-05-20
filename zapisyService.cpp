#include "soapzapisyService.h"
#include "bazadanych.h"
#include <iostream>

int zapiszProjekt(std::string terminID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1){
	BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajTermin(terminID, zapisywanyID) ){
         _param_1.rezultat="ok";
     }else{
         _param_1.rezultat="blad";
     }
}

int zapiszTermin(std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3){
	BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajTermin(projektID, zapisywanyID) ){
         _param_3.rezultat="ok";
     }else{
         _param_3.rezultat="blad";
     }
}

 int zapisyService::dodajProjekt(std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2) {
     BazaDanych* baza=BazaDanych::instancja();
     std::cout << projekt->temat << endl;
     std::cout << _param_2.rezultat << endl;
     std::cout << "zapis" << endl;
     if( baza->dodajProjekt(przedmiotID, *projekt) ){
         _param_2.rezultat="ok";
     }else{
         _param_2.rezultat="blad";
     }
     return SOAP_OK;
 }
 
 int zapisyService::dodajTermin(std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajTermin(przedmiotID, salaID, *termin) ){
         _param_4.rezultat="ok";
     }else{
         _param_4.rezultat="blad";
     }
     return SOAP_OK;
}
 
 int zapisyService::eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5) {return 0;}
 
 int zapisyService::eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6) {return 0;}
 
 int zapisyService::eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7) {return 0;}
