import RPi.GPIO as GPIO
from time import delay

PIE_SENSE = 18
PIE_SIGNAL = 16

run = true

GPIO.setmode(GPIO.BCM)  
GPIO.setup(PIE_SIGNAL, GPIO.OUT)  
GPIO.setup(PIE_SENSE, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def PieOFF():
	run = false

GPIO.add_event_detect(PIE_SENSE, GPIO.FALLING, callback=PieOFF, bouncetime=300)    

while run:
	delay(50)
