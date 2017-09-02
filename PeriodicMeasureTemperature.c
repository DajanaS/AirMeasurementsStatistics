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

unsigned cnt;
char txt[16];
const unsigned short TEMP_RESOLUTION = 9;
char * text = "000.0000";
unsigned temp;

//1min -> 60*2000000=120000000
//cnt*w*prescaler=120000000
//cnt*w*128=120000000
//cnt*w=120000000/128=937500
//w=250
//cnt=937500/250=3750
//TMR0 initial value -> 256-w=6

//3h -> 10800*2000000=21600000000
//cnt*w*prescaler=21600000000
//cnt*w*128=21600000000
//cnt*w=21600000000/128=168750000
//w=250
//cnt=168750000/250=675000
//TMR0 initial value -> 256-w=6

//6h -> 21600*2000000=43200000000
//cnt*w*prescaler=43200000000
//cnt*w*128=43200000000
//cnt*w=43200000000/128=337500000
//w=250
//cnt=337500000/250=1350000
//TMR0 initial value -> 256-w=6

void interrupt() {
    if (TMR0IF_bit) {
        cnt++;
        TMR0IF_bit = 0;
        TMR0 = 6;
    }
}

void Display_Temperature(unsigned int temp2write) {
    const unsigned short RES_SHIFT = TEMP_RESOLUTION - 8;
    char temp_whole;
    unsigned int temp_fraction;
    // Check if temperature is negative
    if (temp2write & 0x8000) {
        text[0] = '-';
        temp2write = ~temp2write + 1;
    }
    // Extract temp_whole
    temp_whole = temp2write >> RES_SHIFT;
    // Convert temp_whole to characters
    if (temp_whole / 100)
        text[0] = temp_whole / 100 + 48;
    else
        text[0] = ' ';
    text[1] = (temp_whole / 10) % 10 + 48; // Extract tens digit
    text[2] = temp_whole % 10 + 48; // Extract ones digit
    // Extract temp_fraction and convert it to unsigned int
    temp_fraction = temp2write << (4 - RES_SHIFT);
    temp_fraction &= 0x000F;
    temp_fraction *= 625;
    // Convert temp_fraction to characters
    text[4] = temp_fraction / 1000 + 48; // Extract thousands digit
    text[5] = (temp_fraction / 100) % 10 + 48; // Extract hundreds digit
    text[6] = (temp_fraction / 10) % 10 + 48; // Extract tens digit
    text[7] = temp_fraction % 10 + 48; // Extract ones digit
    // Print temperature on GLCD
    Glcd_Write_Text(text, 1, 5, 2);
}

void main() {
    OPTION_REG = 0x86;
    ANSEL = 0;
    ANSELH = 0;
    TMR0 = 6;
    INTCON = 0xA0;
    cnt = 0;
    Glcd_Init();
    Glcd_Fill(0x00);
    while (1) {
        if (cnt > 3750) {
            Ow_Reset( & PORTE, 2); // Onewire reset signal
            Ow_Write( & PORTE, 2, 0xCC); // Issue command SKIP_ROM
            Ow_Write( & PORTE, 2, 0x44); // Issue command CONVERT_T
            Delay_us(120);
            Ow_Reset( & PORTE, 2);
            Ow_Write( & PORTE, 2, 0xCC); // Issue command SKIP_ROM
            Ow_Write( & PORTE, 2, 0xBE); // Issue command READ_SCRATCHPAD
            temp = Ow_Read( & PORTE, 2);
            temp = (Ow_Read( & PORTE, 2) << 8) + temp;
            //--- Format and display result on GLCD
            Display_Temperature(temp);
            Delay_ms(500);
            cnt = 0;
        }
    }
}