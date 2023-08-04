// Função que será executada pelo Core 0 (Procesador 1)
void taskCore0(void *pvParameters) {
  while (1) {
    // Incrementa o valor compartilhado de forma segura usando o mutex
    portENTER_CRITICAL(&mux);


    esp_task_wdt_reset();
    rotinaPID();

    portEXIT_CRITICAL(&mux);

    //  Serial.print("teste");
    //delay(1);
  }
}

// Função que será executada pelo Core 1 (Procesador 0)
void taskCore1(void *pvParameters) {
  while (1) {

   

  }
}
