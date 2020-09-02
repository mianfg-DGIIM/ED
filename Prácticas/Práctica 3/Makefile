INC = include
BIN = bin
SRC = src
OBJ = obj
ZIP = zip

$(BIN)/test: $(OBJ)/test.o
	g++ -o $(BIN)/test $(OBJ)/test.o

$(OBJ)/test.o: $(SRC)/test.cpp $(INC)/*.h
	g++ -o $(OBJ)/test.o -c $(SRC)/test.cpp -I$(INC)

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/test
	rm -f $(ZIP)/*

zip: clean
	zip -r $(ZIP)/practica2.zip *
