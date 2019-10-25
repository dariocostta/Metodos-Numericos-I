#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using std::cout;
using std::cin;
using std::string;

typedef struct definicao_pendulo {

  //Dados basicos do problema:
  double a2, a3, lambda;

  //Apenas para exibição de mais informações
  string quadro_NR, quadro_NRFL;
  int qtd_iteracoes;

  double funcao( double x ){
    return a3*(pow(x, 3))-9*a2*x+3;
  }

  double derivadaSimples( double x ){
    return 3*a3*(pow(x,2))-9*a2;
  }

  double derivadaFL( double x, double x_w){
      double dxdy = derivadaSimples(x);
      if(fabs(dxdy)>lambda){
        return dxdy;
      }
      return derivadaSimples(x_w);
  }

    /* opMet  | Metodo
        1     | NR simples
        0     | NR FL

      opInicio | Metodo
        1      | Utiliza o x0 dado
        0      | Procura sozinho pela bissecao
    */
  double NewtonRaphson(double x0, double pres, bool opMet, bool opInicio){
    // x_k é o x da iteração atual e x_a o da iteração anterior
    double x_k = 0, x_a=0,  x_w=0; 
    x_k=(opInicio) ? (x0) : Bissecao(5);
    double derivada, erro;
    qtd_iteracoes=1;
    
		// Nao faz parte do metodo, apenas para printagem do quadro resposta
		char buffer[100];
    quadro_NR = (opMet) ? ("") : quadro_NR;
    quadro_NRFL = (!opMet) ? ("") : quadro_NRFL;
    
    string Quadro = " i |      x      |    f(x)      |      dx      \n";

    do {
    	
    	{ // Construção da tabela de iteração, não há calculos aqui, apenas trabalho com strings
  			sprintf(buffer," %i |   %.5lf   |   %.5lf   |   %.5lf   \n", qtd_iteracoes, x_k, funcao(x_k), derivadaSimples(x_k));
				Quadro +=buffer;
      }
      
      qtd_iteracoes++;
      
      derivada = (opMet) ? (derivadaSimples(x_k)) : (derivadaFL(x_k, x_w));
	
      x_w = (derivadaSimples(x_k)>=lambda) ? (x_k) : (x_w);
      x_a = x_k;

      x_k = x_k - ((funcao(x_k))/derivada); //Calculo do x_k+1
      erro = x_k - x_a;
      
    }while( ( fabs(erro)>pres || funcao(x_k)>pres ) && ( qtd_iteracoes < 1000 ) );
    
  	{ // Construção da tabela de iteração, não há calculos aqui, apenas trabalho com strings
  			sprintf(buffer," %i |   %.5lf   |   %.5lf   |   %.5lf   \n", qtd_iteracoes, x_k, funcao(x_k), derivadaSimples(x_k));
				Quadro +=buffer;
    }
   
    if(opInicio==0 && Bissecao(5)==-100){
      Quadro = "Nao existe raiz positiva.\n";
      x_k=-1;
    } else {
      if(x_k<0 && opInicio==1 && Bissecao(5)==-100)
        Quadro+="Nao existe raiz positiva.\n";
      else if(x_k<0 && opInicio==1 && Bissecao(5)!=-100)
          Quadro+="Existe raiz positiva, mas com o inicial fornecido nao foi possivel encontrar.\n";
    }

    if(opMet)
        quadro_NR = Quadro;
      else
        quadro_NRFL = Quadro;

    return x_k;
  }

  double Bissecao (double pres){
    double * intervalo = IntervaloAB();

    if(intervalo[0] == 0 && intervalo[1]== 0){
      return -100;
    }

    double x = (intervalo[1]+intervalo[0])/2;
    while((intervalo[1]-intervalo[0])>pres){
      x = (intervalo[1]+intervalo[0])/2;
      if (funcao(intervalo[0])*funcao(x)<0)
        intervalo[1] = x;
      else 
        intervalo[0] = x;
    }

    x=(intervalo[1]+intervalo[0])/2;

    delete[] intervalo;
    int contd=0;
    
    while(derivadaSimples(x)<lambda && contd<100){
      x+=1;
      contd++;
    }

    return x;
  }

  double* IntervaloAB(){

    double *I = new(std::nothrow) double[2];
    I[0]=0;
    I[1]=0;
    double r, k=0, x;
    if(3/a3 < a2/a3)
      r = 1+fabs(a2/a3);
    else
      r = 1+fabs(3/a3);
    if(a3*a2>0){
      x=sqrt((3*a2)/a3);
      if(a3>0 && a2>0){
        if(funcao(x)<=0){
          I[1]=x;
          return I;
        }else{
          // Nao existe raiz positiva
          I[0]=0;
          I[1]=0;
          return I;
        }
      }else{
        I[0]=x;
        while(k<=r){
          k=k+5;
          if(funcao(k)<0){
            I[1]=k;
            return I;
          }
        }
      }
    }else{
      if(a3<0 && a2>0){
        while(k<=r){
          k=k+5;
          if(funcao(k)<0){
            I[1]=k;
            return I;
          }
        }
      }else{
          // Nao existe raiz positiva
        I[0]=0;
        I[1]=0;
        return I;
      }
    }
    return I;
  }

} Pendulo;

int main(){
  std::cout.setf( std::ios::fixed, std:: ios::floatfield );
  std::cout.precision(6);
  
  int op=0, op_inicio=0, qtd_lambda, i;
  Pendulo * pendulos=NULL;
  double x,y;
  double pres, *x0=NULL;
  do{
    if(pendulos==NULL)
       cout << "\n1 -- Inserir dados do(s) pendulo(s)\n0 -- Sair\n";
    else
      cout << "\n1 -- Inserir dados do(s) pendulo(s) \n2 -- Quadro Resposta\n3 -- Quadro Comparativo\n0 -- Sair\n";
    cin >> op;

    switch(op){
      case 1:
        cout << "Digite o numero de pendulos:";
        cin >> qtd_lambda;
        if(pendulos!=NULL){
          delete[] pendulos;
          pendulos=NULL;
        }
        pendulos = new(std::nothrow) Pendulo[qtd_lambda];
        x0 = new (std:: nothrow) double[qtd_lambda];
        
        for (i=0 ; i<qtd_lambda ; i++){
          cout << "         Pendulo "<<i+1 <<""<<"\n";
          cout << "Digite o valor do lambda: ";
          cin >> pendulos[i].lambda;
          cout << "Digite o valor de a3: ";
          cin >> pendulos[i].a3;
          cout << "Digite o valor de a2: ";
          cin >> pendulos[i].a2;
        }
        break;

      case 2:
        if(pendulos!=NULL){
          op_inicio=0;
          cout <<"Digite a precisao: ";
          cin >> pres;

          cout << "Deseja fornecer o(s) valor(es) inicial(is) para o Metodo? (1 - Sim | 0 - Nao)";
          cin >> op_inicio;
          if(op_inicio){
            if(x0!=NULL){
              delete[] x0;
              x0=NULL;
            }
            x0 = new(std :: nothrow) double[qtd_lambda];
            for( i=0; i< qtd_lambda; i++){
              cout << "Valor inicial para o pendulo " << i+1<<": ";
              cin >> x0[i];
            }
          }

          cout <<"\n";

          cout << "--------------------------------------------------\n";
          cout << "|          "<< " | Newton Raphson | Newton Raphson FL |\n";
          for (i=0;i<qtd_lambda;i++){
            double NR = pendulos[i].NewtonRaphson(x0[i], pres, 1, op_inicio);
            double NRFL = pendulos[i].NewtonRaphson(x0[i], pres,0, op_inicio);
            cout <<"| Pendulo "<< i+1 <<" | ";
            if(NR<0)
              cout << "      NE";
            else 
              cout << NR;
            cout <<"       | ";
            if(NRFL<0)
              cout << "      NE";
            else
              cout <<NRFL;
            cout <<"          ";
            cout <<"|\n";
          }
          cout << "--------------------------------------------------\n\n";

          int op_met, n_pendulo;
          cout << "Deseja ver algum detalhamento? (1 - Sim | 0 - Nao): ";
          cin >> op_met;
          if(op_met){
            do{
              cout << "\tPendulo que deseja detalhar:";
              cin >> n_pendulo;
            }while(n_pendulo>qtd_lambda || n_pendulo <= 0);
            cout << "\tDetalhar:\n\t1 -- Newton Raphson\n\t2 -- Newton Raphson FL\n\t3 -- Ambos\n";
            cin >> op_met;
            switch(op_met){
              case 1:
                cout << "\nNewton Raphson\n--------------------------------------------------\n";
                cout << pendulos[n_pendulo-1].quadro_NR;
                cout << "--------------------------------------------------\n";
                break;
                
              case 2:
                cout << "\nNewton Raphson FL\n--------------------------------------------------\n";
                cout << pendulos[n_pendulo-1].quadro_NRFL;
                cout << "--------------------------------------------------\n";
                break;

              case 3:
                cout << "\nNewton Raphson\n--------------------------------------------------\n";
                cout << pendulos[n_pendulo-1].quadro_NR;
                cout << "--------------------------------------------------\n";

                cout << "\nNewton Raphson FL\n--------------------------------------------------\n";
                cout << pendulos[n_pendulo-1].quadro_NRFL;
                cout << "--------------------------------------------------\n";
                break;
            }
          }
        }
        break;
      
      case 3:
          cout <<"Digite a precisao: ";
          cin >> pres;

          cout << "Deseja fornecer o(s) valor(es) inicial(is) para o Metodo? (1 - Sim | 0 - Nao)";
          cin >> op_inicio;
          if(op_inicio){
            if(x0!=NULL){
              delete[] x0;
              x0=NULL;
            }
            x0 = new(std :: nothrow) double[qtd_lambda];
            for( i=0; i< qtd_lambda; i++){
              cout << "Valor inicial para o pendulo " << i+1<<": ";
              cin >> x0[i];
            }
          }
          
          cout <<"\n";
          cout << " ----------------------------------------------------------------------\n";
          cout << " |         |         Newton Raphson      |     Newton Raphson FL      |\n";
          cout << " |         |    x    |   f(x)   | iter.  |    x    |   f(x)   | iter. |\n";
        for (i=0;i<qtd_lambda;i++){
          x = pendulos[i].NewtonRaphson(x0[i],pres, 1, op_inicio);
          int qtd_x = pendulos[i].qtd_iteracoes;
          y = pendulos[i].NewtonRaphson(x0[i],pres, 0, op_inicio);
          int qtd_y =pendulos[i].qtd_iteracoes;
          cout <<" | Pênd.  "<< i+1 <<"| ";
          if(x<0)
            cout<<"              NE            |";
          else
            cout<< x <<"| "<< pendulos[i].funcao(x) << " |    " << qtd_x << "   | ";
          if(y<0)
            cout<<"              NE            |\n";
          else
            cout << y <<"| "<< pendulos[i].funcao(y) << " |    " << qtd_y << "  | \n";
        }
        cout << " ----------------------------------------------------------------------\n\n";

        break;

      case 0:
        break;
      default:
        cout << "\nErro!\n";

    }
  
  }while(op);
  delete[] pendulos;
  delete[] x0;
}
