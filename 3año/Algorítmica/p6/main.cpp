#include <iostream>
#include "nReinasBacktracking.hpp"
#include "funcionesComunes.hpp"

int main(){
	int op = 0;
	vector<vector<int> > soluciones;

	while(op != 1){
		cout<<"\t1. Salir"
			<<"\n\t2. N reinas backtraking."
			<<"\n\t3. N reinas probabilistas"
			<<"\nOpcion: ";

			cin>>op;

		switch(op){
			default:
				cout<<"Opcion no encontrada."<<endl;
			break;
			case 1:
				op = 1;
			break;
			case 2:
				cout<<"Indique el numero de reinas: ";
				int nReinas;
				cin>>nReinas;
				nReinasBacktracking(nReinas, soluciones);
				verSoluciones(soluciones);

				cout<<"Hay "<<soluciones.size()<<" soluciones para "<<nReinas<<" reinas\n"<<endl;
			break;
			case 3:
				cout<<"WIP"<<endl;
			break;
		}
		
	}





	return 0;
}