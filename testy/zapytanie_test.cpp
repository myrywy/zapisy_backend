#define BOOST_TEST_MODULE Zapytanie_test
#include <boost/test/included/unit_test.hpp>
#include "../zapytanie.h"
#include "../tabela.h"
#include "test_utils.hpp"
#include "../zapisy.nsmap"        // XML namespace mapping table (only needed once at the global level)


BOOST_AUTO_TEST_SUITE (stringtest)

BOOST_AUTO_TEST_CASE (konstruktory)
{
    string z=Tabela("T").select("k").stworzSql();
    if(!sqlCmp(z,"SELECT k FROM T;")){
        BOOST_ERROR("Wygenerowano nieprawidlowe polecenie SQL:\n"+z);
    }
}

BOOST_AUTO_TEST_SUITE_END( )
