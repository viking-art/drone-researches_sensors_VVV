#define dt 0.0067
#define q1d 0.4
#define r1d 10
#define q2d 0.125
#define r2d 20
void kalman_filter_1D(struct mpu ar, struct rpyAcc acc, struct laban hmc, struct kalman1D *kman)
{
  float accR=ar.AccX,       accP=ar.AccY,        accY=ar.AccZ;
  float Aroll=acc.Aroll,    Apitch=acc.Apitch,   Ayaw=hmc.heading;
  float Rroll=ar.RateRoll,  Rpitch=ar.RatePitch, Ryaw=ar.RateYaw;

  float kr=(*kman).kroll,   kp=(*kman).kpitch,   ky=(*kman).kyaw;
  float pkr=(*kman).Pkroll, pkp=(*kman).Pkpitch, pky=(*kman).Pkyaw;

  kalman_1D(Aroll,Rroll,&kr,&pkr,q1d,r1d,dt);
  kalman_1D(Apitch,Rpitch,&kp,&pkp,q1d,r1d,dt); 
  kalman_1D(Ayaw,Ryaw,&ky,&pky,q1d,r1d,dt); 

  (*kman).kroll=kr,   (*kman).kpitch=kp,   (*kman).kyaw=ky;
  (*kman).Pkroll=pkr, (*kman).Pkpitch=pkp, (*kman).Pkyaw=pky;
}

void kalman_1D(float z_meas,float gyro,float *x_in,float *P_in, float Q, float R,float ts)                    
{
  float xk,P,K;
  float xp=*x_in, Pp=*P_in;
  // Prediction
  xk = xp + ts*gyro;
  P  = Pp + Q;
  // Updatation
  K  = P/(P + R);                     
  xk = xk + K*(z_meas-xk);      
  P  = (1-K)*P;                       
  // New state
  xp = xk;       Pp = P;
  // Output
  *x_in = xk;   *P_in = P;
}


void kalman_filter_2D(struct mpu ar, struct rpyAcc acc, struct laban hmc, struct kalman2D *kman2)
{
  float accR=ar.AccX,       accP=ar.AccY,        accY=ar.AccZ;
  float Aroll=acc.Aroll,    Apitch=acc.Apitch,   Ayaw=hmc.heading;
  float Rroll=ar.RateRoll,  Rpitch=ar.RatePitch, Ryaw=ar.RateYaw;

  float xrk=(*kman2).xrk,   vrk=(*kman2).vrk;
  float xpk=(*kman2).xpk,   vpk=(*kman2).vpk;
  float xyk=(*kman2).xyk,   vyk=(*kman2).vyk;

  float pr11=(*kman2).pr11, pr12=(*kman2).pr12, pr21=(*kman2).pr21, pr22=(*kman2).pr22;
  float pp11=(*kman2).pp11, pp12=(*kman2).pp12, pp21=(*kman2).pp21, pp22=(*kman2).pp22;
  float py11=(*kman2).py11, py12=(*kman2).py12, py21=(*kman2).py21, py22=(*kman2).py22;


  kalman_2D(&xrk, &vrk, 0, &pr11, &pr12, &pr21, &pr22, Aroll, Rroll);
  kalman_2D(&xpk, &vpk, 0, &pp11, &pp12, &pp21, &pp22, Apitch, Rpitch);
  kalman_2D(&xyk, &vyk, 0, &py11, &py12, &py21, &py22, Ayaw, Ryaw);

  (*kman2).xrk=xrk;   (*kman2).vrk=vrk;
  (*kman2).xpk=xpk;   (*kman2).vpk=vpk;
  (*kman2).xyk=xyk;   (*kman2).vyk=vyk;

  (*kman2).pr11=pr11; (*kman2).pr12=pr12; (*kman2).pr21=pr21; (*kman2).pr22=pr22;
  (*kman2).pp11=pp11; (*kman2).pp12=pp12; (*kman2).pp21=pp21; (*kman2).pp22=pp22;
  (*kman2).py11=py11; (*kman2).py12=py12; (*kman2).py21=py21; (*kman2).py22=py22;
}

void kalman_2D(float *xk, float *vk, float ak, float *p11, float *p12,  float *p21, float *p22, float meas, float v_meas) 
{
  float xk_1 = *xk, vk_1 = *vk;
  float R = r2d, temp = 0, K1, K2;
  float Q11 = q2d, Q12 = 0, Q21 = 0, Q22 = q2d;
  float P11 = *p11, P12 = *p12, P21 = *p21, P22 = *p22;

//Prediction  
// x = A*x + B*u; 
  xk_1 = xk_1 + dt*vk_1 + ak*0.5*dt*dt;
  vk_1 = vk_1 + dt*ak;

  P11 = P11 + dt*P21 + dt*(P11 + dt*P22) +Q11;
  P12 = P12 + dt*P22 + Q12;
  P21 = P21 + dt*P22 + Q21;
  P22 = P22 + Q22;

// kalman Parameter (use Single measurement dimension - R)
  temp = P11 + R;
  K1 = P11/temp; K2 = P21/temp; 
              
//Updation
  vk_1 = vk_1 + K2*(v_meas - vk_1);
  xk_1 = xk_1 + K1*(meas - xk_1);
  P22 = P22 - K2*P12;
  P21 = P21 - K2*P11;
  P12 = (1-K1)*P12;
  P11 = (1-K1)*P11;

// Output
  *vk=vk_1;   *xk= xk_1;
  *p11 = P11; *p12 = P12; *p21 = P21; *p22 = P22;
}