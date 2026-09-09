void findball() {  ///////////may improve
  if (frontIR_n == 4) {
    degree = 0;
    closevalue = 0;
  } else {
    if (frontIR_v > backIR_v) {
      b_value = frontIR_v;
      degree = (frontIR_n - 1) * 30 - 90;
      closevalue = frontIR_v / 130 * (chasespeed - 20);
    } else {
      b_value = backIR_v;
      degree = (backIR_n - 1) * 30 + 90;
      if (degree > 180) {
        degree -= 360;
      }
      closevalue = backIR_v / 130 * (chasespeed - 20);
    }
    close_value = max(frontIR_v, backIR_v);
  }
}

void findball2() {  ///////////may improve
  if (frontIR_n == 4) {
    degree = 0;
    closevalue = 0;
  } else {
    if (frontIR_v > backIR_v) {
      degree = (frontIR_n - 1) * 30 - 90;

      closevalue = frontIR_v / 130 * (chasespeed - 20);

    } else {
      degree = (backIR_n - 1) * 30 + 90;
      if (degree > 180) {
        degree -= 360;
      }
      closevalue = backIR_v / 130 * (chasespeed - 20);
    }
    close_value = max(frontIR_v, backIR_v);
    if (degree > 0) {
      degree += close_value * 1.3;

    } else {
      degree -= close_value * 1.3;
    }
  }
}

void follow(int speede_) {
  //assuming that clockwise
  degree1 = (degree - 45) / 180 * 3.14159265;
  degree2 = (degree + 45) / 180 * 3.14159265;

  lfspeed_ = cos(degree1) * 1.04;
  rfspeed_ = -cos(degree2) * 1.05;
  lbspeed_ = cos(degree2) * 1.01;
  rbspeed_ = -cos(degree1);


  rate = speede_ / (max(max(abs(lfspeed_), abs(rfspeed_)), max(abs(lbspeed_), abs(rbspeed_))));


  lfspeed_ = rate * lfspeed_ - cmps / 4;
  rfspeed_ = rate * rfspeed_ - cmps / 4;
  lbspeed_ = rate * lbspeed_ - cmps / 4;
  rbspeed_ = rate * rbspeed_ - cmps / 4;

  //assuming that a = 0, b = 1 is positive, a = 1, b = 0 is(changed
  if (lfspeed_ == 0) {
    digitalWrite(lfa, 0);
    digitalWrite(lfb, 0);
    analogWrite(plf, 10);
  } else {
    digitalWrite(lfa, int(lfspeed_ / abs(lfspeed_) * -0.5 + 0.5));
    digitalWrite(lfb, int(lfspeed_ / abs(lfspeed_) * 0.5 + 0.5));
    analogWrite(plf, abs(lfspeed_));
  }

  if (lbspeed_ == 0) {
    digitalWrite(lba, 0);
    digitalWrite(lbb, 0);
    analogWrite(plb, 10);
  } else {
    digitalWrite(lba, int(lbspeed_ / abs(lbspeed_) * -0.5 + 0.5));
    digitalWrite(lbb, int(lbspeed_ / abs(lbspeed_) * 0.5 + 0.5));
    analogWrite(plb, abs(lbspeed_));
  }

  if (rfspeed_ == 0) {
    digitalWrite(rfa, 0);
    digitalWrite(rfb, 0);
    analogWrite(prf, 10);
  } else {
    digitalWrite(rfa, int(rfspeed_ / abs(rfspeed_) * -0.5 + 0.5));
    digitalWrite(rfb, int(rfspeed_ / abs(rfspeed_) * 0.5 + 0.5));
    analogWrite(prf, abs(rfspeed_));
  }

  if (rbspeed_ == 0) {
    digitalWrite(rba, 0);
    digitalWrite(rbb, 0);
    analogWrite(prb, 10);
  } else {
    digitalWrite(rba, int(rbspeed_ / abs(rbspeed_) * -0.5 + 0.5));
    digitalWrite(rbb, int(rbspeed_ / abs(rbspeed_) * 0.5 + 0.5));
    analogWrite(prb, abs(rbspeed_));
  }

  // Serial.print(lfspeed_);
  // Serial.print(" ");
  // Serial.print(lbspeed_);
  // Serial.print(" ");
  // Serial.print(rfspeed_);
  // Serial.print(" ");
  // Serial.println(rbspeed_);
}

void test() {
  digitalWrite(lfa, 1);
  digitalWrite(lfb, 0);

  analogWrite(plf, 30);

  digitalWrite(lba, 1);
  digitalWrite(lbb, 0);

  analogWrite(plb, 30);

  digitalWrite(rfa, 1);
  digitalWrite(rfb, 0);

  analogWrite(prf, 30);

  digitalWrite(rba, 1);
  digitalWrite(rbb,0);

  analogWrite(prb, 30);
}

void find_ang(float fix) {
  if (b_value > 55) {
    degree2 = abs(degree);
    if (degree2 != 0) {
      angle = (int)(degree2 + b_value * fix);
      while (angle > 180) {
        angle = angle - 360;
      }
      if (degree < 0) {
        angle = -angle;
      }
    } else {
      angle = 0;
    }
  } else {
    angle = degree;
  }
}

void slow_move_ang(int speede_, float angle) {
  //assuming that clockwise
  angle1 = (angle - 45) / 180 * 3.1415926;
  angle2 = (angle + 45) / 180 * 3.1415926;

  lfspeed_ = cos(angle1) * 1.04;
  rfspeed_ = -cos(angle2) * 1.05;
  lbspeed_ = cos(angle2) * 1.01;
  rbspeed_ = -cos(angle1);
  rate = speede_ / (max(max(abs(lfspeed_), abs(rfspeed_)), max(abs(lbspeed_), abs(rbspeed_))));
  lfspeed_ = rate * lfspeed_ - cmps / 12;
  rfspeed_ = rate * rfspeed_ - cmps / 12;
  lbspeed_ = rate * lbspeed_ - cmps / 12;
  rbspeed_ = rate * rbspeed_ - cmps / 12;
  //assuming that a = 0, b = 1 is positive, a = 1, b = 0 is(changed
  if (lfspeed_ == 0) {
    digitalWrite(lfa, 0);
    digitalWrite(lfb, 0);
    analogWrite(plf, 10);
  } else {
    digitalWrite(lfa, int(lfspeed_ / abs(lfspeed_) * -0.5 + 0.5));
    digitalWrite(lfb, int(lfspeed_ / abs(lfspeed_) * 0.5 + 0.5));
    analogWrite(plf, abs(lfspeed_));
  }

  if (lbspeed_ == 0) {
    digitalWrite(lba, 0);
    digitalWrite(lbb, 0);
    analogWrite(plb, 10);
  } else {
    digitalWrite(lba, int(lbspeed_ / abs(lbspeed_) * -0.5 + 0.5));
    digitalWrite(lbb, int(lbspeed_ / abs(lbspeed_) * 0.5 + 0.5));
    analogWrite(plb, abs(lbspeed_));
  }

  if (rfspeed_ == 0) {
    digitalWrite(rfa, 0);
    digitalWrite(rfb, 0);
    analogWrite(prf, 10);
  } else {
    digitalWrite(rfa, int(rfspeed_ / abs(rfspeed_) * -0.5 + 0.5));
    digitalWrite(rfb, int(rfspeed_ / abs(rfspeed_) * 0.5 + 0.5));
    analogWrite(prf, abs(rfspeed_));
  }

  if (rbspeed_ == 0) {
    digitalWrite(rba, 0);
    digitalWrite(rbb, 0);
    analogWrite(prb, 10);
  } else {
    digitalWrite(rba, int(rbspeed_ / abs(rbspeed_) * -0.5 + 0.5));
    digitalWrite(rbb, int(rbspeed_ / abs(rbspeed_) * 0.5 + 0.5));
    analogWrite(prb, abs(rbspeed_));
  }

  analogWrite(plf, abs(lfspeed_));
  analogWrite(plb, abs(lbspeed_));
  analogWrite(prf, abs(rfspeed_));
  analogWrite(prb, abs(rbspeed_));
}

void move_ang(int speede_, float angle) {
  //assuming that clockwise
  angle1 = (angle - 45) / 180 * 3.1415926;
  angle2 = (angle + 45) / 180 * 3.1415926;

  lfspeed_ = cos(angle1) * 1.04;
  rfspeed_ = -cos(angle2) * 1.05;
  lbspeed_ = cos(angle2) * 1.01;
  rbspeed_ = -cos(angle1);



  rate = speede_ / (max(max(abs(lfspeed_), abs(rfspeed_)), max(abs(lbspeed_), abs(rbspeed_))));



  lfspeed_ = rate * lfspeed_ - cmps / 5;
  rfspeed_ = rate * rfspeed_ - cmps / 5;
  lbspeed_ = rate * lbspeed_ - cmps / 5;
  rbspeed_ = rate * rbspeed_ - cmps / 5;



  //assuming that a = 0, b = 1 is positive, a = 1, b = 0 is(changed

  if (lfspeed_ == 0) {
    digitalWrite(lfa, 0);
    digitalWrite(lfb, 0);
    analogWrite(plf, 10);
  } else {
    digitalWrite(lfa, int(lfspeed_ / abs(lfspeed_) * -0.5 + 0.5));
    digitalWrite(lfb, int(lfspeed_ / abs(lfspeed_) * 0.5 + 0.5));
    analogWrite(plf, abs(lfspeed_));
  }

  if (lbspeed_ == 0) {
    digitalWrite(lba, 0);
    digitalWrite(lbb, 0);
    analogWrite(plb, 10);
  } else {
    digitalWrite(lba, int(lbspeed_ / abs(lbspeed_) * -0.5 + 0.5));
    digitalWrite(lbb, int(lbspeed_ / abs(lbspeed_) * 0.5 + 0.5));
    analogWrite(plb, abs(lbspeed_));
  }

  if (rfspeed_ == 0) {
    digitalWrite(rfa, 0);
    digitalWrite(rfb, 0);
    analogWrite(prf, 10);
  } else {
    digitalWrite(rfa, int(rfspeed_ / abs(rfspeed_) * -0.5 + 0.5));
    digitalWrite(rfb, int(rfspeed_ / abs(rfspeed_) * 0.5 + 0.5));
    analogWrite(prf, abs(rfspeed_));
  }

  if (rbspeed_ == 0) {
    digitalWrite(rba, 0);
    digitalWrite(rbb, 0);
    analogWrite(prb, 10);
  } else {
    digitalWrite(rba, int(rbspeed_ / abs(rbspeed_) * -0.5 + 0.5));
    digitalWrite(rbb, int(rbspeed_ / abs(rbspeed_) * 0.5 + 0.5));
    analogWrite(prb, abs(rbspeed_));
  }

  analogWrite(plf, abs(lfspeed_));
  analogWrite(plb, abs(lbspeed_));
  analogWrite(prf, abs(rfspeed_));
  analogWrite(prb, abs(rbspeed_));
}