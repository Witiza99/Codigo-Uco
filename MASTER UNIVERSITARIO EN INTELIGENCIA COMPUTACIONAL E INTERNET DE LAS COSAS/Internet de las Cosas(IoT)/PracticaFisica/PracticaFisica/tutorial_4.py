from machine import Pin
from time import sleep_ms
from buzzer import Buzzer

led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)
button = Pin(13, Pin.IN, Pin.PULL_UP)
flag = 0

def irq_button(pin):
    button.irq(trigger=Pin.IRQ_FALLING, handler=lambda x: None)
    #led.on()
    if flag == 0:
        buzzer.beep_on(200)
        flag == 1
    else:
        buzzer.beep_off()
        flag == 0
    #led.off()
    button.irq(trigger=Pin.IRQ_FALLING, handler=irq_button)

button.irq(trigger=Pin.IRQ_FALLING, handler=irq_button)

while True:
    led.on()
    sleep_ms(500)
    led.off()
    sleep_ms(500)
