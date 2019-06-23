#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>

#define GPIO_ECHO    3 
#define GPIO_TRIGGER  6

//Funcao aciona sensor: 
void ultra(){
	double distancia_do_pulso=0, distancia_certa=30.0;
	distancia_do_pulso = leitura_sensor(); //fazer proporcionalidade com velocidade do som.
	if (distancia_do_pulso<=distancia_certa){
		printf("\nObstaculo encontrado.");
	}
	else{
	sleep(1);
		printf("\nTa Top.");
	}
	return;
}



//Ler gpio do sensor:
int leitura_sensor(){
//Compensa a distância do sensor
int COMP_SENSOR=0;

//Variáveis usadas para hora do dia
struct timeval start, stop ; 

// Setando pinos de input e output
wiringPiSetup () ;
  pinMode (GPIO_TRIGGER, OUTPUT) ;
  pinMode (GPIO_ECHO, INPUT) ;

//Setando trigger pra Low
digitalWrite (GPIO_TRIGGER,  0) ;

//delay de 200 ms pra começar 
delay (200) ;

//Manda pulso de 10us pro trigger
digitalWrite (GPIO_TRIGGER,  1) ;
delayMicroseconds (10) ;
digitalWrite (GPIO_TRIGGER,  0) ;
gettimeofday(&start, NULL) ;
while (digitalRead (GPIO_ECHO)==0) 
{
gettimeofday(&start, NULL) ;
} 
while (digitalRead (GPIO_ECHO)==1) 
{
gettimeofday(&stop, NULL) ;
} 

// Calcula a distância do pulso
double TIME_DELTA, DISTANCE ;
TIME_DELTA=((stop.tv_sec + stop.tv_usec) / 1000000.0) - ((start.tv_sec +start.tv_usec) / 1000000.0);

// Distância percorrida pelo pulso é o tempo multiplicado pela velocidade do som(cm/s)
DISTANCE=TIME_DELTA * 34000 ;

// A distância é de ida e volta, então temos que dividir por dois:
DISTANCE=DISTANCE / 2 ;

// Adicionando o que foi compensado
DISTANCE=DISTANCE + COMP_SENSOR ;

return DISTANCE;
}