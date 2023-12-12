#include "listaCodigo.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

const int NUM_REGISTROS = 10;
int *registros;
int numEtiq = 1;

struct PosicionListaCRep {
  Operacion dato;
  struct PosicionListaCRep *sig;
};

struct ListaCRep {
  PosicionListaC cabecera;
  PosicionListaC ultimo;
  int n;
  char *res;
};

typedef struct PosicionListaCRep *NodoPtr;

ListaC creaLC() {
  ListaC nueva = malloc(sizeof(struct ListaCRep));
  nueva->cabecera = malloc(sizeof(struct PosicionListaCRep));
  nueva->cabecera->sig = NULL;
  nueva->ultimo = nueva->cabecera;
  nueva->n = 0;
  nueva->res = NULL;
  return nueva;
}

void liberaLC(ListaC codigo) {
  while (codigo->cabecera != NULL) {
    NodoPtr borrar = codigo->cabecera;
    codigo->cabecera = borrar->sig;
    free(borrar);
  }
  free(codigo);
}

void insertaLC(ListaC codigo, PosicionListaC p, Operacion o) {
  NodoPtr nuevo = malloc(sizeof(struct PosicionListaCRep));
  nuevo->dato = o;
  nuevo->sig = p->sig;
  p->sig = nuevo;
  if (codigo->ultimo == p) {
    codigo->ultimo = nuevo;
  }
  (codigo->n)++;
}

Operacion recuperaLC(ListaC codigo, PosicionListaC p) {
  assert(p != codigo->ultimo);
  return p->sig->dato;
}

PosicionListaC buscaLC(ListaC codigo, PosicionListaC p, char *clave, Campo campo) {
  NodoPtr aux = p;
  char *info;
  while (aux->sig != NULL) {
    switch (campo) {
      case OPERACION: 
        info = aux->sig->dato.op;
        break;
      case ARGUMENTO1:
        info = aux->sig->dato.arg1;
        break;
      case ARGUMENTO2:
        info = aux->sig->dato.arg2;
        break;
      case RESULTADO:
        info = aux->sig->dato.res;
        break;
    }
    if (info != NULL && !strcmp(info,clave)) break;
	  aux = aux->sig;
  }
  return aux;
}

void asignaLC(ListaC codigo, PosicionListaC p, Operacion o) {
  assert(p != codigo->ultimo);
  p->sig->dato = o;
}

int longitudLC(ListaC codigo) {
  return codigo->n;
}

PosicionListaC inicioLC(ListaC codigo) {
  return codigo->cabecera;
}

PosicionListaC finalLC(ListaC codigo) {
  return codigo->ultimo;
}

void concatenaLC(ListaC codigo1, ListaC codigo2) {
  NodoPtr aux = codigo2->cabecera;
  while (aux->sig != NULL) {
    insertaLC(codigo1,finalLC(codigo1),aux->sig->dato);
    aux = aux->sig;
  }
}

PosicionListaC siguienteLC(ListaC codigo, PosicionListaC p) {
  assert(p != codigo->ultimo);
  return p->sig;
}

void guardaResLC(ListaC codigo, char *res) {
  codigo->res = res;
}

/* Recupera el registro resultado de una lista de codigo */
char * recuperaResLC(ListaC codigo) {
  return codigo	->res;
}

void iniReg() {
  registros = malloc(sizeof(int)*NUM_REGISTROS);
  for (int i = 0; i < NUM_REGISTROS; i++) registros[i] = 0;
}

char *obtenerReg() {
  char registro[4];
  for (int i = 0; i < NUM_REGISTROS; i++) {
    if (registros[i] == 0) {
      registros[i] = 1;
      sprintf(registro, "$t%d", i);
      return strdup(registro);
    }
  }
}

void liberarReg(char *reg) {
  int numRegistro = reg[2]-'0';
  registros[numRegistro]=0;
}

char *concatena(char *cadena1, char *cadena2) {
  int len = strlen(cadena1) + strlen(cadena2);
  char * aux = (char *) malloc(len);
  sprintf(aux,"%s%s", cadena1, cadena2);
  return aux;
}

void imprimirListaC(ListaC listaCodigo) {
  printf("###################\n");
  printf("# Seccion de codigo\n");
  printf("\t.text\n");
  printf("\t.globl main\n");
  printf("main:\n");

  Operacion oper;
  PosicionListaC pos = inicioLC(listaCodigo);

  while (pos != finalLC(listaCodigo)) {
    oper = recuperaLC(listaCodigo, pos);
    if (strcmp(oper.op,"etiq")) {
      printf("\t%s", oper.op);
      if (oper.res) printf(" %s", oper.res);
      if (oper.arg1) printf(", %s", oper.arg1);
      if (oper.arg2) printf(", %s", oper.arg2);
    }
    else printf("%s:", oper.res);
    printf("\n");
    pos = siguienteLC(listaCodigo, pos);
  }

  printf("\n##############\n");
  printf("# Fin\n");
  printf("\tjr $ra\n");;
  printf("\n");

  free(registros);
}

char *nuevaEtiqueta() {
    char aux[16];
    sprintf(aux,"$l%d",numEtiq);
    numEtiq++;
    return strdup(aux);
}
