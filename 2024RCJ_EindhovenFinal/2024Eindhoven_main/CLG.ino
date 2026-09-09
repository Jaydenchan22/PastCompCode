void CLGf()
{
  checkGf = 1;
}
void CLGl()
{
  checkGl = 2;
}
void CLGr()
{
  checkGr = 4;
}
void CLGb()
{
  checkGb = 8;
}

void reseting(){
  if(Sf > 80){
    checkGf = 0;
  }
  if(Sl > 40){
    checkGl = 0;
  }
  if(Sr > 40){
    checkGr = 0;
  }
  if(Sb > 80){
    checkGb = 0;
  }
}
