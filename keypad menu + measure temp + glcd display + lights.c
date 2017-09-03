int counter;
unsigned short kp;
int tempMin, tempMax;
unsigned temp;

// Keypad module connections
char  keypadPort at PORTA;
// End Keypad module connections

// Glcd module connections
char GLCD_DataPort at PORTD;
sbit GLCD_CS1 at RB0_bit;
sbit GLCD_CS2 at RB1_bit;
sbit GLCD_RS  at RB2_bit;
sbit GLCD_RW  at RB3_bit;
sbit GLCD_EN  at RB4_bit;
sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
sbit GLCD_RST at RB5_bit;
// End Glcd module connections

const unsigned short TEMP_RESOLUTION = 9;

char *text = "000.00";

void Display_Temperature(unsigned int temp2write) {
  const unsigned short RES_SHIFT = TEMP_RESOLUTION - 8;
  char temp_whole;
  unsigned int temp_fraction;

  // check if temperature is negative
  if (temp2write & 0x8000) {
    text[0] = '-';
    temp2write = ~temp2write + 1;
  }

  // extract temp_whole
  temp_whole = temp2write >> RES_SHIFT;

  // convert temp_whole to characters
  if (temp_whole/100)
     text[0] = temp_whole/100  + 48;
  else
     text[0] = '0';

  text[1] = (temp_whole/10)%10 + 48;             // Extract tens digit
  text[2] =  temp_whole%10     + 48;             // Extract ones digit

  // extract temp_fraction and convert it to unsigned int
  temp_fraction  = temp2write << (4-RES_SHIFT);
  temp_fraction &= 0x000F;
  temp_fraction *= 625;

  // convert temp_fraction to characters
  text[4] =  temp_fraction/1000    + 48;
  text[5] = (temp_fraction/100)%10 + 48;

  // print temperature on LCD
  Glcd_Write_Text(text,4,5,2);
}

void showHomeScreen() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("======= MENU =======", 5, 0, 2);
     Glcd_Write_Text("0 Home", 0, 2, 2);
     Glcd_Write_Text("1 Measure temperature", 0, 3, 2); // show lights
     Glcd_Write_Text("2 T-statistics", 0, 4, 2); // show graphic
     Glcd_Write_Text("3 Check warning", 0, 5, 2); // ako e visoka alarms
     Glcd_Write_Text("====================", 5, 7, 2);
}

void measureTemperature() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("Measured temperature:", 0, 1, 2);
     
     counter = 0;
     do {    //--- perform temperature reading
        Ow_Reset(&PORTA, 5);                         // Onewire reset signal
        Ow_Write(&PORTA, 5, 0xCC);                   // Issue command SKIP_ROM
        Ow_Write(&PORTA, 5, 0x44);                   // Issue command CONVERT_T
        Delay_us(120);

        Ow_Reset(&PORTA, 5);
        Ow_Write(&PORTA, 5, 0xCC);                   // Issue command SKIP_ROM
        Ow_Write(&PORTA, 5, 0xBE);                   // Issue command READ_SCRATCHPAD

        temp =  Ow_Read(&PORTA, 5);
        temp = (Ow_Read(&PORTA, 5) << 8) + temp;

        //--- Format and display result on Lcd
        Display_Temperature(temp);

        Delay_ms(500);
        counter++;
     } while (counter<5);
  
     Glcd_Write_Text("Normal: 3 or 4", 0, 6, 2);
     TRISC = 0x00;
     PORTC = 0x00;
     if(temp >= -55)
     PORTC.B7 = 1;
     if(temp >= -32.5)
     PORTC.B6 = 1;
     if(temp >= -10)
     PORTC.B5 = 1;
     if(temp >= 12.5)
     PORTC.B4 = 1;
     if(temp >= 35)
     PORTC.B3 = 1;
     if(temp >= 57.5)
     PORTC.B2 = 1;
     if(temp >= 80)
     PORTC.B1 = 1;
     if(temp >= 102.5)
     PORTC.B0 = 1;
}

void showTemperatureStatistics() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("Show T-Statistics", 0, 1, 2);
}

void checkWarning() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("Check Warning", 0, 1, 2);
}

void main() {
     ANSEL = 0; // Configure AN pins as digital
     ANSELH = 0;
     C1ON_bit = 0; // Disable comparators
     C2ON_bit = 0;
     Glcd_Init(); // Initialize GLCD
     Glcd_Fill(0x00);
     tempMin = -10;
     tempMax = 30;
     showHomeScreen(); // FIRST: show menu
     do {
        kp = 0; // Reset key code variable
        do // Wait for key to be pressed and released
           kp = Keypad_Key_Click(); // Store key code in kp variable
        while (!kp);
        switch (kp) {
               case 1: showHomeScreen();
                    break; // 1
               case 2: measureTemperature(); // CLICK RA1
                    break; // 2
               case 3:showTemperatureStatistics();
                    break; // 3
               case 4: checkWarning();
                    break; // A
               case 5: showHomeScreen();
                    break; // 4
               case 6: measureTemperature();
                    break; // 5
               case 7: showHomeScreen();
                    break; // 6
               case 8: checkWarning();
                    break; // B
               case 9: showHomeScreen();
                    break; // 7
               case 10: showHomeScreen();
                    break; // 8
               case 11: showHomeScreen();
                    break; // 9
               case 12: showHomeScreen();
                    break; // C
               case 13: showHomeScreen();
                    break; // *
               case 14: measureTemperature();
                    break; // 0
               case 15: showTemperatureStatistics();
                    break; // #
               case 16: checkWarning();
                    break; // D
        }
     }
     while (1);
}
