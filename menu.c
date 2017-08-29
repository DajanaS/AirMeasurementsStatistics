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

void showScreen(){
   Glcd_Write_Text("======= MENU =======", 5, 0, 2);
   Glcd_Write_Text("1 Measure temperature", 0, 1, 2);   // show lights
   Glcd_Write_Text("2 T-statistics", 0, 2, 2);          // show graphic
   Glcd_Write_Text("3 Measure pressure", 0, 3, 2);     // preassure
   Glcd_Write_Text("4 P-statistics", 0, 4, 2);          //   isto od t, samo copy, so random vrednosti.
   Glcd_Write_Text("5 Check warning", 0, 5, 2);         // ako e visoka alarms
   Glcd_Write_Text("6 Home", 0, 6, 2);
   Glcd_Write_Text("====================", 5, 7, 2);
}

void main() {
  ANSEL  = 0;                                    // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;                                  // Disable comparators
  C2ON_bit = 0;

  Glcd_Init();                                   // Initialize GLCD
  Glcd_Fill(0x00);

  showScreen();  // FIRST: show menu
  
  // key init
  // case.. i vnatre funkcii
}
