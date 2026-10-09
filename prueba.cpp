#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include "Tarea.h"
#include "Lista.h"
#include "Arbol.h"

const unsigned SEMILLA_BASE            = 2026;
const int      TAMANOS[]               = {100, 500, 1000};
const int      CANT_TAMANOS            = 3;
const int      CONSULTAS_INDIVIDUALES  = 200;
const int      CONSULTAS_DESCENDIENTES = 200;
const double   PROB_ID_INEXISTENTE     = 0.10;
const double   PROB_TAREA_RAIZ         = 0.20;
const double   PROB_COMPLETADA         = 0.40;
const int      ESFUERZO_MIN            = 1;
const int      ESFUERZO_MAX            = 8;

int gCorrectas = 0;
int gFallidas  = 0;

void Verificar(bool bCondicion, const std::string &sDescripcion) {
    if (bCondicion) {
        gCorrectas++;
        std::cout << "  OK    " << sDescripcion << "\n";
    } else {
        gFallidas++;
        std::cout << "  FALLO " << sDescripcion << "\n";
    }
}

template <typename Estructura>
bool BusquedaCorrecta(Estructura &rEstructura, int nId, const char *pNombreEsperado) {
    Tarea *pTarea = rEstructura.BuscarPorId(nId);
    if (pNombreEsperado == nullptr) return pTarea == nullptr;
    return pTarea != nullptr && pTarea->id == nId && pTarea->nombre == pNombreEsperado;
}

template <typename Estructura>
bool DescendientesCorrecto(Estructura &rEstructura, int nId, bool bExiste,
                           int nTotal, int nPendiente, int nTareas) {
    ResumenTrabajo resumen;
    bool bEncontrada = rEstructura.ResumenDescendientes(nId, resumen);
    if (!bExiste) return !bEncontrada;
    return bEncontrada && resumen.esfuerzoTotal == nTotal &&
           resumen.esfuerzoPendiente == nPendiente && resumen.tareas == nTareas;
}

void ProbarCasosFijos() {
    std::cout << "=== Casos fijos (comprobacion funcional) ===\n";
    Tarea tareas[] = {
        {1, 0, "Proyecto 1", 0, false},
        {2, 1, "Entregable informe", 0, false},
        {3, 1, "Entregable video", 3, false},
        {4, 2, "Redactar metodologia", 4, false},
        {5, 2, "Redactar resumen", 2, true}
    };

    Lista<Tarea> lista;
    Arbol<Tarea> arbol;
    for (int i = 0; i < 5; i++) {
        Verificar(lista.Insertar(tareas[i]), "Lista inserta tarea " + std::to_string(tareas[i].id));
        Verificar(arbol.Insertar(tareas[i]), "Arbol inserta tarea " + std::to_string(tareas[i].id));
    }

    Tarea huerfana = {9, 50, "Padre inexistente", 1, false};
    Verificar(!lista.Insertar(huerfana), "Lista rechaza tarea con padre inexistente");
    Verificar(!arbol.Insertar(huerfana), "Arbol rechaza tarea con padre inexistente");

    struct CasoBusqueda { int id; const char *nombre; };
    CasoBusqueda busquedas[] = {
        {1, "Proyecto 1"},
        {4, "Redactar metodologia"},
        {5, "Redactar resumen"},
        {9, nullptr},
        {99, nullptr}
    };
    for (int i = 0; i < 5; i++) {
        std::string sId = std::to_string(busquedas[i].id);
        Verificar(BusquedaCorrecta(lista, busquedas[i].id, busquedas[i].nombre), "Lista buscar " + sId);
        Verificar(BusquedaCorrecta(arbol, busquedas[i].id, busquedas[i].nombre), "Arbol buscar " + sId);
    }

    struct CasoDescendientes { int id; bool existe; int total; int pendiente; int tareas; };
    CasoDescendientes descendientes[] = {
        {1, true, 9, 7, 5},
        {2, true, 6, 4, 3},
        {3, true, 3, 3, 1},
        {5, true, 2, 0, 1},
        {99, false, 0, 0, 0}
    };
    for (int i = 0; i < 5; i++) {
        const CasoDescendientes &c = descendientes[i];
        std::string sId = std::to_string(c.id);
        Verificar(DescendientesCorrecto(lista, c.id, c.existe, c.total, c.pendiente, c.tareas),
                  "Lista descendientes de " + sId);
        Verificar(DescendientesCorrecto(arbol, c.id, c.existe, c.total, c.pendiente, c.tareas),
                  "Arbol descendientes de " + sId);
    }
}

std::vector<Tarea> GenerarTareasIndependientes(int n, std::mt19937 &rGenerador) {
    std::uniform_int_distribution<int> esfuerzo(ESFUERZO_MIN, ESFUERZO_MAX);
    std::bernoulli_distribution completada(PROB_COMPLETADA);
    std::vector<Tarea> tareas;
    for (int i = 1; i <= n; i++) {
        Tarea t = {i, 0, "Tarea " + std::to_string(i), esfuerzo(rGenerador), completada(rGenerador)};
        tareas.push_back(t);
    }
    return tareas;
}

std::vector<Tarea> AnidarTareas(std::vector<Tarea> tareas, std::mt19937 &rGenerador) {
    std::bernoulli_distribution esRaiz(PROB_TAREA_RAIZ);
    for (size_t i = 1; i < tareas.size(); i++) {
        if (!esRaiz(rGenerador)) {
            std::uniform_int_distribution<int> padre(1, (int)i);
            tareas[i].idPadre = padre(rGenerador);
        }
    }
    return tareas;
}

std::vector<int> GenerarConsultas(int nCantidad, int n, std::mt19937 &rGenerador) {
    std::bernoulli_distribution inexistente(PROB_ID_INEXISTENTE);
    std::uniform_int_distribution<int> existente(1, n);
    std::uniform_int_distribution<int> fueraDeRango(n + 1, 2 * n);
    std::vector<int> consultas;
    for (int i = 0; i < nCantidad; i++) {
        consultas.push_back(inexistente(rGenerador) ? fueraDeRango(rGenerador)
                                                    : existente(rGenerador));
    }
    return consultas;
}

struct Esperado {
    std::vector<int> total, pendiente, tareas;
};

Esperado CalcularEsperado(const std::vector<Tarea> &tareas) {
    int n = (int)tareas.size();
    Esperado e;
    e.total.assign(n + 1, 0);
    e.pendiente.assign(n + 1, 0);
    e.tareas.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        e.total[i] = tareas[i - 1].esfuerzo;
        e.pendiente[i] = tareas[i - 1].completada ? 0 : tareas[i - 1].esfuerzo;
        e.tareas[i] = 1;
    }
    for (int i = n; i >= 1; i--) {
        int p = tareas[i - 1].idPadre;
        if (p != 0) {
            e.total[p] += e.total[i];
            e.pendiente[p] += e.pendiente[i];
            e.tareas[p] += e.tareas[i];
        }
    }
    return e;
}

void GuardarDatos(const std::string &sArchivo, const std::vector<Tarea> &tareas) {
    std::ofstream archivo(sArchivo.c_str());
    archivo << "id,idPadre,nombre,esfuerzo,completada\n";
    for (size_t i = 0; i < tareas.size(); i++) {
        archivo << tareas[i].id << "," << tareas[i].idPadre << "," << tareas[i].nombre << ","
                << tareas[i].esfuerzo << "," << (tareas[i].completada ? 1 : 0) << "\n";
    }
}

void GuardarConsultas(const std::string &sArchivo, const std::vector<int> &individuales,
                      const std::vector<int> &descendientes) {
    std::ofstream archivo(sArchivo.c_str());
    archivo << "tipo,id\n";
    for (size_t i = 0; i < individuales.size(); i++) archivo << "individual," << individuales[i] << "\n";
    for (size_t i = 0; i < descendientes.size(); i++) archivo << "descendientes," << descendientes[i] << "\n";
}

void Registrar(std::ofstream &rCsv, const std::string &sCarga, int n, const std::string &sEstructura,
               const std::string &sFase, int nOperaciones, const Contadores &c, int nCorrectas, int nIncorrectas) {
    rCsv << sCarga << "," << n << "," << sEstructura << "," << sFase << "," << nOperaciones << ","
         << c.comparaciones << "," << c.nodosVisitados << "," << nCorrectas << "," << nIncorrectas << "\n";
    std::cout << "  " << sCarga << "\tn=" << n << "\t" << sEstructura << "\t" << sFase
              << "\tops=" << nOperaciones << "\tcomparaciones=" << c.comparaciones
              << "\tnodosVisitados=" << c.nodosVisitados
              << "\tcorrectas=" << nCorrectas << "\tincorrectas=" << nIncorrectas << "\n";
    gCorrectas += nCorrectas;
    gFallidas += nIncorrectas;
}

template <typename Estructura>
void EjecutarCarga(const std::string &sCarga, const std::string &sEstructura,
                   const std::vector<Tarea> &tareas, const std::vector<int> &consultasIndividuales,
                   const std::vector<int> *pConsultasDescendientes, const Esperado &esperado,
                   std::ofstream &rCsv) {
    Estructura estructura;
    int n = (int)tareas.size();
    int nCorrectas = 0, nIncorrectas = 0;

    estructura.ReiniciarContadores();
    for (size_t i = 0; i < tareas.size(); i++) {
        if (estructura.Insertar(tareas[i])) nCorrectas++; else nIncorrectas++;
    }
    Registrar(rCsv, sCarga, n, sEstructura, "insercion", n, estructura.ObtenerContadores(),
              nCorrectas, nIncorrectas);

    nCorrectas = nIncorrectas = 0;
    estructura.ReiniciarContadores();
    for (size_t i = 0; i < consultasIndividuales.size(); i++) {
        int nId = consultasIndividuales[i];
        bool bExiste = nId >= 1 && nId <= n;
        bool bCorrecta = BusquedaCorrecta(estructura, nId,
                                          bExiste ? tareas[nId - 1].nombre.c_str() : nullptr);
        if (bCorrecta) nCorrectas++; else nIncorrectas++;
    }
    Registrar(rCsv, sCarga, n, sEstructura, "consulta_individual", (int)consultasIndividuales.size(),
              estructura.ObtenerContadores(), nCorrectas, nIncorrectas);

    if (pConsultasDescendientes == nullptr) return;
    nCorrectas = nIncorrectas = 0;
    estructura.ReiniciarContadores();
    for (size_t i = 0; i < pConsultasDescendientes->size(); i++) {
        int nId = (*pConsultasDescendientes)[i];
        bool bExiste = nId >= 1 && nId <= n;
        bool bCorrecta = bExiste
            ? DescendientesCorrecto(estructura, nId, true, esperado.total[nId],
                                    esperado.pendiente[nId], esperado.tareas[nId])
            : DescendientesCorrecto(estructura, nId, false, 0, 0, 0);
        if (bCorrecta) nCorrectas++; else nIncorrectas++;
    }
    Registrar(rCsv, sCarga, n, sEstructura, "consulta_descendientes",
              (int)pConsultasDescendientes->size(), estructura.ObtenerContadores(),
              nCorrectas, nIncorrectas);
}

int main() {
    std::ofstream parametros("parametros.txt");
    parametros << "SEMILLA_BASE=" << SEMILLA_BASE << " (semilla usada por tamano = SEMILLA_BASE + n)\n"
               << "TAMANOS=";
    for (int i = 0; i < CANT_TAMANOS; i++) parametros << TAMANOS[i] << (i + 1 < CANT_TAMANOS ? "," : "\n");
    parametros << "CONSULTAS_INDIVIDUALES=" << CONSULTAS_INDIVIDUALES << "\n"
               << "CONSULTAS_DESCENDIENTES=" << CONSULTAS_DESCENDIENTES << "\n"
               << "PROB_ID_INEXISTENTE=" << PROB_ID_INEXISTENTE << "\n"
               << "PROB_TAREA_RAIZ=" << PROB_TAREA_RAIZ << "\n"
               << "PROB_COMPLETADA=" << PROB_COMPLETADA << "\n"
               << "ESFUERZO=" << ESFUERZO_MIN << ".." << ESFUERZO_MAX << "\n";
    parametros.close();

    ProbarCasosFijos();

    std::cout << "\n=== Cargas generadas ===\n";
    std::ofstream csv("resultados.csv");
    csv << "carga,n,estructura,fase,operaciones,comparaciones,nodosVisitados,correctas,incorrectas\n";

    for (int i = 0; i < CANT_TAMANOS; i++) {
        int n = TAMANOS[i];
        std::mt19937 generador(SEMILLA_BASE + n);

        std::vector<Tarea> base = GenerarTareasIndependientes(n, generador);
        std::vector<Tarea> modificada = AnidarTareas(base, generador);
        std::vector<int> consultasInd = GenerarConsultas(CONSULTAS_INDIVIDUALES, n, generador);
        std::vector<int> consultasDesc = GenerarConsultas(CONSULTAS_DESCENDIENTES, n, generador);

        std::string sN = std::to_string(n);
        GuardarDatos("datos_base_" + sN + ".csv", base);
        GuardarDatos("datos_modificada_" + sN + ".csv", modificada);
        GuardarConsultas("consultas_" + sN + ".csv", consultasInd, consultasDesc);

        Esperado esperadoBase = CalcularEsperado(base);
        Esperado esperadoMod = CalcularEsperado(modificada);

        EjecutarCarga<Lista<Tarea> >("base", "lista", base, consultasInd, nullptr, esperadoBase, csv);
        EjecutarCarga<Arbol<Tarea> >("base", "arbol", base, consultasInd, nullptr, esperadoBase, csv);

        EjecutarCarga<Lista<Tarea> >("modificada", "lista", modificada, consultasInd, &consultasDesc, esperadoMod, csv);
        EjecutarCarga<Arbol<Tarea> >("modificada", "arbol", modificada, consultasInd, &consultasDesc, esperadoMod, csv);
    }

    std::cout << "\nComprobaciones correctas: " << gCorrectas
              << "\nComprobaciones fallidas:  " << gFallidas << "\n";
    return gFallidas == 0 ? 0 : 1;
}
