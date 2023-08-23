#!/usr/bin/env python

import numpy as np
import misvm
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split


def main():
    ###########################333
    #leer con pandas, junta en listas cada id de bag, transformar a numpy (bags y labels se juntan necesitan numpy)
    import pandas as pd
    #dogs = pd.read_csv("CorelDogs.csv", names=["Class", "BagId", "a1", "a2","a3","a4","a5","a6","a7","a8","a9"])
    #dogs = pd.read_csv("CorelFlowers.csv", names=["Class", "BagId", "a1", "a2","a3","a4","a5","a6","a7","a8","a9"])
    dogs = pd.read_csv("CorelFood.csv", names=["Class", "BagId", "a1", "a2","a3","a4","a5","a6","a7","a8","a9"])
    bags = []
    #total_bags = 0;
    labels = []

    #divido en labels y datos para cada mochila
    result = dogs["BagId"].max()
    for i in range(1,result+1):
        bag = dogs[dogs['BagId'] == i]
        if (bag['Class'] == 1).any():
            labels.append(float(1))
        else:
            labels.append(float(-1))
        bag.drop(['Class', 'BagId'], axis=1)
        bags.append(bag.values.tolist())
        #total_bags =+ 1

    #bags = StandardScaler().fit_transform(bags)

    #porcentage = int(total_bags*0.2);
    # Spilt dataset arbitrarily to train/test sets

    train_bags, test_bags, train_labels, test_labels = train_test_split(bags, labels, stratify=labels)

    # Construct classifiers
    classifiers = {}
    classifiers['MissSVM'] = misvm.MissSVM(kernel='linear', C=1.0, max_iters=20)
    classifiers['sbMIL'] = misvm.sbMIL(kernel='linear', eta=0.1, C=1e2)
    classifiers['SIL'] = misvm.SIL(kernel='linear', C=1.0)
    print("Comienzan los entrenamientos:")
    # Train/Evaluate classifiers
    accuracies = {}
    for algorithm, classifier in classifiers.items():
        classifier.fit(train_bags, train_labels)
        predictions = classifier.predict(test_bags)
        accuracies[algorithm] = np.average(test_labels == np.sign(predictions))

    for algorithm, accuracy in accuracies.items():
        print('\n%s Accuracy: %.1f%%' % (algorithm, 100 * accuracy))


if __name__ == '__main__':
    main()
