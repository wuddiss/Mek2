 #include <avr/io.h>

 int main()
 {
 char cData ;
 // b a u d r a te 4800
 UBRR0H = 0;
 UBRR0L = 207;
 // e n a bl e r e c e i v e r and t r a n sm i t t e r
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 // s e t frame forma t
 UCSR0C=(1<<USBS0)|(3<< UCSZ00);

 while (1)
 {
 // w a i t f o r da ta t o be r e c e i v e d
 while (!(UCSR0A&(1<<RXC0)));
 // g e t and r e t u r n da ta
 cData= UDR0;
 // w a i t f o r empty b u f f e r
 while (!(UCSR0A&(1<<UDRE0)));
 // pu t da ta i n t o b u f f e r
 UDR0=cData+0x01;
 }
 return 0;
 }
