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
from sklearn.model_selection import GridSearchCV

# Load the dataset
data = pd.read_csv('dataset3.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

vector = np.array([1e-2,1e-1,1e0,1e1,1e2,1e3,1e4])

X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size= 0.25, stratify=y);

scaler = preprocessing.StandardScaler();
X_train = scaler.fit_transform(X_train);
X_test = scaler.transform(X_test);


# Train the SVM model
Cs = np.logspace(-2,4, num=7, base=10)
Gs = np.logspace(-2,4, num=7, base=10)
svm_model=svm.SVC(kernel='rbf')
optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs,gamma=Gs), n_jobs=-1, cv=5)
optimo.fit(X_train, Y_train)
test_predictions = optimo.predict(X_test)
test_ccr = (precision_score(Y_test, test_predictions, average='micro'))*100
#print(optimo.score(X_test, Y_test))
print(optimo.best_params_)
print("C=", optimo.get_params()["estimator__C"]," y Gamma=", optimo.get_params()["estimator__gamma"],"-> CCR=", test_ccr, "-> Score=", optimo.score(X_test, Y_test))
#print("C=", get_params(C)," y Gamma=", Gamma," -> CCR=", test_ccr,)

# Plot the points
plt.figure(1, figsize=(16, 12))
plt.clf()
plt.scatter(X_train[:, 0], X_train[:, 1], c=Y_train, zorder=10, cmap=plt.cm.Paired)

# Plot the support vectors class regions, the separating hyperplane and the margins
plt.axis('tight')
# |->Plot support vectors
plt.scatter(optimo.best_estimator_.support_vectors_[:,0], optimo.best_estimator_.support_vectors_[:,1], 
            marker='+', s=100, zorder=10, cmap=plt.cm.Paired)
# |-> Extract the limits
x_min = X_train[:, 0].min()
x_max = X_train[:, 0].max()
y_min = X_train[:, 1].min()
y_max = X_train[:, 1].max()
# |-> Create a grid with all the points and then obtain the SVM 
#    score for all the points
XX, YY = np.mgrid[x_min:x_max:500j, y_min:y_max:500j]
Z = optimo.best_estimator_.decision_function(np.c_[XX.ravel(), YY.ravel()])
# |-> Plot the results in a countour
Z = Z.reshape(XX.shape)
plt.pcolormesh(XX, YY, Z > 0, shading='auto')
plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], 
            linestyles=['--', '-', '--'], levels=[-1, 0, 1])

plt.xlabel('x1')
plt.ylabel('x2')


cadena = "Salidas4/dataset2_C_Gamma.jpg";
plt.savefig(cadena)