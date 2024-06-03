#include <Servo.h>

double lengths[2] = {160, 185};
const byte numChars = 10;
char cmmd[numChars];
boolean newData = false;
double theta1 = 0;
double theta2 = 0;
double prev_theta1 = 0;
double prev_theta2 = 0;
double prev_angle[2] = {90, 90};
double prev_x = 0;
double prev_y = 0;
char x_coord[3];
char y_coord[3];
double x = 0;
double y = 0;
double angle[2] = {0, 0};
bool running = true;
bool inchesFlag = false;
bool g90Flag = true;
double speed = 60;
bool tenflag = true;

Servo servo[2];

void readCmmd();
void returnToOrigin();
void g0Cmmd();
void g1Cmmd();
void copyImage();
void moveServos();
bool IKSolve();

void setup() {
  Serial.begin(115200);
  servo[0].attach(9);
  servo[1].attach(3);
  Serial.setTimeout(1);
  returnToOrigin();
  delay(5000);
  drawten(x, y, 100, 200);
  tenflag = false; 
  
  
}

void loop() {

    readCmmd();
    if (!strcmp(cmmd, "G00")){
      g0Cmmd();
    }
    else if (!strcmp(cmmd, "G01")){
      g1Cmmd();
    }
    else if (!strcmp(cmmd, "G90")){
      g90Flag = true;
    }
    else if (!strcmp(cmmd, "G91")){
      g90Flag = false;
      prev_x = x;
      prev_y = y;
    }
    else if (!strcmp(cmmd, "G20")){
      inchesFlag = true;
    }
    else if (!strcmp(cmmd, "G21")){
      inchesFlag = false;
    }
    else if (!strcmp(cmmd, "M02")){
      running = false;
    }
    else if (!strcmp(cmmd, "M06")){
      returnToOrigin();
      delay(20000);
    }
    else if (!strcmp(cmmd, "M72")){
      returnToOrigin();
    }
    else if (!strcmp(cmmd, "IMG")){
      
      copyImage();      
    }
    else{;}
    //memset(cmmd, '\0', sizeof(cmmd));   
    newData = false;
}

void returnToOrigin(){
  x = 0;
  y = 0;
  moveServos();
}

void g0Cmmd(){
  newData = false;
  delay(10);
  readCmmd();
  
  strcpy(x_coord, cmmd);
  x = atoi(x_coord);
  newData = false;
  
  readCmmd();
  delay(10);
  strcpy(y_coord, cmmd);
  y = atoi(y_coord);
  if (inchesFlag){
    x = x*25.4;
    y = y*25.4;

  }
  if (!inchesFlag){
    x = x;
    y = y;
  }
  if (!g90Flag){
    x = x - prev_x;
    y = y - prev_y;
  }
  
  moveServos();
  newData = false;
  return;
}

void g1Cmmd(){
  char fr[3];
  newData = false;
  delay(10);
  readCmmd();
  strcpy(x_coord, cmmd);
  x = atoi(x_coord);
  readCmmd();
  strcpy(y_coord, cmmd);
  y = atoi(y_coord);
  newData = false;
  readCmmd();
  
  strcpy(fr, cmmd);
  speed = atoi(fr);
  
  if (inchesFlag){
    x = x*25.4;
    y = y*25.4;
    speed = speed*25.4;

  }
    if (!inchesFlag){
    x = x;
    y = y;
    speed = speed;
  }
  if (!g90Flag){
    x = x - prev_x;
    y = y - prev_y;
  }
  moveServos();
  newData = false;
}

void copyImage(){
  
  while (strcmp(cmmd, "END")){
    
    newData = false;
    readCmmd();
    strcpy(x_coord, cmmd);
    x = atoi(x_coord);
    newData = false;
    readCmmd();
    strcpy(y_coord, cmmd);
    y = atoi(y_coord);
    moveServos();
  }
  newData = false;
  
}
//https://forum.arduino.cc/t/serial-input-basics-updated/382007

void readCmmd(){
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
      rc = Serial.read();

      if (rc != endMarker) {
        cmmd[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
            ndx = numChars - 1;
        }
      }
      else {
        cmmd[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
  }
}
void drawten(double x0, double y0, double x1, double y1){
  int steps = 100; 
  //double speed = 100;
  for (int i = 1; i <= steps; i++) {
    double t = (double)i / steps;
    x = x0 + (t * (x1 - x0));
    y = y0 + (t * (y1 - y0));
    Serial.println(x);
    moveServos();
  }
}

void moveServos() {

  if (IKSolve()) {
    double cur_angle[2];
    double angle[2];
    cur_angle[0] = servo[0].read();
    cur_angle[1] = servo[1].read();
    prev_angle[0] = cur_angle[0];
    prev_angle[1] = cur_angle[0];
    angle[0] = constrain(degrees(theta1), 30, 150);
    angle[1] = constrain(degrees(theta2), 0, 180)+90;
    
    double step_size1;
    double step_size2;
    int numerator = min(abs(angle[0] - prev_angle[0]), abs(angle[1] - prev_angle[1]));

    int denominator = max(abs(angle[0] - prev_angle[0]), abs(angle[1] - prev_angle[1]));
    double delay_time = denominator/speed;

    if (numerator > 0){
      step_size1 =  abs(angle[0] - prev_angle[0])/denominator;
      step_size2 = abs(angle[1] - prev_angle[1])/denominator;
    }
    if (abs(angle[0] - prev_angle[0])== 0){
      step_size1 = 0;
    }
    if (abs(angle[1] - prev_angle[1])== 0){
      step_size2 = 0;
    }
    while(cur_angle[0] != angle[0] || cur_angle[1] != angle[1]){

      if (cur_angle[0] < angle[0]) {
        cur_angle[0] += step_size1;
        if (cur_angle[0] > angle[0]) cur_angle[0] = angle[0];
      } else if (cur_angle[0]> angle[0]) {
        cur_angle[0] -= step_size1;
        if (cur_angle[0] < angle[0]) cur_angle[0] = angle[0];
      }


      if (cur_angle[1] <  angle[1]) {
        cur_angle[1] += step_size2;
        if (cur_angle[1] > angle[1]) cur_angle[1] = angle[1];
      } else if (cur_angle[1]> angle[1]) {
        cur_angle[1] -= step_size2;
        if (cur_angle[1] < angle[1]) cur_angle[1] = angle[1];
      }

      servo[0].write(cur_angle[0]);
      servo[1].write(cur_angle[1]);
      
      delay(delay_time);
      
      
    }
    prev_angle[0] = cur_angle[0];
    prev_angle[1] = cur_angle[1];
  } 
  else {;}
}

//https://robotacademy.net.au/lesson/inverse-kinematics-for-a-2-joint-robot-arm-using-geometry/
bool IKSolve() {
  
  y = -abs(y)+160+185;
  
  double distance = sqrt(x * x + y * y);
  
  if (distance > (lengths[0] + lengths[1]) || distance < abs(lengths[0]-lengths[1])) {
    
    return false;
  }

  double cosTheta = (x * x + y * y - lengths[0] * lengths[0] - lengths[1] * lengths[1]) / (2 * lengths[0] * lengths[1]);
  theta2 = acos(cosTheta);

  double sinTheta = sqrt(1 - cosTheta * cosTheta);
  double t1 = lengths[1] * sinTheta;
  double t2 = lengths[0] + lengths[1] * cosTheta;
  
  theta1 = atan2(y, x) - atan2(t1, t2);

  return true;
}
