#include "a_sbr_logger.h"

#include "a_sbr_logger.h"

SBRLogger::SBRLogger(int n_tabuladores = 0) : n_tabuladores(n_tabuladores) {}

SBRLogger *SBRLogger::s_instancia = nullptr;

void SBRLogger::imprimirTabuladores()
{
    auto salida = s_instancia->ficheroSalida;
    for (int i = 0; i < this->n_tabuladores; i++)
        (*salida) << "\t";
}

int SBRLogger::getNTabuladores()
{
    return this->n_tabuladores;
}

void SBRLogger::addMeta(Hecho *nuevaMeta)
{
    this->nuevasMetas.push_back(nuevaMeta);
    this->imprimirNuevasMetas();
}

void SBRLogger::addMeta(std::vector<Hecho *> metas)
{
    for (const auto &meta : metas)
        this->nuevasMetas.push_back(meta);
    this->imprimirTabuladores();
    this->imprimirNuevasMetas();
}

void SBRLogger::addBH(Hecho *bh)
{
    this->bh.push_back(bh);
    this->imprimirBH();
}

void SBRLogger::addBH(std::vector<Hecho *> elems)
{
    for (const auto &elem : elems)
        this->bh.push_back(elem);
    this->imprimirBH();
}

void SBRLogger::addCC(Regla *cr)
{
    this->cc.push_back(cr);
    this->imprimirTabuladores();
    this->imprimirCC();
}

void SBRLogger::addCC(std::vector<Regla *> elems)
{
    for (const auto &elem : elems)
        this->cc.push_back(elem);
    this->imprimirTabuladores();
    this->imprimirCC();
}

void SBRLogger::eliminarMeta(Hecho *meta)
{
    auto salida = s_instancia->ficheroSalida;
    bool found = false;
    auto it = this->nuevasMetas.rbegin();

    while (!found && it != this->nuevasMetas.rend())
    {
        if ((*it)->getNombre().compare(meta->getNombre()) == 0)
            found = true;
        else
            it++;
    }
    if (!found)
    {
        (*salida) << "No se ha encontrado " << meta->getNombre() << std::endl;
        return;
    }

    this->imprimirTabuladores();
    (*salida) << "Meta = " << (*it)->getNombre() << std::endl;

    this->nuevasMetas.erase(std::next(it).base());
    this->imprimirTabuladores();
    this->imprimirNuevasMetas();

    this->imprimirTabuladores();
    (*salida) << "Verificar ( " << meta->getNombre() << ", ";
    this->imprimirBHContenido();
    (*salida) << " )";

    if (meta->getFactorCerteza() != Hecho::SIN_CALCULAR)
    {
        (*salida) << " -> " << meta->getFactorCerteza();
    }

    (*salida) << std::endl;
}

void SBRLogger::eliminarCC()
{
    if (this->cc.empty())
        return;

    auto salida = s_instancia->ficheroSalida;
    this->n_tabuladores++;
    this->imprimirTabuladores();
    this->imprimirCC();

    auto regla = this->cc.back();
    this->cc.erase(this->cc.end() - 1);
    this->imprimirTabuladores();
    (*salida) << "Regla = {" << regla->getNombre() << "}" << std::endl;

    this->imprimirTabuladores();
    (*salida) << "Eliminar " << regla->getNombre() << " -> ";
    this->imprimirCC();
}

void SBRLogger::aplicarRegla(Regla *regla)
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "Aplicar regla " << regla->getNombre() << std::endl;

    this->eliminarCC();
}

void SBRLogger::aplicarRegla()
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "Aplicar regla " << this->cc.front()->getNombre() << std::endl;

    this->eliminarCC();
}
void SBRLogger::usoCaso1(Elemento *hechoCompuesto)
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "Caso 1: " << hechoCompuesto->getNombre() << ", " << hechoCompuesto->getFactorCerteza() << std::endl;
}

void SBRLogger::usoCaso2(Regla *antecedente1, Regla *antecedente2, Hecho *consecuencia)
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "Caso 2: FC(" << consecuencia->getNombre() << ", " << antecedente1->getNombre()
              << " y " << antecedente2->getNombre() << "), " << consecuencia->getFactorCerteza()
              << std::endl;
}

void SBRLogger::usoCaso3(Regla *regla)
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "Caso 3: " << regla->getPrecondicion()->getNombre()
              << ", " << regla->getConsecuencia()->getNombre()
              << ", FC =" << regla->getConsecuencia()->getFactorCerteza()
              << std::endl;
    this->n_tabuladores--;
}

void SBRLogger::imprimirNuevasMetas()
{
    auto salida = s_instancia->ficheroSalida;
    (*salida) << "NuevasMetas = {";
    for (size_t i = 0; i < this->nuevasMetas.size(); ++i)
    {
        (*salida) << this->nuevasMetas[i]->getNombre();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->nuevasMetas.size() - 1)
        {
            (*salida) << ", ";
        }
    }
    // Salto de línea al final
    (*salida) << "}" << std::endl;
}

void SBRLogger::imprimirBH()
{
    auto salida = s_instancia->ficheroSalida;
    this->imprimirTabuladores();
    (*salida) << "BH = ";
    this->imprimirBHContenido();
    (*salida) << std::endl;
}

void SBRLogger::imprimirBHContenido()
{
    auto salida = s_instancia->ficheroSalida;
    (*salida) << "{";
    for (size_t i = 0; i < this->bh.size(); ++i)
    {
        (*salida) << this->bh[i]->getNombre() << ":" << this->bh[i]->getFactorCerteza();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->bh.size() - 1)
        {
            (*salida) << ", ";
        }
    }

    // Salto de línea al final
    (*salida) << "}";
}

void SBRLogger::imprimirCC()
{
    auto salida = s_instancia->ficheroSalida;
    (*salida) << "CC = {";
    for (size_t i = 0; i < this->cc.size(); ++i)
    {
        (*salida) << this->cc[i]->getNombre();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->cc.size() - 1)
        {
            (*salida) << ", ";
        }
    }

    // Salto de línea al final
    (*salida) << "}" << std::endl;
}

void SBRLogger::reset(bool usarLogger, int n_tabuladores)
{
    s_instancia = new SBRLogger(0);
}

SBRLogger *SBRLogger::instancia()
{
    if (!s_instancia)
        s_instancia = new SBRLogger(0);
    return s_instancia;
}

SBRLogger::~SBRLogger()
{

    for (const auto &elem : nuevasMetas)
    {
        if (elem != nullptr)
            delete elem;
    }

    for (const auto &elem : bh)
    {
        if (elem != nullptr)
            delete elem;
    }

    for (const auto &elem : cc)
    {
        if (elem != nullptr)
            delete elem;
    }

    if (ficheroSalida->is_open())
    {
        ficheroSalida->close();
    }
}

void SBRLogger::setFicheroSalida(std::string fichero)
{
    if (!s_instancia)
        s_instancia = new SBRLogger(0);

    s_instancia->ficheroSalida = new std::ofstream(fichero);
}

std::ofstream *SBRLogger::getFicheroSalida()
{
    if (!s_instancia)
        s_instancia = new SBRLogger(0);

    if (s_instancia->ficheroSalida->is_open())
        return ficheroSalida;

    return nullptr;
}
