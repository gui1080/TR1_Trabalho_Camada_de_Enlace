sim: simulador.o CamadaFisica.o CamadaEnlace.o
	g++ -o sim simulador.o CamadaFisica.o CamadaEnlace.o

simulador.o: simulador.cpp CamadaFisica.h CamadaEnlace.h
	g++ -c simulador.cpp

CamadaFisica.o: CamadaFisica.cpp CamadaEnlace.cpp CamadaFisica.h CamadaEnlace.h
	g++ -c CamadaFisica.cpp

CamadaEnlace.o: CamadaFisica.cpp CamadaEnlace.cpp CamadaFisica.h CamadaEnlace.h
	g++ -c CamadaEnlace.cpp

clean:
	rm *.o sim
