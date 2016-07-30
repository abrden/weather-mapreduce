# Weather MapReduce
## Trabajo Práctico 3 - 75.42 Taller de Programación I (FIUBA)
Para realizar operaciones de manera eficiente, surge un esquema que las paraleliza: MapReduce. Este esquema consiste en separar un proceso que recibe y devuelve pares (clave, valor) en unas funciones   ​
map(), y otras reduce(). En este ejercicio, se implementará un esquema MapReduce simple, en el que los Mappers deberán pertenecer a procesos *client*, y los Reducers deberán correr en hilos separados de un *server*. Se deberá deducir, a partir de listas de temperaturas máximas de distintas ciudades del mundo, cuáles fueron las más calurosas del mes de marzo, día por día.

### Verificación de Normas de Codificación
```python ./cpplint.py --extensions=h,hpp,c,cpp --filter=`cat filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'` ```

### Compilación
```cd solucion && make -f Makefile_client_server```

### Corrida sin Valgrind
Script en directorio *run*  
```chmod +x run.sh free_port.sh;./run.sh $(./free_port.sh 10001) no-valgrind```

### Corrida con Valgrind
Script en directorio *run*  
```chmod +x run.sh free_port.sh;./run.sh $(./free_port.sh 10001) valgrind```

### Referencias
* [MapReduce](https://es.wikipedia.org/wiki/MapReduce)

:dizzy:


