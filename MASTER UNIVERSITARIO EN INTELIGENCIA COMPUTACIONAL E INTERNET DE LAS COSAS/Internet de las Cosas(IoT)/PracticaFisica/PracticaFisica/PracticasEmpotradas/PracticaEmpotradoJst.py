import uasyncio
from machine import ADC, Pin, PWM
from rgbled import RGBLed
from joystick import Joystick
import math

Flag = True


from time import sleep_ms

def polar(x, y):
    """returns r, theta(degrees)
    """
    r = (x ** 2 + y ** 2) ** .5
    theta = math.degrees(math.atan2(y,x))
    if theta < 0:
        theta = abs(theta+180)+180
    return r, theta

async def task_led(event_trigger):
    ClaseRGBLed = RGBLed(25,26,27)
    while True:
        await event_trigger.wait()
        ClaseRGBLed.set_color(event_trigger.r,event_trigger.g,event_trigger.b)
        event_trigger.clear()
    

async def task_JST(event_trigger):
    ClaseJoystick = Joystick(34,35)
    global Flag
    while True:
        x,y = ClaseJoystick.read_xy()
        mod,ang = polar(x,y)
        
        if mod > 1:
            print(ang)
            if ang < 150 and ang >= 30:
                #ClaseRGBLed.set_color(255,0,0)
                print("Rojo")
                event_trigger.r = 255
                event_trigger.g = 0
                event_trigger.b = 0
                Flag = True
                event_trigger.set()
            elif ang < 270 and ang >= 150:
                #ClaseRGBLed.set_color(0,255,0)
                print("Verde")
                event_trigger.r = 0
                event_trigger.g = 255
                event_trigger.b = 0
                Flag = True
                event_trigger.set()
            elif ang >= 270 or ang < 30:
                #ClaseRGBLed.set_color(0,0,255)
                print("Azul")
                event_trigger.r = 0
                event_trigger.g = 0
                event_trigger.b = 255
                Flag = True
                event_trigger.set()
            else:
                print("Error inesperado")
                
        elif (Flag):
            #ClaseRGBLed.set_color(0,0,0)
            event_trigger.r = 0
            event_trigger.g = 0
            event_trigger.b = 0
            Flag = False
            event_trigger.set()
            
        await uasyncio.sleep_ms(100)
    


async def task_main():
    
    event_trigger = uasyncio.Event()
    event_trigger.r = 0
    event_trigger.g = 0
    event_trigger.b = 0
    event_trigger.clear
    tasks = []
    tasks.append(uasyncio.create_task(task_led(event_trigger)))
    tasks.append(uasyncio.create_task(task_JST(event_trigger)))
    print(await uasyncio.gather(*tasks))
    
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