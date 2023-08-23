# -*- coding: utf8 -*-
'''
Universidad de Córdoba
Master Inteligencia Computacional e Internet de las Cosas
Asignatura IoT Industrial
Fernando León García (fernando.leon@uco.es)

Procedimiento de conexión con MQTT simple
'''

# librería de cliente MQTT
import paho.mqtt.client as libmqtt
from _thread import allocate_lock, start_new_thread
from time import sleep
import json
import math

IP_SERVIDOR = "localhost"
PUERTO      = 1883

conexion_cliente = libmqtt.Client()
conectado = False

# lock
lock = allocate_lock()
lock.acquire()

# evento
evento = 0
CONEXION_ESTABLECIDA = 1
CONEXION_FALLIDA = 2
PUBLICACION_REALIZADA = 3
SUSCRIPCION_ACTIVA = 4
DATO_RECIBIDO = 5

# mensaje
mensaje = None

def conexion_establecida(client, userdata, flags, rc):
    global lock, evento
    if rc == 0:
        evento = CONEXION_ESTABLECIDA
        lock.release()

def conexion_fallida(client, *args):
    global evento
    evento = CONEXION_FALLIDA
    lock.release()

def publicacion_enviada(client, *args):
    global evento
    evento = PUBLICACION_REALIZADA
    lock.release()

def suscripcion_activa(client, *args):
    global evento
    evento = SUSCRIPCION_ACTIVA
    lock.release()

def datos_recibidos(client, data, msg):
    global evento, mensaje
    mensaje = msg
    evento = DATO_RECIBIDO
    lock.release()

# Registro de eventos
conexion_cliente.on_connect = conexion_establecida
conexion_cliente.on_publish = publicacion_enviada
conexion_cliente.on_connect_fail = conexion_fallida
conexion_cliente.on_subscribe = suscripcion_activa
conexion_cliente.on_message = datos_recibidos

def procesar_eventos():
    global conexion_cliente, lock, conectado, mensaje
    while True:
        lock.acquire()
        if evento == CONEXION_FALLIDA:
            print ("Conexion Fallida")
        elif evento == CONEXION_ESTABLECIDA:
            conectado = True
            #conexion_cliente.subscribe("temperatura")
            MQTT_TOPIC = [("/DATA/OUT/HUMEDAD_AIRE/STAGE1/VALUE",0)]
            conexion_cliente.subscribe(MQTT_TOPIC)
            print("Conexion Establecida")
        elif evento == PUBLICACION_REALIZADA:
            print ("Publicacion realizada")
        elif evento == SUSCRIPCION_ACTIVA:
            print ("Suscripción activa")
        elif evento == DATO_RECIBIDO:
            print (f"Dato recibido: {mensaje.topic}={mensaje.payload}")
            data_in=json.loads(mensaje.payload)
            #procesamiento de este dispositivo
            n = len(data_in) -1
            media = data_in[n]
            varianza = 0
            data_in.pop(n)
            for dato in data_in:
                varianza += math.pow((dato - media), 2)
            varianza = varianza/(n-1)

            data_in.clear()
            print (media)
            data_in.append(media)
            print (round(varianza, 2))
            data_in.append(round(varianza, 2))
            print(data_in)
            data_out=json.dumps(data_in)
            # fin procesamiento de este dispositivo
            conexion_cliente.publish("/DATA/OUT/HUMEDAD_AIRE/STAGE2/VALUE", data_out)


start_new_thread(procesar_eventos,())

while(not conectado):
    print("DispStage2Sensor2")
    print("Conectando...")
    try:
        conexion_cliente.connect(IP_SERVIDOR, PUERTO)
        conexion_cliente.loop_start()
    except:
        conexion_cliente.loop_stop(force=True)
        evento = CONEXION_FALLIDA
        lock.release()
    sleep(5)

while(True):
    sleep(60)