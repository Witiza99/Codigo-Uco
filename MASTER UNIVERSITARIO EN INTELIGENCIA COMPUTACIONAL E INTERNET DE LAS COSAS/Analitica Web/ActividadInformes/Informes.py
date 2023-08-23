import pandas as pd

Dataset = pd.read_csv("LogsDataiku.csv", sep=',')

Dataset = Dataset.groupby(by="visitor_id").nth(0)#obtengo para cada usuario su primera acceso al entrar al sitio web
##print((Dataset['br_lang'].value_counts()))#usar value_count para agrupar por lenguaje

Dataset['Datetime'] = pd.to_datetime(Dataset['server_ts'])#calculo datetime
Dataset['hour'] = pd.to_datetime(Dataset['Datetime']).dt.strftime("%H"+":00")#cojo solo las horas
#print(Dataset['hour'].value_counts())#calculo la frecuencia obtenida

#Dataset['Datetime'] = Dataset.set_index(pd.DatetimeIndex(Dataset['server_ts']))
#Dataset = Dataset.set_index('Datetime')
#Dataset = Dataset.drop(['server_ts'], axis=1)
#df = df.set_index(pd.DatetimeIndex(df['Datetime']))
#print(Dataset)
#times = pd.DatetimeIndex(Dataset.server_ts)
#Dataset['Datetime'] = Dataset.groupby([times.hour, times.minute])


#Dataset = Dataset.set_index('Datetime')
#grouped = Dataset.groupby(Dataset.index.hour)
#print(grouped['Datetime'].value_counts())

#grouped = Dataset.groupby(pd.Grouper(key='Datetime', axis=0, freq='H')).sum()

#print(grouped)

Dataset = Dataset.groupby(by="visitor_id").nth(0)#obtengo para cada usuario su primera acceso al entrar al sitio web
print((Dataset['user_agent'].value_counts()))#usar value_count para agrupar por lenguaje
