#####################################################
# 1- Importar las bibliotecas
#####################################################

# importing the required libraries
import json
import warnings
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import pickle

from sklearn import svm
from sklearn import tree
from sklearn import ensemble
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_score
from sklearn.model_selection import StratifiedKFold


###################################################################################
#funcion para leer datos del fichero
###################################################################################
def read_data(fichero):

	input = None
	output = None
	train_inputs = None
	train_outputs = None
	test_inputs = None
	test_outputs = None 

	#guardamos los datos en un dataset de tipo string
	data = pd.read_csv(fichero)
	input = data.iloc[:,:-1].values
	output = data.iloc[:,-1].values

	#se juntan los dos dataset
	#Dataset = pd.concat([Dataset_train, Dataset_test], axis=1)

	#dividimos en 80% de datos para entreno y el resto para test
	train_inputs, test_inputs, train_outputs, test_outputs = train_test_split(input, output, test_size= 0.20, stratify=output)

	return train_inputs, train_outputs, test_inputs, test_outputs, input, output


###################################################################################
#funcion para guardar un modelo
###################################################################################
def guardar_modelo(modelo, name):

	#guardamos el modelo y el scaler
	with open(name+'.pickle', 'wb') as fw:
		pickle.dump(modelo, fw)


###################################################################################
#funcion para entrenar SVR
###################################################################################
def entrenarSVR(train_inputs, train_outputs, test_inputs, test_outputs, input, output):

	f=open("ResultadosParametrosSVR", "w"); ##archivo donde se almacenan los resultados de los parametros

	#inicializamos parametros que usamos en el entrenamiento
	vector = np.array([1e-1,1e0,1e1,1e2])
	mejor_mse = 999999
	mejor_C = 999999
	mejor_Gamma = 999999

	skf= StratifiedKFold(n_splits=5)
	mejorconf=0
	for C in vector:#entrenamos probando distintas c y gammas
		for Gamma in vector:
			contador = 0
			media = 0
			print("C=%f y Gamma=%f" % (C, Gamma))

			for train_index, test_index in skf.split(train_inputs, test_inputs):
				entrada_train, entrada_test = input[train_index], input[test_index]
				salida_train, salida_test = output[train_index], output[test_index]

				# Entrenamos el modelo
				modelo = svm.SVC(kernel='rbf',C=C, gamma=Gamma)
				modelo.fit(entrada_train, salida_train)
				y_pred=modelo.predict(entrada_test)
				test_ccr = (precision_score(salida_test, y_pred, average='micro'))*100
				contador = contador + test_ccr
			media = contador/5

			f.write("CCR Final con C=%f y G=%f: \t%f\n" % (C, Gamma, media))#lo vamos almacenando en un fichero

			if media > mejorconf:#se va guardando la mejor combinacion de parametros
				mejorconf=media
				mejor_C = C
				mejor_Gamma = Gamma

	#Se realiza la validación del modelo
	modelo = svm.SVC(kernel='rbf',C=mejor_C, gamma=mejor_Gamma)
	modelo.fit(train_inputs, test_inputs)
	y_pred = modelo.predict(train_outputs)
	test_ccr = (precision_score(test_outputs, y_pred, average='micro'))*100

	#se almacena el modelo y el scaler
	guardar_modelo(modelo,"SVR")

	f.write("Los mejores parametros son C:"+ str(mejor_C) +" y Gamma:"+ str(mejor_Gamma) +" con un CCR de "+ str(test_ccr))
	f.close()

	print("******************")
	print("Los mejores parametros son C:"+ str(mejor_C) +" y Gamma:"+ str(mejor_Gamma) +" con un CCR de "+ str(test_ccr))
	print("******************")

	return test_ccr


###################################################################################
#funcion que entrena con el modelo ArbolDecision
###################################################################################
def entrenarArbolDecision(train_inputs, train_outputs, test_inputs, test_outputs, input, output):

	f=open("ResultadosParametrosArbolDecision", "w"); ##archivo donde se almacenan los resultados de los parametros

	#inicializamos parametros que usamos en el entrenamiento
	v_splitter = {"best","random"}
	v_min_samples_split = {0.1, 0.3, 0.5, 0.6, 0.8}
	v_min_samples_leaf = {0.1, 0.3, 0.5}
	mejor_mse = 99999
	mejor_splitter = None
	mejor_min_samples_split = 999999
	mejor_min_samples_leaf = 999999

	skf= StratifiedKFold(n_splits=5)
	mejorconf=0
	#entrenamos probando distintas combinaciones
	for splitter in v_splitter:
		for min_samples_split in v_min_samples_split:
			for min_samples_leaf in v_min_samples_leaf:
				contador = 0
				media = 0
				print("splitter=%s, min_samples_split=%f, min_samples_leaf=%f\n" % (splitter, min_samples_split, min_samples_leaf))

				for train_index, test_index in skf.split(train_inputs, test_inputs):
					entrada_train, entrada_test = input[train_index], input[test_index]
					salida_train, salida_test = output[train_index], output[test_index]

					#Entrenamos el modelo
					modelo = tree.DecisionTreeClassifier(splitter=splitter, min_samples_split=min_samples_split, min_samples_leaf=min_samples_leaf)
					modelo.fit(entrada_train, salida_train)
					y_pred=modelo.predict(entrada_test)
					test_ccr = (precision_score(salida_test, y_pred, average='micro'))*100
					contador = contador + test_ccr
				media = contador/5

				f.write("CCR Final con splitter=%s, min_samples_split=%f y min_samples_leaf=%f: \t%f\n" % (splitter, min_samples_split, min_samples_leaf, media))

				if media > mejorconf:#se va guardando la mejor combinacion de parametros
					mejorconf=media
					mejor_splitter = splitter
					mejor_min_samples_split = min_samples_split
					mejor_min_samples_leaf = min_samples_leaf

		
	#Se realiza la validación del modelo
	modelo = tree.DecisionTreeClassifier(splitter=mejor_splitter, min_samples_split=mejor_min_samples_split, min_samples_leaf=mejor_min_samples_leaf)
	modelo.fit(train_inputs, test_inputs)
	y_pred = modelo.predict(train_outputs)
	test_ccr = (precision_score(test_outputs, y_pred, average='micro'))*100

	#se almacena el modelo
	guardar_modelo(modelo,"ArbolDecision")

	f.write("Los mejores parametros para el arbol de decision es splitter->"+ str(mejor_splitter)+", min_samples_split->"+ str(mejor_min_samples_split)+", min_samples_leaf->"+ str(mejor_min_samples_leaf)+ " con un CCR de:"+ str(test_ccr))
	f.close()

	print("******************")
	print("Los mejores parametros para el arbol de decision es splitter->"+ str(mejor_splitter)+", min_samples_split->"+ str(mejor_min_samples_split)+", min_samples_leaf->"+ str(mejor_min_samples_leaf)+ " con un CCR de:"+ str(test_ccr))
	print("******************")

	return test_ccr


###################################################################################
#funcion que entrena con el modelo RandomForest
###################################################################################
def entrenarRandomForest(train_inputs, train_outputs, test_inputs, test_outputs, input, output):

	f=open("ResultadosParametrosRandomForest", "w"); ##archivo donde se almacenan los resultados de los parametros

	#inicializamos parametros que usamos en el entrenamiento
	v_n_estimators = {100,300}
	v_max_features = {0.01, 0.1,0.3}
	v_min_samples_split = {2, 50, 100}
	v_min_samples_leaf = {2, 50, 100}
	mejor_mse = 99999
	mejor_n_estimators = 999999
	mejor_min_samples_split = 999999
	mejor_min_samples_leaf = 999999
	mejor_max_features = 999999

	skf= StratifiedKFold(n_splits=5)
	mejorconf=0
	#entrenamos probando distintas combinaciones
	for n_estimators in v_n_estimators:
		for max_features in v_max_features:
			for min_samples_split in v_min_samples_split:
				for min_samples_leaf in v_min_samples_leaf:
					contador = 0
					media = 0
					print("n_estimators=%d, max_features=%f, min_samples_split=%f, min_samples_leaf=%f \n" % (n_estimators, max_features, min_samples_split, min_samples_leaf))

					for train_index, test_index in skf.split(train_inputs, test_inputs):
						entrada_train, entrada_test = input[train_index], input[test_index]
						salida_train, salida_test = output[train_index], output[test_index]
						
						#Entrenamos el modelo
						modelo = ensemble.RandomForestClassifier(min_weight_fraction_leaf=0.2, max_samples= 0.5,n_estimators=n_estimators, max_features=max_features, min_samples_split=min_samples_split, min_samples_leaf=min_samples_leaf, bootstrap=True, n_jobs=4)
						modelo.fit(entrada_train, salida_train)
						y_pred=modelo.predict(entrada_test)
						test_ccr = (precision_score(salida_test, y_pred, average='micro'))*100
						contador = contador + test_ccr
					media = contador/5

					f.write("CCR Final con n_estimators=%d, v_max_features=%f, min_samples_split=%f, min_samples_leaf=%f= \t%f\n" % (n_estimators, max_features, min_samples_split, min_samples_leaf, media))

					if media > mejorconf:#se va guardando la mejor combinacion de parametros
						mejorconf=media
						mejor_n_estimators = n_estimators
						mejor_min_samples_split = min_samples_split
						mejor_min_samples_leaf = min_samples_leaf
						mejor_max_features = max_features


	#Se realiza la validación del modelo
	modelo = ensemble.RandomForestClassifier(min_weight_fraction_leaf=0.2, max_samples= 0.5, n_estimators=mejor_n_estimators, max_features=mejor_max_features, min_samples_split=mejor_min_samples_split, min_samples_leaf=mejor_min_samples_leaf, bootstrap=True, n_jobs=4)
	modelo.fit(train_inputs, test_inputs)
	y_pred = modelo.predict(train_outputs)
	test_ccr = (precision_score(test_outputs, y_pred, average='micro'))*100

	#se almacena el modelo
	guardar_modelo(modelo,"RandomForest")

	f.write("Los mejores parametros para el random forest es n_estimators->"+ str(mejor_n_estimators) + "max_features->"+ str(mejor_max_features) + ", min_samples_split->"+ str(mejor_min_samples_split) +", min_samples_leaf->"+ str(mejor_min_samples_leaf) + " con un CCR de:"+ str(test_ccr))
	f.close()

	print("******************")
	print("Los mejores parametros para el random forest es n_estimators->"+ str(mejor_n_estimators) + "max_features->"+ str(mejor_max_features) + ", min_samples_split->"+ str(mejor_min_samples_split) +", min_samples_leaf->"+ str(mejor_min_samples_leaf) + " con un CCR de:"+ str(test_ccr))
	print("******************")

	return test_ccr



###################################################################################
#funcion principal
###################################################################################

#nombre de los ficheros
fichero = "Dataset.csv"

#llamamos a funcion read_data para extraer los datos del fichero csv a un formato con el que podamos trabajar
train_inputs, train_outputs, test_inputs, test_outputs, input, output= read_data(fichero,)
if train_inputs is None or train_outputs is None or test_inputs is None or test_outputs is None or input is None or output is None:
	print("Error con el fichero")
	exit()

#No se aplica standarscaler ya que los datos son 0 y 1, siendo datos muy sencillos

#creamos una lista con el nombre de todos los modelos
NombreModelo = ["SVM", "ArbolDecision", "RandomForest"]
listaCCR = np.zeros(shape=(3), dtype=float)

#entrenamos con los distintos modelo para ver cual es el mejor
print("Entrenando " + NombreModelo[0])
listaCCR[0] = entrenarSVR(train_inputs, test_inputs, train_outputs, test_outputs, input, output)
print("Entrenando " + NombreModelo[1])
listaCCR[1] = entrenarArbolDecision(train_inputs, test_inputs, train_outputs, test_outputs, input, output)
print("Entrenando " + NombreModelo[2])
listaCCR[2] = entrenarRandomForest(train_inputs, test_inputs, train_outputs, test_outputs, input, output)

mejorModelo = -1
mejorCCR = 0

for iterador in range(len(listaCCR)):#comprobamos cual genero un CCR mayor
	if listaCCR[iterador] > mejorCCR:
		mejorCCR = listaCCR[iterador]
		mejorModelo = iterador

print("El mejor modelo es " + NombreModelo[mejorModelo] + " con un CCR de: " + str(mejorCCR))
