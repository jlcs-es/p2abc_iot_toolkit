#!/usr/bin/python 
import socket
import binascii

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# get local machine name
host = socket.gethostname()
#host = "192.168.33.96"

port = 8888

# connection to hostname on the port.
s.connect((host, port))                               

# Receive no more than 1024 bytes


'''
01          :   command recvAPDU
0004        :   length of APDU
BC060000    :   APDU bytes
                INS_SET_WORKING_MODE
'''
test1 = bytearray([0x01, 0x04, 0x00, 0xbc, 0x06, 0x00, 0x00])

s.send(test1)
print(binascii.hexlify(bytearray(s.recv(2048))))
print(binascii.hexlify(bytearray(s.recv(2048))))


'''
01          :   command recvAPDU
0005        :   length of APDU
BC840000ff  :   APDU bytes
                INS_GET_INFO
'''
test2 = bytearray([0x01, 0x05, 0x00, 0xbc, 0x84, 0x00, 0x00, 0xff])

s.send(test2)
print(binascii.hexlify(bytearray(s.recv(2048))))
print(binascii.hexlify(bytearray(s.recv(2048))))




'''
FF : command finishLoop
'''
finish = bytearray([0xff])
s.send(finish)


s.close()
