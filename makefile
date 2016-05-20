sources=zapisyServer.cpp soapC.cpp zapisyService.cpp soapzapisyService.cpp soapzapisyProxy.cpp bazadanych.cpp
objects=$(sources:.cpp=.o)
pathGsoapHeaders=libs/gsoap/import
pathGsoapLibs=libs/gsoap
pathMysqlHeaders=libs/mysql/include
pathMysqlLibs=libs/mysql
pathMysqlCientLib=libs/mysql
headers=-I$(pathMysqlHeaders) -I$(pathGsoapHeaders) -I$(pathMysqlHeaders)/cppcon -Ilibs

LDFLAGS="-Wl,--no-as-needed"

all: zapisy 

zapisy: $(objects)
	g++ -lm $^ -o $@ -L$(pathGsoapLibs) -L$(pathMysqlLibs) -L$(pathMysqlCientLib) -static -lgsoap++ -lmysqlclient -lmysqlcppconn-static -lpthread -ldl

zapisyServer.o: zapisyServer.cpp soapzapisyService.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

zapisyService.o: zapisyService.cpp soapzapisyService.h soapH.h soapStub.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

soapzapisyService.o: soapzapisyService.cpp  soapzapisyService.h soapH.h soapStub.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

soapzapisyProxy.o: soapzapisyProxy.cpp soapzapisyProxy.h soapH.h soapStub.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

bazadanych.o: bazadanych.cpp bazadanych.h soapzapisyService.h soapH.h soapStub.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

soapC.o: soapC.cpp soapH.h soapStub.h
	g++ -Wall -std=c++11 -c $< -o $@ $(headers)

.PHONY: clean

clean:
	rm -f zapisy $(objects)
