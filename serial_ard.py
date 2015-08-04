""" this program allows the user to communicate with Arduino via serial communitcation
There are 3 build in "functions"
1. send serial commands to arduino
2. Read serial commands from arduino
3. two way communitcation with arduino, using serial_commands running on arduino (in folder)

Please note pyserial is required can be downloaded from here (http://pyserial.sourceforge.net/)
also not that this program is written in python 3
"""


#import modules
import serial 
from time import sleep

#connect to arduino by trying the following list of serial ports, mac need to be added
locations=['/dev/ttyACM0','/dev/ttyACM1','/dev/ttyACM2','/dev/ttyACM3','/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',  
'/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3','COM1','COM2','COM3']    
connected =False #set connected to be false

#try each serial port, exit loop if one connects and set connected to True, else desplay failed to connect to any arduino
for device in locations:   
	#try to connect to current device 
    try:    
        #print ("Trying..."+device)  
        arduino = serial.Serial(device, 9600) 
        connected=True  
        break  
    except:    
        print ("Failed to connect on "+device)   

if connected ==False:
	 print ("\nFailed to connect on to any arduino")
else:
	print ("Successfully connected to arduino\n")


#function converts assci to readable text
def convert (enter):
	out=""
	for a in range (0,len(enter)):

		#if enter[a] is \n or 'enter' return string out
		if (enter[a])==13:
			return out
		else:	#if enter[a] is not \n then add the text value of it to out
			out=out+chr(enter[a])
	#if string is not returns and all characters have been used added, then return out
	return out

#function reads serial line from arduino and returns it.
def readline():
	reading = (arduino.readline())	#read line from arduino
	pr=convert (reading)	#convert to readable text
	return (pr)	#return result

#function allows user to get more than one reading from arduino
def read ():
	#determine how many lines should be read from arduino
	inp=input ("How many values should be read? ")
	while inp.isdigit()!=True:
		inp = input ("Please enter a number: ")
	length =int(inp)
	arduino.flush;
	#manual flush, dont know if the flush works properally...test
	"""for a in range (0,3):
		reading = (arduino.readline())"""
	#get readings from arduino and print to screen
	for a in range (0,length):
		print (readline())



#function writes passed text to the arduino
def writetext (inp):
	for a in inp:
		arduino.write(bytes(a,'ascii'))	#in order for the arduino to understand, pass must be converted to ascii

#function get input from user then write that input to the arduino via serial
def write():
	inp=input ("Enter message to be passed to the arduino: ")
	writetext (inp)


#function does two way communication with arduino
def controlarduino():
	#set coninu variable and flush arduino
	continu=True
	arduino.flush;
	#ask user to reset arduino so it can be properally set up
	print("Please reset arduino")
	#read intro from arduino and print to screen
	for a in range (0,3):
		print (readline())

	#get section from user and write to arduino
	selection=input ()
	writetext(selection)

	#get reading from arduino
	print (readline())
	print ("enter command as [pin command]")

	#while continu is true continue running
	while continu==True:
		#get command from user
		command=input()	

		#if command if r then get reading from arduino, used to flush serial port
		if command=="r":
			print (readline())
		#if command is e then exit by setting continu to false
		elif command =="e":
			continu=False
		#else reformate command so that the arduino will understand and then send it, the print the return arduino
		else:
			command=command[0:command.find(" ")]+","+command[(command.find(" ")+1):]+";"
			writetext(command)
			print (readline())





#Main loop, run while connected is true
while connected == True:
	#desplay options
	option=input("\n1. Enter 'r' to read from arduino\n2. Enter 'w' to pass message to the arduino\n3. Enter 'a' todo two way communitcation with arduino\n4. Enter 'e' to exit:\n")
	
	#the following commands will exit
	if option == "exit":
		break
	if option == "e":
		break
	if option == "4":
		break
	
	#the following commands will write to arduino
	elif option =="i":
		write()
	elif option =="2":
		write()
	elif option =="input":
		write()
	elif option =="w":
		write()
	elif option =="write":
		write()

	#the following commands will read from arduino
	elif option == 'r':
		read()
	elif option =='read':
		read()
	elif option =='1':
		read()

	#the following commands will do two way communication
	elif option=='a':
		controlarduino()
	elif option=='arduino':
		controlarduino()
	elif option=='3':
		controlarduino()

	#if command is invalid don't do anything
	else:
		print ("invalid option")
#end of loop

#at end of program require the user to press enter to exit the program
input ("Press enter to exit: ")
