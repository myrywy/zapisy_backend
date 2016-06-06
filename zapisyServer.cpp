#include "zapisy.nsmap"        // XML namespace mapping table (only needed once at the global level)
#include "soapzapisyService.h" // the service class, also #includes "soapH.h" and "soapStub.h"
#include <iostream>
#include <sstream>

#include "mysql_connection.h"

#include "bazadanych.h"
#include "wsserver.hpp"

int main()
{
    WSServer server("server.properties");
}

