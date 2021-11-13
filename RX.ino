
void setup() {
  //defines all pins used as output or serial connection (always defined as using pins 0 & 1)
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
Serial.begin(4800, SERIAL_8N1);
}
//Main system operating loop
void loop() {
  //jump defined and defining/resetting all variables
  skip: int Address = 0;
  int Counter = 0;
  bool OutArray[8]={false,false,false,false,false,false,false,false};
  //checks to see if anything is in serial buffer and runs if there is something.
  if(Serial.available()>0){
    //stores addres from serial master transmission to inturpret and write out.
    Address = Serial.read();
    //reserved 0xFF for special transmission of pulse for Flip Flop clock
    if (Address == 255){
      digitalWrite(10, HIGH);
      delay(5);
      digitalWrite(10, LOW);
      goto skip;
    }
    //writes out 8 bit address for conditions other than buffer empty or special reserved address
    while(Address > 0 && Address < 255){
      //converts address to boolean array for output
      if((Address % 2) == 1){
        OutArray[Counter] = true;
        Address--;
      }else{
        OutArray[Counter] = false;
      }
      Address /= 2;
      Counter++;
    }
    //writes out array to individual GPIO pins 2-9
    for(int i = 0; i < 8; i++){
      if(OutArray[i]){
       digitalWrite((i+2), HIGH); 
      }else{
        digitalWrite((i+2), LOW);
      }
    }
  }
}
