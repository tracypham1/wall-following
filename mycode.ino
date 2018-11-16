//code direction to corrolate with FS and LS value
//as FSvalue increases speedvalue should decrease

//assign the sensor pins to variables
#define LS A2
#define FS A0

//define the output motor pins to variables
#define ENA A4  //left motor
#define IN1 9
#define IN2 8
#define ENB A5   //right motor
#define IN3 7
#define IN4 6


void setup() {
  // put your setup code here, to run once:
  //define sensor pins to be input
  pinMode(LS, INPUT);
  pinMode(FS, INPUT);

  //define the motor pins to be output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //starts serial monitor
  Serial.begin(9600);
  while (! Serial);

}

void loop() {

  //retrieve data from sensors and convert data to centimeters
  double LSvalue = analogRead(LS);
  double LSdistCM = 4800/(LSvalue-20);
  double FSvalue = analogRead(FS);
  double FSdistCM = 4800/(FSvalue-20);

  //print the value to read in the serial monitor
  Serial.println(LSdistCM);

  //use variable to assign value to parameters
  int rangeF = 12;
  int min_rangeL = 10;
  int max_rangeL = 15;

  //start power to motors
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
  //go forward LS in range and FS is out of range
  if (LSdistCM > min_rangeL && LSdistCM <=max_rangeL && FSdistCM > rangeF){ 
    
    //left forward
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
    //right forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  //turn right if LS below range or FS below range
  if (LSdistCM <= min_rangeL || FSdistCM <= rangeF){
    
    //left forward
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
    //right backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  
  //turn left if LS out of range and FS is out of range
  if (LSdistCM >max_rangeL && FSdistCM > rangeF){
    
    //left backward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    //right forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  
}
