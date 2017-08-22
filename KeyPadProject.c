unsigned short kp, cnt, oldstate = 0;
char txt[6];

// Keypad module connections
char  keypadPort at PORTC;
// End Keypad module connections

// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections

void measureTemperature() {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1, 1, "Temperature");
     Lcd_Out(2, 1, "Measure");
}

void measurePressure() {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1, 1, "Pressure");
     Lcd_Out(2, 1, "Measure");
}

void showTemperatureStatistics() {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1, 1, "Temperature");
     Lcd_Out(2, 1, "Statistics");
}

void showPressureStatistics() {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1, 1, "Pressure");
     Lcd_Out(2, 1, "Statistics");
}

void showHomeScreen() {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1, 1, "Home");
}

void main() {
  cnt = 0;                                 // Reset counter
  Keypad_Init();                           // Initialize Keypad
  ANSEL  = 0;                              // Configure AN pins as digital I/O
  ANSELH = 0;
  Lcd_Init();                              // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);                     // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);                // Cursor off

  do {
    kp = 0;                                // Reset key code variable
    // Wait for key to be pressed and released
    do
      // kp = Keypad_Key_Press();          // Store key code in kp variable
      kp = Keypad_Key_Click();             // Store key code in kp variable
    while (!kp);
   // Prepare value for output, transform key to it's ASCII value
    switch (kp) {
      case  1: 
            measureTemperature();
            break; // 1
      case  2:
            measurePressure();
            break; // 2
      case  3: 
            showHomeScreen();
            break; // 3
      case  4:
            showTemperatureStatistics();
            break; // A
      case  5: 
            showPressureStatistics();
            break; // 4
      case  6: 
            break; // 5
      case  7: 
            break; // 6
      case  8:
            break; // B
      case  9: 
            break; // 7
      case 10: 
           break; // 8
      case 11: 
           break; // 9
      case 12: 
           break; // C
      case 13: 
           break; // *
      case 14: 
           break; // 0
      case 15: 
           break; // #
      case 16: 
           break; // D
    }
  } 
  while (1);
}