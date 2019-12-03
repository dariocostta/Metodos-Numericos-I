#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
using std::nothrow;
using std::cout;
using std::cin;
using std::string;

typedef struct def_sistema {
	double ** A , **A_cop; //Na matriz A manteremos o sistema entrado pelo usuario e faremos as alteracoes dos metodos na A_cop
	int m, n; //Matriz m x (m+1)!
	int * permutacaoLinhas, * permutacaoColunas, *Coluna;
  double soma=-pow(10.0,308.0);
	/* Funcao gauss
	 * Acao:
	 * Algoritmo:
	 * Entrada:
	 * Saida padrao:
	 * Saida erro:
	 */
	double * gaussNormal(bool op) {
		reset_Cop();
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
        
        //cout <<j<<"\n"<< A_cop[j][i] <<"/"<<A_cop[i][i]<<"\t";
				double m_i = -(A_cop[j][i]/A_cop[i][i]);
				for(int k=i; k<n; k++) {
					A_cop[j][k]=A_cop[j][k]+m_i*A_cop[i][k];
				 //cout <<"\nA_cop[j][k]="<< A_cop[j][k];
        }
			}
		}
		return substituicoesRetroativas();
	}
	
	
	
	double * substituicoesRetroativas(){
		double * d = (double *) malloc(m * sizeof(double));
		for(int i = m-1; i>=0 ; --i){
      /*cout <<"subst. retroativas 1°for  "<< A_cop[i][m] <<"/"<<A_cop[i][i]<<"\t";*/
        if (A_cop[i][i]==0){
          d[i] = 0;
          if(A_cop[i][m]!=0){
            d[i] = (pow(10.0,308.0));
            return d;
          }
        }
        else
          d[i]=A_cop[i][m]/A_cop[i][i];
			for(int j = m-1; j>i; --j){
        /*cout <<"subst. retroativas 2°for  "<< A_cop[i][j]<<"*"<<d[j]<<"/"<<A_cop[i][i]<<"\t";*/
				d[i]-=(A_cop[i][j]*d[j])/A_cop[i][i];
			}
		}
		return d;
	}
	
	double * gaussJordan(bool op) {
		reset_Cop();
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
        //cout << A_cop[j][i] <<"/"<<A_cop[i][i]<<"\t";
				double m_i=-(A_cop[j][i]/A_cop[i][i]);
				for(int k=i; k<n; k++) {
					if(j==i) {
						continue;
					} else {
						A_cop[j][k]=A_cop[j][k]+m_i*A_cop[i][k];
					}
				}
			}
			double A_i_i = A_cop[i][i];
			for(int k=i; k<n; ++k){
				A_cop[i][k]=A_cop[i][k]/A_i_i;
			}
		}
		return substituicoesRetroativas();
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
			if(fabs(A_cop[i][k]) > fabs(A_cop[indexMaiorPivo][k]))
				indexMaiorPivo = i;
		}
		
		// Caso não tenha x!=0 na coluna k, então usamos pivotacaoCompleta:
		if(A_cop[indexMaiorPivo][k]==0) {
				return pivotacaoCompleta(k);
		}
		
		double * aux_vet = A_cop[k];
		A_cop[k] = A_cop[indexMaiorPivo];
		A_cop[indexMaiorPivo] = aux_vet;
		
		int aux = permutacaoLinhas[k];
		permutacaoLinhas[k] = permutacaoLinhas[indexMaiorPivo];
		permutacaoLinhas[indexMaiorPivo] = aux;
		
		return false;
	}

	bool pivotacaoCompleta(int i) {
		int indexLinha = i;
		int indexColuna = i;
		for(int j=i; j<m; j++) {
			for(int k=i; k<n-1; k++) {
				if( fabs(A_cop[j][k])>fabs(A_cop[indexLinha][indexColuna])) {
					indexLinha=j;
					indexColuna=k;
				}
			}
		}

		if(A_cop[indexLinha][indexColuna]==0) {
			return true;
		}

		if(indexLinha!=i) {
			double * point = A_cop[i];
			A_cop[i] = A_cop[indexLinha];
			A_cop[indexLinha] = point;
		}

		if(indexColuna!=i) {
			double aux;
			for(int j=0; j<m; j++) {
				aux=A_cop[j][i];
				A_cop[j][i]=A_cop[j][indexColuna];
				A_cop[j][indexColuna]=aux;
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
		if(A!=nullptr && A_cop!=nullptr){
			for(int i = 0; i < m; i++) {
				if(A[i]!=nullptr)
					delete[] A[i];
				A[i]=nullptr;
				if(A_cop[i]!=nullptr)
					delete[] A_cop[i];
				A_cop[i]=nullptr;
				
			}
			delete[] A;
			delete[] A_cop;
		}
		if(permutacaoLinhas!=nullptr)
			delete[] permutacaoLinhas;
		if(permutacaoColunas!=nullptr)
			delete[] permutacaoColunas;
		A=nullptr;
		A_cop=nullptr;
		permutacaoLinhas=nullptr;
		permutacaoColunas=nullptr;
	}

	/* Funcao alocaMatriz
	 * Saida padrao: - True: Erro na alocacao
	 * 							 - False: Tudo ocorreu bem
	 */
	bool alocaMatriz() {
		A = (double**) malloc(m * sizeof(double*));
		A_cop = (double**) malloc(m * sizeof(double*));
		
		permutacaoLinhas = (int *) malloc(m * sizeof(int));
		permutacaoColunas = (int *) malloc(m * sizeof(int));

    Coluna = (int *) malloc(m * sizeof(int));

		if(A==nullptr  || A_cop==nullptr || permutacaoLinhas==nullptr ||  permutacaoColunas==nullptr || Coluna==nullptr) {
			deletaMatriz();
			return true;
		}
		
		for(int i=0; i<m; i++) {
			A[i] = (double*) malloc(n * sizeof(double));
			A_cop[i] = (double*) malloc(n * sizeof(double));
			if(A[i] == nullptr || A_cop[i] == nullptr ) {
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
  
	void reset_Cop(){
		if(A !=nullptr && A_cop !=nullptr){
			for(int i = 0; i<m ; ++i){
				for(int j=0; j <n; ++j){
					A_cop[i][j]=A[i][j];
				}
			}
			for(int i=0; i<m; i++){
				permutacaoLinhas[i]=i;
				permutacaoColunas[i]=i;
		  }
		}
    double soma=-pow(10.0,308.0);
	}

	void SistemaEqui(bool original) {
		double ** A_s = (original) ? A : A_cop;
		for(int i=0; i<m; i++) {
			int j;
			for(j=0; j<m; j++) {
        if (A_s[i][j]>=0){
          cout <<A_s[i][j]<<"*"<<"X"<<permutacaoColunas[j]+1;
        }
        else
          cout <<A_s[i][j]*-1<<"*"<<"X"<<permutacaoColunas[j]+1;
				

				if(j!=m-1){
					if(A_s[i][j+1]>=0)
						cout <<"\t+\t ";
          else{
            //A_s[i][j+1] = A_s[i][j+1] *-1; 
            cout <<"\t-\t ";
          }
            
        }
			}
			cout<<" = "<<A_s[i][j]<<"\n";
     
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
		
		if(Cd_v==nullptr)
			cout<< "\nMenu:\n\t1 -- Informar Sistema\n";
		else
			cout << "\nMenu:\n\t1 -- Novo Sistema\n\t2 -- Gauss() \n\t3 -- GaussJordan()\n\t0 -- Sair\n";
		cin >> op;

		switch(op){
			case 0:
				break;
				
			case 1:
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
						cout<<"Preencha a matriz C:\nC["<<i+1<<"]["<<j+1<<"] = ";
						cin >> Cd_v->A[i][j];
					}
				}
				for(int i=0; i < Cd_v->m; i++){
			    system("cls");
					cout<<"Preencha o vetor V:\nV["<<i+1<<"] = ";
					cin >> Cd_v->A[i][Cd_v->m];
				}
				cout << "Por fim, digite o coeficiente a: ";
				cin >> a;
				break;
			
			case 2:
				cout<< "\nQue tipo de pivotacao:\n\t1 -- Parcial\n\t0 -- Total\n";
				cin >> pivotacao;
				cout << "Sistema antes de Gauss():\n";
        Cd_v->reset_Cop();
				Cd_v->SistemaEqui(1);
				d = Cd_v->gaussNormal(pivotacao);
				cout << "\nSistema depois de Gauss():\n";
				Cd_v->SistemaEqui(0);  
				for(int i=0; i < Cd_v->m;++i){
          if(d[i]==(pow(10.0,308.0))){
            cout << "\t\tSISTEMA IMPOSSIVEL\n\n";
            for(int j=0; j < Cd_v->m;++j)
              d[j]=0;
            break;
          }
        }
        for(int i=0; i < Cd_v->m ; ++i){
          //cout <<" A[i][i]="<< Cd_v->A_cop[i][i]<<"\n";
					if(Cd_v->A_cop[i][i]==0){
            Cd_v->soma=0;
            for(int j=0;j <= Cd_v->m;j++){
              Cd_v->soma+=Cd_v->A_cop[i][j];
              //cout << soma<<"\n";
            }
          }
        }
        //cout << soma<<"\n";
        if(Cd_v->soma == 0)
          cout << "\t\tSISTEMA COM MULTIPLAS SOLUCOES\n\n";
        for(int i=0; i < Cd_v->m;++i)
          if(d[i]<0){
            cout << "\t\tSOLUÇÃO iNVÁLIDA: DESLOCAMENTO(S) NEGATIVO(S) \n\n";
            //for(int j=0; j < Cd_v->m;++j)
              //d[j]=0;
            break;
          }
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
				cout<<"\nPermutacao das linhas:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<Cd_v->permutacaoLinhas[i]+1<<"]";
				}
				cout<<"\nPermutacao das colunas:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<Cd_v->permutacaoColunas[i]+1<<"]";
				}
				delete[] d;
				break;
				
			case 3:
				cout<< "\nQue tipo de pivotacao:\n\t1 -- Parcial\n\t0 -- Total\n";
				cin >> pivotacao;
				cout << "Sistema antes de GaussJordan():\n";
        Cd_v->reset_Cop();
				Cd_v->SistemaEqui(1);  
				d = Cd_v->gaussJordan(pivotacao);
				cout << "\nSistema depois de GaussJordan():\n";
				Cd_v->SistemaEqui(0);	
        for(int i=0; i < Cd_v->m;++i){
          if(d[i]==(pow(10.0,308.0))){
            cout << "\t\tSISTEMA IMPOSSIVEL\n\n";
            for(int j=0; j < Cd_v->m;++j)
              d[j]=0;
            break;
          }
        }   
        for(int i=0; i < Cd_v->m ; ++i){
					if(Cd_v->A_cop[i][i]==0){
            Cd_v->soma =0;
            for(int j=0;j <= Cd_v->m;j++){
              Cd_v->soma+=Cd_v->A_cop[i][j];
            }
          }
        }
        if(Cd_v->soma == 0)
          cout << "\t\tSISTEMA COM MULTIPLAS SOLUCOES\n\n";
        for(int i=0; i < Cd_v->m;++i)
          if(d[i]<0){
            cout << "\t\tSOLUÇÃO iNVÁLIDA: DESLOCAMENTO(S) NEGATIVO(S) \n\n";
            //for(int j=0; j < Cd_v->m;++j)
              //d[j]=0;
            break;
          }
				cout<<"Deslocamentos:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<d[i]<<"]";
				}
				cout<<"\n";
				cout<<"Amplitude:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<d[i]*a<<"]";
				}
				cout<<"\nVetor Linha:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<Cd_v->permutacaoLinhas[i]+1<<"]";
				}
				cout<<"\nVetor Coluna:\n";
				for(int i=0; i < Cd_v->m;++i){
					cout<<"["<<Cd_v->permutacaoColunas[i]+1<<"]";
				}
				
				delete[] d;
				break;
				
			default:
				cout << "Erro!\n";
		}
	} while(op);
	Cd_v->deletaMatriz();
	delete Cd_v;
	return 0;
}
