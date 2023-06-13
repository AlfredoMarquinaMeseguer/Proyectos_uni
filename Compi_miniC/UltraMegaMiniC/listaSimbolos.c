#include "listaSimbolos.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

struct PosicionListaRep {
  Simbolo dato;
  struct PosicionListaRep *sig;
};

struct ListaRep {
  PosicionLista cabecera;
  PosicionLista ultimo;
  int n;
};

typedef struct PosicionListaRep *NodoPtr;

Lista creaLS() {
  Lista nueva = malloc(sizeof(struct ListaRep));
  nueva->cabecera = malloc(sizeof(struct PosicionListaRep));
  nueva->cabecera->sig = NULL;
  nueva->ultimo = nueva->cabecera;
  nueva->n = 0;
  return nueva;
}

void liberaLS(Lista lista) {
  while (lista->cabecera != NULL) {
    NodoPtr borrar = lista->cabecera;
    lista->cabecera = borrar->sig;
    free(borrar);
  }
  free(lista);
}

void insertaLS(Lista lista, PosicionLista p, Simbolo s) {
  NodoPtr nuevo = malloc(sizeof(struct PosicionListaRep));
  nuevo->dato = s;
  nuevo->sig = p->sig;
  p->sig = nuevo;
  if (lista->ultimo == p) {
    lista->ultimo = nuevo;
  }
  (lista->n)++;
}

void suprimeLS(Lista lista, PosicionLista p) {
  assert(p != lista->ultimo);
  NodoPtr borrar = p->sig;
  p->sig = borrar->sig;
  if (lista->ultimo == borrar) {
    lista->ultimo = p;
  }
  free(borrar);
  (lista->n)--;
}

Simbolo recuperaLS(Lista lista, PosicionLista p) {
  assert(p != lista->ultimo);
  return p->sig->dato;
}

PosicionLista buscaLS(Lista lista, char *nombre) {
  NodoPtr aux = lista->cabecera;
  while (aux->sig != NULL && strcmp(aux->sig->dato.nombre,nombre) != 0) {
    aux = aux->sig;
  }
  return aux;
}

void asignaLS(Lista lista, PosicionLista p, Simbolo s) {
  assert(p != lista->ultimo);
  p->sig->dato = s;
}

int longitudLS(Lista lista) {
  return lista->n;
}

PosicionLista inicioLS(Lista lista) {
  return lista->cabecera;
}

PosicionLista finalLS(Lista lista) {
  return lista->ultimo;
}

PosicionLista siguienteLS(Lista lista, PosicionLista p) {
  assert(p != lista->ultimo);
  return p->sig;
}

bool perteneceTablaS(Lista lista, char *nombre) {
  PosicionLista pos = buscaLS(lista, nombre);
  PosicionLista final = finalLS(lista);
  return pos != final;
}

void anyadeEntrada(Lista lista, char *nombre, Tipo tipo) {
  PosicionLista ultimaPosicion = finalLS(lista);
  Simbolo nuevoSimbolo = {nombre, tipo};
  insertaLS(lista, ultimaPosicion, nuevoSimbolo);
}

bool esConstante(Lista lista, char *nombre) {
   Simbolo s;
   PosicionLista pos = buscaLS(lista, nombre);
   if (pos != finalLS(lista)) {
    s = recuperaLS(lista, pos);
    return (s.tipo == CONSTANTE);
   }
   
}

void imprimirTablaS(Lista lista) {
  printf("###################\n");
  printf("# Seccion de datos\n");
  printf("\t.data\n");
  printf("\n");
  PosicionLista pos = inicioLS(lista); // Obtenemos la posición del primer elemento
  Simbolo simbolo;
  
  while (pos != finalLS(lista)) { // Recorremos la lista hasta llegar al final
    simbolo = recuperaLS(lista, pos); // Obtenemos el simbolo de la posición actual
    
    // Imprimimos la información del simbolo con formato según su tipo
    if (simbolo.tipo == CADENA) {
       printf("$str%d:\n", simbolo.valor);
       printf("\t.asciiz %s\n", simbolo.nombre);
    }
    
    pos = siguienteLS(lista, pos); // Avanzamos a la siguiente posición
  }

  pos = inicioLS(lista);
  while (pos != finalLS(lista)) {
    simbolo = recuperaLS(lista, pos);
    if (simbolo.tipo != CADENA) {
      printf("_%s:\n", simbolo.nombre);
      printf("\t.word 0\n");
    }
    pos = siguienteLS(lista, pos);
  }
  printf("\n");
}
