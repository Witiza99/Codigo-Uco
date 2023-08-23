/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2021
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
#include <omp.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Obtain an integer random number in the range [Low,High]
int randomInt(int Low, int High)
{
	int random;
	random = (rand()%(High+Low+1))-Low;
	return random;
}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{
	double random;
	random = Low + ((double) (rand())) /( (double) (RAND_MAX/(High-Low)));
	return random;
}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	nOfLayers = 0;
	layers = NULL;
	eta = 0;
	mu = 0;
	validationRatio = 0;
	decrementFactor = 0;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[], int nTh) {
	nOfLayers = nl;
	layers = new Layer[nl];
	nThreads = nTh;
	copys = new Layer*[nThreads];
	int i;
	for (int n = 0; n < nThreads; n++) {
		copys[n] = new Layer[nl];
		#pragma omp parallel for private(i)
		for (i = 0; i < nl; i++) {
			copys[n][i].nOfNeurons = npl[i];
			copys[n][i].neurons = new Neuron[npl[i]];
		}
		#pragma omp parallel for private(i)
		for (i = 1; i < nl - 1; i++) {
			for (int j = 0; j < copys[n][i].nOfNeurons; j++) {
				copys[n][i].neurons[j].w = new double[copys[n][i-1].nOfNeurons +1];
				copys[n][i].neurons[j].wCopy = new double[copys[n][i-1].nOfNeurons +1];
				copys[n][i].neurons[j].deltaW = new double[copys[n][i-1].nOfNeurons +1];
				copys[n][i].neurons[j].lastDeltaW = new double[copys[n][i-1].nOfNeurons +1];
			}
		}

		for (int j = 0; j < copys[n][nOfLayers-1].nOfNeurons-1; j++) {
			copys[n][nOfLayers-1].neurons[j].w = new double[copys[n][nOfLayers-2].nOfNeurons +1];
			copys[n][nOfLayers-1].neurons[j].wCopy = new double[copys[n][nOfLayers-2].nOfNeurons +1];
			copys[n][nOfLayers-1].neurons[j].deltaW = new double[copys[n][nOfLayers-2].nOfNeurons +1];
			copys[n][nOfLayers-1].neurons[j].lastDeltaW = new double[copys[n][nOfLayers-2].nOfNeurons +1];
		}
		copys[n][nOfLayers-1].neurons[copys[n][nOfLayers-1].nOfNeurons-1].w = NULL;
		copys[n][nOfLayers-1].neurons[copys[n][nOfLayers-1].nOfNeurons-1].wCopy = NULL;
		copys[n][nOfLayers-1].neurons[copys[n][nOfLayers-1].nOfNeurons-1].deltaW = NULL;
		copys[n][nOfLayers-1].neurons[copys[n][nOfLayers-1].nOfNeurons-1].lastDeltaW = NULL;
	}

	#pragma omp parallel for private(i)
	for (i = 0; i < nl; i++) {
		layers[i].nOfNeurons = npl[i];
		layers[i].neurons = new Neuron[npl[i]];
	}
	#pragma omp parallel for private(i)
	for (i = 1; i < nl - 1; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
		}
	}

	for (int j = 0; j < layers[nOfLayers-1].nOfNeurons-1; j++) {
		layers[nOfLayers-1].neurons[j].w = new double[layers[nOfLayers-2].nOfNeurons +1];
		layers[nOfLayers-1].neurons[j].wCopy = new double[layers[nOfLayers-2].nOfNeurons +1];
		layers[nOfLayers-1].neurons[j].deltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
		layers[nOfLayers-1].neurons[j].lastDeltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
	}
	layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].w = NULL;
	layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].wCopy = NULL;
	layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].deltaW = NULL;
	layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].lastDeltaW = NULL;


	return 1;
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	if (layers!=NULL) {
		freeMemory();
	}
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	for (int n = 0; n < nThreads; n++) {
		delete[] copys[n][0].neurons;
		int i;
		#pragma omp parallel for private(i)
		for (i = 1; i < nOfLayers; i++) {
			for (int j = 0; j < copys[n][i].nOfNeurons; j++) {
				if (layers[i].neurons[j].w != NULL) {
					delete[] copys[n][i].neurons[j].w;
					delete[] copys[n][i].neurons[j].wCopy;
					delete[] copys[n][i].neurons[j].deltaW;
					delete[] copys[n][i].neurons[j].lastDeltaW;
				}
			}
			delete[] copys[n][i].neurons;
		}
		delete[] copys[n];
	}
	delete copys;

	delete[] layers[0].neurons;
	int i;
	#pragma omp parallel for private(i)
	for (i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			if (layers[i].neurons[j].w != NULL) {
				delete[] layers[i].neurons[j].w;
				delete[] layers[i].neurons[j].wCopy;
				delete[] layers[i].neurons[j].deltaW;
				delete[] layers[i].neurons[j].lastDeltaW;
			}
		}
		delete[] layers[i].neurons;
	}
	delete[] layers;
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	int i;
	#pragma omp parallel for private(i)
	for (i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].w[k] = randomDouble(-1, 1);
				}
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input, int n) {
	for (int i = 0; i < copys[n][0].nOfNeurons; i++) {
		copys[n][0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputsOriginal(double* input) {
	for (int i = 0; i < layers[0].nOfNeurons; i++) {
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)
{
	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		output[i] = layers[nOfLayers-1].neurons[i].out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
				}
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k];
				}
			}
		}
	}
}
// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagateOriginal() {
	double sumNet = 0;
	int j;
	for (int i = 1; i < nOfLayers-1; i++) {
		//#pragma omp parallel for private(j)
		for (j = 0; j < layers[i].nOfNeurons; j++) {
			layers[i].neurons[j].net = 0;
			layers[i].neurons[j].net += layers[i].neurons[j].w[0];
			for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].net += layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
			}
			layers[i].neurons[j].out = 1/(1+exp(-layers[i].neurons[j].net));
		}
	}
	for (j = 0; j < layers[nOfLayers-1].nOfNeurons-1; j++) {
		layers[nOfLayers-1].neurons[j].net = 0;
		layers[nOfLayers-1].neurons[j].net += layers[nOfLayers-1].neurons[j].w[0];
		for (int k = 1; k < layers[nOfLayers-2].nOfNeurons+1; k++) {
			layers[nOfLayers-1].neurons[j].net += layers[nOfLayers-1].neurons[j].w[k] * layers[nOfLayers-2].neurons[k-1].out;
		}
		sumNet += exp(layers[nOfLayers-1].neurons[j].net);
	}
	layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].net = 0;
	for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
		layers[nOfLayers-1].neurons[j].out = exp(layers[nOfLayers-1].neurons[j].net)/(1+sumNet);
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate(int n) {
	double sumNet = 0;
	int j;
	for (int i = 1; i < nOfLayers-1; i++) {
		//#pragma omp parallel for private(j)
		for (j = 0; j < copys[n][i].nOfNeurons; j++) {
			copys[n][i].neurons[j].net = 0;
			copys[n][i].neurons[j].net += copys[n][i].neurons[j].w[0];
			for (int k = 1; k < copys[n][i-1].nOfNeurons+1; k++) {
				copys[n][i].neurons[j].net += copys[n][i].neurons[j].w[k] * copys[n][i-1].neurons[k-1].out;
			}
			copys[n][i].neurons[j].out = 1/(1+exp(-copys[n][i].neurons[j].net));
		}
	}
	for (j = 0; j < copys[n][nOfLayers-1].nOfNeurons-1; j++) {
		copys[n][nOfLayers-1].neurons[j].net = 0;
		copys[n][nOfLayers-1].neurons[j].net += copys[n][nOfLayers-1].neurons[j].w[0];
		for (int k = 1; k < copys[n][nOfLayers-2].nOfNeurons+1; k++) {
			copys[n][nOfLayers-1].neurons[j].net += copys[n][nOfLayers-1].neurons[j].w[k] * copys[n][nOfLayers-2].neurons[k-1].out;
		}
		sumNet += exp(copys[n][nOfLayers-1].neurons[j].net);
	}
	copys[n][nOfLayers-1].neurons[copys[n][nOfLayers-1].nOfNeurons-1].net = 0;
	for (int j = 0; j < copys[n][nOfLayers-1].nOfNeurons; j++) {
		copys[n][nOfLayers-1].neurons[j].out = exp(copys[n][nOfLayers-1].neurons[j].net)/(1+sumNet);
	}
}

// ------------------------------
// Obtain the output error of the out vector of the output layer wrt a target vector and return it

double MultilayerPerceptron::obtainError(double* target) {
	double error = 0;

	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		error += target[i] * log(layers[nOfLayers-1].neurons[i].out);
	}

	error /= layers[nOfLayers-1].nOfNeurons;
	return error;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--

void MultilayerPerceptron::backpropagateError(double* target, int n) {
	double sum = 0;
	int I;
	for (int j = 0; j < copys[n][nOfLayers-1].nOfNeurons; j++) {
		for (int i = 0; i < copys[n][nOfLayers-1].nOfNeurons; i++) {
			if (i == j) {
				I = 1;
			}else{
				I = 0;
			}
			sum += ((target[i] / copys[n][nOfLayers-1].neurons[i].out) * copys[n][nOfLayers-1].neurons[j].out * (I - copys[n][nOfLayers-1].neurons[i].out));
		}
		copys[n][nOfLayers-1].neurons[j].delta = -sum;
		sum = 0;
	}
	for (int i = nOfLayers-2; i > 0 ; i--) {
		double sumVec[copys[n][i].nOfNeurons];
		int j;
		//#pragma omp parallel for private(j)
		for (j = 0; j < copys[n][i].nOfNeurons; j++) {
			sumVec[j] = 0;
			for (int k = 0; k < copys[n][i+1].nOfNeurons; k++) {
				if (copys[n][i+1].neurons[k].w != NULL) {
					sumVec[j] += copys[n][i+1].neurons[k].w[j+1] * copys[n][i+1].neurons[k].delta;
				}
			}
			copys[n][i].neurons[j].delta = sumVec[j] * (copys[n][i].neurons[j].out * (1 - copys[n][i].neurons[j].out));
		}
	}
}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange(int n) {
	for (int i = 1; i < nOfLayers; i++) {
		int j;
		//#pragma omp parallel for private(j)
		for (j = 0; j < copys[n][i].nOfNeurons; j++) {
			if (copys[n][i].neurons[j].deltaW != NULL) {
				for (int k = 1; k < copys[n][i-1].nOfNeurons+1; k++) {
					copys[n][i].neurons[j].deltaW[k] +=  copys[n][i].neurons[j].delta * copys[n][i-1].neurons[k-1].out;
				}
				copys[n][i].neurons[j].deltaW[0] = copys[n][i].neurons[j].deltaW[0] + copys[n][i].neurons[j].delta;
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	double etaPerLayer = 0;
	int N = 0;
	if (online) {
		N = 1;
	}else{
		N = nOfTrainingPatterns;
	}
	for (int i = 1; i < nOfLayers; i++) {
		etaPerLayer = pow(decrementFactor, -((nOfLayers-1)-i)) * eta;
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			if (layers[i].neurons[j].w != NULL) {
				int k;
				//TODO probar con mas grandes
				#pragma omp parallel for private(k)
				for (k = 1; k < layers[i-1].nOfNeurons+1; k++) {
					layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k] - ((etaPerLayer * layers[i].neurons[j].deltaW[k])/N) - ((mu * (etaPerLayer * layers[i].neurons[j].lastDeltaW[k]))/N);
				}
				layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - ((etaPerLayer * layers[i].neurons[j].deltaW[0])/N) - ((mu * (etaPerLayer * layers[i].neurons[j].lastDeltaW[0]))/N);
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustmentOnline(int n) {
	double etaPerLayer = 0;
	int N = 0;
	if (online) {
		N = 1;
	}else{
		N = nOfTrainingPatterns;
	}
	for (int i = 1; i < nOfLayers; i++) {
		etaPerLayer = pow(decrementFactor, -((nOfLayers-1)-i)) * eta;
		for (int j = 0; j < copys[n][i].nOfNeurons; j++) {
			if (copys[n][i].neurons[j].w != NULL) {
				int k;
				//TODO probar con mas grandes
				#pragma omp parallel for private(k)
				for (k = 1; k < copys[n][i-1].nOfNeurons+1; k++) {
					copys[n][i].neurons[j].w[k] = copys[n][i].neurons[j].w[k] - ((etaPerLayer * copys[n][i].neurons[j].deltaW[k])/N) - ((mu * (etaPerLayer * copys[n][i].neurons[j].lastDeltaW[k]))/N);
				}
				copys[n][i].neurons[j].w[0] = copys[n][i].neurons[j].w[0] - ((etaPerLayer * copys[n][i].neurons[j].deltaW[0])/N) - ((mu * (etaPerLayer * copys[n][i].neurons[j].lastDeltaW[0]))/N);
			}
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
	for (int i = 1; i < nOfLayers; i++) {
		std::cout << "Layer " << i << '\n';
		std::cout << "------" << '\n';
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					std::cout << layers[i].neurons[j].w[k]<< " ";
				}
			}
			std::cout  << '\n';
		}
		std::cout  << '\n';
	}
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function

void MultilayerPerceptron::performEpoch(double* input, double* target, int n) {
	if (online) {
		for (int i = 1; i < nOfLayers; i++) {
			for (int j = 0; j < copys[n][i].nOfNeurons; j++) {
				for (int k = 0; k < copys[n][i-1].nOfNeurons+1; k++) {
					if (copys[n][i].neurons[j].deltaW != NULL) {
						copys[n][i].neurons[j].deltaW[k] = 0;
					}
				}
			}
		}
	}
	feedInputs(input, n);
	forwardPropagate(n);
	backpropagateError(target, n);
	accumulateChange(n);
	if (online) {
		weightAdjustmentOnline(n);
	}
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	Dataset *data;
	data = new Dataset;
	string aux;
	ifstream file(fileName);
	if(!file.is_open()){
		std::cout << "Couldn't open the file" << '\n';
		exit(1);
	}
	getline(file, aux, ' ');
	data->nOfInputs = atoi(aux.c_str());
	getline(file, aux, ' ');
	data->nOfOutputs = atoi(aux.c_str());
	getline(file, aux);
	data->nOfPatterns = atoi(aux.c_str());

	nOfTrainingPatterns = data->nOfPatterns;


	data->inputs = new double*[data->nOfPatterns];
	data->outputs = new double*[data->nOfPatterns];

	for (int i = 0; i < data->nOfPatterns; i++) {
		data->inputs[i] = new double[data->nOfInputs];
		data->outputs[i] = new double[data->nOfOutputs];
	}

	double n;
	int i = 0;
	for(int k = 0; k < data->nOfPatterns; k++){
		for (i = 0; i < data->nOfInputs ; i++) {
			getline(file, aux, ' ');
			n = atof(aux.c_str());
			data->inputs[k][i] = n;
		}
		for (i=0; i < data->nOfOutputs-1 ; i++) {
			getline(file, aux, ' ');
			n = atof(aux.c_str());
			data->outputs[k][i] = n;
		}
		getline(file, aux);
		n = atof(aux.c_str());
		data->outputs[k][i] = n;

	}


	file.close();
	return data;
}

void MultilayerPerceptron::sumNetworks(){
	for (int n = 0; n < nThreads; n++) {
		for (int i = 1; i < nOfLayers; i++) {
			int j;
			#pragma omp parallel for private(j)
			for (j = 0; j < layers[i].nOfNeurons; j++) {
				for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
					if (layers[i].neurons[j].deltaW != NULL) {
						layers[i].neurons[j].deltaW[k] += copys[n][i].neurons[j].deltaW[k];
					}
				}
			}
		}
	}
}

void MultilayerPerceptron::copyOriginalToCopys(){
	int n;
	#pragma omp parallel for private(n)
	for (n = 0; n < nThreads; n++) {
		for (int i = 1; i < nOfLayers; i++) {
			for (int j = 0; j < layers[i].nOfNeurons; j++) {
				copys[n][i].neurons[j].out = layers[i].neurons[j].out;
				for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
					if (layers[i].neurons[j].deltaW != NULL) {
						copys[n][i].neurons[j].deltaW[k] = layers[i].neurons[j].deltaW[k];
						copys[n][i].neurons[j].w[k] = layers[i].neurons[j].w[k];
						copys[n][i].neurons[j].wCopy[k] = layers[i].neurons[j].wCopy[k];
						copys[n][i].neurons[j].lastDeltaW[k] = layers[i].neurons[j].lastDeltaW[k];
					}
				}
			}
		}
	}
}


// ------------------------------
// Train the network for a dataset (one iteration of the external loop)

void MultilayerPerceptron::train(Dataset* trainDataset) {
	if (!online) {
		for (int n = 0; n < nThreads; n++) {
			for (int i = 1; i < nOfLayers; i++) {
				for (int j = 0; j < layers[i].nOfNeurons; j++) {
					for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
						if (layers[i].neurons[j].deltaW != NULL) {
							copys[n][i].neurons[j].deltaW[k] = 0;
							layers[i].neurons[j].deltaW[k] = 0;
						}
					}
				}
			}
		}
	}

	//idea v2 bucle de hilos y cuando todos terminan se hace el weightAdjustment asi es semioffline o semionline
	//idea para semi-online
	int j, i;
	int patronesPorHilo = trainDataset->nOfPatterns/nThreads;
	copyOriginalToCopys();
	omp_set_num_threads(nThreads);
	#pragma omp parallel for private(i,j)
	for(i=0; i<nThreads; i++){
		for (j = i*patronesPorHilo; j < (i*patronesPorHilo)+patronesPorHilo; j++) {
			performEpoch(trainDataset->inputs[j], trainDataset->outputs[j], i);
		}
	}
	sumNetworks();

	//paralelizar si offline
	/*for(int i=0; i<trainDataset->nOfPatterns; i++){
		performEpoch(trainDataset->inputs[i], trainDataset->outputs[i], sdda);
	}*/
	if (!online) {
		weightAdjustment();
	}
}

// ------------------------------
// Test the network with a dataset and return the error

double MultilayerPerceptron::test(Dataset* dataset) {
	double sumError = 0;
	for (int i = 0; i < dataset->nOfPatterns; i++) {
		feedInputsOriginal(dataset->inputs[i]);
		forwardPropagateOriginal();
		sumError += obtainError(dataset->outputs[i]);
	}
	sumError /= dataset->nOfPatterns;
	sumError = -sumError;

	return sumError;
}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
	double CCR = 0;
	int sum = 0;
	double *obtainedOutputs;
	obtainedOutputs = new double[dataset->nOfOutputs];

	for (int i = 0; i < dataset->nOfPatterns; i++) {
		feedInputsOriginal(dataset->inputs[i]);
		forwardPropagateOriginal();
		getOutputs(obtainedOutputs);
		if (maxIndexVector(dataset->outputs[i], dataset->nOfOutputs) == maxIndexVector(obtainedOutputs, dataset->nOfOutputs)) {
			sum++;
		}
	}
	delete [] obtainedOutputs;


	CCR = 100*((double)sum/dataset->nOfPatterns);

	return CCR;
}



void MultilayerPerceptron::printConfusionMatrix(Dataset* dataset){
	int	**confusionMatrix = new int*[dataset->nOfOutputs];
	double *obtainedOutputs = new double[dataset->nOfOutputs];

	for (int i = 0; i < dataset->nOfOutputs; i++) {
		confusionMatrix[i] = new int[dataset->nOfOutputs];
	}
	for (int i = 0; i < dataset->nOfOutputs; i++) {
		for (int j = 0; j < dataset->nOfOutputs; j++) {
			confusionMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < dataset->nOfPatterns; i++) {
		feedInputsOriginal(dataset->inputs[i]);
		forwardPropagateOriginal();
		getOutputs(obtainedOutputs);
		confusionMatrix[maxIndexVector(dataset->outputs[i], dataset->nOfOutputs)][maxIndexVector(obtainedOutputs, dataset->nOfOutputs)]++;
		confusionMatrix[maxIndexVector(obtainedOutputs, dataset->nOfOutputs)][maxIndexVector(dataset->outputs[i], dataset->nOfOutputs)]++;
	}

	for (int i = 0; i < dataset->nOfOutputs; i++) {
		std::cout << "class "<<i<<" | ";
	}
	std::cout << '\n';
	for (int i = 0; i < dataset->nOfOutputs; i++) {
		std::cout << "class "<<i<<" | ";
		for (int j = 0; j < dataset->nOfOutputs; j++) {
			std::cout << confusionMatrix[i][j]<<" | ";
		}
		std::cout  << '\n';
	}
}



// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest

void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int *count, int i)
{
	int countTrain = 0;
	*count = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	nOfTrainingPatterns = trainDataset->nOfPatterns;

	Dataset * validationDataset = NULL;
	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;

	Dataset *newTrainData;

	newTrainData = new Dataset;
	validationDataset = NULL;

	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		validationDataset = new Dataset;
		validationDataset->nOfInputs = trainDataset->nOfInputs;
		validationDataset->nOfOutputs = trainDataset->nOfOutputs;
		validationDataset->nOfPatterns = trainDataset->nOfPatterns*validationRatio;
		validationDataset->inputs = new double*[validationDataset->nOfPatterns];
		validationDataset->outputs = new double*[validationDataset->nOfPatterns];

		for (int i = 0; i < validationDataset->nOfPatterns; i++) {
			validationDataset->inputs[i] = new double[validationDataset->nOfInputs];
			validationDataset->outputs[i] = new double[validationDataset->nOfOutputs];
		}

		newTrainData->nOfInputs = trainDataset->nOfInputs;
		newTrainData->nOfOutputs = trainDataset->nOfOutputs;
		newTrainData->nOfPatterns = trainDataset->nOfPatterns - validationDataset->nOfPatterns;
		newTrainData->inputs = new double*[newTrainData->nOfPatterns];
		newTrainData->outputs = new double*[newTrainData->nOfPatterns];

		for (int i = 0; i < newTrainData->nOfPatterns; i++) {
			newTrainData->inputs[i] = new double[newTrainData->nOfInputs];
			newTrainData->outputs[i] = new double[newTrainData->nOfOutputs];
		}

		int *randomVector = integerRandomVectorWithoutRepeating(0,trainDataset->nOfPatterns-1,trainDataset->nOfPatterns);
		int i;


		for(i = 0; i < validationDataset->nOfPatterns; i++) {
			validationDataset->inputs[i] = trainDataset->inputs[randomVector[i]];
			validationDataset->outputs[i] = trainDataset->outputs[randomVector[i]];
		}
		for (int j = 0; j < newTrainData->nOfPatterns; j++) {
			newTrainData->inputs[j] = trainDataset->inputs[randomVector[i]];
			newTrainData->outputs[j] = trainDataset->outputs[randomVector[i]];
			i++;
		}
	}else{
		newTrainData = trainDataset;
	}

	// Learning
	do {

		train(newTrainData);

		double trainError = test(newTrainData);
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
			cout << "Hilo["<<i<<"]:We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}

		countTrain++;

		if(validationDataset!=NULL){
			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				cout << "Hilo["<<i<<"]:We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}
		(*count)++;
		//cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	if (validationDataset != NULL) {
		delete [] validationDataset;
	}

	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();

	//cout << "NETWORK WEIGHTS" << endl;
	//cout << "===============" << endl;
	//printNetwork();

	//cout << "Desired output Vs Obtained output (test)" << endl;
	//cout << "=========================================" << endl;
	/*for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}*/

	/*cout << "CONFUSION MATRIX" << endl;
	cout << "===============" << endl;
	printConfusionMatrix(testDataset);*/

	*errorTest=test(testDataset);;
	*errorTrain=minTrainError;
	*ccrTest = testClassification(testDataset);
	*ccrTrain = testClassification(trainDataset);
}
