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
// Obtain an integer random number in the range [Low,High]
int randomInt(int Low, int High)
{

}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{

}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()//no haría falta
{

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
			if ((outputFunction == 1) and (i== this->nOfLayers-1) and (j==layers[i].nOfNeurons-1)){
				layers[i].neurons[j].w = NULL;
				layers[i].neurons[j].wCopy = NULL;
				layers[i].neurons[j].deltaW = NULL;
				layers[i].neurons[j].lastDeltaW = NULL;
			}else{
				layers[i].neurons[j].w = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].wCopy = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].deltaW = new double [layers[i-1].nOfNeurons+1];
				layers[i].neurons[j].lastDeltaW = new double [layers[i-1].nOfNeurons+1];
			}		
		}
	}
	return 0;
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	freeMemory();
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	/*for(int i=1;i<this->nOfLayers;i++){
		for(int j = 0; j<this->layers[i].nOfNeurons;j++){
			if (not((outputFunction == 1) and (i== this->nOfLayers-1) and (j==layers[i].nOfNeurons-1))){
				//cout<<"i->"<<i<<"  "<<"j->"<<j<<endl;
				delete[] this->layers[i].neurons[j].w;
				delete[] this->layers[i].neurons[j].wCopy;
				delete[] this->layers[i].neurons[j].deltaW;
				delete[] this->layers[i].neurons[j].lastDeltaW;
			}			
		}
		delete[] this->layers[i].neurons;//da error al liberar cierta memoria
	}
	delete[] this->layers[0].neurons;*/
	delete[] this->layers;
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	int decimales = 1000000000;
	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
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
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	for(int j=0;j<layers[0].nOfNeurons;j++){
		layers[0].neurons[j].out = input[j];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
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
			if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
				for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
					layers[i].neurons[j].wCopy[x] = layers[i].neurons[j].w[x];
				}
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {//guardo los pesos de la copia en w
	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){
			if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
				for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
					layers[i].neurons[j].w[x] = layers[i].neurons[j].wCopy[x];
				}
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {//calculamos el resultado aplicando los calculos hacia adelante

	for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada

		double netTotal = 0.0;
		if(outputFunction == 1 && i==this->nOfLayers-1){//si es softMax y estamos en la ultima capa calculamos todos los net //calculo en net total de la ultima capa la multiplicacion de todas
			for(int j=0;j<layers[i].nOfNeurons;j++){//numero de neuronas por capa
				if (not(layers[i].neurons[j].w==NULL)){//evito sumar lo que hay en null
					double auxiliar = 0.0;
					auxiliar = layers[i].neurons[j].w[0];//añado el sesgo a la salida
					for(int x=1;x<layers[i-1].nOfNeurons+1;x++){//sumo mas 1 por el sesgo
						auxiliar += layers[i].neurons[j].w[x]*layers[i-1].neurons[x-1].out;//calculo los pesos con las salidas anteriores
					}
					netTotal += exp(auxiliar);
				}
			}
		}

		for(int j=0;j<layers[i].nOfNeurons;j++){//numero de neuronas por capa
			if (not(layers[i].neurons[j].w==NULL)){//evito sumar lo que hay en null
				layers[i].neurons[j].out = layers[i].neurons[j].w[0];//añado el sesgo a la salida
				for(int x=1;x<layers[i-1].nOfNeurons+1;x++){//sumo mas 1 por el sesgo
					layers[i].neurons[j].out += layers[i].neurons[j].w[x]*layers[i-1].neurons[x-1].out;//calculo los pesos con las salidas anteriores
				}
			}else{
				layers[i].neurons[j].out = 0.0;
			}
			if(outputFunction ==1 && i == this->nOfLayers-1){
				layers[i].neurons[j].out=exp(layers[i].neurons[j].out)/(1+(netTotal));//aplico softMax				
			}else{
				layers[i].neurons[j].out=1/(1+exp(-(layers[i].neurons[j].out)));//aplico la sigmoide
			}
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {
	double acumulador = 0.0;
	if(errorFunction == 0){
		for(int j=0;j<this->layers[nOfLayers-1].nOfNeurons;j++){//para todas las neuronas de salida
			acumulador += pow(target[j]-layers[nOfLayers-1].neurons[j].out,2);//lo que deberia de salir menos lo que nos sale al cuadrado
		}
		
	}else{
		for(int j=0;j<this->layers[nOfLayers-1].nOfNeurons;j++){//para todas las neuronas de salida
			acumulador += target[j]*log(layers[nOfLayers-1].neurons[j].out);//lo que deberia de salir menos lo que nos sale al cuadrado
		}

	}
	acumulador = acumulador/layers[nOfLayers-1].nOfNeurons;//entre todas las neuronas de salida
	return acumulador;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {
	double acumulador;

	if(outputFunction == 0){//si no es softMax

		if(errorFunction == 0){
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para 	 -2(d-out)out(1-out)para la sigmoide g()=out(1-out)
				this->layers[nOfLayers-1].neurons[j].delta = -2*(target[j]-layers[nOfLayers-1].neurons[j].out)*layers[nOfLayers-1].neurons[j].out*(1-layers[nOfLayers-1].neurons[j].out);//con el 2 disminuye el error
			}
		}else{
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada entropia
				this->layers[nOfLayers-1].neurons[j].delta = -(target[j]/layers[nOfLayers-1].neurons[j].out)*layers[nOfLayers-1].neurons[j].out*(1-layers[nOfLayers-1].neurons[j].out);//con el 2 disminuye el error
			}
		}

	}else if(outputFunction == 1){//si es softMax

		if(errorFunction == 0){
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada 
				this->layers[nOfLayers-1].neurons[j].delta = 0.0;
				for(int i=0;i<layers[nOfLayers-1].nOfNeurons;i++){//para cada neurona de salida calculamos su derivada 
					int Findicador;
					if(i==j){
						Findicador = 1;
					}else{
						Findicador = 0;
					}
					this->layers[nOfLayers-1].neurons[j].delta += (target[i]-layers[nOfLayers-1].neurons[i].out)*layers[nOfLayers-1].neurons[j].out*(Findicador-layers[nOfLayers-1].neurons[i].out);//con el 2 disminuye el error
				}
				this->layers[nOfLayers-1].neurons[j].delta=-2*this->layers[nOfLayers-1].neurons[j].delta;
			}
		}else{
			for(int j=0;j<layers[nOfLayers-1].nOfNeurons;j++){//para cada neurona de salida calculamos su derivada 
				this->layers[nOfLayers-1].neurons[j].delta = 0.0;
				for(int i=0;i<layers[nOfLayers-1].nOfNeurons;i++){//para cada neurona de salida calculamos su derivada 
					int Findicador;
					if(i==j){
						Findicador = 1;
					}else{
						Findicador = 0;
					}
					this->layers[nOfLayers-1].neurons[j].delta += (target[i]/layers[nOfLayers-1].neurons[i].out)*layers[nOfLayers-1].neurons[j].out*(Findicador-layers[nOfLayers-1].neurons[i].out);//con el 2 disminuye el error
				}
				this->layers[nOfLayers-1].neurons[j].delta=-(this->layers[nOfLayers-1].neurons[j].delta);
			}	
		}
	}
	//para las capas ocultas
	for(int i=this->nOfLayers-2;i>0;i--){//comienzo desde la capa final hasta la capa 1
		for(int j=0;j<layers[i].nOfNeurons+1;j++){//para todos los pesos despues añado 1 para no coger el sesgo
			acumulador = 0.0;		
			for(int x=0;x<layers[i+1].nOfNeurons;x++){//numero de neuronas de la capa siguiente
				if (not(outputFunction == 1 and layers[i+1].neurons[x].w==NULL)){
					acumulador += layers[i+1].neurons[x].w[j+1]*layers[i+1].neurons[x].delta;//almaceno el peso de la neurona siguiente con su respectivo delta
				}
			}		
			layers[i].neurons[j].delta = acumulador * layers[i].neurons[j].out * (1-layers[i].neurons[j].out);//calculo el delta de esta neurona con la derivada de la sigmoide con la sumatoria anterior
		}
	}
}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {//acumulo los cambios acumulados

	for(int i=1;i<nOfLayers;i++){//la capa 0 es de entrada
		for(int j=0;j<layers[i].nOfNeurons;j++){		
			if (not(outputFunction == 1 and layers[i].neurons[j].deltaW==NULL)){
				layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0] + layers[i].neurons[j].delta * 1;//calculo el sesgo en deltaw
				for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
					layers[i].neurons[j].deltaW[x+1] = layers[i].neurons[j].deltaW[x+1] + layers[i].neurons[j].delta * layers[i-1].neurons[x].out;//calculo los deltaw (salida de la neuronas de la capa anterior por el delta de la neurona actual)
				}
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
			if(online == true){
				if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
					layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - F * layers[i].neurons[j].deltaW[0] - mu * (F * layers[i].neurons[j].lastDeltaW[0]);//calculo para el sesgo
					for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
						layers[i].neurons[j].w[x+1] = layers[i].neurons[j].w[x+1] - (F * layers[i].neurons[j].deltaW[x+1]) - mu * (F * layers[i].neurons[j].lastDeltaW[x+1]);//calculo para el resto con la formula
					}
				}
			}else{
				if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
					layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - (F * layers[i].neurons[j].deltaW[0]/this->nOfTrainingPatterns) - (mu * (F * layers[i].neurons[j].lastDeltaW[0])/this->nOfTrainingPatterns);//calculo para el sesgo
					for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
						layers[i].neurons[j].w[x+1] = layers[i].neurons[j].w[x+1] - (F * layers[i].neurons[j].deltaW[x+1]/this->nOfTrainingPatterns) - (mu * (F * layers[i].neurons[j].lastDeltaW[x+1])/this->nOfTrainingPatterns);//calculo para el resto con la formula
					}
				}
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
			if (not(outputFunction == 1 and layers[i].neurons[j].w==NULL)){
				for(int x=0; x<this->layers[i-1].nOfNeurons+1;x++){
					cout<<this->layers[i].neurons[j].w[x]<<" ";
				}
				cout<<endl;
			}
		}
	}
	cout<<endl;
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::performEpoch(double* input, double* target, int errorFunction) {
	if(online == true){
		for(int i=1;i<nOfLayers;i++){//guardo los deltasW de la etapa anterior
			for(int j=0;j<layers[i].nOfNeurons;j++){
				if (not(outputFunction == 1 and layers[i].neurons[j].lastDeltaW==NULL)){
					for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
						layers[i].neurons[j].lastDeltaW[x] = layers[i].neurons[j].deltaW[x];
					}
				}
			}
		}

		for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
			for(int j=0;j<layers[i].nOfNeurons;j++){
				if (not(outputFunction == 1 and layers[i].neurons[j].deltaW==NULL)){
					for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
						layers[i].neurons[j].deltaW[x] = 0;
					}
				}
			}
		}
	}
	//aplico algoritmo
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target, errorFunction);
	accumulateChange();
	if(online == true){
		weightAdjustment();
	}
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {

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
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {

	for(int i=0; i<trainDataset->nOfPatterns; i++){//realizo el entrenamiento con todos los patrones
		if (not(online == true)){
			for(int i=1;i<nOfLayers;i++){//guardo los deltasW de la etapa anterior
				for(int j=0;j<layers[i].nOfNeurons;j++){
					if (not(outputFunction == 1 and layers[i].neurons[j].lastDeltaW==NULL)){
						for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
							layers[i].neurons[j].lastDeltaW[x] = layers[i].neurons[j].deltaW[x];
						}
					}
				}
			}

			for(int i=1;i<this->nOfLayers;i++){//la capa 0 es de entrada
				for(int j=0;j<layers[i].nOfNeurons;j++){
					if (not(outputFunction == 1 and layers[i].neurons[j].deltaW==NULL)){
						for(int x=0;x<layers[i-1].nOfNeurons+1;x++){
							layers[i].neurons[j].deltaW[x] = 0;
						}
					}
				}
			}
		}
		performEpoch(trainDataset->inputs[i], trainDataset->outputs[i], errorFunction);
		if (not(online == true)){
			weightAdjustment();
		}
	}
}

// ------------------------------
// Test the network with a dataset and return the error
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::test(Dataset* dataset, int errorFunction) {

	double error = 0.0;
	for(int i=0; i<dataset->nOfPatterns; i++){
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		error += obtainError(dataset->outputs[i], errorFunction);
	}
	if(errorFunction == 0){//diferente si es MSE o entropía cruzada
		return error/dataset->nOfPatterns;
	}else{
		return -(error/dataset->nOfPatterns);
	}
}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
	double acumulador = 0.0;
	//cout<<"tamaño"<<dataset->nOfOutputs<<endl;
	/*double ** MatrizConfusion = new double * [dataset->nOfOutputs];
	for(int i = 0; i < dataset->nOfOutputs; i++){
		MatrizConfusion[i] = new double [dataset->nOfOutputs];
	}
	for(int i=0; i<dataset->nOfOutputs; i++){
		for(int j=0; j<dataset->nOfOutputs; j++){
			MatrizConfusion[i][j]=0;
		}
	}*/


	for(int i=0; i<dataset->nOfPatterns; i++){
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		
		int maxIndEsp = 0;
		int maxIndDes = 0;
		double * VectorSalidas = new double [dataset->nOfOutputs];
		this->getOutputs(VectorSalidas);

		for(int j=1; j<dataset->nOfOutputs; j++){				
			if(VectorSalidas[maxIndEsp]<VectorSalidas[j]){
				maxIndEsp = j;
			}
			if(dataset->outputs[i][maxIndDes]<dataset->outputs[i][j]){
				maxIndDes = j;
			}
		}


		//MatrizConfusion[maxIndDes][maxIndEsp]=MatrizConfusion[maxIndDes][maxIndEsp]+1;

		//cout<<VectorSalidas[maxIndEsp]<<"--"<<dataset->outputs[i][maxIndDes]<<endl;
		//cout<<maxIndEsp<<"--"<<maxIndDes<<endl;
		if(maxIndEsp==maxIndDes){
			
			acumulador++;
		}/*else{
			cout<<"Error encontrado en -> "<<i<<endl;
		}*/
	}
	/*for(int i=0; i<dataset->nOfOutputs; i++){
		for(int j=0; j<dataset->nOfOutputs; j++){
			cout<< MatrizConfusion[i][j]<<"   ";
		}
		cout<<endl;
	}*/

	return (100*acumulador/(double)dataset->nOfPatterns);
}


// ------------------------------
// Optional Kaggle: Obtain the predicted outputs for a dataset
void MultilayerPerceptron::predict(Dataset* dataset)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * salidas = new double[numSalidas];
	
	cout << "Id,Category" << endl;
	
	for (i=0; i<dataset->nOfPatterns; i++){

		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(salidas);

		int maxIndex = 0;
		for (j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;
		
		cout << i << "," << maxIndex << endl;

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
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	nOfTrainingPatterns = trainDataset->nOfPatterns;

	Dataset * validationDataset = NULL;
	//guardo el anterior para restaurarlo posteriormente
	Dataset * trainDatasetAnterior = trainDataset;

	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;


	if(validationRatio > 0 && validationRatio < 1){
		validationDataset = new Dataset();
		Dataset *auxiliar = new Dataset();

		int* vectorAleatorios = NULL;

		//calculamos la cantidad de patrones de validacion
		int cantidadPatronesValidacion = trainDataset->nOfPatterns * validationRatio;
		vectorAleatorios = integerRandomVectorWithoutRepeating(0, trainDataset->nOfPatterns-1, cantidadPatronesValidacion);

		auxiliar->nOfPatterns = trainDataset->nOfPatterns - cantidadPatronesValidacion;
		auxiliar->nOfInputs = trainDataset->nOfInputs;
		auxiliar->nOfOutputs = trainDataset->nOfOutputs;

		validationDataset->nOfPatterns = cantidadPatronesValidacion;
		validationDataset->nOfInputs = trainDataset->nOfInputs;
		validationDataset->nOfOutputs = trainDataset->nOfOutputs;

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
		MatrizEntradasVALIDACION = new double * [validationDataset->nOfPatterns];
		for(int i = 0; i < validationDataset->nOfPatterns; i++){
			MatrizEntradasVALIDACION[i] = new double [validationDataset->nOfInputs];
		}

		MatrizSalidasVALIDACION = new double * [validationDataset->nOfPatterns];
		for(int i = 0; i < validationDataset->nOfPatterns; i++){
			MatrizSalidasVALIDACION[i] = new double [validationDataset->nOfOutputs];
		}
		validationDataset->inputs = MatrizEntradasVALIDACION;
		validationDataset->outputs = MatrizSalidasVALIDACION;

		//una vez reservada la memoria relleno los valores con trainDataset para validacion y auxiliar
		int contadorValidacion = 0;
		int contadorAuxiliar = 0;
		for(int i=0; i<trainDataset->nOfPatterns; i++){//separo validacion de entrenamiento
			if(encontrarEnVector(i, vectorAleatorios, cantidadPatronesValidacion)){
				for(int j=0; j<validationDataset->nOfInputs; j++){
					validationDataset->inputs[contadorValidacion][j] = trainDataset->inputs[i][j];
				}
				for(int j=0; j<validationDataset->nOfOutputs; j++){
					validationDataset->outputs[contadorValidacion][j] = trainDataset->outputs[i][j];
				}
				contadorValidacion++;
			}else{
				for(int j=0; j<auxiliar->nOfInputs; j++){
					auxiliar->inputs[contadorAuxiliar][j] = trainDataset->inputs[i][j];
				}
				for(int j=0; j<auxiliar->nOfOutputs; j++){
					auxiliar->outputs[contadorAuxiliar][j] = trainDataset->outputs[i][j];
				}	
				contadorAuxiliar++;
			}
		}
		trainDataset = auxiliar;
	}

	// Learning
	do {

		train(trainDataset,errorFunction);

		double trainError = test(trainDataset,errorFunction);
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

		countTrain++;

		if(validationDataset!=NULL){
			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset,errorFunction);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				cout << "We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	//libero la memoria posible
	if(validationRatio > 0 && validationRatio < 1){

		for(int i=0; i<validationDataset->nOfPatterns; i++){
				delete[] validationDataset->inputs[i];
				delete[] validationDataset->outputs[i];
		}
		delete[] validationDataset->inputs;
		delete[] validationDataset->outputs;
		delete[] validationDataset;

		for(int i=0; i<trainDataset->nOfPatterns; i++){
			delete[] trainDataset->inputs[i];
			delete[] trainDataset->outputs[i];
		}
		delete[] trainDataset->inputs;
		delete[] trainDataset->outputs;
		delete[] trainDataset;

		trainDataset = trainDatasetAnterior;
	}

	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];
		//cout<<"Patron-> "<<i<<endl;

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	*errorTest=test(testDataset,errorFunction);
	*errorTrain=minTrainError;
	*ccrTest = testClassification(testDataset);
	*ccrTrain = testClassification(trainDataset);
}

// -------------------------
// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * fileName)
{
	// Object for writing the file
	ofstream f(fileName);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
	{
		f << " " << layers[i].nOfNeurons;
	}
	f << " " << outputFunction;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(layers[i].neurons[j].w!=NULL)
				    f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// -----------------------
// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * fileName)
{
	// Object for reading a file
	ifstream f(fileName);

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
	{
		f >> npl[i];
	}
	f >> outputFunction;

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(!(outputFunction==1 && (i==(nOfLayers-1)) && (k==(layers[i].nOfNeurons-1))))
					f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
