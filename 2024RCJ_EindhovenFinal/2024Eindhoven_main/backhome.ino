void backhome() {
  if (Sb > 180) {  //use back sonic to move(forward)
    if (Sl < 115) {
      back_degree = atan((Sb - 170) / (130 - Sl)) / 3.1416 * 180;
      degree = back_degree + 90;
    } else if (Sr < 115) {  //use back sonic to move(backward)
      back_degree = atan((Sb - 170) / (130 - Sr)) / 3.1416 * 180;
      degree = -90 - back_degree;
    } else {
      degree = 180;
    }
  } else {
    if (Sl < 130) {
      degree = atan((150 - Sb) / (130 - Sl)) / 3.1416 * 180;
    } else if (Sr < 130) {  //use back sonic to move(backward)
      degree = -atan((150 - Sb) / (130 - Sr)) / 3.1416 * 180;
    } else {
      if (Sb > 140) {
        backed = 1;
      } else {
        degree = 0;
      }
    }
  }
}

void backhome2() {
  Serial.println(Sr);
  if (Sr < 200) {
    degree = -90;
    backed = 0;
  } else {
    degree = 90;
    backed = 1;
  }
}
