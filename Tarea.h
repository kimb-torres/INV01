#ifndef TAREA_H
#define TAREA_H
#include <string>

struct Tarea {
    int id;
    int idPadre;
    std::string nombre;
    int esfuerzo;
    bool completada;
};

#endif
