// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

// 1. Pre-processor Directives Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses
// TExaS.o is the object code for the real-board grader

#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control


// 2. Declarations Section
//   Global Variables
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED blue )

void Delay100ms(unsigned long time);

// basic functions defined at end of startup.s
//   Function Prototypes
void PortF_Init(void);
void Delay(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable


int main(void){ unsigned long volatile delay;
  TExaS_Init(SW_PIN_PF4,LED_PIN_PF2); 
  // TExaS_Init initializes the real board grader for lab 6
  PortF_Init();        // Call initialization of port PF4, PF3, PF2, PF1, PF0    
  EnableInterrupts();  // The grader uses interrupts
	

	

			
			
while(1){		
				
		Delay100ms(1);      // delay about 100 ms
	SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
	if (!SW1){											//switch is pressed
		GPIO_PORTF_DATA_R ^=  0x04;    //
		}
		else {
			GPIO_PORTF_DATA_R = 0x04;
				}
	
		
	  
	}
    
}
// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED -only PF2 is used
// Inputs: 1
// Outputs: 1
// Notes: These ? pins are connected to hardware on the LaunchPad


void PortF_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4, input, ,PF2, output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) Clear the PF4 and PF2 bits in Port F AFSEL to disable alternate functions
  GPIO_PORTF_PUR_R = 0x10;          // enable pullup resistors on PF4,       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0
  //GPIO_PORTF_DATA_R = 0xE;					// 8) Set the PF2 bit in Port F DATA so the LED is initially ON
	GPIO_PORTF_DATA_R = 0x04;
}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 100 ms
  }
}