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

	f=open("Errores2.txt", "a");

	#tree
	X = Dataset.iloc[:,:-outputs].values
	y = Dataset.iloc[:,-outputs].values

	le = preprocessing.LabelEncoder()
	y = le.fit_transform(y.reshape((y.shape[0],)))

	X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size= 0.30, random_state=1);

	Cs = np.logspace(-2,2, num=5, base=10)
	svm_model=svm.SVC(kernel='linear')
	optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs), n_jobs=-1, cv=10)
	optimo.fit(X_train, Y_train)
	test_predictions = optimo.predict(X_test)
	test_ccr_svm = (precision_score(Y_test, test_predictions, average='micro'))*100
	print("SVM_CCR->", test_ccr_svm)

	neighbors = range(1,6)
	neigh = KNeighborsClassifier()
	optimo = GridSearchCV(estimator=neigh, param_grid=dict(n_neighbors=neighbors), n_jobs=-1, cv=10)
	optimo.fit(X_train, Y_train)
	test_predictions = optimo.predict(X_test)
	test_ccr_vecinos = (precision_score(Y_test, test_predictions, average='micro'))*100
	print("neighbors_CCR->", test_ccr_vecinos)

	f.write(train_file + "	" + str(test_ccr_svm) + "	" + str(test_ccr_vecinos) + "\n")

	f.close()


def read_data(train_file, outputs):

	Dataset = None;

	if train_file[-5:] == ".arff":

		datos = arff.loadarff(train_file)
		Dataset = pd.DataFrame(data=datos[0])

	return Dataset


if __name__ == "__main__":
	pruebas()
