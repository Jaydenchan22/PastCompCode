int front_(int speed_){
  digitalWrite(lfa, 0);
  digitalWrite(lfb, 1);
  digitalWrite(lba, 1);
  digitalWrite(lbb, 0);
  digitalWrite(rfa, 1);
  digitalWrite(rfb, 0);
  digitalWrite(rba, 1);
  digitalWrite(rbb, 0);
  analogWrite(plf, speed_);
  analogWrite(plb, speed_);
  analogWrite(prf, speed_);
  analogWrite(prb, speed_);
}

int back_(int speed_){
  digitalWrite(lfa, 0);
  digitalWrite(lfb, 1);
  digitalWrite(lba, 0);
  digitalWrite(lbb, 1);
  digitalWrite(rfa, 0);
  digitalWrite(rfa, 1);
  digitalWrite(rba, 1);
  digitalWrite(rba, 0);
  analogWrite(plf, speed_);
  analogWrite(plb, speed_);
  analogWrite(prf, speed_);
  analogWrite(prb, speed_);
}

int left_(int speed_){
  digitalWrite(lfa, 1);
  digitalWrite(lfb, 0);
  digitalWrite(lba, 0);
  digitalWrite(lbb, 1);
  digitalWrite(rfa, 0);
  digitalWrite(rfa, 1);
  digitalWrite(rba, 0);
  digitalWrite(rba, 1);
  analogWrite(plf, speed_);
  analogWrite(plb, speed_);
  analogWrite(prf, speed_);
  analogWrite(prb, speed_);
}

int right_(int speed_){
  digitalWrite(lfa, 0);
  digitalWrite(lfb, 1);
  digitalWrite(lba, 1);
  digitalWrite(lbb, 0);
  digitalWrite(rfa, 1);
  digitalWrite(rfa, 0);
  digitalWrite(rba, 1);
  digitalWrite(rba, 0);
  analogWrite(plf, speed_);
  analogWrite(plb, speed_);
  analogWrite(prf, speed_);
  analogWrite(prb, speed_);
}

int stop_(){
  digitalWrite(lfa, 0);
  digitalWrite(lfb, 0);
  digitalWrite(lba, 0);
  digitalWrite(lbb, 0);
  digitalWrite(rfa, 0);
  digitalWrite(rfa, 0);
  digitalWrite(rba, 0);
  digitalWrite(rba, 0);
  analogWrite(plf, 10);
  analogWrite(plb, 10);
  analogWrite(prf, 10);
  analogWrite(prb, 10);
}

int right_cyc(int speed_){
  digitalWrite(lfa, 0);
  digitalWrite(lfb, 1);
  digitalWrite(lba, 1);
  digitalWrite(lbb, 0);
  digitalWrite(rfa, 1);
  digitalWrite(rfa, 0);
  digitalWrite(rba, 1);
  digitalWrite(rba, 0);
  analogWrite(plf, speed_/4);
  analogWrite(plb, speed_);
  analogWrite(prf, speed_/4);
  analogWrite(prb, speed_);
}