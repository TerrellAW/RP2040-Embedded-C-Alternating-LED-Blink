/*
RP2040 EMBEDDED C ALTERNATING LED BLINKING PROGRAM

Alternates between blinking the onboard LED at GPIO 25 and the offboard LED at GPIO 0
*/

#include <stdint.h>

// Define macros
#define RST_CLR		((volatile uint32_t *)0x4000f000)	// reset clear value
#define RST_BASE	((volatile uint32_t *)0x4000c000)	// reset base value
#define CTRL_25		((volatile uint32_t *)0x400140cc)	// GPIO25 controller
#define CTRL_0 		((volatile uint32_t *)0x40014004)	// GPIO0 controller
#define SIO_BASE	((volatile uint32_t *)0xd0000000)	// SIO base register
#define BIG_NUM		((volatile uint32_t)0x00780000)	// big number for delay

// Bit masks
#define GPIO25_MASK (1UL << 25)
#define GPIO0_MASK (1UL << 0)

// Check if reset is cleared - if bit 5 of RST_BASE == 1, reset is cleared
void rst() {

	// Release IO_BANK0 from reset controller
	*RST_CLR = 1 << 5; // Clear all bits and set bit 5 to 1

	while ((RST_BASE[2] & (1 << 5)) == 0) {
		// Do nothing (Wait)
	}
}

// Set SIO control over GPIO pins 0 and 25
void ctrl() {

	// Set SIO control over GPIO 0 (EXTERN)
	*CTRL_0 = 5;
	// Enable GPIO 0 (EXTERN)
	SIO_BASE[9] = GPIO0_MASK;

	// Set SIO control over GPIO 25 (LED)
	*CTRL_25 = 5;
	// Enable GPIO 25 (LED)
	SIO_BASE[9] = GPIO25_MASK;

}

// Delay countdown
void delay() {
	uint32_t count = BIG_NUM;
	while (count > 0) {
		count--;
	}
}

// Loop to blink LEDs
void led_loop() {

	while (1) {

		// Turn on GPIO25
		SIO_BASE[5] = GPIO25_MASK;
		delay();

		// Turn off GPIO25
		SIO_BASE[6] = GPIO25_MASK;
		delay();

		// Turn on GPIO0
		SIO_BASE[5] = GPIO0_MASK;
		delay();

		// Turn off GPIO0
		SIO_BASE[6] = GPIO0_MASK;
		delay();

	}
}

int main() {

	rst();

	ctrl();

	led_loop();

}
