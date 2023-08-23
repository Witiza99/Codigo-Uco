import click
import numpy as np
import pandas as pd
from scipy.io import arff
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.preprocessing import StandardScaler
import seaborn as sns

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

	print(Dataset)
	Dataset.hist()
	plt.show()

	
	x = Dataset.values #returns a numpy array
	DatasetNormalizado=x[:, :-outputs]
	Estandarizado=x[:, :-outputs]
	auxiliarEstandar = pd.DataFrame(Estandarizado)

	min_max_scaler = preprocessing.MinMaxScaler()
	x_scaled = min_max_scaler.fit_transform(DatasetNormalizado)
	DatasetNormalizado = pd.DataFrame(x_scaled)
	DatasetNormalizado.hist()
	plt.show()

	Estandarizado_scaled= preprocessing.StandardScaler() 
	EstandarizadoFinal= Estandarizado_scaled.fit_transform(Estandarizado)
	names=auxiliarEstandar.columns
	EstandarizadoFinal =pd.DataFrame(EstandarizadoFinal, columns=names)
	EstandarizadoFinal.hist()
	plt.show()

	pd.plotting.scatter_matrix(Dataset)
	plt.show()

	pd.plotting.scatter_matrix(DatasetNormalizado)
	plt.show()

	pd.plotting.scatter_matrix(EstandarizadoFinal)
	plt.show()

	corr = Dataset.corr()
	sns.heatmap(corr, xticklabels=corr.columns,yticklabels=corr.columns)
	plt.show()

	pd.plotting.parallel_coordinates(Dataset, 'class')
	plt.show()


def read_data(train_file, outputs):

	Dataset = None;

	if train_file[-5:] == ".arff":

		datos = arff.loadarff(train_file)
		Dataset = pd.DataFrame(data=datos[0])

	return Dataset


if __name__ == "__main__":
	pruebas()
