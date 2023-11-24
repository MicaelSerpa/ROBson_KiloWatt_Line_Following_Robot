void rotinaPista() {
  //Função que transforma a leitura analogica dos tcrts em um valor entre 0 e 100
  mapTcrt();

  //Função que transoforma a leitura de todos sensores em uma unica variavel
  funcsOut();
}

void rotinaPID() {

  rotinaPista();


  float sOutFloat = static_cast<float>(sOut);
  float sOutOffset = sOutFloat - 50.0;





  if (sOut > 40 && sOut < 60) {


    velMedia = 200; //200



  }

  else {

    velMedia = 140; //sem ajuste padrão 100 //110 PADRAO 125
  }


//  K = 0.9 + 0.4 * abs(sOutOffset) / 5.0; //5.0
//  K = constrain(K, 0.9, 7.5);


  erro = ref - sOut;
  P = K * erro;
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
