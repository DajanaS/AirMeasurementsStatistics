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

int temperatureMax;
int temperatureMin;
int temperature;
int i;

void checkLimits() {
     if(temperature>temperatureMax) {
          i=0;
          while(i<30) {
               PORTA=0b00010000;
               Delay_ms(100);
               PORTA=0b00000000;
               Delay_ms(100);
               i=i+1;
          }
     }
     if(temperature<temperatureMin) {
          i=0;
          while(i<30) {
               PORTA=0b00001000;
               Delay_ms(100);
               PORTA=0b00000000;
               Delay_ms(100);
               i=i+1;
          }
     }
}

void main() {
     temperatureMax=45;
     temperatureMin=-20;
     ANSEL  = 0;
     ANSELH = 0;
     TRISA=0x00;
     PORTA=0x00;
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     while(1) {
          temperature=55;
          Lcd_Cmd(_LCD_CLEAR);
          Lcd_Cmd(_LCD_CURSOR_OFF);
          Lcd_Out(1, 1, "HIGH");
          checkLimits();
          Delay_ms(100);
          temperature=25;
          Lcd_Cmd(_LCD_CLEAR);
          Lcd_Cmd(_LCD_CURSOR_OFF);
          Lcd_Out(1, 1, "NORMAL");
          checkLimits();
          Delay_ms(100);
          temperature=-45;
          Lcd_Cmd(_LCD_CLEAR);
          Lcd_Cmd(_LCD_CURSOR_OFF);
          Lcd_Out(1, 1, "LOW");
          checkLimits();
          Delay_ms(100);
     }
}
