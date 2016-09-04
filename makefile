obj = ./build/Date.o ./build/Meeting.o ./build/User.o ./build/Storage.o ./build/AgendaService.o ./build/AgendaUI.o ./build/Main.o

vpath %.hpp ./include 
vpath %.cpp ./src

Agenda: Date.o Meeting.o User.o Storage.o AgendaService.o AgendaUI.o Main.o
	g++ -std=c++11 $(obj) -o ./bin/Agenda.exe
Date.o: Date.hpp Date.cpp
	g++ -std=c++11 ./src/Date.cpp -c -o ./build/Date.o
Meeting.o: Meeting.hpp Meeting.cpp
	g++ -std=c++11 ./src/Meeting.cpp -c -o ./build/Meeting.o 
User.o: User.hpp User.cpp
	g++ -std=c++11 ./src/User.cpp -c -o ./build/User.o
Storage.o: Storage.cpp Storage.cpp
	g++ -std=c++11 ./src/Storage.cpp -c -o ./build/Storage.o
AgendaService.o: AgendaService.hpp ./AgendaService.cpp
	g++ -std=c++11 ./src/AgendaService.cpp -c -o ./build/AgendaService.o
AgendaUI.o: AgendaUI.cpp AgendaUI.cpp
	g++ -std=c++11 ./src/AgendaUI.cpp -c -o ./build/AgendaUI.o
Main.o: Agenda.cpp
	g++ -std=c++11 ./src/Agenda.cpp -c -o ./build/Main.o