
#define LCD_RD   A0
#define LCD_WR   A1     
#define LCD_RS   A2        
#define LCD_CS   A3       
#define LCD_REST A4

void Lcd_Writ_Bus(unsigned char VH)
{
  unsigned int i,temp,data; 
  data=VH;
  for(i=8;i<=9;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }  
  for(i=2;i<=7;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }  

  digitalWrite(LCD_WR,LOW);
  digitalWrite(LCD_WR,HIGH);
}


void Lcd_Write_Com(unsigned char VH)  
{   
  digitalWrite(LCD_RS,LOW);
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  digitalWrite(LCD_RS,HIGH);
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  Lcd_Write_Com_Data(0x02,x1>>8);
  Lcd_Write_Com_Data(0x03,x1);
  Lcd_Write_Com_Data(0x04,x2>>8);
  Lcd_Write_Com_Data(0x05,x2);
  Lcd_Write_Com_Data(0x06,y1>>8);
  Lcd_Write_Com_Data(0x07,y1);
  Lcd_Write_Com_Data(0x08,y2>>8);
  Lcd_Write_Com_Data(0x09,y2);
  Lcd_Write_Com(0x22);               
}

void Lcd_Init(void)
{
  digitalWrite(LCD_REST,HIGH);
  delay(5); 
  digitalWrite(LCD_REST,LOW);
  delay(15);
  digitalWrite(LCD_REST,HIGH);
  delay(15);

  digitalWrite(LCD_CS,HIGH);
  digitalWrite(LCD_WR,HIGH);
  digitalWrite(LCD_CS,LOW);  //CS

    Lcd_Write_Com_Data(0x46,0x91);
  Lcd_Write_Com_Data(0x47,0x11);
  Lcd_Write_Com_Data(0x48,0x00);
  Lcd_Write_Com_Data(0x49,0x66);
  Lcd_Write_Com_Data(0x4a,0x37);
  Lcd_Write_Com_Data(0x4b,0x04);
  Lcd_Write_Com_Data(0x4c,0x11);
  Lcd_Write_Com_Data(0x4d,0x77);
  Lcd_Write_Com_Data(0x4e,0x00);
  Lcd_Write_Com_Data(0x4f,0x1f);
  Lcd_Write_Com_Data(0x50,0x0f);
  Lcd_Write_Com_Data(0x51,0x00);

  //240x320 window setting
  Lcd_Write_Com_Data(0x02,0x00); // Column address start2
  Lcd_Write_Com_Data(0x03,0x00); // Column address start1
  Lcd_Write_Com_Data(0x04,0x00); // Column address end2
  Lcd_Write_Com_Data(0x05,0xef); // Column address end1
  Lcd_Write_Com_Data(0x06,0x00); // Row address start2
  Lcd_Write_Com_Data(0x07,0x00); // Row address start1
  Lcd_Write_Com_Data(0x08,0x01); // Row address end2
  Lcd_Write_Com_Data(0x09,0x3f); // Row address end1

  // Display Setting
  Lcd_Write_Com_Data(0x01,0x06); // IDMON=0, INVON=1, NORON=1, PTLON=0
  Lcd_Write_Com_Data(0x16,0xC8); // MY=0, MX=0, MV=0, ML=1, BGR=0, TEON=0   0048
  Lcd_Write_Com_Data(0x23,0x95); // N_DC=1001 0101
  Lcd_Write_Com_Data(0x24,0x95); // PI_DC=1001 0101
  Lcd_Write_Com_Data(0x25,0xFF); // I_DC=1111 1111

  Lcd_Write_Com_Data(0x27,0x02); // N_BP=0000 0010
  Lcd_Write_Com_Data(0x28,0x02); // N_FP=0000 0010
  Lcd_Write_Com_Data(0x29,0x02); // PI_BP=0000 0010
  Lcd_Write_Com_Data(0x2a,0x02); // PI_FP=0000 0010
  Lcd_Write_Com_Data(0x2C,0x02); // I_BP=0000 0010
  Lcd_Write_Com_Data(0x2d,0x02); // I_FP=0000 0010

  Lcd_Write_Com_Data(0x3a,0x01); // N_RTN=0000, N_NW=001    0001
  Lcd_Write_Com_Data(0x3b,0x00); // P_RTN=0000, P_NW=001
  Lcd_Write_Com_Data(0x3c,0xf0); // I_RTN=1111, I_NW=000
  Lcd_Write_Com_Data(0x3d,0x00); // DIV=00
  delay(1);
  Lcd_Write_Com_Data(0x35,0x38); // EQS=38h
  Lcd_Write_Com_Data(0x36,0x78); // EQP=78h
  Lcd_Write_Com_Data(0x3E,0x38); // SON=38h
  Lcd_Write_Com_Data(0x40,0x0F); // GDON=0Fh
  Lcd_Write_Com_Data(0x41,0xF0); // GDOFF

  // Power Supply Setting
  Lcd_Write_Com_Data(0x19,0x49); // CADJ=0100, CUADJ=100, OSD_EN=1 ,60Hz
  Lcd_Write_Com_Data(0x93,0x0F); // RADJ=1111, 100%
  delay(1);
  Lcd_Write_Com_Data(0x20,0x40); // BT=0100
  Lcd_Write_Com_Data(0x1D,0x07); // VC1=111   0007
  Lcd_Write_Com_Data(0x1E,0x00); // VC3=000
  Lcd_Write_Com_Data(0x1F,0x04); // VRH=0011

  //VCOM SETTING
  Lcd_Write_Com_Data(0x44,0x4D); // VCM=101 0000  4D
  Lcd_Write_Com_Data(0x45,0x0E); // VDV=1 0001   0011
  delay(1);
  Lcd_Write_Com_Data(0x1C,0x04); // AP=100
  delay(2);

  Lcd_Write_Com_Data(0x1B,0x18); // GASENB=0, PON=0, DK=1, XDK=0, VLCD_TRI=0, STB=0
  delay(1);
  Lcd_Write_Com_Data(0x1B,0x10); // GASENB=0, PON=1, DK=0, XDK=0, VLCD_TRI=0, STB=0
  delay(1);
  Lcd_Write_Com_Data(0x43,0x80); //set VCOMG=1
  delay(2);

  // Display ON Setting
  Lcd_Write_Com_Data(0x90,0x7F); // SAP=0111 1111
  Lcd_Write_Com_Data(0x26,0x04); //GON=0, DTE=0, D=01
  delay(1);
  Lcd_Write_Com_Data(0x26,0x24); //GON=1, DTE=0, D=01
  Lcd_Write_Com_Data(0x26,0x2C); //GON=1, DTE=0, D=11
  delay(1);
  Lcd_Write_Com_Data(0x26,0x3C); //GON=1, DTE=1, D=11

  // INTERNAL REGISTER SETTING
  Lcd_Write_Com_Data(0x57,0x02); // TEST_Mode=1: into TEST mode
  Lcd_Write_Com_Data(0x95,0x01); // SET DISPLAY CLOCK AND PUMPING CLOCK TO SYNCHRONIZE
  Lcd_Write_Com_Data(0x57,0x00); // TEST_Mode=0: exit TEST mode
  Lcd_Write_Com_Data(0x21,0x00);
  Lcd_Write_Com(0x22);   
    digitalWrite(LCD_CS,HIGH);
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{ 
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{ 
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  { 
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
int RGB(int r,int g,int b)
{return r << 16 | g << 8 | b;
}
void LCD_Clear(unsigned int j)                   
{ 
  unsigned int i,m;

  Lcd_Write_Com(0x022); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
// Address_set(0,0,320,240);

  for(i=0;i<320;i++)
    for(m=0;m<240;m++)
    {
      Lcd_Write_Data(j);

    }
  digitalWrite(LCD_CS,HIGH);   
}

void setup()
{
  for(int p=2;p<10;p++)
  {
    pinMode(p,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  Lcd_Init();
LCD_Clear(0xf800);
}

void loop()
{  

/* for(int i=0;i<1000;i++)
  {
    Rect(random(300),random(300),random(300),random(300),random(65535)); // rectangle at x, y, with, hight, color
  }
  */
//  LCD_Clear(0xf800);
}
