.PHONY: x clean tar

EJECUTABLE= practica_objetos_B3

MODULOS:= practica_objetos_B3.o\
         objetos_B3.o\
         file_ply_stl.o\
      
LIBS:= -L/usr/lib -framework OpenGL -framework GLUT -lm -lc -lstdc++ -lpthread
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

clean:
	rm -rf *.o $(EJECUTABLE)