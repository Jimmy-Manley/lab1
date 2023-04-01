#include <pic14/pic12f675.h>
// Interfacing 74HC95 Serial Shift Register
#define push_button GP5	//push button
#define SER_595 GP0	//serial data in pin 14
#define RCLK_595 GP1	//storage register clock input pin 12 "latch"
#define SCLK_595 GP2	//shift register clock input pin 11 "storage"

/*========= Globals=========*/
char data[10] = {0x30,0x5B,0x4F,0X66,0x6D,0X7D,0X47,0X7F,0X4F,0X3F};
/* ======== Function space ==========*/
/* Delay function */
void delay (unsigned int tiempo);

/* setup function*/
void setup (void)
{
	ADCON0 = 0x00;
	ANSEL = 0x00;
	CMCON = 0x07; //shut off comparator
	VRCON = 0X00;
	TRISIO = 0X20;	// set all GPIOs as outputs, except GP5= push button
	GPIO = 0x20;	// set all pins low except GP5 
}
/* sclock:
 * This function will enable the storage clock to 74HC695
 */
void sclock(void)
{
	SCLK_595 =1;
	delay(10);
	SCLK_595 = 0;
	delay(10);
}
/* rclock:
 * This function will strobe/latch and enable the output trigger of 74HC695	
 */
void rclock(void)
{
	RCLK_595 =1;
	delay(10);
	RCLK_595 = 0;
	//delay(500);
} 
/* data display:
 * Thiss function will send the data to the serial line 74HC595 
 */
void data_display(int data)
{
	for(int i=0; i<8;i++)
	{
		SER_595 = (data >> i) & 0x01; // bit shift and bit mask.
		sclock(); // enable data storage clock
	
	}
	//rclock(); // data latch

} 
 /*======= Main loop ========*/
void main(void)
{

    unsigned int time = 250;
    
    setup();

    delay(time);

    while(1)
    {	
    	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(push_button == 0)
			{
				data_display(data[i]);
				data_display(data[j]);
				rclock();

			}
		}
	}
    }
    return;
}

void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
