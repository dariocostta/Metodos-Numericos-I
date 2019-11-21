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

	/* Funcao gauss
	 * Acao:
	 * Algoritmo:
	 * Entrada:
	 * Saida padrao:
	 * Saida erro:
	 */
	void gaussNormal(bool op) {
		for(int i=0; i<m; i++) {
			if(op==1) {
				if(pivotacaoParcial(i)==1) {
					break;  //nao tem mais elementos diferentes de 0
				}
			} else {
				if(pivotacaoCompleta(i)==1) {
					break; //nao tem mais elementos diferentes de 0
				}
			}
			for(int j=i+1; j<m; j++) {
				for(int k=i; k<=n; k++) {
					A[j][k]=A[j][k]-((A[j][i]/A[i][i])*A[i][k]);
				}
			}
		}
	}
	void gaussJordan(bool op) {
		for(int i=0; i<m; i++) {
			if(op==1) {
				if(pivotacaoParcial(i)==1) {
					break;  //nao tem mais elementos diferentes de 0
				}
			} else {
				if(pivotacaoCompleta(i)==1) {
					break; //nao tem mais elementos diferentes de 0
				}
			}
			for(int j=0; j<m; j++) {
				for(int k=i; k<=n; k++) {
					if(j==i) {
						A[j][k]=A[j][k]/A[i][i];
					} else {
						A[j][k]=A[j][k]-((A[j][i]/A[i][i])*A[i][k]);
					}
				}
			}
		}
	}


	/* Funcao pivotacaoParcial
	 * Acao: Troca a linha k pela linha i, onde ocorra
	 *			 max{absoluto(A[i][k])}, com i em {k, ..., m}
	 * Entrada: - Inteiro k: Passo que deve ser feita a pivotacao,
	 *						a partir do elemento A[k][k]
	 */
	bool pivotacaoParcial(int k) {
		int indexMaiorPivo = k;
		for(int i=k+1; i < m; i++) {
			if(fabs(A[i][k]) > fabs(A[indexMaiorPivo][k]))
				indexMaiorPivo = i;
		}
		if(A[indexMaiorPivo][k]==0) {
			if(pivotacaoCompleta(k+1)==1) {
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
	
	bool pivotacaoCompleta(int i) {
		int indexLinha = i;
		int indexColuna = i;
		for(int j=i; j<m; j++) {
			for(int k=i; k<n; k++) {
				if( fabs(A[j][k])>fabs(A[indexLinha][indexColuna])){
					indexLinha=j;
					indexColuna=k;
				}
			}
		}
		
		if(A[indexLinha][indexColuna]==0) {
			return 1;
		}
		
		if(indexLinha!=i) {
			double * point = A[i];
			A[i] = A[indexLinha];
			A[indexLinha] = point;
		}
		
		if(indexColuna!=i) {
			double aux;
			for(int j=0; j<m; j++) {
				aux=A[j][i];
				A[j][i]=A[j][indexColuna];
				A[j][indexColuna]=aux;
			}
		}
		return 0;
	}

	void deletaMatriz(){
		for(int i = 0; i < m; i++) {
			if(A[i]!=nullptr)
				delete[] A[i];
			A[i]=nullptr;
		}
		delete[] A;
	}

	/* Funcao alocaMatriz
	 * Saida padrao: - True: Erro na alocacao
	 * 							 - False: Tudo ocorreu bem
	 */
	bool alocaMatriz(){
		A = (double**) malloc(m);
		if(A!=nullptr) {
			for(int i=0; i<m; i++) {
				A[i] = (double*) malloc(n);
				if(A[i] == nullptr) {
					deletaMatriz();
					return true;
				}
			}
			return false;
		}
		return true;
	}

	void SistemaEqui(){
		for(int i=0; i<m; i++) {
			int j;
			for(j=0; j<n-1; j++) {
				cout <<"X"<<i<<"*"<<A[i][j]<<"+";
			}
			cout <<"X"<<i+1<<"*"<<A[i+1][j]<<"+";
			cout <<"X"<<i+2<<"*"<<A[i+2][j]<<"+";
		}
	}

} Sistema;

int main() {
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);
	int op=1;
	do {
		cout << "\n1 -- Inserir dados do(s) pendulo(s) \n0 -- Sair\n";
		cin >> op;
	} while(op);
	return 0;
}
