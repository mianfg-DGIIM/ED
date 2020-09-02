#!/bin/bash

unzip diccionario.zip -d diccionario
unzip guia.zip -d guia
cd guia; make; cd ..;
cd diccionario; make; cd ..;
cd diccionario
./bin/usodiccionario < ./data/data.txt
echo "\n\n====================================="
cd ..; cd guia
./bin/usoguia < ./data/data.txt
