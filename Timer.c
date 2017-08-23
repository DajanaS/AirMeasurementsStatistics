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

unsigned cnt;
char txt[16];

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
     if(TMR0IF_bit) {
          cnt++;
          TMR0IF_bit=0;
          TMR0=6;
     }
}

void main() {
     OPTION_REG=0x86;
     ANSEL=0;
     ANSELH=0;
     TMR0=6;
     INTCON=0xA0;
     cnt=0;
     UART1_Init(9600);
     Delay_ms(50);
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     while(1) {
          IntToStr(cnt,txt);
          Lcd_Out(1,1,Ltrim(txt));
          if(cnt>3750) {
               Lcd_Cmd(_LCD_CLEAR);
               Lcd_Cmd(_LCD_CURSOR_OFF);
               Lcd_Out(1, 1, "Minute passed");
               cnt=0;
          }
     }
}