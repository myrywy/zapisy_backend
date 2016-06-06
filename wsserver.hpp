#ifndef WSSERVER_HPP
#define WSSERVER_HPP

#include "soapzapisyService.h" // the service class, also #includes "soapH.h" and "soapStub.h"
#include <iostream>
#include <sstream>

#include <string>
using std::string;

/**
 * @brief Klasa WSServer zawiera podstawowe parametry serwera (adres, port), uruchamia serwer usług sieciowych systemu zapisów.
 */
class WSServer
{
public:
    /**
     * @brief WSServer konstruktor domyślny; nie uruchamia serwera
     */
    WSServer();
    /**
     * @brief WSServer konstruktor pobierający ustawienia (adres i port) oraz uruchamiający serwer
     * @param properties_file_name nazwa pliku z opcjami serwera
     */
    WSServer(string properties_file_name);
    /**
     * @brief Funkcja z główną pętlą odbierającą zapytania i tworzącą nowe wątki do ich obsługi
     * @return
     */
    int run();

    string getAddress() const;
    void setAddress(const string &value);
    int getPort() const;
    void setPort(int value);

private:
    int port;
    string address;
    zapisyService* service{nullptr};
    SOAP_SOCKET sock;
};

/**
 * Funkcja obsługująca zapytania http GET. Implementuje zwracanie pliku wsdl dla zapytania ?wsdl;
 */
int http_get(struct soap *soap);
/**
 * Funkcja obsługująca wywołania usług sieciowych, uruchamiana przez serwer w osobnych wątkach.
 */
void *process_request(void *serviceCopy);

#endif // WSSERVER_HPP
