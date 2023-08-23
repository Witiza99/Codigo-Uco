import uasyncio
from machine import ADC, Pin, PWM
from rgbled import RGBLed
from endcoder import Encoder


from time import sleep_ms


async def task_led(event_trigger):
    ClaseRGBLed = RGBLed(25,26,27)
    while True:
        await event_trigger.wait()
        ClaseRGBLed.set_color(event_trigger.r,event_trigger.g,event_trigger.b)
        event_trigger.clear()

async def task_main():
    
    event_trigger = uasyncio.Event()
    event_trigger.r = 0
    event_trigger.g = 0
    event_trigger.b = 0
    event_trigger.clear
    tasks = []
    tasks.append(uasyncio.create_task(task_led(event_trigger)))
    tasks.append(uasyncio.create_task(task_Encoder(event_trigger)))
    print(await uasyncio.gather(*tasks))
    
def handle_exception(loop, context):
    import sys
    sys.print_exception(context["exception"])
    sys.exit()
    
evt_loop = uasyncio.get_event_loop()
evt_loop.set_exception_handler(handle_exception)
evt_loop.create_task(task_main())

##parte de la tarea encoder
ClaseEncoder = Encoder(Pin(34,35))
    
    while True:
        valor = ClaseEncoder.value()#entre 0 y 1024
        event_trigger.r = (valor/1024)*255
        event_trigger.g = (valor/1024)*255
        event_trigger.b = (valor/1024)*255
        await uasyncio.sleep_ms(100)

while True:
    try:   
        evt_loop.run_forever()
    finally:
        uasyncio.new_event_loop()
