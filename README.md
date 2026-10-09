# Integrantes
* Kimberly Torres González
* Gerald Vindas Ramírez

# Tema
  *Tareas y Subtareas*
  Pregunta central: ¿cuál de las estructuras resulta más adecuada cuando 
  se pasa de consultar tareas individuales a
  consultar las relaciones entre una tarea y sus descendientes?
  Contexto particular: herramienta de seguimiento con la que un profesor administra las tareas de un curso.
  Al inicio registra tareas independientes (quices, prácticas) y las consulta por identificador.
  Luego asigna proyectos que se dividen en entregables y subtareas, y necesita calcular el esfuerzo total y 
  las horas de trabajo pendientes de una tarea a partir de todos sus descendientes.

# Estructuras Seleccionadas
```
Tipo         |                                       Representación Tarea-Subtarea
------------------------------------------------------------------------------------------------------
             Lista simplemente enlazada               Cada Tarea guarda el Id de su padre.
             Lista.h y Nodo.h                         No hay enlaces entre padres e hijos.
Lineal                                                Para encontrar los hijos se recorre la
                                                      lista completa.
------------------------------------------------------------------------------------------------------
             Árbol n-ario con representación          Cada nodo tiene enlaces al primerHijo,
             primerHijo y siguienteHermano            al siguienteHermano y al padre.
             Arbol.h y NodoArbol.h                    Una Raiz ficticia que posee un Id 0 agrupa
Jerárquica                                            las tareas sueltas.
------------------------------------------------------------------------------------------------------
```
Las estructuras son adaptadas del proyecto PY2 del curso desarrolladas por mi persona Kimberly Torres

# Inventario de archivos
# Tarea.h
Proposito: Tener los datos de una tarea como el id, idPadre,
nombre, esfuerzo en horas y si esta completada la tarea.
Tambien tiene ResumenTrabajo, que guarda el esfuerzo total, el esfuerzo
pendiente y la cantidad de tareas de una consulta sobre descendientes.

# Contadores.h
Proposito: Guardar los contadores de comparaciones y nodos visitados
que usan ambas estructuras.

# Nodo.h
Proposito: Nodo de la lista enlazada o Lista.h

# Lista.h
Proposito: Contiene los metodos Insertar, BuscarPorId y
ResumenDescendientes y además los contadores.

# NodoArbol.h
Proposito: Nodo del Arbol conteniendo el primer hijo,
el siguiente hermano y el padre.

# Arbol.h
Proposito: Contiene los metodos Insertar,
BuscarPorId y ResumenDescendientes y los contadores.

# prueba.cpp
Proposito: Programa principal para el estudio. Primero ejecuta las pruebas funcionales
con un ejemplo pequeño de resultados conocidos, despues genera ambas cargas con std::mt19937
y una semilla fija, ejecuta las consultas, verifica cada resultado contra un valor esperado
calculado sin usar ninguna de las dos estructuras y escribe los csv.

# salida de: parametros.txt
Proposito: Guarda la semilla y los parametros con los que se generaron las cargas.

# salida de: datos_base_N.csv
Proposito: Son las tareas usadas en la carga base para cada tamaño N

# salida de: datos_modificada_N.csv
Proposito: Tareas usadas para la carga que ya se modifico

# salida de: consultas_N.csv
Proposito: Ids de las consultas individuales y de las consultas sobre descendientes
para cada tamaño N.

# salida de: resultados.csv
Proposito: Mostrara una fila por carga, tamaño, estructura y fase (insercion,
consulta_individual y consulta_descendientes), con la cantidad de operaciones,
las comparaciones, los nodos visitados y cuantos resultados fueron correctos e incorrectos.

# Sistema de Herramientas
Estándar: C++11
Compilador: g++
Sistema Operativo: Windows 11
Terminal: Powershell
Bibliotecas estandar: <random>, <vector>, <fstream>,
<iostream> y <string>.


# Instrucciones de Ejecución

g++ -std=c++11 -Wall -Wextra -pedantic prueba.cpp -o prueba
.\prueba

Para guardar la salida de consola como evidencia:

.\prueba > registro_estudio.txt

## Procedimiento para reproducir ambas cargas

Una sola ejecución de `prueba` hace las pruebas funcionales y genera y prueba ambas cargas para N = 100, 500 y 1000 tareas,
con la semilla 2026 + N (los parametros se cambian al inicio de `prueba.cpp`).

- **Pruebas funcionales:** 5 tareas con resultados calculados a mano. Se prueban la insercion de una tarea con padre inexistente,
- busquedas de la primera, una intermedia, la ultima, una rechazada y una inexistente, y consultas de descendientes de una tarea con dos niveles, una con hijos, una sin subtareas, una completada y una inexistente.
- **Carga base:** N tareas independientes (idPadre = 0). Se ejecutan 200 búsquedas por id; el 10 % son ids que no existen.
- **Carga modificada:** las mismas N tareas, pero cada una (salvo la primera) tiene un 20 % de probabilidad de ser independiente y
-  si no es subtarea de una tarea anterior elegida al azar. Se ejecutan las mismas 200 búsquedas y
-  200 consultas de descendientes; el 10 % son ids que no existen.
- Cada tarea tiene un esfuerzo de 1 a 8 horas, y el 40 % está completada.
- Las mismas tareas se insertan en el mismo orden en la lista y en el árbol, y ambas reciben las mismas consultas.
-  Los contadores se reinician antes de cada fase y cada resultado se verifica contra el valor esperado.

**Definiciones**

- `ResumenDescendientes(id)`: suma el esfuerzo total y el esfuerzo pendiente (tareas no completadas) de la tarea y
- de todos sus descendientes, incluyendo la tarea misma, y cuenta cuantas tareas sumo. Retorna false si la tarea no existe.
- **Nodos visitados:** cada nodo que examina la estructura, incluyendo el recorrido de hermanos en el árbol.
- **Comparaciones:** cada comparación de un id (`id` o `idPadre`) contra el valor buscado.

## Resultados que deberían observarse

`prueba` termina con `Comprobaciones fallidas: 0` de 10 032 comprobaciones.

| Carga | Operación (N = 1000) | Lista | Árbol |
|---|---|---|---|
| Base | buscar | 534.4 | 535.4 |
| Modificada | buscar | 534.4 | 553.9 |
| Modificada | resumen de descendientes | 4 309.0 | 568.7 |

*Promedio de nodos visitados por consulta; los demás tamaños están en `resultados.csv`.*

Construir el árbol cuesta más que construir la lista: con N = 1000 en la carga base, el árbol visita 500 500 nodos 
porque recorre a todos los hermanos para colgar cada tarea al final, mientras que la lista no visita ninguno.
En la carga modificada el árbol visita 224 159 nodos y la lista 203 867, porque ambas buscan al padre de cada tarea.

## Limitaciones conocidas

- Los datos son sintéticos, no provienen de un curso real.
- Ninguna estructura está ordenada por id, así que ambas buscan con un recorrido.
- La forma de la carga modificada depende de la probabilidad de 20 % y de elegir el padre al azar; otra forma (por ejemplo ramas más profundas)
-  puede dar otros conteos.
- Se midió trabajo (contadores), no tiempo ni memoria.
- Solo se probó con g++, no con BCC 10.2.

# Declaración de uso de IA
Herramienta: Gemini
Modelo: 4 Argon

1. Finalidad: aclarar conceptos
   Consulta: significado de carga base, carga modificada y contadores
   Parte afectada: comprensión del enunciado

2. Finalidad: aclarar conceptos
   Consulta: elementos de una portada estudiantil APA 7
   Parte afectada: portada

3. Finalidad: interpretar un error
   Consulta: error de PowerShell al ejecutar `prueba` sin `.\`
   Parte afectada: ejecución del prototipo

4. Finalidad: consultar sintaxis
   Consulta: opción `-std=c++11` de g++
   Parte afectada: compilación

5. Corrección de errores ortográficos y aplicación de formato APA7 al texto y links

