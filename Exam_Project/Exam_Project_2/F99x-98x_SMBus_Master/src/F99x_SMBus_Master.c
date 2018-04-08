//-----------------------------------------------------------------------------
// F99x_SMBus_Master.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// Example software to demonstrate the SMBus interface in
// Master mode.
// - Interrupt-driven SMBus implementation
// - Only master states defined (no slave or arbitration)
// - 1-byte SMBus data holders used for each transmit and receive
// - Timer1 used as SMBus clock source
// - Timer3 used by SMBus for SCL low timeout detection
// - SCL frequency defined by SMBus 0 module in Configurator
// - SMB0CN_ARBLOST support included
// - Pinout:
//    P0.0 -> SDA (SMBus)
//    P0.1 -> SCL (SMBus)
//
//    P1.3 -> YELLOW_LED
//
//    P2.7 -> C2D (debug interface)
//
//    all other port pins unused
//
// How To Test:
//
// 1) Verify that J13 and J14 are not populated.
// 2) Ensure that jumpers are placed on the following:
//       J11:  PWR/WALL_PWR
//       J17:  VDD_PIN/PWR
// 3) Connect the device to another 'Fxxx device running SMBus - Slave code.
// 4) Connect the USB Debug Adapter to J4.
// 5) Turn the POWER switch (SW5) to the "ON" position.
// 6) Compile and download code to a 'F99x device on a C8051F99x-TB development
//    board by selecting Run -> Debug from the menus, clicking the Debug button
//    in the quick menu, or pressing F11.
// 7) Run the code by selecting Run -> Resume from the menus, clicking the
//    Resume button in the quick menu, or pressing F8:
//         a) The test will indicate proper communication with the slave by
//            toggling the YELLOW_LED on and off each time a value is sent and
//            received.
//         b) The best method to view the proper functionality is to run to
//            the indicated line of code in the TEST CODE section of main and
//            view the SMB_DATA_IN and SMB_DATA_OUT variables in the Watch
//            Window.
//
//
// Target:         C8051F99x-C8051F98x
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Command Line:   None
//
// Release 1.1 (BL)
//    - Updated Description / How to Test
//    - 13 JAN 2014
//
// Release 1.0
//    - Initial Revision (FB)
//    - 19 MAY 2010
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <compiler_defs.h>
#include <SI_C8051F990_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include <stdio.h>
#include "F99x_SMBus_Master.h"

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
U8 SMB_DATA_IN;                        // Global holder for SMBus data
                                       // All receive data is written here

U8 SMB_DATA_OUT;
U8 SMB_REG_OUT;
U8 START_SMB;
U8 RW_Reg; // Global holder for SMBus data.
                                       // All transmit data is read from here

U8 TARGET;                             // Target SMBus slave address

volatile bit SMB_BUSY;                 // Software flag to indicate when the
                                       // SMB_Read() or SMB_Write() functions
                                       // have claimed the SMBus

volatile bit SMB_RW;                   // Software flag to indicate the
                                       // direction of the current transfer

U16 NUM_ERRORS;                        // Counter for the number of errors.

SBIT (SDA, SFR_P0, 0);                 // SMBus on P0.0
SBIT (SCL, SFR_P0, 1);                 // and P0.1

LOCATED_VARIABLE_NO_INIT (reserved, U8, SEG_XDATA, 0x0000);

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SMB_Write (void);
void SMB_Read (void);
void T0_Wait_ms (U8 ms);
void SMB_Write_Reg(U8 Addr,U8 Reg, U8 Dat);
U8 SMB_Read_Reg(U8 Addr, U8 Reg);


//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
void UART_Init(int baudrate)
{
	SCON0 = 0x50;  // Asynchronous mode, 8-bit data and 1-stop bit
    TMOD = 0x20;  //Timer1 in Mode2.
   // TH1 = 256 - (24500000UL)/(long)(32*12*baudrate); // Load timer value for baudrate generation
    TH1 = (0x2B << TH1_TH1__SHIFT);
    TCON |= (1<<6);      //Turn ON the timer for Baud rate generation
}

void UART_Send(char c)
{
	SBUF0 = c;      // Load the data to be transmitted
	while(SCON0_TI==0);   // Wait till the data is trasmitted
	SCON0_TI = 0;
}
U8 SMB_Read_Reg(U8 Addr, U8 Reg)
{
	RW_Reg=0;
	TARGET = Addr;
	SMB_REG_OUT = Reg;
	START_SMB=1;// Define next outgoing byte
	SMB_Write();                     // Initiate SMBus write
	START_SMB=1;
	TARGET = Addr|0x01;             // Target the F3xx/Si8250 Slave for next								   // SMBus transfer
	SMB_Read();
	return SMB_DATA_IN;
}

void SMB_Write_Reg(U8 Addr,U8 Reg, U8 Dat)
{
	RW_Reg=1;
		TARGET = Addr;             // Target the F3xx/Si8250 Slave for next
		START_SMB=1;
		SMB_DATA_OUT = Dat;
		SMB_REG_OUT = Reg;// SMBus transfer
		SMB_Write();

		while(SMB_BUSY){
			;;
		}

}

int main (void)
{
	volatile U8 dat;                    // Test counter
	U8 i;                               // Dummy variable counters
	double a;
	//Enter default mode
	enter_DefaultMode_from_RESET();
	//printf("%d",0x22);
	// If slave is holding SDA low because of an improper SMBus reset or error
	while(!SDA)
	{
	  // Provide clock pulses to allow the slave to advance out
	  // of its current state. This will allow it to release SDA.
	  XBR2 = 0x40;                     // Enable Crossbar
	  SCL = 0;                         // Drive the clock low
	  for(i = 0; i < 255; i++);        // Hold the clock low
	  SCL = 1;                         // Release the clock
	  while(!SCL);                     // Wait for open-drain
									   // clock output to rise
	  for(i = 0; i < 10; i++);         // Hold the clock high
	  XBR2 = 0x00;                     // Disable Crossbar
	}

	enter_Mode2_from_DefaultMode();
	 UART_Init(57600);
	//printf("%d",0x22);
	//YELLOW_LED = LED_OFF;
	//printf("hej");
	dat = 0;                            // Output data counter
	NUM_ERRORS = 0;                     // Error counter

	SMB_Write_Reg(0x30,0x20,0x37);
	while (1)
	{






	  UART_Send(SMB_Read_Reg(0x30,0x2B));
	 // UART_Send('\n');
	  UART_Send('\r');
	  // Check transfer data
	  if(SMB_DATA_IN != 0x20)  // Received data match transmit data?
	  {
		 NUM_ERRORS++;                 // Increment error counter if no match
	  }

	  // Indicate that an error has occurred (YELLOW_LED no longer lit)

		 YELLOW_LED = !YELLOW_LED;

		 //YELLOW_LED= 1;

	  // Run to here to view the SMB_DATA_IN and SMB_DATA_OUT variables


	//  printf("weds");
	 for(a=0;a<100000;a++){
		 ;;
		 // Wait 50 ms until the next cycle
	 }
										// so that YELLOW_LED blinks slow
										// enough to see

	}

	// END TEST CODE---------------------------------------------------------------

	// NOTREACHED
	return 0;
}

//-----------------------------------------------------------------------------
// Support Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SMB_Write
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Writes a single byte to the slave with address specified by the <TARGET>
// variable.
// Calling sequence:
// 1) Write target slave address to the <TARGET> variable
// 2) Write outgoing data to the <SMB_DATA_OUT> variable
// 3) Call SMB_Write()
//
//-----------------------------------------------------------------------------
void SMB_Write (void)
{
   while (SMB_BUSY);                   // Wait for SMBus to be free.
   SMB_BUSY = 1;                       // Claim SMBus (set to busy)
   SMB_RW = 0;                         // Mark this transfer as a WRITE
   SMB0CN_STA = 1;                            // Start transfer
}

//-----------------------------------------------------------------------------
// SMB_Read
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Reads a single byte from the slave with address specified by the <TARGET>
// variable.
// Calling sequence:
// 1) Write target slave address to the <TARGET> variable
// 2) Call SMB_Write()
// 3) Read input data from <SMB_DATA_IN> variable
//
//-----------------------------------------------------------------------------
void SMB_Read (void)
{
   while (SMB_BUSY != 0);               // Wait for transfer to complete
   SMB_BUSY = 1;                       // Claim SMBus (set to busy)
   SMB_RW = 1;                         // Mark this transfer as a READ

   SMB0CN_STA = 1;                            // Start transfer

   while (SMB_BUSY);                   // Wait for transfer to complete
}

//-----------------------------------------------------------------------------
// T0_Wait_ms
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) U8 ms - number of milliseconds to wait
//                        range is full range of character: 0 to 255
//
// Configure Timer0 to wait for <ms> milliseconds using SYSCLK as its time
// base.
//
//-----------------------------------------------------------------------------
void T0_Wait_ms (U8 ms)
{

   while (ms) {
      TCON_TR0 = 0;                         // Stop Timer0
      TH0 = ((-(SYSCLK/1000)) >> 8);   // Overflow in 1ms
      TL0 = ((-(SYSCLK/1000)) & 0xFF);
      TCON_TF0 = 0;                         // Clear overflow indicator
      TCON_TR0 = 1;                         // Start Timer0
      while (!TCON_TF0);                    // Wait for overflow
      ms--;                            // Update ms counter
   }

   TCON_TR0 = 0;                            // Stop Timer0
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------