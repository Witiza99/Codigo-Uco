#include "Quicksort.hpp"
#include "ClaseTiempo.cpp"

void rellenarVector(vector <float> &v){
	
	v.clear();
	for(unsigned i=0; i<v.capacity();i++){
		v.push_back(rand()%10000);
	}
}

void estaOrdenado(const vector <float> &v){

	for(unsigned i = 1; i<v.size();i++){
		assert(v[i-1]<=v[i]);
	}
}

 
// Función recursiva quicksort para hacer el ordenamiento
void quicksort(int izq, int der, vector <float> &v ){
int i, j, x , aux;
i = izq;
j = der;
x = v[ (izq + der) /2 ];
    while(i<=j){
        while( (v[i] < x) )
        {
            i++;
        }

        while( (x < v[j]))
        {
            j--;
        }

        if( i <= j )
        {
            aux = v[i];
            v[i]=v[j];
            v[j] = aux;
            i++;
            j--;
        }

    }

    if( izq < j )
        quicksort(izq, j,v );
    if( i < der )
        quicksort(i, der,v );
}

void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1){

	int m=n.size();
	double z=0, t=0, zt=0, aux=0, cuadrado=0.0;
	vector < vector < double > > A;//matriz A
	vector < vector < double > > B;//matriz B
	vector < vector < double > > X;//Matriz X, para guardar resultados
	for(int i=0;i<m;i++){
		aux=n[i]*log10(n[i]);
		z+=aux;//sumatorio de z
		cuadrado+=pow(aux,2);//sumatorio de cuadrados de z
		t+=tiemposReales[i];//sumatorio t
		zt+=tiemposReales[i]*aux;//sumatorio de la multiplicación de z y t
	}

	A = vector < vector < double > >(2, vector< double > (2));//introduzco valores para A
	A[0][0]=m;
	A[0][1]=z;
	A[1][0]=z;
	A[1][1]=cuadrado;

	B = vector < vector < double > >(2, vector< double > (1));//introduzco valores para B
	B[0][0]=t;
	B[1][0]=zt;

	X = vector < vector < double > >(2, vector< double > (2));//introduzco tamaño de X
	resolverSistemaEcuaciones(A,B,2,X);//funcion que resuelve el sistema de ecuaciones
	a0=X[0][0];
	a1=X[1][0];
}

void calcularTiemposEstimadosNlogN(const vector <double> &n, const double &a0, const double &a1, vector <double> &tiemposEstimados){
	int m=n.size();
	tiemposEstimados.resize(m);
	for (int i = 0; i < m; i++) {
    	tiemposEstimados[i]=a0+(a1*n[i]*log10(n[i]));
	}
}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados){
	double suma1=0.0, suma2=0.0, media1=0.0, media2=0.0;
	for(unsigned i=0; i < tiemposReales.size(); i++){
		suma1+=tiemposReales[i];
		suma2+=tiemposEstimados[i];
	}
	media1=suma1/tiemposReales.size();
	media2=suma2/tiemposEstimados.size();
	suma1=0.0;
	suma2=0.0;
	for(unsigned i=0; i < tiemposReales.size(); i++){
		suma1+=pow(tiemposReales[i]-media1,2);
		suma2+=pow(tiemposEstimados[i]-media2,2);
	}
	suma1/=(tiemposReales.size()-1);
	suma2/=(tiemposEstimados.size()-1);

	return suma2/suma1;
}

double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1){
	return ((a0+a1*n*log10(n))/(3600*24*(double)1000000));//calculo la funcion y transformo el resultado a dias
}

void Parte1(){

	//Creo todas aquellas variables que me van a ser necearias
	Clock time;
	vector <float> v;
	vector <double> tiemposReales, n, tiemposEstimados;
	int min, max, incremento, m;
	double media=0.0,a0,a1,coef, aux=0.0;

	//Se piden por teclado las variables necesarias
	cout<<"Introduce el máximo número de elementos"<<endl;
	cin>>max;
	cout<<"Introduce el mínimo número de elementos"<<endl;
	cin>>min;
	cout<<"Introduce por cuanto vas a querer incrementar n"<<endl;
	cin>>incremento;
	

	//se dimensiona el vector
	v.resize(max);
	m=max;

	//Comprobamos que la función quicksort ordena bien el vector
	rellenarVector(v);
	quicksort(0,m-1,v);
	estaOrdenado(v);

	//iniciamos el bucle de repeticiones y almaceno los datos en tanto de los tiempos reales como los n
	rellenarVector(v);
	for (int i = min; i <= max; i+=incremento) {
		v.resize(i);
		m=v.size();
		media=0.0;
		for (int j = 0; j < REP; j++) {
			rellenarVector(v);
			time.start();
			quicksort(0,m-1,v);
			if (time.isStarted())
			{
				time.stop();
			}
			media=media+time.elapsed();
		}
		media=media/(double)REP;
		tiemposReales.push_back(media);
		n.push_back(i);
		v.clear();
	}
  /////////////////////////////////////////////////////////////////////

	//ajusto la funcion para obtener a0 y a1
	ajusteNlogN(n,tiemposReales,a0,a1);
	//calculo los tiempos estimados
	calcularTiemposEstimadosNlogN(n,a0,a1,tiemposEstimados);

	//volcar tiempos y n en ficheros
	ofstream F("valores.txt");//abro fichero
	if (!F){
	   cout << "Error al crear fichero, saliendo..." << endl;
	   exit(0);
	}
	for (unsigned int i = 0; i < n.size(); i++) {
		F<<n[i]<<" "<<tiemposReales[i]<<" "<<tiemposEstimados[i]<<std::endl;
	}
	F.close();

	cout << "Ecuación de la curva ajustada con parametros a0 y a1: "<<a0<<"+"<<a1<<"*nlogn"<< endl;
	//calculo el coeficiente de Determinación
	coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
	cout << "El coeficiente de Determinación es: " << coef << endl;

	do{
		cout << "Introduce la N para la que quiere calcular su tiempo: " << endl;
		cin>>aux;
		if(aux!=0){
			coef=calcularTiempoEstimadoNlogN(aux,a0,a1);//esta funcion calcula el tiempo estimado
     		cout << "Tardaría " << coef <<" días para ordenar un vector de "<< aux <<" elementos"<< '\n';
		}
		if(aux==0){
     		cout << "El numero introducido no es correcto"<< '\n';
		}

	}while(aux==0);

	// Se elimina el salto de línea del flujo de entrada
    cin.ignore();
    cin.ignore();
}