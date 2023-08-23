#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 10:14:36 2017

@author: pedroa
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.metrics import precision_score
from sklearn.model_selection import StratifiedKFold

# Load the dataset
data = pd.read_csv('dataset3.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

vector = np.array([1e-2,1e-1,1e0,1e1,1e2,1e3,1e4])

X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size= 0.25, stratify=y);

scaler = preprocessing.StandardScaler();
X_train = scaler.fit_transform(X_train);
X_test = scaler.transform(X_test);


skf= StratifiedKFold(n_splits=5)
mejorconf=0
for C in vector:
	for Gamma in vector:
		contador = 0
		media = 0
		for train_index, test_index in skf.split(X_train, Y_train):
			X_trainV2, X_testV2 = X[train_index], X[test_index]
			y_trainV2, y_testV2 = y[train_index], y[test_index]

			# Train the SVM model

			svm_model = svm.SVC(kernel='rbf',C=C, gamma=Gamma)
			svm_model.fit(X_trainV2, y_trainV2)
			test_predictions = svm_model.predict(X_testV2)
			test_ccr = (precision_score(y_testV2, test_predictions, average='micro'))*100
			contador = contador + test_ccr
		media = contador/5
		print("C=", C," y Gamma=", Gamma," -> CCR=", media)
		if(media>mejorconf):
			mejorconf=media
			mejorC=C
			mejorGamma=Gamma

svm_model = svm.SVC(kernel='rbf',C=mejorC, gamma=mejorGamma)
svm_model.fit(X_train, Y_train)
test_predictions = svm_model.predict(X_test)
test_ccr = (precision_score(Y_test, test_predictions, average='micro'))*100
print("Final")
print("C=", mejorC," y Gamma=", mejorGamma," -> CCR=", test_ccr)

# Plot the points
plt.figure(1, figsize=(16, 12))
plt.clf()
plt.scatter(X_train[:, 0], X_train[:, 1], c=Y_train, zorder=10, cmap=plt.cm.Paired)

# Plot the support vectors class regions, the separating hyperplane and the margins
plt.axis('tight')
# |->Plot support vectors
plt.scatter(svm_model.support_vectors_[:,0], svm_model.support_vectors_[:,1], 
            marker='+', s=100, zorder=10, cmap=plt.cm.Paired)
# |-> Extract the limits
x_min = X_train[:, 0].min()
x_max = X_train[:, 0].max()
y_min = X_train[:, 1].min()
y_max = X_train[:, 1].max()
# |-> Create a grid with all the points and then obtain the SVM 
#    score for all the points
XX, YY = np.mgrid[x_min:x_max:500j, y_min:y_max:500j]
Z = svm_model.decision_function(np.c_[XX.ravel(), YY.ravel()])
# |-> Plot the results in a countour
Z = Z.reshape(XX.shape)
plt.pcolormesh(XX, YY, Z > 0, shading='auto')
plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], 
            linestyles=['--', '-', '--'], levels=[-1, 0, 1])

plt.xlabel('x1')
plt.ylabel('x2')

cadena = "Salida5/dataset3_C"+str(C)+"_Gamma"+str(Gamma)+".jpg";
plt.savefig(cadena)
