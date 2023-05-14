//Função de controle do motor esquerdo, recebe valor entre -255 e 255
void mDireita (int vel) {
  if (vel == 0) {
    analogWrite(ENA, 0);
  } else {
    if (vel >= 0) {
      vel = vel + ZONA_MORTA;
      vel = constrain(vel, 0, VEL_MAX);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, vel);
    } else {
      vel = vel - ZONA_MORTA;
      vel = constrain(vel, -VEL_MAX_NEG, 0);
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, HIGH);
      analogWrite(ENA, -vel);
    }
  }
}

//Função de controle do motor direito, recebe valor entre -255 e 255
void  mEsquerda(int vel) {
  if (vel == 0) {
    analogWrite(ENB, 0);
  } else {
    if (vel >= 0) {
      vel = vel + ZONA_MORTA;
      vel = constrain(vel, 0, VEL_MAX);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, vel);
    } else {
      vel = vel - ZONA_MORTA;
      vel = constrain(vel, -VEL_MAX_NEG, 0);
      digitalWrite(IN4, LOW);
      digitalWrite(IN3, HIGH);
      analogWrite(ENB, -vel );
    }
  }
}
