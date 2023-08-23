

#####################################################
# 1- Importar las bibliotecas y realizar la conexión
#####################################################

# importing the required libraries
import pymongo
import json
import warnings
import pandas as pd
warnings.filterwarnings('ignore')


#-----------------------------------------


# connect to the mongoclient
#client = pymongo.MongoClient("mongodb+srv://AntonioGG:patata@cluster0.uoqzgcw.mongodb.net/?retryWrites=true&w=majority")

client = pymongo.MongoClient('mongodb://localhost:27017')

vficheros = ["sms-call-internet-mi-2013-11-24"]

# get the database
database = client['Milan_CDR_db'];

#####################################################
# 2- Crear las colecciones.
#####################################################

collist = database.list_collection_names()

if "Milan_CDR_c" in collist:
  print("The collection Milan_CDR_c exists.");
  Milan_CDR_collection = database.get_collection("Milan_CDR_c");

  modo = input("Introducir archivos: [0=NO/1=SI]")
  if modo == 1:

    flag = input("Desea crear los ficheros de nuevo: [0=NO/1=SI]")
    if flag == 1:
      print("Creando Ficheros JSON -> ")
      for x in vficheros:
        datos = pd.read_csv(x+".txt", 
                  sep='\t',
                  header=0, 
                  names=['cellid', 'time', 'countrycode', 'smsin','smsout','callin','callout','internet'])
        datos.to_json(x+".json", orient = "records")

    print("Introduciendo Ficheros JSON a la BD -> ")

    for x in vficheros:
      print("Introduciendo Ficheros  -> ")
      print(x)
      with open(x+".json") as f:
        file_data = json.load(f);
        # insert the data into the collection
        Milan_CDR_collection.insert_many(file_data);

  else:
    print("Modo peticiones")
    """my_set=set({0})
    #busqueda de paises con los que interacciona
    for i in Milan_CDR_collection.find({},{"_id": 0, "countrycode": 1}):
      my_set.add(i['countrycode'])

    print(my_set)"""

    """result = Milan_CDR_collection.aggregate([
    ## stage 1
    {
        "$group" : 
                {"_id": "$countrycode",
                "total": { "$sum": 1 }}
    },
    {"$sort": {"total":-1}},#ordeno de mayor a menor
    {"$limit": 3}#cojo solo dos
    ])

    for i in result:
      print(i)"""

    """result = Milan_CDR_collection.aggregate([
    {
        "$group" : 
                {"_id": "$cellid",
                "maxsmsin": { "$max": "$smsin" }}
    },
    {"$sort": {"maxsmsin":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)
    result = Milan_CDR_collection.aggregate([
    {
        "$group" : 
                {"_id": "$cellid",
                "maxsmsout": { "$max": "$smsout" }}
    },
    {"$sort": {"maxsmsout":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)
    result = Milan_CDR_collection.aggregate([
    {
        "$group" : 
                {"_id": "$cellid",
                "maxcallin": { "$max": "$callin" }}
    },
    {"$sort": {"maxcallin":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)
    result = Milan_CDR_collection.aggregate([
    {
        "$group" : 
                {"_id": "$cellid",
                "maxcallout": { "$max": "$callout" }}
    },
    {"$sort": {"maxcallout":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)
    result = Milan_CDR_collection.aggregate([
    {
        "$group" : 
                {"_id": "$cellid",
                "maxinternet": { "$max": "$internet" }}
    },
    {"$sort": {"maxinternet":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)"""

    """result = Milan_CDR_collection.aggregate([
    { "$group" : 
        {"_id": "$cellid",
        "sumactividad": { "$sum": { "$add" : [ 
            '$smsin', "$smsin","$smsout","$callin","$callout","$internet"
        ]}}}
    },
    {"$sort": {"sumactividad":-1}},#ordeno de mayor a menor
    {"$limit": 1}#cojo solo dos
    ])
    for i in result:
      print(i)"""

    """result = Milan_CDR_collection.aggregate([
    { "$group" : 
        {"_id": "$cellid",
        "smsinacum": { "$sum": "$smsin" },
        "smsoutacum": { "$sum": "$smsout" },
        "callinacum": { "$sum": "$callin" },
        "calloutacum": { "$sum": "$callout" },
        "internetacum": { "$sum": "$internet" },            
        }
    },
    { "$out" : "Ej6" }
    ])"""

    result = Milan_CDR_collection.aggregate([
    { "$group" : 
        {"_id": {"cellid":"$cellid","hour":{"$hour": {"$toDate": "$time"}}},
        "smsinacum": { "$sum": "$smsin" },
        "smsoutacum": { "$sum": "$smsout" },
        "callinacum": { "$sum": "$callin" },
        "calloutacum": { "$sum": "$callout" },
        "internetacum": { "$sum": "$internet" },           
        }
    },
    { "$out" : "Ej7" } 
    ], allowDiskUse=True)


else:
  # create weekly demand collection
  database.create_collection("Milan_CDR_c")
  Milan_CDR_collection = database.get_collection("Milan_CDR_c");

  flag = input("Desea crear los ficheros de nuevo: [0=NO/1=SI]")
  if flag == 1:
    print("Creando Ficheros JSON -> ")
    for x in vficheros:
      datos = pd.read_csv(x+".txt", 
                sep='\t',
                header=0, 
                names=['cellid', 'time', 'countrycode', 'smsin','smsout','callin','callout','internet'])
      datos.to_json(x+".json", orient = "records")

  print("Introduciendo Ficheros JSON a la BD -> ")

  for x in vficheros:
    print("Introduciendo Ficheros  -> ")
    print(x)
    with open(x+".json") as f:
      file_data = json.load(f);
      # insert the data into the collection
      Milan_CDR_collection.insert_many(file_data);



##for x in Milan_CDR_collection.find({},{  "_id": 0,  "countrycode": 1}):
 # print(x)
        
