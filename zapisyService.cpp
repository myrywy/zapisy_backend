#include "soapzapisyService.h"
#include "bazadanych.h"
#include <iostream>

int zapisyService::zapiszProjekt(std::string ID, z1__student *zapisywany, struct z1__zapiszProjektResponse &_param_1)
{
    std::cout << "ID: " << ID << std::endl;
    std::cout << zapisywany->imie << " " << zapisywany->nazwisko << ", nr indeksu: " << zapisywany->index << std::endl;
    std::cout << _param_1.rezultat << std::endl;
    _param_1.rezultat="ok";
    return SOAP_OK;
}

 int zapisyService::dodajProjekt(z1__temat *projekt, struct z1__dodajProjektResponse &_param_2) {
     BazaDanych* baza=BazaDanych::instancja();
     std::cout << projekt->temat << endl;
     std::cout << _param_2.rezultat << endl;
     std::cout << "zapis" << endl;
     if( baza->dodajProjekt(*projekt) ){
         _param_2.rezultat="ok";
     }else{
         _param_2.rezultat="blad";
     }
     return SOAP_OK;
 }
 
 
 int zapisyService::zapiszTermin(std::string ID, z1__student *zapisywany, struct z1__zapiszTerminResponse &_param_3) {return 0;}
 
 int zapisyService::dodajTermin(z1__termin *termin, struct z1__dodajTerminResponse &_param_4) {return 0;}
 
 int zapisyService::eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5) {return 0;}
 
 int zapisyService::eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6) {return 0;}
 
 int zapisyService::eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7) {return 0;}
