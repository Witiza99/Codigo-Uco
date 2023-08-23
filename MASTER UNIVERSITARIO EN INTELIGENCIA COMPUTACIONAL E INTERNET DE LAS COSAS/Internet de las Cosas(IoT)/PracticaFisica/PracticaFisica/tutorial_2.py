from machine import Pin
from time import sleep
from buzzer import Buzzer
led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)

while True:
    led.on()
    buzzer.beep(50,1)
    led.off()
    sleep(1)