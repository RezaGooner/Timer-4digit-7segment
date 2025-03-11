#include <mega32.h>
// reza asadi 4011531007
#include <delay.h>

void main(void){
    int i , j ;
    int seconds = 0;
    int minutes = 0 ;
    int s[4] = { 0 ,0 , 0 ,0};
    DDRD=0x0f;
    DDRC=0x0f;
    while(1){
        PORTD=1;
        s[0] = minutes / 10;
        s[1] = minutes % 10;
        s[2] = seconds / 10;
        s[3] = seconds % 10;
        PORTB = PORTD;        
        for (j=0;j<250;j++){
            PORTD = PORTB;
            for(i=0;i<4;i++){
                PORTC=s[i];
                delay_ms(1);
                PORTD *= 2;
           }
      }               

        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
            }
        } 
    }  
}



