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


#-----------------------------------------------------#
from numpy import gradient, mean
from random import gauss

"""
Función auxiliar que genera una curva normalizada y suavizada entre 0 
y el valor final, teniendo en cuenta la pendiente inicial
"""
#𝑓(𝑥)=(m−2𝑏)x^3+(3𝑏−2m)x^2+mx
def spline(x, v_final, m):
    return (v_final -2*m)*x**3 + (3*v_final - 2*m)*x**2 + m*x

"""
Función que recibe:
1.- un buffer con los datos históricos del valor
2.- el valor final deseado
y devuelve el próximo valor de la serie
"""
def generar_asintota(ultimos_valores, v_final):
    l = len(ultimos_valores)
    if l > 1:
        m = mean(gradient(ultimos_valores if l <=5 else ultimos_valores[-5:]))
        v = ultimos_valores[-1]
    else:
        m = 0
        v = 0 if l == 0 else ultimos_valores[0]
    v_inc = v_final - v if v_final > v else v - v_final

    imean = spline(0.2, v_inc, m)
    istd  = spline(0.1, v_inc, m)
    return v + gauss(imean, istd)*(1 if v_final > v else -1)
#-----------------------------------------------------#


IP_SERVIDOR = "localhost"
PUERTO      = 1883

conexion_cliente = libmqtt.Client()
conectado = False

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
buffer = [15, ] # valor inicial
v_final = 25
#...

while(not conectado):
    print("DispSensor1")
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
        buffer.append(round(generar_asintota(buffer, v_final), 2))
        data_out=json.dumps(buffer)
        conexion_cliente.publish("/DATA/OUT/TEMPERATURA/STAGE0/VALUE", data_out)
        sleep(60)
    else:
        buffer.append(round(generar_asintota(buffer, v_final), 2))

    
    # periodo del bucle (en segundos)
    #sleep(1)