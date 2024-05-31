#include <FABRIK2D.h> //https://github.com/henriksod/Fabrik2DArduino
#include <Servo.h>

int lengths[] = {180, 190};//MEASURE LENGTHS OF ARM HERE!! in mm

Fabrik2D fabrik2D(3, lengths);
const byte numChars = 10;
char cmmd[numChars];
boolean newData = false;
double theta1 = 0;
double theta2 = 0;
double prev_theta1 = 0;
double prev_theta2 = 0;
double prev_angle[2] = {0, 0};
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
double speed = 20;
Servo servo[2];
void readCmmd();
void returnToOrigin();
void g0Cmmd();
void g1Cmmd();
void copyImage();
void moveServos();
void IKSolve();

void setup() {
  Serial.begin(115200);
  servo[0].attach(9);
  servo[1].attach(3);
  Serial.setTimeout(1);
  fabrik2D.setTolerance(0.5);
  returnToOrigin();
  Serial.println("enter cmmd");
  
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
      Serial.println("You are now in inches");
      inchesFlag = true;

    }
    else if (!strcmp(cmmd, "G21")){
      Serial.println("You are now in millimeters");
      inchesFlag = false;
    }
    else if (!strcmp(cmmd, "M02")){
      running = false;
    }
    else if (!strcmp(cmmd, "M06")){
      returnToOrigin();
      Serial.println("Change tool");
      delay(20000);
    }
    else if (!strcmp(cmmd, "M72")){
      returnToOrigin();
    }
    else if (!strcmp(cmmd, "IMG")){
      copyImage();      
    }
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
  delay(3000);
  readCmmd();
  strcpy(x_coord, cmmd);
  x = atoi(x_coord);
  newData = false;
  delay(3000);
  readCmmd();
  strcpy(y_coord, cmmd);
  if (inchesFlag){
    x = x/25.4;
    y = y/25.4;

  }
  if (!g90Flag){
    x = x - prev_x;
    y = y - prev_y;
  }
  moveServos();
  newData = false;
}

void g1Cmmd(){
  char fr[3];
  newData = false;
  readCmmd();
  strcpy(x_coord, cmmd);
  x = atoi(x_coord);
  newData = false;
  readCmmd();
  strcpy(y_coord, cmmd);
  newData = false;
  readCmmd();
  strcpy(fr, cmmd);
  speed = atoi(fr);
  if (inchesFlag){
    x = x/25.4;
    y = y/25.4;
    speed = speed/25.4;

  }
  if (!g90Flag){
    x = x - prev_x;
    y = y - prev_y;
  }
  moveServos();
  newData = false;
}

void copyImage(){
  /*
  while (strcmp(cmmd, "END")){
    
    newData = false;
    readCmmd();
    strcpy(x_coord, cmmd);
    x = atoi(x_coord);
    newData = false;
    readCmmd();
    strcpy(y_coord, cmmd);
    moveServos();
  }
    */
    
    servo[0].write(180);
    delay(100);
    servo[1].write(180);
    delay(100);
    servo[0].write(0);
    delay(100);
    servo[1].write(0);
    delay(100);
    servo[0].write(180);
    delay(100);
    servo[1].write(0);
    delay(100);
    servo[0].write(0);
    delay(100);
    servo[1].write(180);
        //moveServos();
      
  
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



void moveServos(){
  IKSolve();
  double cur_angle[2] = {prev_angle[0], prev_angle[1]};
  double step_size;
  int numerator = min(abs(angle[0] - prev_angle[0]), abs(angle[1] - prev_angle[1]));

  int denominator = max(abs(angle[0] - prev_angle[0]), abs(angle[1] - prev_angle[1]));
  double delay_time =  10 * denominator/speed;

  if (numerator > 0){
    step_size =  numerator/denominator;
  }
  else{
    step_size = 0;
  }

  for (int i = 0; i < denominator; i++){
    if (angle[0] > prev_angle[0]){
      if( numerator == abs(angle[0] - prev_angle[0])){
        servo[0].write(cur_angle[0]);
        cur_angle[0] += step_size;  
      }
      else{
        servo[0].write(cur_angle[0]);
        cur_angle[0]++;
      }
      
    }
    else if (angle[0] < prev_angle[0]){
      if( numerator == abs(angle[0] - prev_angle[0])){
        servo[0].write(cur_angle[0]);
        cur_angle[0] -= step_size;  
      }
      else{
        servo[0].write(cur_angle[0]);
        cur_angle[0]--;
      }
      
    }

    if (angle[1] > prev_angle[1]){
      if( numerator == abs(angle[1] - prev_angle[1])){
        servo[1].write(cur_angle[1]);
        cur_angle[1] += step_size;  
      }
      else{
        servo[1].write(cur_angle[1]);
        cur_angle[1]++;
      }
      
    }
    else if (angle[1] < prev_angle[1]){
      if(numerator == abs(angle[1] - prev_angle[1])){
        servo[1].write(cur_angle[1]);
        cur_angle[1] -= step_size;  
      }
      else{
        servo[1].write(cur_angle[1]);
        cur_angle[1]--;
      }
    }
    Serial.println(cur_angle[0]);
    delay(delay_time);
    Serial.println(delay_time);
  }
  prev_angle[0] = cur_angle[0];
  prev_angle[1] = cur_angle[1];
  return;
}

void IKSolve(){
    //x = x + 350;
    //y = y + 220;
    fabrik2D.solve(x, y, lengths);
    theta1 = fabrik2D.getAngle(0) * RAD_TO_DEG;
    theta2 = fabrik2D.getAngle(1) * RAD_TO_DEG;
    Serial.println(theta1);
    Serial.println(theta2);
    if (theta1 > prev_theta1){
      angle[0] = min(180, max(0, theta1));
      
    }
    else if (theta1 < prev_theta1){
      angle[0] = min(180, max(0, theta1));
    }
    else{;}

    if (theta2 > prev_theta2){
      angle[1] = min(180, max(0, theta2 - 90));
    }
    else if (theta2 < prev_theta2){
      angle[1] = min(180, max(0, theta2 - 90));
    }
    else{;}
    Serial.println(angle[0]);
    Serial.println(angle[1]);
    prev_theta1 = theta1;
    prev_theta2 = theta2;
}