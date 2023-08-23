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

IP_SERVIDOR = "localhost"
PUERTO      = 1883

conexion_cliente = libmqtt.Client()
mqtt_ubidots_client = libmqtt.Client()
conectado = False
conectado_ubidots = False

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

#codigo mqtt para ubidots

'''
global variables
'''

BROKER_ENDPOINT = "industrial.api.ubidots.com"
TLS_PORT = 1883  # Secure port
MQTT_USERNAME = "BBFF-m54xl604oKGS6Z3lMqNVGrXLfkENIJ"  # Put here your Ubidots TOKEN
MQTT_PASSWORD = "BBFF-m54xl604oKGS6Z3lMqNVGrXLfkENIJ"  # Leave this in blank
TOPIC = "/v1.6/devices/iot-huerto"

def on_connect_ubidots(client, userdata, flags, rc):
    global conectado_ubidots  # Use global variable
    if rc == 0:

        print("[INFO] Conectando a ubidots")
        conectado_ubidots = True  
    else:
        print("[INFO] Error, conexion fallida")


def on_publish_ubidots(client, userdata, result):
    print("Publicado correctamente")

def connect(mqtt_ubidots_client, mqtt_username, mqtt_password, broker_endpoint, port):
    global conectado_ubidots

    if not conectado_ubidots:
        mqtt_ubidots_client.username_pw_set(mqtt_username, password=mqtt_password)
        #eventos de mqtt para ubidots
        mqtt_ubidots_client.on_connect = on_connect_ubidots
        mqtt_ubidots_client.on_publish = on_publish_ubidots
        mqtt_ubidots_client.connect(broker_endpoint, port=port)
        mqtt_ubidots_client.loop_start()

        intentos = 0

        while not conectado_ubidots and intentos < 5:  # Wait for connection
            print(conectado_ubidots)
            print("Intentando conectar...")
            sleep(1)
            intentos += 1

    if not conectado_ubidots:
        print("[ERROR] No se puede conectar con ubidots")
        return False

    return True

def publish(mqtt_ubidots_client, topic, payload):

    try:
        mqtt_ubidots_client.publish(topic, payload)

    except Exception as e:
        print("[ERROR] No se puede realizar la publicacion, error: {}".format(e))

def main(mqtt_ubidots_client, Dict):
    payload = json.dumps(Dict)
    topic = TOPIC

    
    if not connect(mqtt_ubidots_client, MQTT_USERNAME,
                   MQTT_PASSWORD, BROKER_ENDPOINT, TLS_PORT):
        return False

    publish(mqtt_ubidots_client, topic, payload)

    return True

#fin codigo mqtt para ubidots

def procesar_eventos():
    global conexion_cliente, lock, conectado, mensaje
    while True:
        lock.acquire()
        if evento == CONEXION_FALLIDA:
            print ("Conexion Fallida")
        elif evento == CONEXION_ESTABLECIDA:
            conectado = True
            #conexion_cliente.subscribe("temperatura")
            MQTT_TOPIC = [("/DATA/OUT/TEMPERATURA/STAGE3/VALUE",0),("/DATA/OUT/HUMEDAD_AIRE/STAGE3/VALUE",0),("/DATA/OUT/HUMEDAD_SUELO/STAGE3/VALUE",0)]
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

            if mensaje.topic == "/DATA/OUT/TEMPERATURA/STAGE3/VALUE":

                media = data_in[len(data_in) -3]
                varianza = data_in[len(data_in) -2]
                desv_tipica = data_in[len(data_in) -1]
                Dict = {
                'TEMPERATURA_MEDIA': media,  
                'TEMPERATURA_VARIANZA': varianza,               
                'TEMPERATURA_DESVTIPICA': desv_tipica
                }

            elif mensaje.topic == "/DATA/OUT/HUMEDAD_AIRE/STAGE3/VALUE":

                media = data_in[len(data_in) -3]
                varianza = data_in[len(data_in) -2]
                desv_tipica = data_in[len(data_in) -1]
                Dict = {
                'HUMEDAD_AIRE_MEDIA': media,
                'HUMEDAD_AIRE_VARIANZA': varianza,
                'HUMEDAD_AIRE_DESVTIPICA': desv_tipica
                }

            elif mensaje.topic == "/DATA/OUT/HUMEDAD_SUELO/STAGE3/VALUE":

                media = data_in[len(data_in) -3]
                varianza = data_in[len(data_in) -2]
                desv_tipica = data_in[len(data_in) -1]
                Dict = {
                'HUMEDAD_SUELO_MEDIA': media,
                'HUMEDAD_SUELO_VARIANZA': varianza,
                'HUMEDAD_SUELO_DESVTIPICA': desv_tipica
                }

            # fin procesamiento de este dispositivo
            main(mqtt_ubidots_client, Dict)
            #conexion_cliente.publish("/DATA/OUT/STAGEFINAL/VALUE", data_out)


start_new_thread(procesar_eventos,())

while(not conectado):
    print("DispConexNube")
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
