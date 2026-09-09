/*
Inter-Integrated Circuit

I²C uses only two bidirectional open-drain lines, Serial Data Line (SDA) and
Serial Clock (SCL), pulled up with resistors. Typical voltages used are +15 V 
or +3.3 V although systems with other voltages are permitted.
The I²C reference design has a 7-bit or a 10-bit (depending on the device used)
address space[5]. Common I²C bus speeds are the 100 kbit/s standard mode and
the 10 kbit/s low-speed mode, but arbitrarily low clock frequencies are also
allowed.

Recent revisions of I²C can host more nodes and run at faster speeds (600 kbit/s 
Fast mode, 1 Mbit/s Fast mode plus or Fm+, and 3.4 Mbit/s High Speed mode). 
These speeds are more widely used on embedded systems than on PCs. There are
alsoother features, such as 16-bit addressing.

There are a number of hardware solutions for host computers, running Linux,
Mac orWindows, I²C master and/or slave capabilities. Most of them are based 
on Universal Serial Bus (USB) to I²C adapters. Not all of them require 
proprietary drivers or APIs.

We made an Arduino verson at 31/05/2011.
*/
//#include<Arduino.h>
/*-----------------------------------Soft_I2C_Start-------------------------------------------------*/
void Soft_I2C_Start(unsigned char SDA,unsigned char SCL)
{ 
  pinMode(SDA,OUTPUT);
  digitalWrite(SDA,HIGH);
  pinMode(SCL,OUTPUT);
  digitalWrite(SCL,HIGH);
  digitalWrite(SDA,LOW);
  digitalWrite(SCL,LOW);
}

void Soft_I2C_Stop(unsigned char SDA,unsigned char SCL)
{
  pinMode(SDA,OUTPUT);
  pinMode(SCL,OUTPUT);
  digitalWrite(SDA,LOW);
  digitalWrite(SCL,HIGH);
  digitalWrite(SDA,HIGH);
  digitalWrite(SCL,LOW);
}

unsigned char Soft_I2C_Write(unsigned char wb,unsigned char SDA,unsigned char SCL)
{  //wb:0~7(R/W)8
  unsigned char ack=0,SDA_Read;
  int i;
  pinMode(SDA,OUTPUT);
  pinMode(SCL,OUTPUT);
  for(i=0;i<8;i++)
  {       //0~7 ;
    if( wb&0x80 )          
      digitalWrite(SDA,HIGH);          
    else
      digitalWrite(SDA,LOW);
    wb=wb<<1;
    digitalWrite(SCL,HIGH);
    digitalWrite(SCL,LOW);
  }
 //---------------------------------------------------------------------------------------------------------------------
  pinMode(SDA,INPUT);
  digitalWrite(SCL,HIGH);
  if(digitalRead(SDA))
    ack=0;
  else
    ack=1;
  digitalWrite(SCL,LOW);
  return ack;
}
/*-------------------------------------------------------------------------------------------------*/
 
/*-------------------------------Soft_I2C_Read-----------------------------------------------------*/
unsigned char Soft_I2C_Read(unsigned char bEnd,unsigned char SDA,unsigned char SCL)
{
  unsigned char i,mb;
  mb=0;
  pinMode(SDA,INPUT);
  pinMode(SCL,OUTPUT);
  for(i=0;i<8;i++)
  {
    digitalWrite(SCL,LOW);
    digitalWrite(SCL,HIGH);
    mb=mb<<1;  
    if(digitalRead(SDA))
      mb++;
  }
  digitalWrite(SCL,LOW);
  pinMode(SDA,OUTPUT);
  if(bEnd)
    digitalWrite(SDA,HIGH);
  else
    digitalWrite(SDA,LOW); 
  digitalWrite(SCL,HIGH);
  digitalWrite(SCL,LOW);
  return mb;
}
/*-------------------------------------------------------------------------------------------------*/

//---------------------------------------------------------------------------------------------------C--O--M--P--A--S--S--------------------*/
unsigned int GetCompass(unsigned char SDA,unsigned char SCL)
{
  unsigned char low;
  unsigned char high;
  unsigned int angle;
  
  Soft_I2C_Start(SDA ,SCL);//S 
  
  Soft_I2C_Write(0x76, SDA, SCL);//1110110
  Soft_I2C_Write(0x01, SDA, SCL);//0000001
  
  Soft_I2C_Start(SDA,SCL);//Sr
  
  Soft_I2C_Write(0x77, SDA, SCL);//1110111
  
  high=Soft_I2C_Read(0, SDA, SCL);
  low=Soft_I2C_Read(1, SDA, SCL);
  
  Soft_I2C_Stop(SDA,SCL);
  
  if(high==1)
  angle=256+low;
  else
  if(high==0)
  angle=low;
  else
  angle=9999;
  return angle;
}

//---------------------------------------------------------------------------------------------------C--O--M--P--O--I--3--------------------
/*
1~7---value of no1~7
8---max_no
9---max_value
10---min_no
11---min_value
12---average_value
13---B mode
14---A mode
15---don't use
*/
unsigned int GetCompoI3(unsigned char command, unsigned char SDA, unsigned char SCL)
{
  unsigned char m_temp,m_fix;
  if( command <= 7)
  {
    switch(command)
    {
    case 1:m_fix = 4;
    break;
        case 2:m_fix = 3;
    break;
    case 3:m_fix = 2;
    break;
    case 4:m_fix = 1;
    break;
    case 5:m_fix = 7;
    break;
    case 6:m_fix = 6;
    break;
    case 7:m_fix = 5;
    break;
    }
  }
  else
  {
    m_fix = command;
  }
  
  Soft_I2C_Start(SDA, SCL);
  Soft_I2C_Write(0x02, SDA, SCL);
  Soft_I2C_Write(m_fix, SDA, SCL);
  Soft_I2C_Stop(SDA, SCL);
  Soft_I2C_Start(SDA, SCL);
  Soft_I2C_Write(0x03, SDA, SCL);     
  m_temp=Soft_I2C_Read(1, SDA, SCL);
  Soft_I2C_Stop( SDA, SCL); 
  
  if(m_fix == 8)
   {
   if(m_temp==255)return 255;
   return (8-m_temp);
   }
  else
   {
   return m_temp;
   }
}

/*
  KS103 Ultra Sonic

 Ranging with temperature revised, high precision in distance 
 Range in 1cm to 650cm, using patent technologies(KS103/KS103S range in 1cm to 550cm) 
 Detecting frequency up to 500Hz, which can detect 500 times per second 
 Use slave I2C bus, detect master’s command automatically 
 20 I2C address and can be changed, the address is 0xd0-0xfe (except 0xf0,0xf2,0xf4,0xf6) 
 Broadcast address 0x00 allowed(except KS103/KS103S)
 Short and high precision temperature detect of 83ms each time 
 Sleep automatically after 5s without commands, wake up by master at any time 
 Short range in 10cm, 20cm to 470cm, 47 steps total 
 1ms in light intensity detect. Special command for light intensity detect 
 Industrial and Extended Temperature range(-30 ~+85 ) ℃ ℃ (KS103/KS103S work in 0~70 ) ℃
 Wide operating voltage range (3.0V~5.5V) 
 Unique filtering noise reduction technology, can still work under noisy power suppl
*/

void write_byte(unsigned char address,unsigned char reg,unsigned char command,char SDA,char SCL) //address+register+command
{
  Soft_I2C_Start(SDA,SCL);
  Soft_I2C_Write(address,SDA,SCL);
  Soft_I2C_Write(reg,SDA,SCL);
  Soft_I2C_Write(command,SDA,SCL);
  Soft_I2C_Stop(SDA,SCL);
}

unsigned char read_byte(unsigned char address,unsigned char reg,char SDA,char SCL) //address(with bit 0 set) + register
{
  unsigned char dat;
  Soft_I2C_Start(SDA,SCL);
  Soft_I2C_Write(address,SDA,SCL);
  Soft_I2C_Write(reg,SDA,SCL);
  Soft_I2C_Start(SDA,SCL);
  Soft_I2C_Write(address+1,SDA,SCL);
  delayMicroseconds(6000);
  dat=Soft_I2C_Read(1, SDA, SCL);
  Soft_I2C_Stop(SDA,SCL);
  return dat;
}

unsigned int detect(unsigned char address,unsigned char command,char SDA,char SCL) //0xe8(address) + 0xb0(command)
{
  unsigned int distance=0,count;
  write_byte(address,2,command,SDA,SCL);
  digitalWrite(SCL,1);
   while(!digitalRead(SCL));
  distance=read_byte(address,2,SDA,SCL);
  distance <<= 8;
  distance += read_byte(address,3,SDA,SCL);
  return distance/10; 
}
//-----------------------------------------------------------------------------------------------------L--C--D--Monitor----------------
void Set_Monitor()
{
  //mon setup
  /*pinMode(44,OUTPUT);  digitalWrite(44,HIGH); //MON BACK LIGHT POWER+
  pinMode(42,OUTPUT);  digitalWrite(42,LOW); //MON BACK LIGHT POWER- 
  pinMode(51,OUTPUT);  digitalWrite(51,HIGH); //MON POWER+
  pinMode(53,OUTPUT);  digitalWrite(53,LOW); //MON POWER-
  
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(47, 45, 43, 52, 50, 48, 46);
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); */
  //end of setting of monitor
}
//-----------------------------------------------------------------------------------------------------S--R--F--05----------------
unsigned int get_sonic(unsigned char pin)
{
  // trig pin
  // echo pin-1
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10); // send the sensor a 10 microsecond pulse:
  digitalWrite(pin, LOW);

  // wait for the pulse to return. The pulse
  // goes from low to HIGH to low, so we specify
  // that we want a HIGH-going pulse below:
  unsigned long pulse_length = pulseIn(pin-1, HIGH,7500);

  // can't send more than one pulse each 50 ms or
  // we could get interference
  //delay(50);

  // convert to inches and return
  return( (unsigned int) (pulse_length)/80 );
} 

