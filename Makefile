all:
	g++ main.cpp -o teste -std=c++11 -lboost_iostreams -lboost_system -lboost_filesystem -lgsl -lgslcblas
run:
	./teste
