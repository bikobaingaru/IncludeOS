#ifndef CLASS_OS_H
#define CLASS_OS_H

#include <os>

extern char _BSS_START_, _BSS_END_;

//#include "globals.h"
//#include "class_service.h"

class OS{
  
 private:  
  static const char* boot_msg;
  
  //Call halt - i.e. wait for interrupts
  static void halt();  
        
 public:

//Receive a byte from port
  static uint8_t inb(int port);
  
  //Send a byte to port
  static void outb(int port, uint8_t data);
  
  //Write a character to serial port
  static int rswrite(char c);

  //Write a cstring to serial port
  static int rsprint(const char* ptr);

  static void start();
  
};


#endif
