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
data = pd.read_csv('train_spam.csv',header=None)
data2 = pd.read_csv('test_spam.csv',header=None)
X_train = data.iloc[:,:-1].values
Y_train = data.iloc[:,-1].values
X_test = data2.iloc[:,:-1].values
Y_test = data2.iloc[:,-1].values


# Train the SVM model
Cs = np.logspace(-2,1, num=4, base=10)
svm_model=svm.SVC(kernel='linear')
optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs), n_jobs=-1, cv=5)
optimo.fit(X_train, Y_train)
test_predictions = optimo.predict(X_test)
test_ccr = (precision_score(Y_test, test_predictions, average='micro'))*100
#print(optimo.score(X_test, Y_test))
print(optimo.best_params_)
print("-> CCR=", test_ccr, "-> Score=", optimo.score(X_test, Y_test))
#print("C=", get_params(C)," y Gamma=", Gamma," -> CCR=", test_ccr,)

# Plot the points
"""plt.figure(1, figsize=(16, 12))
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


cadena = "Salidas6/dataset2_C_Gamma.jpg";
plt.savefig(cadena)"""