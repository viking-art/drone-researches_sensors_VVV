#include <Wire.h>
#define address_HMC 0x1E // HMC5883 I2C addreess
#define address_MPU 0x68 // MPU I2C addreess

// **************************************** MPU *******************************************
struct mpucalib{
  float CalibRoll; float CalibPitch; float CalibYaw; int sign = 0;
} clib; // Global

struct mpu {
  float AccX; float AccY; float AccZ;
  float RateRoll; float RatePitch; float RateYaw;
};

struct rpyGyro {
  inline static float Grroll, Grpitch, Gryaw;
} ;

struct rpyAcc {
  float Aroll;  float Apitch;
};

// **************************************** HMC *******************************************
struct laban {
  float heading;  float true_north;
};

// ************************************** Kalman ******************************************
struct kalman1D {
  inline static float kroll=1, kpitch=11, kyaw=1;
  inline static float Pkroll=1, Pkpitch=1, Pkyaw=1;
};

struct kalman2D {
  inline static float xrk=1, vrk=1;
  inline static float xpk=1, vpk=1;
  inline static float xyk=1, vyk=1;
  inline static float pr11=1, pr12=1, pr21=1, pr22=1;
  inline static float pp11=1, pp12=1, pp21=1, pp22=1;
  inline static float py11=1, py12=1, py21=1, py22=1;
};
