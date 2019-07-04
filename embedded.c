// INCOMPLETE
// All memory locations are given in the question and are assumed to be defined in the header file,
// which is shown in the readme. C-style pointers are used to access the data members of these memory locations.

void Init(){
  // initialize the timer
  *TIMER_START_LO = 0x00005008;
  *TIMER_START_HI = 0x0000500C;
  *TIMER_STATUS = 0;
  *TIMER_CONTROL = 0x7;           // 0x0111, enable bottom 3 bits
  
  // initialize the pushbutton
  *BUTTONS_MASK = 0x1;            // ienable bit
  *BUTTONS_EDGE = 0;
  
  // initialize the LEDs
  *GREEN_LEDS = 0;                // turns all LEDs off, alternatively 0x3FFF for all LEDs on. 
  
  // FPGA NIOS2 specific interupt enable functions
  NIOS2_WRITE_IENABLE(0x3);       // first bit enables timer, second bit enables pushbutton. 
  NIOS2_WRITE_STATUS(0x1);       
}

void PrintChar(unsigned int ch){
  while( (*JTAG_UART_STATUS & 0xFFFF0000) == 0 ){ // the top 4 bits will change when JTAG status flag is ready 
    // do nothing, wait for status flag to be ready
  }
  // data is now ready to be sent
  *JTAG_UART_DATA = ch;
}

void interrupt_handler(){
  int ipending;
  ipending = NIOS2_READ_IPENDING();
  if ( (ipending & 0x1) == 1 ){
    // reset interupt source
  
  }
}

