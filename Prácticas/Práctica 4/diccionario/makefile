INC = include
BIN = bin
SRC = src
OBJ = obj
ZIP = zip

$(BIN)/usodiccionario: $(OBJ)/usodiccionario.o
	g++ -o $(BIN)/usodiccionario $(OBJ)/usodiccionario.o

$(OBJ)/usodiccionario.o: $(SRC)/usodiccionario.cpp $(INC)/*.h
	g++ -o $(OBJ)/usodiccionario.o -c $(SRC)/usodiccionario.cpp -I$(INC)

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/usodiccionario
	rm -f $(ZIP)/*

zip: clean
	zip -r $(ZIP)/diccionario.zip *
