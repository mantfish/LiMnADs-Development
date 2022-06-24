// Include the SoftwareSerial library. It allows us to use serial communication.
#include <SoftwareSerial.h>

// Define temperature serial pins
#define temp_rx 2
#define temp_tx 3

// Define pressure serial pins
#define press_rx 4
#define press_tx 5

// Define ph serial pins
#define ph_rx 6
#define ph_tx 7

// Define conductivity pins
#define conduct_rx 8
#define conduct_tx 9

// Set up all the sensor serial ports
SoftwareSerial temp_serial(temp_rx, temp_tx);                      
SoftwareSerial press_serial(press_rx, press_tx);
SoftwareSerial ph_serial(ph_rx, ph_tx);
SoftwareSerial conduct_serial(conduct_rx, conduct_tx);

void setup() {           
  // Begin all the serial port

  Serial.begin(9600);  // This is the serial monitor / Raspberry Pi serial port                                 
  temp_serial.begin(9600);
  press_serial.begin(9600);
  ph_serial.begin(9600);
  conduct_serial.begin(9600);
}


float takeSensorReading(sensor_serial_port){
  // Fuction to take sernsor readings with the Ph, temperature, conductivity and pressure
  //  sensors

  String sensor_string = "";                                          // Create an empty string to store the output of the sensor  
  float reading;                                                      // Create a number which can store the value read by the sensor
  bool sensor_string_complete = false;                                // Set the reading complete variable to false
  unsigned long timer = millis();                                     // Start a timer

  // If there is still data coming in from the sensor, or if less then 10 seconds have passed, continue looping
  while (sensor_serial_port.available() > 0 && sensor_string_complete == false) {  
      char sensor_char = (char)sensor_serial_port.read();             // read a character from the serial port       
      sensor_string += sensor_char;                                   // Add this character to the sensor string       
      if (sensor_char == '\r') {                                      // if the character is newline, stop the loop                   
          sensor_string_complete = true;                  
      }

      if ( (millis() - timer) < 10000){                               // if more then 10 seconds have passed, return -1000 as the value.
          return -1000;
      }

  }

  if (isdigit(sensor_string[0])) {                                    // If the first vaulue of the data received from the sensor is a digit contineu           
      reading = sensor_string.toFloat();                              // make the sensor string a number
  }
  else {
      reading = -1000;                                                 // If the data is NOT a digit return -1000
  }

  return reading;
}


void loop() { 
  // Main loop of the program  
  if (Serial.available()) {                                           // If there is data in the serial port from the serial monitor / Raspberry Pi                    
    String measurmenttype = Serial.readString();                      // Read the string given by the serial monitor       
    switch(measurmenttype){                                           // Take what ever measurment is required optinos are "temp", "press", "ph" and "conduct"
      case "temp":
        float temp_result = takeSensorReading(temp_serial);
        Serial.print(temp_result);
        Serial.println( " Degrees");
        break;

      case "press":
        //Todo: check pressure units
        float pres_result = takeSensorReading(press_serial);
        Serial.print(pres_result);
        Serial.println( " Bar?");
        break;

      case "ph":
        float ph_result = takeSensorReading(ph_serial);
        Serial.print(ph_result);
        Serial.println(" pH");
        break;

      case "conduct":
        float conduct_result = takeSensorReading(conduct_serial);
        Serial.print(conduct_result);
        Serial.println(" micro s");
        break;

      default:
        // If the input to the serial port isn't temp, ph, condcut or press display not implemented yet
        Serial.println("Not implemented yet");
        break;
    }

  }

}