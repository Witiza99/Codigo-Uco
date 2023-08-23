import uasyncio
from random import randint

def print_(i):
    print(i)
    
async def task_main():
    while True:
        print_('main task generates -> %d' %randint(0,100))
        await uasyncio.sleep(1)

"""
uasyncio.run(task_main())
"""
evt_loop = uasyncio.new_event_loop()
task = evt_loop.create_task(task_main())
try:
    evt_loop.run_forever()
finally:
    evt_loop.new_event_loop()