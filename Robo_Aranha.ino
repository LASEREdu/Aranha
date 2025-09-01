/*
  Codigo do Robô Aranha
*/

/*
  Bibliotecas incluidas
*/
#include <Servo.h>
#include "R_A_Funcao.h"
#include <SoftwareSerial.h>


/*
  Definições para os controles do aplicativo
*/

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'
#define ZERO '0'

/*
  Definições das portas do Arduino para o Bluetooth 
*/

SoftwareSerial bluetooth(12,13);

/*
  Definições das Juntas
*/

  Junta* coxa[4] ={

    new Junta(5),
    new Junta(-7),
    new Junta(-5),
    new Junta(-10)

  };

  Junta* joelho[4] ={

    new Junta(0),
    new Junta(-3),
    new Junta(-8),
    new Junta(-2)

  };

/*

  Variaveis do Robô

*/

boolean ligar;
char comando;

/*

  Função para fazer o robô andar

*/

void anda(int direcao){

  direcao--;

  coxa[(direcao+2)%4]->mexe(180);

  joelho[(direcao+3)%4]->mexe(180);
  coxa[(direcao+3)%4]->mexe(180);
  joelho[(direcao+3)%4]->mexe(90);

  coxa[(direcao+2)%4]->mexe(0);

  joelho[(direcao+1)%4]->mexe(180);
  coxa[(direcao+1)%4]->mexe(0);
  joelho[(direcao+1)%4]->mexe(90);

  coxa[(direcao+2)%4]->mexe(90);

  joelho[direcao]->mexe(180);

  coxa[(direcao+3)%4]->mexe(110);
  coxa[(direcao+1)%4]->mexe(70);

  joelho[direcao]->mexe(90);

  coxa[(direcao+3)%4]->mexe(90);
  coxa[(direcao+1)%4]->mexe(90);

}

/*

  função para quando o robô estiver sendo reparado

*/

void reparo(){
  
  for(int i=0;i<4;i++){

    coxa[i]->write(45);
    joelho[i]->write(90);

  }

  delay(15);

}

/*

  função para quando o robô estiver parado

*/

void parado(){

  for(int i=0;i<4;i++){

    coxa[i]->mexe(90);
    joelho[i]->mexe(90);

  }

  delay(15);
}

/*

  Função para quando o robô quiser ir para frente
  casso sentido for true vai para frente casso contrario para traz

*/

void reto(boolean sentido){

  while(comando != ZERO){
    
    comando = bluetooth.read();
    Serial.println(comando);

    if(sentido){

      anda(1);
      anda(2);
    
    }

    else{

      anda(3);
      anda(4);

    }
  }
  delay(15);

}

/*

  Função para quando o robô quiser ir para direita ou para esquerda
  se sentido for true vai para direita se não para esquerda

*/

void lados(boolean sentido){

  while(comando != ZERO){
    
    comando = bluetooth.read();
    Serial.println(comando);

    if(sentido){

      anda(1);
      anda(4);
    
    }

    else{

      anda(2);
      anda(3);

    }
  }
  delay(15);

}

/*

  Função para quando o robô quiser ir para frente ou para traz na diagonal Principal
  se sentido for true vai para frente na diagonal principal

*/

void diaP(boolean sentido){

  while(comando != ZERO){
    
    comando = bluetooth.read();
    Serial.println(comando);

    if(sentido){

      anda(2);
    
    }

    else{

      anda(4);

    }
  }
  delay(15);

}

/*

  Função para quando o robô quiser ir para frente ou para traz na diagonal Secundaria
  se sentido for true vai para frente na diagonal secundaria 

*/

void diaS(boolean sentido){

  while(comando != ZERO){
    
    comando = bluetooth.read();
    Serial.println(comando);

    if(sentido){

      anda(1);
    
    }

    else{

      anda(3);

    }
  }
  delay(15);

}

/*

  Função para girar o robô
  se sentido for true gira sentido horario

*/

void giro(boolean sentido){

  while(comando != ZERO){

    comando = bluetooth.read();
    Serial.println(comando);

    if(sentido){

      coxa[1]->mexe(70);
      coxa[3]->mexe(110);

      for(int i=4;i>0;i--){

        joelho[i%4]->mexe(180);
        coxa[i%4]->mexe(0);
        joelho[i%4]->mexe(90);
        
      }

      parado();

    }

    else{

      for(int i=0;i<4;i++){

        joelho[i]->mexe(180);
        coxa[i]->mexe(180);
        joelho[i]->mexe(90);
        
      }

      parado();

    }

  }

}

/*
  Setup do côdigo
*/

void setup() {

  //Seriais para controlar via bluetooth

  Serial.begin(9600);
  bluetooth.begin(9600);

  //Atribuição dos servos as portas do Arduino
  
  coxa[0]->attach(4);
  joelho[0]->attach(5);
  coxa[1]->attach(6);
  joelho[1]->attach(7);
  coxa[2]->attach(8);
  joelho[2]->attach(9);
  coxa[3]->attach(10);
  joelho[3]->attach(11);

  //Inicialização da posição do robô

  parado();
  
  //Inicialização das variaveis

  ligar = false;
  comando = 0;

}

/*
  Loop principal do côdigo
*/

void loop() {

  //codigo para controlar via bluetooth

  if(!ligar){

    if(bluetooth.available()){

      comando = bluetooth.read();
      Serial.println(comando);

      if(comando == START){

        ligar = true;

      }
    }
  }

  else{

    if(bluetooth.available()){

      comando = bluetooth.read();

      Serial.println(comando);

      switch(comando){

        case FORWARD:

          delay(200);

          comando = bluetooth.read();

          if(comando == CIRCLE){

            giro(true);

          }

          else if(comando == SQUARE){

            giro(false);

          }

          else{

            reto(true);

          }

          break;

        case BACKWARD:

          reto(false);

          break;

        case RIGHT:

          lados(true);

          break;

        case LEFT:

          lados(false);

          break;

        case CIRCLE:

          diaS(true);

          break;

        case CROSS:

          diaS(false);

          break;

        case TRIANGLE:

          diaP(true);

          break;

        case SQUARE:

          diaP(false);

          break;

        case PAUSE:

          ligar = false;

          break;

        case ZERO:

          parado();

          break;

      }
    }
  }
}

