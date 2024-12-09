#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ps5Controller.h>
#include <FastLED.h>

#define TFT_CS     15
#define TFT_DC     25
#define TFT_RST    26
#define TFT_MOSI   13
#define TFT_SCLK   14

#define LED_PIN     16       // Pin where the LED data line is connected
#define NUM_LEDS    120      // Number of LEDs in your strip
#define BRIGHTNESS  100     // Brightness (0 to 255)
#define LED_TYPE    WS2812 // Type of LEDs (e.g., WS2812B, WS2811, APA102)
#define COLOR_ORDER GRB     // Color order (GRB is common for WS2812B)
#define POT_PIN     34

#define b1  5
#define b2  18
#define b3  32
#define b4  4


CRGB leds[NUM_LEDS];   


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
unsigned long lastTimeStamp = 0;
uint16_t corPersonalizada = tft.color565(128, 64, 200);


int currentItem = 0;
int m=0;
int galoX = 0;
int galoY = 0;
int ronda = 0;
int bolaX = 0;
int bolaY = 0;
int raquete = 20;
int altura1Y = 53;
int lastAltura1Y = 52;
int altura2Y = 53;
int lastAltura2Y = 52;
int lastDebounceTime=0;
int ball_x = 80 ,ball_y = 64;
int ball_dir_x = 1 ,ball_dir_y = 1;
int new_x = 1 ,new_y = 1;
int ball_update;
int score1 = 0, score2 = 0;
int snakeX[100], snakeY[100];
int oldSnakeX[100],oldSnakeY[100]; 
int snakeLength = 3;
int foodX, foodY; 
int score = 0;         
int direction = 0; 
int currentEffect=0;
int hue = 0;
int brightness =0;
int delta = 5;
int cor = 0;
int ledCobra = 0;
int capicidadeMax = 4000;
int quantidade = 5;
unsigned long bebida1 = 0, bebida2 = 0, bebida3 = 0, bebida4 = 0;
int copo = 0;
unsigned long tempo1 = 0,tempo2 = 0,tempo3 = 0,tempo4 = 0;
int vitoria = 0;



            // Direção do Snake: 0=Up, 1=Right, 2=Down, 3=Left
bool turn=false;
bool jogo=false;
bool clear = false;
bool resetBall = false;
bool start = false;
bool isGameOver = false;

char tabuleiro[3][3]={{'\0','\0 ','\0'},
							        {'\0','\0','\0'},
							        {'\0','\0','\0'}};


int buttonStateCross = LOW, lastButtonStateCross = LOW;
int buttonStateCircle = LOW, lastButtonStateCircle = LOW;
int buttonStateUp = LOW, lastButtonStateUp = LOW;
int buttonStateDown = LOW, lastButtonStateDown = LOW;
int buttonStateRight = LOW, lastButtonStateRight = LOW;
int buttonStateLeft = LOW, lastButtonStateLeft = LOW;
int buttonStateR1 = LOW, lastButtonStateR1 = LOW;
int buttonStateL1 = LOW, lastButtonStateL1 = LOW;
int buttonStateR2 = LOW, lastButtonStateR2 = LOW;
int buttonStateL2 = LOW, lastButtonStateL2 = LOW;

unsigned long lastDebounceTimeCross = 0, lastDebounceTimeCircle = 0;
unsigned long lastDebounceTimeUp = 0, lastDebounceTimeDown = 0;
unsigned long lastDebounceTimeRight = 0, lastDebounceTimeLeft = 0;
unsigned long lastDebounceTimeR1 = 0, lastDebounceTimeR2 = 0;
unsigned long lastDebounceTimeL1 = 0, lastDebounceTimeL2 = 0;
unsigned long Debounce = 0;
unsigned long ledDebounce = 0;
unsigned long menuDebounce = 0;
unsigned long bebidaDebounce = 0;
unsigned long debounceTime = 0;

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

bool buttonPressedR1() {
  int reading = ps5.R1();
  bool pressed = false;
  if (reading != lastButtonStateR1) lastDebounceTimeR1 = millis();
  if ((millis() - lastDebounceTimeR1) > debounceDelay) {
    if (reading != buttonStateR1) {
      buttonStateR1 = reading;
      if (buttonStateR1 == HIGH) pressed = true;
    }
  }
  lastButtonStateR1 = reading;
  return pressed;
}

bool buttonPressedL1() {
  int reading = ps5.L1();
  bool pressed = false;
  if (reading != lastButtonStateL1) lastDebounceTimeL1 = millis();
  if ((millis() - lastDebounceTimeL1) > debounceDelay) {
    if (reading != buttonStateL1) {
      buttonStateL1 = reading;
      if (buttonStateL1 == HIGH) pressed = true;
    }
  }
  lastButtonStateL1 = reading;
  return pressed;
}

bool buttonPressedR2() {
  int reading = ps5.R2();
  bool pressed = false;
  if (reading != lastButtonStateR2) lastDebounceTimeR2 = millis();
  if ((millis() - lastDebounceTimeR2) > debounceDelay) {
    if (reading != buttonStateR2) {
      buttonStateR2 = reading;
      if (buttonStateR2 == HIGH) pressed = true;
    }
  }
  lastButtonStateR2 = reading;
  return pressed;
}

bool buttonPressedL2() {
  int reading = ps5.L2();
  bool pressed = false;
  if (reading != lastButtonStateL2) lastDebounceTimeL2 = millis();
  if ((millis() - lastDebounceTimeL2) > debounceDelay) {
    if (reading != buttonStateL2) {
      buttonStateL2 = reading;
      if (buttonStateL2 == HIGH) pressed = true;
    }
  }
  lastButtonStateL2 = reading;
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
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  SPI.begin(TFT_SCLK, -1, TFT_MOSI);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  navigateMenu(NULL);
  menuDebounce = millis();
}



void loop() {
  Serial.println(currentItem);
  if(hue==256){
    hue = 0;
  }
  effect();

  if(m == 4){
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
      if(!turn){
        tabuleiro[galoX][galoY]='X';
        turn = !turn;
        ronda++;
      }
      else if(turn){
        tabuleiro[galoX][galoY]='O';
        turn = !turn;
        ronda++;
      }
      }
    }
  }




  if (ps5.Up() == HIGH && m == 2) {
    if(millis()-menuDebounce >50){
      menuDebounce = millis();
      navigateMenu(-1);
    }
  } 
  else if (ps5.Down() == HIGH && m == 2) {
    if(millis()-menuDebounce >50){
      menuDebounce = millis();
      navigateMenu(1);
    }
  }
  else if(buttonPressedUp()){
    navigateMenu(-1);
  }
  else if(buttonPressedDown()){
    navigateMenu(1);
  }
  else if (buttonPressedCross()) {
    Serial.println(currentItem);

    if(m == 0 && currentItem == 0){
      m = 10;
    }
    else if(m == 0 && currentItem == 1){
      m=1;
    }
    else if(m == 0 && currentItem == 2){
      m=3;
    }
    else if(m == 0 && currentItem == 3){
      m=6;
    }

    else if(m == 1 && currentItem == 0){
      m=2;
      copo = 1;
    }
    else if(m == 1 && currentItem == 1){
      m=2;
      copo = 2;
    }
    else if(m == 1 && currentItem == 2){
      m=2;      
      copo = 3;
    }
    else if(m == 1 && currentItem == 3){
      m=2;
      copo = 4;
    }
    else if(m == 1 && currentItem == 4){
      m = 9;
      bebidaDebounce = millis();
    }
    else if(m == 1 && currentItem == 5){
      bebida1 = 0;
      bebida2 = 0;
      bebida3 = 0;
      bebida4 = 0;
      tempo1 = 0;
      tempo2 = 0;
      tempo3 = 0;
      tempo4 = 0;
      m=0;
    }

    else if(m == 2 && copo == 1){
      bebida1 = quantidade;
      m = 1;
      quantidade = 0;
    }
    else if(m == 2 && copo == 2){
      bebida2 = quantidade;
      m = 1;
      quantidade = 0;
    }
    else if(m == 2 && copo == 3){
      bebida3 = quantidade;
      m = 1;
      quantidade = 0;
    }
    else if(m == 2 && copo == 4){
    bebida4 = quantidade;
    m = 1;
    quantidade = 0;
    }

    else if(m==3 && currentItem == 0){
      start = true;
      m=4;
      vitoria = 0;
    }
    else if(m==3 && currentItem == 1){
      start = true;
      m=7;
      ledDebounce = millis();
    } 
    else if(m==3 && currentItem == 2){
      start = true;
      vitoria = 0;
      m=5;
    }
    else if(m==6 && currentItem == 0){
      currentEffect = 0;
      currentItem = 0;
    }
    else if(m==6 && currentItem == 1){
      currentEffect = 1;
      currentItem = 1;
    }
    else if(m==6 && currentItem == 2){
      currentEffect = 2;
      currentItem = 2;
    }
    else if(m==6 && currentItem == 3){
      currentEffect = 3;
      currentItem = 3;
    }
    else if(m==6 && currentItem == 4){
      currentEffect = 4;
      currentItem = 4;
      Debounce = millis();
    }
    else if(m==6 && currentItem == 5){
      currentEffect = 5;
      m = 8;
    }
    else if(m==8 && currentItem == 0){
      cor = hue;
      m = 6;
    }
    else if(m==8 && currentItem == 1){
      m = 6;
    }

    else if(m==10 && currentItem == 0){
     shotRefrigerante();
     m=0;
    }
    else if(m==10 && currentItem == 1){
      tracadinho();
      m=0;
    }
    else if(m==10 && currentItem == 2){
      shot();
      m=0;
    }
    else if(m==11){
      m=0;
    }

    else if(m==12){
      m=0;
    }
    currentItem = 0; 
    navigateMenu(0);
  }

  else if(buttonPressedCircle()){

    if(m == 1){
      m=0;
    }
    else if(m == 2){
      m=1;
    }
    else if(m == 3){
      m=0;
    }
    else if(m == 4){
      start = true;
      ronda = 0;
      m=0;
      currentItem=0;
      turn = false;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          tabuleiro[i][j]='\0';
        }       
      }
    }
    else if(m == 5){
      m=0;
      score1 = 0;
      score2 = 0;
      altura1Y = 53;
      altura2Y = 53;
    }
    else if(m == 6){
      m=0;
    }
    else if(m == 10){
      m=0;
    }
    currentItem = 0; 
    navigateMenu(0);
  }

  if (m == 4 || m == 5 || m == 7){
    navigateMenu(0);
  }
}

void navigateMenu(int direction) {
  switch(m){
    case 0:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"BebidaPredefinida", "BebidaPersonalizada", "Jogos","Luz"};
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
        tft.print(menuItems[i]);  
      }
      tft.setCursor(100,100);
      tft.print("Menu 0");
    break;
    }



    case 1:{
      tft.fillScreen(ST77XX_BLACK);
      String menuItems1[] = {"Bebida 1", "Bebida 2", "Bebida 3", "Bebida 4","Encher Copo","RESET bebida"};
      currentItem = currentItem + direction;

      if(currentItem == 7)
        currentItem = 0;
      else if(currentItem == -1)
        currentItem = 6;

      tft.setCursor(100, 20);
      int bebidaTotal = bebida1 + bebida2 + bebida3 + bebida4;
      Serial.println(bebida1);
      Serial.println(bebida2);
      Serial.println(bebida3);
      Serial.println(bebida4);
      tft.print(bebidaTotal);
      tft.print(" ml;");
      for (int i = 0; i < 6; i++) {  
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
    case 2:{
      if((bebida1 + bebida2 + bebida3 + bebida4)>4000){
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(20, 10);
        tft.println("Quantidade de bebida");
        tft.print("maxima atingida");
      }
      else{
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(20, 10);
        tft.println("Quantidade:");
        tft.setCursor(20, 30);
        tft.println("Quantidade maxima:");
        tft.setCursor(20, 40);
        tft.println("1000ml");
        if(direction == 1){
          direction = -5;
        }
        else if(direction == -1){
          direction = 5;
        }
        quantidade = quantidade + direction;
        if(quantidade == 1005){
          quantidade = 0;
        }
        else if(quantidade < 0){
          quantidade = 1000;
        }
        tft.setCursor(20, 60);
        tft.print(quantidade);
        tft.println("  ml");

        tft.setCursor(10, 110);
        tft.println("Precione X para confirmar");
    }
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

    case 6:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"Vermelho", "Verde", "Azul","Arco-Iris","Respiracao","Custom"};
      currentItem = currentItem + direction;
      if(currentItem >=0 && currentItem <= 4){
        if(currentItem == 5)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 2;

        for (int i = 0; i < 5; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);  
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + i * 20);
          tft.print(menuItems[i]);  
        }
        tft.setCursor(100,100);
      }
      else if(currentItem>=5){
        /*
        if(currentItem == 5)
          currentItem = 0;
        else if(currentItem == -1)
          currentItem = 2;
        */
        for (int i = 5; i < 6; i++) {  
          if (i == currentItem) {
            tft.setTextColor(ST77XX_GREEN);  
          } else {
            tft.setTextColor(ST77XX_WHITE);
          }
          tft.setCursor(20, 20 + (i-5) * 20);
          tft.print(menuItems[i]);  
        }
        tft.setCursor(100,100);
      }
    break;  
    }

    case 7:{
      snake();
    break;
    }
    case 8:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"Salvar","Cancelar"};
      currentItem = currentItem + direction;

      for (int i = 0; i < 2; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);
        } else {
          tft.setTextColor(ST77XX_WHITE);        
        }
        tft.setCursor(20, 20 + i * 20);
        tft.print(menuItems[i]); 
      }
    break;
    }
    case 9:{
      tft.fillScreen(ST77XX_BLACK);
      encherCopo();
    break;
    }

    case 10:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      String menuItems[] = {"Shot + Refrigerante","Tracadinho","Shot"};
      currentItem = currentItem + direction;

      if(currentItem == 3){
        currentItem = 0;
      }
      else if(currentItem == -1){
        currentItem = 2;
      }
      for (int i = 0; i < 3; i++) {  
        if (i == currentItem) {
          tft.setTextColor(ST77XX_GREEN);
        } else {
          tft.setTextColor(ST77XX_WHITE);        
        }
        tft.setCursor(20, 20 + i * 20);
        tft.print(menuItems[i]); 
      }
    break;
    }
    case 11:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(20, 20);
      tft.print("Vitoria do jogador:");
      tft.println(vitoria);

      tft.setCursor(20, 50);
      tft.print("Pressione X para continuar");
    break;
    } 

    case 12:{
      tft.setTextSize(1);
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(20, 20);
      tft.print("EMPATE");
      tft.setCursor(20, 50);
      tft.print("Pressione X para continuar");
    break;
    } 
  }
}

void jogoDoGalo(){
  if(start){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    start = false;
  }
  tft.setTextSize(2);
  Serial.print("X: ");
  Serial.print(galoX);
  Serial.print(" Y: ");
  Serial.println(galoY);

  tft.drawLine(65,109,65,19,ST77XX_WHITE);
  tft.drawLine(95,109,95,19,ST77XX_WHITE);

  tft.drawLine(35,79,125,79,ST77XX_WHITE);
  tft.drawLine(35,49,125,49,ST77XX_WHITE);

  if(galoX==3){
    galoX=0;
  }
  else if (galoX==-1){
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
  }
  else if(!turn){
    printTabuleiro();
    tft.setTextColor(ST77XX_BLUE);
    tft.print("X"); 
    tft.setTextColor(ST77XX_GREEN);
  }
  
  if(verificaVitoria()){
    if(turn){
      vitoria = 1;
    }
    else if(!turn){
      vitoria = 2;
    }

    ronda = 0;
    start = true;
    m=11;
    currentItem=0;
    turn = false;
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        tabuleiro[i][j]='\0';
      }       
    }
    navigateMenu(0);
    return;
  }
  if(ronda == 9){
    start = true;
    ronda = 0;
    m=12;
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
    return;
  }
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
  if(start){
    printCampo();
    printScore();
    printTracos();
    printJogador1();
    printJogador2();
    ball_x = random(45, 50);
    ball_y = random(23, 33);
    ball_update = millis(); 
    lastDebounceTime = millis(); 
    start = false;
  }
  if(resetBall){
    tft.fillScreen(ST77XX_BLACK);
    printCampo();
    printScore();
    printTracos();
    ball_x = random(45, 50);
    ball_y = random(23, 33);
    ball_dir_x = 1;
    ball_dir_y = 1;
    resetBall = false;
    ball_update = millis();
    printJogador1();
    printJogador2();
  }
  else{
    if((millis()-ball_update) > 10){
      printTracos();
      ball_update = millis();
      int new_x = ball_x + ball_dir_x;
      int new_y = ball_y + ball_dir_y;

      if(score1 == 10 || score2 == 10){
        if(score1 == 10){
          vitoria = 1;
          m = 11;
          navigateMenu(0);
        }
        else if(score2 = 10){
          vitoria = 2;
          m = 11;
          navigateMenu(0);
        }

        score1 = 0;
        score2 = 0;
        resetBall = true;
      }
      if  (new_x == 0) {
        score2++;
        resetBall = true;
      }
      if  (new_x == 160) {
        score1++;
        resetBall = true;
      }

      if(new_y == 17 || new_y == 127){
        ball_dir_y = -ball_dir_y;
        new_y = new_y + (ball_dir_y + ball_dir_y);
      }

      if (new_x == 157 && new_y <= altura2Y && new_y >=  altura2Y - raquete) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }

      if (new_x == 3 && new_y <= altura1Y && new_y >=  altura1Y - raquete) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }


      tft.drawPixel(ball_x,  ball_y, ST77XX_BLACK);
      tft.drawPixel(new_x, new_y, ST77XX_WHITE);
      ball_x = new_x;
      ball_y = new_y;
    }

    if(ps5.L2() == HIGH && (millis()-lastDebounceTime)>50){
      lastDebounceTime = millis();
      altura1Y+=10;
      if(altura1Y > 126){
        altura1Y = 126;
      }
      printJogador1();
    }
    if(ps5.L1() == HIGH && (millis()-lastDebounceTime)>50){
      lastDebounceTime = millis() ;
      altura1Y-=10;
      if(altura1Y < 37){
        altura1Y = 37;
      }

      printJogador1();
    }

    if(ps5.R2() == HIGH && (millis()-lastDebounceTime)>50){
      lastDebounceTime = millis() ;
      altura2Y+=10;
      if(altura2Y > 126){
        altura2Y = 126;
      }
      printJogador2();

    }
    if(ps5.R1() == HIGH && (millis()-lastDebounceTime)>50){
      lastDebounceTime = millis();
      altura2Y-=10;
      if(altura2Y < 37){
        altura2Y = 37;
      }

      printJogador2();
    }

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
  tft.drawRect(0,  16, 160, 112, ST77XX_WHITE); 
}

void printTracos(){
    for (int i = 0; i < 128; i = i+10) {
    tft.drawLine(80, i, 80, i + 5, ST77XX_WHITE);
  }
}

void printScore() {
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(35, 1);
  tft.println(score1);
  tft.setCursor(115, 1);
  tft.println(score2);
}

void printJogador1() {
  tft.drawLine(3, lastAltura1Y, 3, lastAltura1Y - raquete, ST77XX_BLACK);
  tft.drawLine(3, altura1Y, 3, altura1Y - raquete, ST77XX_WHITE);
  lastAltura1Y = altura1Y;
}

void printJogador2() {
  tft.drawLine(157, lastAltura2Y, 157, lastAltura2Y - raquete, ST77XX_BLACK);
  tft.drawLine(157, altura2Y, 157, altura2Y - raquete, ST77XX_WHITE);
  lastAltura2Y = altura2Y;
}
void snake() {
    if (start) {
        jogo = true;
        tft.fillScreen(ST77XX_BLACK);
        tft.setTextColor(ST77XX_GREEN);
        tft.setTextSize(2);
        // Inicializa variáveis do jogo Snake
        resetSnakeGame();
        debounceTime = millis();
        start = false;
        tft.drawRect(0,  8, 160, 120, ST77XX_WHITE); 
    }
    if (isGameOver) {
        tft.fillScreen(ST77XX_RED);
        tft.setCursor(30, 50);
        tft.setTextColor(ST77XX_WHITE);
        tft.print("Game Over");
        delay(1000);
        resetSnakeGame();
        m = 0;
        navigateMenu(0);
        return ;
    }

    // Verifica controles
    if (ps5.Up() == HIGH && direction != 2) direction = 0;
    if (ps5.Right() == HIGH && direction != 3) direction = 1;
    if (ps5.Down() == HIGH && direction != 0) direction = 2;
    if (ps5.Left() == HIGH && direction != 1) direction = 3;

    // Sai do jogo se o botão Circle for pressionado
    if (ps5.Circle() == HIGH) {
        jogo = false;
        m = 0;
        currentItem = 0;
    }

    if ((millis() - debounceTime) > 150) {
        debounceTime = millis();
        // Atualiza a posição do Snake
        updateSnake();
        // Renderiza o Snake e a pontuação
        drawSnake();
        drawScore();
        tft.drawRect(0,  8, 160, 128, ST77XX_WHITE); 
    }
}

void resetSnakeGame() {
    snakeLength = 3;
    snakeX[0] = 5;
    snakeY[0] = 5;
    for (int i = 1; i < snakeLength; i++) {
        snakeX[i] = snakeX[0] - i;
        snakeY[i] = snakeY[0];
    }
    snakeY[0]++;
    spawnFood();
    score = 0;  // Reinicia a pontuação
    isGameOver = false;
}

void updateSnake() {
    // Move o corpo do Snake
    for (int i = snakeLength - 1; i > 0; i--) {
        oldSnakeX[i] = snakeX[i];
        oldSnakeY[i] = snakeY[i];
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Move a cabeça do Snake
    if (direction == 0) snakeY[0]--; // cima
    if (direction == 1) snakeX[0]++; // direita
    if (direction == 2) snakeY[0]++; // baixo
    if (direction == 3) snakeX[0]--; // esquerda

    // Verifica se bate nas bordas
    if (snakeX[0] > 19 || snakeX[0] < 0 || snakeY[0] < 1 || snakeY[0] > 15) {
        isGameOver = true;
    }

    // Verifica se bate na própria cobra
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            isGameOver = true;
        }
    }

    // Verifica se comeu a comida
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeLength++;
        spawnFood();
        score++;  // Incrementa a pontuação
    }
}

void drawSnake() {
    // Desenha a comida
    tft.fillRect(foodX * 8, foodY * 8, 8, 8, ST77XX_RED);

    // Desenha o Snake
    for (int i = 0; i < snakeLength; i++) {
      tft.fillRect(oldSnakeX[i] * 8, oldSnakeY[i] * 8, 8, 8, ST77XX_BLACK);
      tft.fillRect(snakeX[i] * 8, snakeY[i] * 8, 8, 8, ST77XX_GREEN);
    }
}

void drawScore() {
    // Desenha a pontuação no canto superior esquerdo
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.fillRect(0, 0, 50, 10, ST77XX_BLACK); // Apaga o texto anterior
    tft.print("Score: ");
    tft.print(score);
}

void spawnFood() {
    foodX = random(0, 19);
    foodY = random(0, 15);
}

void effect(){
  if(m==5){
    int x = map(ball_x,0,160,21,46);
    FastLED.clear();
    leds[x] = CRGB::White;
    FastLED.show();
    return;
  }
  if(m==7){
  if(m==7 && (millis()-ledDebounce)>150){
    if(ledCobra==90)
      ledCobra = 0;

    ledDebounce = millis();
    FastLED.clear();
    leds[ledCobra] = CRGB::White;
    FastLED.show();
    ledCobra++;
  }
      return;
  }


  if(currentEffect == 0)
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  else if(currentEffect == 1)
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  else if(currentEffect == 2)
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  else if(currentEffect == 3){
      fill_rainbow(leds, NUM_LEDS, hue, 7); // Fill the strip with a gradient
      hue++;
  }
  else if(currentEffect==4){
      if(millis()-Debounce > 20){
        Debounce = millis();
        brightness += delta;
        if(brightness == 0 || brightness == 255) {
          delta = -delta;
        }
      fill_solid(leds, NUM_LEDS, CHSV(cor, 255, 255));
      FastLED.setBrightness(brightness);
    }
  }
  else if(currentEffect==5){
    int potValue = analogRead(POT_PIN);
    potValue = potValue / 4;
    hue = map(potValue, 0, 1023, 0, 255);
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
  }
  FastLED.show();

}

void encherCopo(){

  tft.setCursor(20,10);
  tft.print("Aguarde...");

  if(bebida1 !=0){
    tempo1 = bebida1 * 0.044 * 1000;
    analogWrite(b1, 255);
    delay(tempo1);
    analogWrite(b1, 0);
    delay(50);
  }

  if(bebida2 !=0){
    tempo2 = bebida2 * 0.047* 1000;
    analogWrite(b2, 255);
    delay(tempo2);
    analogWrite(b2, 0);
    delay(50);
  }

  if(bebida3 !=0){
    tempo3 = bebida3 * 0.047* 1000;
    analogWrite(b3, 255);
    delay(tempo3);
    analogWrite(b3, 0);
    delay(50);
  }

  if(bebida4 !=0){
    tempo4 = bebida4 * 0.045* 1000;
    analogWrite(b4, 255);
    delay(tempo4);
    analogWrite(b4, 0);
    delay(50);
  }

  m=0;
  currentItem = 0;
  navigateMenu(0);

  tempo1 = 0;
  tempo2 = 0;
  tempo3 = 0;
  tempo4 = 0;

  return;
}

void shotRefrigerante(){
  
  bebida1 = 25;
  tempo1 = bebida1 * 0.044;
  analogWrite(b1, 255);
  delay(600);
  delay(tempo1*1000);
  analogWrite(b1, 0);
  delay(550);

  bebida2 = 225;
  tempo2 = bebida2 * 0.047;
  analogWrite(b2, 255);
  delay(600);
  delay(tempo2*1000);
  analogWrite(b2, 0);
  delay(50);

  bebida1 = 0;
  bebida2 = 0;
  navigateMenu(0);
  return;

}

void tracadinho(){
  bebida3 = 125;
  tempo3 = bebida3 * 0.047;
  analogWrite(b3, 255);
  delay(tempo3*1000);
  analogWrite(b3, 0);
  delay(50);

  bebida4 = 125;
  tempo4 = bebida4 * 0.045;
  analogWrite(b4, 255);
  delay(tempo4*1000);
  analogWrite(b4, 0);
  delay(50);

  bebida3 = 0;
  bebida4 = 0;
  navigateMenu(0);
  return;

}

void shot(){
  bebida1 = 25;
  tempo1 = bebida1 * 0.044;
  analogWrite(b1, 255);
  delay(600);
  delay(tempo1*1000);
  analogWrite(b1, 0);
  delay(50);

  bebida1 = 0;
  navigateMenu(0);
  return;
}
