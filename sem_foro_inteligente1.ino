

const int PINO_TRIG = 9;  
const int PINO_ECHO = 10; 

const int S1_VERMELHO = 13;
const int S1_AMARELO = 12;
const int S1_VERDE = 11;


const int S2_VERMELHO = 7;
const int S2_AMARELO = 6;
const int S2_VERDE = 5;




// Distância mínima e máxima que o sensor deve considerar (em cm)
const int DISTANCIA_MIN_CM = 10;
const int DISTANCIA_MAX_CM = 40;

// Tempo mínimo e máximo que o semáforo ficará aberto (em milissegundos)
const int TEMPO_MIN_MS = 3000;  // 3 segundos
const int TEMPO_MAX_MS = 10000; // 10 segundos

// Tempos fixos
const int TEMPO_AMARELO_MS = 1500; // 1.5 segundos
const int TEMPO_FIXO_VERDE_S1_MS = 5000; // 5 segundos para o verde do Semáforo 1


void setup() {
  // Inicia a comunicação serial para depuração (essencial para testes)
  Serial.begin(9600);
  Serial.println("Sistema de Semaforo Inteligente Iniciado.");

  // Configura todos os pinos de LED como SAÍDA (OUTPUT)
  pinMode(S1_VERMELHO, OUTPUT);
  pinMode(S1_AMARELO, OUTPUT);
  pinMode(S1_VERDE, OUTPUT);
  pinMode(S2_VERMELHO, OUTPUT);
  pinMode(S2_AMARELO, OUTPUT);
  pinMode(S2_VERDE, OUTPUT);

  // Configura os pinos do sensor ultrassônico
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}


void loop() {
  // --- 1. LEITURA DO SENSOR ULTRASSÔNICO ---
  
  // Gera o pulso ultrassônico para iniciar a medição
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);

  // Mede o tempo que o som levou para ir e voltar
  long duracao = pulseIn(PINO_ECHO, HIGH);
  
  // Converte o tempo em distância (cm). A fórmula é: (duração * velocidade do som) / 2
  int distancia = duracao * 0.034 / 2;


  // --- 2. CÁLCULO DO TEMPO DO SEMÁFORO ---

  // Mapeia a faixa de distância (ex: 10-40cm) para a faixa de tempo (ex: 3-10s)
  int tempoVariavel = map(distancia, DISTANCIA_MIN_CM, DISTANCIA_MAX_CM, TEMPO_MIN_MS, TEMPO_MAX_MS);
  
  // Garante que o tempo calculado não saia dos limites definidos (mínimo e máximo)
  tempoVariavel = constrain(tempoVariavel, TEMPO_MIN_MS, TEMPO_MAX_MS);

  // **DEPURAÇÃO**: Imprime os valores no Monitor Serial para verificação
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm -> Tempo Calculado: ");
  Serial.print(tempoVariavel / 1000); // Mostra em segundos
  Serial.println(" s");


  // --- 3. CONTROLE DOS SEMÁFOROS ---

  // ESTADO 1: Semáforo 1 VERMELHO, Semáforo 2 VERDE (tempo baseado no sensor)
  digitalWrite(S1_VERDE, LOW);
  digitalWrite(S1_AMARELO, LOW);
  digitalWrite(S1_VERMELHO, HIGH);
  
  digitalWrite(S2_VERMELHO, LOW);
  digitalWrite(S2_AMARELO, LOW);
  digitalWrite(S2_VERDE, HIGH);
  delay(tempoVariavel); // Usa o tempo calculado a partir da distância

  // TRANSIÇÃO: Semáforo 2 fica AMARELO para fechar
  digitalWrite(S2_VERDE, LOW);
  digitalWrite(S2_AMARELO, HIGH);
  delay(TEMPO_AMARELO_MS);

  // ESTADO 2: Semáforo 1 VERDE, Semáforo 2 VERMELHO (tempo fixo)
  digitalWrite(S1_VERMELHO, LOW);
  digitalWrite(S1_VERDE, HIGH);
  
  digitalWrite(S2_AMARELO, LOW);
  digitalWrite(S2_VERMELHO, HIGH);
  delay(TEMPO_FIXO_VERDE_S1_MS);

  // TRANSIÇÃO: Semáforo 1 fica AMARELO para fechar
  digitalWrite(S1_VERDE, LOW);
  digitalWrite(S1_AMARELO, HIGH);
  delay(TEMPO_AMARELO_MS);

  // O loop reinicia e o ciclo começa novamente
}
