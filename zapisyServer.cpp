#include "zapisy.nsmap"        // XML namespace mapping table (only needed once at the global level)
#include "soapzapisyService.h" // the service class, also #includes "soapH.h" and "soapStub.h"
#include <iostream>
#include <sstream>

#include "mysql_connection.h"

#include "bazadanych.h"

int http_get(struct soap *soap);

void *process_request(void *serviceCopy)
{
    pthread_detach(pthread_self());
    zapisyService *c = static_cast<zapisyService*>(serviceCopy) ;
    c->serve() ;
    c->destroy() ;
    delete c ;
    return NULL;
}

int main()
{

    zapisyService service(SOAP_IO_KEEPALIVE);

    //soap_init2(service.soap, SOAP_IO_KEEPALIVE, SOAP_IO_KEEPALIVE | SOAP_XML_INDENT);
    service.soap->bind_flags= SO_REUSEPORT;
    service.soap->fget=http_get;
    //service.soap->version=1;
    //soap_set_version(service.soap,1);
    //soap_set_mime(service.soap, "text/xml", "text/xml");
    std::cerr << "\nSoap version: " <<  service.soap->version << std::endl;
    std::cerr << "\nHttp content: " <<  service.soap->http_content << std::endl;
    service.soap->http_content="text/xml";
    int port=8090;

    //SOAP_SOCKET sock = service.bind("127.0.0.1", port, 100);
    SOAP_SOCKET sock = service.bind("192.168.0.13", port, 100);
    if(soap_valid_socket(sock)){
        std::cout << "socket poprawny" << std::endl;
    }else{
        std::cout << "blad przy tworzeniu socketa: " << sock << std::endl;

        std::ostringstream stream;
        soap_stream_fault(service.soap, stream);
        std::cout << stream.str();
        return -5;
    }
    std::cout << "path: " << service.soap->path << std::endl;
    service.soap->socket_flags = MSG_NOSIGNAL;
    //service.soap->accept_flags = SO_NOSIGPIPE;
    zapisyService *tc;
    pthread_t tid;
    while(true)
    {
        if (!soap_valid_socket(service.accept()))
            return service.soap->error;
        tc = service.copy() ; // make a safe copy
        if (tc == NULL)
            break;
        pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tc);

        printf("Created a new thread %ld\n", tid) ;
    }

    /*int errcode = service.run(port);
    std::cout << "errcode: " << errcode << std::endl;
    while (errcode != SOAP_OK && service.soap->error != SOAP_TCP_ERROR)
      service.soap_stream_fault(std::cerr);
    */
    service.destroy();
}

int http_get(struct soap *soap)
{
   FILE *fd = NULL;
   char *s = strchr(soap->path, '?');
   std::cerr << std::endl << "Zapytanie http\n" << s << std::endl;
   if (!s || strcmp(s, "?wsdl"))
       return SOAP_GET_METHOD;
   fd = fopen("zapisy.wsdl", "rb"); // open WSDL file to copy
   if (!fd)
       return 404; // return HTTP not found error
   soap->http_content = "text/xml"; // HTTP header with text/xml content
   soap_response(soap, SOAP_FILE);
   for (;;)
   {
      size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
      if (!r)
         break;
      if (soap_send_raw(soap, soap->tmpbuf, r))
         break; // can't send, but little we can do about that
   }
   fclose(fd);
   soap_end_send(soap);
   return SOAP_OK;
}
