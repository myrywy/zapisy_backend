#include "soapzapisyService.h"
#include "bazadanych.h"
#include <iostream>
#include <cstdio>
#include "tabela.h"

int zapisyService::zapiszProjekt(std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1){
    cerr<< "zapisyService::zapiszProjekt" << endl;
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
     if( baza->zapiszNaTermin(zapisywanyID, projektID) ){
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
 
 int zapisyService::eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5) {
     try{
        _param_5.nazwa="projekty_";
        _param_5.nazwa+=Tabela("przedmiot").select("nazwa").whereEqual("id",ID);
     }catch(...){
         cerr << "Nie mozna znalezc nazwy przedmiotu. Zignorowano\n";
         _param_5.nazwa="projekty";
     }

     _param_5.plik=BazaDanych::instancja()->pobierzProjekt(ID);
     return SOAP_OK;
 }
 
 int zapisyService::eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6) {
     try{
        _param_6.nazwa="terminy_";
        _param_6.nazwa+=Tabela("przedmiot").select("nazwa").whereEqual("id",ID);
     }catch(...){
         cerr << "Nie mozna znalezc nazwy przedmiotu. Zignorowano\n";
         _param_6.nazwa="terminy";
     }
     _param_6.plik=BazaDanych::instancja()->pobierzTermin(ID);
     return SOAP_OK;
 }
 
 int zapisyService::eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7) {
     try{
        _param_7.nazwa="studenci_";
        _param_7.nazwa+=Tabela("przedmiot").select("nazwa").whereEqual("id",ID);
     }catch(...){
         cerr << "Nie mozna znalezc nazwy przedmiotu. Zignorowano\n";
         _param_7.nazwa="studenci";
     }
     _param_7.plik=BazaDanych::instancja()->pobierzPrzedmiot(ID);
     return SOAP_OK;}

 int zapisyService::dodajPrzedmiot(z1__importowanyPrzedmiot *przedmiot, struct z1__dodajPrzedmiotResponse &_param_8) {

     BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajPrzedmiot(przedmiot->szczegoly,przedmiot->emailProwadzacego) ){
         _param_8.rezultat="ok";
     }else{
         _param_8.rezultat="error";
     }
     string przedmiotId;
     try{
         przedmiotId = Tabela("przedmiot").select("id").whereEqual("nazwa","\'"+przedmiot->szczegoly->nazwa+"\'");
     }catch(...){
         _param_8.rezultat="error";
         return SOAP_OK;
     }
     if(przedmiot->listaStudentow){
         baza->importujStudentow(przedmiotId,*(przedmiot->listaStudentow));
     }
     if(przedmiot->tematyProjektow){
         baza->importujStudentow(przedmiotId,*(przedmiot->tematyProjektow));
     }
     if(przedmiot->terminyLaboratoriow){
         baza->importujStudentow(przedmiotId,*(przedmiot->terminyLaboratoriow));
     }
     return SOAP_OK;
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

 int zapisyService::zmienDaneProwadzacego(std::string idProwadzacego, z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->zmienProwadzacego(idProwadzacego, daneProwadzacego) ){
         _param_10.rezultat="ok";
     }else{
         _param_10.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::usunProwadzacego(std::string ID, struct z1__usunProwadzacegoResponse &_param_11) {
     try{
         BazaDanych::instancja()->usun("prowadzacy","id",ID);
     }catch(...){
         _param_11.rezultat="error";
     }
     _param_11.rezultat="ok";
    return SOAP_OK;
 }

 int zapisyService::dodajStudenta(std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->dodajStudenta(przedmiotID, student) ){
         _param_12.rezultat="ok";
     }else{
         _param_12.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::usunStudentaZPrzedmiotu(std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13) {
     BazaDanych* baza=BazaDanych::instancja();
     try{
         string id=Tabela("student").select("id").whereEqual("`index`",student->index);
         baza->usun("student_przedmiot","student_id",id);
     }catch(...){
         _param_13.rezultat="error";
         return SOAP_OK;
     }
     _param_13.rezultat="ok";
    return SOAP_OK;
 }

 int zapisyService::usunWszystkichZPrzedmiotu(std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14) {
     BazaDanych* baza=BazaDanych::instancja();
     try{
         baza->usun("student_przedmiot","przedmiot_id",ID);
     }catch(...){
         _param_14.rezultat="error";
         return SOAP_OK;
     }
     _param_14.rezultat="ok";
    return SOAP_OK;
 }

 int zapisyService::usunPrzedmiot(std::string ID, struct z1__usunPrzedmiotResponse &_param_15) {
     BazaDanych* baza=BazaDanych::instancja();
     try{
         baza->usun("przedmiot","id",ID);
     }catch(...){
         _param_15.rezultat="error";
         return SOAP_OK;
     }
     _param_15.rezultat="ok";
    return SOAP_OK;}

 int zapisyService::edytujProjekt(std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16) {
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->edytujProjekt(projektID, *projekt) ){
         _param_16.rezultat="ok";
     }else{
         _param_16.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::edytujTermin(std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17) {
     BazaDanych* baza=BazaDanych::instancja();
     std::cout << "termin: dzien: " << termin->dzien << " godzina do: "
               << termin->godzinaDo << "godzina od: "
                  << termin->godzinaOd << "miejsca: "
                     << termin->miejsca << "nr salo: "
                        << termin->nrSali
                           << "salaID: " << salaID
                              << "terminID: " << terminID << std::endl;
     if( baza->edytujTermin(terminID, *termin) ){
         _param_17.rezultat="ok";
     }else{
         _param_17.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::wypiszZProjektu(std::string projektID, std::string zapisywanyID, struct z1__wypiszZProjektuResponse &_param_18){

     if(BazaDanych::instancja()->wypiszZProjektu(zapisywanyID,projektID)){
         _param_18.rezultat="ok";
     }else{
         _param_18.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::wypiszZTerminu(std::string terminID, std::string zapisywanyID, struct z1__wypiszZTerminuResponse &_param_19){
     if(BazaDanych::instancja()->wypiszZTerminu(zapisywanyID,terminID)){
         _param_19.rezultat="ok";
     }else{
         _param_19.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::usunWszystkieTematy(std::string ID, struct z1__usunWszystkieTematyResponse &_param_20){
     try{
         BazaDanych::instancja()->procedura("usunWszystkieTematyPrzedmiotu",ID);
     }catch(...){
         _param_20.rezultat="error";
         return SOAP_OK;
     }
    _param_20.rezultat="ok";
     return SOAP_OK;
 }

 int zapisyService::usunWszystkieTerminy(std::string ID, struct z1__usunWszystkieTerminyResponse &_param_21){
     try{
         BazaDanych::instancja()->procedura("usunWszystkieTerminyPrzedmiotu",ID);
     }catch(...){
         _param_21.rezultat="error";
         return SOAP_OK;
     }
    _param_21.rezultat="ok";
     return SOAP_OK;
 }
 int zapisyService::usunTemat(std::string ID, struct z1__usunTematResponse &_param_22){
     try{
         BazaDanych::instancja()->procedura("usunTemat",ID);
     }catch(...){
         _param_22.rezultat="error";
         return SOAP_OK;
     }
    _param_22.rezultat="ok";
     return SOAP_OK;
 }
 int zapisyService::usunTermin(std::string ID, struct z1__usunTerminResponse &_param_23){
     try{
         BazaDanych::instancja()->procedura("usunTermin",ID);
     }catch(...){
         _param_23.rezultat="error";
         return SOAP_OK;
     }
    _param_23.rezultat="ok";
     return SOAP_OK;
 }

 int zapisyService::importujProjekty(std::string przedmiotId, std::string dane, struct z1__importujProjektyResponse &_param_24){
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->importujProjekty(przedmiotId, dane) ){
         _param_24.rezultat="ok";
     }else{
         _param_24.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::importujTerminy(std::string przedmiotId, std::string dane, struct z1__importujTerminyResponse &_param_25){
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->importujTerminy(przedmiotId, dane) ){
         _param_25.rezultat="ok";
     }else{
         _param_25.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::importujStudentow(std::string przedmiotId, std::string dane, struct z1__importujStudentowResponse &_param_26){
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->importujStudentow(przedmiotId, dane) ){
         _param_26.rezultat="ok";
     }else{
         _param_26.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::edytujStudenta(std::string studentId, z1__student *student, struct z1__edytujStudentaResponse &_param_27){
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->edytujStudenta(studentId, *student) ){
         _param_27.rezultat="ok";
     }else{
         _param_27.rezultat="error";
     }
     return SOAP_OK;
 }

 int zapisyService::zmienOpcje(z1__opcja *opcja, struct z1__zmienOpcjeResponse &_param_28){
     BazaDanych* baza=BazaDanych::instancja();
     if( baza->zmienOpcje(*opcja) ){
         _param_28.rezultat="ok";
     }else{
         _param_28.rezultat="error";
     }
     return SOAP_OK;
 }
