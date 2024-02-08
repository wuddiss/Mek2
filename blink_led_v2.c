/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: vidar
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main() {
  initLED();  // Set LED sem útgang 13
  initButton();     // Set takka sem inngang 2

  while (1) {
    // Les stöðu á takka (HIGH or LOW)
    int buttonState = isButtonPressed();

    // Ath stöðu á takka (buttonState is LOW)
    if (buttonState == 0) {
      // LED á
    	LED_off();
    } else {
      // LED aff
    	LED_on();
    }

    _delay_ms(100);  // Denounce töf
  }

  return 0;
}
