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
from sklearn.metrics import confusion_matrix

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
print(confusion_matrix(Y_test, test_predictions))
IndicesErrores = np.where(Y_test.reshape(Y_test.shape[0],) != test_predictions)[0]
print("patrones erroneos en test: ")
print("patron --> valor esperado | valor obtenido")

fpalabras = open("vocab.txt", mode="r")
matrizpal = fpalabras.read().replace("\t", "\n")
matrizpal = np.array(matrizpal.split(sep="\n"))[1::2]

for i in IndicesErrores:
    print(i+1, " --> ", Y_test.reshape(Y_test.shape[0],)[i]," | ", test_predictions[i], sep="")
    """valPos = np.where(X_test[i] == 1)[0]
    print("Parametros activados en el patron de entrada-> ", X_train[i])
    print(valPos)"""
    valPos = np.where(X_test[i] == 1)[0]
    print("Patron[",i+1,"] -> ",matrizpal[valPos], sep="")
    
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