/* soapzapisyProxy.cpp
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

#include "soapzapisyProxy.h"

zapisyProxy::zapisyProxy()
{	this->soap = soap_new();
	this->soap_own = true;
	zapisyProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

zapisyProxy::zapisyProxy(const zapisyProxy& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
	this->soap_endpoint = rhs.soap_endpoint;
}

zapisyProxy::zapisyProxy(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	zapisyProxy_init(_soap->imode, _soap->omode);
}

zapisyProxy::zapisyProxy(const char *endpoint)
{	this->soap = soap_new();
	this->soap_own = true;
	zapisyProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = endpoint;
}

zapisyProxy::zapisyProxy(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	zapisyProxy_init(iomode, iomode);
}

zapisyProxy::zapisyProxy(const char *endpoint, soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	zapisyProxy_init(iomode, iomode);
	soap_endpoint = endpoint;
}

zapisyProxy::zapisyProxy(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	zapisyProxy_init(imode, omode);
}

zapisyProxy::~zapisyProxy()
{	if (this->soap_own)
		soap_free(this->soap);
}

void zapisyProxy::zapisyProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] = {
        {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
        {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
        {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
        {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
        {"z1", "localhost/zapisy.wsdl", NULL, NULL},
        {NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

#ifndef WITH_PURE_VIRTUAL
zapisyProxy *zapisyProxy::copy()
{	zapisyProxy *dup = SOAP_NEW_COPY(zapisyProxy);
	if (dup)
		soap_copy_context(dup->soap, this->soap);
	return dup;
}
#endif

zapisyProxy& zapisyProxy::operator=(const zapisyProxy& rhs)
{	if (this->soap_own)
		soap_free(this->soap);
	this->soap = rhs.soap;
	this->soap_own = false;
	this->soap_endpoint = rhs.soap_endpoint;
	return *this;
}

void zapisyProxy::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void zapisyProxy::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	zapisyProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void zapisyProxy::soap_noheader()
{	this->soap->header = NULL;
}

::SOAP_ENV__Header *zapisyProxy::soap_header()
{	return this->soap->header;
}

::SOAP_ENV__Fault *zapisyProxy::soap_fault()
{	return this->soap->fault;
}

const char *zapisyProxy::soap_fault_string()
{	return *soap_faultstring(this->soap);
}

const char *zapisyProxy::soap_fault_detail()
{	return *soap_faultdetail(this->soap);
}

int zapisyProxy::soap_close_socket()
{	return soap_closesock(this->soap);
}

int zapisyProxy::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

void zapisyProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void zapisyProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *zapisyProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

int zapisyProxy::zapiszProjekt(const char *endpoint, const char *soap_action, std::string projektID, std::string zapisywanyID, struct z1__zapiszProjektResponse &_param_1)
{	struct soap *soap = this->soap;
	struct z1__zapiszProjekt soap_tmp_z1__zapiszProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__zapiszProjekt.projektID = projektID;
	soap_tmp_z1__zapiszProjekt.zapisywanyID = zapisywanyID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__zapiszProjekt(soap, &soap_tmp_z1__zapiszProjekt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__zapiszProjekt(soap, &soap_tmp_z1__zapiszProjekt, "z1:zapiszProjekt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__zapiszProjekt(soap, &soap_tmp_z1__zapiszProjekt, "z1:zapiszProjekt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_1)
		return soap_closesock(soap);
	soap_default_z1__zapiszProjektResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__zapiszProjektResponse(soap, &_param_1, "z1:zapiszProjektResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajProjekt(const char *endpoint, const char *soap_action, std::string przedmiotID, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2)
{	struct soap *soap = this->soap;
	struct z1__dodajProjekt soap_tmp_z1__dodajProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajProjekt.przedmiotID = przedmiotID;
	soap_tmp_z1__dodajProjekt.projekt = projekt;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__dodajProjekt(soap, &soap_tmp_z1__dodajProjekt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__dodajProjekt(soap, &soap_tmp_z1__dodajProjekt, "z1:dodajProjekt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__dodajProjekt(soap, &soap_tmp_z1__dodajProjekt, "z1:dodajProjekt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_2)
		return soap_closesock(soap);
	soap_default_z1__dodajProjektResponse(soap, &_param_2);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__dodajProjektResponse(soap, &_param_2, "z1:dodajProjektResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::zapiszTermin(const char *endpoint, const char *soap_action, std::string projektID, std::string zapisywanyID, struct z1__zapiszTerminResponse &_param_3)
{	struct soap *soap = this->soap;
	struct z1__zapiszTermin soap_tmp_z1__zapiszTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__zapiszTermin.projektID = projektID;
	soap_tmp_z1__zapiszTermin.zapisywanyID = zapisywanyID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__zapiszTermin(soap, &soap_tmp_z1__zapiszTermin);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__zapiszTermin(soap, &soap_tmp_z1__zapiszTermin, "z1:zapiszTermin", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__zapiszTermin(soap, &soap_tmp_z1__zapiszTermin, "z1:zapiszTermin", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_3)
		return soap_closesock(soap);
	soap_default_z1__zapiszTerminResponse(soap, &_param_3);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__zapiszTerminResponse(soap, &_param_3, "z1:zapiszTerminResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajTermin(const char *endpoint, const char *soap_action, std::string przedmiotID, std::string salaID, z1__termin *termin, struct z1__dodajTerminResponse &_param_4)
{	struct soap *soap = this->soap;
	struct z1__dodajTermin soap_tmp_z1__dodajTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajTermin.przedmiotID = przedmiotID;
	soap_tmp_z1__dodajTermin.salaID = salaID;
	soap_tmp_z1__dodajTermin.termin = termin;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__dodajTermin(soap, &soap_tmp_z1__dodajTermin);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__dodajTermin(soap, &soap_tmp_z1__dodajTermin, "z1:dodajTermin", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__dodajTermin(soap, &soap_tmp_z1__dodajTermin, "z1:dodajTermin", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_4)
		return soap_closesock(soap);
	soap_default_z1__dodajTerminResponse(soap, &_param_4);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__dodajTerminResponse(soap, &_param_4, "z1:dodajTerminResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::eksportujProjekt(const char *endpoint, const char *soap_action, std::string ID, struct z1__eksportujProjektResponse &_param_5)
{	struct soap *soap = this->soap;
	struct z1__eksportujProjekt soap_tmp_z1__eksportujProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujProjekt.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__eksportujProjekt(soap, &soap_tmp_z1__eksportujProjekt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__eksportujProjekt(soap, &soap_tmp_z1__eksportujProjekt, "z1:eksportujProjekt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__eksportujProjekt(soap, &soap_tmp_z1__eksportujProjekt, "z1:eksportujProjekt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_5)
		return soap_closesock(soap);
	soap_default_z1__eksportujProjektResponse(soap, &_param_5);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__eksportujProjektResponse(soap, &_param_5, "z1:eksportujProjektResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::eksportujTermin(const char *endpoint, const char *soap_action, std::string ID, struct z1__eksportujTerminResponse &_param_6)
{	struct soap *soap = this->soap;
	struct z1__eksportujTermin soap_tmp_z1__eksportujTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujTermin.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__eksportujTermin(soap, &soap_tmp_z1__eksportujTermin);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__eksportujTermin(soap, &soap_tmp_z1__eksportujTermin, "z1:eksportujTermin", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__eksportujTermin(soap, &soap_tmp_z1__eksportujTermin, "z1:eksportujTermin", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_6)
		return soap_closesock(soap);
	soap_default_z1__eksportujTerminResponse(soap, &_param_6);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__eksportujTerminResponse(soap, &_param_6, "z1:eksportujTerminResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::eksportujPrzedmiot(const char *endpoint, const char *soap_action, std::string ID, struct z1__eksportujPrzedmiotResponse &_param_7)
{	struct soap *soap = this->soap;
	struct z1__eksportujPrzedmiot soap_tmp_z1__eksportujPrzedmiot;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujPrzedmiot.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__eksportujPrzedmiot(soap, &soap_tmp_z1__eksportujPrzedmiot);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__eksportujPrzedmiot(soap, &soap_tmp_z1__eksportujPrzedmiot, "z1:eksportujPrzedmiot", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__eksportujPrzedmiot(soap, &soap_tmp_z1__eksportujPrzedmiot, "z1:eksportujPrzedmiot", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_7)
		return soap_closesock(soap);
	soap_default_z1__eksportujPrzedmiotResponse(soap, &_param_7);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__eksportujPrzedmiotResponse(soap, &_param_7, "z1:eksportujPrzedmiotResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajPrzedmiot(const char *endpoint, const char *soap_action, std::string importowanyPrzedmiot, z1__temat *projekt, struct z1__dodajPrzedmiotResponse &_param_8)
{	struct soap *soap = this->soap;
	struct z1__dodajPrzedmiot soap_tmp_z1__dodajPrzedmiot;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajPrzedmiot.importowanyPrzedmiot = importowanyPrzedmiot;
	soap_tmp_z1__dodajPrzedmiot.projekt = projekt;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__dodajPrzedmiot(soap, &soap_tmp_z1__dodajPrzedmiot);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__dodajPrzedmiot(soap, &soap_tmp_z1__dodajPrzedmiot, "z1:dodajPrzedmiot", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__dodajPrzedmiot(soap, &soap_tmp_z1__dodajPrzedmiot, "z1:dodajPrzedmiot", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_8)
		return soap_closesock(soap);
	soap_default_z1__dodajPrzedmiotResponse(soap, &_param_8);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__dodajPrzedmiotResponse(soap, &_param_8, "z1:dodajPrzedmiotResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajProwadzacego(const char *endpoint, const char *soap_action, z1__prowadzacy *daneProwadzacego, struct z1__dodajProwadzacegoResponse &_param_9)
{	struct soap *soap = this->soap;
	struct z1__dodajProwadzacego soap_tmp_z1__dodajProwadzacego;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajProwadzacego.daneProwadzacego = daneProwadzacego;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__dodajProwadzacego(soap, &soap_tmp_z1__dodajProwadzacego);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__dodajProwadzacego(soap, &soap_tmp_z1__dodajProwadzacego, "z1:dodajProwadzacego", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__dodajProwadzacego(soap, &soap_tmp_z1__dodajProwadzacego, "z1:dodajProwadzacego", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_9)
		return soap_closesock(soap);
	soap_default_z1__dodajProwadzacegoResponse(soap, &_param_9);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__dodajProwadzacegoResponse(soap, &_param_9, "z1:dodajProwadzacegoResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::zmienDaneProwadzacego(const char *endpoint, const char *soap_action, std::string idProwadzacego, z1__prowadzacy *daneProwadzacego, struct z1__zmienDaneProwadzacegoResponse &_param_10)
{	struct soap *soap = this->soap;
	struct z1__zmienDaneProwadzacego soap_tmp_z1__zmienDaneProwadzacego;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__zmienDaneProwadzacego.idProwadzacego = idProwadzacego;
	soap_tmp_z1__zmienDaneProwadzacego.daneProwadzacego = daneProwadzacego;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__zmienDaneProwadzacego(soap, &soap_tmp_z1__zmienDaneProwadzacego);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__zmienDaneProwadzacego(soap, &soap_tmp_z1__zmienDaneProwadzacego, "z1:zmienDaneProwadzacego", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__zmienDaneProwadzacego(soap, &soap_tmp_z1__zmienDaneProwadzacego, "z1:zmienDaneProwadzacego", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_10)
		return soap_closesock(soap);
	soap_default_z1__zmienDaneProwadzacegoResponse(soap, &_param_10);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__zmienDaneProwadzacegoResponse(soap, &_param_10, "z1:zmienDaneProwadzacegoResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::usunProwadzacego(const char *endpoint, const char *soap_action, std::string ID, struct z1__usunProwadzacegoResponse &_param_11)
{	struct soap *soap = this->soap;
	struct z1__usunProwadzacego soap_tmp_z1__usunProwadzacego;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__usunProwadzacego.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__usunProwadzacego(soap, &soap_tmp_z1__usunProwadzacego);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__usunProwadzacego(soap, &soap_tmp_z1__usunProwadzacego, "z1:usunProwadzacego", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__usunProwadzacego(soap, &soap_tmp_z1__usunProwadzacego, "z1:usunProwadzacego", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_11)
		return soap_closesock(soap);
	soap_default_z1__usunProwadzacegoResponse(soap, &_param_11);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__usunProwadzacegoResponse(soap, &_param_11, "z1:usunProwadzacegoResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajStudenta(const char *endpoint, const char *soap_action, std::string przedmiotID, z1__student *student, struct z1__dodajStudentaResponse &_param_12)
{	struct soap *soap = this->soap;
	struct z1__dodajStudenta soap_tmp_z1__dodajStudenta;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajStudenta.przedmiotID = przedmiotID;
	soap_tmp_z1__dodajStudenta.student = student;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__dodajStudenta(soap, &soap_tmp_z1__dodajStudenta);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__dodajStudenta(soap, &soap_tmp_z1__dodajStudenta, "z1:dodajStudenta", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__dodajStudenta(soap, &soap_tmp_z1__dodajStudenta, "z1:dodajStudenta", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_12)
		return soap_closesock(soap);
	soap_default_z1__dodajStudentaResponse(soap, &_param_12);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__dodajStudentaResponse(soap, &_param_12, "z1:dodajStudentaResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::usunStudentaZPrzedmiotu(const char *endpoint, const char *soap_action, std::string przedmiotID, z1__student *student, struct z1__usunStudentaZPrzedmiotuResponse &_param_13)
{	struct soap *soap = this->soap;
	struct z1__usunStudentaZPrzedmiotu soap_tmp_z1__usunStudentaZPrzedmiotu;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__usunStudentaZPrzedmiotu.przedmiotID = przedmiotID;
	soap_tmp_z1__usunStudentaZPrzedmiotu.student = student;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__usunStudentaZPrzedmiotu(soap, &soap_tmp_z1__usunStudentaZPrzedmiotu);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__usunStudentaZPrzedmiotu(soap, &soap_tmp_z1__usunStudentaZPrzedmiotu, "z1:usunStudentaZPrzedmiotu", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__usunStudentaZPrzedmiotu(soap, &soap_tmp_z1__usunStudentaZPrzedmiotu, "z1:usunStudentaZPrzedmiotu", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_13)
		return soap_closesock(soap);
	soap_default_z1__usunStudentaZPrzedmiotuResponse(soap, &_param_13);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__usunStudentaZPrzedmiotuResponse(soap, &_param_13, "z1:usunStudentaZPrzedmiotuResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::usunWszystkichZPrzedmiotu(const char *endpoint, const char *soap_action, std::string ID, struct z1__usunWszystkichZPrzedmiotuResponse &_param_14)
{	struct soap *soap = this->soap;
	struct z1__usunWszystkichZPrzedmiotu soap_tmp_z1__usunWszystkichZPrzedmiotu;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__usunWszystkichZPrzedmiotu.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__usunWszystkichZPrzedmiotu(soap, &soap_tmp_z1__usunWszystkichZPrzedmiotu);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__usunWszystkichZPrzedmiotu(soap, &soap_tmp_z1__usunWszystkichZPrzedmiotu, "z1:usunWszystkichZPrzedmiotu", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__usunWszystkichZPrzedmiotu(soap, &soap_tmp_z1__usunWszystkichZPrzedmiotu, "z1:usunWszystkichZPrzedmiotu", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_14)
		return soap_closesock(soap);
	soap_default_z1__usunWszystkichZPrzedmiotuResponse(soap, &_param_14);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__usunWszystkichZPrzedmiotuResponse(soap, &_param_14, "z1:usunWszystkichZPrzedmiotuResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::usunPrzedmiot(const char *endpoint, const char *soap_action, std::string ID, struct z1__usunPrzedmiotResponse &_param_15)
{	struct soap *soap = this->soap;
	struct z1__usunPrzedmiot soap_tmp_z1__usunPrzedmiot;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__usunPrzedmiot.ID = ID;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__usunPrzedmiot(soap, &soap_tmp_z1__usunPrzedmiot);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__usunPrzedmiot(soap, &soap_tmp_z1__usunPrzedmiot, "z1:usunPrzedmiot", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__usunPrzedmiot(soap, &soap_tmp_z1__usunPrzedmiot, "z1:usunPrzedmiot", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_15)
		return soap_closesock(soap);
	soap_default_z1__usunPrzedmiotResponse(soap, &_param_15);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__usunPrzedmiotResponse(soap, &_param_15, "z1:usunPrzedmiotResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::edytujProjekt(const char *endpoint, const char *soap_action, std::string przedmiotID, std::string projektID, z1__temat *projekt, struct z1__edytujProjektResponse &_param_16)
{	struct soap *soap = this->soap;
	struct z1__edytujProjekt soap_tmp_z1__edytujProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__edytujProjekt.przedmiotID = przedmiotID;
	soap_tmp_z1__edytujProjekt.projektID = projektID;
	soap_tmp_z1__edytujProjekt.projekt = projekt;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__edytujProjekt(soap, &soap_tmp_z1__edytujProjekt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__edytujProjekt(soap, &soap_tmp_z1__edytujProjekt, "z1:edytujProjekt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__edytujProjekt(soap, &soap_tmp_z1__edytujProjekt, "z1:edytujProjekt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_16)
		return soap_closesock(soap);
	soap_default_z1__edytujProjektResponse(soap, &_param_16);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__edytujProjektResponse(soap, &_param_16, "z1:edytujProjektResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::edytujTermin(const char *endpoint, const char *soap_action, std::string przedmiotID, std::string terminID, std::string salaID, z1__termin *termin, struct z1__edytujTerminResponse &_param_17)
{	struct soap *soap = this->soap;
	struct z1__edytujTermin soap_tmp_z1__edytujTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.0.13:8090/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__edytujTermin.przedmiotID = przedmiotID;
	soap_tmp_z1__edytujTermin.terminID = terminID;
	soap_tmp_z1__edytujTermin.salaID = salaID;
	soap_tmp_z1__edytujTermin.termin = termin;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_z1__edytujTermin(soap, &soap_tmp_z1__edytujTermin);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_z1__edytujTermin(soap, &soap_tmp_z1__edytujTermin, "z1:edytujTermin", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_z1__edytujTermin(soap, &soap_tmp_z1__edytujTermin, "z1:edytujTermin", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_17)
		return soap_closesock(soap);
	soap_default_z1__edytujTerminResponse(soap, &_param_17);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_z1__edytujTerminResponse(soap, &_param_17, "z1:edytujTerminResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
