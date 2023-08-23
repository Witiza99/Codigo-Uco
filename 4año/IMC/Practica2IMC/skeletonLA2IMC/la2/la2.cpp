//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
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
#include <float.h> // For DBL_MAX

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	// Process the command line
	bool Tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0, mflag = 0, vflag = 0, dflag = 0, wflag = 0, pflag = 0, sflag = 0, oflag = 0, fflag = 0;
	char *tvalue = NULL, *Tvalue = NULL, *wvalue = NULL;
	int ivalue, lvalue, hvalue, fvalue;
	float evalue, mvalue, dvalue, vvalue;
	int c;

    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:T:i:l:h:e:m:v:d:w:osf:p")) != -1)
    {

        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
        	case 't'://nombre del fichero que contiene los datos de entrenamiento
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
			case 's':
				sflag = true;
				break;
			case 'o':
				oflag = true;
				break;
			case 'f':
				fflag = true;
				fvalue = atoi(optarg);
				break;
            case '?':
                if (optopt == 't' ||optopt == 'T' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e'
                		|| optopt == 'm' || optopt == 'v' || optopt == 'd' || optopt == 'w' || optopt == 'p' || optopt == 's' || optopt == 'o' || optopt == 'f')
                    fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Caracter de opción desconocido `\\x%x'.\n",
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
		evalue = 0.7;
	}

	if(mflag != true){
		mflag = true;
		mvalue = 1;
	}

	if(vflag != true){
		vflag = true;
		vvalue = 0;
	}

	if(fflag != true){
		fflag = true;
		fvalue = 0;
	}

	if(dflag != true){
		dflag = true;
		dvalue = 1;
	}

    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value
    	mlp.eta = evalue;//tasa de aprendizaje
		mlp.mu = mvalue;//momento
		mlp.validationRatio = vvalue;//ratio de validacion
		mlp.decrementFactor = dvalue;//tasa de decremento de aprendizaje
		mlp.outputFunction = sflag;//tipo de funcione de salida softMax o sigmoide
		mlp.online = oflag;//para ver si es online o offline

    	// Type of error considered
    	int error=fvalue; //Tipo de error a considerar MSE o entropia cruzada
		if(fvalue<0 or fvalue>1){
			cout<<"No es correcto este tipo de error, asignando MSE"<<endl;
			error=0;
		}

    	// Maximum number of iterations
    	int maxIter=ivalue; //Numero de iteraciones

        // Read training and test data: call to mlp.readData(...)
    	Dataset * trainDataset = mlp.readData(tvalue);
    	Dataset * testDataset = mlp.readData(Tvalue);

        // Initialize topology vector
    	int layers=lvalue;
        int *topology = new int[layers+2];
        topology[0] = trainDataset->nOfInputs;
        for(int i=1; i<(layers+2-1); i++)
            topology[i] = hvalue;
        topology[layers+2-1] = trainDataset->nOfOutputs;
        mlp.initialize(layers+2,topology);

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[5];
		double *testErrors = new double[5];
		double *trainCCRs = new double[5];
		double *testCCRs = new double[5];
		double bestTestError = DBL_MAX;
		for(int i=0; i<5; i++){
			cout << "**********" << endl;
			cout << "SEED " << seeds[i] << endl;
			cout << "**********" << endl;
			srand(seeds[i]);
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error);
			cout << "We end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError)
			{
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}
		}


		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;

        // Obtain training and test averages and standard deviations
		for(int i=0; i<5;i++){
			trainAverageError += trainErrors[i];
			testAverageError += testErrors[i];
			trainAverageCCR += trainCCRs[i];
			testAverageCCR += testCCRs[i];
		}

		trainAverageError = trainAverageError/5;
		testAverageError = testAverageError/5;
		trainAverageCCR = trainAverageCCR/5;
		testAverageCCR = testAverageCCR/5;

		for(int i=0; i<5;i++){
			trainStdError += pow(trainErrors[i]-trainAverageError,2);
			testStdError += pow(testErrors[i]-testAverageError,2);
			trainStdCCR += pow(trainCCRs[i]-trainAverageCCR,2);
			testStdCCR += pow(testCCRs[i]-testAverageCCR,2);
		}
//arreglar
		trainStdError = sqrt(trainStdError/5);
		testStdError = sqrt(testStdError/5);
		trainStdCCR = sqrt(trainStdCCR/5);
		testStdCCR = sqrt(testStdCCR/5);

		cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "FINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
		return EXIT_SUCCESS;
    } else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////

        // You do not have to modify anything from here.
        
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
}

