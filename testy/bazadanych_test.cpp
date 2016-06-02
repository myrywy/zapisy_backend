#define BOOST_TEST_MODULE BazaDanych_test
#include <boost/test/included/unit_test.hpp>
#include "../bazadanych.h"
#include "test_utils.hpp"
#include <iostream>

BOOST_AUTO_TEST_SUITE (baza)

BOOST_AUTO_TEST_CASE (parseCsv_test)
{
    string s1="a;b;c\nd;e;f";
    vector< vector<string> > v1{{"a","b","c"},{"d","e","f"}};
    vector<string> v2{"a","b","c"};
    vector<string> ev{""};
    vector< vector<string> > evv;
    BOOST_CHECK(BazaDanych::splitString("",',')==ev);
    BOOST_CHECK(BazaDanych::splitString(",",',')==(vector<string>({"",""})));
    BOOST_CHECK(BazaDanych::splitString("a,b,c",',')==v2);


    BOOST_CHECK(BazaDanych::parseCsv("",',',';')==(vector<vector<string> >({{""}})));
    BOOST_CHECK(BazaDanych::parseCsv(s1,';','\n')==v1);
}

BOOST_AUTO_TEST_SUITE_END( )
