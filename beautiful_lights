void main() {

   ANSEL = 0;
   ANSELH = 0;
   TRISC=0x00;
   PORTC=0x00;
   TRISA=0x00;
   PORTA=0x00;
   TRISB=0x00;
   PORTB=0x00;
   TRISD=0x00;
   PORTD=0x00;
   while(1){
       PORTA=0b01010101; 
       PORTB=0b10101010;
       PORTC=0b01010101;
       PORTD=0b10101010;
       Delay_ms(1000);
       PORTA=0b10101010;
       PORTB=0b01010101;
       PORTC=0b10101010;
       PORTD=0b01010101;
       Delay_ms(1000);
   }
}
