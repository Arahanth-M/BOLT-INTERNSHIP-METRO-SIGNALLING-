// Define the pins for the LEDs
const int st1RLED = 2;
const int st1YLED = 3;
const int st1GLED = 4;


const int st2RLED = 5;
const int st2YLED = 6;
const int st2GLED = 7;

const int st3RLED = 0;
const int st3YLED = A1;
const int st3GLED = 1;

// Define the pins for the ultrasonic sensors
const int s1trigpin = 8;
const int s1echopin = 9;

const int s2trigpin = 10;
const int s2echopin = 11;

const int s3trigpin = 12;
const int s3echopin = 13;

void setup() {
  // Initialize ultrasonic sensors
  pinMode(s1trigpin, OUTPUT);
  pinMode(s1echopin, INPUT);
  
  pinMode(s2trigpin, OUTPUT);
  pinMode(s2echopin, INPUT);
  
  pinMode(s3trigpin, OUTPUT);
  pinMode(s3echopin, INPUT);
  
  // Initialize LEDs
  pinMode(st1RLED, OUTPUT);
  pinMode(st1YLED, OUTPUT);
  pinMode(st1GLED, OUTPUT);
  
  pinMode(st2RLED, OUTPUT);
  pinMode(st2YLED, OUTPUT);
  pinMode(st2GLED, OUTPUT);
  
  pinMode(st3RLED, OUTPUT);
  pinMode(st3YLED, OUTPUT);
  pinMode(st3GLED, OUTPUT);
  Serial.begin(9600);
  
  // Initially, set all LEDs to OFF
  turnOffAllLEDs();
}

void loop() {
  // Measure the distance from the ultrasonic sensors
  long distance1 = measureDistance(s1trigpin, s1echopin);
  long distance2 = measureDistance(s2trigpin, s2echopin);
  long distance3 = measureDistance(s3trigpin, s3echopin);
  
  if(distance1<10 && distance2<10)
  {
    Serial.println("MESSAGE TO TRAIN 2: cant move already train exists!!!");
  digitalWrite(st1RLED, HIGH);
  digitalWrite(st1YLED, LOW);
  digitalWrite(st1GLED, LOW);
  
  digitalWrite(st2RLED, HIGH);
  digitalWrite(st2YLED, LOW);
  digitalWrite(st2GLED, LOW);
  
  digitalWrite(st3RLED, LOW);
  digitalWrite(st3YLED, LOW);
  digitalWrite(st3GLED, LOW);
  }
  // Check which station the train is at and control the LEDs accordingly
  else
  {
    if (distance1 < 10) {
    // Train is at station 1
    setStation1LEDs();
    Serial.println("Train is at station 1 and no train at station 2");
  } else if (distance2 < 10) {
    // Train is at station 2
    Serial.println("Train is at station 2 and the next train should slow down at station 1 ");
    setStation2LEDs();
  } else if (distance3 < 10) {
    // Train is at station 3
    setStation3LEDs();
    Serial.println("no train is on the track.");
  }
  }
}

long measureDistance(int triggerPin, int echoPin) {
  // Measure the distance using an ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = ((0.017)*duration); // Calculate distance in centimeters
  
  return distance;
}

void turnOffAllLEDs() {
  // Turn off all LEDs
  digitalWrite(st1RLED, LOW);
  digitalWrite(st1YLED, LOW);
  digitalWrite(st1GLED, LOW);
  
  digitalWrite(st2RLED, LOW);
  digitalWrite(st2YLED, LOW);
  digitalWrite(st2GLED, LOW);
  
  digitalWrite(st3RLED, LOW);
  digitalWrite(st3YLED, LOW);
  digitalWrite(st3GLED, LOW);
}

void setStation1LEDs() {
  // Set station 1 LED to Red, station 2 LED to Yellow, and station 3 LED to Green
  digitalWrite(st1RLED, HIGH);
  digitalWrite(st2RLED, LOW);
  digitalWrite(st3RLED, LOW);
  
  digitalWrite(st1YLED, LOW);
  digitalWrite(st2YLED, LOW);
  digitalWrite(st3YLED, LOW);
  
  digitalWrite(st1GLED, LOW);
  digitalWrite(st2GLED, HIGH);
  digitalWrite(st3GLED, HIGH);
}

void setStation2LEDs() {
  // Set station 1 LED to Yellow, station 2 LED to Red, and station 3 LED to Green
  digitalWrite(st1RLED, LOW);
  digitalWrite(st2RLED, HIGH);
  digitalWrite(st3RLED, LOW);
  
  digitalWrite(st1YLED, HIGH);
  digitalWrite(st2YLED, LOW);
  digitalWrite(st3YLED, LOW);
  
  digitalWrite(st1GLED, LOW);
  digitalWrite(st2GLED, LOW);
  digitalWrite(st3GLED, HIGH);
}

void setStation3LEDs() {
  // Set station 1 LED to Green, station 2 LED to Yellow, and station 3 LED to Red
  digitalWrite(st1RLED, LOW);
  digitalWrite(st2RLED, LOW);
  digitalWrite(st3RLED, HIGH);
  
  digitalWrite(st1YLED, LOW);
  digitalWrite(st2YLED, LOW);
  digitalWrite(st3YLED, LOW);
  
  digitalWrite(st1GLED, HIGH);
  digitalWrite(st2GLED, HIGH);
  digitalWrite(st3GLED, LOW);
}
