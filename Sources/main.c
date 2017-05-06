/*Burak Demirci *
 * 141044091    */
  
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

unsigned int Tcount;

/*Nota frekans degerleri */
#define C 9555  
#define D 8513  
#define E 7584  
#define F 7158   
#define G 6377  
#define A 5681  
#define B 5061  


unsigned int music1[]={C,B,A,G,E,B,A,B,C,A,C,B,A,G,E,B,A,B,C,A,A,B,C,B,A,G,G,A,B,A,
G,A,A,B,C,B,A,G,G,A,B,A,G,A,C,C,C,B,A,G,G,G,A,B,B,A,A}; 

unsigned int music2[]={A,A,B,C,D,C,B,B,D,C,B,A,G,F,E,A,A,B,C,D,C,B,B,D,C,B,A,G,A,A,B};
unsigned int music3[]={D,D,A,A,D,D,A,C,B,A,C,C,A,A,C,C,B,C,D,B,C,B,A,A,D,D,A,A,D,D,B};

unsigned int m1=57,m2=31,m3=31,tre=0;

void music(unsigned int type);
void led(int val);
void SevenSeg(unsigned int val);

void main(void) {

   DDRH = 0; /* DIP switch input*/
   DDRT = DDRT | 0b00100000;    // PTT5 as output 
   TSCR1= 0x80;
   TSCR2 = 0x00;
   TCTL1 = 0x04;
   DDRB  = 0xFF;
   DDRP  = 0x07;
      
    while(1)
   {
       TIOS =0;
       switch(PTH)
       {
        
        case 0: 
            tre=1;
            music(1);
            music(2);
            music(3);
            tre=0;
            break;        
        case 1: 
          music(1); tre=0; break;
        case 2:
          music(2); tre=0; break;
        case 3:
          music(3); tre=0; break;
       }   
   }
     
}
     

void music(unsigned int type) {

       int i;    
       int add;
       int count = 0;
       int counter = 366/2;
       SevenSeg(type);
       
       TFLG2 = 0x80 ;
       TIOS = 0x20;
       if(tre==0)
          i=30;
       if(tre==1)
          i=10;
       
       switch(type) {
        case 1: add=music1[0]; count=m1; break;
        case 2: add=music2[0]; count=m2; break;
        case 3: add=music3[0]; count=m3; break;
       }
       
       while(i>0){
        
         led(add);
         while(counter!=0) 
         {
            while(!(TFLG2 & 0x80)){
              
              Tcount = TCNT;
                
              Tcount = Tcount + add;
              TC5 = Tcount;
           
              while(!(TFLG1 & TFLG1_C5F_MASK));
              TFLG1 = TFLG1 | TFLG1_C5F_MASK ;  
            
            }
            TFLG2 = 0x80 ;
            counter--;
         }
         counter = 366/2;
         count--;
         if(count > 0) 
         {
           switch(type){
             case 1: add=music1[m1-count]; break;
             case 2: add=music2[m2-count]; break;
             case 3: add=music3[m2-count]; break;
           } 
          
         }
                 
         i--; 
     }
}

/*Çalan notayý ledlerde gösterir */
void led(int val) {

  switch(val) {
    case C: PORTB = 1; break;
    case D: PORTB = 2; break;
    case E: PORTB = 3; break;
    case F: PORTB = 4; break;
    case G: PORTB = 5; break;
    case A: PORTB = 6; break;
    case B: PORTB = 7; break;
  }
}

/*Çalan müzik numarasýný 1saniye Seven segmentte gösterir*/
void SevenSeg(unsigned int val)
{
  
  int counter = 366;
  TIOS =0;
  TFLG2 = 0x80 ;
  switch(val){
    
    case 1: PORTB = 0x06; break;
    case 2: PORTB = 0xDB; break;
    case 3: PORTB = 0x4F; break;
  }
  
  while(counter!=0) 
  { 
     while(!(TFLG2 & 0x80));
      TFLG2 = 0x80 ;
      counter--;    
  }

}