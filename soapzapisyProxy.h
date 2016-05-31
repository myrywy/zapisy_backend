/* soapzapisyProxy.h
   Generated by gSOAP 2.8.30 for zapisy.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapzapisyProxy_H
#define soapzapisyProxy_H
#include "soapH.h"

    class SOAP_CMAC zapisyProxy {
      public:
        /// Context to manage proxy IO and data
        struct soap *soap;
        bool soap_own; ///< flag indicating that this context is owned by this proxy when context is shared
        /// Endpoint URL of service 'zapisyProxy' (change as needed)
        const char *soap_endpoint;
        /// Variables globally declared in zapisy.h, if any
        /// Construct a proxy with new managing context
        zapisyProxy();
        /// Copy constructor
        zapisyProxy(const zapisyProxy& rhs);
        /// Construct proxy given a shared managing context
        zapisyProxy(struct soap*);
        /// Constructor taking an endpoint URL
        zapisyProxy(const char *endpoint);
        /// Constructor taking input and output mode flags for the new managing context
        zapisyProxy(soap_mode iomode);
        /// Constructor taking endpoint URL and input and output mode flags for the new managing context
        zapisyProxy(const char *endpoint, soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        zapisyProxy(soap_mode imode, soap_mode omode);
        /// Destructor deletes non-shared managing context only (use destroy() to delete deserialized data)
        virtual ~zapisyProxy();
        /// Initializer used by constructors
        virtual void zapisyProxy_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual zapisyProxy *copy() SOAP_PURE_VIRTUAL;
        /// Copy assignment
        zapisyProxy& operator=(const zapisyProxy&);
        /// Delete all deserialized data (uses soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to default
        virtual void reset();
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
        /// Get SOAP Fault structure (i.e. soap->fault, which is NULL when absent)
        virtual ::SOAP_ENV__Fault *soap_fault();
        /// Get SOAP Fault string (NULL when absent)
        virtual const char *soap_fault_string();
        /// Get SOAP Fault detail as string (NULL when absent)
        virtual const char *soap_fault_detail();
        /// Close connection (normally automatic, except for send_X ops)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Print fault
        virtual void soap_print_fault(FILE*);
    #ifndef WITH_LEAN
    #ifndef WITH_COMPAT
        /// Print fault to stream
        virtual void soap_stream_fault(std::ostream&);
    #endif
        /// Write fault to buffer
        virtual char *soap_sprint_fault(char *buf, size_t len);
    #endif
        /// Web service operation 'zapiszProjekt' (returns SOAP_OK or error code)
        virtual int zapiszProjekt(std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1)
        { return this->zapiszProjekt(NULL, NULL, projektID, zapisywanyID, _param_1); }
        virtual int zapiszProjekt(const char *soap_endpoint, const char *soap_action, std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1);
        /// Web service operation 'dodajProjekt' (returns SOAP_OK or error code)
        virtual int dodajProjekt(std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2)
        { return this->dodajProjekt(NULL, NULL, przedmiotID, projekt, _param_2); }
        virtual int dodajProjekt(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2);
        /// Web service operation 'zapiszTermin' (returns SOAP_OK or error code)
        virtual int zapiszTermin(std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3)
        { return this->zapiszTermin(NULL, NULL, projektID, zapisywanyID, _param_3); }
        virtual int zapiszTermin(const char *soap_endpoint, const char *soap_action, std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3);
        /// Web service operation 'dodajTermin' (returns SOAP_OK or error code)
        virtual int dodajTermin(std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4)
        { return this->dodajTermin(NULL, NULL, przedmiotID, salaID, termin, _param_4); }
        virtual int dodajTermin(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4);
        /// Web service operation 'eksportujProjekt' (returns SOAP_OK or error code)
        virtual int eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5)
        { return this->eksportujProjekt(NULL, NULL, ID, _param_5); }
        virtual int eksportujProjekt(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__eksportujProjektResponse &_param_5);
        /// Web service operation 'eksportujTermin' (returns SOAP_OK or error code)
        virtual int eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6)
        { return this->eksportujTermin(NULL, NULL, ID, _param_6); }
        virtual int eksportujTermin(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__eksportujTerminResponse &_param_6);
        /// Web service operation 'eksportujPrzedmiot' (returns SOAP_OK or error code)
        virtual int eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7)
        { return this->eksportujPrzedmiot(NULL, NULL, ID, _param_7); }
        virtual int eksportujPrzedmiot(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7);
        /// Web service operation 'dodajPrzedmiot' (returns SOAP_OK or error code)
        virtual int dodajPrzedmiot(std::string importowanyPrzedmiot, z1__temat *projekt, struct z1__dodajPrzedmiotResponse &_param_8)
        { return this->dodajPrzedmiot(NULL, NULL, importowanyPrzedmiot, projekt, _param_8); }
        virtual int dodajPrzedmiot(const char *soap_endpoint, const char *soap_action, std::string importowanyPrzedmiot, z1__temat *projekt, struct z1__dodajPrzedmiotResponse &_param_8);
        /// Web service operation 'dodajProwadzacego' (returns SOAP_OK or error code)
        virtual int dodajProwadzacego(z1__prowadzacy *daneProwadzacego, struct z1__dodajProwadzacegoResponse &_param_9)
        { return this->dodajProwadzacego(NULL, NULL, daneProwadzacego, _param_9); }
        virtual int dodajProwadzacego(const char *soap_endpoint, const char *soap_action, z1__prowadzacy *daneProwadzacego, struct z1__dodajProwadzacegoResponse &_param_9);
        /// Web service operation 'zmienDaneProwadzacego' (returns SOAP_OK or error code)
        virtual int zmienDaneProwadzacego(std::string idProwadzacego, z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10)
        { return this->zmienDaneProwadzacego(NULL, NULL, idProwadzacego, daneProwadzacego, _param_10); }
        virtual int zmienDaneProwadzacego(const char *soap_endpoint, const char *soap_action, std::string idProwadzacego, z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10);
        /// Web service operation 'usunProwadzacego' (returns SOAP_OK or error code)
        virtual int usunProwadzacego(std::string ID, struct z1__usunProwadzacegoResponse &_param_11)
        { return this->usunProwadzacego(NULL, NULL, ID, _param_11); }
        virtual int usunProwadzacego(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__usunProwadzacegoResponse &_param_11);
        /// Web service operation 'dodajStudenta' (returns SOAP_OK or error code)
        virtual int dodajStudenta(std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12)
        { return this->dodajStudenta(NULL, NULL, przedmiotID, student, _param_12); }
        virtual int dodajStudenta(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12);
        /// Web service operation 'usunStudentaZPrzedmiotu' (returns SOAP_OK or error code)
        virtual int usunStudentaZPrzedmiotu(std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13)
        { return this->usunStudentaZPrzedmiotu(NULL, NULL, przedmiotID, student, _param_13); }
        virtual int usunStudentaZPrzedmiotu(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13);
        /// Web service operation 'usunWszystkichZPrzedmiotu' (returns SOAP_OK or error code)
        virtual int usunWszystkichZPrzedmiotu(std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14)
        { return this->usunWszystkichZPrzedmiotu(NULL, NULL, ID, _param_14); }
        virtual int usunWszystkichZPrzedmiotu(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14);
        /// Web service operation 'usunPrzedmiot' (returns SOAP_OK or error code)
        virtual int usunPrzedmiot(std::string ID, struct z1__usunPrzedmiotResponse &_param_15)
        { return this->usunPrzedmiot(NULL, NULL, ID, _param_15); }
        virtual int usunPrzedmiot(const char *soap_endpoint, const char *soap_action, std::string ID, struct z1__usunPrzedmiotResponse &_param_15);
        /// Web service operation 'edytujProjekt' (returns SOAP_OK or error code)
        virtual int edytujProjekt(std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16)
        { return this->edytujProjekt(NULL, NULL, przedmiotID, projektID, projekt, _param_16); }
        virtual int edytujProjekt(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16);
        /// Web service operation 'edytujTermin' (returns SOAP_OK or error code)
        virtual int edytujTermin(std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17)
        { return this->edytujTermin(NULL, NULL, przedmiotID, terminID, salaID, termin, _param_17); }
        virtual int edytujTermin(const char *soap_endpoint, const char *soap_action, std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17);
    };
#endif
