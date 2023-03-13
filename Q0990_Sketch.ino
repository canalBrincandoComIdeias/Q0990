/*  
*  AUTOR:    BrincandoComIdeias
*  APRENDA:  https://cursodearduino.net/
*  SKETCH:   Sensor Fim de Curso
*  DATA:     16/02/23
*/

// DEFINIÇÕES DE PINOS
#define pinLdr A0
#define pinAbrir 9
#define pinFechar 10

#define pinFimAbre 7
#define pinFimFecha 6

// DEFINIÇÕES
#define luzAbrir 800
#define luzFechar 500

#define ABERTA 1
#define FECHADA -1

// VARIÁVEIS GLOBAIS
int persiana; // VARIAVEL DO TIPO INT PODE ARMAZENAR MAIS ESTADOS

void setup() {
  Serial.begin(9600);

  // CONFIGURAÇÃO DOS PINOS
  pinMode(pinLdr, INPUT);
  
  /*  O módulo fim de curso já tem circuito de pullup
      mantemos o INPUT_PULLUP pois serve tanto para o modulo 
      quanto para o botão fim de curso ligado diretamente
  */
  pinMode(pinFimAbre, INPUT_PULLUP);
  pinMode(pinFimFecha, INPUT_PULLUP);

  pinMode(pinAbrir, OUTPUT);
  pinMode(pinFechar, OUTPUT);

  // CONFIRMA O MOTOR PARADO
  digitalWrite(pinAbrir, LOW);
  digitalWrite(pinFechar, LOW);

  // VERIFICANDO POSICAO DA CORTINA AO INICIAR
  if (!digitalRead(pinFimAbre)) {
    persiana = ABERTA;
  } else if (!digitalRead(pinFimFecha)) {
    persiana = FECHADA;
  } else {
    fecharPersiana();
    persiana = FECHADA;
  }

  Serial.println("Fim do setup();");
}

void loop() {
  // LEITURA DO SENSOR
  int leitura = analogRead(pinLdr);

  // INVERTE A LÓGICA DO SENSOR ANALÓGICO
  leitura = map(leitura, 0, 1023, 1023, 0);

  // EXIBE O VALOR DA LEITURA NO MONITOR SERIAL
  //Serial.println(leitura);

  if (persiana == FECHADA) {
    if (leitura > luzAbrir) {
      Serial.print("|Abrindo \t");

      abrirPersiana();

      Serial.println("Aberto|");
      persiana = ABERTA;
    }
  }

  if (persiana == ABERTA) {
    if (leitura < luzFechar) {
      Serial.print("|Fechando\t");

      fecharPersiana();

      Serial.println("Fechado|");
      persiana = FECHADA;
    }
  }

}

void abrirPersiana() {
  /* Liga o motor */
  analogWrite(pinAbrir, 120);
  digitalWrite(pinFechar, LOW);

  /* Não faz nada até que o fim de curso seja pressionado */
  while(digitalRead(pinFimAbre)){;}

  /* Desliga o motor */
  digitalWrite(pinAbrir, LOW);
  digitalWrite(pinFechar, LOW);
}

void fecharPersiana() {
  /* Liga o motor */
  digitalWrite(pinAbrir, LOW);
  analogWrite(pinFechar, 120);

  /* Não faz nada até que o fim de curso seja pressionado */
  while(digitalRead(pinFimFecha)){;}

  /* Desliga o motor */
  digitalWrite(pinAbrir, LOW);
  digitalWrite(pinFechar, LOW);
}