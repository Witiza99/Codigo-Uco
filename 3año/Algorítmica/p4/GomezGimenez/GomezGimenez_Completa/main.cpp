#include "algorithm.hpp"
#include "suppressioncollinearpointsmethod.hpp"
#include "greedymethod.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
   int aux=0;

   while (aux!=3){

      cout << "Pulsa la opción que desee:"<<endl;
      cout <<"1.CollinearSuppressionMethod: "<<endl;
      cout <<"2.GreedyMethod: "<<endl;
      cout <<"3.Cerrar programa"<<endl;

      cin >> aux;

      Algorithm *a;
      char fileNameDC[100], fileNamePA[100];
      int n;
      DigitalCurve aP;

      switch(aux){

         case 1:
            //It creates a pointer to algorithm class to use overload in execution               
            cout << "Digital curve to obtain polygonal approximation: ";
            cin >> fileNameDC;

            //Creates a new class for method and the pointer points to the new class
            a = new CollinearSuppressionMethod(fileNameDC);

            //Execute the method
            a->apply();

            cout << "Number of points of the polygonal approxmation: " << a->getNumberPointsPolygonalApproximation() << endl;
            cout << "The value of ISE is " << a->getISE() << endl;

            aP = a->getPolygonalApproximation();

            cout << "Name of file to save the polygonal approximation: ";
            cin >> fileNamePA;
         
            aP.saveDigitalCurve(fileNamePA);
         break;

         case 2:
            cout << "Digital curve to obtain polygonal approximation: ";
            cin >> fileNameDC;
            cout << "Number of points: ";
            cin >> n;

            //Creates a new class for method and the pointer points to the new class
            a = new GreedyMethod(fileNameDC, n);

            //Execute the method
            a->apply();

            cout << "Number of points of the polygonal approxmation: " << a->getNumberPointsPolygonalApproximation() << endl;
            cout << "The value of ISE is " << a->getISE() << endl;

            aP = a->getPolygonalApproximation();

            cout << "Name of file to save the polygonal approximation: ";
            cin >> fileNamePA;
         
            aP.saveDigitalCurve(fileNamePA);
         break;
       
         case 3:
            cout << "Cerrando el programa" << endl;
         break;

         default:
            cout <<"El valor introducido no es válido, introduzca un valor correcto."<<endl;
            // Se elimina el salto de línea del flujo de entrada
            std::cin.ignore();
            std::cin.ignore();           
         break;
      }
      system("clear");
   }
        
   return 0;
}
