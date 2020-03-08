int offset =0; // set the correction offset value
double bVoltage = 0;

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // (0x27,16,2) for 16x2 LCD. //0X27 LCD ADDRESS

void setup() {
  // Initiate the LCD:
  Serial.begin(115200);   //Serial Monitor for debugging
  lcd.begin(16,2);        //Initialize display
  lcd.init();
  lcd.backlight();
  
}
void loop() {   //COLUMN, ROW

  double volt = analogRead(A0);// read the input from Battery
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  voltage /=100;// divide by 100 to get the decimal values
  bVoltage = voltage; 
  
  Serial.print("bat Voltage: "); Serial.print(voltage); Serial.println("V");   //PRINT VOLTAGE
  lcd.setCursor(0, 0); 
  lcd.print("Voltage:"); 
  lcd.setCursor(9,0);
  lcd.print(bVoltage);
  
  double volt2 = analogRead(A1); // read the input from Piezo discs
  double voltage2 = map(volt2,0,1023, 0, 2500);// map 0-1023 to 0-2500 and add correction offset
  voltage2 /=100;// divide by 100 to get the decimal values
  double pvolt = voltage2;
  
  int prev;
  
  Serial.print("Pressure Voltage: ");
  Serial.print(pvolt);//print the voltge
  Serial.println("V");

  if(pvolt> prev+.01){
    displayCharging();
  }
  prev = pvolt;
  delay(10);
  
}


void displayCharging(){        //Prints charging status to display
  lcd.setCursor(2, 1); 
  lcd.print("Charging...");   
  delay(1000);
  lcd.setCursor(0, 1); 
  lcd.print("             "); //clears line
}
