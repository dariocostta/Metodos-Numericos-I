#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using std::cout;
using std::cin;
using std::string;
int **A=(int**) malloc(m);
for(i=0; i<m; i++){
   *(A+i)=(int*) malloc(n);
}


int main(){
  std::cout.setf( std::ios::fixed, std:: ios::floatfield );
  std::cout.precision(6);
  int op=1;

  do{
  	cout << "\n1 -- Inserir dados do(s) pendulo(s) \n0 -- Sair\n";
    cin >> op;
	}while(op);

}
void gauss(){
//matriz MxN
   for(i=0; i<m; i++){
      if(*(*(A+i)+j)==0){
         for(p=0; p<m; p++){
            if(*(*(A+p)+i)!=0)){
              k=p;
              break;
            }
         for(p=i-1; p<m; p++){
            aux=*(*(A+i)+p);
            *(*(A+i)+p)=*(*(A+k)+p);
            *(*(A+k)+p)=aux;
         }
       }
      j=0;
      while(j<m){
         for(k=m-1; k<n; k++){
            b=*(*(A+i)+k);
            *(*(A+j)+k)=*(*(A+j)+k)-(*(*(A+j)+i)/(*(*(A+i)+i))*b;
         }
         j++;
         if(j==i){
           j++;
         }
      }
   }
