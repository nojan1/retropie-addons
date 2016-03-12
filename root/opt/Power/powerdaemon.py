import RPi.GPIO as GPIO
from time import sleep
import os

PIE_SENSE = 16
PIE_SIGNAL = 18

run = True

GPIO.setmode(GPIO.BCM)  
GPIO.setup(PIE_SIGNAL, GPIO.OUT)  
GPIO.setup(PIE_SENSE, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.output(PIE_SIGNAL, True)

def PieOFF():
	run = False
	GPIO.output(PIE_SIGNAL, False)
	os.system("halt")
	
GPIO.add_event_detect(PIE_SENSE, GPIO.FALLING, callback=PieOFF, bouncetime=300)    

while run:
	sleep(1)
