# -*- coding: utf-8 -*-
"""
Editor de Spyder

Este es un archivo temporal.
"""


#####################################################
# 1- Importar las bibliotecas y realizar la conexión
#####################################################

# importing the required libraries
import pymongo
import json
import warnings
import argparse
import random
from bson import ObjectId
from datetime import datetime, timezone
from datetime import timedelta
warnings.filterwarnings('ignore')

#-----------------------------------------
#linea de comando para cada apartado

 
parser = argparse.ArgumentParser(description='Programa para realizar la practica 1 y sus 3 modos',)
parser.add_argument("-m", "--mode", help="Modo de funcionamiento para cada apartado", action="store", dest="modo", type=int)
parametros = parser.parse_args()
 
# Aquí procesamos lo que se tiene que hacer con cada argumento
if parametros.modo == 0:
    print("Creación del esquema")

    # conexión con la base de datos en la nube
    client = pymongo.MongoClient("mongodb+srv://AntonioGG:patata@cluster0.uoqzgcw.mongodb.net/?retryWrites=true&w=majority")
    #client = pymongo.MongoClient('mongodb://localhost:27017')

    # vemos las bases de datos existentes
    database_list = client.list_database_names()
    print("Nombres de bd:", database_list)

    #damos la opción de borra alguna bd
    name = input("Introduce el nombre de la base de datos a borrar: ")
    if name == "":
        print("No se elimina ninguna bd")
    else:
        try:
            #eliminamos la base de datos
            client.drop_database(name)
            database_list = client.list_database_names()
            print("Nombres de bd:", database_list)
        except:
            print("Ha ocurrido algun error al borrar la bd")

    #creamos base de datos y las collecciones necesarios
    bdpractica1 = client["Practica1"]
    database_list = client.list_database_names()

    #añadir salario y comm atributo prescindible
    #creo vectores con datos aleatorios
    vName = ["I+D+I","Recursos Humanos","Relaciones Internacionales","Gestion Economica","Secretaria Tecnica","Marketing"]
    vLoc = ["Espiel","Cordoba","Belmez","Pozoblanco","FuenteOvejuna","Villanueva del Rey"]
    vEName = ["Antonio Gomez Gimenez", "Rafael Hormigo Cabello", "Alejandro Garcia Garcia", "Juanma Gomez Morales", "Imanol Rubio Plata",
    "Clara Martinez Rodrigez", "Pilar Grande Romero", "Ana Garcia Fernandez", "Marta Diaz Pedrajas", "Lucia Ruiz Cid"]
    vJOB = ["Informatico", "Electricista", "Contable", "Gestor", "Secretario", "Tecnico", "Fontanero", "Director"]
    vSAL = [1000, 1500, 2000, 2500, 3000, 4000, 5000, 5500]
    vHIREDATE = [datetime.strptime("2014-10-21", '%Y-%m-%d'),datetime.strptime("2017-9-13", '%Y-%m-%d'),datetime.strptime("2022-3-27", '%Y-%m-%d'),datetime.strptime("2023-1-17", '%Y-%m-%d')]

    if "Practica1" in database_list:
        print("La base de datos esta ya creada.")
    else:
        print("Creando BD...");

    print("Creando Colecciones...");
    database = client['Practica1'];
    #compruebo si existen la colecciones
    collist = database.list_collection_names()

    if "DEPT" in collist:
        print("La coleccion DEPT existe.");
        DEPTColeccion = database.get_collection("DEPT");
    else:
        #coleccion DEPT
        DEPTColeccion = bdpractica1.get_collection("DEPT")

        #####################################################
        # 3- Insertar datos en las colecciones.
        #####################################################

        for x in range(50):
            mydict = {"_id": x, "DNAME": vName[random.randint(0, 5)], "LOC": vLoc[random.randint(0, 5)] }
            DEPTColeccion.insert_one(mydict)

        #----------------------------------------------------

    if "EMP" in collist:
        print("La coleccion EMP existe.");
        EMPColeccion = database.get_collection("EMP");
    else:
        #coleccion EMP
        bdpractica1.create_collection("EMP")
        EMPColeccion = bdpractica1.get_collection("EMP")

        #####################################################
        # 3- Insertar datos en las colecciones.
        #####################################################
        for x in range(100):
            #referencia cambiada por id de la collecion referida #{"$ref": "DEPT", "$_id": random.randint(0, 49)}
            mydict = {"_id": x, "ENAME": vEName[random.randint(0, 9)], "JOB": vJOB[random.randint(0, 7)], "HIREDATE": vHIREDATE[random.randint(0, 3)], "SAL": vSAL[random.randint(0, 7)], "COMM": "temp","DEPARTAMENTO":  random.randint(0, 49) }
            EMPColeccion.insert_one(mydict)

        for x in range(100):
            #referencias cambiada por id de la collecion referida #{"$ref": "EMP", "$_id": valoraleatoriox}
            query = {"_id": x}
            valoraleatorio = random.randint(0, 99)#para subordinado
            valoraleatorio2 = random.randint(0, 99)#para jefe
            # 
             #valor aleatorio para ver cuantos subordinados tiene
            valoraleatorio3 = random.randint(1, 5)
            vecSubordinados = []
            for w in range(valoraleatorio3):
                valoraleatorio4 = random.randint(0, 99)
                while valoraleatorio4 == x:#compruebo que no sea el mismo
                    valoraleatorio4 = random.randint(0, 99)
                vecSubordinados.append(valoraleatorio4)

            if valoraleatorio == x: ##controlo que no pueda ser jefe o subordinado de si mismo
                if valoraleatorio2 == x:
                    mydict = {"$set": {"Es_JEFE": "", "Es_subordinado": ""}}
                else:
                    mydict = {"$set": {"Es_JEFE": valoraleatorio2, "Es_subordinado": ""}} 
            else:
                if valoraleatorio2 == x:
                    mydict = {"$set": {"Es_JEFE": "", "Es_subordinado": valoraleatorio2}}
                else:
                    mydict = {"$set": {"Es_JEFE": vecSubordinados, "Es_subordinado": valoraleatorio2}}

            EMPColeccion.update_one(query, mydict)

elif parametros.modo == 1:
    print("Consultas a la informacion")

    # conexión con la base de datos
    client = pymongo.MongoClient("mongodb+srv://AntonioGG:patata@cluster0.uoqzgcw.mongodb.net/?retryWrites=true&w=majority")
    #client = pymongo.MongoClient('mongodb://localhost:27017')

    database_list = client.list_database_names()

    if "Practica1" in database_list:
        database = client['Practica1'];
        #compruebo si existen la colecciones
        collist = database.list_collection_names()
        if "DEPT" in collist and "EMP" in collist:

            bdpractica1 = client["Practica1"]
            DEPTColeccion = bdpractica1.get_collection("DEPT")
            EMPColeccion = bdpractica1.get_collection("EMP")

            ##peticion usando find_one
            print('-----------------------------------------------')#peticion para primer encuentro 
            print(DEPTColeccion.find_one( {}, { "DNAME": 1, "LOC" : 1}))
            print('-----------------------------------------------')#peticion que devuelve primer encuentro con recursos humanos y devuelve todo menos la localidad
            print(DEPTColeccion.find_one( {"DNAME" : "Recursos Humanos"}, {"LOC" : 0} ))
            print('-----------------------------------------------')#peticion que devuelve el primer encuentro con el id 47 dando la localidad
            print(DEPTColeccion.find_one( {"_id" : 47}, {"LOC" : 1} ))
            print('-----------------------------------------------')

            #consulta que devuelve los resultados que coinciden con el id 24 o 11
            result_1 = DEPTColeccion.find({"_id" : { "$in" : [ 24, 11] }})
            for i in result_1:
                print(i)
            print('-----------------------------------------------')

            #consulta que devuelve los resultados cuyo Localidad es Espiel y su id esta entre 40 y 10
            result_1 = DEPTColeccion.find({"LOC" : "Espiel","_id" : { "$lt" : 40, "$gt" : 10}})
            for i in result_1:
                print(i)
            print('-----------------------------------------------')

            #consulta que devuelve los resultados cuyo nombre es Relaciones Internacionales y no se encuentran en Espiel
            result_1 = DEPTColeccion.find({
            "$and" : [{
                         "DNAME" : { "$eq" : "Relaciones Internacionales"}
                      },
                      {
                           "LOC" : { "$ne" : "Espiel"}
                      }]
            })
            for i in result_1:
                print(i)
            print('-----------------------------------------------')

            #consulta que devuelve de la coleccion empleado las personas que se llaman Juanma o son gestores o contables y devuelvo solo el id
            result_1 = EMPColeccion.find({
            "$or" : [{
                         "ENAME" : { "$eq" : "Juanma Gomez Morales"}
                      },
                      {
                           "JOB" : { "$in" : ["Gestor", "Contable"]}
                      }]
            },{"_id": 1})

            for i in result_1:
                print(i) 
            print('-----------------------------------------------') 

            #consulta que devuelve la informacion de todas las personas que se llaman Marta Diaz Pedrajas y su trabajo comienza por G
            result_1 = EMPColeccion.find({
            "JOB" : { "$regex" : "^G" },
            "ENAME": "Marta Diaz Pedrajas"
            })

            for i in result_1:
                print(i)
            print('-----------------------------------------------') 

        else:
            print("No existen todas las colecciones necesarias, pruebe el modo 0")
    else:
        print("No existe la base de datos, pruebe el modo 0")

else:
    print("Modo incorrecto, saliendo del programa")
    exit()
