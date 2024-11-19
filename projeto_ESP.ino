#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ps5Controller.h>

#define TFT_CS     15
#define TFT_DC     25
#define TFT_RST    26
#define TFT_MOSI   13
#define TFT_SCLK   14

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
unsigned long lastTimeStamp = 0;
uint16_t corPersonalizada = tft.color565(128, 64, 200);

bool jogo=false;
int totalDrink=0;
int currentItem = -1;
const int numItems = 5;
int m=0;

char tabuleiro[3][3]={{'\0','\0 ','\0'},
							        {'\0','\0','\0'},
							        {'\0','\0','\0'}};

int galoX = 0;
int galoY = 0;
bool turn=true;

void onConnect(){
  Serial.println("Connected!.");
}

void onDisConnect(){
  Serial.println("Disconnected!.");    
}



void setup() {
  Serial.begin(115200);
  ps5.attachOnConnect(onConnect);
  ps5.attachOnDisconnect(onDisConnect);
  ps5.begin("D0:BC:C1:63:5C:B2");  //your PS5 controller mac address 
  while (ps5.isConnected() == false) { 
    Serial.println("PS5 controller not found");
    delay(300);
  }
  Serial.println("Ready.");

  SPI.begin(TFT_SCLK, -1, TFT_MOSI);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  navigateMenu(NULL);
}



void loop() {
  Serial.println(currentItem);
  if (ps5.Up() == HIGH) {
    navigateMenu(-1);
    delay(200);
  } 
  if (ps5.Down() == HIGH) {
    navigateMenu(1);
    delay(200);
  }
  if (ps5.Cross() == HIGH) {
    Serial.println(currentItem);
    if(m == 0 && currentItem == 1){
      m=1;
    }
    else if(m == 0 && currentItem == 2){
      m=3;
    }

    else if(m==1 && currentItem == 0){
      m = 2;
    }
    else if(m==1 && currentItem == 1){
      m = 2;
    }
    else if(m==1 && currentItem == 2){
      m = 2;
    }
    else if(m==1 && currentItem == 3){
      m = 2;
    }
    else if(m == 1 && currentItem == 4){
      m=0;
    }


    else if(m == 2 && currentItem == 0){
      m=1;
      totalDrink = totalDrink + 1;
    }
    else if(m == 2 && currentItem == 1){
      m=1;
      totalDrink = totalDrink + 2;
    }
    else if(m == 2 && currentItem == 2){
      m=1;
      totalDrink = totalDrink + 3;
    }
    else if(m == 2 && currentItem == 3){
      m=1;
      totalDrink = 4;
    }
    else if(m == 2 && currentItem == 4){
      totalDrink = 0;
      m=1;
    }
    else if(m == 2 && currentItem == 5){
      m=1;
    }

    else if(m==3 && currentItem == 0){
      m=4;
    }
    else if(m==3 && currentItem == 0){
      m=0;
    }

    currentItem = 0; 
    navigateMenu(0);
    delay(500);
  }
}

void navigateMenu(int direction) {
  switch(m){
    case 0:{
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"BebidaPredefinida", "BebidaPersonalizada", "Jogos"};
      currentItem = currentItem + direction;

      if(currentItem == 3)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 2;

      //Serial.println(currentItem);

      for (int i = 0; i < numItems-2; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);  
        } else {
          tft.setTextColor(ST77XX_WHITE);
        }
        tft.setCursor(20, 20 + i * 20);
        tft.print(menuItems[i]);  
      }
      tft.setCursor(100,100);
      tft.print("Menu 0");
    break;
    }



    case 1:{
      tft.fillScreen(ST77XX_BLACK);
      String menuItems1[] = {"Bebida 1", "Bebida 2", "Bebida 3", "Bebida 4","Sair"};
      currentItem = currentItem + direction;

      if(currentItem == 5)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 4;

      for (int i = 0; i < numItems; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);
        } else {
          tft.setTextColor(ST77XX_WHITE);        
        }
        tft.setCursor(20, 20 + i * 20);
        tft.print(menuItems1[i]); 
      }
      tft.setCursor(100,100);
      tft.print("Menu 1");
    break;
    }
    case 2:{
      int x=0;
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(20, 10);
      tft.print("Quantidade:");
      String menuItems2[] = {"1/4", "2/4", "3/4", "4/4","RESET","Sair"};
      currentItem = currentItem + direction;

      if(totalDrink == 0){
        x=4;

        if(currentItem == 6)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 4;
        
        for (int i = 0; i < x; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + i * 20);
          tft.print(menuItems2[i]);   
        }
      }
      else if(totalDrink == 1){
        x=3;

        if(currentItem == 6)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 4;
        
        for (int i = 0; i < x; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + i * 20);
          tft.print(menuItems2[i]);   
        }
      }
      else if(totalDrink == 2){
        x=2;

        if(currentItem == 6)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 4;
        
        for (int i = 0; i < x; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + i * 20);
          tft.print(menuItems2[i]);   
        }
      }
      else if(totalDrink == 3){
        x=1;

        if(currentItem == 6)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 4;
        
        for (int i = 0; i < x; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + i * 20);
          tft.print(menuItems2[i]);   
        }
      }
      else if(totalDrink == 4){
        tft.setCursor(20,20);
        tft.print("Copo cheio;");
        
      }

      for (int i = 4; i < 2; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);
        } else {
          tft.setTextColor(ST77XX_WHITE);
        }
        tft.setCursor(20, 60 + i * 10);
        tft.print(menuItems2[i]); 
      }

      tft.setCursor(100,100);
      tft.print("Menu 2");
    break;
    }
    case 3:{
      tft.fillScreen(ST77XX_BLACK);
      String menuItems1[] = {"Jogo do Galo", "Snake", "Pong","Sair"};
      currentItem = currentItem + direction;

      if(currentItem == 4)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 3;

      for (int i = 0; i < 4; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);
        } else {
          tft.setTextColor(ST77XX_WHITE);        
        }
        tft.setCursor(20, 20 + i * 20);
        tft.print(menuItems1[i]); 
      }
    break;
    }
    case 4:{
      jogo=true;
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextColor(ST77XX_GREEN);
      tft.setTextSize(2);
      while(jogo){
        Serial.print("X: ");
        Serial.print(galoX);
        Serial.print(" Y: ");
        Serial.println(galoY);
        tft.drawLine(65,109,65,19,ST77XX_WHITE);
        tft.drawLine(95,109,95,19,ST77XX_WHITE);

        tft.drawLine(35,79,125,79,ST77XX_WHITE);
        tft.drawLine(35,49,125,49,ST77XX_WHITE);
        if(ps5.Up() == HIGH){
          delay(500);
          galoY = galoY - 1;
          tft.fillScreen(ST77XX_BLACK);
        }
        else if(ps5.Down() == HIGH){
          delay(200);
          galoY = galoY + 1;
          tft.fillScreen(ST77XX_BLACK);
        }
        else if(ps5.Right() == HIGH){
          delay(200);
          galoX = galoX + 1;
          tft.fillScreen(ST77XX_BLACK);
        }
        else if(ps5.Left() == HIGH){
          delay(200);
          galoX = galoX - 1;
          tft.fillScreen(ST77XX_BLACK);
        }

        if(galoX==3){
          galoX=0;
        }
        else if (galoX == -1){
          galoX=2;
        }
        if(galoY==3){
          galoY=0;
        }
        else if (galoY == -1){
          galoY=2;
        }

        if(turn){
          tft.setCursor(50+(30*galoX),34+(30*galoY));
          tft.print("O"); 
        }
        else if(!turn){
          tft.setCursor(50+(30*galoX),34+(30*galoY));
          tft.print("X"); 
        }

        if(ps5.Circle() == HIGH){
          jogo=false;
          m=0;
          currentItem=0;
        }
      }
    tft.setTextSize(1);
    break;
    }


  }
}
