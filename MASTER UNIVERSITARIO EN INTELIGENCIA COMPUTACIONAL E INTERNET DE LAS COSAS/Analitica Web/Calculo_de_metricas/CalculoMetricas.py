import pandas as pd

Dataset = pd.read_csv("LogsDataiku.csv", sep=',')

print(len(Dataset['session_id'].unique())) #calculo la cantidad de sesiones únicas que se han producido para conocer el numero de visitas

print(len(Dataset['visitor_id'].unique())) #calculo la cantidad de id de visitantes para saber los visitantes únicos

print(Dataset['session_id'].value_counts().mean()) #calculo la frecuencia de cada session y hago la media

print((Dataset['session_id'].value_counts() == 1).sum())#usar value_count para agrupar por session, dar la cantidad de valores a uno

print(Dataset['location'].value_counts())#numero total de veces que se repite cada página
Dataset_tmp = Dataset.loc[:, ['session_id', 'location']]#escojo columnas que me interesan
Dataset_tmp = Dataset_tmp.groupby(by="session_id").nth(-1)#obtengo para cada session la última página
print((Dataset_tmp['location'].value_counts()))#numero total de veces que se repite cada página siendo la última
print(Dataset_tmp['location'].value_counts().sum()/Dataset['location'].value_counts().sum())#tasa de salidas frente a numero de páginas

#para la tasa va por páginas, no por sitio, es decir, para cada página el % de que sea ultima entre esto->(el numero de sesiones únicas indica las salidas totales)


print(pd.isna(Dataset['referer']).sum())#calculo la cantidad de sesiones que no tienen referer

Dataset_tmp = Dataset.loc[:, ['session_id', 'referer']]#escojo columnas que me interesan
Dataset_tmp = Dataset_tmp.groupby(by="session_id").nth(0)#obtengo para cada session la primera páginaS
Dataset_tmp=Dataset_tmp.dropna(axis=0)#elimino filas con valores vacios ya que son por tráfico directo
print(Dataset_tmp.loc[Dataset_tmp['referer'].str.contains('www.dataiku.com/blog/')==True].count())#escojo aquellos que son por busqueda


print(Dataset_tmp.loc[Dataset_tmp['referer'].str.contains('www.dataiku.com/blog/')==False].count())#escojo aquellos que son por link de otra página


