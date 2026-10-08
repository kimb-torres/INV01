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

# Instrucciones de Ejecucción

g++ -std=c++11 -Wall pruebas_funcionales.cpp -o pruebas
.\pruebas

g++ -std=c++11 -Wall main.cpp -o estudio
mkdir resultados
cd resultados
..\estudio
