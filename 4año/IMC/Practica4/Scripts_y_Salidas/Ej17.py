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
Gs = np.logspace(-2,1, num=4, base=10)
svm_model=svm.SVC(kernel='rbf')
optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs,gamma=Gs), n_jobs=-1, cv=5)
optimo.fit(X_train, Y_train)
test_predictions = optimo.predict(X_test)
print(confusion_matrix(Y_test, test_predictions))

    
test_ccr = (precision_score(Y_test, test_predictions, average='micro'))*100

print(optimo.best_params_)
print("-> CCR=", test_ccr, "-> Score=", optimo.score(X_test, Y_test))
