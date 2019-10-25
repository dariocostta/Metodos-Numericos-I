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
