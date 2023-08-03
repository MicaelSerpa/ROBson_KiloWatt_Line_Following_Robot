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

  Serial.print(analogRead(tcrt1));
  Serial.print(" ");
  Serial.print(analogRead(tcrt2));
  Serial.print(" ");
  Serial.print(analogRead(tcrt3));
  Serial.print(" ");
  Serial.print(analogRead(tcrt4));
  Serial.println(" ");


  SerialBT.print(s[0]);
  SerialBT.print(" ");
  SerialBT.print(s[1]);
  SerialBT.print(" ");
  SerialBT.print(s[2]);
  SerialBT.print(" ");
  SerialBT.print(s[3]);
  SerialBT.print(" ");

  SerialBT.print(analogRead(tcrt1));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt2));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt3));
  SerialBT.print(" ");
  SerialBT.print(analogRead(tcrt4));
  SerialBT.print(" ");


////////////////////
  SerialBT.print(erro);
  SerialBT.print(" ");
  SerialBT.println(velMedia);








}
