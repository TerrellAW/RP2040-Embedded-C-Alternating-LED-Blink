/*
RP2040 EMBEDDED C ALTERNATING LED BLINKING PROGRAM

Alternates between blinking the onboard LED at GPIO 25 and the offboard LED at GPIO 0
*/

// Define macros
#define RST_CLR		(*(volatile uint32_t *)0x4000f000)	// atomic register to clear reset controller
#define RST_BASE	(*(volatile uint32_t *)0x4000c000)	// reset controller base
#define CTRL_25		(*(volatile uint32_t *)0x400140cc)	// GPIO25 controller
#define CTRL_0 		(*(volatile uint32_t *)0x40014004)	// GPIO0 controller
#define SIO_BASE	(*(volatile uint32_t *)0xd0000000)	// SIO base
#define BIG_NUM		(*(volatile uint32_t *)0x00780000)	// big number for delay

// Check if reset is cleared - if bit 5 of RST_BASE == 1, reset is cleared
void rst() {

	// Release IO_BANK0 from reset controller
	RST_CLR |= 1 << 5; // Clear all bits and set bit 5 to 1

	while (1) {
		
		// Check if bit 5 is not 1
		if (!(RST_BASE & (1 << 5))) {
			// Do nothing (Wait)
		}
	}
}

// Set SIO control over GPIO pins 0 and 25
void ctrl() {

	

}

int main() {

	rst();

}
