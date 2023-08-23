import uasyncio
from random import randint
from time import sleep
from time import sleep_ms
from machine import Pin
from buzzer import Buzzer

led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)
button = Pin(13, Pin.IN, Pin.PULL_UP)
flag = 0

async def task_led(period):
    while True:
        led.on()
        await uasyncio.sleep(period)
        led.off()
        await uasyncio.sleep(period)
    
async def task_bip(event_trigger):
    while True:
        await event_trigger.wait()
        buzzer.beep_on(400)
        await uasyncio.sleep_ms(100)
        event_trigger.clear()
        await event_trigger.wait()
        buzzer.beep_off()
        uasyncio.sleep_ms(100)
        event_trigger.clear()
        
async def task_boton(period,event_trigger):
    last_value = True
    while True:
        value = button.value()
        if value != last_value and value == False:
            event_trigger.set()
        last_value = value
            
        await uasyncio.sleep_ms(period)

async def task_main():
    event_trigger = uasyncio.Event()
    event_trigger.clear
    tasks = []
    tasks.append(uasyncio.create_task(task_led(2)))
    tasks.append(uasyncio.create_task(task_bip(event_trigger)))
    tasks.append(uasyncio.create_task(task_boton(50,event_trigger)))
    print(await uasyncio.gather(*tasks))

"""    
evt_loop = uasyncio.get_event_loop()
evt_loop.create_task(task_main())
evt_loop.run_forever()"""

def handle_exception(loop, context):
    import sys
    sys.print_exception(context["exception"])
    sys.exit()
    
evt_loop = uasyncio.get_event_loop()
evt_loop.set_exception_handler(handle_exception)
evt_loop.create_task(task_main())


while True:
    try:   
        evt_loop.run_forever()
    finally:
        uasyncio.new_event_loop()
