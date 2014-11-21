//initialize variables

String command;
String pin;
boolean analog=false;
int pinnum=0;
boolean validpin=false;
int numofpins=0;
int numofanpins=0;
int initpins[70];
int pwmpins[15];

void setup(){
  Serial.begin (9600); 
  setboard();
}

void loop(){

  if (Serial.available()){
    //read serial information to variables
    serialread();
    //set pin variables
    pinset(); 
    //if the pin entered is valid, the check if command is valid and if so excute it
    if (validpin==true){
      //do command 
      runcommand();
    }
  }
}

void serialread(){
  //initalize all variable to be blank
  String input="";
  char inchar=0;

  int comma;
  pin="";
  command="";

  //while serial char isnt ";" continue reading
  while(inchar !=59) {
    if (Serial.available()){
      //read character from serial port, if there is a character available
      inchar = Serial.read(); 
      //add inchar to input
      input.concat(inchar);
      //temp++;
    }
  }

  comma=input.indexOf(",");

  pin = input.substring(0,comma);
  command=input.substring(comma+1,input.length()-1);
}

void pinset(){
  //reset values
  pinnum=0;
  analog=true;
  validpin=true;
  if (pin.substring(0,1)=="a"|| (pin.substring(0,1)=="A")) {
    analog=true;
    if (pin.length()>3){
      Serial.println ("Invaild input for pin"); 
      validpin=false;
    }
    else{
      if(isnum(pin.substring(1,pin.length()+1))==true){
        pinnum=pin.substring (1,pin.length()+1).toInt();
        if (pinnum<0||pinnum>numofanpins){
          Serial.println ("Invaild input for pin");
          validpin=false;
        }
      }
      else{
        Serial.println ("Invaild input for pin");
        validpin=false;
      }
    }
  } 
  else {
    analog=false;
    if (pin.length()>2){
      Serial.println ("Invaild input for pin"); 
      validpin=false;
    }
    else{
      if(isnum(pin.substring(0,pin.length()+1))==true){
        pinnum=pin.substring (0,pin.length()+1).toInt();
        //check if pin number of valid for the arduino selected
        if (pinnum<1||pinnum>numofpins){
          Serial.println ("Invaild input for pin");
          validpin=false;
        }
      }
      else{
        Serial.println ("Invaild input for pin");
        validpin=false;
      }
    }
  }
}

boolean isnum(String in){
  //for each character in string in, check if it is a number and if not return false, else return true
  for (int i=0;i<in.length();i++){
    if (isDigit(in.charAt(i))==false){
      return false;
    }
  } 
  return true;
}

void setboard(){
  char inchar=0;
  Serial.println ("Please select your arduino");
  Serial.println ("1. Uno");
  Serial.println ("2. Mega");

  while (numofpins==0){
    if (Serial.available()){
      inchar = Serial.read(); 
      
      //if serial input is 2 then initialize uno
      if (inchar==49){
        numofpins=13;
        //boolean initpins[13];
        numofanpins=5;
        pwmpins[0]=3;
        pwmpins[1]= 5;
        pwmpins[2]=6;
        pwmpins[3]=9;
        pwmpins[4]=10;
        pwmpins[5]=11;
        Serial.println ("Arduino Uno initialized, enter command");
      } 
      //if serial input is 2 then initialize mega
      else if (inchar==50){
        numofpins=53;
        numofanpins=16;
        pwmpins[0]=2;
        pwmpins[1]=3;
        pwmpins[2]=4;
        pwmpins[3]=5;
        pwmpins[4]=6;
        pwmpins[5]=7;
        pwmpins[6]=8;
        pwmpins[7]=9;
        pwmpins[8]=10;
        pwmpins[9]=11;
        pwmpins[10]=12;
        pwmpins[11]=13;
        pwmpins[12]=44;
        pwmpins[13]=45;
        pwmpins[14]=46;

        Serial.println ("Arduino Mega initialized, enter command");
      }
      else{
        Serial.println ("Please enter a valid selection");
      }
    } 
  }
}

void runcommand(){

  //if command is o or output, set selected pin to be output
  if (command=="o"||command=="output"||command=="OuTPUT"){
    if (analog==true){
      Serial.println ("Cannot initialize analog pin");
    } 
    else {
      Serial.println ("Pin "+pin+ " set to output");
      pinMode (pinnum,OUTPUT);
      initpins[pinnum-1]=2;
    }
  }
  //if command is i or input, set selected pin to be an input
  else if (command=="i"||command=="input"||command=="INPUT"){
    if (analog==true){
      Serial.println ("Cannot initialize analog pin");
    } 
    else {
      Serial.println ("Pin "+pin+" set to input");
      pinMode (pinnum,INPUT);
      initpins[pinnum-1]=1;
    }
  }

  else if (command=="1"||command=="HIGH"||command=="high"||command=="h"){
    if (analog==true){
      Serial.println ("Cannot set analog pin to high");
    } 
    else {
      //check if pin has been set to output
      if (initpins[pinnum-1]==2){
        Serial.println ("Pin "+pin+" set to high");
        digitalWrite (pinnum,HIGH);
      }
      else{
        Serial.println ("Pin "+ pin+" has not been initialized");
      }
    }
  }

  else if (command=="0"||command=="LOW"||command=="low"||command=="l"){
    if (analog==true){
      Serial.println ("Cannot set analog pin to low");
    } 
    else {
      //check if pin has been set to output
      if (initpins[pinnum-1]==2){
        Serial.println ("Pin "+pin+" set to low");
        digitalWrite (pinnum,LOW);
      }
      else{
        Serial.println ("Pin "+ pin+" has not been initialized");
      }
    }
  }

  else if (command=="r"||command=="read"||command=="READ"){
    if (analog==true){
      //Serial.print ("Reading from analog pin "+pinnum+" is");
      Serial.println (analogRead (pinnum));
    } 
    else {
      //check if pin has been set to output if it hasnt, 
      if (initpins[pinnum-1]==1){
        //Serial.print ("Reading from digital pin ");
        Serial.println (digitalRead (pinnum));
      }
      else{
        Serial.println ("Pin "+ pin+" has not been initialized");
      }
    }
  }
  //else check if it is pwm
  else if (isnum(command)==true){

    if (analog==true){
      Serial.println ("Cannot use analog pins with this command");
    } 

    else {
      //check if pin has been set to output
      if (initpins[pinnum-1]==2){

        if(arraysearch(pwmpins,15,pinnum)>0){
          int pwm=command.toInt();
          if (pwm>0&&pwm<256){

            Serial.println ("Pin " + pin + " set to "+ pwm);
            analogWrite (pinnum,pwm); 

          }
          else {
            Serial.println ("Invald value for PWM");
          }
        } 
        else {
          Serial.println ("Invaild pin selection");
        }


      }
      else{
        Serial.println ("Pin "+ pin+" has not been initialized");
      }
    }
  }
}

int arraysearch(int inarray[],int length, int search){
  for (int i=0; i<length; i++){
    if (inarray[i]==search){
      return i; 
    }
  }
  return 0;
}



























