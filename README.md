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
Tipo         |
------------------------------------------------------------------------------------------------------
             | Lista simplemente
Lineal       | enlazada
             | Lista.h y Nodo.h
             |
---------------------------------------------------------------------------------------------------
             |
Jerárquica   |
             |
             |
----------------------------------------------------------------------------------------------------

# Instrucciones de Ejecucción

g++ -std=c++11 -Wall pruebas_funcionales.cpp -o pruebas
.\pruebas

g++ -std=c++11 -Wall main.cpp -o estudio
mkdir resultados
cd resultados
..\estudio
