#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define temp_rx 2                                          //define what pin rx is going to be
#define temp_tx 3                                          //define what pin tx is going to be

#define press_rx 4
#define press_tx 5

#define ph_rx 6
#define ph_tx 7

#define conduct_rx 8
#define conduct_tx 9

SoftwareSerial temp_serial(temp_rx, temp_tx);                      //define how the soft serial port is going to work
SoftwareSerial press_serial(press_rx, press_tx);
SoftwareSerial ph_serial(ph_rx, ph_tx);
SoftwareSerial conduct_serial(conduct_rx, conduct_tx);

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


void print_EC_data(void) {                            //this function will pars the string  

  char sensorstring_array[30];                        //we make a char array
  char *EC;                                           //char pointer used in string parsing
  char *TDS;                                          //char pointer used in string parsing
  char *SAL;                                          //char pointer used in string parsing
  char *GRAV;                                         //char pointer used in string parsing
  float f_ec;                                         //used to hold a floating point number that is the EC
  
  sensorstring.toCharArray(sensorstring_array, 30);   //convert the string to a char array 
  EC = strtok(sensorstring_array, ",");               //let's pars the array at each comma
  TDS = strtok(NULL, ",");                            //let's pars the array at each comma
  SAL = strtok(NULL, ",");                            //let's pars the array at each comma
  GRAV = strtok(NULL, ",");                           //let's pars the array at each comma

  Serial.print("EC:");                                //we now print each value we parsed separately
  Serial.println(EC);                                 //this is the EC value

  Serial.print("TDS:");                               //we now print each value we parsed separately
  Serial.println(TDS);                                //this is the TDS value

  Serial.print("SAL:");                               //we now print each value we parsed separately
  Serial.println(SAL);                                //this is the salinity value

  Serial.print("GRAV:");                              //we now print each value we parsed separately
  Serial.println(GRAV);                               //this is the specific gravity
  Serial.println();                                   //this just makes the output easier to read
  
//f_ec= atof(EC);                                     //uncomment this line to convert the char to a float
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

float takePressure() {
// Take pressure reading
// Todo: Check don't need to send anything to temperature probe
    char inchar;
    bool press_sensor_string_complete = false;
    unsigned long press_start = millis();

    while (press_serial.available() > 0 && press_string_complete == false) {
        char press_inchar = (char)press_serial.read();              
        press_sensorstring += inchar;
        if (inchar == '\r') {                             
            press_sensor_string_complete = true;                  
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

float takePh() {
// Take pressure reading
// Todo: Check don't need to send anything to temperature probe
    char inchar;
    bool press_sensor_string_complete = false;
    unsigned long press_start = millis();

    while (press_serial.available() > 0 && press_string_complete == false) {
        char press_inchar = (char)press_serial.read();              
        press_sensorstring += inchar;
        if (inchar == '\r') {                             
            press_sensor_string_complete = true;                  
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

float takeConduct() {
// Take pressure reading
// Todo: Check don't need to send anything to temperature probe
    char inchar;
    bool press_sensor_string_complete = false;
    unsigned long press_start = millis();

    while (press_serial.available() > 0 && press_string_complete == false) {
        char press_inchar = (char)press_serial.read();              
        press_sensorstring += inchar;
        if (inchar == '\r') {                             
            press_sensor_string_complete = true;                  
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

      case "press":
        //Todo: check pressure units
        float presresult = takePressure();
        Serial.print(presresult);
        Serial.println( " Bar?");
        break;

      default:
        Serial.println("Not implemented yet");
        break;
    }

  }

}