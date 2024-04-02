# Especifica el compilador
COMPILADOR = g++

# Bandera de compilación
BANDERA = -std=c++17 -Wall -g

# Directorio de los archivos de cabecera
CARPETASCABECERA = cabeceros

# Obtén la lista de archivos de implementación
SRCS = $(wildcard *.cpp)

# Objetos generados a partir de los archivos de implementación
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
NOMBRE = contactos

# Regla para construir el ejecutable
$(NOMBRE): $(OBJS)
	$(COMPILADOR) $(BANDERA) -o $@ $^

# Regla para construir los objetos
%.o: %.cpp
	$(COMPILADOR) $(BANDERA) -I$(CARPETASCABECERA) -c -o $@ $<

# Regla para limpiar los archivos generados
clean:
	rm -f $(NOMBRE) $(OBJS)

# Regla para ejecutar el programa
run: $(NOMBRE)
	./$(NOMBRE)