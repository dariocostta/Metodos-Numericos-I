#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using std::cout;
using std::cin;
using std::string;

int main(){
  std::cout.setf( std::ios::fixed, std:: ios::floatfield );
  std::cout.precision(6);
  int op=1;

  do{
  	cout << "\n1 -- Inserir dados do(s) pendulo(s) \n0 -- Sair\n";
    cin >> op;
	}while(op);

}

/* Função deletaMatriz()
 * Acao: Desaloca toda a matriz
 * Entrada: Ponteiro - Para a Matriz (double **)
 * 					Inteiro  - Quantidade de linhas
 */
void deletaMatriz(double ** A, int m){
	for(int i = 0; i < m; i++){
		if(A[i]!=nullptr)
			delete[] A[i];
	}
	delete[] A;
}

/* Função alocaMatriz()
 * Acao: Aloca toda a matriz
 * Entrada: Inteiros m e n, dimensoes para a matriz
 * Saida padrao: Ponteiro para a matriz mxn
 *							 Tipo (double **)
 * Saida erro:   nullptr - falta de memoria 	
 */
double ** alocaMatriz(int m, int n){
	double ** A = (double**) malloc(m);
	if(A!=nullptr)
	{
		for(int i=0; i<m; i++){
	   	A[i] = (double*) malloc(n);
	   	if(A[i] == nullptr){
	   		deletaMatriz(A, m);
	   		break;
			}
		}
	}
	return A;
}

/* Função gauss()
 * Acao:
 * Algoritmo:
 * Entrada:
 * Saida padrao: 
 * Saida erro:
 */
void gauss(double ** A, int m, int n){
  for(int i=0; i < m; i++){
    if(A[i][j] == 0){
      for(p=0; p < m; p++){
        if(A[p][i] != 0){
          k=p;
          break;
        }
        for(p=i-1; p < m; p++){
          aux=A[i][p];
          A[i][p]=A[k][p];
           A[k][p]=aux;
        }
      }
      j=0;
      while(j < m){
        for(k=m-1; k<n; k++){
          b = A[i][k];
          A[j][k] = A[j][k] - ((A[j][i])/((A[i][i])*b));
        }
        j++;
        if(j==i){
          j++;
        }
      }
	  }
	}
}
