// INCOMPLETE
// All memory locations are given in the question and are assumed to be defined in the header file,
// which is shown in the readme. C-style pointers are used to access the data members of these memory locations.

#include "nios2_control.h"
// addresses given in question. 
#define TIMER_STATUS ((volatile unsigned int*) 0x00005000)
#define TIMER_CONTROL ((volatile unsigned int*) 0x00005004)
#define TIMER_START_LO ((volatile unsigned int*) 0x00005008)
#define TIMER_START_HI ((volatile unsigned int*) 0x0000500C)

#define JTAG_UART_DATA ((volatile unsigned int*) 0x00006800)
#define JTAG_UART_STATUS ((volatile unsigned int*) 0x00006804)

#define GREEN_LEDS ((volatile unsigned int*) 0x00004A80) // output port
#define INPORT ((volatile unsigned int*) 0x00004A00)

int timer_flag;

void Init(){
  // initialize the timer
  *TIMER_START_LO = 0x4B40;
  *TIMER_START_HI = 0x004C;
  *TIMER_STATUS = 0;
  *TIMER_CONTROL = 0x7;           // 0x0111, enable bottom 3 bits
  timer_flag = 0;
  
  // initialize the LEDs
  *GREEN_LEDS = 0x0F;             // turns on 4 of 8 LEDs, 0000 1111
  
  // FPGA NIOS2 specific interupt enable functions
  NIOS2_WRITE_IENABLE(0x1);       // first bit enables timer, second bit enables pushbutton. 
  NIOS2_WRITE_STATUS(0x1);       
}

void PrintChar(unsigned int ch){
  while( (*JTAG_UART_STATUS & 0xFFFF0000) == 0 ){ // the top 4 bits will change when JTAG status flag is ready 
    // do nothing, wait for status flag to be ready
  }
  // data is now ready to be sent
  *JTAG_UART_DATA = ch;
}

void UpdateLEDs(){
  unsigned int state;
  state = *GREEN_LEDS;
  if ( (state & 0x0F) == 1){
    *GREEN_LEDS = 0xF0; // swap LEDs 
  }
  else if ( (state & 0xF0) == 1){
    *GREEN_LEDS = 0x0F; // swap LEDs back 
  }
}

void interrupt_handler(){
  int ipending;
  ipending = NIOS2_READ_IPENDING();
  if ( (ipending & 0x1) == 1 ){
    // reset interupt source, which is a timer in this case
    *TIMER_STATUS = 0;
    timer_flag = 1;
  }
  // if there are multiple interrupt sources, check as well and do similiar using...
  // if ( (ipending & 0x2) == 2 ){ , same logic as before and do whatever requirements are necessary. 
}

int main(){
  int num_zeros = 0;
  Init();
  float led_time = 0;
  float read_time = 0;
  while(1){
    
  }
  
}
      
      

