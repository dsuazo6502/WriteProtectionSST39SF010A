//predefining mux and enable pin numbers as a pseudonyme
#define WE 11
#define OE 12
#define CE 10
#define MUX 13
//predefining global variables and functions.
int Num = 0;
bool input = false;
bool DigitalArray[8] = {false,false,false,false,false,false,false,false};
//assigns bool variables to Digital Array(saves the slightest ammount of programming time)
void AssignArray(bool A,bool B,bool C,bool D,bool E,bool F,bool G,bool H){
  DigitalArray[0] = A;
  DigitalArray[1] = B;
  DigitalArray[2] = C;
  DigitalArray[3] = D;
  DigitalArray[4] = E;
  DigitalArray[5] = F;
  DigitalArray[6] = G;
  DigitalArray[7] = H;
}
//Function that writes current saved binary encoded bool array out to GPIO pins 2-9
void DigitalOut(){
   for(int i = 0; i < 8; i++){
      if(DigitalArray[i]){
       digitalWrite((i+2), HIGH); 
      }else{
        digitalWrite((i+2), LOW);
      }
   }
}
//tells slave to send pulse to Flip Flops
void Pulse(){
  Serial.write(255);
  delay(6);
}
//sends sequence to erase all data from flash memory chip
void ChipErase(){
  digitalWrite(CE, LOW);
  digitalWrite(MUX, HIGH);
  AssignArray(false,true,false,true,false,true,false,true);
  DigitalOut();
  delay(1);
  digitalWrite(WE, LOW);
  Pulse();
  AssignArray(true,false,true,false,true,false,true,false);
  digitalWrite(WE, HIGH);
  DigitalOut();
  delay(1);
  digitalWrite(WE, LOW);
  Pulse();
  AssignArray(false,false,false,false,false,false,false,true);
  digitalWrite(WE, HIGH);
  DigitalOut();
  delay(1);
  digitalWrite(WE, LOW);
  delay(1);
  AssignArray(false,true,false,true,false,true,false,true);
  digitalWrite(WE, HIGH);
  DigitalOut();
  delay(1);
  digitalWrite(WE, LOW);
  Pulse();
  AssignArray(true,false,true,false,true,false,true,false);
  digitalWrite(WE,HIGH);
  DigitalOut();
  delay(1);
  digitalWrite(WE, LOW);
  Pulse();
  AssignArray(false,false,false,false,true,false,false,false);
  digitalWrite(WE,HIGH);
  DigitalOut();
  delay(1);
  digitalWrite(WE,LOW);
  delay(3);
  digitalWrite(WE,HIGH);
  delay(120);
  digitalWrite(CE,HIGH);
  digitalWrite(MUX, LOW);
}
//writes a byte to flash memory address defined here
void WriteTo(bool A,bool B,bool C,bool D,bool E,bool F,bool G,bool H, int address){
  //sequence sent in order to subvert flash memory write protection
  digitalWrite(MUX,HIGH);
  AssignArray(false,true,false,true,false,true,false,true);
  digitalWrite(CE,LOW);
  DigitalOut();
  digitalWrite(WE,LOW);
  delay(1);
  AssignArray(true,false,true,false,true,false,true,false);
  digitalWrite(WE,HIGH);
  Pulse();
  DigitalOut();
  digitalWrite(WE,LOW);
  delay(1);
  AssignArray(false,false,false,false,false,true,false,true);
  digitalWrite(WE,HIGH);
  DigitalOut();
  Pulse();
  digitalWrite(WE,LOW);
  delay(1);
  //writes to the out array
  AssignArray(A,B,C,D,E,F,G,H);
  digitalWrite(WE,HIGH);
  //sends desired address location to slave
  Serial.write(address);
  //switches address MUXs to slave from flip flops
  digitalWrite(MUX,LOW);
  //completes GPIO pin output and outputs sequence of enables to write to flash memory
  DigitalOut();
  delay(6);
  digitalWrite(WE,LOW);
  delay(2);
  digitalWrite(WE,HIGH);
  digitalWrite(CE,HIGH);
  Serial.write(0);
}
//main program
void setup() {
//setting up pins for sequence
Serial.begin(4800, SERIAL_8N2);
delay(100);
pinMode(MUX, OUTPUT);
pinMode(WE, OUTPUT);
pinMode(OE,OUTPUT);
pinMode(CE, OUTPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
digitalWrite(WE, HIGH);
digitalWrite(OE, HIGH);
digitalWrite(CE, HIGH);
digitalWrite(MUX, LOW);
//Initializing flip flop chain to known position
for(int i = 0; i <= 17; i++){
  Pulse();
}
delay(3);
//my chosen test write sequence
ChipErase();
WriteTo(false,false,false,true,false,false,true,false,1);
WriteTo(true,false,true,false,false,true,true,false,2);
WriteTo(false,false,true,true,false,true,true,false,3);
WriteTo(false,false,true,true,false,true,true,false,4);
WriteTo(true,true,true,true,false,true,true,false,5);
WriteTo(false,false,false,false,false,true,false,false,6);
WriteTo(true,true,true,false,true,true,true,false,7);
WriteTo(true,true,true,true,false,true,true,false,8);
WriteTo(false,true,false,false,true,true,true,false,9);
WriteTo(false,false,true,true,false,true,true,false,10);
WriteTo(false,false,true,false,false,true,true,false,11);
WriteTo(true,false,false,false,false,true,false,false,12);
WriteTo(false,true,false,true,false,true,false,true,34);
}

void loop() {

}
