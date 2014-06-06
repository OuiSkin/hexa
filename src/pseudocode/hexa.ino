// Name the LEDs
int led_1 = 13;
int led_2 = 12;
int led_3 = 11;
int led_4 = 10;
int led_5 = 9;
int led_6 = 8;

// Analog input pin with the sensor
const int analogInPin = A0;  
int sensorValue = 0;  

// Prototypes
void blink(int);

// Wake the Hexa - start looping
void setup()  {
  // initialize digital pins as an output.
  pinMode(led_1, OUTPUT);     
  pinMode(led_2, OUTPUT);     
  pinMode(led_3, OUTPUT);     
  pinMode(led_4, OUTPUT);     
  pinMode(led_5, OUTPUT);     
  pinMode(led_6, OUTPUT);     
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
}

void loop()  {
  // LED 1 blinks
  blink(led_1);
  
  // Measure Temperature && Humidity 
  /* 
    TO BE IMPLEMENTED
  */
  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            

  // Place the sensor on the skin
  if (sensorValue > 0)  	// Place on zone 1 && value > 0
  {
    int sum = 0;
    
    // Records 10 measures   
    for (int i = 0; i < 10; i++)
    {
      blink(led_1);

      int zone1 = analogRead(analogInPin);
      
      // if one measure is null exit
      if (zone1 == 0)
        break;
      
      sum += zone1;
              
      Serial.println(i);
      Serial.print(zone1);
      delay(500);
    }
    
    Serial.print("the average of zone 1 is");
    Serial.println(sum/10);
    
    light(led_1);
    
    delay(5000);
    sensorValue = analogRead(analogInPin);          
    
  }  
  
  Serial.println("done");
  
		// Compute the average
		// Store the average
		// LED 1 stops blinking 
		// LED 2 starts blinking
}




	// Place on zone 2 && value > 0
                // Records measures during 2 secs
                // Compute the average
                // Store the average
                // LED 2 stops blinking 
                // LED 3 starts blinking 
        // Place on zone 3 && value > 0
                // Records measures during 2 secs
                // Compute the average
                // Store the average
                // LED 3 stops blinking
                // LED 4 starts blinking
        // Place on zone 4 && value > 0
                // Records measures during 2 secs
                // Compute the average
                // Store the average
                // LED 4 stops blinking
                // LED 5 starts blinking
        // Place on zone 5 && value > 0
                // Records measures during 2 secs
                // Compute the average
                // Store the average
                // LED 5 stops blinking
                // LED 6 starts blinking
        // Place on zone 6 && value > 0
                // Records measures during 2 secs
                // Compute the average
                // Store the average
                // LED 6 stops blinking

// Wait 5 secs

// Transmit values stored

// LEDs switch off

void blink(int led)  {
  digitalWrite(led, HIGH); 
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
} 

void light(int led)  {
  digitalWrite(led, HIGH); 
} 

  

