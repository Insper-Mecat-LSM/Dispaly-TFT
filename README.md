Autor: Henrique Rosa  [link](https://github.com/https://github.com/Henriquer88)

Repositóio no MBED [link](https://os.mbed.com/users/henriquer/code/)
# Shield-TFT
Primeiros passos com o Shield TFT


# Objetivo
 Apresentar as funções básicas do Display tft 2.4 touch screen.
 
 # Materiais 
* Nucleo F103
* Compilador MBED [link](https://os.mbed.com/)
* Display 2.4 Touch

# Display TFT 2.4
 
 Esse display tft de 2,4¨ tem resolução de 320×240 pixels, com um esquema de cores de 18 bits que permitem a exibição de até 262.000 tonalidades diferentes, tela touch    resistiva e  um slot para cartão microSD mais controlador ILI9341 e protocolo de comunicação paralela.
  Datasheet do  controlador do Display [link](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)
 
 
<a href="https://imgur.com/NtV6pqn"><img src="https://i.imgur.com/NtV6pqn.png?1" title="source: imgur.com" /></a>
 
 * Pinagem

<a href="https://imgur.com/HqB6b2H"><img src="https://i.imgur.com/HqB6b2H.png?1" title="source: imgur.com" /></a>

# Programas e bibliotecas 

Para utilizar o Display TFT Touch, precisaremos das três bibliotecas abaixo:

* ADA_GFX_kbv
* MCUFRIEND
* TFT_TOUCHSHIELD

# Programas 

##  Escrevendo no Display


```javascript
 //   Exemplo 1
//************************ Biblioteca *****************************************//
#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//****************************************************************************//

//***********************Orientação  Display**********************************//


uint8_t Orientation = 1;  

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

//***********************Escrita no  Display**********************************//
void write ()
{
    tft.setTextColor(BLUE);
    tft.setTextSize(3);     // Tamanho do Texto no Display
    tft.setCursor(60, 30); //  Orientação do texto X,Y
    tft.println("DISPLAY TFT");


}

//****************************************************************************//



void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);  // Fundo do Display
    write();
    delay(1000);
}

void loop()
{

}


```
Compilando esse código no MBED, teremos o resultado abaixo :

<a href="https://imgur.com/QpR13FC"><img src="https://i.imgur.com/QpR13FC.jpg?1" title="source: imgur.com" /></a>

  Para fazermos a escrita no display, devemos utilizar as seguintes funções :
*  tft.setTextColor          Define a cor da fonte   
*  tft.setTextSize()         Define o tamnho da fonte a ser exibida no display
*  tft.setCursor(X,Y)        Define o posicionamento da palavra no plano XY
*  tft.println(" ")          Escreve uma palavra no display 


Se quisermos mudar a cor da tela de fundo , devemos utilizar a função  **tft.fillScreen( WHITE )**

<a href="https://imgur.com/mdVP9Ut"><img src="https://i.imgur.com/mdVP9Ut.jpg?2" title="source: imgur.com" /></a>


## Criando formas geométricas no display.
 Utlizando a biblioteca a ADA_GFX_kbv, conseguimos criar diversas formas, tais como retângulos, círculos, triângulos etc.
 
 * Criando um Retângulo
```javascript
 //   Exemplo 2
//************************ Biblioteca *****************************************//
#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//****************************************************************************//

//***********************Orientação  Display**********************************//


uint8_t Orientation = 1;  

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

//***********************Escrita no  Display**********************************//
void forma ()
{
    //tft.setCursor(100, 50);
    tft.drawRoundRect(60, 90, 190, 40, 1, WHITE); // (x,y,x1,y1,s)
    //tft.fillRoundRect(60, 90, 190, 40, 1, BLUE);
    //tft.fillCircle(250,190,20,WHITE);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(70, 98); // Orientação X,Y
    tft.println("RECTANGLE");


}

//****************************************************************************//



void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);  // Fundo do Display
    forma();
    delay(1000);
}

void loop()
{

}
```

Compilando esse código no MBED, teremos o resultado abaixo :

<a href="https://imgur.com/yduBaTw"><img src="https://i.imgur.com/yduBaTw.jpg?1" title="source: imgur.com" /></a>

Para desenharmos um retângulo, utilizamos a função  **tft.drawRoundRect(X,Y,X1,Y1,S COR)**
*  X   Deslocamento  do retañgulo no plano X
*  Y   Deslocamento  do retângulo no plano Y
*  X1  Tamanho do retângulo em relação ao plano X
*  Y1  Tamanho do retângulo em relação ao plano Y
*  S   Arredondamento das laterais do retângulo


Se quisermos fazer um retângulo com uma determinada cor de fundo, devemos utilizar a função  **tft.fillRoundRect(60, 90, 190, 40, 1, BLUE)**

<a href="https://imgur.com/58mXztE"><img src="https://i.imgur.com/58mXztE.jpg?1" title="source: imgur.com" /></a>

# Criando  Círculos 
```javascript
 //   Exemplo 3
// ************** Display TFT-  ILI9341 Circle************** \\


//************************ Biblioteca *****************************************//
#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//****************************************************************************//

//***********************Orientação  Display**********************************//


uint8_t Orientation = 1;  

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

//***********************Escrita no  Display**********************************//
void forma ()
{

    tft.drawCircle(150,110,80,WHITE);
    //tft.fillCircle(150,110,80,WHITE);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(95, 98); // Orientação X,Y
    tft.println("CIRCLE");


}

//****************************************************************************//



void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);  // Fundo do Display
    forma();
    delay(1000);
}

void loop()
{

}
```
Para desenharmos um círculo, utilizamos a função  **tft.drawCircle(X,Y,R,COR)**
*  X   Deslocamento  do retañgulo no plano X
*  Y   Deslocamento  do retângulo no plano Y
*  R   Raio da circunfência 

Compilando esse código no MBED, teremos o seguinte resultado:

<a href="https://imgur.com/g0Oxw0P"><img src="https://i.imgur.com/g0Oxw0P.jpg?1" title="source: imgur.com" /></a>

Se quisermos fazer um retângulo com uma determinada cor de fundo, devemos utilizar a função  **tft.fillCircle(150,110,80,WHITE)**

<a href="https://imgur.com/XV4qUA1"><img src="https://i.imgur.com/XV4qUA1.jpg?2" title="source: imgur.com" /></a>

# Criando um Triângulo
 ```javascript
  //   Exemplo 4
 // ************** Display TFT-  ILI9341 Triangle******************************\\


//************************ Biblioteca *****************************************//
#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//****************************************************************************//

//***********************Orientação  Display**********************************//


uint8_t Orientation = 1;  

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

//***********************Escrita no  Display**********************************//
void forma ()
{

    tft.drawTriangle(40, 200, 150, 100, 280, 200, WHITE); 
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(86, 160); // Orientação X,Y
    tft.println("TRIANGLE");


}

//****************************************************************************//



void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);  // Fundo do Display
    forma();
    delay(1000);
}

void loop()
{

}
  ```
  
  Compilando esse código no MBED, teremos o seguinte resultado:
  
  <a href="https://imgur.com/6QXZmFz"><img src="https://i.imgur.com/6QXZmFz.jpg?2" title="source: imgur.com" /></a>
  
  Para desenharmos um círculo, utilizamos a função  **tft.drawTriangle(A,B,C,A1,B1,C1 ,COR)**
  
  * (A,A1),(B,B1) e (C,C1)  são os vertíces do triângulo

  Se quisermos fazer um triângulo com uma determinada cor de fundo, devemos utilizar a função  **tft.fillTriangle(40, 200, 150, 100, 280, 200, WHITE)**  
 
  <a href="https://imgur.com/VieGKzo"><img src="https://i.imgur.com/VieGKzo.jpg?1" title="source: imgur.com" /></a>


# Utilizando o touch screen

Antes de utilizarmos o touch, é necessário calibrá-lo. Isso é importantre para mapear os valores dos pontos na tela do display

<a href="https://imgur.com/RVW7MT3"><img src="https://i.imgur.com/RVW7MT3.png" title="source: imgur.com" /></a>

* Calibrando o Touch

```javascript
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


```

Algumas funções importantes para habilitar o touch:

* TouchScreen_kbv         -  Biblioteca responsável por conter as funções do touch 
* ts.getPoint()           -  Função para captura dos dados do display
* uint8_t Orientation     -  Função responsável pela orientação do display
* tft.printf()            -  Escreve um  valor de uma variável no display


Valores obtidos com  calibração medindo as extremidaddes do display:

* Ponto 1 - 894  94
* Ponto 2 - 891  873
* Ponto 3 - 164  876
* Ponto 4 - 164  89

 Valores X e Y  na tela do display

<a href="https://imgur.com/UEgY0eT"><img src="https://i.imgur.com/UEgY0eT.jpg?1" title="source: imgur.com" /></a>
 
 
 # Criando botões no display touch screen
 
 Nesse código criaremos três botôes retângulares, sendo que cada botão corresponde a um determinado comando. Quando fazemos o acionamento de um dos três botões, mudamos o preenchimento da área do retângulo. Para o botão voltar ao seu estado inicial, basta pressioná-lo novamente.
 
 ```javascript
  //   Exemplo 6
 // ************************** Henrique  **************************************//

//  Programa Exemplo 7   - Programa teste para uso de três botões

//
// ************** Display TFT-  ILI9341 Toutch********************************\\


//************************ Biblioteca*****************************************//


#include "mbed.h"
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include "TouchScreen_kbv_mbed.h"

//************************Configuração do Display*****************************//

const int TS_LEFT=121,TS_RT=922,TS_TOP=82,TS_BOT=890;
const PinName XP = D8, YP = A3, XM = A2, YM = D9;   //next common configuration
DigitalInOut YPout(YP);
DigitalInOut XMout(XM);


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

TouchScreen_kbv ts = TouchScreen_kbv(XP, YP, XM, YM, 300);
TSPoint_kbv tp;

// Valores para detectar a pressão do toque
#define MINPRESSURE 10
#define MAXPRESSURE 1000
//****************************************************************************//


//***********************Orientação  Display**********************************//

uint8_t Orientation = 0;

//****************************************************************************//
bool botao_1 = 0;
bool botao_2 = 0;
bool botao_3 = 0;
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


void draw()

{

    tft.drawRoundRect(5, 15, 154, 50, 5, WHITE);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(15, 30);
    tft.println("Button 1");

    tft.drawRoundRect(5, 70, 154, 50, 5, WHITE);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(15,85);
    tft.println("Button 2");

    tft.drawRoundRect(5, 125, 154, 50, 5, WHITE);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(15,140);
    tft.println("Button 3");

}

void show_tft(void)
{

    tft.setTextSize(2);


    tft.setTextColor(MAGENTA,BLUE);


    while (1) {
        tp = ts.getPoint();
        YPout.output();
        XMout.output();

        if (tp.z < MINPRESSURE && tp.z > MAXPRESSURE)

            tp.x = tft.width() - (map(tp.x, TS_RT, TS_LEFT, tft.width(), 0));
            tp.y = tft.height() - (map(tp.y, TS_BOT, TS_TOP, tft.height(), 0));



        if (tp.x>=240&&tp.x<=475 && tp.y>=260&&tp.y<=310) {
            if(botao_1 ==0) {

                tft.fillRoundRect(5, 15, 154, 50, 5, RED);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15, 30);
                tft.println("Button 1");
                botao_1 =!botao_1;
            }

            else {

                tft.fillRoundRect(5, 15, 154, 50, 5, BLACK);
                tft.drawRoundRect(5, 15, 154, 50, 5, WHITE);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15, 30);
                tft.println("Button 1");
                botao_1 =!botao_1;

            }
        }


        if (tp.x>=260&&tp.x<=465 && tp.y>=200&&tp.y<=250) {
            if(botao_2 ==0) {

                tft.fillRoundRect(5, 70, 154, 50, 5, BLUE);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15, 85);
                tft.println("Button 2");
                botao_2 =!botao_2;
            }

            else {


                tft.fillRoundRect(5, 70, 154, 50, 5, BLACK);
                tft.drawRoundRect(5, 70, 154, 50, 5, WHITE);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15,85);
                tft.println("Button 2");
                botao_2 =!botao_2;
            }
        }

        if (tp.x>=460&&tp.x<=650 && tp.y>=150&&tp.y<=195) {
            if(botao_3 ==0) {

                tft.fillRoundRect(5, 125, 154, 50, 5, MAGENTA);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15, 140);
                tft.println("Button 3");
                botao_3 =!botao_3;
            }

            else {
                tft.fillRoundRect(5, 125, 154, 50, 5, BLACK);
                tft.drawRoundRect(5, 125, 154, 50, 5, WHITE);
                tft.setTextColor(GREEN);
                tft.setTextSize(3);
                tft.setCursor(15,140);
                tft.println("Button 3");
                botao_3 =!botao_3;
            }
        }

        // tft.setCursor(0, (tft.height() * 3) / 4);
        // tft.printf("tp.x=%d tp.y=%d   ", tp.x, tp.y);


    }
}





void setup(void)
{

    tft.reset();
    tft.begin();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);
    draw();
    show_tft();


    delay(1000);
}

void loop()
{

}

 ```
 Compilando esse código no MBED, teremos o seguinte resultado:
 
<a href="https://imgur.com/Lk8BUn0"><img src="https://i.imgur.com/Lk8BUn0.jpg?2" title="source: imgur.com" /></a>
 
 ## Botão 1 pressionado 
 
 <a href="https://imgur.com/FwF1RcQ"><img src="https://i.imgur.com/FwF1RcQ.jpg?1" title="source: imgur.com" /></a>

 
 ## Botão 2 pressionado 

 <a href="https://imgur.com/x7RfWcn"><img src="https://i.imgur.com/x7RfWcn.jpg" title="source: imgur.com" /></a>
 
 ## Botão 3 pressionado 
 
 <a href="https://imgur.com/BLlVUcE"><img src="https://i.imgur.com/BLlVUcE.jpg?3" title="source: imgur.com" /></a>

 ## Resultado final
 
<a href="https://imgur.com/7citGbp"><img src="https://i.imgur.com/7citGbp.gif" title="source: imgur.com" /></a>

## Observações 
 As bibliotecas utilizadas nos exemplos estão implementadas apenas para alguns modelos de Nucleo, são elas:
 
 * F072RB
 * F103RB
 * F401RE
 * F411RE
 * F446RE
 * L4333RC
 * L476RG
 * F767ZI

 Caso queira incluir um novo modelo de placa, devemos adicionar um novo Target na biblioteca MCUFRIEND_kbv - utility - pin_shield.h
