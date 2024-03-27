#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *lista = (List *)malloc(sizeof(List));    //Asignación de memoria para la lista.
  lista->head=NULL;                    
  lista->tail=NULL;                  //Se asignan las variables del struct lista head, tail, current.
  lista->current=NULL;

  return lista;
}

void * firstList(List * list) {
  if (list==NULL || list->head==NULL) return NULL;    //Condición por si la lista está vacía, en ese caso retorna NULL.
  list->current = list->head;        //Reemplazamos el current con el primero de la lista.
  return(void *)list->current->data;  //Retorna el dato(key) del primer nodo. 
}

void * nextList(List * list) {
  if (list==NULL || list->current == NULL || list->current->next == NULL) return NULL;    //Condición por si la lista está vacía o ya está seleccionado el último nodo.
  list->current = list->current->next;    //Sino, se asigna el siguiente valor al current.
  return (void *) list->current->data;  //Y se retorna el dato.
}

void * lastList(List * list) {
  if (list==NULL || list->tail ==NULL) return NULL;    //Condición lista vacía.
  list->current = list->tail;
  return (void *) list->current->data;
}

void * prevList(List * list) {
  if (list==NULL || list->current == NULL || list->current->prev == NULL){
    return NULL;
  }
  list->current = list->current->prev;
  return (void *) list->current->data;
}

void pushFront(List * list, void * data) {
  Node * newNode = createNode(data);      //Se crea un nuevo nodo vacío con la función createNode.
  if (list->head == NULL)    //Condición por si la lista está vacía.
  {
    list->head = newNode;    //En ese caso al ser el único valor(nodo) se le asigna la primera y última posición (head y tail).
    list->tail = newNode;
  } else{
    newNode->next = list->head;  //Sino se le asigna al puntero next del nuevo nodo al nodo head
    list->head->prev = newNode;  //y al head el puntero prev al nuevo nodo.
    list->head = newNode;      //Finalmente se reemplaza el head con el nuevo nodo.
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;            //Se reemplaza el current por la cola de la lista.
  pushCurrent(list,data);        //Se usa la función pushCurrent para reemplazar el último nodo.
}

void pushCurrent(List * list, void * data) {
  Node *newNode = createNode(data);    //Se crea un nuevo nodo.
  if (list->current == NULL){        //Condición lista vacía.
    list->head = newNode;        
    list->tail = newNode;          //Si se cumple la condición, se les asigna todas las variables al nuevo nodo.
    list->current = newNode;
  } else{                            //Sino, al prev y next del nuevo nodo se les reemplaza con los punteros del nodo current.
    newNode->prev = list->current;
    newNode->next = list->current->next;
  }

  if(list->current->next != NULL){
    list->current->next->prev = newNode;
  } else{
    list->tail = newNode;
  }
  list->current->next = newNode;
  list->current = newNode;
}

void * popFront(List * list) {
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == NULL) return NULL;
  void * data = list->current->data;
  Node *nodeToRemove = list->current;
  if (list->current->prev != NULL){
    list->current->prev->next = list->current->next;
  } else{
    list->head = list->current->next;
  }
  if(list->current->next != NULL){
    list->current->next->prev = list->current->prev;
  } else{
    list->tail = list->current->prev;
  }
  list->current = list->current->next;
  free(nodeToRemove);
  
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}