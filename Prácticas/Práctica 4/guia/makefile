INC = include
BIN = bin
SRC = src
OBJ = obj
ZIP = zip

$(BIN)/usoguia: $(OBJ)/usoguia.o $(OBJ)/Guia_Tlf.o
	g++ -o $(BIN)/usoguia $(OBJ)/usoguia.o $(OBJ)/Guia_Tlf.o

$(OBJ)/usoguia.o: $(SRC)/usoguia.cpp $(INC)/*.h
	g++ -o $(OBJ)/usoguia.o -c $(SRC)/usoguia.cpp -I$(INC)

$(OBJ)/Guia_Tlf.o: $(SRC)/Guia_Tlf.cpp $(INC)/Guia_Tlf.h
	g++ -o $(OBJ)/Guia_Tlf.o -c $(SRC)/Guia_Tlf.cpp -I$(INC)

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/usoguia
	rm -f $(ZIP)/*

zip: clean
	zip -r $(ZIP)/guia.zip *
