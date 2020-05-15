#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte pik[8]{
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
};

byte karo[8]{
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

byte herc[8]{
  B00000,
  B01010,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};

byte tref[8]{
  B00100,
  B01110,
  B00100,
  B11111,
  B00100,
  B01110,
  B00000,
};


char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

int main()
{ 
  char pozicija=0,simbol=0;
  char pocetak=0;
  
  lcd.begin(16, 2);
	
  lcd.createChar(0, pik);
  lcd.createChar(1,karo);
  lcd.createChar(2,herc);
  lcd.createChar(3,tref);
  
	while(1)
    { 
	  char taster = ocitaj_taster();
      if (taster == '*')
      { pocetak=1;
        lcd.setCursor(9,1);
        lcd.print("pocetak");
      	_delay_ms(500);
        
        lcd.setCursor(0,0);
         lcd.write(byte(random(0,3)));
        
         lcd.setCursor(1,0);
         lcd.write(byte(random(0,3)));
        
        lcd.setCursor(2,0);
         lcd.write(byte(random(0,3)));
        
        lcd.setCursor(3,0);
        lcd.write(byte(random(0,3)));
        
       
        
        _delay_ms(2000);
        
        lcd.setCursor(0,0);
         lcd.write("_");
        
        lcd.setCursor(1,0);
         lcd.write("_");
        
         lcd.setCursor(2,0);
         lcd.write("_");
        
        lcd.setCursor(3,0);
         lcd.write("_");
       
       if(pocetak==1){
        
         while(1){
          char taster = ocitaj_taster();
          if (taster == '2'){
            simbol++;
            simbol=simbol%4;
          }
          
          if (taster == '8'){
            simbol--;
            simbol=simbol%4;
          }
        
          
          if (taster == '4'){
            pozicija--;
            pozicija=pozicija%4;
          }
          
          if (taster == '6'){
            pozicija++;
            pozicija=pozicija%4;
          }
        
          lcd.setCursor(pozicija,0);
        lcd.write(byte(simbol));
        }
       }
      }
  
  	return 0;
    }