
void processReceivedData(String data) {
  int separatorIndex1 = data.indexOf(';'); // Encontra o índice do primeiro separador ';'
  int separatorIndex2 = data.indexOf(';', separatorIndex1 + 1); // Encontra o índice do segundo separador ';'

  if (separatorIndex1 == -1 || separatorIndex2 == -1) {
    Serial.println("Formato de dados inválido!"); // Verifica se os separadores foram encontrados
    return;
  }

  // Extrai os dados individuais a partir das posições dos separadores
  String dados1 = data.substring(0, separatorIndex1);
  String dados2 = data.substring(separatorIndex1 + 1, separatorIndex2);
  String dados3 = data.substring(separatorIndex2 + 1);

  // Imprime os dados recebidos no monitor serial
  Serial.print("Dados 1: ");
  Serial.print(dados1);
  Serial.print("Dados 2: ");
  Serial.print(dados2);
  Serial.print("Dados 3: ");
  Serial.println(dados3);
}


void receber() {

  if (SerialBT.available() > 0) { // Verifica se há dados disponíveis na porta serial
    String receivedData = SerialBT.readStringUntil('@'); // Lê os dados até encontrar o caractere '@'
    processReceivedData(receivedData); // Chama a função para processar os dados recebidos
  }



}







void envio_dados() {

  controle_LED = !controle_LED;


  digitalWrite(LED1, controle_LED);
  digitalWrite(LED2, !controle_LED);

  //      Serial.print(s[0]);
  //      Serial.print(" ");
  //
  //      Serial.print(s[1]);
  //      Serial.print(" ");
  //
  //      Serial.print(s[2]);
  //      Serial.print(" ");
  //      Serial.print(s[3]);
  //      Serial.println(" ");

  //  Serial.print(analogRead(tcrt1));
  //  Serial.print(" ");
  //  Serial.print(analogRead(tcrt2));
  //  Serial.print(" ");
  //  Serial.print(analogRead(tcrt3));
  //  Serial.print(" ");
  //  Serial.print(analogRead(tcrt4));
  //  Serial.println(" ");


  //  SerialBT.print(s[0]);
  //  SerialBT.print(" ");
  //  SerialBT.print(s[1]);
  //  SerialBT.print(" ");
  //  SerialBT.print(s[2]);
  //  SerialBT.print(" ");
  //  SerialBT.print(s[3]);
  //  SerialBT.print(" ");

  Serial.print(analogRead(tcrt1));
  Serial.print(" ");
  Serial.print(analogRead(tcrt2));
  Serial.print(" ");
  Serial.print(analogRead(tcrt3));
  Serial.print(" ");
  Serial.print(analogRead(tcrt4));
  Serial.print(" ");

  Serial.println(sOut);


  //
  SerialBT.print(analogRead(tcrt1));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt2));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt3));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt4));
  SerialBT.println(" ");
  //
  //
  //  ////////////////////
  //  SerialBT.print(erro);
  //  SerialBT.print(" ");
  //  SerialBT.println(velMedia);
  // SerialBT.println(K);




}
