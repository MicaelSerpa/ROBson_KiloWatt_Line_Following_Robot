//-------------------------------------------------------------------------------------------------------------------------------
//bibliotecas
//#include <analogWrite.h>
#include "BluetoothSerial.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_task_wdt.h>

#define WDT_TIMEOUT 300000

//-------------------------------------------------------------------------------------------------------------------------------
//definiçoes de porta

#define tcrt1 27
#define tcrt2 26
#define tcrt3 25
#define tcrt4 33

#define LED1 13
#define LED2 32

//#define B1 A4
//#define B2 A5

#define STBY 17


#define IN3 18
#define IN4 5
#define ENB 19

#define IN1 4
#define IN2 16
#define ENA 0

#define B0 15

//-------------------------------------------------------------------------------------------------------------------------------
//constantes e variaveis

//constantes motor
volatile int VEL_MAX = 255;
volatile int VEL_MAX_NEG = 255;
volatile int ZONA_MORTA = 80;


//Parametros PID
volatile int velMedia = 75; //45//50//70/80/90//100//98 padrão era 65
volatile float K = 2.8;  //1.2//1.3//1.7//1.9//1.9//1.9
volatile float T_i = 0.1;//0
volatile float T_d = 0.035;//0.004//0.035//0.1/0.004/0.15//0.25//0.13 padrao 0.022// 0.035

//constantes PID
#define T 0.001
#define TEMPO T*1000000
#define p 10/T_d
#define ref 50


volatile bool controle_LED = 1;


//Variaveis PID
volatile float P = 0;
volatile float I = 0, I_ant = 0;
volatile float D = 0, D_ant = 0;
volatile float erro, erro_ant;
volatile float controleEsquerda, controleDireita, sinal_controle;
volatile int sensorMax = 1, sensorMaxAnt = 1;
volatile int valorMax = 0;
volatile int flagTimer = 0;
volatile long timer_tempo;

//Variaveis leitura de sensores
volatile int s[4], sOut, sOut_ant = 0;

//Calibração de sensores
//int s_min[4] = { 2128, 1643, 1930, 2158}, s_max[4] = {4095, 4095, 4095, 4095}; //guarda os valores maximos e minimos de preto e branco
volatile int s_min[4] = {100, 100, 100, 100}, s_max[4] = {3400, 2900, 2900, 3400};

//int s_min[4] = { 858, 854, 854, 818}, s_max[4] = {2112, 1857, 2107, 2137}; //guarda os valores maximos e minimos de preto e branco

volatile float dif[4];

const int Sconst = 35;


byte leitura_B0 = 1;
bool estado_B0 = false;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


//Configuração da interrupção por timer:
#define tempo_int TEMPO // período de interrupção em microsegundos
hw_timer_t * timer = NULL;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; //Destrava o MUX

void funcTimer() {
  portENTER_CRITICAL_ISR(&mux);
  flagTimer = 1;

  portEXIT_CRITICAL_ISR(&mux);

}


void setup() {
  //Satura a calibração dos senores para diminuir a zona linear e em preto e branco ser 0 e 100
  for (int i = 0; i <= 3; i++)
  {
    dif[i] = (s_max[i] - s_min[i]) / 4.0;
    s_min[i] = s_min[i] + dif[i];
    s_max[i] = s_max[i] - dif[i];
  }

  Serial.begin(57600);
  SerialBT.begin("Robson KiloWatt"); //Bluetooth device name

  //Declaraçao de portas
  // pinMode(B1, INPUT_PULLUP);
  // pinMode(B2, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);


  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(STBY, OUTPUT);

  pinMode(tcrt1, INPUT);
  pinMode(tcrt2, INPUT);
  pinMode(tcrt3, INPUT);
  pinMode(tcrt4, INPUT);
  pinMode(B0, INPUT_PULLUP);


  //  timer = timerBegin(0, 80, true);
  //  timerAttachInterrupt(timer, &funcTimer, true);
  //  timerAlarmWrite(timer, tempo_int, true);
  //  timerAlarmEnable(timer);

  //Inciando o timer para o PID começar a funcionar

  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch



  // Cria uma tarefa no Core 0 para incrementar a variável compartilhada
  xTaskCreatePinnedToCore(taskCore0, "TaskCore0", 10000, NULL, 1, NULL, 0);

  // Cria uma tarefa no Core 1 para imprimir o valor da variável
  //xTaskCreatePinnedToCore(taskCore1, "TaskCore1", 10000, NULL, 1, NULL, 1);

}
float Flag = 0;
void loop() {


 portENTER_CRITICAL(&mux);

    if (xTaskGetTickCount() - timer_tempo > 500) {
      timer_tempo = xTaskGetTickCount();
      envio_dados();
      receber();

    }
    esp_task_wdt_reset();
    portEXIT_CRITICAL(&mux);

 
  // if (flagTimer == 1) {
  //Rotina que realiza o PID

  //Retorna a flag para zero, assim so entra na condição novamente quando a interrupção de timer rodar
  //  flagTimer = 0;
  // }



}
