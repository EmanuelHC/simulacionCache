%-----------------------------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License
    
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

%-----------------------------------------------------------------------------------------

Autores: Felipe Moya Coto, Emanuel Hernández Castillo

RESUMEN DEL PROYECTO

El presente trabajo pretende simular el funcionamiento de una memoria caché mediante
utilizando C++. Se propuso simular el comportamiento para 3 distintos tipos de mapeo, 
directo, 2 way-associative y 4 way-associative con distintos tamaños de caché y bloque. 
Se utilizó el archivo que provee el link http://ie0521.jsdanielh.org/memory-tracegcc.trace.gz
y se graficó el rendimiento del caché para los distintos casos ya mencionados, con uso del 
miss rate como indicador de rendimiento.

%-----------------------------------------------------------------------------------------

COMPILACIÓN Y EJECUCIÓN

El proyecto consta de los archivos cache.cpp, cache.h y Makefile. Para compilar y ejecutar el proyecto, 
en la misma carpeta que contiene los archivos cache.cpp, cache.h y Makefile (asumiendo que el archivo .trace 
también se encuentra en esta carpeta), se deben seguir los siguentes pasos, en una terminal de linux:

- $ make
- $ ./cache [asociatividad] [tamaño del caché] [tamaño del 
bloque]

Donde la asociatividad se escribe como: n-way-associative, donde n = 1,2,4.
El tamaño de caché se asume en kilobytes [KB] y el tamaño del bloque en bytes [B].
Ejemplos de ejecución en la terminal de linux:

Para mapeo asociativo, tipo 2-way associative:
$ ./cache 2-way-associative 64 8

Esto sería un caché de 64 KB de memoria, con bloques de 8 bytes. 

Para mapeo asociativo, tipo 4-way associtive:
$ ./cache 4-way-associative 256 16

Esto sería un caché de 256 KB de memoria, con bloques de 16 bytes.

Ó bien, para mapeo directo:
$ ./cache 1-way-associative 128 4

Esto sería un caché de 128 KB de memoria, con bloques de 4 bytes.

%-----------------------------------------------------------------------------------------

RESULTADOS ESPERADOS

Una vez ejecutado el simulador, la consola imprimirá la cantidad de misses y hits totales, 
tanto para writes como para reads, ya que se asumió que las escrituras eran del tipo write-allocate;
así como se muestra el miss rate total en consola. Como el caché hace uso de una política de 
escritura aleatoria, al correr varias veces la simulación para un mismo caché, el miss rate resultante
puede variar ligeramente, sin alejarse mucho de su promedio.

%-----------------------------------------------------------------------------------------

FIN
