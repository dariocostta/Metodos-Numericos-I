#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
using std::nothrow;
using std::cout;
using std::cin;
using std::string;

typedef struct def_sistema {
	double ** A;
	int m, n; //Matriz m x (m+1)!
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
			if(op) {
				if(pivotacaoParcial(i)) {
					break;  //nao tem mais elementos diferentes de 0
				}
			} else {
				if(pivotacaoCompleta(i)) {
					break; //nao tem mais elementos diferentes de 0
				}
			}
			for(int j=i+1; j<m; j++) {
				double m_i = -(A[j][i]/A[i][i]);
				for(int k=i; k<n; k++) {
					A[j][k]=A[j][k]+m_i*A[i][k];
				}
			}
		}
	}
	
	double * substituicoesRetroativas(){
		double * d = (double *) malloc(m * sizeof(double));
		for(int i = m-1; i>=0 ; --i){
				d[i]=A[i][m]/A[i][i];
			for(int j = m-1; j>i; --j){
				d[i]-=(A[i][j]*d[j])/A[i][i];
			}
		}
		return d;
	}
	
	void gaussJordan(bool op) {
		for(int i=0; i<m; i++) {
			if(op==1) {
				if(pivotacaoParcial(i)) {
					break;  //nao tem mais elementos diferentes de 0
				}
			} else {
				if(pivotacaoCompleta(i)) {
					break; //nao tem mais elementos diferentes de 0
				}
			}
			
			for(int j=0; j<m; j++) {
				double m_i=-(A[j][i]/A[i][i]);
				for(int k=i; k<n; k++) {
					if(j==i) {
						continue;
					} else {
						A[j][k]=A[j][k]+m_i*A[i][k];
					}
				}
			}
			double A_i_i = A[i][i];
			for(int k=i; k<n; ++k){
				A[i][k]=A[i][k]/A_i_i;
			}
		}
	}


	/* Funcao pivotacaoParcial
	 * Acao: Troca a linha k pela linha i, onde ocorra
	 *			 max{absoluto(A[i][k])}, com i em {k, ..., m}
	 * Entrada: - Inteiro k: Passo que deve ser feita a pivotacao,
	 *						a partir do elemento A[k][k]
	 * Saida: - True:  Pivo nulo
	 * 				- False: Pivo encontrado
	 */
	bool pivotacaoParcial(int k) {
		int indexMaiorPivo = k;
		for(int i=k+1; i < m; i++) {
			if(fabs(A[i][k]) > fabs(A[indexMaiorPivo][k]))
				indexMaiorPivo = i;
		}
		
		// Caso não tenha x!=0 na coluna k, então usamos pivotacaoCompleta:
		if(A[indexMaiorPivo][k]==0) {
				return pivotacaoCompleta(k);
		}
		
		double * aux_vet = A[k];
		A[k] = A[indexMaiorPivo];
		A[indexMaiorPivo] = aux_vet;
		
		int aux = permutacaoLinhas[k];
		permutacaoLinhas[k] = permutacaoLinhas[indexMaiorPivo];
		permutacaoLinhas[indexMaiorPivo] = aux;
		
		return false;
	}

	bool pivotacaoCompleta(int i) {
		int indexLinha = i;
		int indexColuna = i;
		for(int j=i; j<m; j++) {
			for(int k=i; k<n; k++) {
				if( fabs(A[j][k])>fabs(A[indexLinha][indexColuna])) {
					indexLinha=j;
					indexColuna=k;
				}
			}
		}

		if(A[indexLinha][indexColuna]==0) {
			return true;
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
		
		int aux_p = permutacaoLinhas[i];
		permutacaoLinhas[i] = permutacaoLinhas[indexLinha];
		permutacaoLinhas[indexLinha] = aux_p;
		
		aux_p = permutacaoColunas[i];
		permutacaoColunas[i] = permutacaoColunas[indexColuna];
		permutacaoColunas[indexColuna] = aux_p;
		
		return false;
	}

	void deletaMatriz() {
		if(A!=nullptr){
			for(int i = 0; i < m; i++) {
				if(A[i]!=nullptr)
					delete[] A[i];
				A[i]=nullptr;
			}
			delete[] A;
		}
		if(permutacaoLinhas!=nullptr)
			delete[] permutacaoLinhas;
		if(permutacaoColunas!=nullptr)
			delete[] permutacaoColunas;
		A=nullptr;
		permutacaoLinhas=nullptr;
		permutacaoColunas=nullptr;
	}

	/* Funcao alocaMatriz
	 * Saida padrao: - True: Erro na alocacao
	 * 							 - False: Tudo ocorreu bem
	 */
	bool alocaMatriz() {
		A = (double**) malloc(m * sizeof(double*));
		permutacaoLinhas = (int *) malloc(m * sizeof(int));
		permutacaoColunas = (int *) malloc(m * sizeof(int));
		if(A==nullptr || permutacaoLinhas==nullptr ||  permutacaoColunas==nullptr) {
			deletaMatriz();
			return true;
		}
		
		for(int i=0; i<m; i++) {
			A[i] = (double*) malloc(n * sizeof(double));
			if(A[i] == nullptr) {
				deletaMatriz();
				return true;
			}
		}
		
		for(int i=0; i<m; i++){
			permutacaoLinhas[i]=i;
			permutacaoColunas[i]=i;
		}
			
		return false;
	}

	void SistemaEqui() {
		for(int i=0; i<m; i++) {
			int j;
			for(j=0; j<m; j++) {
				cout <<A[i][j]<<"*"<<"X"<<j+1;
				if(j!=m-1)
					cout <<"+";
			}
			cout<<" = "<<A[i][j]<<"\n";
		}
	}
	
} Sistema;

int main() {
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(3);
	int tamanho;
	Sistema * Cd_v=nullptr;
	bool pivotacao=true;
	double * d;
	double a;
	
	int op=1;
	do {
		
		
		cout << "Quantos pendulos?";
		cin >> tamanho;
		if(Cd_v==nullptr){
			Cd_v = new(nothrow) Sistema;
		} else {
			Cd_v->deletaMatriz();
		}
		
		Cd_v->m=tamanho;
		Cd_v->n=tamanho+1; //Vetor v incluso na matriz A
		
		if(Cd_v->alocaMatriz()){
			cout<<"Erro na alocacao!\n";
			break;
		}
		for(int i=0; i < Cd_v->m ; ++i){
			for(int j=0; j < Cd_v->m; ++j){
        system("cls");
				//Cd_v->SistemaEqui(); //<---- Para teste! Apagar depois esta linha!
				cout<<"Preencha a matriz C:\nC["<<i+1<<"]["<<j+1<<"] = ";
				cin >> Cd_v->A[i][j];
			}
		}
		for(int i=0; i < Cd_v->m; i++){
	    system("cls");
			//Cd_v->SistemaEqui(); //<---- Para teste! Apagar depois esta linha!
			cout<<"Preencha o vetor V:\nV["<<i+1<<"] = ";
			cin >> Cd_v->A[i][Cd_v->m];
		}
		cout << "Por fim, digite o coeficiente a: ";
		cin >> a;
		
		
		cout << "\n\t1 -- Gauss() \n\t2 -- GaussJordan()\n\t0 -- Sair\n";
		cin >> op;

		switch(op){
			case 0:
				break;
				
			case 1:
				cout<< "\nDeseja pivotacao?\n\t1 -- Sim\n\t0 -- Nao\n";
				cin >> pivotacao;
				cout << "Sistema antes de GaussNormal():\n"; //<---- Para teste! Apagar depois esta linha!
				//Cd_v->SistemaEqui();  //<---- Para teste! Apagar depois esta linha!
				Cd_v->gaussNormal(pivotacao);
				cout << "\nSistema depois de GaussNormal():\n"; //<---- Para teste! Apagar depois esta linha!
				d = Cd_v->substituicoesRetroativas();
				
				cout<<"Deslocamentos:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<d[i]<<"]";
				}
				cout<<"\n";
				cout<<"Amplitude:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<d[i]*a<<"]";
				}
				cout<<"\n";
				
				delete[] d;
				//Cd_v->SistemaEqui();				 //<---- Para teste! Apagar depois esta linha!
				break;
				
			case 2:
				cout<< "\nDeseja pivotacao?\n\t1 -- Sim\n\t0 -- Nao\n";
				cin >> pivotacao;
				cout << "Sistema antes de GaussJordan():\n"; //<---- Para teste! Apagar depois esta linha!
				//Cd_v->SistemaEqui();  //<---- Para teste! Apagar depois esta linha!
				Cd_v->gaussJordan(pivotacao);
				cout << "\nSistema depois de GaussJordan():\n"; //<---- Para teste! Apagar depois esta linha!
				//Cd_v->SistemaEqui();				 //<---- Para teste! Apagar depois esta linha!
				break;
				
			default:
				cout << "Erro!\n";
		}
	} while(op);
	Cd_v->deletaMatriz();
	delete Cd_v;
	return 0;
}
