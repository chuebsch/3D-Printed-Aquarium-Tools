

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
#define AVG_ARRAY_SIZE          63
#define DELAY_BETWEEN_SAMPLES   23 //ms
#define VOLTAGE                 5  //V
#define VOLTAGE_REF             1023
#define MENUENTRYS              9
#define ECA                     4
#define ECB                     5
#define FANPIN                  6
#define RELAIS1                 9
#define RELAIS2                10
const byte sf =(byte) sizeof(float);

const byte T1pin = A0;
const byte T2pin = A2;


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
float pHmin=15.0f;
float pHmax=-1.0f;
float Tmin=50.0f;
float Tmax=-1.0f;

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
float ecValue=0.0;
byte menu             = 0;
byte amenu            = 0; 
uint16_t fanspeed     = 0;
OneButton menuButton(12, true);
OneButton okButton  (11, true);
unsigned long nextDispTime = 0ul;
unsigned long nextECTime = 0ul;
unsigned long mimapause = 0ul;

bool yes =            false;//OK button
bool info =           true;//verbose extra info on display
bool measureEC =      true;//enable EC measurementa
bool lcd_backlight =  true;//what to sleep at night turn off the light? 
bool blowFish =       true;//enable fan

void fillBuffer();
void getFloatingAvg();
void sampling();

////////////////////////////////////////////////////////////////////////////////////////
void regression(bool store){
  yes=false;
  float sx2 = xph4 * xph4 + xph7 * xph7 + xph9 * xph9;//Summe x^2
  float sx  = xph4 + xph7 + xph9;// Summe x
  float sy  = yph4 + yph7 + yph9;// Summe y
  //float sy2=;
  float sxy =  xph4 * yph4 +xph7 * yph7 + xph9 * yph9;//Summe x*y
  float nenner =  (3 * sx2 - sx * sx);
  if (nenner!=0.0f){ 
  steigung = (3 * sxy - sx * sy) / nenner;
  achsenabschnitt = (sx2 * sy - sx * sxy) / nenner;
  }else{ steigung = 1.0; achsenabschnitt = 0;}
  lcd.clear();
  lcd.setCursor(0, 0);    
  lcd.print("m * x + b ="); 
  lcd.setCursor(0, 1);
  lcd.print(steigung,3);   
  lcd.print(" * x + "); 
  lcd.print(achsenabschnitt,3);  
  lcd.setCursor(0, 3);  
  lcd.print("[OK]");
#ifdef DEBUG  
  Serial.print("X-PH4: ");Serial.println(xph4);
  Serial.print("X-PH7: ");Serial.println(xph7);
  Serial.print("X-PH9: ");Serial.println(xph9);
  Serial.print("Y-PH4: ");Serial.println(yph4);
  Serial.print("Y-PH7: ");Serial.println(yph7);
  Serial.print("Y-PH9: ");Serial.println(yph9);
  Serial.println("m * x + b ="); 
  Serial.print(steigung,3);
  Serial.print(" * x + ");
  Serial.print(achsenabschnitt,3);
#endif
  while ((!yes)&&(store)) {
    delay(10);  
    okButton.tick();
  }
  yes=false;
  if (store){
    EEPROM.put(sf * 0, xph4);  
    EEPROM.put(sf * 1, xph7);
    EEPROM.put(sf * 2, xph9);
  }else{
    delay(1000);
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
  fillBuffer();
  while (!yes) {
    sampling();
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
  lcd.setCursor(0, 0);    
  lcd.print("fillBuffer"); 
  for (int i = 0; i < AVG_ARRAY_SIZE; i++) {
    analogValBuf[i] = analogRead(PH_SENSOR_PIN);
    delay(DELAY_BETWEEN_SAMPLES);
  }
}

void fillBufferT1(){  
  lcd.setCursor(0, 1);    
  lcd.print("fillBufferT1"); 
  for (int i = 0; i < AVG_ARRAY_SIZE; i++) {
    analogValBufT1[i] = analogRead(T1pin);
    delay(DELAY_BETWEEN_SAMPLES);
  }
}

void fillBufferT2(){  
  lcd.setCursor(0, 2);    
  lcd.print("fillBufferT2"); 
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
#ifdef DEBUG  
for (int i=0; i<AVG_ARRAY_SIZE; i++){
  Serial.print((i==actualIdx)?"pH->>>>: ":"pH-Read: "); Serial.print(i);  Serial.print(" ");  Serial.println(analogValBuf[i]);
}
#endif
    actualIdx++;
    actualIdx%=AVG_ARRAY_SIZE;
  }
}

float sigma(){
  double f,DM=0.0f,DS=0.0f;
  for (int i=0; i<AVG_ARRAY_SIZE; i++){
    f=analogValBuf[i];
    DM+=f;
    DS+=f*f;
  }
  return sqrt((DS/AVG_ARRAY_SIZE)-((DM/AVG_ARRAY_SIZE)*(DM/AVG_ARRAY_SIZE)));
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
  yes=false;
  menu++;
  menu%=MENUENTRYS;
}

void doMenuLongClick(){  
  yes=false;
  lcd_backlight=!lcd_backlight;
  if (lcd_backlight) lcd.backlight();
  else {
    lcd.noBacklight(); 
    menu=0;
  }
}

void doMenuDClick(){  
  yes=false;
  menu+=MENUENTRYS;//this way menu never gets negative
  menu--;  
  menu%=MENUENTRYS;
}

void doOKClick(){
  yes=true;  
}

void doOKDClick(){
  if (menu==0) {
    measureEC=!measureEC; 
    nextECTime = 0ul;
    yes=false;
}
}

void doOKLongClick(){
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.clear();
  menu=0;
  nextDispTime = 0ul;
  yes=false;
}
// setup

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();//can't see without
  lcd.noAutoscroll();
  lcd.clear();
  menuButton.attachClick(doMenuClick);
  menuButton.attachDoubleClick(doMenuDClick);
  menuButton.attachLongPressStop(doMenuLongClick);
  okButton.attachClick(doOKClick);
  okButton.attachDoubleClick(doOKDClick);
  okButton.attachLongPressStart(doOKLongClick);
#ifdef DEBUG  
  Serial.begin(9600);
#endif

  EEPROM.get(sf * 0, xph4);  
  EEPROM.get(sf * 1, xph7);
  EEPROM.get(sf * 2, xph9);
  regression(false);
  //analogReference(EXTERNAL);// use this if you use AREF pin
  uint8_t temp[8]  = {0x4,  0xa,  0xa, 0xa, 0xa, 0x11, 0x11, 0xe};
  uint8_t deg[8]   = {0xc, 0x12, 0x12, 0xc,  0x0,  0x0, 0x0, 0x0};
  uint8_t copy[8]  = {0xc, 0x10, 0x10, 0xc,  0x0,  0x5, 0x7, 0x5};
  lcd.createChar(4, temp);//thermometer symbol
  lcd.createChar(1, deg);//degree
  lcd.createChar(2, copy);//CH
  lcd.setCursor(0, 0);
  pinMode(ECA, OUTPUT);
  pinMode(ECB, OUTPUT);
  pinMode(RELAIS1, OUTPUT);
  pinMode(RELAIS2, OUTPUT);
  digitalWrite(ECA, LOW);
  digitalWrite(ECB, LOW);
  digitalWrite(RELAIS1, HIGH);
  digitalWrite(RELAIS2, HIGH);
  lcd.clear();
}

float conductivity(){
  analogWrite(FANPIN,0);
  float rs=2200*2;
  int a6=0,a7=0;
  unsigned long diff1=0;
  digitalWrite(RELAIS1, LOW);
  digitalWrite(RELAIS2, LOW);
  delay(300); 
  for (int i=0; i<200; i++){
    digitalWrite(ECA, HIGH);
    digitalWrite(ECB, LOW);
    delayMicroseconds(150);//50mus
    a6 = analogRead(A6);//100mus
    a7 = analogRead(A7);//100mus
    diff1+=abs(a6-a7);


    digitalWrite(ECA, LOW);
    digitalWrite(ECB, HIGH);
    delayMicroseconds(150);//50mus
    a6 = analogRead(A6);//100mus
    a7 = analogRead(A7);//100mus
    diff1+=abs(a6-a7);
  }  // 1/(550)us = 1.8kHz

  float r1 = (1023.0/(1023-((float)diff1/400.0)) - 1.0) *  rs;    
  digitalWrite(ECA, LOW);
  digitalWrite(ECB, LOW);
  digitalWrite(RELAIS1, HIGH);
  digitalWrite(RELAIS2, HIGH);
  return (1/r1 * 1000000);
}

//loop

void loop() {
  unsigned long nowis = millis();

  menuButton.tick();
  okButton.tick();
  if (menu==0)if ((nowis - nextDispTime) > 500ul) {
    digitalWrite(13,!digitalRead(13));
    sampling();
    mimapause++;
    sensorVoltage = (float)avgValue * VOLTAGE / VOLTAGE_REF;
    phValue = steigung * sensorVoltage + achsenabschnitt;
    float sig=sigma();
    sig*= abs(steigung * VOLTAGE / VOLTAGE_REF);
    int8_t dig = min(max(-1*floor(log(2.5*sig)/log(10)),1),2);
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
    lcd.print(phValue,dig);
    lcd.print(F(" "));
    lcd.printByte(229);//sigma
    lcd.print(sig,dig);
    lcd.print(F(" "));
    if (info) {
      lcd.print(avgValue);
      lcd.print(F(" "));
      lcd.setCursor(18, 1);
      lcd.print(F("  "));
      lcd.setCursor(18, 1);
      lcd.print(actualIdx,HEX);
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
    if (!measureEC){
      if ((blowFish)&&(fanspeed!=0)) mimapause=0;
      if ((mimapause>AVG_ARRAY_SIZE)&&((!blowFish)||(fanspeed==0))){
      pHmin=min(pHmin,phValue);
      pHmax=max(pHmax,phValue);
      }
      Tmin=min((t1+t2*5)/6.0,Tmin);
      Tmax=max((t1+t2*5)/6.0,Tmax);
      if (!info){
        lcd.setCursor(0, 1);
        lcd.print(F("pH:"));
        lcd.print(pHmin,1);
        lcd.print(F(" "));
        lcd.print(pHmax,1);
        lcd.print(F(" "));
        lcd.setCursor(0, 2);
        lcd.printByte(4);//temp
        lcd.print(Tmin,1); 
        lcd.printByte(1);//grad
        lcd.print(F("C "));  
        lcd.print(Tmax,1); 
        lcd.printByte(1);//grad
        lcd.print(F("C "));  
      }
    }
    uint16_t oldfan=fanspeed;
    fanspeed = (uint16_t) max((int)((((t1+t2*5)/6.0)-21.5)*44.0), 0);
    fanspeed = min(255, fanspeed);
    if (oldfan==0){//hysteresis
      fanspeed = (fanspeed < 45)?0: fanspeed;//22.5grad
    }else{
      fanspeed = (fanspeed < 23)?0: fanspeed;//22grad
    }
    analogWrite(FANPIN,(blowFish)?fanspeed:0);
    if (info){
      lcd.print(fanspeed);   
      lcd.print((blowFish)?" ":"! ");
    }
    if (measureEC){
      lcd.setCursor(0, 2);  
      if ((nowis - nextECTime) > 60000ul){//5000ul){//
      ecValue = conductivity();
      nextECTime=nowis;
      }
      if (ecValue>0){
        lcd.print(ecValue);
        lcd.printByte(228);//micro
        lcd.print(F("S   "));  
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
      lcd.print((menu==5)?">":" ");
      lcd.print(F("Debug info: "));
      lcd.print((info)?"[yes]":"[no] ");
      lcd.setCursor(0, 1); 
      lcd.print((menu==6)?">":" ");
      lcd.print(F("Enable EC: "));
      lcd.print((measureEC)?"[yes]":"[no] ");
      lcd.setCursor(0, 2); 
      lcd.print((menu==7)?">":" ");
      lcd.print(F("Reset min/max: "));
      lcd.setCursor(0, 3); 
      lcd.print((menu==8)?">":" ");
      lcd.print(F("Enable FAN: "));
      lcd.print((blowFish)?"[yes]":"[no] ");
    }//*/
    if(yes){
      switch (menu){
        case 1: calib_pH4();break;
        case 2: calib_pH7();break;        
        case 3: calib_pH9();break;        
        case 4: fanspeed=255;break;
        case 5: info=!info; break;
        case 6: measureEC=!measureEC;break;
        case 7: 
                pHmin=15.0f;
                pHmax=-1.0f;
                Tmin=50.0f;
                Tmax=-1.0f;
                break;
        case 8:
                blowFish=!blowFish;
                fanspeed=(blowFish)?fanspeed:0;
                analogWrite(FANPIN,fanspeed);
                break;
        default: 
        lcd.clear();
        lcd.print(F("Not implementet yet!"));
        yes=false;
        while (!yes) okButton.tick();
      }
      fanspeed=max(fanspeed, 0);
      fanspeed%=256;
      if (fanspeed) fanspeed= (fanspeed<35)?35:fanspeed;
      //analogWrite(6,fanspeed);
      yes=false;
    }
    analogWrite(FANPIN,(blowFish)?fanspeed:0);
    if (menu<5){
    lcd.setCursor(15, 3); 
    lcd.print(fanspeed/2.55, 0); 
    lcd.print("% ");}
    
  }
  amenu=menu;
  
}
