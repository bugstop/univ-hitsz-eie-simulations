#include <msp430.h> 
#define uchar unsigned char
#define uint  unsigned int
#define CS_1 P6OUT |= BIT1
#define CS_0 P6OUT &= ~BIT1
#define CLK_1 P6OUT |= BIT2
#define CLK_0 P6OUT &= ~BIT2
#define DIN_1 P6OUT |= BIT0
#define DIN_0 P6OUT &= ~BIT0

unsigned char disp1[38][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//��
{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//��
};
/**
 * main.c
 */
void Delay_xms(unsigned int x)
{
    unsigned int i,j;
    for(i=0;i<x;i++)
        for(j=0;j<112;j++);
}
//--------------------------------------------
//���ܣ���MAX7219(U3)д���ֽ�
//��ڲ�����DATA
//���ڲ�������
//˵����
void Write_Max7219_byte(unsigned char DATA)
{
    unsigned char i;
        CS_0;
        for(i=8;i>=1;i--)
          {
            CLK_0;                 //CLK �õ͵�ƽ
            if (0x80 & DATA)
             {     //�����λΪ1
                   DIN_1;
             } else
             {               //�����λΪ0
                   DIN_0;
             }
                   DATA=DATA<<1;            //����һλ
                   CLK_1;                 //CLK
           }
}
//-------------------------------------------
//���ܣ���MAX7219д������
//��ڲ�����address��dat
//���ڲ�������
//˵����
void Write_Max7219(unsigned char address, unsigned char dat)
{
     CS_0;
     Write_Max7219_byte(address);           //д���ַ��������ܱ��
     Write_Max7219_byte(dat);               //д�����ݣ����������ʾ����
     CS_1;
}

void Init_MAX7219(void)
{
    P6DIR |= BIT0 + BIT1 + BIT2;
    Write_Max7219(0x09, 0x00);       //���뷽ʽ��BCD��
    Write_Max7219(0x0A, 0x03);       //����
    Write_Max7219(0x0B, 0x07);       //ɨ����ޣ�8���������ʾ
    Write_Max7219(0x0C, 0x01);       //����ģʽ��0����ͨģʽ��1
    Write_Max7219(0x0F, 0x01);       //��ʾ���ԣ�1�����Խ�����������ʾ��0
    _delay_cycles(500000);
    Write_Max7219(0x0F, 0x00);

}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	unsigned char i,j;
	unsigned char test[8]={0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C};
	Delay_xms(50);
	Init_MAX7219();
	/*
	 while(1){
	     for(i=1;i<9;i++)
	 { Write_Max7219(i,0b01010101);}
	     Delay_xms(1000);
	 }
	 */
	while(1)
	 {
	  for(j=0;j<38;j++)
	  {
	  for(i=0;i<8;i++)
	  {Write_Max7219(i+1,disp1[j][i]);_delay_cycles(500000);}
	 _delay_cycles(500000);
	 }
	 }
	return 0;
}