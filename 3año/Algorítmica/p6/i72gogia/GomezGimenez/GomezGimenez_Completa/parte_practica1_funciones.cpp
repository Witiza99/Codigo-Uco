#include "parte_practica1_funciones.hpp"

double factorial(const int n){
  if (n==0) {
    return 1;
  }else{
    return factorial(n-1)*n;
  }
}

double media(const vector<double> &v){
  double suma=0;
  for(unsigned i=0; i < v.size(); i++){
		suma+=v[i];
	}
  return suma/v.size();
}

double varianza(const vector<double> &v){
  double varianza=0;
  double v_media=media(v);

  for(unsigned i=0; i < v.size(); i++){
  	varianza+=pow(v[i]-v_media,2);
  }
  varianza/=(v.size()-1);

  return varianza;
}


void extraccion_datos(int &min, int &max, int &incremento, vector <double> &tiemposReales, vector <int> &n){
	//iniciamos el bucle de repeticiones y almaceno los datos en tanto de los tiempos reales como los n
	vector<vector<int>> soluciones;
	Clock time;
	for (int i = min; i <= max; i+=incremento) {
		cout<<"Calculando "<<i<<"reinas"<<endl;
		//limpiamos vector de soluciones
		for(int j=0;j<soluciones.size();j++){
			soluciones[j].clear();
		}
		soluciones.clear();

		time.start();//controlo el tiempo
		backtracking_reinas(i, soluciones);//llamo a la funcion de las reinas
		if (time.isStarted())
		{
			time.stop();
		}

		tiemposReales.push_back(time.elapsed());//metemos el tiempo en el vector de tiempos
		n.push_back(i);//lo mismo con los n
	}
}

void ajustefactorialN(const vector <int> &n, const vector <double> &tiemposReales, double &a0, double &a1){
	double z=0, t=0, zt=0, aux=0, cuadrado=0.0;
	vector < vector < double > > A;//matriz A
	vector < vector < double > > B;//matriz B
	vector < vector < double > > X;//Matriz X, para guardar resultados
	for(int i=0;i<n.size();i++){
		aux=n[i]*factorial(n[i]);
		z+=aux;//sumatorio de z
		cuadrado+=pow(aux,2);//sumatorio de cuadrados de z
		t+=tiemposReales[i];//sumatorio t
		zt+=tiemposReales[i]*aux;//sumatorio de la multiplicación de z y t
	}

	A = vector < vector < double > >(2, vector< double > (2));//introduzco valores para A
	A[0][0]=n.size();
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

void calcularTiemposEstimadosfactorialN(const vector <int> &n, double &a0, double &a1, vector <double> &tiemposEstimados){
	int m=n.size();
	tiemposEstimados.resize(m);
	for (int i = 0; i < m; i++) {
    	tiemposEstimados[i]=a0+(a1*n[i]*factorial(n[i]));
	}
}

void volcarTiemposFicheros(const vector <int> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
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
}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados){
	double varianza_de_reales;
	double varianza_de_estimados;

	varianza_de_reales=varianza(tiemposReales);
 	varianza_de_estimados=varianza(tiemposEstimados);

 	return varianza_de_estimados/varianza_de_reales;
}

void calculoTiempoEstimado(const double &a0, const double &a1){
	double coef;
	int N;
	do{
		cout << "Introduce la N para la que quiere calcular su tiempo: " << endl;
		cin>>N;
		if(N!=0){
			coef=calcularTiemposEstimadosfactorialN(N,a0,a1);//esta funcion calcula el tiempo estimado
     		cout << "Tardaría " << coef <<" días para el calculo de "<< N <<" reinas"<<endl;
		}
		if(N==0){
     		cout << "El numero introducido no es correcto"<<endl;
		}

	}while(N==0);
}

double calcularTiemposEstimadosfactorialN(const double &N, const double &a0, const double &a1){
	return ((a0+(a1*N*factorial(N)))/(3600*24*(double)1000000));//calculo la funcion y transformo el resultado a dias
}

void mostrar_grafica(){
	system("../nreinascurva.sh");
}