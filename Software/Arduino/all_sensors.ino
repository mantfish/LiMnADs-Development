#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define temp_rx 2                                          //define what pin rx is going to be
#define temp_tx 3                                          //define what pin tx is going to be

SoftwareSerial temp_serial(temp_rx, temp_tx);                      //define how the soft serial port is going to work


String inputstring = "";                              
String sensorstring = "";                             
boolean input_string_complete = false;                
boolean sensor_string_complete = false;               
float temperature;                                    



void setup() {                                        
  Serial.begin(9600);                                 
  myserial.begin(9600);                               
  inputstring.reserve(10);                            
  sensorstring.reserve(30);                           
}


void serialEvent() {                                  
  inputstring = Serial.readStringUntil(13);           
  input_string_complete = true;                       
}


float takeTemperature() {
// Take temperature reading
// Todo: Check don't need to send anything to temperature probe
    char inchar;
    bool sensor_string_complete = false;
    unsigned long start = millis();

    while (temp_serial.available() > 0 && sensor_string_complete == false) {
        char inchar = (char)temp_serial.read();              
        sensorstring += inchar;
        if (inchar == '\r') {                             
            sensor_string_complete = true;                  
        }

        if ( (millis() - start) < 10000){
            return -1000;
        }

    }

    if (isdigit(sensorstring[0])) {                  
        temperature = sensorstring.toFloat();
    }
    else {
        temperature = -1000;
    }

    return temperature;
}

void loop() {   
  if (Serial.available()) {
    String measurmenttype = Serial.readString();
    switch(measurmenttype){
      case "temp":
        float tempresult = takeTemperature();
        Serial.print(tempresult);
        Serial.println( " Degrees");
        break;

      default:
        Serial.println("Not implemented yet");
        break;
    }

  }

}