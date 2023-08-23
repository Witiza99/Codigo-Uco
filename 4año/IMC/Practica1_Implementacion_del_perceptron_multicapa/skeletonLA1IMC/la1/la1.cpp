//============================================================================
// Introduction to computational models
// Name        : la1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
    // Process arguments of the command line
    bool tflag = 0, Tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0, mflag = 0, vflag = 0, dflag = 0, wflag = 0, pflag = 0;
    char *tvalue = NULL, *Tvalue = NULL, *wvalue = NULL;
    int ivalue, lvalue, hvalue;
    float evalue, mvalue, dvalue, vvalue;
    int c;

    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:T:i:l:h:e:m:v:d:w:p")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
			case 't'://nombre del fichero que contiene los datos de entrenamiento
				tflag = true;
				tvalue = optarg;
				break;
            case 'T'://nombre del fichero que contiene los datos de test
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'i'://numero de iteraciones
				iflag = true;
				ivalue = atoi(optarg);
				break;
            case 'l'://numero de capas ocultas del modelo de red neuronal
				lflag = true;
				lvalue = atoi(optarg);
				break;
            case 'h'://numero de neuronas por capa oculta
				hflag = true;
				hvalue = atoi(optarg);
				break;
            case 'e'://Indica el valor del parametro eta
				eflag = true;
				evalue = atof(optarg);
				break;
            case 'm'://Indica el valor del parametro mu
				mflag = true;
				mvalue = atof(optarg);
				break;
            case 'v'://Indica el ratio de patrones de entrenamiento a utilizar como patronesde validacion
				vflag = true;
				vvalue = atof(optarg);
				break;
            case 'd'://Indica el valor del factor de decremento (F en las diapositivas) a utilizar por cada una de las capas
				dflag = true;
				dvalue = atof(optarg);
				break;
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 't' ||optopt == 'T' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e'
                		|| optopt == 'm' || optopt == 'v' || optopt == 'd' || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "The option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown character `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }
    //para los valores por defecto
    if(Tflag != true){
		Tflag = true;
		Tvalue = tvalue;
	}

	if(iflag != true){
		iflag = true;
		ivalue = 1000;
	}

	if(lflag != true){
		lflag = true;
		lvalue = 1;
	}

	if(hflag != true){
		hflag = true;
		hvalue = 5;
	}

	if(eflag != true){
		eflag = true;
		evalue = 0.1;
	}

	if(mflag != true){
		mflag = true;
		mvalue = 0.9;
	}

	if(vflag != true){
		vflag = true;
		vvalue = 0;
	}

	if(dflag != true){
		dflag = true;
		dvalue = 1;
	}

    if (tflag){

		if (!pflag) {
			//////////////////////////////////
			// TRAINING AND EVALUATION MODE //
			//////////////////////////////////

			// Multilayer perceptron object
			MultilayerPerceptron mlp;

			//Rellenamos los valores de mlp
			mlp.eta = evalue;//tasa de aprendizaje
			mlp.mu = mvalue;//momento
			mlp.validationRatio = vvalue;//ratio de validacion
			mlp.decrementFactor = dvalue;//tasa de decremento de aprendizaje

			int iterations = ivalue; //iteraciones de nuestro programa

			//Lectura de los datos de entrenamiento y test
			Dataset * trainDataset = mlp.readData(tvalue);
			Dataset * testDataset = mlp.readData(Tvalue);

			//Creamos la estructura de nuestra red
			int layers=lvalue;
			int * VectorNumeroNeuronasEnCapa = NULL;
			VectorNumeroNeuronasEnCapa = new int [layers+2];
			VectorNumeroNeuronasEnCapa[0] = trainDataset->nOfInputs;

			for(int i = 1; i <= layers; i++){
				VectorNumeroNeuronasEnCapa[i] = hvalue;
			}

			VectorNumeroNeuronasEnCapa[layers+1] = trainDataset->nOfOutputs;
			int * topology = VectorNumeroNeuronasEnCapa;

			// Inicialiamos la red con el numero de capas mas dos (entrada y salida) y la topologia con el numero de neuronas por capa
			mlp.initialize(layers+2,topology);

			// Seed for random numbers
			int seeds[] = {1,2,3,4,5};
			double *testErrors = new double[5];
			double *trainErrors = new double[5];
			double bestTestError = 1;
			for(int i=0; i<5; i++){
				cout << "**********" << endl;
				cout << "SEED " << seeds[i] << endl;
				cout << "**********" << endl;
				srand(seeds[i]);
				mlp.runOnlineBackPropagation(trainDataset,testDataset,iterations,&(trainErrors[i]),&(testErrors[i]));//llamamos a nuestro algoritmo
				cout << "We end!! => Final test error: " << testErrors[i] << endl;

				// We save the weights every time we find a better model
				if(wflag && testErrors[i] <= bestTestError)
				{
					mlp.saveWeights(wvalue);
					bestTestError = testErrors[i];
				}
			}

			cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

			double averageTestError = 0, stdTestError = 0;
			double averageTrainError = 0, stdTrainError = 0;

			// Obtain training and test averages and standard deviations
			for(int i=0; i<5;i++){
				averageTrainError += trainErrors[i];
				averageTestError += testErrors[i];
			}

			averageTrainError = averageTrainError/5;
			averageTestError = averageTestError/5;

			for(int i=0; i<5;i++){
				stdTrainError += pow(trainErrors[i]-averageTrainError,2);
				stdTestError += pow(testErrors[i]-averageTestError,2);
			}

			stdTrainError = stdTrainError/5;
			stdTestError = stdTestError/5;

			cout << "FINAL REPORT" << endl;
			cout << "************" << endl;
			cout << "Train error (Mean +- SD): " << averageTrainError << " +- " << stdTrainError << endl;
			cout << "Test error (Mean +- SD):          " << averageTestError << " +- " << stdTestError << endl;
			return EXIT_SUCCESS;
		}
		else {

			//////////////////////////////
			// PREDICTION MODE (KAGGLE) //
			//////////////////////////////

			// Multilayer perceptron object
			MultilayerPerceptron mlp;

			// Initializing the network with the topology vector
			if(!wflag || !mlp.readWeights(wvalue))
			{
				cerr << "Error while reading weights, we can not continue" << endl;
				exit(-1);
			}

			// Reading training and test data: call to mlp.readData(...)
			Dataset *testDataset;
			testDataset = mlp.readData(Tvalue);
			if(testDataset == NULL)
			{
				cerr << "The test file is not valid, we can not continue" << endl;
				exit(-1);
			}

			mlp.predict(testDataset);

			return EXIT_SUCCESS;
		}

    }else{

    	cerr << "The training file is not valid, we can not continue" << endl;
    	exit(-1);

    }
    
}

