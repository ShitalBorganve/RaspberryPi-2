import time
import math
import os

HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKGREEN = '\033[32m'
WARNING = '\033[93m'
FAIL = '\033[31m'
ENDC = '\033[0m'
BOLD = "\033[1m"
CYAN = '\33[36m'

os.system('clear')

def main():
  try:
    while True:
      cpu = getCPUuse()
      RAM = getRAMinfo()
      ramu = str(round(( float(RAM[1])/float(RAM[0])) * 100.0, 2))
      print OKGREEN + "\033[1;1HCPU:" + str(cpu) + WARNING + "  CPU Temp:" + getCPUtemperature() + "c" + CYAN + "  RAM:" + ramu + ENDC
      time.sleep(1)
  except KeyboardInterrupt:
    pass

def getCPUtemperature():
  res = os.popen('vcgencmd measure_temp').readline()
  return(res.replace("temp=","").replace("'C\n",""))

def getCPUuse():
  return(str(os.popen("top -n1 | awk '/Cpu\(s\):/ {print $2}'").readline().strip(\
)))

def getRAMinfo():
  p = os.popen('free')
  i = 0
  while 1:
    i = i + 1
    line = p.readline()
    if i==2:
      return(line.split()[1:4])

if __name__ == '__main__':
  main()
