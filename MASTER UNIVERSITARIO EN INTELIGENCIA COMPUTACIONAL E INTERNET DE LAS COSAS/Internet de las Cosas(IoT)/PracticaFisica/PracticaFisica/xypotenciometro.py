from machine import Pin, ADC
import uasyncio

async def main(x,y):
    while True:
        print('Eje X: ', x.read())
        print('Eje Y: ', y.read())
        await uasyncio.sleep_ms(1000)
        
x_axis = ADC(Pin(34))
x_axis.atten(ADC.ATTN_11DB)
y_axis = ADC(Pin(35))
y_axis.atten(ADC.ATTN_11DB)
uasyncio.run(main(x_axis,y_axis))
