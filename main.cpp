#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Tarea.h"
#include "Lista.h"
#include "Arbol.h"
#include "Generador.h"
#include "Referencia.h"

const unsigned int SEMILLA_POR_DEFECTO = 2026;
const int TAMANOS[] = {100, 500, 1000, 2000};
const int CANTIDAD_TAMANOS = 4;
const int CONSULTAS_ALEATORIAS = 10;

struct Consulta {
    std::string operacion;
    std::string caso;
    int id;
};

struct Fila {
    std::string carga, operacion, caso, estructura;
    int n, id, resultado, esperado;
    bool correcto;
    long long visitados, comparaciones;
};

void AgregarBusquedas(std::vector<Consulta> &c, int n, Generador &g) {
    Consulta inicio = {"buscar", "limite_inicio", 1};
    Consulta medio = {"buscar", "medio", n / 2};
    Consulta final = {"buscar", "limite_final", n};
    c.push_back(inicio);
    c.push_back(medio);
    c.push_back(final);
    for (int k = 0; k < CONSULTAS_ALEATORIAS; k++) {
        Consulta normal = {"buscar", "normal", g.Entero(1, n)};
        c.push_back(normal);
    }
    Consulta noExiste1 = {"buscar", "inexistente", n + 1};
    Consulta noExiste2 = {"buscar", "inexistente", -1};
    c.push_back(noExiste1);
    c.push_back(noExiste2);
}

std::vector<Consulta> ConsultasBase(int n, Generador &g) {
    std::vector<Consulta> c;
    AgregarBusquedas(c, n, g);
    return c;
}

std::vector<Consulta> ConsultasModificada(int n, Generador &g, const Referencia &ref) {
    std::vector<Consulta> c;
    AgregarBusquedas(c, n, g);

    int raizMayor = 1, maxDesc = -1, intermedio = -1, hoja = -1;
    for (int id = 1; id <= n; id++) {
        int desc = ref.CantidadDescendientes(id);
        int prof = ref.Profundidad(id);
        if (prof == 1 && desc > maxDesc) { maxDesc = desc; raizMayor = id; }
        if (intermedio == -1 && prof == 2 && desc > 0) intermedio = id;
        if (hoja == -1 && desc == 0) hoja = id;
    }
    Consulta proyecto1 = {"pendiente", "proyecto_1", 1};
    Consulta mayor = {"pendiente", "raiz_mayor", raizMayor};
    c.push_back(proyecto1);
    c.push_back(mayor);
    if (intermedio != -1) { Consulta q = {"pendiente", "nivel_intermedio", intermedio}; c.push_back(q); }
    if (hoja != -1) { Consulta q = {"pendiente", "hoja", hoja}; c.push_back(q); }
    for (int k = 0; k < CONSULTAS_ALEATORIAS; k++) {
        Consulta normal = {"pendiente", "normal", g.Entero(1, n)};
        c.push_back(normal);
    }
    Consulta noExiste = {"pendiente", "inexistente", n + 1};
    c.push_back(noExiste);
    return c;
}

int Esperado(const Consulta &q, const Referencia &ref) {
    if (q.operacion == "buscar") return ref.Existe(q.id) ? q.id : -1;
    return ref.EsfuerzoPendiente(q.id);
}

template <typename Estructura>
int Ejecutar(Estructura &e, const Consulta &q) {
    if (q.operacion == "buscar") {
        Tarea *t = e.BuscarPorId(q.id);
        return (t == nullptr) ? -1 : t->id;
    }
    return e.EsfuerzoPendiente(q.id);
}

void GuardarTareas(const std::string &archivo, const std::vector<Tarea> &tareas) {
    std::ofstream f(archivo.c_str());
    f << "id,idPadre,nombre,esfuerzo,completada\n";
    for (size_t i = 0; i < tareas.size(); i++) {
        const Tarea &t = tareas[i];
        f << t.id << "," << t.idPadre << "," << t.nombre << ","
          << t.esfuerzo << "," << (t.completada ? 1 : 0) << "\n";
    }
}

void EstudiarCarga(const std::string &carga, int n, const std::vector<Tarea> &tareas,
                   const std::vector<Consulta> &consultas, const Referencia &ref,
                   std::vector<Fila> &filas) {
    Lista<Tarea> lista;
    Arbol<Tarea> arbol;

    bool construccionOk = true;
    for (size_t i = 0; i < tareas.size(); i++) {
        lista.AgregarFinal(tareas[i]);
        if (!arbol.Insertar(tareas[i])) construccionOk = false;
    }
    Fila cl = {carga, "construccion", "todas", "lista", n, 0, lista.Elementos(), n,
               lista.Elementos() == n, lista.ObtenerVisitados(), lista.ObtenerComparaciones()};
    Fila ca = {carga, "construccion", "todas", "arbol", n, 0, construccionOk ? n : -1, n,
               construccionOk, arbol.ObtenerVisitados(), arbol.ObtenerComparaciones()};
    filas.push_back(cl);
    filas.push_back(ca);

    for (size_t k = 0; k < consultas.size(); k++) {
        const Consulta &q = consultas[k];
        int esperado = Esperado(q, ref);

        lista.ReiniciarContadores();
        int rl = Ejecutar(lista, q);
        Fila fl = {carga, q.operacion, q.caso, "lista", n, q.id, rl, esperado, rl == esperado,
                   lista.ObtenerVisitados(), lista.ObtenerComparaciones()};
        filas.push_back(fl);

        arbol.ReiniciarContadores();
        int ra = Ejecutar(arbol, q);
        Fila fa = {carga, q.operacion, q.caso, "arbol", n, q.id, ra, esperado, ra == esperado,
                   arbol.ObtenerVisitados(), arbol.ObtenerComparaciones()};
        filas.push_back(fa);
    }
}

void GuardarResultados(const std::string &archivo, const std::vector<Fila> &filas) {
    std::ofstream f(archivo.c_str());
    f << "carga,n,operacion,caso,id,estructura,resultado,esperado,correcto,visitados,comparaciones\n";
    for (size_t i = 0; i < filas.size(); i++) {
        const Fila &r = filas[i];
        f << r.carga << "," << r.n << "," << r.operacion << "," << r.caso << "," << r.id << ","
          << r.estructura << "," << r.resultado << "," << r.esperado << ","
          << (r.correcto ? 1 : 0) << "," << r.visitados << "," << r.comparaciones << "\n";
    }
}

struct Acumulado {
    int consultas, correctas;
    long long visitados, comparaciones;
};

void GuardarResumen(const std::string &archivo, const std::vector<Fila> &filas) {

    std::map<std::string, Acumulado> grupos;
    for (size_t i = 0; i < filas.size(); i++) {
        const Fila &r = filas[i];
        if (r.operacion == "construccion") continue;
        std::string nTexto = std::to_string(r.n);
        while (nTexto.size() < 5) nTexto = "0" + nTexto;
        std::string clave = r.carga + "|" + nTexto + "|" + r.operacion + "|" + r.estructura;
        Acumulado &a = grupos[clave];
        a.consultas++;
        if (r.correcto) a.correctas++;
        a.visitados += r.visitados;
        a.comparaciones += r.comparaciones;
    }

    std::ofstream f(archivo.c_str());
    f << "carga,n,operacion,estructura,consultas,correctas,promedio_visitados,promedio_comparaciones\n";
    std::cout << "\n" << std::left << std::setw(11) << "carga" << std::setw(6) << "n"
              << std::setw(11) << "operacion" << std::setw(7) << "estr."
              << std::setw(10) << "correctas" << std::setw(14) << "prom.visitas"
              << "prom.comparac.\n";
    std::cout << std::string(73, '-') << "\n";

    for (std::map<std::string, Acumulado>::iterator it = grupos.begin(); it != grupos.end(); ++it) {
        std::vector<std::string> partes;
        std::string resto = it->first;
        size_t pos;
        while ((pos = resto.find('|')) != std::string::npos) {
            partes.push_back(resto.substr(0, pos));
            resto = resto.substr(pos + 1);
        }
        partes.push_back(resto);
        int n = std::atoi(partes[1].c_str());
        const Acumulado &a = it->second;
        double pv = (double)a.visitados / a.consultas;
        double pc = (double)a.comparaciones / a.consultas;

        f << partes[0] << "," << n << "," << partes[2] << "," << partes[3] << ","
          << a.consultas << "," << a.correctas << "," << std::fixed << std::setprecision(1)
          << pv << "," << pc << "\n";

        std::cout << std::left << std::setw(11) << partes[0] << std::setw(6) << n
                  << std::setw(11) << partes[2] << std::setw(7) << partes[3]
                  << std::setw(10) << (std::to_string(a.correctas) + "/" + std::to_string(a.consultas))
                  << std::setw(14) << std::fixed << std::setprecision(1) << pv << pc << "\n";
    }
}

int main(int argc, char *argv[]) {
    unsigned int semilla = SEMILLA_POR_DEFECTO;
    if (argc > 1) semilla = (unsigned int)std::strtoul(argv[1], nullptr, 10);
    std::cout << "Semilla: " << semilla << "\n";

    std::vector<Fila> filas;
    for (int s = 0; s < CANTIDAD_TAMANOS; s++) {
        int n = TAMANOS[s];

        Generador gDatosBase(semilla + n);
        Generador gConsultasBase(semilla + n + 1);
        std::vector<Tarea> base = gDatosBase.CargaBase(n);
        Referencia refBase(base);
        GuardarTareas("tareas_base_" + std::to_string(n) + ".csv", base);
        EstudiarCarga("base", n, base, ConsultasBase(n, gConsultasBase), refBase, filas);

        Generador gDatosMod(semilla + n + 2);
        Generador gConsultasMod(semilla + n + 3);
        std::vector<Tarea> mod = gDatosMod.CargaModificada(n);
        Referencia refMod(mod);
        GuardarTareas("tareas_modificada_" + std::to_string(n) + ".csv", mod);
        EstudiarCarga("modificada", n, mod, ConsultasModificada(n, gConsultasMod, refMod), refMod, filas);
    }

    GuardarResultados("resultados.csv", filas);
    GuardarResumen("resumen.csv", filas);

    int incorrectas = 0;
    for (size_t i = 0; i < filas.size(); i++) if (!filas[i].correcto) incorrectas++;
    std::cout << "\nResultados incorrectos: " << incorrectas << " de " << filas.size() << "\n";
    std::cout << "Archivos: resultados.csv, resumen.csv, tareas_base_N.csv, tareas_modificada_N.csv\n";
    return incorrectas == 0 ? 0 : 1;
}
