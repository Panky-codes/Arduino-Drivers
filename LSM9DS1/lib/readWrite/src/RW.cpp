#include <RW.h>
#include <Wire.h>

uint8_t LSM9DS1Driver::gyroAvailable()
{
  uint8_t data;
  uint8_t status = I2CreadData(address_AG,STATUS_REG_1, &data, 1);
	return ((data & (1<<1)) >> 1);
}

uint8_t LSM9DS1Driver::accelAvailable()
{
  uint8_t data;
  uint8_t status = I2CreadData(address_AG,STATUS_REG_1, &data, 1);
	return ((data & (1<<0)) >> 0);
}

uint8_t LSM9DS1Driver::magAvailable()
{
  uint8_t data;
  uint8_t status = I2CreadData(address_M,STATUS_REG_M, &data, 1);
	return ((data & (1<<3)) >> 3);
}

int LSM9DS1Driver::whoAmI_AG(){
  uint8_t data;
  int reval = I2CreadData(address_AG,WHO_AM_I_AG, &data, 1);
  if ( data != 0x68){
    return 0;
  }
  return 1;
}

int LSM9DS1Driver::whoAmI_M(){
  uint8_t data;
  int reval = I2CreadData(address_M,WHO_AM_I_M, &data, 1);
  if ( data != 0x3D){
    return 0;
  }
  return 1;
}


int LSM9DS1Driver::I2CreadData (addressSelect address, uint8_t subAddress, uint8_t *data , uint8_t numOfBytes)
{
  addressLSM = addrAG;
  if (address == address_M) {
      addressLSM = addrMA;
  }
  Wire.beginTransmission(addressLSM);
  Wire.write(subAddress);
  int val = Wire.endTransmission(false);
  if (val !=0){
    return 0;
  }
  Wire.requestFrom(addressLSM, numOfBytes);
  for (int i =0; i< numOfBytes;i++) {
    data[i] = Wire.read();
  }
  return 1;
}

int LSM9DS1Driver::I2CreadDatas (addressSelect address, uint8_t subAddress, int *data, uint8_t numOfBytes) //TODO change it to bytes
{
  addressLSM = addrAG;
  if (address == address_M) {
      addressLSM = addrMA;
  }
  Wire.beginTransmission(addressLSM);
  Wire.write((subAddress|0x80));
  int val = Wire.endTransmission(false);
  if (val !=0){
    return 0;
  }
  int count = Wire.requestFrom(addressLSM, numOfBytes,true);
  // if (count != numOfBytes){
  //   return 0;
  // }
  for (uint8_t i =0; i < numOfBytes;i++) {
    data[i] = Wire.read();
  }
  return 1;
}

int LSM9DS1Driver::I2CwriteData (addressSelect address, uint8_t subAddress, uint8_t data) {

  addressLSM = addrAG;
  if (address == address_M) {
      addressLSM = addrMA;
  }
  Wire.beginTransmission(addressLSM);
  Wire.write(subAddress);
  Wire.write(data);
  int status = Wire.endTransmission();
  if (status != 0){
    return 0;
  }
  return 1;
}
