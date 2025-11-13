
const int vermelho1 = 13;
const int amarelo1 = 12;
const int verde1 = 11;
const int vermelho2 = 10;
const int verde2 = 9;
const int botao = 8;

unsigned long tempo;

void setup()
{
  tempo = millis();
  
  pinMode(vermelho1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(verde1, OUTPUT);
  pinMode(vermelho2, OUTPUT);
  pinMode(verde2, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  digitalWrite(verde1, 1);
  digitalWrite(vermelho2, 1);
  
}

void loop(){
  int leitura = digitalRead(botao);
  
  if((millis() - tempo) > 5000){
    
    if(leitura == 0){
      
      digitalWrite(verde1, 0);
      digitalWrite(amarelo1, 1);
      delay(2000);
      digitalWrite(amarelo1, 0);
      digitalWrite(vermelho1, 1);
      delay(1000);
      digitalWrite(vermelho2, 0);
      digitalWrite(verde2, 1);
      delay(5000);
      
      for(int i = 0 ; i<5 ; i++){
        digitalWrite(verde2, 0);
        delay(500);
        digitalWrite(verde2, 1);
        delay(500);
      }
      digitalWrite(verde2, 0);
      digitalWrite(vermelho2, 1);
      
      delay(500);
      
      digitalWrite(vermelho1, 0);
      digitalWrite(verde1, 1);
              
      tempo = millis();
    }
  }
  delay(10);
}
