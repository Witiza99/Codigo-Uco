/*	main.cpp
 *
 * Fichero que define la función main para ejecutar experimentos sobre el Multiple Quadratic Knapsack Problem.
 * En particular, estos experimentos generan varias búsquedas con enfriamiento simulado, búsqueda tabú e iterated greedy sobre cuatro instancias.
 *
 * Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

//Definición de algunos parámetros de la experimentación
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000

#include <RPOEvaluator.h>
#include <RPOInstance.h>
#include <RPOSolGenerator.h>
#include <RPOSolution.h>
#include <RPOSimulatedAnnealing.h>
#include <RPOTabuSearch.h>
#include <RPOIteratedGreedy.h>
#include <RPOStopCondition.h>
#include <Timer.h>

#include <iostream>
using namespace std;


/**
 * Función que ejecuta el enfriamiento simulado, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runASAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, RPOInstance &instance) {

	//Inicialización
	RPOSolution initialSolution(instance);
	RPOSimulatedAnnealing sa;
	RPOStopCondition stopCond;
	RPOEvaluator::resetNumEvaluations();
	sa.initialise(0.9, 10, 0.9999, 50, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generar solución aleatoria
	RPOSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = RPOEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	sa.setSolution(&initialSolution);

	//Aplicar SA
	sa.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsSA = sa.getResults();

	for (auto aResult : resultsSA) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que ejecuta la búsqueda tabú, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runATSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, RPOInstance &instance) {

	//Inicialización
	RPOSolution initialSolution(instance);
	RPOTabuSearch ts;
	RPOStopCondition stopCond;
	RPOEvaluator::resetNumEvaluations();
	ts.initialise(&instance, ((unsigned)(instance.getNDims() / 2.5)));
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generar solución aleatoria
	RPOSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = RPOEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	ts.setSolution(&initialSolution);

	//Aplicar TS
	ts.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsTS = ts.getResults();

	for (auto aResult : resultsTS) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que ejecuta todos los experimentos para los argumentos pasados al programa principal
 * @param[out] results matriz 3D donde se almacenarán los resultados. El primer índice será para la instancia considerada. El segundo para el experimento sobre dicha instancia. El tercero para la solución generada en dicho experimento
 * @param[in] mainArgs Argumentos de la función main (argv). En los argumentos vienen, desde el índice 1, <nombre del fichero de la instancia 1> <número de mochilas> <nombre del fichero de la instancia 2> <número de mochilas>...
 * @param[in] numMainArgs Número de argumentos de la función main (argc)
 */
void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs,
		unsigned int numMainArgs) {

	//Para cada instancia del problema
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2) {

		//Leer la instancia y crear la estructuras de datos necesarias para guardar los resultados
		string path = mainArgs[iInstance];
		int numInstance= atoi(mainArgs[iInstance + 1]);
    RPOInstance instance(numInstance, path);
		vector<vector<double>*>* resultsOnThisInstance = new vector<
				vector<double>*>;
		results.push_back(resultsOnThisInstance);

		//Ejecutar el enfriamientoSimulado
		vector<double> *theseFirstResults = new vector<double>;
		vector<double> *bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		std::cerr << "1" << '\n';
		runASAExperiment(*theseFirstResults, *bestFirstResults, instance);
		std::cerr << "2" << '\n';
	}
}

/**
 * Función que libera la memoria de un vector 2D
 * @param[in] array vector 2D que se va a liberar de memoria
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int)(array.size()));

	for (int i = 0; i < numVectors; i++) {
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función que libera la memoria de un vector 3D
 * @param[in] array matriz 3D que se va a liberar de memoria
 */
template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) {

	int numArrays = (int)(array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función main que ejecuta la experimentación. Optimización mediante metaheurísticas basadas en trayectorias, búsquedas con enfriamiento simulado, búsqueda tabú e iterated greedy para las instancias.
 *
 * Finalmente se escribe en la salida estandar los resultados generados en forma de matriz. Por cada instancia se generan ocho columnas, una con los resultados
 * que va aceptando cada metaheurística en cada momento y otra con los mejores resultados hasta el momento (para cada metaheurística)
 */
int main(int argc, char **argv) {

	if (argc < 3 || (argc % 2) != 1) {
		cout << argv[0] << " (<problem instance files> <numKnapsacks>)+"
				<< endl;
		return 0;
	}

	//////////////////////////
	//Ejecución de experimentos
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector<vector<vector<double>*>*> allTheResults;
	srand(0);
	//En la matriz allTheResults se almacenarán todos los valores de fitness generados
	//Es tridimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre las ejecuciones que se han hecho sobre la misma instancia
	//El tercer índice recorre las soluciones que se han generado en la misma ejecución

	runExperiments(allTheResults, argv, argc);






	//////////////////////
	// Impresión de resultados
	//////////////////////
	vector<double> lastResults;
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
		cout << "_currentSA\t";
		cout << "_bestSA\t";

		lastResults.push_back(allTheResults.at(iInstance)->at(0)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(1)->at(0));
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false){
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){

			if (allTheResults.at(iInstance)->at(0)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(0)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(0)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(0)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(1)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(1)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}




	//////////////////////
	// Liberar memoria
	//////////////////////
	free3Darray(allTheResults);
	return 0;
}
