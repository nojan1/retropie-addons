import RPi.GPIO as GPIO
from time import sleep

PIE_SENSE = 18
PIE_SIGNAL = 16

run = True

GPIO.setmode(GPIO.BCM)  
GPIO.setup(PIE_SIGNAL, GPIO.OUT)  
GPIO.setup(PIE_SENSE, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def PieOFF():
	run = False

GPIO.add_event_detect(PIE_SENSE, GPIO.FALLING, callback=PieOFF, bouncetime=300)    

while run:
	sleep(1)
