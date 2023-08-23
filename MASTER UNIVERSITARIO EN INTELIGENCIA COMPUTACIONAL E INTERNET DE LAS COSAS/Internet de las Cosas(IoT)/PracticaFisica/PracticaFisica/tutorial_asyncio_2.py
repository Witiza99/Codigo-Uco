import uasyncio
from random import randint
from time import sleep
from machine import Pin
from buzzer import Buzzer

led = Pin(2, Pin.OUT)
buzzer = Buzzer(4)


async def task_generator(id, period):
    if id == 1:
        #print(1/0)
        led.on()
        await uasyncio.sleep(period)
        led.off()
        await uasyncio.sleep(period)
    if id == 2:
        buzzer.beep_on(200)
        await uasyncio.sleep(period)
        buzzer.beep_off()
        await uasyncio.sleep(period)
    """for i in range(5):
        n = randint(0,100)
        print(f'task {id} ({period} s) generates -> {n} ', '*'*(i+1))
        await uasyncio.sleep(period)
    print('task ',id,' done!')"""
    return id

async def task_main():
    tasks = []
    for i in range(1,3):
        t = uasyncio.create_task(task_generator(i, randint(1,5)))
        tasks.append(t)
    print(await uasyncio.gather(*tasks))
    print('main done! ')
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