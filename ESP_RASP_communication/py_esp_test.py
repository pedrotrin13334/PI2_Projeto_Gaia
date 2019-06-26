#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial

port = "/dev/ttyACM0"
rate = 9600

s1 = serial.Serial(port, rate)
s1.flushInput()

comp_list = ["Girando motores para o angulo:\r\n", "Digite seu angulo\r\n"]
angle_list = ["Motores desligados!\r\n", "A espera de obstaculo\r\n"]
while True:
	if s1.inWaiting()>0:
		inputValue = s1.readline()
		print(inputValue)
		
		if inputValue in angle_list:
			try:
				ang = input("Angulo:")
				s1.write('%d'%ang)
			except:
				print("Erro!")
				s1.write('0')
		if inputValue in comp_list:
			try:
				n = input("Motor status:")
				s1.write('%d'%n)
			except:
				print("Erro!")
				s1.write('0')
