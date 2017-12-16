#ifndef LedControl_h
#define LedControl_h

/**
 * Chord Organ / Radio Music LED control
 *
 * 4 LEDs across the top and 1 reset LED.
 *
 */
#define LED0 0
#define LED1 5
#define LED2 4
#define LED3 3
#define RESET_LED 1 // Reset LED indicator

class LedControl {

	public:
		LedControl();
		void init();
		void single(int index);
		void multi(uint8_t bits);
		void bankAndSingle(int bank, int index);
		void flash();
		void showReset(boolean high);
	private:
		boolean flashingBank = false;
		elapsedMillis bankFlashTimer = 0;
		uint16_t bankLedFlashTimes[3] = {400,100,30};

};
#endif
