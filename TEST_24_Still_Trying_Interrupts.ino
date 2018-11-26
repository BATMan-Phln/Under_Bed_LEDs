/*
 * 
 *  Use the DIY button codes to set the preset colors and brightness as needed
 *  Need housing for the IR emitter
 *  Need housing for the IR receiver
 *  Need housing for the Arduino Leonardo
 *  
 *  Can this have an emergency battery backup to turn on medium red when power fails?  (NC Relay)?
 *      This will have to reset to off after a few minutes once power is restored.
 * 
 */
#include "boarddefs.h"
#include "IRremoteInt.h"
#include "ir_Lego_PF_BitStreamEncoder.h"
#include "IRremote.h"


int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Since these are interrupts they don't need declarations )-----*/
            //INTERRUPT PINS Micro, Leonardo 0, 1, 2, 3, 7  (Ordered 3, 2, 0, 1, 7) - 3 is for IR Emitter ONLY
volatile  int pir1 = 2;       //Pick some inputs for the 3 PIR's - PIR 1 = Dad's side
// COMBINED WITH MomsPIRs - volatile  int pir2 = ;      //PIR 2 = Foot 
volatile  int pir3 = 0;       //PIR 3 = Mom's side

volatile  int btnPanic = 1;      //Pick some inputs for the 2 bedside buttons

      /*-----( THIS WON'T WORK!  THE IR EMITTER HAS TO BE ON PIN 3 )-----*/
// int btnDad = ;   //Put both buttons on one Interrupt pin (3)
        // Don't forget to debounce buttons

volatile int rly =  7 ;       //Input from power loss relay to trigger a specific color/brightness

int ldr = A0 ;       //Analog pin if used - Should we include a photoresistor to prevent the lights in daylight?

/* -------- I'll have to work out min/max values for the LDR --------- */
int ldrValue = 150;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);
IRsend irsend;
decode_results results;      // create instance of 'decode_results'


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);

//SET UP PINS
  pinMode(btnPanic, INPUT);     //One button on each bed table turn turn lights on bright white
  pinMode(A0, INPUT);           //Analog pin for the LDR input
  
//Digital interrupt       HIGH might not work - Since the PIR's stay HIGH for a set time I was hoping to use that
  attachInterrupt(0, MomsPIRs, HIGH);     //Set pin 2 to turn LED's on red medium brightness PIR sensors in HIGH state
  attachInterrupt(1, DadsPIRs, HIGH);     //Set pin 3 to turn on all lights bright white when button is pushed
  attachInterrupt(2, Panic, RISING);      //Set pin 3 to turn on all lights bright white when button is pushed
  attachInterrupt(3, PwrOut, RISING);     //Set pin 3 to turn on all lights bright white when button is pushed

 irrecv.enableIRIn(); // Start the receiver
  Serial.println("IR Receiver Button Decode");

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
        irrecv.enableIRIn(); // Start the receiver
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/


//Interrupt 0 - LEDs pink medium
void MomsPIRs()
  {
      irsend.sendNEC(0xFF30CF, 32);      //Turns LEDs on medium pink - DIY 1
  }

//Interrupt 1 - LEDs on my side only purple medium
void DadsPIRs()
  {
      irsend.sendNEC(0xFFB04F, 32);      //Turns LEDs on my side only on medium purple - DIY 2
  }

//Interrupt 2 - LEDs bright white
void Panic()
  {
      irsend.sendNEC(0xFF708F, 32);      //Turns LEDs on bright white - DIY 3
  }


//Interrupt 3 - LEDs fadiing up/down 
void PwrOut()
{

      //When power goes out a relay switches to battery and turns all lights fadiing up/down  - DIY 4

      irsend.sendNEC(0xFF10EF, 32);      //Turns LEDs on fadiing up/down 
  
}

/*-----( END INTERRUPTS )-----*/

void LDRSwitch()
{
        analogRead(ldr);
      if(ldr > ldrValue){
        //SOMEHOW STOP LIGHTS FROM ACTIVATING
      }
}

void translateIR() // takes action based on IR code received


// describing Remote IR codes 

{

  switch(results.value)

  {

  case 0xFF3AC5: Serial.println(" UP") ;    irsend.sendNEC(0xFF3AC5, 32) ; break;   //UP  irsend.sendNEC(0xFF1AE5, 32); 
  case 0xFF1AE5: Serial.println(" RED");    irsend.sendNEC(0xFF1AE5, 32) ; break;   //RED
  case 0xFF2AD5: Serial.println(" R2");     irsend.sendNEC(0xFF2AD5, 32) ; break;   //R2
  case 0xFF0AF5: Serial.println(" OR");     irsend.sendNEC(0xFF0AF5, 32) ; break;   //OR
  case 0xFF38C7: Serial.println(" OR2");    irsend.sendNEC(0xFF38C7, 32) ; break;   //OR2
  case 0xFF18E7: Serial.println(" YELLOW"); irsend.sendNEC(0xFF18E7, 32) ; break;
  case 0xFF28D7: Serial.println(" RUP");    irsend.sendNEC(0xFF28D7, 32) ; break;
  case 0xFF08F7: Serial.println(" RDN");    irsend.sendNEC(0xFF08F7, 32) ; break;
  case 0xFF30CF: Serial.println(" DIY1");   irsend.sendNEC(0xFF30CF, 32) ; break;     //Program this for medium red
  case 0xFF10EF: Serial.println(" DIY4");   irsend.sendNEC(0xFF10EF, 32) ; break;
  case 0xFF20DF: Serial.println(" J3");     irsend.sendNEC(0xFF20DF, 32) ; break;
//END COL ONE
  

  case 0xFFBA45: Serial.println(" DN") ;   irsend.sendNEC(0xFFBA45, 32) ; break;   
  case 0xFF9A65: Serial.println(" G");     irsend.sendNEC(0xFF9A65, 32) ; break;   
  case 0xFFAA55: Serial.println(" G2");    irsend.sendNEC(0xFFAA55, 32) ; break;  
  case 0xFF8A75: Serial.println(" G3");    irsend.sendNEC(0xFF8A75, 32) ; break;   
  case 0xFFB847: Serial.println(" G4");    irsend.sendNEC(0xFFB847, 32) ; break;   
  case 0xFF9867: Serial.println(" G5");    irsend.sendNEC(0xFF9867, 32) ; break;
  case 0xFFA857: Serial.println(" GUP");   irsend.sendNEC(0xFFA857, 32) ; break;
  case 0xFF8877: Serial.println(" GDN");   irsend.sendNEC(0xFF8877, 32) ; break;
  case 0xFFB04F: Serial.println(" DIY2");  irsend.sendNEC(0xFFB04F, 32) ; break;     //Program this for bright white
  case 0xFF906F: Serial.println(" DIY5");  irsend.sendNEC(0xFF906F, 32) ; break;
  case 0xFFA05F: Serial.println(" J7");    irsend.sendNEC(0xFFA05F, 32) ; break;
//END COL 2

  case 0xFF827D: Serial.println(" STOP") ; irsend.sendNEC(0xFF827D, 32) ; break;   
  case 0xFFA25D: Serial.println(" B");     irsend.sendNEC(0xFFA25D, 32) ; break;   
  case 0xFF926D: Serial.println(" B2");    irsend.sendNEC(0xFF926D, 32) ; break;  
  case 0xFFB24D: Serial.println(" B3");    irsend.sendNEC(0xFFB24D, 32) ; break;   
  case 0xFF7887: Serial.println(" B4");    irsend.sendNEC(0xFF7887, 32) ; break;   
  case 0xFF58A7: Serial.println(" B5");    irsend.sendNEC(0xFF58A7, 32) ; break;
  case 0xFF6897: Serial.println(" BUP");   irsend.sendNEC(0xFF6897, 32) ; break;
  case 0xFF48B7: Serial.println(" BDN");   irsend.sendNEC(0xFF48B7, 32) ; break;
  case 0xFF708F: Serial.println(" DIY3");  irsend.sendNEC(0xFF708F, 32) ; break;
  case 0xFF50AF: Serial.println(" DIY6");  irsend.sendNEC(0xFF50AF, 32) ; break;
  case 0xFF609F: Serial.println(" FADE3"); irsend.sendNEC(0xFF609F, 32) ; break;
//END COL 3


  case 0xFF02FD: Serial.println(" OFF") ;  irsend.sendNEC(0xFF02FD, 32) ; break;  
  case 0xFF22DD: Serial.println(" W");     irsend.sendNEC(0xFF22DD, 32) ; break;   
  case 0xFF12ED: Serial.println(" P1");    irsend.sendNEC(0xFF12ED, 32) ; break; 
  case 0xFF32CD: Serial.println(" P2");    irsend.sendNEC(0xFF32CD, 32) ; break;   
  case 0xFFF807: Serial.println(" LB1");   irsend.sendNEC(0xFFF807, 32) ; break;   
  case 0xFFD827: Serial.println(" LB2");   irsend.sendNEC(0xFFD827, 32) ; break;
  case 0xFFE817: Serial.println(" QUICK"); irsend.sendNEC(0xFFE817, 32) ; break;
  case 0xFFC837: Serial.println(" SLOW");  irsend.sendNEC(0xFFC837, 32) ; break;
  case 0xFFF00F: Serial.println(" AUTO");  irsend.sendNEC(0xFFF00F, 32) ; break;
  case 0xFFD02F: Serial.println(" FLASH"); irsend.sendNEC(0xFFD02F, 32) ; break;
  case 0xFFE01F: Serial.println(" FADE7"); irsend.sendNEC(0xFFE01F, 32) ; break;
//END COL 4  
  
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} 
