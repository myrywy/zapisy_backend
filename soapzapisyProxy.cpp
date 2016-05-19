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
        {"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
        {"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
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

int zapisyProxy::zapiszProjekt(const char *endpoint, const char *soap_action, std::string ID, z1__student *zapisywany, struct z1__zapiszProjektResponse &_param_1)
{	struct soap *soap = this->soap;
	struct z1__zapiszProjekt soap_tmp_z1__zapiszProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__zapiszProjekt.ID = ID;
	soap_tmp_z1__zapiszProjekt.zapisywany = zapisywany;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__zapiszProjektResponse(soap, &_param_1, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajProjekt(const char *endpoint, const char *soap_action, z1__temat *projekt, struct z1__dodajProjektResponse &_param_2)
{	struct soap *soap = this->soap;
	struct z1__dodajProjekt soap_tmp_z1__dodajProjekt;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajProjekt.projekt = projekt;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__dodajProjektResponse(soap, &_param_2, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::zapiszTermin(const char *endpoint, const char *soap_action, std::string ID, z1__student *zapisywany, struct z1__zapiszTerminResponse &_param_3)
{	struct soap *soap = this->soap;
	struct z1__zapiszTermin soap_tmp_z1__zapiszTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__zapiszTermin.ID = ID;
	soap_tmp_z1__zapiszTermin.zapisywany = zapisywany;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__zapiszTerminResponse(soap, &_param_3, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int zapisyProxy::dodajTermin(const char *endpoint, const char *soap_action, z1__termin *termin, struct z1__dodajTerminResponse &_param_4)
{	struct soap *soap = this->soap;
	struct z1__dodajTermin soap_tmp_z1__dodajTermin;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__dodajTermin.termin = termin;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__dodajTerminResponse(soap, &_param_4, "", NULL);
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
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujProjekt.ID = ID;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__eksportujProjektResponse(soap, &_param_5, "", NULL);
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
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujTermin.ID = ID;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__eksportujTerminResponse(soap, &_param_6, "", NULL);
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
		soap_endpoint = "http://127.0.0.1/";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_z1__eksportujPrzedmiot.ID = ID;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
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
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_z1__eksportujPrzedmiotResponse(soap, &_param_7, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
