void rotinaPista() {
  //Função que transforma a leitura analogica dos tcrts em um valor entre 0 e 100
  mapTcrt();

  //Função que transoforma a leitura de todos sensores em uma unica variavel
  funcsOut();
}

void rotinaPID() {
  rotinaPista();

  //////////

  if (sOut == 50) {

    velMedia = 255;//90/padrao 95 // 210
    K = 0.7;//padrao 1.7


  }


  if ((sOut >= 47 && sOut <= 50) || (sOut >= 50 && sOut <= 53)) {

    velMedia = 240;//90/padrao 95 // 210 200
    K = 0.7;//padrao 1.7


  }

  if ((sOut >= 45 && sOut < 47) || (sOut > 53 && sOut <= 55)) {

    velMedia = 190;//90/padrao 95 140 160
    K = 1.7;//padrao 1.7


  }


  else {

    velMedia = 90; //padrao 60// 95// 130
    K = 2.7; //padrao 3.0
//K = 2 + 0.05 * sOut;

  }
  /////////

  erro = ref - sOut;

  P = K * erro;
  //eI = I_ant + K * T * (erro + erro_ant) / (2 * T_i);
  D = D_ant * (2 - p * T) / (2 + p * T) + 2 * p * K * T_d / (2 + p * T) * (erro - erro_ant);

  sinal_controle = P + I + D;

  erro_ant = erro;
  I_ant = I;
  D_ant = D;

  controleEsquerda = velMedia + sinal_controle;
  controleDireita = velMedia - sinal_controle;


  leitura_B0 = leitura_B0 << 1;
  leitura_B0 = leitura_B0 | digitalRead(B0);


  if (leitura_B0 == 0b11111110) {

    estado_B0 = !estado_B0;

  }
  digitalWrite(STBY, controle_voltas(estado_B0, leitura_da_pista));

  mEsquerda(controleEsquerda);
  mDireita(controleDireita);

}
