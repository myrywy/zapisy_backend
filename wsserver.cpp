#include "wsserver.hpp"

#include <fstream>
#include <iostream>
#include "bazadanych.h"

using namespace std;

WSServer::WSServer()
{

}

WSServer::WSServer(string properties_file_name)
{
    ifstream props(properties_file_name);
    if(props.is_open()){
        string o;
        while(props >> o){
            auto option=BazaDanych::splitString(o,'=');
            if(option.size()<2){
                continue;
            }
            if(option[0]=="address"){
                setAddress(option[1]);
            }else if(option[0]=="port"){
                setPort(stoi(option[1]));
            }
        }
    }
    props.close();
    cout << "adres: " << address << " port: " << port << endl;
    run();
}

int WSServer::run()
{
    service=new zapisyService(SOAP_IO_KEEPALIVE | SOAP_C_UTFSTRING);

    service->soap->bind_flags= SO_REUSEPORT;
    service->soap->fget=http_get;
    service->soap->http_content="text/xml";

    SOAP_SOCKET sock = service->bind("192.168.0.13", port, 100);
    if(soap_valid_socket(sock)){
        std::cout << "socket poprawny" << std::endl;
    }else{
        std::cout << "blad przy tworzeniu socketa: " << sock << std::endl;

        std::ostringstream stream;
        soap_stream_fault(service->soap, stream);
        std::cout << stream.str();
        return -5;
    }
    std::cout << "path: " << service->soap->path << std::endl;
    service->soap->socket_flags = MSG_NOSIGNAL;
    zapisyService *tc;
    pthread_t tid;
    while(true)
    {
        if (!soap_valid_socket(service->accept()))
            return service->soap->error;
        tc = service->copy() ;
        if (tc == NULL)
            break;
        pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tc);

        printf("Utworzono watek %ld\n", tid) ;
    }

    service->destroy();
    delete service;
    service=nullptr;
}
string WSServer::getAddress() const
{
    return address;
}

void WSServer::setAddress(const string &value)
{
    address = value;
}
int WSServer::getPort() const
{
    return port;
}

void WSServer::setPort(int value)
{
    port = value;
}

void *process_request(void *serviceCopy)
{
    pthread_detach(pthread_self());
    zapisyService *c = static_cast<zapisyService*>(serviceCopy) ;
    c->serve() ;
    c->destroy() ;
    delete c ;
    return NULL;
}

int http_get(struct soap *soap)
{
   FILE *fd = NULL;
   char *s = strchr(soap->path, '?');
   if (!s || strcmp(s, "?wsdl"))
       return SOAP_GET_METHOD;
   fd = fopen("zapisy.wsdl", "rb");
   if (!fd)
       return 404;
   soap->http_content = "text/xml";
   soap_response(soap, SOAP_FILE);
   for (;;)
   {
      size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
      if (!r)
         break;
      if (soap_send_raw(soap, soap->tmpbuf, r))
         break;
   }
   fclose(fd);
   soap_end_send(soap);
   return SOAP_OK;
}


