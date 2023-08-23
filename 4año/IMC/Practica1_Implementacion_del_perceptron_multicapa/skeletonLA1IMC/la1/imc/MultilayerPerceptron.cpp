/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Constructor: valores por defecto pero podria estas vacio ya que lo contemplo en el main
MultilayerPerceptron::MultilayerPerceptron()
{
	eta = 1;
	mu = 5;
	validationRatio = 0.1;
	decrementFactor = 0.9;

	nOfLayers = 3;
	layers = NULL;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {//reservo memoria para las capas y para todas las neuronas de las capas

	nOfLayers = nl;
	layers = new Layer [nOfLayers];

	for(int i=0;i<nOfLayers;i++){
		layers[i].nOfNeurons = npl[i];
		layers[i].neurons = new Neuron [layers[i].nOfNeurons];
	}

	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			layers[i].neurons[j].w = new double [layers[i-1].nOfNeurons+1];
			layers[i].neurons[j].wCopy = new double [layers[i-1].nOfNeurons+1];
			layers[i].neurons[j].deltaW = new double [layers[i-1].nOfNeurons+1];
			layers[i].neurons[j].lastDeltaW = new double [layers[i-1].nOfNeurons+1];
		}
	}

	return 0;
}//


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	freeMemory();
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {//libero la memoria

	/*for(int i=1;i<this->nOfLayers;i++){
		for(int j = 0; j<this->layers[i].nOfNeurons;j++){
			delete[] this->layers[i].neurons[j].deltaW;
			delete[] this->layers[i].neurons[j].lastDeltaW;
			delete[] this->layers[i].neurons[j].w;
			delete[] this->layers[i].neurons[j].wCopy;
		}
		delete[] this->layers[i].neurons;//da error al liberar cierta memoria
	}
	delete[] this->layers[0].neurons;*/
	delete[] this->layers;
}

// ------------------------------
// Feel all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {//creo pesos aleatorios
	int decimales = 1000000000;
	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				//genero los valores aleatorios
				double valor = rand()%(decimales*2+1);
				layers[i].neurons[j].w[x] = (valor-decimales)/decimales;
				//inicializo los vectores a 0
				layers[i].neurons[j].deltaW[x] = 0;
				layers[i].neurons[j].lastDeltaW[x] = 0;
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {//alimento las entradas de la primera capa
	for(int j=0;j<layers[0].nOfNeurons;j++){
		layers[0].neurons[j].out = input[j];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)//cojo la salida de nuestra red
{
	for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){
		output[j] = layers[nOfLayers-1].neurons[j].out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {//guardo los pesos en vector de pesos auxiliar
	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){//numero de neuronas por capa
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].wCopy[x] = layers[i].neurons[j].w[x];
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {//guardo los pesos de la copia en w
	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].w[x] = layers[i].neurons[j].wCopy[x];
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {//calculamos el resultado aplicando los calculos hacia adelante
	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){//numero de neuronas por capa
			layers[i].neurons[j].out = layers[i].neurons[j].w[0];//añado el sesgo a la salida
			for(int x=1;x<layers[i-1].nOfNeurons+1;x++){//sumo mas 1 por el sesgo
				layers[i].neurons[j].out += layers[i].neurons[j].w[x]*layers[i-1].neurons[x-1].out;//calculo los pesos con las salidas anteriores
			}
			layers[i].neurons[j].out=1/(1+exp(-(layers[i].neurons[j].out)));//aplico la sigmoide
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {//calculo el error medio

	double acumulador = 0.0;

	for(int j=0;j<this->layers[nOfLayers-1].nOfNeurons;j++){//para todas las neuronas de salida
		acumulador += pow(target[j]-layers[nOfLayers-1].neurons[j].out,2);//lo que deberia de salir menos lo que nos sale al cuadrado
	}
	acumulador = acumulador/layers[nOfLayers-1].nOfNeurons;//entre todas las neuronas de salida

	return acumulador;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {//calculo la retropropacion del error
	double acumulador;

	for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada -2(d-out)out(1-out)para la sigmoide g()=out(1-out)
		this->layers[nOfLayers-1].neurons[j].delta = -2*(target[j]-layers[nOfLayers-1].neurons[j].out)*layers[nOfLayers-1].neurons[j].out*(1-layers[nOfLayers-1].neurons[j].out);//con el 2 disminuye el error
	}

	for(int i=this->nOfLayers-2;i>0;i--){//comienzo desde la capa final hasta la capa 1
		for(int j=0;j<layers[i].nOfNeurons+1;j++){//para todos los pesos despues añado 1 para no coger el sesgo
			acumulador = 0.0;
			for(int x=0;x<layers[i+1].nOfNeurons;x++){//numero de neuronas de la capa siguiente
				acumulador += layers[i+1].neurons[x].w[j+1]*layers[i+1].neurons[x].delta;//almaceno el peso de la neurona siguiente con su respectivo delta
			}
			layers[i].neurons[j].delta = acumulador * layers[i].neurons[j].out * (1-layers[i].neurons[j].out);//calculo el delta de esta neurona con la derivada de la sigmoide con la sumatoria anterior
		}
	}
}


// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {//acumulo los cambios acumulados

	for(int i=1;i<nOfLayers;i++){//guardo los deltasW de la etapa anterior
		for(int j=0;j<layers[i].nOfNeurons;j++){
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].lastDeltaW[x] = layers[i].neurons[j].deltaW[x];
			}
		}
	}

	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0] + layers[i].neurons[j].delta * 1;//calculo el sesgo en deltaw
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].deltaW[x+1] = layers[i].neurons[j].deltaW[x+1] + layers[i].neurons[j].delta * layers[i-1].neurons[x].out;//calculo los deltaw (salida de la neuronas de la capa anterior por el delta de la neurona actual)
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {//ajusto los pesos
	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		double F = pow(decrementFactor,-(nOfLayers-i))*eta;//calculo F con su formula
		for(int j=0;j<layers[i].nOfNeurons;j++){
			layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - F * layers[i].neurons[j].deltaW[0] - mu * (F * layers[i].neurons[j].lastDeltaW[0]);//calculo para el sesgo
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].w[x+1] = layers[i].neurons[j].w[x+1] - F * layers[i].neurons[j].deltaW[x+1] - mu * (F * layers[i].neurons[j].lastDeltaW[x+1]);//calculo para el resto con la formula
			}
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {//imprimo la red
	for(int i = 1; i<this->nOfLayers; i++){
		cout<<"Layer "<<i<<endl;
		cout<<"------"<<endl;
		for(int j=0; j<this->layers[i].nOfNeurons;j++){
			for(int x=0; x<this->layers[i-1].nOfNeurons+1;x++){
				cout<<this->layers[i].neurons[j].w[x]<<" ";
			}
			cout<<endl;
		}
	}
	cout<<endl;
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
void MultilayerPerceptron::performEpochOnline(double* input, double* target, double N) {
	//vacio deltaW como dicta el algoritmo online
	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
				layers[i].neurons[j].deltaW[x] = 0;
			}
		}
	}//aplico algoritmo
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target);
	accumulateChange();
	weightAdjustment();
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {//leo datos y reservo memoria

	Dataset *auxiliar = new Dataset();

	double ** MatrizEntradas = NULL;
	double ** MatrizSalidas = NULL;

	char cadena[128];
	ifstream f;

	f.open(fileName);
	if (f.is_open()) {

		f >> cadena;
		auxiliar->nOfInputs = atoi(cadena);
		int entradas = auxiliar->nOfInputs;

		f >> cadena;
		auxiliar->nOfOutputs = atoi(cadena);
		int salidas = auxiliar->nOfOutputs;

		f >> cadena;
		auxiliar->nOfPatterns = atoi(cadena);
		int NumeroPatrones = auxiliar->nOfPatterns;

		MatrizEntradas = new double * [NumeroPatrones];
		for(int i = 0; i < NumeroPatrones; i++){
			MatrizEntradas[i] = new double [entradas];
		}

		MatrizSalidas = new double * [NumeroPatrones];
		for(int i = 0; i < NumeroPatrones; i++){
			MatrizSalidas[i] = new double [salidas];
		}

		for(int j = 0; j<NumeroPatrones; j++ )
		{
			for( int c=0; c<entradas+salidas; c++ ){
				if(c<entradas){
					f >> MatrizEntradas[j][c];
				}else{
					f >> MatrizSalidas[j][c-entradas];
				}
			}
		}

		auxiliar->inputs = MatrizEntradas;   /* Matrix with the inputs of the problem */
		auxiliar->outputs = MatrizSalidas;

		f.close();

	}else{
		cerr << "The file is not valid, we can not continue" << endl;
		f.close();
		exit(-1);
	}

	return auxiliar;
}

// ------------------------------
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {//realizo el entrenamiento
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){//realizo el entrenamiento con todos los patrones
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i], trainDataset->nOfPatterns);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {//realizo el test en todos los patrones y saco el error medio
	int i;
	double MSEMEDIO = 0.0;
	for(i=0; i<testDataset->nOfPatterns; i++){
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		MSEMEDIO += obtainError(testDataset->outputs[i]);
	}
	return MSEMEDIO/testDataset->nOfPatterns;
}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];
	
	cout << "Id,Predicted" << endl;
	
	for (i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << obtained[j];
		cout << endl;

	}
}

bool encontrarEnVector(int valor, int *vector, int size){//funcion donde ve si un valor esta en un vector
	for(int i=0; i<size; i++){
		if(valor == vector[i]){
			return true;
		}
	}
	return false;
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;
	int countValidacion = 0;

	// Random assignment of weights (starting point)
	//se crean pesos aleatorios
	randomWeights();

	double minTrainError = 0;
	double minValidationError = 0;
	int iterWithoutImproving = 0;
	int iterWithoutImprovingV = 0;
	int iteracionesTotales = 0;
	double testError = 0;

	Dataset * validacion = NULL;
	validacion = new Dataset();
	//guardo el anterior para restaurarlo posteriormente
	Dataset * trainDatasetAnterior = trainDataset;

	double validationError = 1;

	// Generate validation data y hacemos reserva de memoria
	if(validationRatio > 0 && validationRatio < 1){//esto usa el util
		Dataset *auxiliar = new Dataset();
		int* vectorAleatorios = NULL;

		//calculamos la cantidad de patrones de validacion
		int cantidadPatronesValidacion = trainDataset->nOfPatterns * validationRatio;
		vectorAleatorios = integerRandomVectoWithoutRepeating(0, trainDataset->nOfPatterns-1, cantidadPatronesValidacion);

		auxiliar->nOfPatterns = trainDataset->nOfPatterns - cantidadPatronesValidacion;
		auxiliar->nOfInputs = trainDataset->nOfInputs;
		auxiliar->nOfOutputs = trainDataset->nOfOutputs;

		validacion->nOfPatterns = cantidadPatronesValidacion;
		validacion->nOfInputs = trainDataset->nOfInputs;
		validacion->nOfOutputs = trainDataset->nOfOutputs;

		//reservo memoria para entradas y salidas de auxiliar y validacion
		double ** MatrizEntradasAUX = NULL;
		double ** MatrizSalidasAUX = NULL;
		MatrizEntradasAUX = new double * [auxiliar->nOfPatterns];
		for(int i = 0; i < auxiliar->nOfPatterns; i++){
			MatrizEntradasAUX[i] = new double [auxiliar->nOfInputs];
		}

		MatrizSalidasAUX = new double * [auxiliar->nOfPatterns];
		for(int i = 0; i < auxiliar->nOfPatterns; i++){
			MatrizSalidasAUX[i] = new double [auxiliar->nOfOutputs];
		}
		auxiliar->inputs = MatrizEntradasAUX;
		auxiliar->outputs = MatrizSalidasAUX;

		double ** MatrizEntradasVALIDACION = NULL;
		double ** MatrizSalidasVALIDACION = NULL;
		MatrizEntradasVALIDACION = new double * [validacion->nOfPatterns];
		for(int i = 0; i < validacion->nOfPatterns; i++){
			MatrizEntradasVALIDACION[i] = new double [validacion->nOfInputs];
		}

		MatrizSalidasVALIDACION = new double * [validacion->nOfPatterns];
		for(int i = 0; i < validacion->nOfPatterns; i++){
			MatrizSalidasVALIDACION[i] = new double [validacion->nOfOutputs];
		}
		validacion->inputs = MatrizEntradasVALIDACION;
		validacion->outputs = MatrizSalidasVALIDACION;

		//una vez reservada la memoria relleno los valores con trainDataset para validacion y auxiliar
		int contadorValidacion = 0;
		int contadorAuxiliar = 0;
		for(int i=0; i<trainDataset->nOfPatterns; i++){//separo validacion de entrenamiento
			if(encontrarEnVector(i, vectorAleatorios, cantidadPatronesValidacion)){
				validacion->inputs[contadorValidacion] = trainDataset->inputs[i];
				validacion->outputs[contadorValidacion] = trainDataset->outputs[i];
				contadorValidacion++;
			}else{
				auxiliar->inputs[contadorAuxiliar] = trainDataset->inputs[i];
				auxiliar->outputs[contadorAuxiliar] = trainDataset->outputs[i];
				contadorAuxiliar++;
			}
		}
		trainDataset = auxiliar;
	}


	// Learning
	do {
		trainOnline(trainDataset);
		double trainError = test(trainDataset);
		iteracionesTotales++;
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(iterWithoutImproving==50){
			cout << "We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}
		if(iteracionesTotales == 1000*trainDataset->nOfPatterns){
			cout << "The maximum was reached"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}

		countTrain++;

		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set

		if(validationRatio > 0 && validationRatio < 1){

			validationError = test(validacion);

			if(countValidacion==0 || validationError < minValidationError){
				minValidationError = validationError;
				copyWeights();
				iterWithoutImprovingV = 0;
			}
			else if( (validationError-minValidationError) < 0.00001)
				iterWithoutImprovingV = 0;
			else
				iterWithoutImprovingV++;

			if(iterWithoutImprovingV==50){
				cout << "We exit because the training is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
			if(iteracionesTotales == 1000*validacion->nOfPatterns){
				cout << "The maximum was reached"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
			//cambio posterior a las ejecuciones
			minValidationError = validationError;//guardo la ultima validacion, siempre que se reduzca se reseteara la condicion de parada
			countValidacion++;

		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	//libero la memoria posible
	if(validationRatio > 0 && validationRatio < 1){



		for(int i=0; i<validacion->nOfPatterns; i++){
				delete[] validacion->inputs[i];
				delete[] validacion->outputs[i];
		}
		delete[] validacion->inputs;
		delete[] validacion->outputs;
		delete[] validacion;

		/*for(int i=0; i<trainDataset->nOfPatterns; i++){
			delete[] trainDataset->inputs[i];
			delete[] trainDataset->outputs[i];
		}
		delete[] trainDataset->inputs;
		delete[] trainDataset->outputs;
		delete[] trainDataset;*/

		trainDataset = trainDatasetAnterior;
	}

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nOfPatterns; i++){
		double* prediction = new double[pDatosTest->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<pDatosTest->nOfOutputs; j++)
			cout << pDatosTest->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
