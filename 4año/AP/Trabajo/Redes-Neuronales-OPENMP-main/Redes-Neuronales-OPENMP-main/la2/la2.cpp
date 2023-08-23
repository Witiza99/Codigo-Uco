//============================================================================
// Name        : Entrenamiento para redes neuronales
// Author      : Rafael Hormigo & Antonio Gómez
// Version     : 1
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
#include <omp.h>

#include "MultilayerPerceptron.h"


using namespace imc;
using namespace std;

#define ntest 5

int main(int argc, char **argv) {
	// Process the command line
  bool tflag = 0, Tflag = 0, oflag = 0;
  char *Tvalue = NULL;
  int c;

  opterr = 0;

  char *trainFileName = NULL;

  int niter = 1000;
  int nOfLayers = 1, nOfNeurons = 5;
  double eta = 0.1, mu = 0.9, valRatio = 0.0, decrementFactor = 1;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:i:l:n:e:m:v:h:d:T:w:o")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
            case 't':
                tflag = true;
                trainFileName = optarg;
                break;
            case 'i':
                niter = atoi(optarg);
                break;
            case 'l':
                nOfLayers = atoi(optarg);
                break;
            case 'h':
                nOfNeurons = atoi(optarg);
                break;
            case 'e':
                eta = atof(optarg);
                break;
            case 'm':
                mu = atof(optarg);
                break;
            case 'v':
                valRatio = atof(optarg);
                break;
            case 'd':
                decrementFactor = atof(optarg);
                break;
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'o':
                oflag = true;
                break;
            case '?':
                if (optopt == 't' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' ||
                    optopt == 'm' || optopt == 'v' || optopt == 'd' ||
                    optopt == 'T' )
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

    if (tflag == false) {
      std::cerr << "You must provide a train file" << '\n';
      return EXIT_FAILURE;
    }

    if (Tflag == false) {
      std::cerr << "You must provide a test file" << '\n';
      return EXIT_FAILURE;
    }


        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp[ntest];

      // Read training and test data: call to mlp.readData(...)
      Dataset * trainDataset = mlp[0].readData(trainFileName);

      Dataset * testDataset = mlp[0].readData(Tvalue);
      // Initialize topology vector
      int layers = nOfLayers+2;
      int * topology = new int[layers]; // This should be corrected

      topology[0] = trainDataset->nOfInputs;
      for (int i = 1; i < layers-1; i++) {
        topology[i] = nOfNeurons;
      }
      topology[layers-1] = trainDataset->nOfOutputs;

      for (size_t n = 0; n < ntest; n++) {
        // Parameters of the mlp. For example, mlp.eta = value
        mlp[n].eta = eta;
        mlp[n].mu = mu;
        mlp[n].decrementFactor = decrementFactor;
        mlp[n].validationRatio = valRatio;
        mlp[n].online = oflag;


          // Initialize the network using the topology vector
        mlp[n].initialize(layers,topology, 4);
      }

      // Maximum number of iterations
      int maxIter = niter; // This should be completed

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[ntest];
		double *testErrors = new double[ntest];
		double *trainCCRs = new double[ntest];
		double *testCCRs = new double[ntest];
    int *count = new int[ntest];
		double bestTestError = DBL_MAX;
    double t_ini = omp_get_wtime();
    int segmento = 1;
    int i;
    omp_set_num_threads(ntest);
    #pragma omp parallel for private(i)
  		for( i=0; i<ntest; i++){
  			/*cout << "**********" << endl;
  			cout << "SEED " << seeds[i] << endl;
  			cout << "**********" << endl;*/
  			srand(seeds[i]);
  			mlp[i].runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),
        &(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),&(count[i]), i);
        std::cout << "semilla["<<i<<"]" << '\n'
  			 << "We end!! => Final test CCR: " << testCCRs[i] << '\n'
         << " We end!! => Final train CCR: " << trainCCRs[i] << endl;
  		}

    double final_time = omp_get_wtime();
    double total_time = (final_time - t_ini);

		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;
    double averageCount;

    double sumAverageTrain = 0, sumStdTrain = 0, sumAverageTest = 0, sumStdTest = 0,
    sumAverageCCRTest = 0, sumAverageCCRTrain = 0, sumStdCCRTest = 0, sumStdCCRTrain = 0, sumAverageCount = 0;

    for (int i = 0; i < ntest; i++) {
      sumAverageTest += testErrors[i];
      sumAverageTrain += trainErrors[i];
      sumAverageCCRTest += testCCRs[i];
      sumAverageCCRTrain += trainCCRs[i];
      sumAverageCount += count[i];
    }
    testAverageError = sumAverageTest/ntest;
    trainAverageError = sumAverageTrain/ntest;
    trainAverageCCR = sumAverageCCRTrain/ntest;
    testAverageCCR = sumAverageCCRTest/ntest;
    averageCount = sumAverageCount/ntest;

    for (int i = 0; i < ntest; i++) {
      sumStdTest += (testErrors[i] - testAverageError) * (testErrors[i] - testAverageError);
      sumStdTrain += (trainErrors[i] - trainAverageError) * (trainErrors[i] - trainAverageError);
      sumStdCCRTrain += (trainCCRs[i] - trainAverageCCR) * (trainCCRs[i] - trainAverageCCR);
      sumStdCCRTest += (testCCRs[i] - testAverageCCR) * (testCCRs[i] - testAverageCCR);
    }

    sumStdTest /= 4;
    sumStdTrain /= 4;
    sumStdCCRTrain /= 4;
    sumStdCCRTest /= 4;

    testStdError = sqrt(sumStdTest);
    trainStdError = sqrt(sumStdTrain);
    trainStdCCR = sqrt(sumStdCCRTrain);
    testStdCCR = sqrt(sumStdCCRTest);

        // Obtain training and test averages and standard deviations

		cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "FINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
      cout << "Average iteration number: " << averageCount << endl;
      cout << "Time elapsed: " << total_time <<'\n';

		return EXIT_SUCCESS;
}
