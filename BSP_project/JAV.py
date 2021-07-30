import serial
import time

port = 'COM5'
baud = 115200
# ser = serial.Serial(
# port='/dev/ttyS0',
#baudrate = 9600,
# parity=serial.PARITY_NONE,
# stopbits=serial.STOPBITS_ONE,
# bytesize=serial.EIGHTBITS,
# timeout=1000
# )
ser = serial.Serial(port, baud, timeout=1)

if ser.isOpen():
    print(ser.name + ' is_open...')

while(1):
    #out = ser.readlines(1)
    # if out != []:
    #   print(out)
    flag = "FACEOK"
    #flag = "FERROR"
    ser.write(str(flag).encode())
    time.sleep(1)
