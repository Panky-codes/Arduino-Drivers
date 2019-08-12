#include <Arduino.h>
#include <Wire.h>
#include  <RW.h>

LSM9DS1Driver lsm;
int gyroData[6] = {0};
float gyroSens = 0.00875;
float accelSens = 0.000061;
float magSens = 0.00014;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  delay(10);
  if (lsm.whoAmI_AG() && lsm.whoAmI_M()){
    Serial.println("Success baby");
  }
  else {
    Serial.println("Booooo");
    while (1);
  }
  delay(10);
  lsm.I2CwriteData (address_AG,CTRL_REG_1_G, 0x20); // For gyro
  lsm.I2CwriteData (address_AG,CTRL_REG_6_X, 0x20); // For accel
  lsm.I2CwriteData (address_M,CTRL_REG_3_M, 0x00); // For Mag
}

void loop() {
//  put your main code here, to run repeatedly:
  if (lsm.accelAvailable())
    {
      int status = lsm.I2CreadDatas(address_AG, OUT_X_L_XL, gyroData,6);
      if (status){
        lsm.accelVect.AcX=gyroData[0]|gyroData[1]<< 8;
        lsm.accelVect.AcY=gyroData[2]|gyroData[3]<<8;
        lsm.accelVect.AcZ=gyroData[4]|gyroData[5]<<8;
        Serial.print("AcX = "); Serial.print((float)lsm.accelVect.AcX * accelSens);Serial.print(",");
        Serial.print("AcY = "); Serial.print((float)lsm.accelVect.AcY* accelSens);Serial.print(",");
        Serial.print("AcZ = "); Serial.print((float)lsm.accelVect.AcZ* accelSens);Serial.print(",");
        Serial.println("");
          }
      else{
        Serial.println("Problem with multiple read");
      }
    }
    if (lsm.gyroAvailable())
      {
        int status = lsm.I2CreadDatas(address_AG,OUT_X_L_G, gyroData,6);
        if (status){
          lsm.gyroVect.GaX=gyroData[0]|gyroData[1]<< 8;
          lsm.gyroVect.GaY=gyroData[2]|gyroData[3]<<8;
          lsm.gyroVect.GaZ=gyroData[4]|gyroData[5]<<8;
          Serial.print("GaX = "); Serial.print((float)lsm.gyroVect.GaX * gyroSens);Serial.print(",");
          Serial.print("GaY = "); Serial.print((float)lsm.gyroVect.GaY* gyroSens);Serial.print(",");
          Serial.print("GaZ = "); Serial.print((float)lsm.gyroVect.GaZ* gyroSens);Serial.print(",");
          Serial.println("");
            }
        else{
          Serial.println("Problem with multiple read");
        }
      }
      if (lsm.magAvailable())
        {
          int status = lsm.I2CreadDatas(address_M,OUT_X_L_M, gyroData,6);
          if (status){
            lsm.magVect.MaX=gyroData[0]|gyroData[1]<< 8;
            lsm.magVect.MaY=gyroData[2]|gyroData[3]<<8;
            lsm.magVect.MaZ=gyroData[4]|gyroData[5]<<8;
            Serial.print("MaX = "); Serial.print((float)lsm.magVect.MaX * magSens);Serial.print(",");
            Serial.print("MaY = "); Serial.print((float)lsm.magVect.MaY* magSens);Serial.print(",");
            Serial.print("MaZ = "); Serial.print((float)lsm.magVect.MaZ* magSens);Serial.print(",");
            Serial.println("");
              }
          else{
            Serial.println("Problem with multiple read");
          }
        }
}
