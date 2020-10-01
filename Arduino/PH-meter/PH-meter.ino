
/*******************************************************************************


 ********************************************************************************
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneButton.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

//#define DEBUG 1

#define PH_SENSOR_PIN           A1
#define AVG_ARRAY_SIZE          9
#define DELAY_BETWEEN_SAMPLES   20 //ms
#define VOLTAGE                 5  //V
#define VOLTAGE_REF             1023
#define MENUENTRYS 7
#define ECA 4
#define ECB 5
#define FANPIN 6
const size_t sf =sizeof(float);

const int T1pin = A0;
const int T2pin = A2;


#define R251  100000.0f//NTC1 R at 25C
#define R1a   82000.0f//R1 pullup
#define R252  10000.0f//NTC2 R at 25C
#define R2a   15000.0f//R2 pullup
#define b1    3950.0f//temperature coeffitient for ntc1
#define b2    3435.0f//temperature coeffitient for ntc2

float steigung = -1.0f;
float achsenabschnitt = 0.0f;

float xph4=5.0f;
float xph7=2.5f;
float xph9=0.833f;

float yph4=4.0f;
float yph7=6.86f;
float yph9=9.0f;

uint32_t avgValue   = 0;
uint32_t avgValueT1 = 0;
uint32_t avgValueT2 = 0;
uint16_t analogValBuf[AVG_ARRAY_SIZE];
uint16_t analogValBufT1[AVG_ARRAY_SIZE];
uint16_t analogValBufT2[AVG_ARRAY_SIZE];
uint8_t actualIdx    = 0;
uint8_t actualIdx1   = 0;
uint8_t actualIdx2   = 0;
bool firstSampling   = true;
bool firstSamplingT1 = true;
bool firstSamplingT2 = true;
float sensorVoltage;
float phValue;
int menu=0;
int amenu=0; 
int fanspeed=0;
OneButton menuButton(12, true);
OneButton okButton  (11, true);

bool yes=false;//OK button
bool info=true;//verbose extra info on display
bool measureEC=true;//enable EC measurement

void fillBuffer();
void getFloatingAvg();
void sampling();

////////////////////////////////////////////////////////////////////////////////////////
void regression(bool store){
  float sx2 = xph4 * xph4 + xph7 * xph7 + xph9 * xph9;//Summe x^2
  float sx  = xph4 + xph7 + xph9;// Summe x
  float sy  = yph4 + yph7 + yph9;// Summe y
  //float sy2=;
  float sxy =  xph4 * yph4 +xph7 * yph7 + xph9 * yph9;//Summe x*y
  steigung = (3 * sxy - sx * sy) / (3 * sx2 - sx * sx);
  achsenabschnitt = (sx2 * sy - sx * sxy) / (3 * sx2 - sx * sx);
  lcd.clear();
  lcd.setCursor(0, 0);    
  lcd.print("m * x + b ="); 
  lcd.setCursor(0, 1);
  lcd.print(steigung,3);   
  lcd.print(" * x + "); 
  lcd.print(achsenabschnitt,3);  
  lcd.setCursor(0, 3);  
  lcd.print("[OK]");
  while (!yes) {
    delay(1);    
    menuButton.tick();
    okButton.tick();
  }
  yes=false;
  if (store){
    EEPROM.put(sf * 0, xph4);  
    EEPROM.put(sf * 1, xph7);
    EEPROM.put(sf * 2, xph9);
  }
}

void calibComm(int ph){
  yes=false;
  lcd.clear();
  //lcd.print("01234567890123456789  //20 Zeichen
  lcd.setCursor(0, 0);  
  lcd.print("Bitte pH-Sonde mit");
  lcd.setCursor(0, 1);  
  lcd.print("demin. H2O sp");lcd.printByte(245);
  lcd.print("hlen");
  lcd.setCursor(0, 2);  
  lcd.print("und in pH");
  lcd.print(ph);
  lcd.print("Lsg.");
  lcd.setCursor(0, 3);  
  lcd.print("eintauchen [OK]");
  while (!yes) {
    fillBuffer();
    menuButton.tick();
    okButton.tick();
  }
  yes=false;
  while (!yes) {
    sampling();
    sensorVoltage = (float)avgValue * VOLTAGE / VOLTAGE_REF;
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("Volt = ");
    lcd.print(sensorVoltage,3);
    lcd.setCursor(0, 1);  
    lcd.print("[OK] ");
    delay(200);
    menuButton.tick();
    okButton.tick();
  }
  yes=false;
}

void calib_pH4(){
  calibComm(4);
  xph4=sensorVoltage;
  regression(true);
}

void calib_pH7(){
  calibComm(7);//6.86
  xph7=sensorVoltage;
  regression(true);
}

void calib_pH9(){
  calibComm(9);
  xph9=sensorVoltage;
  regression(true);
}


//fill whole floating average buffer, it is used only at start (empty buffer) 
void fillBuffer(){
  for (int i = 0; i < AVG_ARRAY_SIZE; i++) {
    analogValBuf[i] = analogRead(PH_SENSOR_PIN);
    delay(DELAY_BETWEEN_SAMPLES);
  }
}

void fillBufferT1(){
  for (int i = 0; i < AVG_ARRAY_SIZE; i++) {
    analogValBufT1[i] = analogRead(T1pin);
    delay(DELAY_BETWEEN_SAMPLES);
  }
}

void fillBufferT2(){
  for (int i = 0; i < AVG_ARRAY_SIZE; i++) {
    analogValBufT2[i] = analogRead(T2pin);
    delay(DELAY_BETWEEN_SAMPLES);
  }
}

//calculate actual value of floating average
void getFloatingAvg(){
  avgValue=0;
  for (int i = 0; i < AVG_ARRAY_SIZE; i++){
    avgValue += analogValBuf[i];
  }
  avgValue = avgValue / AVG_ARRAY_SIZE;
}


void getFloatingAvgT1(){
  avgValueT1=0;
  for (int i = 0; i < AVG_ARRAY_SIZE; i++){
    avgValueT1 += analogValBufT1[i];
  }
  avgValueT1 = avgValueT1 / AVG_ARRAY_SIZE;
}

void getFloatingAvgT2(){
  avgValueT2=0;
  for (int i = 0; i < AVG_ARRAY_SIZE; i++){
    avgValueT2 += analogValBufT2[i];
  }
  avgValueT2 = avgValueT2 / AVG_ARRAY_SIZE;
}

//when function is called one sample is grabbed
void sampling(){
  if(firstSampling){
    fillBuffer();
    getFloatingAvg();
    firstSampling = !firstSampling;
  }
  else{    
    analogValBuf[actualIdx] = analogRead(PH_SENSOR_PIN);
    getFloatingAvg();
    actualIdx++;
    actualIdx%=AVG_ARRAY_SIZE;
  }
}

void samplingT1(){
  if(firstSamplingT1){
    fillBufferT1();
    getFloatingAvgT1();
    firstSamplingT1 = !firstSamplingT1;
  }
  else{    
    analogValBufT1[actualIdx1] = analogRead(T1pin);
    getFloatingAvgT1();
    actualIdx1++;
    actualIdx1%=AVG_ARRAY_SIZE;

  }
}

void samplingT2(){
  if(firstSamplingT2){
    fillBufferT2();
    getFloatingAvgT2();
    firstSamplingT2 = !firstSamplingT2;
  }
  else{    
    analogValBufT2[actualIdx2] = analogRead(T2pin);
    getFloatingAvgT2();
    actualIdx2++;
    actualIdx2%=AVG_ARRAY_SIZE;

  }
}

void doMenuClick(){
  menu++;
  menu%=MENUENTRYS;
}

void doMenuDClick(){
  menu+=MENUENTRYS;//this way menu never gets negative
  menu--;  
  menu%=MENUENTRYS;
}

void doOKClick(){
  yes=true;  
}

void setup() {
#ifdef DEBUG  
  Serial.begin(9600);
#endif

  EEPROM.get(sf * 0, xph4);  
  EEPROM.get(sf * 1, xph7);
  EEPROM.get(sf * 2, xph9);
  regression(false);
  //analogReference(EXTERNAL);// use this if you use AREF pin
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();//can't see without
  lcd.noAutoscroll();
  uint8_t temp[8]  = {0x4,  0xa,  0xa, 0xa, 0xa, 0x11, 0x11, 0xe};
  uint8_t deg[8]   = {0xc, 0x12, 0x12, 0xc,  0x0,  0x0, 0x0, 0x0};
  uint8_t copy[8]  = {0xc, 0x10, 0x10, 0xc,  0x0,  0x5, 0x7, 0x5};
  lcd.createChar(4, temp);//thermometer symbol
  lcd.createChar(1, deg);//degree
  lcd.createChar(2, copy);//CH
  lcd.setCursor(0, 0);
  pinMode(ECA, OUTPUT);
  pinMode(ECB, OUTPUT);
  digitalWrite(ECA, LOW);
  digitalWrite(ECB, LOW);
  lcd.clear();
  menuButton.attachClick(doMenuClick);
  okButton.attachClick(doOKClick);
  menuButton.attachDoubleClick(doMenuDClick);
}

float conductivity(){
  float rs=2200*2;
  int a6=0,a7=0;
  unsigned long diff1=0;
  for (int i=0; i<100; i++){
    digitalWrite(ECA, HIGH);
    digitalWrite(ECB, LOW);
    delayMicroseconds(75);//50mus
    a6 = analogRead(A6);//100mus
    a7 = analogRead(A7);//100mus
    diff1+=abs(a6-a7);


    digitalWrite(ECA, LOW);
    digitalWrite(ECB, HIGH);
    delayMicroseconds(75);//50mus
    a6 = analogRead(A6);//100mus
    a7 = analogRead(A7);//100mus
    diff1+=abs(a6-a7);
  }  // 1/(550)us = 1.8kHz

  float r1 = (1023.0/(1023-((float)diff1/200.0)) - 1.0) *  rs;    
  digitalWrite(ECA, LOW);
  digitalWrite(ECB, LOW);
  return 1/r1 * 1000000;
}

void loop() {
  unsigned long nowis = millis();
  static unsigned long nextDispTime = 0ul;

  menuButton.tick();
  okButton.tick();
  if (menu==0)if ((nowis - nextDispTime) > 500ul) {

    sampling();
    sensorVoltage = (float)avgValue * VOLTAGE / VOLTAGE_REF;
    phValue = steigung * sensorVoltage + achsenabschnitt;
#ifdef DEBUG  
    Serial.print(F("pH value: "));
    Serial.println(phValue);
#endif  
    //lcd.clear();
    if (menu!=amenu) lcd.clear();
    samplingT1();
    samplingT2();
    //float R1 =  0.0f;
    //float R2 =  0.0f;
    float R1=(1023.0/(1023-((float)avgValueT1)) - 1.0) * R1a ;
    float R2=(1023.0/(1023-((float)avgValueT2)) - 1.0) * R2a;
    lcd.setCursor(0, 0);
    lcd.print(F("pH: "));
    lcd.print(phValue);
    lcd.print(F("  "));
    if (info) 
    {
      lcd.print(avgValue);
      lcd.setCursor(0, 1);
      lcd.print((R1 > 1000) ? ((R1 > 1000000) ? 0.000001 * R1 : 0.001 * R1) : R1, 1);
      lcd.print((R1 > 1000) ? ((R1 > 1000000) ? "M" : "k") : "");  
      lcd.printByte(0xf4);//Omega 
      lcd.print(F(" "));
      lcd.print((R2 > 1000) ? ((R2 > 1000000) ? 0.000001 * R2 : 0.001 * R2) : R2, 1);
      lcd.print((R2 > 1000) ? ((R2 > 1000000) ? "M" : "k") : "");  
      lcd.printByte(0xf4);//Omega     
      lcd.print(F("   "));
    } 
    double t1 =  1.0/(log(R1/R251)/b1 + 1.0/298.15) -273.15;
    double t2 =  1.0/(log(R2/R252)/b2 + 1.0/298.15) -273.15;      


    lcd.setCursor(0, 3);  
    lcd.printByte(4);//temp
    lcd.print((t1+t2*5)/6.0);  //mehr Gewicht auf T2 da genauer
    lcd.printByte(1);//grad
    lcd.print("C");  
    lcd.print("   ");
    fanspeed = max((int)((((t1+t2*5)/6.0)-21)*44.0), 0);
    fanspeed = min(255, fanspeed);
    fanspeed = (fanspeed < 20)?0: fanspeed;
    analogWrite(FANPIN,fanspeed);
    if (info){
      lcd.print(fanspeed);   
      lcd.print(" ");
    }
    if (measureEC){
      lcd.setCursor(0, 2);  
      float ec=conductivity();
      if (ec>250){
        lcd.print(ec);
        lcd.printByte(228);
        lcd.print("S");  
        lcd.print("   ");
      } else if (info){
        lcd.print(avgValueT1);
        lcd.print(F(" "));
        lcd.print(avgValueT2);
        lcd.print(F(" "));
      }
    }
    nextDispTime = nowis; 
  }
  if (menu){
    if (menu!=amenu) lcd.clear();
    if (menu<5){
      lcd.setCursor(0, 0);  
      lcd.print((menu==1)?">":" ");
      lcd.print(F("Calibrate pH4 "));
      lcd.setCursor(0, 1); 
      lcd.print((menu==2)?">":" ");
      lcd.print(F("Calibrate pH7 "));
      lcd.setCursor(0, 2); 

      lcd.print((menu==3)?">":" ");
      lcd.print(F("Calibrate pH9 "));
      lcd.setCursor(0, 3); 
      lcd.print((menu==4)?">":" ");
      lcd.print(F("Fan full speed "));
    }else{
      lcd.setCursor(0, 0);  
      lcd.print((menu==3)?">":" ");
      lcd.print(F("Calibrate pH9 "));
      lcd.setCursor(0, 1); 
      lcd.print((menu==4)?">":" ");
      lcd.print(F("Fan full speed "));
      lcd.setCursor(0, 2); 
      lcd.print((menu==5)?">":" ");
      lcd.print(F("Debug info: "));
      lcd.print((info)?"[yes]":"[no]");
      lcd.setCursor(0, 3); 
      lcd.print((menu==6)?">":" ");
      lcd.print(F("Enable EC: "));
      lcd.print((measureEC)?"[yes]":"[no]");
    }//*/
    if(yes){
      switch (menu){
        case 1: calib_pH4();break;
        case 2: calib_pH7();break;        
        case 3: calib_pH9();break;        
        case 4: fanspeed=255;break;
        case 5: info=!info; break;
        case 6: measureEC=!measureEC;break;
        default: 
        lcd.clear();
        lcd.print(F("Not implementet yet!"));
        yes=false;
        while (!yes) okButton.tick();
      }
      fanspeed=max(fanspeed, 0);
      fanspeed%=256;
      if (fanspeed) fanspeed= (fanspeed<15)?15:fanspeed;
      //analogWrite(6,fanspeed);
      yes=false;
    }
    analogWrite(FANPIN,fanspeed);
    lcd.print(F(" "));
    lcd.print(fanspeed/2.55, 0); 
    lcd.print("% ");
  }
  amenu=menu;
}
