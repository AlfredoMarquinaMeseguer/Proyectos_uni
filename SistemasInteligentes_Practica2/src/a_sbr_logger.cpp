#include "a_sbr_logger.h"

#include "a_sbr_logger.h"

SBRLogger::SBRLogger(int n_tabuladores = 0) : n_tabuladores(n_tabuladores) {}

SBRLogger *SBRLogger::s_instancia = nullptr;

void SBRLogger::imprimirTabuladores()
{
    for (int i = 0; i < this->n_tabuladores; i++)
        std::cout << "\t";
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
        std::cout << "No se ha encontrado " << meta->getNombre() << std::endl;
        return;
    }

    this->imprimirTabuladores();
    std::cout << "Meta = " << (*it)->getNombre() << std::endl;

    this->nuevasMetas.erase(std::next(it).base());
    this->imprimirTabuladores();
    this->imprimirNuevasMetas();

    this->imprimirTabuladores();
    std::cout << "Verificar ( " << meta->getNombre() << ", ";
    this->imprimirBHContenido();
    std::cout << " )";

    if (meta->getFactorCerteza() != Hecho::SIN_CALCULAR)
    {
        std::cout << " -> " << meta->getFactorCerteza();
    }

    std::cout << std::endl;
}

void SBRLogger::eliminarCC()
{
    if (this->cc.empty())
        return;

    this->n_tabuladores++;
    this->imprimirTabuladores();
    this->imprimirCC();

    auto regla = this->cc.back();
    this->cc.erase(this->cc.end() - 1);
    this->imprimirTabuladores();
    std::cout << "Regla = {" << regla->getNombre() << "}" << std::endl;

    this->imprimirTabuladores();
    std::cout << "Eliminar " << regla->getNombre() << " -> ";
    this->imprimirCC();
}

void SBRLogger::aplicarRegla(Regla *regla)
{
    this->imprimirTabuladores();
    std::cout << "Aplicar regla " << regla->getNombre() << std::endl;

    this->eliminarCC();
}

void SBRLogger::aplicarRegla()
{
    this->imprimirTabuladores();
    std::cout << "Aplicar regla " << this->cc.front()->getNombre() << std::endl;

    this->eliminarCC();
}
void SBRLogger::usoCaso1(Elemento *hechoCompuesto)
{
    this->imprimirTabuladores();
    std::cout << "Caso 1: " << hechoCompuesto->getNombre() << ", " << hechoCompuesto->getFactorCerteza() << std::endl;
}

void SBRLogger::usoCaso2(Regla *antecedente1, Regla *antecedente2, Hecho *consecuencia)
{
    this->imprimirTabuladores();
    std::cout << "Caso 2: FC(" << consecuencia->getNombre() << ", " << antecedente1->getNombre()
              << " y " << antecedente2->getNombre() << "), " << consecuencia->getFactorCerteza()
              << std::endl;
}

void SBRLogger::usoCaso3(Regla *regla)
{
    this->imprimirTabuladores();
    std::cout << "Caso 3: " << regla->getPrecondicion()->getNombre()
              << ", " << regla->getConsecuencia()->getNombre()
              << ", FC =" << regla->getConsecuencia()->getFactorCerteza()
              << std::endl;
    this->n_tabuladores--;
}

void SBRLogger::imprimirNuevasMetas()
{
    std::cout << "NuevasMetas = {";
    for (size_t i = 0; i < this->nuevasMetas.size(); ++i)
    {
        std::cout << this->nuevasMetas[i]->getNombre();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->nuevasMetas.size() - 1)
        {
            std::cout << ", ";
        }
    }
    // Salto de línea al final
    std::cout << "}" << std::endl;
}

void SBRLogger::imprimirBH()
{
    this->imprimirTabuladores();
    std::cout << "BH = ";
    this->imprimirBHContenido();
    std::cout << std::endl;
}

void SBRLogger::imprimirBHContenido()
{
    std::cout << "{";
    for (size_t i = 0; i < this->bh.size(); ++i)
    {
        std::cout << this->bh[i]->getNombre() << ":" << this->bh[i]->getFactorCerteza();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->bh.size() - 1)
        {
            std::cout << ", ";
        }
    }

    // Salto de línea al final
    std::cout << "}";
}

void SBRLogger::imprimirCC()
{
    std::cout << "CC = {";
    for (size_t i = 0; i < this->cc.size(); ++i)
    {
        std::cout << this->cc[i]->getNombre();

        // Imprimir la coma solo si no es el último elemento
        if (i < this->cc.size() - 1)
        {
            std::cout << ", ";
        }
    }

    // Salto de línea al final
    std::cout << "}" << std::endl;
}

void SBRLogger::reset(bool usarLogger, int n_tabuladores)
{
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
}
