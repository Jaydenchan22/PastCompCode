int frontIR_n, backIR_n, frontIR_v, backIR_v;
int Sf, Sb, Sl, Sr;
int lfa = 13;
int lfb = 12;

int plf = 5;

int lba = 7;
int lbb = 6;

int plb = 4;

int rfa = 10;
int rfb = 11;

int prf = 2;

int rba = 8;
int rbb = 9;

int prb = 3;
int start = 0;
int backed = 0;
int back_degree;
float chasespeed, closevalue;

int checkGf, checkGl, checkGr, checkGb;
int direction_, determine;
int i, j, k;
int checksum = 0;
int x_, y_;
float lfspeed_;
float rfspeed_;
float lbspeed_;
float rbspeed_;
int degree;
float rate;
int sumCL = 0;
int CL_stop = 0;
float degree1, degree2;
float angle, angle1, angle2;
float b_value;
float cmps;
float close_value;
int near = 0;
int near_c = 0;
int have_b = 0;
int count_k;

void setup() {
  pinMode(lfa, OUTPUT);
  pinMode(lfb, OUTPUT);
  pinMode(lba, OUTPUT);
  pinMode(lbb, OUTPUT);
  pinMode(rfa, OUTPUT);
  pinMode(rfb, OUTPUT);
  pinMode(rba, OUTPUT);
  pinMode(rbb, OUTPUT);

  // pinMode(12, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(3, CLGf, RISING);
  attachInterrupt(2, CLGl, RISING);
  attachInterrupt(4, CLGr, RISING);
  attachInterrupt(5, CLGb, RISING);
}

void loop() {
  GetCompoI3(14, 25, 24);
  GetCompoI3(14, 23, 22);
  frontIR_n = GetCompoI3(8, 25, 24);
  frontIR_v = GetCompoI3(9, 25, 24);
  backIR_n = GetCompoI3(8, 23, 22);
  backIR_v = GetCompoI3(9, 23, 22);

  Sf = analogRead(A2);
  if (analogRead(A0) < 400) {
    Sl = analogRead(A0);
  }
  if (analogRead(A6) < 400) {
    Sr = analogRead(A6);
  }
  Sb = analogRead(A4);

  sumCL = checkGf + checkGl + checkGb + checkGr;
  // Serial.println(sumCL);
  cmps = GetCompass(31, 30);
  while (cmps > 360) {
    cmps = cmps - 360;
  }
  if (cmps > 180) {
    cmps = -360 + cmps;
  }

  findball();
  if (b_value > 100 && degree == 0) {
    near = 1;
  }
  if (near == 1) {
    digitalWrite(29, 1);
    if (near_c < 200) {
      near_c += 1;
    }
  }else
  {
    digitalWrite(29,0);
  }

  if (have_b == 0) {
    if (near_c < 200) {
      find_ang(0.7);
      move_ang(20, angle);
    } else {
      have_b = 1;
    }
  } else {
    if (Sb > 90 || abs(cmps) > 20) {
      if (abs(cmps) < 20) {
        move_ang(20, 180);
      } else {
        slow_move_ang(18, 0);
      } 
    } else {
      test();
      delay(500);     
      near = 0;
    }
  }
}
