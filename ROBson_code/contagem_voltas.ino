
byte controle_de_volta = 1;//
int cont_volta = 0;//dentro da funcao
bool leitura_da_pista;//vai pra funcao
bool controle_ponteH;

bool controle_voltas(bool estado_ponteH, bool pulso) {


  if (estado_ponteH == true) {

    controle_de_volta = controle_de_volta << 1;
    controle_de_volta = controle_de_volta | pulso;

    if (controle_de_volta == 0b11111110) {

      cont_volta++;
    }

    controle_ponteH = 1;
  }

  else {
    controle_ponteH = 0;

  }

//    if (cont_volta >= 2) {
//  
//  estado_ponteH = !estado_ponteH;
//   estado_B0 = !estado_B0;
//  
//      controle_ponteH = 0;
//  
//    }

  return controle_ponteH;

}
