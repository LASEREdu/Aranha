/*
Arquivo onde as Funções vão ser implementadas 
*/
#include <Servo.h>


class Junta : public Servo{
  private:

    /*
    
      variaveis privadas da classe Servos
    
    */

    //variavel que guarda a diferença de regulagem
    
    int dife;
    int anguloAnte = 90;


  public:

    /*
    
      Metodo criador da classe Servos
    
    */

    Junta(int diferenca) : Servo(){

      dife = diferenca;

    }

    /*
    
      Metodos da classe Servos
    
    */

    //Retorna a diferença na regulagem

    int getDiferenca(){

      return dife;

    }

    //mexe o servo para o angulo + a diferença de regulagem

    void mexe(int angulo){

      int rAngulo = angulo+dife;

      if(rAngulo > anguloAnte){

        for(int i=0;i < (rAngulo-anguloAnte);i++){

          write(anguloAnte+i);
          delay(5);

        }

      }

      else{

        for(int i=0;i < (anguloAnte-rAngulo);i++){

          write(anguloAnte-i);
          delay(5);
          
        }

      }

      anguloAnte = rAngulo;

    }


};
