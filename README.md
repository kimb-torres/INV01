# Integrantes
* Kimberly Torres González
* Gerald Vindas Ramírez

 # Tema
  *Tareas y Subtareas*
  Pregunta central: ¿cuál de las estructuras resulta más adecuada cuando se pasa de consultar tareas individuales a
  consultar las relaciones entre una tarea y sus descendientes?
  Contexto particular: herramienta de seguimiento con la que un profesor administra las tareas de un curso.
  Al inicio registra tareas independientes (quices, prácticas) y las consulta por identificador.
  Luego asigna proyectos que se dividen en entregables y subtareas, y necesita calcular las horas de trabajo pendientes de una tarea a partir de todos sus descendientes.
  
# Estructuras Seleccionadas
Tipo         |                                       Representación Tarea-Subtarea
------------------------------------------------------------------------------------------------------
             Lista simplemente enlazada               Cada Tarea guarda el Id de su padre.           
             Lista.h y Nodo.h                         No hay enlaces entre padres y hijos
Lineal       
             
-----------------------------------------------------------------------------------------------------
             Árbol n-arios con representación         Cada nodo tiene enlaces al primerHijo
             primerHijo y siguienteHermano            al siguienteHermano y al padre.
             Arbol.h y NodoArbol.h                    Una Raiz ficticia que posee un Id 0 agrupa
                                                      las tareas sueltas
Jerárquica             
             
----------------------------------------------------------------------------------------------------
Las estructuras son adaptadas del proyecto PY2 del curso desarrolladas por mi persona Kimberly Torres

# Inventario de archivos
# Tarea.h

Proposito: Tener los datos de una tarea como el id,idPadre
nombre, esfuerzo en las horas y si esta completada la tarea

# Nodo.h
Proposito: Nodo de la lista enlazada o Lista.h

# Lista.h
proposito: Enlaza con AgregarFinal el BuscarPorId y 
EsfuerzoPendiente y además de contadores

# NodoArbol.h
Proposito: Nodo del Arbol conteniendo el primer hijo,
el siguiente hermano y el padre.

# Arbol.h
Proposito: Contiene los metodos Insertar,
BuscarPorId y EsfuerzoPendienten y contadores.

# Generador.h
Proposito: Genera las tareas dela carga base
y de la carga que ya se modifico con std:: mt19937  y el uso fijo

# Referncia.h
Proposito: Calcular independientemente con std::vector,
con propoposito de verificar que ambas estructuras respondan correctamente.

#  pruevas_funcionales.cpp
Proposito: Pruebas con un ejemplo pequeño de resultados conocidos

# Main.h
Proposito: Programa principal paar el estudio, genera ambas cargas,
ejecuta las consultas y verifica y escribe los csv

# salida de : tareas-base_N.csv
Proposito: Son las tareas usadas en la carga base para cada tamaño N

# salia de : tareas_modificadas_N.csv
Proposito: Tareas usadas para la carga que ya se modifico

# resultados.cvs
Proposito: Mostrara una fila para cada estructura, resultado, valor esperado,
si es correcto, nodos que se visitaron y las comparaciones realizadas.

# Resumen
Proposito: Promedios por carga, tamaño, operación y la estructura

# salida de: registro_priuevbas_funcionales.txt
Proposito:  salida ala consola de pruevas  que contiene las evidencias de que ambas
estructuras dan los resultados que se esperan.

# salida de: registro_estudio.txt
proposito: Salida a consola d estudio con la semilla en 2026 que contiene tabla de resumen
y cantidad de resultados incorrectos.

# Sistema de Herramientas
Estándar: C++11
Compilador: g++
Sistema Operativo: Windows 11
Terminal:; Powershell
Bibliotecas estandar: <ramdon>,<vector>, <map>, <fstream>, 
<iostream>, <iomanip>, <string> y <cstdlib>.


# Instrucciones de Ejecucción

g++ -std=c++11 -Wall pruebas_funcionales.cpp -o pruebas
.\pruebas

g++ -std=c++11 -Wall main.cpp -o estudio
mkdir resultados
cd resultados
..\estudio

## Procedimiento para reproducir ambas cargas

Una sola ejecución de `estudio` genera y prueba ambas cargas para N = 100, 500, 1000 y 2000 tareas, con la semilla 2026 (se puede cambiar: `..\estudio.exe 12345`).

- **Carga base:** N tareas independientes. Se ejecutan 15 búsquedas por id: primera, media, última, 10 aleatorias y 2 inexistentes.
- **Carga modificada:** N tareas anidadas hasta 4 niveles (proyecto → entregable → tarea → subtarea). Se ejecutan las mismas 15 búsquedas y 15 consultas de esfuerzo pendiente (proyecto mayor, tarea intermedia, hoja, 10 aleatorias y 1 inexistente).
- Cada tarea tiene un esfuerzo de 1 a 8 horas, y el 30 % está completada.
- Las mismas tareas se insertan en el mismo orden en la lista y en el árbol. Los contadores se reinician antes de cada consulta y cada resultado se verifica contra `Referencia.h`.

**Definiciones**

- `EsfuerzoPendiente(id)`: suma del esfuerzo de los descendientes no completados de la tarea (sin incluirla). Retorna −1 si no existe.
- **Nodos visitados:** cada nodo que examina la estructura.
- **Comparaciones:** cada comparación de un id (`id` o `idPadre`).

## Resultados que deberían observarse

`pruebas` termina con `Fallos: 0` y `estudio` con `Resultados incorrectos: 0 de 376`.

| Carga | Operación (N = 2000) | Lista | Árbol |
|---|---|---|---|
| Base | buscar | 981.6 | 982.6 |
| Modificada | buscar | 1253.5 | 1217.5 |
| Modificada | esfuerzo pendiente | 96 694.5 | 664.4 |

*Promedio de nodos visitados por consulta; los demás tamaños están en `resumen.csv`.*

Construir el árbol cuesta más que construir la lista: con N = 2000 en la carga modificada, el árbol visita 1 104 567 nodos buscando al padre de cada tarea, mientras que la lista no visita ninguno.

## Limitaciones conocidas

- Los datos son sintéticos, no provienen de un curso real.
- Ninguna estructura está ordenada por id, así que ambas buscan con un recorrido completo.
- En la carga modificada, el proyecto 1 es también el más grande, así que esos dos casos coinciden.
- Se midió trabajo (contadores), no tiempo ni memoria.
- Solo se probó con g++, no con BCC 10.2.

- # Declaración de uso de IA
Herramienta: Gemini
Modelo: 4 Argon

1. Finalidad: aclarar conceptos
   Consulta: significado de carga base, carga modificada y contadores
   Parte afectada: comprensión del enunciado

2. Finalidad: aclarar conceptos
   Consulta: elementos de una portada estudiantil APA 7
   Parte afectada: portada

3. Finalidad: interpretar un error
   Consulta: error de PowerShell al ejecutar `pruebas` sin `.\`
   Parte afectada: ejecución del prototipo

4. Finalidad: consultar sintaxis
   Consulta: opción `-std=c++11` de g++
   Parte afectada: compilación
   
5. Corrección de errores ortográficos y aplicación de formato APA7 a links

Las estructuras, cargas, conteos, fuentes, código, resultados y redacción fueron realizados por el grupo sin IA.+
