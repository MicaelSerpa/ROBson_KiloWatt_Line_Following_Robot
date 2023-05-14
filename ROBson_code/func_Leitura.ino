//Função que faz a eitura analogica dos tcrts
void lerTcrt() {
  s[0] = analogRead(tcrt1);
  s[1] = analogRead(tcrt2);
  s[2] = analogRead(tcrt3);
  s[3] = analogRead(tcrt4);
}

//Função que transforma a leitura analogica dos tcrts em um valor entre 0 e 100
void mapTcrt() {
  lerTcrt();

  s[0] = constrain(map(s[0], s_min[0], s_max[0], 0, 100), 0, 100);
  s[1] = constrain(map(s[1], s_min[1], s_max[1], 0, 100), 0, 100);
  s[2] = constrain(map(s[2], s_min[2], s_max[2], 0, 100), 0, 100);
  s[3] = constrain(map(s[3], s_min[3], s_max[3], 0, 100), 0, 100);
}

//Função que transoforma a leitura de todos sensores em uma unica variavel
void funcsOut() {
  while (1) {
    for (int J = max(0, sensorMax - 1); J <= min(3, sensorMax + 1) ; J++) {
      if ((max(valorMax, s[J]) == s[J])) {
        if (max(valorMax, s[J]) != 0) {//incrementa ate 12 quando ta errado
          if (s[sensorMax - 1] > 80 && s[sensorMax] > 80 && s[sensorMax + 1] > 80) {

          } else {
            sensorMax = J;
          }
        }
      }
      valorMax = max(valorMax, s[sensorMax]);
    }



    if (s[0] > Sconst && s[1] < Sconst && s[2] < Sconst && s[3] < Sconst) {
      //Se todos sensores estão fora da linha
      leitura_da_pista = 0;

      sOut = 15;//15
      break;
    }
    if (s[0] < Sconst && s[1] < Sconst && s[2] < Sconst && s[3] > Sconst) {
      //Se todos sensores estão fora da linha
      leitura_da_pista = 0;

      sOut = 85;//85
      break;
    }

    if (s[0] < Sconst && s[1] < Sconst && s[2] < Sconst && s[3] < Sconst) {
      //Se todos sensores estão fora da linha
      leitura_da_pista = 0;

      sOut = sOut_ant;
      break;
    }
    else {
      if ((s[0] + s[1] + s[2] + s[3]) >=  390) {
        //todos sensores em cima da linha(possivel encruzilhada)
        leitura_da_pista = 1;

        sOut = 50;
      }

      else {
        //linha normal
        leitura_da_pista = 0;
        sOut = 100 / 3 * (0 * s[0] + 1 * s[1] + 2 * s[2] + 3 * s[3]) / (s[0] + s[1] + s[2] + s[3]);

        if ((s[0] + s[1] + s[2] + s[3]) <= 100) {
          //Se todos sensores estão fora da linha
          leitura_da_pista = 0;
          //velMedia = 255;
          sOut = sOut_ant;
          break;
        }
      }
      break;
    }
  }

  sOut_ant = sOut;
}
