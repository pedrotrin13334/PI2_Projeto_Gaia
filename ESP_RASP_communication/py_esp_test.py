#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial

port = "/dev/ttyACM0"
rate = 9600

s1 = serial.Serial(port, rate)
s1.flushInput()

comp_list = ["Flash completo\r\n", "Olar. Aqui eh o arduino\r\n"]
while True:
	if s1.inWaiting()>0:
		inputValue = s1.readline()
		print(inputValue)
		if inputValue in comp_list:
			try:
				n = input("Número de flashes:")
				s1.write('%d'%n)
			except:
				print("Erro! Coloque o número de flashes")
				s1.write('0')
