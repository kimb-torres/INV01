# Integrantes
* Kimberly Torres González*
* Gerald Vindas Ramírez*

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

# Instrucciones de Ejecucción

g++ -std=c++11 -Wall pruebas_funcionales.cpp -o pruebas
.\pruebas

g++ -std=c++11 -Wall main.cpp -o estudio
mkdir resultados
cd resultados
..\estudio
