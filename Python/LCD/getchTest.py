import RPi.GPIO as GPIO, os, time

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

print WARNING + BOLD + "Press 'q' to exit" + ENDC

class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

led1 = False
led2 = False

print "\033[1;1H"
print "LED 1: " + BOLD + FAIL +  "OFF" + ENDC
print "\033[2;1H"
print "LED 2: " + BOLD + FAIL +  "OFF" + ENDC
print "\033[3;1H"

try:
	while True:
		getch = _GetchUnix()
		c = getch()
		if c == 'q':
			break
		
		if c == 'a':
			if led1 == True:
        			print "\033[1;1H"
		        	print "LED 1: " + BOLD + FAIL +  "OFF" + ENDC
		        	print "\033[3;1H"
				led1 = False
			else:
                                print "\033[1;1H"
                                print "LED 1: " + BOLD + OKGREEN +  "ON " + ENDC
                                print "\033[3;1H"
				led1 = True
			
			GPIO.output(LED_1, led1)
			
		if c == 's':
			if led2 == True:
                                print "\033[2;1H"
                                print "LED 2: " + BOLD + FAIL +  "OFF" + ENDC
                                print "\033[3;1H"
				led2 = False
			else:
                                print "\033[2;1H"
                                print "LED 2: " + BOLD + OKGREEN +  "ON " + ENDC
                                print "\033[3;1H"
				led2 = True
			
			GPIO.output(LED_2, led2)
		
#		print c

except KeyboardInterrupt:
	pass

print CYAN + BOLD + "Closed GPIO" + ENDC
GPIO.cleanup()
time.sleep(1)
os.system('clear')
