.PHONY: x clean tar

EJECUTABLE= practica_objetos_B5

MODULOS:= practica_objetos_B5.o\
         objetos_B5.o\
         file_ply_stl.o\
      
LIBS:= -L/usr/lib -framework OpenGL -framework GLUT -lm -lc -lstdc++ -lpthread
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE)
	./$(EJECUTABLE) ant

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

clean:
	rm -rf *.o $(EJECUTABLE)

