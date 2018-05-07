//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_C8051F990_Register_Enums.h>
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS


//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	PCA_0_enter_DefaultMode_from_RESET();
	VREG_0_enter_DefaultMode_from_RESET();
	HFOSC_0_enter_DefaultMode_from_RESET();
	CLOCK_0_enter_DefaultMode_from_RESET();
	//TIMER01_0_enter_DefaultMode_from_RESET();
	TIMER16_2_enter_DefaultMode_from_RESET();
	UART_0_enter_DefaultMode_from_RESET();
	// [Config Calls]$
}


//================================================================================
// PCA_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCA_0_enter_DefaultMode_from_RESET(void) {
	// $[Watchdog Disable]
	// Stop Watchdog
	// If MCU is reset by WDT before it runs to main(), please disable it in SILABS_STARTUP.A51
	SFRPAGE = 0x00;
	PCA0MD &= ~PCA0MD_WDTE__BMASK;





}

//================================================================================
// VREG_0_enter_DefaultMode_from_RESET
//================================================================================
extern void VREG_0_enter_DefaultMode_from_RESET(void) {
	// $[REG0CN - Voltage Regulator Control]
	/*
	// OSCBIAS (High Frequency Oscillator Bias) = ENABLED (Enable the
	//     precision High Frequency Oscillator bias.)
	*/
	REG0CN = REG0CN_OSCBIAS__ENABLED;
	// [REG0CN - Voltage Regulator Control]$


}

//================================================================================
// HFOSC_0_enter_DefaultMode_from_RESET
//================================================================================
extern void HFOSC_0_enter_DefaultMode_from_RESET(void) {
	// $[OSCICL - High Frequency Oscillator Calibration]
	// [OSCICL - High Frequency Oscillator Calibration]$

	// $[OSCICN - High Frequency Oscillator Control]
	/*
	// IOSCEN (High Frequency Oscillator Enable) = ENABLED (High Frequency
	//     Oscillator enabled.)
	*/
	OSCICN |= OSCICN_IOSCEN__ENABLED;
	// [OSCICN - High Frequency Oscillator Control]$


}

//================================================================================
// CLOCK_0_enter_DefaultMode_from_RESET
//================================================================================
extern void CLOCK_0_enter_DefaultMode_from_RESET(void) {
	// $[CLKSEL - Clock Select]
	/*
	// CLKDIV (Clock Source Divider) = SYSCLK_DIV_1 (SYSCLK is equal to
	//     selected clock source divided by 1.)
	// CLKSL (Clock Source Select) = HFOSC (Clock derived from the internal
	//     precision High-Frequency Oscillator.)
	*/
	CLKSEL = CLKSEL_CLKDIV__SYSCLK_DIV_32 | CLKSEL_CLKSL__HFOSC;
	// [CLKSEL - Clock Select]$


}

//================================================================================
// PORTS_1_enter_Mode2_from_DefaultMode
//================================================================================
extern void PORTS_1_enter_Mode2_from_DefaultMode(void) {
	// $[P1 - Port 1 Pin Latch]

	SFRPAGE = 0x00;
	P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__OPEN_DRAIN | P1MDOUT_B2__OPEN_DRAIN
	| P1MDOUT_B3__PUSH_PULL | P1MDOUT_B4__OPEN_DRAIN | P1MDOUT_B5__OPEN_DRAIN
	| P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;
	// [P1MDOUT - Port 1 Output Mode]$

	// $[P1MDIN - Port 1 Input Mode]
	// [P1MDIN - Port 1 Input Mode]$

	// $[P1SKIP - Port 1 Skip]
	// [P1SKIP - Port 1 Skip]$

	// $[P1MASK - Port 1 Mask]
	// [P1MASK - Port 1 Mask]$

	// $[P1MAT - Port 1 Match]
	// [P1MAT - Port 1 Match]$

	// $[P1DRV - Port 1 Drive Strength]
	// [P1DRV - Port 1 Drive Strength]$


}

//================================================================================
// PBCFG_0_enter_Mode2_from_DefaultMode
//================================================================================
extern void PBCFG_0_enter_Mode2_from_DefaultMode(void) {
	// $[XBR2 - Port I/O Crossbar 2]
	/*
	// WEAKPUD (Port I/O Weak Pullup Disable) = PULL_UPS_ENABLED (Weak
	//     Pullups enabled (except for Ports whose I/O are configured for analog
	//     mode).)
	// XBARE (Crossbar Enable) = ENABLED (Crossbar enabled.)
	*/
	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED;
	// [XBR2 - Port I/O Crossbar 2]$

	// $[XBR0 - Port I/O Crossbar 0]
	/*
	// URT0E (UART I/O Output Enable) = DISABLED (UART I/O unavailable at
	//     Port pin.)
	// SPI0E (SPI I/O Enable) = DISABLED (SPI I/O unavailable at Port pins.)
	// SMB0E (SMBus0 I/O Enable) = ENABLED (SMBus0 I/O routed to Port pins.)
	// CP0E (Comparator0 Output Enable) = DISABLED (CP0 unavailable at Port
	//     pin.)
	// CP0AE (Comparator0 Asynchronous Output Enable) = DISABLED
	//     (Asynchronous CP0 unavailable at Port pin.)
	// SYSCKE (SYSCLK Output Enable) = DISABLED (SYSCLK unavailable at Port
	//     pin.)
	*/
	XBR0 = XBR0_URT0E__ENABLED | XBR0_SPI0E__DISABLED | XBR0_SMB0E__ENABLED
	| XBR0_CP0E__DISABLED | XBR0_CP0AE__DISABLED | XBR0_SYSCKE__DISABLED;
	// [XBR0 - Port I/O Crossbar 0]$

	// $[XBR1 - Port I/O Crossbar 1]
	// [XBR1 - Port I/O Crossbar 1]$


}

//================================================================================
// TIMER01_0_enter_Mode2_from_DefaultMode
//================================================================================
extern void TIMER00_0_enter_Mode2_from_DefaultMode(void) {
	// $[Timer Initialization]
	//Save Timer Configuration
	U8 TCON_save = TCON;
	//Stop Timers
	TCON &= TCON_TR0__BMASK & TCON_TR1__BMASK;

	// [Timer Initialization]$

	// $[TH0 - Timer 0 High Byte]
	// [TH0 - Timer 0 High Byte]$

	// $[TL0 - Timer 0 Low Byte]
	// [TL0 - Timer 0 Low Byte]$

	// $[TH1 - Timer 1 High Byte]
	// [TH1 - Timer 1 High Byte]$

	// $[TL1 - Timer 1 Low Byte]
	/*
	// TL1 (Timer 1 Low Byte) = 52
	*/
	TH0 =254;

	// [TL1 - Timer 1 Low Byte]$

	// $[Timer Restoration]
	//Restore Timer Configuration
	TCON = TCON_save;

	// [Timer Restoration]$


}

//================================================================================
// TIMER16_3_enter_Mode2_from_DefaultMode
//================================================================================
extern void TIMER16_3_enter_Mode2_from_DefaultMode(void) {
	// $[Timer Initialization]
	// Save Timer Configuration
	U8 TMR3CN_TR3_save = TMR3CN & TMR3CN_TR3__BMASK;
	// Stop Timer
	TMR3CN &= ~(TMR3CN_TR3__BMASK);
	// [Timer Initialization]$

	// $[TMR3CN - Timer 3 Control]
	// [TMR3CN - Timer 3 Control]$

	// $[TMR3H - Timer 3 High Byte]
	/*
	// TMR3H (Timer 3 High Byte) = 56
	*/
	TMR3H = (56 << TMR3H_TMR3H__SHIFT);
	// [TMR3H - Timer 3 High Byte]$

	// $[TMR3L - Timer 3 Low Byte]
	/*
	// TMR3L (Timer 3 Low Byte) = 158
	*/
	TMR3L = (158 << TMR3L_TMR3L__SHIFT);
	// [TMR3L - Timer 3 Low Byte]$

	// $[TMR3RLH - Timer 3 Reload High Byte]
	/*
	// TMR3RLH (Timer 3 Reload High Byte) = 56
	*/
	TMR3RLH = (56 << TMR3RLH_TMR3RLH__SHIFT);
	// [TMR3RLH - Timer 3 Reload High Byte]$

	// $[TMR3RLL - Timer 3 Reload Low Byte]
	/*
	// TMR3RLL (Timer 3 Reload Low Byte) = 158
	*/
	TMR3RLL = (158 << TMR3RLL_TMR3RLL__SHIFT);
	// [TMR3RLL - Timer 3 Reload Low Byte]$

	// $[TMR3CN]
	/*
	// TR3 (Timer 3 Run Control) = RUN (Start Timer 3 running.)
	*/
	TMR3CN |= TMR3CN_TR3__RUN;
	// [TMR3CN]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	TMR3CN |= TMR3CN_TR3_save;
	// [Timer Restoration]$


}

//================================================================================
// TIMER_SETUP_0_enter_Mode2_from_DefaultMode
//================================================================================
extern void TIMER_SETUP_0_enter_Mode2_from_DefaultMode(void) {
	// $[CKCON - Clock Control]
	// [CKCON - Clock Control]$

	// $[TMOD - Timer 0/1 Mode]
	/*
	// T0M (Timer 0 Mode Select) = MODE0 (Mode 0, 13-bit Counter/Timer)
	// CT0 (Counter/Timer 0 Select) = TIMER (Timer Mode. Timer 0 increments
	//     on the clock defined by T0M in the CKCON register.)
	// GATE0 (Timer 0 Gate Control) = DISABLED (Timer 0 enabled when TR0 = 1
	//     irrespective of /INT0 logic level.)
	// T1M (Timer 1 Mode Select) = MODE2 (Mode 2, 8-bit Counter/Timer with
	//     Auto-Reload)
	// CT1 (Counter/Timer 1 Select) = TIMER (Timer Mode. Timer 1 increments
	//     on the clock defined by T1M in the CKCON register.)
	// GATE1 (Timer 1 Gate Control) = DISABLED (Timer 1 enabled when TR1 = 1
	//     irrespective of /INT1 logic level.)
	*/
	CKCON = CKCON_SCA__SYSCLK_DIV_4  | CKCON_T1M__SYSCLK|CKCON_T0M__SYSCLK;

	TMOD = TMOD_T0M__MODE2 | TMOD_CT0__TIMER | TMOD_GATE0__DISABLED
	| TMOD_T1M__MODE2 | TMOD_CT1__TIMER | TMOD_GATE1__DISABLED;

	// [TMOD - Timer 0/1 Mode]$

	// $[TCON - Timer 0/1 Control]
	/*
	// TR1 (Timer 1 Run Control) = RUN (Start Timer 1 running.)
	*/
	TCON |= TCON_TR0__RUN;
	TCON |= TCON_TR1__RUN;
	// [TCON - Timer 0/1 Control]$


}

//================================================================================
// SMBUS_0_enter_Mode2_from_DefaultMode
//================================================================================
extern void SMBUS_0_enter_Mode2_from_DefaultMode(void) {
	// $[SMB0CF - SMBus 0 Configuration]
	/*
	// SMBCS (SMBus Clock Source Selection) = TIMER1 (Timer 1 Overflow.)
	// ENSMB (SMBus Enable) = ENABLED (Enable the SMBus module.)
	// SMBFTE (SMBus Free Timeout Detection Enable) = FREE_TO_ENABLED (Enable
	//     bus free timeouts. The bus the bus will be considered free if SCL and
	//     SDA remain high for more than 10 SMBus clock source periods.)
	// SMBTOE (SMBus SCL Timeout Detection Enable) = SCL_TO_ENABLED (Enable
	//     SCL low timeouts.)
	// EXTHOLD (SMBus Setup and Hold Time Extension Enable) = ENABLED (Enable
	//     SDA extended setup and hold times.)
	// INH (SMBus Slave Inhibit) = SLAVE_DISABLED (Slave states are
	//     inhibited.)
	*/
	SMB0CF = SMB0CF_SMBCS__TIMER0 | SMB0CF_ENSMB__ENABLED | SMB0CF_SMBFTE__FREE_TO_ENABLED
	| SMB0CF_SMBTOE__SCL_TO_ENABLED | SMB0CF_EXTHOLD__ENABLED | SMB0CF_INH__SLAVE_DISABLED;
	// [SMB0CF - SMBus 0 Configuration]$

	// $[SMB0ADR - SMBus 0 Slave Address]
	// [SMB0ADR - SMBus 0 Slave Address]$

	// $[SMB0ADM - SMBus 0 Slave Address Mask]
	// [SMB0ADM - SMBus 0 Slave Address Mask]$


}

//================================================================================
// INTERRUPT_0_enter_Mode2_from_DefaultMode
//================================================================================
extern void INTERRUPT_0_enter_Mode2_from_DefaultMode(void) {
	// $[EIE1 - Extended Interrupt Enable 1]
	/*
	// EADC0 (ADC0 Conversion Complete Interrupt Enable) = DISABLED (Disable
	//     ADC0 Conversion Complete interrupt.)
	// ECP0 (Comparator0 (CP0) Interrupt Enable) = DISABLED (Disable CP0
	//     interrupts.)
	// EPCA0 (Programmable Counter Array (PCA0) Interrupt Enable) = DISABLED
	//     (Disable all PCA0 interrupts.)
	// ERTC0A (RTC Alarm Interrupt Enable) = DISABLED (Disable RTC Alarm
	//     interrupts.)
	// ESMB0 (SMBus (SMB0) Interrupt Enable) = ENABLED (Enable interrupt
	//     requests generated by SMB0.)
	// ET3 (Timer 3 Interrupt Enable) = ENABLED (Enable interrupt requests
	//     generated by the TF3L or TF3H flags.)
	// EWADC0 (Window Comparison ADC0 Interrupt Enable) = DISABLED (Disable
	//     ADC0 Window Comparison interrupt.)
	*/
	EIE1 = EIE1_EADC0__DISABLED | EIE1_ECP0__DISABLED | EIE1_EPCA0__DISABLED
	| EIE1_ERTC0A__DISABLED | EIE1_ESMB0__ENABLED | EIE1_ET3__DISABLED
	| EIE1_EWADC0__DISABLED;
	// [EIE1 - Extended Interrupt Enable 1]$

	// $[EIP1 - Extended Interrupt Priority 1]
	// [EIP1 - Extended Interrupt Priority 1]$

	// $[IE - Interrupt Enable]
	/*
	// EA (All Interrupts Enable) = ENABLED (Enable each interrupt according
	//     to its individual mask setting.)
	// EX0 (External Interrupt 0 Enable) = DISABLED (Disable external
	//     interrupt 0.)
	// EX1 (External Interrupt 1 Enable) = DISABLED (Disable external
	//     interrupt 1.)
	// ESPI0 (SPI0 Interrupt Enable) = DISABLED (Disable all SPI0
	//     interrupts.)
	// ET0 (Timer 0 Interrupt Enable) = DISABLED (Disable all Timer 0
	//     interrupt.)
	// ET1 (Timer 1 Interrupt Enable) = DISABLED (Disable all Timer 1
	//     interrupt.)
	// ET2 (Timer 2 Interrupt Enable) = DISABLED (Disable Timer 2 interrupt.)
	// ES0 (UART0 Interrupt Enable) = DISABLED (Disable UART0 interrupt.)
	*/
	IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED | IE_ESPI0__DISABLED
	| IE_ET0__DISABLED | IE_ET1__DISABLED | IE_ET2__ENABLED | IE_ES0__DISABLED;
	// [IE - Interrupt Enable]$

	// $[IP - Interrupt Priority]
	// [IP - Interrupt Priority]$

	// $[EIE2 - Extended Interrupt Enable 2]
	// [EIE2 - Extended Interrupt Enable 2]$

	// $[EIP2 - Extended Interrupt Priority 2]
	// [EIP2 - Extended Interrupt Priority 2]$


}
extern void UART_0_enter_DefaultMode_from_RESET(void) {
	// $[SCON0 - UART0 Serial Port Control]
	/*
	// REN (Receive Enable) = RECEIVE_ENABLED (UART0 reception enabled.)
	*/
	SCON0 |= SCON0_REN__RECEIVE_ENABLED;
	// [SCON0 - UART0 Serial Port Control]$


}
extern void TIMER01_0_enter_DefaultMode_from_RESET(void) {
	// $[Timer Initialization]
	//Save Timer Configuration
	U8 TCON_save = TCON;
	//Stop Timers
	TCON &= TCON_TR0__BMASK & TCON_TR1__BMASK;

	// [Timer Initialization]$

	// $[TH0 - Timer 0 High Byte]
	// [TH0 - Timer 0 High Byte]$

	// $[TL0 - Timer 0 Low Byte]
	// [TL0 - Timer 0 Low Byte]$

	// $[TH1 - Timer 1 High Byte]
	/*
	// TH1 (Timer 1 High Byte) = 0xCB
	*/
	TH1 = (0x2B << TH1_TH1__SHIFT);
	// [TH1 - Timer 1 High Byte]$

	// $[TL1 - Timer 1 Low Byte]
	/*
	// TL1 (Timer 1 Low Byte) = 0xCB
	*/
	//TL1 = (0x2B << TL1_TL1__SHIFT);
	// [TL1 - Timer 1 Low Byte]$

	// $[Timer Restoration]
	//Restore Timer Configuration
	TCON = TCON_save;

	// [Timer Restoration]$


}
extern void TIMER16_2_enter_DefaultMode_from_RESET(void) {
	U8 TMR2CN_TR2_save = TMR2CN & TMR2CN_TR2__BMASK;
	// Stop Timer
	TMR2CN &= ~(TMR2CN_TR2__BMASK);
	// [Timer Initialization]$

	// $[TMR2CN - Timer 2 Control]
	// [TMR2CN - Timer 2 Control]$

	// $[TMR2H - Timer 2 High Byte]
	/*
	// TMR2H (Timer 2 High Byte) = 215
	*/
	TMR2H = (0x06 << TMR2H_TMR2H__SHIFT);
	// [TMR2H - Timer 2 High Byte]$

	// $[TMR2L - Timer 2 Low Byte]
	/*
	// TMR2L (Timer 2 Low Byte) = 96
	*/
	TMR2L = (0xC5 << TMR2L_TMR2L__SHIFT);
	// [TMR2L - Timer 2 Low Byte]$

	// $[TMR2RLH - Timer 2 Reload High Byte]
	/*
	// TMR2RLH (Timer 2 Reload High Byte) = 215
	*/
	TMR2RLH = (0x06 << TMR2RLH_TMR2RLH__SHIFT);
	// [TMR2RLH - Timer 2 Reload High Byte]$

	// $[TMR2RLL - Timer 2 Reload Low Byte]
	/*
	// TMR2RLL (Timer 2 Reload Low Byte) = 79
	*/
	TMR2RLL = (0xC5 << TMR2RLL_TMR2RLL__SHIFT);
	// [TMR2RLL - Timer 2 Reload Low Byte]$

	// $[TMR2CN]
	/*
	// TR2 (Timer 2 Run Control) = RUN (Start Timer 2 running.)
	*/
	TMR2CN |= TMR2CN_TR2__RUN;
	// [TMR2CN]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	TMR2CN |= (TMR2CN_TR2_save);
	//TMR2CN &= (0xFD);
	// [Timer Restoration]$


}


//==============================================================================
// enter_Mode2_from_DefaultMode
//==============================================================================
extern void enter_Mode2_from_DefaultMode(void) {
	// $[Config Calls]
	PORTS_1_enter_Mode2_from_DefaultMode();
	PBCFG_0_enter_Mode2_from_DefaultMode();
	SMBUS_0_enter_Mode2_from_DefaultMode();
	TIMER00_0_enter_Mode2_from_DefaultMode();
	//TIMER16_3_enter_Mode2_from_DefaultMode();
	TIMER_SETUP_0_enter_Mode2_from_DefaultMode();

	INTERRUPT_0_enter_Mode2_from_DefaultMode();
	// [Config Calls]$
}



