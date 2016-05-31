sources= ../bazadanych.cpp ../tabela.cpp ../zapytanie.cpp
test_sources=zapytanie_test.cpp test_utils.cpp
objects=$(sources:.cpp=.o)
pathMysqlHeaders=../libs/mysql/include
pathMysqlLibs=../libs/mysql
pathMysqlCientLib=../libs/mysql
headers=-I$(pathMysqlHeaders) -I$(pathGsoapHeaders) -I$(pathMysqlHeaders)/cppcon -Ilibs

LDFLAGS="-Wl,--no-as-needed"

all: zapytanie_test

#zapisy: $(objects)
#	g++ -lm $^ -o $@ -L$(pathGsoapLibs) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -static -lgsoap++ -lmysqlclient -lmysqlcppconn-static -lpthread -ldl

zapytanie_test: $(test_sources)
	g++ --std=c++11 -lm $(test_sources) -o $@ $(objects) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -static -lmysqlclient -lmysqlcppconn-static -lpthread -ldl -lboost_unit_test_framework

.PHONY: clean

clean:
	rm -f zapisy_test
