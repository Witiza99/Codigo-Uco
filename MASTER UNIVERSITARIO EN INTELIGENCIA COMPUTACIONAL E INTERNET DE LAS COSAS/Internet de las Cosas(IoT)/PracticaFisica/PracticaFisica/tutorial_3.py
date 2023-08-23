from machine import Pin
from time import sleep_ms
from buzzer import Buzzer

led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)
button = Pin(13, Pin.IN, Pin.PULL_UP)

while True:
    if button.value() == False:
        led.on()
        buzzer.beep(400,1)
    else:
        led.off()
    
    sleep_ms(100)
