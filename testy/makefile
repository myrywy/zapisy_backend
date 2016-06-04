sources= ../bazadanych.cpp ../tabela.cpp ../zapytanie.cpp ../soapC.cpp ../soapzapisyProxy.cpp ../soapzapisyService.cpp ../zapisyService.cpp 
test_sources=zapytanie_test.cpp test_utils.cpp bazadanych_test.cpp
objects=$(sources:.cpp=.o)
pathMysqlHeaders=../libs/mysql/include
pathMysqlLibs=../libs/mysql
pathMysqlCientLib=../libs/mysql
pathGsoapLibs=../libs/gsoap
pathGsoapHeaders=libs/gsoap/import
headers=-I$(pathMysqlHeaders) -I$(pathGsoapHeaders) -I$(pathMysqlHeaders)/cppcon -Ilibs

LDFLAGS="-Wl,--no-as-needed"

all: zapytanie_test bazadanych_test

#zapisy: $(objects)
#	g++ -lm $^ -o $@ -L$(pathGsoapLibs) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -static -lgsoap++ -lmysqlclient -lmysqlcppconn-static -lpthread -ldl

zapytanie_test: zapytanie_test.cpp test_utils.cpp
	g++ --std=c++11 -lm $^ -o $@ $(objects) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -L$(pathGsoapLibs) $(headers) -static -lgsoap++ -lmysqlclient -lmysqlcppconn-static -lpthread -ldl -lboost_unit_test_framework

bazadanych_test: bazadanych_test.cpp test_utils.cpp
	g++ --std=c++11 -lm $^ -o $@ $(objects) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -L$(pathGsoapLibs) $(headers) -static -lgsoap++ -lmysqlclient -lmysqlcppconn-static -lpthread -ldl -lboost_unit_test_framework


.PHONY: clean

clean:
	rm -f zapisy_test bazadanych_test
