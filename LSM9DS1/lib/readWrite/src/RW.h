#ifndef RW_H
#define RW_H
#include <Arduino.h>
#define addrAG 0x6B
#define addrMA 0x1E
#define WHO_AM_I_AG 0x0F
#define WHO_AM_I_M 0x0F
#define OUT_X_L_G 0x18
#define OUT_X_L_XL 0x28
#define CTRL_REG_1_G 0x10
#define CTRL_REG_6_X 0x20
#define STATUS_REG_1 0x17
#define CTRL_REG_4 0x1E
#define CTRL_REG_5_X 0x1F
#define STATUS_REG_M 0x27
#define OUT_X_L_M 0x28
#define CTRL_REG_3_M 0x22
enum addressSelect{
  address_AG,
  address_M
};

struct gyroVector {
  int16_t GaX,GaY,GaZ;
};
struct accelVector {
  int16_t AcX,AcY,AcZ;
};
struct magVector {
  int16_t MaX,MaY,MaZ;
};
class LSM9DS1Driver {
public:
  gyroVector gyroVect;
  accelVector accelVect;
  magVector magVect;
  float gyroSens;
  uint8_t addressLSM;
  int beginI2C ();
  int getGyro();
  void setScaleGyro(int scaleFactor);
  void setOdrGyro(int odrFactor);
  uint8_t gyroAvailable();
  uint8_t accelAvailable();
  uint8_t magAvailable();
  int whoAmI_AG();
  int whoAmI_M();
  int I2CreadData (addressSelect address, uint8_t subAddress, uint8_t *data , uint8_t numOfBytes);
  int I2CreadDatas (addressSelect address, uint8_t subAddress, int *data , uint8_t numOfBytes); //TODO change it to bytes
  int I2CwriteData (addressSelect address, uint8_t subAddress, uint8_t data);
};
#endif /* RW_H*/
