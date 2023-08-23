import click
import numpy as np
import pandas as pd
from scipy.io import arff
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import StandardScaler
from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.metrics import precision_score
from sklearn.model_selection import KFold
from sklearn.model_selection import GridSearchCV
from sklearn.neighbors import KNeighborsClassifier
import sys

@click.command()
@click.option('--train_file', '-d', default=None, required=True,
			help=u'Name of the file with training data.')
@click.option('--outputs', '-o', default=1, required=False, 
			show_default=True, help=u'Number of columns that will be used as target variables (all at the end).')

def pruebas(train_file, outputs):
	Dataset = read_data(train_file, outputs)

	if Dataset is None:
		print("Error con el fichero")
		return	

	f=open("Errores.txt", "a");
	f2=open("ErroresCCRTotales.txt", "a");

	#tree
	X = Dataset.iloc[:,:-outputs].values
	y = Dataset.iloc[:,-outputs].values

	le = preprocessing.LabelEncoder()
	y = le.fit_transform(y.reshape((y.shape[0],)))

	X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size= 0.30, random_state=1);

	skf= KFold(n_splits=10)
	contador = 0
	mediatree = 0
	f2.write(train_file + "\n")
	for train_index, test_index in skf.split(X_train, Y_train):
		X_trainV2, X_testV2 = X[train_index], X[test_index]
		y_trainV2, y_testV2 = y[train_index], y[test_index]

		# Create Decision Tree classifer object
		clf=DecisionTreeClassifier()
		# Train Decision Tree Classifer
		clf=clf.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=clf.predict(X_testV2)
		test_ccr = (precision_score(y_testV2, y_pred, average='micro'))*100
		f2.write(str(test_ccr) + ", ")
		contador = contador + test_ccr
	mediatree = contador/10
	print("Tree_CCR->", mediatree)
	f2.write("\n")

	#Cs = np.logspace(-2,1, num=4, base=10)
	Cs = np.logspace(1,1, num=1, base=10)
	svm_model=svm.SVC(kernel='linear')
	optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs), n_jobs=-1, cv=10, return_train_score=True)
	optimo.fit(X_train, Y_train)
	test_predictions = optimo.predict(X_test)
	test_ccr_svm = (precision_score(Y_test, test_predictions, average='micro'))*100
	print("SVM_CCR->", test_ccr_svm)
	
	vector_aux = np.empty((0,))
	for x in range(skf.n_splits):
		varaux = 'split' + str(x) + '_test_score'
		vector_aux = np.append(vector_aux, optimo.cv_results_[varaux])

	vector_aux=vector_aux*100
	for x in vector_aux:
		f2.write(str(x)+ " ")
	f2.write("\n")

	#neighbors = range(1,5)
	neighbors = [1]
	neigh = KNeighborsClassifier()
	optimo = GridSearchCV(estimator=neigh, param_grid=dict(n_neighbors=neighbors), n_jobs=-1, cv=10, return_train_score=True)
	optimo.fit(X_train, Y_train)
	test_predictions = optimo.predict(X_test)
	test_ccr_vecinos = (precision_score(Y_test, test_predictions, average='micro'))*100
	print("neighbors_CCR->", test_ccr_vecinos)

	vector_aux = np.empty((0,))
	for x in range(skf.n_splits):
		varaux = 'split' + str(x) + '_test_score'
		vector_aux = np.append(vector_aux, optimo.cv_results_[varaux])

	vector_aux=vector_aux*100
	for x in vector_aux:
		f2.write(str(x)+ " ")
	f2.write("\n")

	f.write(train_file + "	" + str(mediatree) + "	" + str(test_ccr_svm) + "	" + str(test_ccr_vecinos) + "\n")

	f2.close()
	f.close()


def read_data(train_file, outputs):

	Dataset = None;

	if train_file[-5:] == ".arff":

		datos = arff.loadarff(train_file)
		Dataset = pd.DataFrame(data=datos[0])

	return Dataset


if __name__ == "__main__":
	pruebas()
