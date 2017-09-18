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

int temps[42];
int i;
int x;
int y;
int k;

void main() {

  i = 0;
  x = 0;
  y = 1;
  
  //int temps[100] = {-27,-14,-10,-5,-4,-2,0,1,3,8,12,18,29,35,27,26,34,28,15,14,19,16,20,25,57,43,44,42,41,48,-4,-2,0,1,3,8,12,18,29,35,27,26,34,26,34,28,15,14,44,42,41,48,-4,-2,0,-27,-14,-10,-5,-4,-2,0,1,3,8,27,26,34,26,34,28,0,1,3,8,12,10,0,1,3,9,12,18,29,35,27,22,34,28,15,14,42,41,48,0,1,3,8,12,18,29,35,27,26,34,26,34,28,15,14,44,42,41,48,-4,-2,0,-27,-14,-10,-5,-4,-2,0,1,3,8};

  // temps[42] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};

  for(k = 0; k < 42; k++)
    temp[k] = k+1;

  ANSEL  = 0;                                    // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;                                  // Disable comparators
  C2ON_bit = 0;

  Glcd_Init();                                   // Initialize GLCD
  Glcd_Fill(0x00);                               // Clear GLCD
  
  while(i<=42) {
    y = temps[i]*0.35+19.25;
    Glcd_Line(x,y,x,63,2);
    Glcd_Line(x+1,y,x+1,63,2);
    Glcd_Line(x+2,y,x+2,63,2);
    x+=3;
    i++;
  }
  
  Delay_ms(2000); // delays 2S
}
