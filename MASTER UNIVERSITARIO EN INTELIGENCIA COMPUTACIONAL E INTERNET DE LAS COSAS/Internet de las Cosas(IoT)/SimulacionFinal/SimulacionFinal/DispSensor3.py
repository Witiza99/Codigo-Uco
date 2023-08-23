# -*- coding: utf8 -*-
'''
Universidad de Córdoba
Master Inteligencia Computacional e Internet de las Cosas
Asignatura IoT Industrial
Fernando León García (fernando.leon@uco.es)

Procedimiento de conexión con MQTT simple
'''

import paho.mqtt.client as libmqtt
from time import sleep
import json

# librería para generar números aleatorios
from random import randint

IP_SERVIDOR = "localhost"
PUERTO      = 1883

conexion_cliente = libmqtt.Client()
conectado = False
buffer_envio = []

def conexion_establecida(client, *args):
    if client.is_connected():
        print(f"Conexión establecida con {IP_SERVIDOR}:{PUERTO}")
        global conectado
        conectado = True
    else:
        print(u"No se puede establecer la conexión")

def publicacion_enviada(client, *args):
    print(u"Publicación enviada")

# Registro de eventos
conexion_cliente.on_connect = conexion_establecida # evento de conexión
conexion_cliente.on_publish = publicacion_enviada  # publicación enviada

#inicicacion de valores aleatorios
#...
buffer = [] # valor inicial
#...

while(not conectado):
    print("DispSensor3")
    print("Conectando...")
    try:
        conexion_cliente.connect(IP_SERVIDOR, PUERTO)
        conexion_cliente.loop_start()
    except:
        conexion_cliente.loop_stop(force=True)
        print ("Conexion Fallida")
    sleep(5)

while(True):
    # envía un valor aleatorio para la variable
    

    #si el tamaño del buffer es 50 elimina el primero que entro
    if len(buffer) >= 60:
        buffer.pop(0)
        buffer.append(randint(0, 1000) / 100.0)
        data_out=json.dumps(buffer)
        conexion_cliente.publish("/DATA/OUT/HUMEDAD_SUELO/STAGE0/VALUE", data_out)
        sleep(60)
    else:
        buffer.append(randint(15, 8500) / 100.0)

    
    # periodo del bucle (en segundos)
    #sleep(1)