#ifndef WSSERVER_HPP
#define WSSERVER_HPP

#include "soapzapisyService.h" // the service class, also #includes "soapH.h" and "soapStub.h"
#include <iostream>
#include <sstream>

#include <string>
using std::string;

class WSServer
{
public:
    WSServer();
    WSServer(string properties_file_name);
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
