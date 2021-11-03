.PHONY: all simulador run

all: simulador

simulador: src/CamadaEnlace.cpp src/CamadaFisica.cpp src/Helpers.cpp src/Simulador.cpp
		g++ src/CamadaEnlace.cpp src/CamadaFisica.cpp src/Helpers.cpp src/Simulador.cpp -o build/simulador

run: simulador
		./build/simulador
