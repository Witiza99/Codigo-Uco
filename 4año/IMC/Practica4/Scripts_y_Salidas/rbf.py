#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 25 12:37:04 2020

IMC: lab assignment 3

@author: pagutierrez
"""

import pickle
import os
import click
import numpy as np
import pandas as pd
from sklearn.cluster import KMeans
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from scipy.io import arff
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import precision_score
from sklearn.metrics import confusion_matrix


@click.command()
@click.option('--train_file', '-t', default=None, required=False,
			  help=u'Name of the file with training data.')
@click.option('--test_file', '-T', default=None, required=True,
			  help=u'Name of the file with test data.')
@click.option('--classification', '-c', default=False, is_flag=True, show_default=True,
			  help=u'The problem considered is a classification problem.')
@click.option('--ratio_rbf', '-r', default=0.1, required=False, show_default=True,
			  help=u'Ratio of RBF neurons (as a fraction of 1) with respect to the total number of patterns.')
@click.option('--l2', '-l', default=False, is_flag=True, show_default=True, help=u'Use L2 regularization instead of L1.')
@click.option('--eta', '-e', default=0.01, required=False, show_default=True,
			  help=u'Value of the regularization parameter for logistic regression.')
@click.option('--outputs', '-o', default=1, required=False, show_default=True,
			  help=u'Number of columns that will be used as target variables (all at the end).')
@click.option('--pred', '-p', is_flag=True, default=False, show_default=True,
			  help=u'Use the prediction mode.') # KAGGLE
@click.option('--model', '-m', default="", show_default=False,
			  help=u'Directory name to save the models (or name of the file to load the model, if the prediction mode is active).') # KAGGLE
def train_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model, pred):
	""" 5 executions of RBFNN training
	
		RBF neural network based on hybrid supervised/unsupervised training.
		We run 5 executions with different seeds.
	"""
	if not pred:    

		if train_file is None:
			print("You have not specified the training file (-t)")
			return

		train_mses = np.empty(5)
		train_ccrs = np.empty(5)
		test_mses = np.empty(5)
		test_ccrs = np.empty(5)
		mediacof = np.empty(5)
	
		for s in range(1,6,1):   
			print("-----------")
			print("Seed: %d" % s)
			print("-----------")     
			np.random.seed(s)
			train_mses[s-1], test_mses[s-1], train_ccrs[s-1], test_ccrs[s-1], mediacof[s-1] = \
				train_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, \
							 model and "{}/{}.pickle".format(model, s) or "")
			print("Training MSE: %f" % train_mses[s-1])
			print("Test MSE: %f" % test_mses[s-1])
			print("Training CCR: %.2f%%" % train_ccrs[s-1])
			print("Test CCR: %.2f%%" % test_ccrs[s-1])
			print("Coeficientes: %f" % mediacof[s-1])
		
		print("******************")
		print("Summary of results")
		print("******************")
		print("Training MSE: %f +- %f" % (np.mean(train_mses), np.std(train_mses)))
		print("Test MSE: %f +- %f" % (np.mean(test_mses), np.std(test_mses)))
		print("Training CCR: %.2f%% +- %.2f%%" % (np.mean(train_ccrs), np.std(train_ccrs)))
		print("Test CCR: %.2f%% +- %.2f%%" % (np.mean(test_ccrs), np.std(test_ccrs)))
		print("Coeficientes:  %f" % np.mean(mediacof[s-1]))
			
	else:
		# KAGGLE
		if model is None:
			print("You have not specified the file with the model (-m).")
			return

		# Obtain the predictions for the test set
		predictions = predict(test_file, model)

		# Print the predictions in csv format
		print("Id,Category")
		for prediction, index in zip(predictions, range(len(predictions))):
			s = ""            
			s += str(index)
			
			if isinstance(prediction, np.ndarray):
				for output in prediction:
					s += ",{}".format(output)
			else:
				s += ",{}".format(int(prediction))
				
			print(s)

	
def pasar_a_IJ(matriz, n_etiquetas):
    auxiliar = np.zeros(shape=(matriz.shape[0], n_etiquetas))
    for i in range(matriz.shape[0]):
        auxiliar[i][matriz[i].astype(int)] = 1
    return auxiliar		


def train_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model_file=""):
	""" One execution of RBFNN training
	
		RBF neural network based on hybrid supervised/unsupervised training.
		We run 1 executions.

		Parameters
		----------
		train_file: string
			Name of the training file
		test_file: string
			Name of the test file
		classification: bool
			True if it is a classification problem
		ratio_rbf: float
			Ratio (as a fraction of 1) indicating the number of RBFs
			with respect to the total number of patterns
		l2: bool
			True if we want to use L2 regularization for logistic regression 
			False if we want to use L1 regularization for logistic regression
		eta: float
			Value of the regularization factor for logistic regression
		outputs: int
			Number of variables that will be used as outputs (all at the end
			of the matrix)
		model_file: string
			Name of the file where the model will be written

		Returns
		-------
		train_mse: float
			Mean Squared Error for training data 
			For classification, we will use the MSE of the predicted probabilities
			with respect to the target ones (1-of-J coding)
		test_mse: float 
			Mean Squared Error for test data 
			For classification, we will use the MSE of the predicted probabilities
			with respect to the target ones (1-of-J coding)
		train_ccr: float
			Training accuracy (CCR) of the model 
			For regression, we will return a 0
		test_ccr: float
			Training accuracy (CCR) of the model 
			For regression, we will return a 0
	"""
	train_inputs, train_outputs, test_inputs, test_outputs = read_data(train_file, 
																		test_file,
																		outputs, classification)
	#TODO: Obtain num_rbf from ratio_rbf
	num_rbf = int(train_inputs.shape[0]*ratio_rbf);
	print("Number of RBFs used: %d" %(num_rbf))
	kmeans, distances, centers = clustering(classification, train_inputs, 
											  train_outputs, num_rbf)

	radii = calculate_radii(centers, num_rbf)
	r_matrix = calculate_r_matrix(distances, radii)
	if not classification:
		coefficients = invert_matrix_regression(r_matrix, train_outputs)
	else:
		logreg = logreg_classification(r_matrix, train_outputs, l2, eta)

	"""
	TODO: Obtain the distances from the centroids to the test patterns
		  and obtain the R matrix for the test set
	"""
	distances = euclidean_distances(test_inputs, centers);
	r_matrix_test = calculate_r_matrix(distances, radii)

	# # # # KAGGLE # # # #
	if model_file != "":
		save_obj = {
			'classification' : classification,            
			'radii' : radii,
			'kmeans' : kmeans
		}
		if not classification:
			save_obj['coefficients'] = coefficients
		else:
			save_obj['logreg'] = logreg

		dir = os.path.dirname(model_file)
		if not os.path.isdir(dir):
			os.makedirs(dir)

		with open(model_file, 'wb') as f:
			pickle.dump(save_obj, f)
	
	# # # # # # # # # # #
	coeficientes = 0;
	if not classification:
		"""
		TODO: Obtain the predictions for training and test and calculate
			  the MSE
		"""
		train_predictions = np.dot(r_matrix,coefficients)
		test_predictions = np.dot(r_matrix_test,coefficients)

		train_mse = mean_squared_error(train_outputs, train_predictions)
		test_mse = mean_squared_error(test_outputs, test_predictions)

		if outputs > 1:
			train_ccr = 0
			test_ccr = 0
		else:
			#print(confusion_matrix(np.abs(np.around(test_outputs, decimals=0)), np.abs(np.around(test_predictions, decimals=0))))
			#train_ccr = (precision_score(np.abs(np.around(train_outputs, decimals=0)), np.abs(np.around(train_predictions, decimals=0)), average='micro'))*100
			#test_ccr = (precision_score(np.abs(np.around(test_outputs, decimals=0)), np.abs(np.around(test_predictions, decimals=0)), average='micro'))*100
			train_ccr = 0
			test_ccr = 0

	else:
		"""
		TODO: Obtain the predictions for training and test and calculate
			  the CCR. Obtain also the MSE, but comparing the obtained
			  probabilities and the target probabilities
		"""
		train_predictions = logreg.predict(r_matrix)
		test_predictions = logreg.predict(r_matrix_test)
		coeficientes = np.sum(np.abs(logreg.coef_)>10**-6)
		#y_train=np.empty(shape=(0,))#para hacer vector de etiquetas
		#for i in range(train_outputs.shape[0]):
			#y_train = np.append(y_train, np.argmax(train_outputs[i]))

		#y_test=np.empty(shape=(0,))#para hacer vector de etiquetas
		#for i in range(test_outputs.shape[0]):
			#y_test = np.append(y_test, np.argmax(test_outputs[i]))
		n_etiqueta = int(np.amax(train_outputs) + 1)
		#print(n_etiqueta)
		matrizbinaria_train_outputs = pasar_a_IJ(train_outputs, n_etiqueta)
		matrizbinaria_train_predictions = pasar_a_IJ(train_predictions, n_etiqueta)
		matrizbinaria_test_outputs = pasar_a_IJ(test_outputs, n_etiqueta)
		matrizbinaria_test_predictions = pasar_a_IJ(test_predictions, n_etiqueta)

		train_mse = mean_squared_error(matrizbinaria_train_outputs, matrizbinaria_train_predictions)
		test_mse = mean_squared_error(matrizbinaria_test_outputs, matrizbinaria_test_predictions)
		#print(test_outputs)
		#print(test_predictions)
		print("Confusion Matrix:")
		print(confusion_matrix(test_outputs, test_predictions))
		train_ccr = (precision_score(train_outputs, train_predictions, average='micro'))*100
		test_ccr = (precision_score(test_outputs, test_predictions, average='micro'))*100


	return train_mse, test_mse, train_ccr, test_ccr, coeficientes


def read_data(train_file, test_file, outputs, classification):
	""" Read the input data
		It receives the name of the input data file names (training and test)
		and returns the corresponding matrices

		Parameters
		----------
		train_file: string
			Name of the training file
		test_file: string
			Name of the test file
		outputs: int
			Number of variables to be used as outputs
			(all at the end of the matrix).
			  
		Returns
		-------
		train_inputs: array, shape (n_train_patterns,n_inputs)
			Matrix containing the inputs for the training patterns
		train_outputs: array, shape (n_train_patterns,n_outputs)
			Matrix containing the outputs for the training patterns
		test_inputs: array, shape (n_test_patterns,n_inputs)
			Matrix containing the inputs for the test patterns
		test_outputs: array, shape (n_test_patterns,n_outputs)
			Matrix containing the outputs for the test patterns
	"""

	#TODO: Complete the code of the function

	if train_file[-4:] == ".csv":

		aux_entrenamiento = np.loadtxt(train_file, delimiter=',')
		train_inputs=aux_entrenamiento[:, :-outputs]
		train_outputs=aux_entrenamiento[:, -outputs:]


		#if classification:
			#ajuste a la ultima columna por ser csv
			#ultima_columna=np.add.reduce(train_outputs, axis=1)
			#ultima_columna=ultima_columna*(-1);
			#ultima_columna=ultima_columna+1;
			#ultima_columna=ultima_columna.reshape(ultima_columna.shape[0], 1)
			#train_outputs = np.append(train_outputs, ultima_columna, axis=1)

	elif train_file[-5:] == ".arff":

		aux_entrenamiento = arff.loadarff(train_file)
		aux_entrenamiento = pd.DataFrame(data=datos[0])
		aux_entrenamiento = datos.to_numpy().astype(np.float)
		train_inputs=aux_entrenamiento[:, :-outputs]
		train_outputs=aux_entrenamiento[:, -outputs:]

		#if classification:
			#ajuste a la ultima columna por ser csv
			#ultima_columna=np.add.reduce(train_outputs, axis=1)
			#ultima_columna=ultima_columna*(-1);
			#ultima_columna=ultima_columna+1;
			#ultima_columna=ultima_columna.reshape(ultima_columna.shape[0], 1)
			#train_outputs = np.append(train_outputs, ultima_columna, axis=1)

	elif train_file[-4:] == ".dat":

		aux_entrenamiento = np.loadtxt(train_file, delimiter=',', skiprows = 1)
		train_inputs=aux_entrenamiento[:, :-outputs]
		train_outputs=aux_entrenamiento[:, -outputs:]

		#if not classification:
			#train_outputs=np.delete(train_outputs, -1, 1)

	else:

		print("Formato de fichero no valido")

	if test_file[-4:] == ".csv":

		aux_test = np.loadtxt(test_file, delimiter=',')
		test_inputs=aux_test[:, :-outputs]
		test_outputs=aux_test[:, -outputs:]

		#if classification:
			#ajuste a la ultima columna por ser csv
			#ultima_columna=np.add.reduce(test_outputs, axis=1)
			#ultima_columna=ultima_columna*(-1);
			#ultima_columna=ultima_columna+1;
			#ultima_columna=ultima_columna.reshape(ultima_columna.shape[0], 1)
			#test_outputs = np.append(test_outputs, ultima_columna, axis=1)

	elif test_file[-5:] == ".arff":

		aux_test = arff.loadarff(train_file)
		aux_test = pd.DataFrame(data=datos[0])
		aux_test = datos.to_numpy().astype(np.float)
		test_inputs=aux_test[:, :-outputs]
		test_outputs=aux_test[:, -outputs:]

		#if classification:
			#ajuste a la ultima columna por ser csv
			#ultima_columna=np.add.reduce(test_outputs, axis=1)
			#ultima_columna=ultima_columna*(-1);
			#ultima_columna=ultima_columna+1;
			#ultima_columna=ultima_columna.reshape(ultima_columna.shape[0], 1)
			#test_outputs = np.append(test_outputs, ultima_columna, axis=1)

	elif test_file[-4:] == ".dat":

		aux_test = np.loadtxt(test_file, delimiter=',')
		test_inputs=aux_test[:, :-outputs]
		test_outputs=aux_test[:, -outputs:]

		#if not classification:
			#test_outputs=np.delete(test_outputs, -1, 1)

	else:

		print("Formato de fichero no valido")

	return train_inputs, train_outputs, test_inputs, test_outputs

def init_centroids_classification(train_inputs, train_outputs, num_rbf):
	""" Initialize the centroids for the case of classification
		This method selects, approximately, num_rbf/num_clases
		patterns for each class.

		Parameters
		----------
		train_inputs: array, shape (n_patterns,n_inputs)
			Matrix with all the input variables
		train_outputs: array, shape (n_patterns,n_outputs)
			Matrix with the outputs of the dataset
		num_rbf: int
			Number of RBFs to be used in the network
			
		Returns
		-------
		centroids: array, shape (num_rbf,n_inputs)
			Matrix with all the centroids already selected
	"""
	
	#TODO: Complete the code of the function

	#y=np.empty(shape=(0,))#para hacer vector de etiquetas
	#for i in range(train_outputs.shape[0]):
		#y = np.append(y, np.argmax(train_outputs[i]))

	centroids = train_test_split(train_inputs, train_outputs, train_size=num_rbf, stratify=train_outputs[:,-1])

	return centroids[0]

def clustering(classification, train_inputs, train_outputs, num_rbf):
	""" It applies the clustering process
		A clustering process is applied to set the centers of the RBFs.
		In the case of classification, the initial centroids are set
		using the method init_centroids_classification(). 
		In the case of regression, the centroids have to be set randomly.

		Parameters
		----------
		classification: bool
			True if it is a classification problem
		train_inputs: array, shape (n_patterns,n_inputs)
			Matrix with all the input variables
		train_outputs: array, shape (n_patterns,n_outputs)
			Matrix with the outputs of the dataset
		num_rbf: int
			Number of RBFs to be used in the network
			
		Returns
		-------
		kmeans: sklearn.cluster.KMeans
			KMeans object after the clustering
		distances: array, shape (n_patterns,num_rbf)
			Matrix with the distance from each pattern to each RBF center
		centers: array, shape (num_rbf,n_inputs)
			Centers after the clustering
	"""

	#TODO: Complete the code of the function
	if classification == True:
		centroids = init_centroids_classification(train_inputs, train_outputs, num_rbf)
		kmeans = KMeans(num_rbf, n_init=1, init=centroids).fit(train_inputs)#k-means++
	else:
		kmeans = KMeans(num_rbf, init='random').fit(train_inputs)

	centers = kmeans.cluster_centers_;
	distances = euclidean_distances(train_inputs, centers);

	return kmeans, distances, centers

def calculate_radii(centers, num_rbf):
	""" It obtains the value of the radii after clustering
		This methods is used to heuristically obtain the radii of the RBFs
		based on the centers

		Parameters
		----------
		centers: array, shape (num_rbf,n_inputs)
			Centers from which obtain the radii
		num_rbf: int
			Number of RBFs to be used in the network
			
		Returns
		-------
		radii: array, shape (num_rbf,)
			Array with the radius of each RBF
	"""

	#TODO: Complete the code of the function

	distances = euclidean_distances(centers, centers);
	radii = np.mean(distances, axis=1)/2

	return radii

def calculate_r_matrix(distances, radii):
	""" It obtains the R matrix
		This method obtains the R matrix (as explained in the slides),
		which contains the activation of each RBF for each pattern, including
		a final column with ones, to simulate bias
		
		Parameters
		----------
		distances: array, shape (n_patterns,num_rbf)
			Matrix with the distance from each pattern to each RBF center
		radii: array, shape (num_rbf,)
			Array with the radius of each RBF
			
		Returns
		-------
		r_matrix: array, shape (n_patterns,num_rbf+1)
			Matrix with the activation of every RBF for every pattern. Moreover
			we include a last column with ones, which is going to act as bias
	"""

	#TODO: Complete the code of the function

	r_matrix = np.exp(-np.square(distances/radii)/2)
	ultima_columna = np.ones((r_matrix.shape[0],1))
	r_matrix = np.append(r_matrix, ultima_columna, axis=1)

	return r_matrix

def invert_matrix_regression(r_matrix, train_outputs):
	""" Inversion of the matrix for regression case
		This method obtains the pseudoinverse of the r matrix and multiplies
		it by the targets to obtain the coefficients in the case of linear
		regression
		
		Parameters
		----------
		r_matrix: array, shape (n_patterns,num_rbf+1)
			Matrix with the activation of every RBF for every pattern. Moreover
			we include a last column with ones, which is going to act as bias
		train_outputs: array, shape (n_patterns,n_outputs)
			Matrix with the outputs of the dataset
			  
		Returns
		-------
		coefficients: array, shape (n_outputs,num_rbf+1)
			For every output, values of the coefficients for each RBF and value 
			of the bias 
	"""

	#TODO: Complete the code of the function


	R=np.linalg.pinv(r_matrix,rcond=1e-5)
	coefficients = np.dot(R,train_outputs)

	return coefficients

def logreg_classification(matriz_r, train_outputs, l2, eta):
	""" Performs logistic regression training for the classification case
		It trains a logistic regression object to perform classification based
		on the R matrix (activations of the RBFs together with the bias)
		
		Parameters
		----------
		r_matrix: array, shape (n_patterns,num_rbf+1)
			Matrix with the activation of every RBF for every pattern. Moreover
			we include a last column with ones, which is going to act as bias
		train_outputs: array, shape (n_patterns,n_outputs)
			Matrix with the outputs of the dataset
		l2: bool
			True if we want to use L2 regularization for logistic regression 
			False if we want to use L1 regularization for logistic regression
		eta: float
			Value of the regularization factor for logistic regression
			  
		Returns
		-------
		logreg: sklearn.linear_model.LogisticRegression
			Scikit-learn logistic regression model already trained
	"""

	#TODO: Complete the code of the function

	#y=np.empty(shape=(0,))#para hacer vector de etiquetas
	#for i in range(train_outputs.shape[0]):
		#y = np.append(y, np.argmax(train_outputs[i]))

	if not l2:
		logreg = LogisticRegression(penalty="l1", C=1/eta, solver="liblinear").fit(matriz_r, train_outputs[:,-1])
	else:
		logreg = LogisticRegression(penalty="l2", C=1/eta, solver="liblinear").fit(matriz_r, train_outputs[:,-1])

	return logreg


def predict(test_file, model_file):
	""" Performs a prediction with RBFNN model
		It obtains the predictions of a RBFNN model for a test file, using two files, one
		with the test data and one with the model

		Parameters
		----------
		test_file: string
			Name of the test file
		model_file: string
			Name of the file containing the model data

		Returns
		-------
		test_predictions: array, shape (n_test_patterns,n_outputs)
			Predictions obtained with the model and the test file inputs
	"""
	test_df = pd.read_csv(test_file, header=None)
	test_inputs = test_df.values[:, :]
	
	with open(model_file, 'rb') as f:
		saved_data = pickle.load(f)
	
	radii = saved_data['radii']
	classification = saved_data['classification']
	kmeans = saved_data['kmeans']
	
	test_distancias = kmeans.transform(test_inputs)    
	test_r = calculate_r_matrix(test_distancias, radii)    
	
	if classification:
		logreg = saved_data['logreg']
		test_predictions = logreg.predict(test_r)
	else:
		coeficientes = saved_data['coefficients']
		test_predictions = np.dot(test_r, coeficientes)
		
	return test_predictions
	
if __name__ == "__main__":
	train_rbf_total()
