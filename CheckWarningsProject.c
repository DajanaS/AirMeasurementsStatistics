// Keypad module connections
char keypadPort at PORTD;
// End Keypad module connections

// Glcd module connections
char GLCD_DataPort at PORTD;
sbit GLCD_CS1 at RB0_bit;
sbit GLCD_CS2 at RB1_bit;
sbit GLCD_RS at RB2_bit;
sbit GLCD_RW at RB3_bit;
sbit GLCD_EN at RB4_bit;
sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction at TRISB2_bit;
sbit GLCD_RW_Direction at TRISB3_bit;
sbit GLCD_EN_Direction at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
sbit GLCD_RST at RB5_bit;
// End Glcd module connections

unsigned short kp;
int tempMax;
int tempMin;
int temperature;
int i;

void showHomeScreen() {
    Glcd_Fill(0x00);
    Glcd_Write_Text("======= MENU =======", 5, 0, 2);
    Glcd_Write_Text("1 Home", 0, 1, 2);
    Glcd_Write_Text("2 Measure temperature", 0, 2, 2); // show lights
    Glcd_Write_Text("3 Measure pressure", 0, 3, 2); // preassure
    Glcd_Write_Text("4 T-statistics", 0, 4, 2); // show graphic
    Glcd_Write_Text("5 P-statistics", 0, 5, 2); //   isto od t, samo copy, so random vrednosti.
    Glcd_Write_Text("6 Check warning", 0, 6, 2); // ako e visoka alarms
    Glcd_Write_Text("====================", 5, 7, 2);
}

void measureTemperature() {

}

void measurePressure() {

}

void showTemperatureStatistics() {

}

void showPressureStatistics() {

}

void checkWarnings() {
    TRISC = 0x00;
    PORTC = 0x00;
    if (temperature > tempMax) {
        Glcd_Fill(0x00);
        Glcd_Write_Text("WARNING!!!", 5, 3, 2);
        Glcd_Write_Text("Temperature too high", 5, 4, 2);
        Glcd_Write_Text("WARNING!!!", 5, 5, 2);
        i = 0;
        while (i < 30) {
            PORTC = 0b00010000;
            Delay_ms(100);
            PORTC = 0b00000000;
            Delay_ms(100);
            i = i + 1;
        }
    }
    if (temperature < tempMin) {
        Glcd_Fill(0x00);
        Glcd_Write_Text("WARNING!!!", 5, 3, 2);
        Glcd_Write_Text("Temperature too low", 5, 4, 2);
        Glcd_Write_Text("WARNING!!!", 5, 5, 2);
        i = 0;
        while (i < 30) {
            PORTC = 0b00001000;
            Delay_ms(150);
            PORTC = 0b00000000;
            Delay_ms(150);
            i = i + 1;
        }
    }
    PORTC = 0x00;
}

void main() {
    tempMax = 30;
    tempMin = -10;
    i = 0;
    ANSEL = 0; // Configure AN pins as digital
    ANSELH = 0;
    C1ON_bit = 0; // Disable comparators
    C2ON_bit = 0;
    Glcd_Init(); // Initialize GLCD
    Glcd_Fill(0x00);
    showHomeScreen(); // FIRST: show menu
    do {
        kp = 0; // Reset key code variable
        // Wait for key to be pressed and released
        do
            kp = Keypad_Key_Click(); // Store key code in kp variable
        while (!kp);
        // Prepare value for output, transform key to it's ASCII value
        switch (kp) {
        case 1:
            showHomeScreen();
            break; // 1
        case 2:
            measureTemperature();
            break; // 2
        case 3:
            measurePressure();
            break; // 3
        case 4:
            showTemperatureStatistics();
            break; // A
        case 5:
            showPressureStatistics();
            break; // 4
        case 6:
            checkWarnings();
            break; // 5
        case 7:
            break; // 6
        case 8:
            break; // B
        case 9:
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
