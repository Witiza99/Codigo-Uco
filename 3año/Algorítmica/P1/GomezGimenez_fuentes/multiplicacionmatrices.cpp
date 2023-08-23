#include "Quicksort.hpp"
#include "ClaseTiempo.cpp"

void rellenarMatriz(vector<vector <double> > &v){
	
	for (int i = 0; i < (int) v.size(); i++) {
		for (int j = 0; j < (int) v[0].size(); j++) {
			v[i][j]=(double)(rand()%11)/100+0.95;//introduzco valores entre 1.05 y 0.95
		}
	}
}

double sumatorio(const vector <double> &n, int valor){
	double aux=0;
	for (int i = 0; i <(int) n.size(); i++) {
    	aux+=pow(n[i],valor);
 	}
 	return aux;
}

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){//funcion para realizar el ajuste polinomico de n³
	
	vector < vector < double > > A;
	vector < vector < double > > B;
	vector < vector < double > > X;

	double x=0,x2=0,x3=0,x4=0,x5=0,x6=0;
	//calculamos los sumatorios necesarios
	for (int i = 0; i <(int) n.size(); i++) {
		x+=n[i];
		x2+=pow(n[i],2);
		x3+=pow(n[i],3);
		x4+=pow(n[i],4);
		x5+=pow(n[i],5);
		x6+=pow(n[i],6);
	}
  	A = vector< vector< double > >(4, vector< double > (4));
	//rellenamos la matriz A(intente con un doble for rellenarlo pero ocurria algun tipo de error asi que lo introduje directamente)
	A[0][0]=n.size();
	A[0][1]=x;
	A[0][2]=x2;
	A[0][3]=x3;
	A[1][0]=x;
	A[1][1]=x2;
	A[1][2]=x3;
	A[1][3]=x4;
	A[2][0]=x2;
	A[2][1]=x3;
	A[2][2]=x4;
	A[2][3]=x5;
	A[3][0]=x3;
	A[3][1]=x4;
	A[3][2]=x5;
	A[3][3]=x6;

	double xt=0,xt2=0,xt3=0;
	for (int i = 0; i <(int) n.size(); i++) {
		xt+=n[i]*tiemposReales[i];
		xt2+=pow(n[i],2)*tiemposReales[i];
		xt3+=pow(n[i],3)*tiemposReales[i];
	}
	B = vector< vector< double > >(4, vector< double > (1));//creamos y rellenamos B
	B[0][0]=sumatorio(tiemposReales,1);
	B[1][0]=xt;
	B[2][0]=xt2;
	B[3][0]=xt3;

	X = vector< vector< double > >(4, vector< double > (4));//creamos X y llamamos a resolver Sistemas de ecuaciones para averiguar a0,a1,a2 y a3
	resolverSistemaEcuaciones(A,B,4,X);

	for(int i=0; i<4;i++){//guardo los resultados en el vector de a
		a.push_back(X[i][0]);
	}
}

void calcularTiemposEstimadosPolinomico(const vector <double> &n, vector <double> &tiemposEstimados,const vector <double> &a){
	int m=n.size();
	tiemposEstimados.resize(m);
	for (int i = 0; i < m; i++) {
    	tiemposEstimados[i]=a[0]+a[1]*n[i]+a[2]*pow(n[i],2)+a[3]*pow(n[i],3);
	}
}

double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a){
	return ((a[0]+a[1]*n+a[2]*pow(n,2)+a[3]*pow(n,3))/(3600*24*(double)1000000));//calculo la funcion y transformo el resultado a dias
}

void Parte2(){

	//Creo todas aquellas variables que me van a ser necearias
	Clock time;
	vector <vector <double> > v1, v2;
	vector <double> tiemposReales, n, tiemposEstimados, a;
	int min, max, incremento;
	double coef, aux=0.0;

	//Se piden por teclado las variables necesarias
	cout<<"Introduce el máximo número de elementos"<<endl;
	cin>>max;
	cout<<"Introduce el mínimo número de elementos"<<endl;
	cin>>min;
	cout<<"Introduce por cuanto vas a querer incrementar n"<<endl;
	cin>>incremento;
	

	/////////////////////////////////////////////////////////////////////
	//iniciamos el bucle de repeticiones y almaceno los datos en tanto de los tiempos reales como los n
	for (int i = min; i <= max; i+=incremento) {
		//reservamos espacio para los elementos de las matrices que vamos a multiplicar
		v1.resize(i);
		v2.resize(i);
		for (int j = 0; j < i; j++) {
			v1[j].resize(i);
			v2[j].resize(i);
		}
		
		//relleno las matrices
		rellenarMatriz(v1);
		rellenarMatriz(v2);
		
		time.start();//controlo el tiempo
		multiplicarMatrices(v1,v2,v1);//llamo a la funcion que realiza la multiplicacion
		if (time.isStarted())
		{
			time.stop();
		}
		tiemposReales.push_back(time.elapsed());//metemos el tiempo en el vector de tiempos
		n.push_back(i);//lo mismo con los n
		
		//vaciamos matrices
		v1.clear();
		v2.clear();
		for (int j = 0; j < i; j++) {
			v1[j].clear();
			v2[j].clear();
    	}
	}
	/////////////////////////////////////////////////////////////////////
	printf("Hola\n");
	//ajusto la funcion para obtener los a
	ajustePolinomico(n,tiemposReales,a);
	printf("Hola2\n");
	//calculo los tiempos estimados
	calcularTiemposEstimadosPolinomico(n,tiemposEstimados,a);
	printf("Hola3\n");

	//volcar tiempos y n en ficheros
	ofstream F("valoresmatrices.txt");//abro fichero
	if (!F){
	   cout << "Error al crear fichero, saliendo..." << endl;
	   exit(0);
	}
	for (unsigned int i = 0; i < n.size(); i++) {
		F<<n[i]<<" "<<tiemposReales[i]<<" "<<tiemposEstimados[i]<<std::endl;
	}
	F.close();

	cout << "Ecuación de la curva ajustada con parametros desde a0 hasta a3: ("<<a[0]<<")+("<<a[1]<<")n+("<<a[2]<<")n^2+("<<a[3]<<")n^3"<< endl;
	//calculo el coeficiente de Determinación
	coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
	cout << "El coeficiente de Determinación es: " << coef << endl;

	do{
		cout << "Introduce la N para la que quiere calcular su tiempo: " << endl;
		cin>>aux;
		if(aux!=0){
			coef=calcularTiempoEstimadoPolinomico(aux,a);//esta funcion calcula el tiempo estimado
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