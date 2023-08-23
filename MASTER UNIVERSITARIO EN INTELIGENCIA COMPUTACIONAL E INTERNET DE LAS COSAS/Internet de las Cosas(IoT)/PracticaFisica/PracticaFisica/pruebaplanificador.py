import uasyncio
from random import randint
from time import sleep
from machine import Pin
from buzzer import Buzzer

led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)

async def task_led(period):
    while True:
        led.on()
        await uasyncio.sleep(period)
        led.off()
        await uasyncio.sleep(period)
    
async def task_bip(period):
    while True:
        buzzer.beep_on(400)
        await uasyncio.sleep(period)
        buzzer.beep_off()
        await uasyncio.sleep(period)

async def task_main():
    
    tasks = []
    tasks.append(uasyncio.create_task(task_led(2)))
    tasks.append(uasyncio.create_task(task_bip(1)))
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