#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using std::cout;
using std::cin;
using std::string;

typedef struct def_sistema {
	double ** A;
	int m, n;
	int * permutacaoLinhas, * permutacaoColunas;
	
	/* Função gauss
	 * Acao:
	 * Algoritmo:
	 * Entrada:
	 * Saida padrao: 
	 * Saida erro:
	 */
	void gauss(){
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
	
	/* Função pivotacaoParcial
	 * Acao: Troca a linha k pela linha i, onde ocorra
	 *			 max{absoluto(A[i][k])}, com i em {k, ..., m}
	 * Entrada: - Inteiro k: Passo que deve ser feita a pivotacao,
	 *						a partir do elemento A[k][k]
	 */
	void pivotacaoParcial(int k){
		int indexMaiorPivo = k;
		for(int i=k+1; i < m; i++){
			if(fabs(A[i][k]) > fabs(A[indexMaiorPivo][k]))
				indexMaiorPivo = i;
		}
		double * aux = A[k];
		A[k] = A[indexMaiorPivo];
		A[indexMaiorPivo] = aux;
		
		permutacaoColunas[k] = indexMaiorPivo;
		permutacaoColunas[indexMaiorPivo] = k;
	}
		
	void deletaMatriz(){
		for(int i = 0; i < m; i++){
			if(A[i]!=nullptr)
				delete[] A[i];
				A[i]=nullptr;
		}
		delete[] A;
	}
	
	/* Função alocaMatriz
	 * Saida padrao: - True: Erro na alocacao
	 * 							 - False: Tudo ocorreu bem
	 */
	bool alocaMatriz(){
		A = (double**) malloc(m);
		if(A!=nullptr)
		{
			for(int i=0; i<m; i++){
		   	A[i] = (double*) malloc(n);
		   	if(A[i] == nullptr){
		   		deletaMatriz();
		   		return true;
				}
			}
			return false;
		}
		return true;
	}
	
} Sistema;


int main(){
  std::cout.setf( std::ios::fixed, std:: ios::floatfield );
  std::cout.precision(6);
  int op=1;

  do{
  	cout << "\n1 -- Inserir dados do(s) pendulo(s) \n0 -- Sair\n";
    cin >> op;
	}while(op);

}
