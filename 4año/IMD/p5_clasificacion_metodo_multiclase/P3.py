import numpy as np
import pandas as pd
from scipy.io import arff
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.metrics import precision_score
from sklearn.model_selection import GridSearchCV
from sklearn.multiclass import OutputCodeClassifier
from sklearn.multiclass import OneVsRestClassifier
from sklearn.multiclass import OneVsOneClassifier

from sklearn.model_selection import KFold
import sys


def read_data(train_file):

	Dataset = None;

	if train_file[-5:] == ".arff":

		datos = arff.loadarff(train_file)
		Dataset = pd.DataFrame(data=datos[0])

	return Dataset

f=open("Ej3_OVO_OVA_ECOC.txt", "a");

train_files = ["soybean_mod.arff","segment-challenge.arff","wine.arff","iris.arff","glass.arff","segment-test_mod.arff"]

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
	contador_ovo = 0
	contador_ova = 0
	contador_ecoc = 0
	mediatree1 = 0
	mediatree2 = 0
	mediatree3 = 0
	for train_index, test_index in skf.split(X_train, Y_train):
		X_trainV2, X_testV2 = X[train_index], X[test_index]
		y_trainV2, y_testV2 = y[train_index], y[test_index]

		###ovo
		# Create Decision Tree classifer object
		clf = OneVsOneClassifier(DecisionTreeClassifier())
		# Train Decision Tree Classifer
		clf=clf.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=clf.predict(X_testV2)
		test_ccr_ovo = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador_ovo = contador_ovo + test_ccr_ovo

		###ova
		# Create Decision Tree classifer object
		clf = OneVsRestClassifier(DecisionTreeClassifier())
		# Train Decision Tree Classifer
		clf=clf.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=clf.predict(X_testV2)
		test_ccr_ova = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador_ova = contador_ova + test_ccr_ova

		###ecoc
		# Create Decision Tree classifer object
		clf = OutputCodeClassifier(DecisionTreeClassifier())
		# Train Decision Tree Classifer
		clf=clf.fit(X_trainV2, y_trainV2)
		# Predict the response for test dataset
		y_pred=clf.predict(X_testV2)
		test_ccr_ecoc = (precision_score(y_testV2, y_pred, average='micro'))*100
		contador_ecoc = contador_ecoc + test_ccr_ecoc

	mediatree1 = contador_ovo/10
	print("Tree_CCR_ovo->", mediatree1)

	mediatree2 = contador_ova/10
	print("Tree_CCR-_ova>", mediatree2)

	mediatree3 = contador_ecoc/10
	print("Tree_CCR_ecoc->", mediatree3)



	f.write(train_file + "	" + str(mediatree1) + "	" + str(mediatree2) + "	" + str(mediatree3) +"\n")

f.close()