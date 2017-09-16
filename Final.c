int counter;
unsigned short kp;
int tempMin, tempMax;
unsigned temp;
int tf, i, j, tmp;

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
const int c48 = 48;
const int c10 = 10;
const int c100 = 100;
const int N = 4;
int temps[N] = {0};

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
  if (temp_whole/c100)
     text[0] = temp_whole/c100  + c48;
  else
     text[0] = ' ';

  text[1] = (temp_whole/c10)%c10 + c48;         // Extract tens digit
  tf = (temp_whole/c10)%c10;
  text[2] =  temp_whole%c10 + c48;             // Extract ones digit
  tf = tf*c10 + temp_whole%c10;

  // extract temp_fraction and convert it to unsigned int
  temp_fraction  = temp2write << (4-RES_SHIFT);
  temp_fraction &= 0x000F;
  temp_fraction *= 625;

  // convert temp_fraction to characters
  text[4] =  temp_fraction/(c100*c10) + c48;
  text[5] = (temp_fraction/c100)%c10 + c48;

  // print temperature on LCD
  Glcd_Write_Text(text,38,4,2);
}

void showHomeScreen() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("MENU", 45, 0, 2);
     Glcd_Write_Text("0 Home", 0, 2, 2);
     Glcd_Write_Text("1 Temp", 0, 3, 2); // show lights
     Glcd_Write_Text("2 T-stats", 0, 4, 2); // show graphic
     Glcd_Write_Text("3 Warning", 0, 5, 2); // ako e visoka alarms
     Glcd_Write_Text("===", 45, 7, 2);
}

void measureTemperature() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("Measured temperature:", 0, 1, 2);

     counter = 0;
     do {    //--- perform temperature reading
        Ow_Reset(&PORTE, 2);                         // Onewire reset signal
        Ow_Write(&PORTE, 2, 0xCC);                   // Issue command SKIP_ROM
        Ow_Write(&PORTE, 2, 0x44);                   // Issue command CONVERT_T
        Delay_us(120);

        Ow_Reset(&PORTE, 2);
        Ow_Write(&PORTE, 2, 0xCC);                   // Issue command SKIP_ROM
        Ow_Write(&PORTE, 2, 0xBE);                   // Issue command READ_SCRATCHPAD

        temp =  Ow_Read(&PORTE, 2);
        temp = (Ow_Read(&PORTE, 2) << 8) + temp;
        Delay_ms(500);
        counter++;
     } while (counter<3);
     
     //--- Format and display result on Lcd
     Display_Temperature(temp);
     
     // Shift left old values and add new in the beginning
     for(i = 0; i < N; i++)
           temps[i] = temps[i+1];
     temps[N-1] = tf;
    
     TRISC = 0x00;
     PORTC = 0x00;
     if(tf >= -55)
     PORTC.B7 = 1;
     if(tf >= -32.5)
     PORTC.B6 = 1;
     if(tf >= -10)
     PORTC.B5 = 1;
     if(tf >= 12.5)
     PORTC.B4 = 1;
     if(tf >= 35)
     PORTC.B3 = 1;
     if(tf >= 57.5)
     PORTC.B2 = 1;
     if(tf >= 80)
     PORTC.B1 = 1;
     if(tf >= 102.5)
     PORTC.B0 = 1;
}

void showTemperatureStatistics() {
     Glcd_Fill(0x00);
     j = 0;
     for(i = 0; i < N; i++){
         Glcd_Box(j+1,63-(temps[i]*0.35+19.25),j+27,63,2);
         j+=29;
     }
}

void checkWarning() {
     Glcd_Fill(0x00);
     Glcd_Write_Text("Warning", 38, 1, 2);

     TRISC = 0x00;
    PORTC = 0x00;
    if (tf > tempMax) {
        Glcd_Write_Text("HIGH", 50, 4, 2);
        i = 0;
        while (i < 30) {
            PORTC = 0b11111111;
            Delay_ms(100);
            PORTC = 0b00000000;
            Delay_ms(100);
            i = i + 1;
        }
    }
    else if (tf < tempMin) {
        Glcd_Write_Text("LOW", 50, 4, 2);
        i = 0;
        while (i < 30) {
            PORTC = 0b11111111;
            Delay_ms(150);
            PORTC = 0b00000000;
            Delay_ms(150);
            i = i + 1;
        }
    }
    else {
         Glcd_Write_Text("OK", 50, 4, 2);
    }
    PORTC = 0x00;
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
     tf = 0;
     showHomeScreen(); // FIRST: show menu
     do {
        kp = 0; // Reset key code variable
        do // Wait for key to be pressed and released
           kp = Keypad_Key_Click(); // Store key code in kp variable
        while (!kp);
        switch (kp) {
               case 1: showHomeScreen();
                    break; // 1
               case 2: measureTemperature();
                    break; // 2
               case 3: showTemperatureStatistics();
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
