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
  /*int row_check[10], col_check[10], box_check[10];
    
    // Validar filas y columnas
    for (int i = 0; i < 9; i++) {
        // Reiniciar los arreglos de chequeo
        for (int x = 0; x < 10; x++) row_check[x] = col_check[x] = 0;

        for (int j = 0; j < 9; j++) {
            // Validar fila
            int num_row = n->sudo[i][j];
            if (num_row != 0) {
                if (row_check[num_row]) return 0;
                row_check[num_row] = 1;
            }

            // Validar columna
            int num_col = n->sudo[j][i];
            if (num_col != 0) {
                if (col_check[num_col]) return 0;
                col_check[num_col] = 1;
            }
        }
    }

    // Validar submatrices de 3x3
    for (int k = 0; k < 9; k++) {
        // Reiniciar el arreglo de chequeo
        for (int x = 0; x < 10; x++) box_check[x] = 0;

        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];

            if (num != 0) {
                if (box_check[num]) return 0;
                box_check[num] = 1;
            }
        }
    }*/

    int i,j,k,p;

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j] != 0){
                for(k=0;k<9;k++){
                    if(k != j && n->sudo[i][k] == n->sudo[i][j]) return 0;
                    if(k != i && n->sudo[k][j] == n->sudo[i][j]) return 0;
                }
                
                int k= 3 * (i/3) + (j/3);
                for(p=0;p<9;p++){
                    int a=3*(k/3) + (p/3) ;
                    int b=3*(k%3) + (p%3) ;
                    if (a != i || b != j)
                          if (n->sudo[a][b] == n->sudo[i][j]) return 0;
                }

            }
        }
    }

    return 1;
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
                return list; // se retorna la lista de nodos adyacentes
            }
        }
    }

    return list;
}


int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j] == 0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);
    while (top(S)) {
        Node* n = top(S);
        pop(S);

        (*cont)++;
        if (is_final(n)) {
            if (is_valid(n)) return n;
            else return NULL;
        }

        // visit(n); // Descomenta si tienes una función visit
        List* adj = get_adj_nodes(n);
        Node* aux = first(adj);
        while (aux) {
            push(S, aux);
            aux = next(adj);
        }
        free(n);
    }
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