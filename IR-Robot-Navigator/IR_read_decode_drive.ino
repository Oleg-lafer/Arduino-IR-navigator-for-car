#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Define motor control pins
const int LeftPWM = 3;
const int LeftForward = 5;
const int LeftBackward = 4;

const int RightPWM = 6;
const int RightForward = 7;
const int RightBackward = 8;


void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

    // Set motor control pins as outputs
    pinMode(LeftPWM, OUTPUT);
    pinMode(LeftForward, OUTPUT);
    pinMode(LeftBackward, OUTPUT);

    pinMode(RightPWM, OUTPUT);
    pinMode(RightForward, OUTPUT);
    pinMode(RightBackward, OUTPUT);

    // Initialize motors (stopped)
    digitalWrite(LeftForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightForward, HIGH);
    digitalWrite(RightBackward, LOW);

    analogWrite(RightPWM, 0);
    analogWrite(LeftPWM, 0);

}



//Infinite loop
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value

    if (results.decode_type != UNKNOWN && results.value<0x100) {


      
    

      int HEX_recive= results.value;
      int Y_recieved = HEX_recive/16;
      int X_recieved = HEX_recive-16*Y_recieved;

      int Y_recieved_centerd = Y_recieved -7;
      int X_recieved_centerd = X_recieved -7;



      Serial.print("X recieved: "+String(X_recieved)+", X recieved centerd: "+String(X_recieved_centerd));
      Serial.println("");
      Serial.print("Y recieved: "+String(Y_recieved)+", Y recieved centerd: "+String(Y_recieved_centerd));


      move(X_recieved_centerd, Y_recieved_centerd);
    }
    Serial.println("");
    Serial.println("------------------------------------------------------------------------------------");

  }
}






//Dumps the result and prints the numeric received dada and type of remote
void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  // Serial.print("Raw (");
  // Serial.print(count, DEC);
  // Serial.print("): ");
  
  // for (int i = 1; i < count; i++) {
  //   if (i & 1) {
  //     Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
  //   }
  //   else {
  //     Serial.write('-');
  //     Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
  //   }
  //   Serial.print(" ");
  // }
  // Serial.println(); 
}



// -7 <= V <= 7
void move(int V_left, int V_right) {
    if(V_left>0){
      //left wheel moving forward
      digitalWrite(LeftForward, HIGH);   // Left motor forward
      digitalWrite(LeftBackward, LOW);   // Left motor not backward
    }else{
      //left wheel moving backward
      digitalWrite(LeftForward, LOW);  // Left motor not forward
      digitalWrite(LeftBackward, HIGH);  // Left motor backward
    }

    if(V_right>0){
      //right wheel moving forward
      digitalWrite(RightForward, HIGH);   // Right motor forward
      digitalWrite(RightBackward, LOW);   // Right motor not backward
    }else{
      //right wheel moving backward
      digitalWrite(RightForward, LOW);  // Right motor not forward
      digitalWrite(RightBackward, HIGH);  // Right motor backward
    }



    int left_PWM_value = map(abs(V_left), 0 ,7, 0, 255);
    int right_PWM_value = map(abs(V_right), 0 ,7, 0, 255);

    Serial.println("");
    Serial.println("Motor left is forawrd: "+String(V_left>0)+" speed: "+String(left_PWM_value));
    Serial.println("Motor right is forawrd: "+String(V_right>0)+" speed: "+String(right_PWM_value));
    Serial.println("");
  


    analogWrite(LeftPWM, left_PWM_value);   //  speed forward for left motor
    analogWrite(RightPWM, right_PWM_value);  //  speed forward for right motor
    delay(30);
}