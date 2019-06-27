def passar_interrupt_esp(n):
    #!/usr/bin/env python
    # -*- coding: utf-8 -*-
    import serial
    port = "/dev/ttyUSB0"
    rate = 9600
    s1 = serial.Serial(port, rate)
    s1.flushInput()
    comp_list = ["ESP\r\n"]
    while True:
        if s1.inWaiting()>0:
            inputValue = s1.readline()
            print(inputValue)
            if inputValue in comp_list:
                try:
                    s1.write('%d'%n)
                    return
                    except:
                        print("Erro!")
                        s1.write('0')
                        return
