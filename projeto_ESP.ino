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


int totalDrink=0;
int currentItem = -1;
int m=0;
int galoX = 0;
int galoY = 0;
int bolaX = 0;
int bolaY = 0;
bool turn=false;
bool jogo=false;
bool clear = false;

char tabuleiro[3][3]={{'\0','\0 ','\0'},
							        {'\0','\0','\0'},
							        {'\0','\0','\0'}};


int buttonStateCross = LOW, lastButtonStateCross = LOW;
int buttonStateCircle = LOW, lastButtonStateCircle = LOW;
int buttonStateUp = LOW, lastButtonStateUp = LOW;
int buttonStateDown = LOW, lastButtonStateDown = LOW;
int buttonStateRight = LOW, lastButtonStateRight = LOW;
int buttonStateLeft = LOW, lastButtonStateLeft = LOW;

unsigned long lastDebounceTimeCross = 0, lastDebounceTimeCircle = 0;
unsigned long lastDebounceTimeUp = 0, lastDebounceTimeDown = 0;
unsigned long lastDebounceTimeRight = 0, lastDebounceTimeLeft = 0;

const unsigned long debounceDelay = 50;

bool buttonPressedCross() {
  int reading = ps5.Cross();
  bool pressed = false;
  if (reading != lastButtonStateCross) lastDebounceTimeCross = millis();
  if ((millis() - lastDebounceTimeCross) > debounceDelay) {
    if (reading != buttonStateCross) {
      buttonStateCross = reading;
      if (buttonStateCross == HIGH) pressed = true;
    }
  }
  lastButtonStateCross = reading;
  return pressed;
}

bool buttonPressedCircle() {
  int reading = ps5.Circle();
  bool pressed = false;
  if (reading != lastButtonStateCircle) lastDebounceTimeCircle = millis();
  if ((millis() - lastDebounceTimeCircle) > debounceDelay) {
    if (reading != buttonStateCircle) {
      buttonStateCircle = reading;
      if (buttonStateCircle == HIGH) pressed = true;
    }
  }
  lastButtonStateCircle = reading;
  return pressed;
}

bool buttonPressedUp() {
  int reading = ps5.Up();
  bool pressed = false;
  if (reading != lastButtonStateUp) lastDebounceTimeUp = millis();
  if ((millis() - lastDebounceTimeUp) > debounceDelay) {
    if (reading != buttonStateUp) {
      buttonStateUp = reading;
      if (buttonStateUp == HIGH) pressed = true;
    }
  }
  lastButtonStateUp = reading;
  return pressed;
}

bool buttonPressedDown() {
  int reading = ps5.Down();
  bool pressed = false;
  if (reading != lastButtonStateDown) lastDebounceTimeDown = millis();
  if ((millis() - lastDebounceTimeDown) > debounceDelay) {
    if (reading != buttonStateDown) {
      buttonStateDown = reading;
      if (buttonStateDown == HIGH) pressed = true;
    }
  }
  lastButtonStateDown = reading;
  return pressed;
}

bool buttonPressedRight() {
  int reading = ps5.Right();
  bool pressed = false;
  if (reading != lastButtonStateRight) lastDebounceTimeRight = millis();
  if ((millis() - lastDebounceTimeRight) > debounceDelay) {
    if (reading != buttonStateRight) {
      buttonStateRight = reading;
      if (buttonStateRight == HIGH) pressed = true;
    }
  }
  lastButtonStateRight = reading;
  return pressed;
}

bool buttonPressedLeft() {
  int reading = ps5.Left();
  bool pressed = false;
  if (reading != lastButtonStateLeft) lastDebounceTimeLeft = millis();
  if ((millis() - lastDebounceTimeLeft) > debounceDelay) {
    if (reading != buttonStateLeft) {
      buttonStateLeft = reading;
      if (buttonStateLeft == HIGH) pressed = true;
    }
  }
  lastButtonStateLeft = reading;
  return pressed;
}



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
  tft.setRotation(3);
  navigateMenu(NULL);
}


void loop() {
  Serial.println(currentItem);
  if (buttonPressedUp()) {
    navigateMenu(-1);
  } 
  if (buttonPressedDown()) {
    navigateMenu(1);
  }
  if (buttonPressedCross()) {
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



    else if(m==3 && currentItem == 0){
      m=4;
    }
    else if(m==3 && currentItem == 2){
      m=5;
    }
    
    currentItem = 0; 
    navigateMenu(0);
  }

  if(buttonPressedCircle()){

    if(m == 1){
      m=0;
    }
    else if(m == 2){
      m=1;
    }
    else if(m == 3){
      m=0;
    }
    currentItem = 0; 
    navigateMenu(0);
  }
}

void navigateMenu(int direction) {
  switch(m){
    case 0:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"BebidaPredefinida", "BebidaPersonalizada", "Jogos"};
      currentItem = currentItem + direction;

      if(currentItem == 3)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 2;

      for (int i = 0; i < 3; i++) {  
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
      String menuItems1[] = {"Bebida 1", "Bebida 2", "Bebida 3", "Bebida 4"};
      currentItem = currentItem + direction;

      if(currentItem == 5)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 4;

      for (int i = 0; i < 4; i++) {  
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
      String menuItems2[] = {"1/4", "2/4", "3/4", "4/4","RESET"};
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

      for (int i = 4; i < 5; i++) {  
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
      String menuItems1[] = {"Jogo do Galo", "Snake", "Pong"};
      currentItem = currentItem + direction;

      if(currentItem == 4)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 3;

      for (int i = 0; i < 3; i++) {  
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
      jogoDoGalo();
    break;
    }


    case 5:{
      pong();
    break;  
    }
  }
}

void jogoDoGalo(){
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
    if(buttonPressedUp()){
      galoY = galoY - 1;
      clear = !clear;
    }

    else if(buttonPressedDown()){
      galoY = galoY + 1;
      clear = !clear;
    }

    else if(buttonPressedRight()){
      galoX = galoX + 1;
      clear = !clear;
    }
    else if(buttonPressedLeft()){
      galoX = galoX - 1;
      clear = !clear;
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
      printTabuleiro();
      tft.setTextColor(ST77XX_BLUE);
      tft.print("O"); 
      tft.setTextColor(ST77XX_GREEN);
      if(buttonPressedCross()){
        if(tabuleiro[galoX][galoY]=='X'|| tabuleiro[galoX][galoY]=='O'){
            tft.fillScreen(ST77XX_BLACK);
            tft.setCursor(50,34);
            tft.print("Espaço Ocupado");
            clear=!clear;
            delay(2000);
        }
        else{
        tabuleiro[galoX][galoY]='O';
        turn = !turn;
        }
      }
    }
    else if(!turn){
      printTabuleiro();
      tft.setTextColor(ST77XX_BLUE);
      tft.print("X"); 
      tft.setTextColor(ST77XX_GREEN);
      if(buttonPressedCross()){
        if(tabuleiro[galoX][galoY]=='X'|| tabuleiro[galoX][galoY]=='O'){
            tft.fillScreen(ST77XX_BLACK);
            tft.setCursor(50,34);
            tft.setTextSize(1);
            tft.print("Espaço Ocupado");
            tft.setTextSize(2);
            clear=!clear;
            delay(2000);
        }
        else{
        tabuleiro[galoX][galoY]='X';
        turn = !turn;
        }
      }
    }
    
    if(verificaVitoria()){
      jogo=false;
      m=0;
      currentItem=0;
      turn = false;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          tabuleiro[i][j]='\0';
        }       
      }
      navigateMenu(0);
    }

    if(buttonPressedCircle()){
      jogo=false;
      m=0;
      currentItem=0;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          tabuleiro[i][j]='\0';
        }       
      }
      navigateMenu(0);
    }
  }
tft.setTextSize(1);
}




void printTabuleiro(){
  if(clear){
    tft.fillScreen(ST77XX_BLACK);
    clear = !clear;
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      tft.setCursor(45+(30*i),27+(30*j));
      tft.print(tabuleiro[i][j]);
    }
  }
    tft.setCursor(45+(30*galoX),27+(30*galoY));
}

bool verificaVitoria(){

	for (int i = 0; i < 3; i++){
		if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][2] == 'X'){
			return true;
		}
		 else if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][2] == 'O'){
			return true;
		}
	}
	for (int i = 0; i < 3; i++){
		if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[2][i] == 'X'){
			return true;
		}
		else if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[2][i] == 'O'){
			return true;
		}
	}

	if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[1][1] == 'X'){
		return true;
	}
	else if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[1][1] == 'O'){
		return true;
	}

	if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[1][1] == 'X'){
		return true;
	} 
	else if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[1][1] == 'O'){
		return true;
	}
	return false;
}

void pong(){
  jogo = true;
  printCampo();
  drawScore();
  while(jogo){
    if(buttonPressedCircle()){
      m=0;
      jogo = false;
      currentItem = 0;
      navigateMenu(0);
    }
  }
}

void printCampo(){
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRect(0,  0, 160, 128, ST77XX_WHITE); 
  for (int i = 0; i < 128; i = i+10) {
    tft.drawLine(80, i, 80, i + 5, ST77XX_WHITE);
  }
}

void drawScore() {
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(35, 1);
  tft.println(0);
  tft.setCursor(115, 1);
  tft.println(0);
}
