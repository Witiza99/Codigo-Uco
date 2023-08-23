#####################################################
# 1- Importar las bibliotecas y realizar la conexión
#####################################################

# importing the required libraries
import pymongo
import json
import warnings
import pandas as pd
import numpy as np
warnings.filterwarnings('ignore')

#################################################################################################################################
#Detalles conexion
connection_details  = 'mongodb+srv://AntonioGG:patata@cluster0.uoqzgcw.mongodb.net/?retryWrites=true&w=majority'

#Detalles_2 base de datos molecular
#db_name='CDS16';
db_name='CDS29';

# connect to the mongoclient
client = pymongo.MongoClient(connection_details);

# the list_database_names() method returns a list of strings
database_names = client.list_database_names();

if db_name in database_names:
  print('The database ' +  db_name + ' exists');
  db=client.get_database(db_name);
else:
    print('&&&&&& The database ' +  db_name + ' must be loaded &&&&&.');
    print()
    sys.exit()

npatrones = db.molecules.count_documents({})
print(npatrones)

pdEntrada = pd.DataFrame(np.zeros((npatrones, 1024), dtype=np.int8))
pdSalida = pd.DataFrame(np.zeros((npatrones,1),dtype=np.int8))

print(pdEntrada.shape)

iterador = 0

result = db.molecules.find({},{"_id": 0, "mfp.bits": 1, "class":1})

for i in result:
	for posicion in i['mfp']['bits']:
		pdEntrada[posicion][iterador] = 1
	if i['class'] == "Active":
		pdSalida[0][iterador] = 1
	iterador = iterador + 1
result = []

dataset = pd.concat([pdEntrada, pdSalida], axis=1)

dataset.to_csv('Dataset.csv',index=False)
#eliminar linea de index que se genera

client.close();

