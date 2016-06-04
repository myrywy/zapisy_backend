/* soapzapisyService.h
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

#ifndef soapzapisyService_H
#define soapzapisyService_H
#include "soapH.h"

    class SOAP_CMAC zapisyService {
      public:
        /// Context to manage service IO and data
        struct soap *soap;
        bool soap_own;  ///< flag indicating that this context is owned by this service when context is shared
        /// Variables globally declared in zapisy.h, if any
        /// Construct a service with new managing context
        zapisyService();
        /// Copy constructor
        zapisyService(const zapisyService&);
        /// Construct service given a shared managing context
        zapisyService(struct soap*);
        /// Constructor taking input+output mode flags for the new managing context
        zapisyService(soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        zapisyService(soap_mode imode, soap_mode omode);
        /// Destructor deletes non-shared managing context only (use destroy() to delete deserialized data)
        virtual ~zapisyService();
        /// Delete all deserialized data (with soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to defaults
        virtual void reset();
        /// Initializer used by constructors
        virtual void zapisyService_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual zapisyService *copy() SOAP_PURE_VIRTUAL;
        /// Copy assignment
        zapisyService& operator=(const zapisyService&);
        /// Close connection (normally automatic)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Return sender-related fault to sender
        virtual int soap_senderfault(const char *string, const char *detailXML);
        /// Return sender-related fault with SOAP 1.2 subcode to sender
        virtual int soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML);
        /// Return receiver-related fault to sender
        virtual int soap_receiverfault(const char *string, const char *detailXML);
        /// Return receiver-related fault with SOAP 1.2 subcode to sender
        virtual int soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML);
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
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
        /// Run simple single-thread (iterative, non-SSL) service on port until a connection error occurs (returns SOAP_OK or error code), use this->bind_flag = SO_REUSEADDR to rebind for immediate rerun
        virtual int run(int port);
    #if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
        /// Run simple single-thread SSL service on port until a connection error occurs (returns SOAP_OK or error code), use this->bind_flag = SO_REUSEADDR to rebind for immediate rerun
        virtual int ssl_run(int port);
    #endif
        /// Bind service to port (returns master socket or SOAP_INVALID_SOCKET)
        virtual SOAP_SOCKET bind(const char *host, int port, int backlog);
        /// Accept next request (returns socket or SOAP_INVALID_SOCKET)
        virtual SOAP_SOCKET accept();
    #if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
        /// When SSL is used, after accept() should perform and accept SSL handshake
        virtual int ssl_accept();
    #endif
        /// After accept() serve this request (returns SOAP_OK or error code)
        virtual int serve();
        /// Used by serve() to dispatch a request (returns SOAP_OK or error code)
        virtual int dispatch();
        virtual int dispatch(struct soap *soap);
        ///
        /// Service operations are listed below (you should define these)
        /// Note: compile with -DWITH_PURE_VIRTUAL for pure virtual methods
        ///
        /// Web service operation 'zapiszProjekt' (returns SOAP_OK or error code)
        virtual int zapiszProjekt(std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1) SOAP_PURE_VIRTUAL;
        /// Web service operation 'dodajProjekt' (returns SOAP_OK or error code)
        virtual int dodajProjekt(std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2) SOAP_PURE_VIRTUAL;
        /// Web service operation 'zapiszTermin' (returns SOAP_OK or error code)
        virtual int zapiszTermin(std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3) SOAP_PURE_VIRTUAL;
        /// Web service operation 'dodajTermin' (returns SOAP_OK or error code)
        virtual int dodajTermin(std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4) SOAP_PURE_VIRTUAL;
        /// Web service operation 'eksportujProjekt' (returns SOAP_OK or error code)
        virtual int eksportujProjekt(std::string ID, struct z1__eksportujProjektResponse &_param_5) SOAP_PURE_VIRTUAL;
        /// Web service operation 'eksportujTermin' (returns SOAP_OK or error code)
        virtual int eksportujTermin(std::string ID, struct z1__eksportujTerminResponse &_param_6) SOAP_PURE_VIRTUAL;
        /// Web service operation 'eksportujPrzedmiot' (returns SOAP_OK or error code)
        virtual int eksportujPrzedmiot(std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7) SOAP_PURE_VIRTUAL;
        /// Web service operation 'dodajPrzedmiot' (returns SOAP_OK or error code)
        virtual int dodajPrzedmiot(z1__importowanyPrzedmiot *przedmiot, struct z1__dodajPrzedmiotResponse &_param_8) SOAP_PURE_VIRTUAL;
        /// Web service operation 'dodajProwadzacego' (returns SOAP_OK or error code)
        virtual int dodajProwadzacego(z1__prowadzacy *daneProwadzacego, struct z1__dodajProwadzacegoResponse &_param_9) SOAP_PURE_VIRTUAL;
        /// Web service operation 'zmienDaneProwadzacego' (returns SOAP_OK or error code)
        virtual int zmienDaneProwadzacego(std::string idProwadzacego, z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunProwadzacego' (returns SOAP_OK or error code)
        virtual int usunProwadzacego(std::string ID, struct z1__usunProwadzacegoResponse &_param_11) SOAP_PURE_VIRTUAL;
        /// Web service operation 'dodajStudenta' (returns SOAP_OK or error code)
        virtual int dodajStudenta(std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunStudentaZPrzedmiotu' (returns SOAP_OK or error code)
        virtual int usunStudentaZPrzedmiotu(std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunWszystkichZPrzedmiotu' (returns SOAP_OK or error code)
        virtual int usunWszystkichZPrzedmiotu(std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunPrzedmiot' (returns SOAP_OK or error code)
        virtual int usunPrzedmiot(std::string ID, struct z1__usunPrzedmiotResponse &_param_15) SOAP_PURE_VIRTUAL;
        /// Web service operation 'edytujProjekt' (returns SOAP_OK or error code)
        virtual int edytujProjekt(std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16) SOAP_PURE_VIRTUAL;
        /// Web service operation 'edytujTermin' (returns SOAP_OK or error code)
        virtual int edytujTermin(std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17) SOAP_PURE_VIRTUAL;
        /// Web service operation 'wypiszZProjektu' (returns SOAP_OK or error code)
        virtual int wypiszZProjektu(std::string projektID, std::string zapisywanyID, struct z1__wypiszZProjektuResponse &_param_18) SOAP_PURE_VIRTUAL;
        /// Web service operation 'wypiszZTerminu' (returns SOAP_OK or error code)
        virtual int wypiszZTerminu(std::string terminID, std::string zapisywanyID, struct z1__wypiszZTerminuResponse &_param_19) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunWszystkieTematy' (returns SOAP_OK or error code)
        virtual int usunWszystkieTematy(std::string ID, struct z1__usunWszystkieTematyResponse &_param_20) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunWszystkieTerminy' (returns SOAP_OK or error code)
        virtual int usunWszystkieTerminy(std::string ID, struct z1__usunWszystkieTerminyResponse &_param_21) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunTemat' (returns SOAP_OK or error code)
        virtual int usunTemat(std::string ID, struct z1__usunTematResponse &_param_22) SOAP_PURE_VIRTUAL;
        /// Web service operation 'usunTermin' (returns SOAP_OK or error code)
        virtual int usunTermin(std::string ID, struct z1__usunTerminResponse &_param_23) SOAP_PURE_VIRTUAL;
        /// Web service operation 'importujProjekty' (returns SOAP_OK or error code)
        virtual int importujProjekty(std::string przedmiotId, std::string dane, struct z1__importujProjektyResponse &_param_24) SOAP_PURE_VIRTUAL;
        /// Web service operation 'importujTerminy' (returns SOAP_OK or error code)
        virtual int importujTerminy(std::string przedmiotId, std::string dane, struct z1__importujTerminyResponse &_param_25) SOAP_PURE_VIRTUAL;
        /// Web service operation 'importujStudentow' (returns SOAP_OK or error code)
        virtual int importujStudentow(std::string przedmiotId, std::string dane, struct z1__importujStudentowResponse &_param_26) SOAP_PURE_VIRTUAL;
        /// Web service operation 'edytujStudenta' (returns SOAP_OK or error code)
        virtual int edytujStudenta(std::string studentId, z1__student *student, struct z1__edytujStudentaResponse &_param_27) SOAP_PURE_VIRTUAL;
        /// Web service operation 'zmienOpcje' (returns SOAP_OK or error code)
        virtual int zmienOpcje(z1__opcja *opcja, struct z1__zmienOpcjeResponse &_param_28) SOAP_PURE_VIRTUAL;
    };
#endif
