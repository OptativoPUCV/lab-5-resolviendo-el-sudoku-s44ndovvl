#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k, p;
    int seen[10]; // Arreglo para marcar números vistos (índices 1-9)

    // Validar filas
    for (i = 0; i < 9; i++) {
        for (k = 0; k < 10; k++) seen[k] = 0; // Reiniciar el arreglo de marcadores para cada fila
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num] == 1) return 0; // Número repetido en la fila
                seen[num] = 1;
            }
        }
    }

    // Validar columnas
    for (j = 0; j < 9; j++) {
        for (k = 0; k < 10; k++) seen[k] = 0; // Reiniciar el arreglo de marcadores para cada columna
        for (i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num] == 1) return 0; // Número repetido en la columna
                seen[num] = 1;
            }
        }
    }

    // Validar submatrices de 3x3
    for (k = 0; k < 9; k++) {
        for (p = 0; p < 10; p++) seen[p] = 0; // Reiniciar el arreglo de marcadores para cada submatriz
        for (p = 0; p < 9; p++) {
            int row = 3 * (k / 3) + (p / 3);
            int col = 3 * (k % 3) + (p % 3);
            int num = n->sudo[row][col];
            if (num != 0) {
                if (seen[num] == 1) return 0; // Número repetido en la submatriz
                seen[num] = 1;
            }
        }
    }

    return 1; // El estado es válido
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    int i,j,k; 
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j] == 0){ // se encuentra una casilla vacia
                for(k = 1; k<=9; k++){ //revisa los 9 posibles numeros que se pueden poner en casilla vacia
                  Node* new=copy(n);
                  new->sudo[i][j] = k;
                  if(is_valid(new)) pushBack(list, new);
              }
            }
        }
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/