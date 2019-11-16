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
	void gaussNormal(bol op){
	    for(i=0; i<m; i++){
               if(op==1){
                 if(pivotacaoParcial(i)==1){
                   break;  //nao tem mais elementos diferentes de 0
                 }
               }else{
                 if(pivotacaoCompleta(i)==1){
                   break; //nao tem mais elementos diferentes de 0
                 }
               }
               for(int j=i+1; j<m; j++){
                  for(k=i; k<=n; k++){
                     A[j][k]=A[j][k]-((A[j][i]/A[i][i])*A[i][k]);
                  }
               }
            }
            void gaussJordan(bol op){
	    for(i=0; i<m; i++){
               if(op==1){
                 if(pivotacaoParcial(i)==1){
                   break;  //nao tem mais elementos diferentes de 0
                 }
               }else{
                 if(pivotacaoCompleta(i)==1){
                   break; //nao tem mais elementos diferentes de 0
                 }
               }
               for(int j=0; j<m; j++){
                  for(k=i; k<=n; k++){
                     if(j==i){
                        A[j][k]=A[j][k]/A[i][i];
                     }else{
                        A[j][k]=A[j][k]-((A[j][i]/A[i][i])*A[i][k]);
                     }
                  }
               }
            

	/* Função pivotacaoParcial
	 * Acao: Troca a linha k pela linha i, onde ocorra
	 *			 max{absoluto(A[i][k])}, com i em {k, ..., m}
	 * Entrada: - Inteiro k: Passo que deve ser feita a pivotacao,
	 *						a partir do elemento A[k][k]
	 */
	bol pivotacaoParcial(int k){
		int indexMaiorPivo = k;
		for(int i=k+1; i < m; i++){
			if(fabs(A[i][k]) > fabs(A[indexMaiorPivo][k]))
				indexMaiorPivo = i;
		}
                if(A[indexMaiorPivo][k]==0){
                  if(pivotacaoCompleta(k+1)==1){
                    return 1;
                  }
                }
		double * aux = A[k];
		A[k] = A[indexMaiorPivo];
		A[indexMaiorPivo] = aux;

		permutacaoColunas[k] = indexMaiorPivo;
		permutacaoColunas[indexMaiorPivo] = k;
                return 0;
	}
        bol pivotacaoCompleta(int i){
                for(int j=i; j<m; j++){
                   for(k=i; k<n; k++){
                      if(fabs(A[j][k])>A[indeLinha][indeColun]){
                        indeLinha=j;
                        indeColun=k;
                      }
                   }
                 }
                 if(A[indeLinha][indeColun]==0){
                   return 1;
                 }
                 if(indeLinha!=i){
                   double * point = A[i];
		   A[i] = A[indeLinha];
		   A[indeLinha] = point;
                 }
                 if(indeColun!=i){
                   for(int j=0; j<m; j++){
                      aux=A[i][i];
                      A[j][i]=A[j][indeColun];
                      A[j][indeColun]=aux;
                   }
                 }
                 return 0;
                 
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
        void SistemaEqui(){
             for(int i=0; i<m; i++){
                
                for(int j=0; j<n-1; j++){
                   cout <<"X"<<i<<"*"<<A[i][j]<<"+";
                }
                 cout <<"X"<<i+1<<"*"<<A[i+1][j]<<"+";
                 cout <<"X"<<i+2<<"*"<<A[i+2][j]<<"+";
             }
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
