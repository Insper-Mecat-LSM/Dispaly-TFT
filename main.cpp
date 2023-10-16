 //   Exemplo 5
// ************** Display TFT-  ILI9341 Toutch********************************\\


//************************ Biblioteca*****************************************//
#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include "TouchScreen_kbv_mbed.h"

//******************************Configuração do Display***********************//
const PinName XP = D8, YP = A3, XM = A2, YM = D9; 
const int TS_LEFT=121,TS_RT=922,TS_TOP=82,TS_BOT=890;
DigitalInOut YPout(YP);
DigitalInOut XMout(XM);
TouchScreen_kbv ts = TouchScreen_kbv(XP, YP, XM, YM);
TSPoint_kbv tp;

// Valores para detectar a pressão do toque 
#define MINPRESSURE 10
#define MAXPRESSURE 1000

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//***********************Orientação  Display**********************************//

uint8_t Orientation = 0;

//****************************************************************************//



//***********************Tabela de Cores**************************************//

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//****************************************************************************//


Serial pc(USBTX, USBRX);


void disp()

{
    
        tft.setTextSize(2);
        tft.setTextColor(MAGENTA,BLACK);
        
    while (1) {
        
        tp = ts.getPoint();
        YPout.output();
        XMout.output(); 
        
        tft.setCursor(0, (tft.height() * 2) / 4);
        tft.printf("tp.x=%d tp.y=%d   ", tp.x, tp.y);

    }
    


}



void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);
    disp();
}

void loop()
{


}

int main(void)
{
    setup();
    while (1) {
        loop();
    }
}

