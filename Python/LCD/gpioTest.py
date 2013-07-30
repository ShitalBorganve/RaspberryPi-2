#!/usr/bin/python
import RPi.GPIO as GPIO, time, os
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
LED_1 = 25
LED_2 = 24
GPIO.setup(LED_1, GPIO.OUT)
GPIO.setup(LED_2, GPIO.OUT)

GPIO.output(LED_1, False)
GPIO.output(LED_2, False)

os.system('clear')

HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKGREEN = '\033[32m'
WARNING = '\033[93m'
FAIL = '\033[31m'
ENDC = '\033[0m'
BOLD = "\033[1m"
CYAN = '\33[36m'

print WARNING + BOLD + "Press Ctrl+C to exit" + ENDC

try:
    while True:
        GPIO.output(LED_1, True)
        print "\033[1;1H"
        print  "LED 1: " + BOLD + OKGREEN + "ON " + ENDC
        print "\033[3;1H"
        time.sleep(0.06)
        GPIO.output(LED_2, True)
        print "\033[2;1H"
        print  "LED 2: " + BOLD + OKGREEN + "ON " + ENDC
        print "\033[3;1H"
        time.sleep(0.12)
        GPIO.output(LED_1, False)
        print "\033[1;1H"
        print "LED 1: " + BOLD + FAIL +  "OFF" + ENDC
        print "\033[3;1H"
        time.sleep(0.06)
        GPIO.output(LED_2, False)
        print "\033[2;1H"
        print "LED 2: " + BOLD + FAIL +  "OFF" + ENDC
        print "\033[3;1H"
        time.sleep(0.12)
except KeyboardInterrupt:
    pass

GPIO.cleanup()
print "\033[3;1H"
print BOLD + CYAN + "Closed GPIO" + ENDC
time.sleep(1)
os.system('clear')
