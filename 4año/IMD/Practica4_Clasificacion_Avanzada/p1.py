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
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import GridSearchCV

from sklearn.model_selection import KFold
import sys

def read_data(train_file):

	Dataset = None;

	if train_file[-5:] == ".arff":

		datos = arff.loadarff(train_file)
		Dataset = pd.DataFrame(data=datos[0])

	return Dataset

f=open("Ej2_1.txt", "a");

train_files = ["vote_mod.arff","soybean_mod.arff","segment-challenge.arff","wine.arff","ionosphere.arff","iris.arff","diabetes.arff","glass.arff","labor_mod.arff","segment-test_mod.arff"]

for train_file in train_files:

	Dataset = read_data(train_file)

	if Dataset is None:
		print("Error con el fichero")
		exit()	

	
	#tree
	X = Dataset.iloc[:,:-1].values
	y = Dataset.iloc[:,-1].values

	le = preprocessing.LabelEncoder()
	y = le.fit_transform(y.reshape((y.shape[0],)))

	X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size= 0.30, random_state=1);

	skf= KFold(n_splits=10)
	contador = 0
	mediatree = 0
	for train_index, test_index in skf.split(X_train, Y_train):
		X_trainV2, X_testV2 = X[train_index], X[test_index]
		y_trainV2, y_testV2 = y[train_index], y[test_index]

		# Create Decision Tree classifer object
		clf = DecisionTreeClassifier()
		# Train Decision Tree Classifer
		clf=clf.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=clf.predict(X_testV2)
		test_ccr = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador = contador + test_ccr
	mediatree = contador/10
	print("Tree_CCR->", mediatree)

	skf= KFold(n_splits=10)
	contador = 0
	mediasvm = 0
	for train_index, test_index in skf.split(X_train, Y_train):
		X_trainV2, X_testV2 = X[train_index], X[test_index]
		y_trainV2, y_testV2 = y[train_index], y[test_index]

		# Create Decision Tree classifer object
		svm_model = svm.SVC(kernel='linear')
		# Train Decision Tree Classifer
		svm_model=svm_model.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=svm_model.predict(X_testV2)
		test_ccr = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador = contador + test_ccr
	mediasvm = contador/10
	print("SVM_CCR->", mediasvm)


	skf= KFold(n_splits=10)
	contador = 0
	medianeigh = 0
	for train_index, test_index in skf.split(X_train, Y_train):
		X_trainV2, X_testV2 = X[train_index], X[test_index]
		y_trainV2, y_testV2 = y[train_index], y[test_index]

		# Create Decision Tree classifer object
		neigh = GaussianNB()
		# Train Decision Tree Classifer
		neigh=neigh.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=neigh.predict(X_testV2)
		test_ccr = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador = contador + test_ccr
	medianeigh = contador/10
	print("Gaussian_CCR->", medianeigh)

	f.write(train_file + "	" + str(mediatree) + "	" + str(mediasvm) + "	" + str(medianeigh) + "\n")

f.close()
