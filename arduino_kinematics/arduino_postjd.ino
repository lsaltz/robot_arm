#include <Servo.h>

double lengths[2] = {160, 185};
const byte numChars = 10;
char cmmd[numChars];
boolean newData = false;
double theta1 = 0;
double theta2 = 0;
double angle[2] = {90, 90};
double prev_theta1 = 0;
double prev_theta2 = 0;
double prev_angle[2] = {90, 90};
double prev_x = 0;
double prev_y = 0;
char x_coord[3];
char y_coord[3];
double x = 0;
double y = 0;
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
void moveServos(double x0, double y0, double x1, double y1);
bool IKSolve(double x1, double y1);

void setup() {
  Serial.begin(115200);
  servo[0].attach(9);
  servo[1].attach(3);
  Serial.setTimeout(1);
  returnToOrigin();
  /*
  Serial.println("start");
moveServos(0.00, 0.00, 75.89, 32.86);
delay(100);
moveServos(75.89, 32.86, 87.41, 37.61);
delay(100);
moveServos(87.41, 37.61, 90.12, 44.38);
delay(100);
moveServos(90.12, 44.38, 89.44, 51.84);
delay(100);
moveServos(89.44, 51.84, 86.06, 58.95);
delay(100);
moveServos(86.06, 58.95, 81.99, 65.39);
delay(100);
moveServos(81.99, 65.39, 85.72, 59.29);
delay(100);
moveServos(85.72, 59.29, 89.78, 52.85);
delay(100);
moveServos(89.78, 52.85, 95.54, 49.80);
delay(100);
moveServos(95.54, 49.80, 103.67, 48.11);
delay(100);
moveServos(103.67, 48.11, 110.79, 51.16);
delay(100);
moveServos(110.79, 51.16, 114.85, 58.27);
delay(100);
moveServos(114.85, 58.27, 115.53, 65.39);
delay(100);
moveServos(115.53, 65.39, 112.14, 70.47);
delay(100);
moveServos(112.14, 70.47, 106.38, 74.87);
delay(100);
moveServos(106.38, 74.87, 99.95, 75.89);
delay(100);
moveServos(99.95, 75.89, 95.54, 76.57);
delay(100);
moveServos(95.54, 76.57, 90.46, 76.91);
delay(100);
moveServos(90.46, 76.91, 97.24, 77.25);
delay(100);
moveServos(97.24, 77.25, 104.01, 77.25);
delay(100);
moveServos(104.01, 77.25, 109.77, 79.96);
delay(100);
moveServos(109.77, 79.96, 114.51, 85.72);
delay(100);
moveServos(114.51, 85.72, 114.51, 94.53);
delay(100);
moveServos(114.51, 94.53, 111.80, 101.64);
delay(100);
moveServos(111.80, 101.64, 105.03, 102.66);
delay(100);
moveServos(105.03, 102.66, 98.25, 103.67);
delay(100);
moveServos(98.25, 103.67, 91.48, 99.27);
delay(100);
moveServos(91.48, 99.27, 86.73, 95.20);
delay(100);
moveServos(86.73, 95.20, 83.68, 88.43);
delay(100);
moveServos(83.68, 88.43, 86.06, 92.83);
delay(100);
moveServos(86.06, 92.83, 89.44, 99.95);
delay(100);
moveServos(89.44, 99.95, 91.14, 110.45);
delay(100);
moveServos(91.14, 110.45, 87.07, 114.85);
delay(100);
moveServos(87.07, 114.85, 79.28, 116.55);
delay(100);
moveServos(79.28, 116.55, 71.15, 117.22);
delay(100);
moveServos(71.15, 117.22, 65.05, 113.50);
delay(100);
moveServos(65.05, 113.50, 62.68, 106.38);
delay(100);
moveServos(62.68, 106.38, 64.03, 98.93);
delay(100);
moveServos(64.03, 98.93, 67.08, 92.15);
delay(100);
moveServos(67.08, 92.15, 69.79, 87.75);
delay(100);
moveServos(69.79, 87.75, 69.45, 91.14);
delay(100);
moveServos(69.45, 91.14, 64.71, 96.22);
delay(100);
moveServos(64.71, 96.22, 60.31, 101.30);
delay(100);
moveServos(60.31, 101.30, 52.51, 104.01);
delay(100);
moveServos(52.51, 104.01, 44.04, 101.30);
delay(100);
moveServos(44.04, 101.30, 38.62, 94.53);
delay(100);
moveServos(38.62, 94.53, 37.95, 84.70);
delay(100);
moveServos(37.95, 84.70, 42.69, 80.63);
delay(100);
moveServos(42.69, 80.63, 48.79, 77.25);
delay(100);
moveServos(48.79, 77.25, 56.58, 76.91);
delay(100);
moveServos(56.58, 76.91, 63.02, 76.57);
delay(100);
moveServos(63.02, 76.57, 54.89, 75.89);
delay(100);
moveServos(54.89, 75.89, 48.11, 76.23);
delay(100);
moveServos(48.11, 76.23, 42.69, 72.84);
delay(100);
moveServos(42.69, 72.84, 38.62, 62.68);
delay(100);
moveServos(38.62, 62.68, 39.64, 54.55);
delay(100);
moveServos(39.64, 54.55, 46.42, 48.45);
delay(100);
moveServos(46.42, 48.45, 51.84, 48.45);
delay(100);
moveServos(51.84, 48.45, 58.27, 50.82);
delay(100);
moveServos(58.27, 50.82, 62.68, 53.87);
delay(100);
moveServos(62.68, 53.87, 65.39, 57.26);
delay(100);
moveServos(65.39, 57.26, 68.10, 61.32);
delay(100);
moveServos(68.10, 61.32, 69.79, 65.39);
delay(100);
moveServos(69.79, 65.39, 68.10, 60.31);
delay(100);
moveServos(68.10, 60.31, 63.02, 51.84);
delay(100);
moveServos(63.02, 51.84, 63.02, 46.42);
delay(100);
moveServos(63.02, 46.42, 65.73, 36.25);
delay(100);
moveServos(65.73, 36.25, 72.16, 33.88);
delay(100);
moveServos(72.16, 33.88, 84.02, 35.24);
delay(100);
moveServos(84.02, 35.24, 90.12, 43.37);
delay(100);
moveServos(90.12, 43.37, 89.44, 51.84);
delay(100);
moveServos(89.44, 51.84, 85.72, 59.97);
delay(100);
moveServos(85.72, 59.97, 82.67, 65.39);
delay(100);
moveServos(82.67, 65.39, 86.73, 71.49);
delay(100);
moveServos(86.73, 71.49, 86.39, 81.31);
delay(100);
moveServos(86.39, 81.31, 81.65, 86.06);
delay(100);
moveServos(81.65, 86.06, 74.87, 87.75);
delay(100);
moveServos(74.87, 87.75, 67.76, 85.72);
delay(100);
moveServos(67.76, 85.72, 64.71, 79.96);
delay(100);
moveServos(64.71, 79.96, 65.05, 74.20);
delay(100);
moveServos(65.05, 74.20, 68.78, 69.45);
delay(100);
moveServos(68.78, 69.45, 75.89, 63.36);
delay(100);

Serial.println("done");
  */
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
     
    newData = false;
}

void returnToOrigin(){
  servo[0].write(90);
  servo[1].write(90);
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
  
  moveServos(prev_x, prev_y, x, y);
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
  moveServos(prev_x, prev_y, x, y);
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
    moveServos(prev_x, prev_y, x, y);
    prev_x = x;
    prev_y = y;
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
        Serial.println("ACK\n");
        newData = true;
      }
  }
}

void moveServos(double x0, double y0, double x1, double y1) {
  int steps = 100;
  double cur_x;
  double cur_y;
    for (int i = 0; i <= steps; i++) {
      
      double t = (double)i / steps;
      cur_x = x0 + (t * (x1 - x0));
      cur_y = y0 + (t * (y1 - y0));
      if (IKSolve(cur_x, cur_y)) { 
        angle[0] = constrain(degrees(theta1), 30, 150);
        angle[1] = constrain(degrees(theta2), 0, 180)+90;
        servo[0].write(angle[0]);
        servo[1].write(angle[1]);
      }
    }
    
}


//https://www.youtube.com/watch?v=kAdbxsJZGto
bool IKSolve(double x1, double y1) {
  y1 = -y1 + 160 + 185;
  
  
  double distance = sqrt((x1*x1)+(y1*y1));
  
  if (distance > (lengths[0] + lengths[1]) || distance < abs(lengths[0]-lengths[1])) {
    Serial.println("Could not solve");
    Serial.println(distance);
    return false;
  }
  theta2 = acos(((x1*x1)+(y1*y1)-(lengths[0]*lengths[0])-(lengths[1]*lengths[1]))/(2*lengths[0]*lengths[1]));
  
  theta1 = atan(y1/x1)-asin((lengths[1]*sin(theta2))/(distance));
  
  delay(50);
  return true;
}
