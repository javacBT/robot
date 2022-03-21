
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <SparkFun_APDS9960.h>
#include <BleKeyboard.h>


BleKeyboard bleKeyboard("泥菩萨","泥菩萨的私有设备",100);
SparkFun_APDS9960 apds = SparkFun_APDS9960();

void setup() {

  Wire.begin();  

  pinMode(2,OUTPUT);

  //串口输出
  Serial.begin(9600);

  //模拟蓝牙简谱初始化
  bleKeyboard.begin();

  //oled显示初始化
  oled.init();    
  oled.setFont(font8x8);

  //手势识别初始化
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  setText("No connection",3,0);

  digitalWrite(2,1);
  while(!bleKeyboard.isConnected());
  digitalWrite(2,0);
  setText("......",3,5);
}

void loop() {

  if(bleKeyboard.isConnected()){

    handleGesture();
  }
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {

      digitalWrite(2,1);
      
    switch ( apds.readGesture() ) {
      case DIR_UP:

        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press('d');
        delay(100);
        bleKeyboard.releaseAll();
      
        setText("UP",3,5);
        Serial.println("UP");
        break;
        
      case DIR_DOWN:

        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_F4);
        delay(100);
        bleKeyboard.releaseAll();
      
        setText("DOWN",3,5);
        Serial.println("DOWN");
        break;
        
      case DIR_LEFT:

        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_LEFT_ARROW);
        delay(100);
        bleKeyboard.releaseAll();
      
        setText("LEFT",3,5);
        Serial.println("LEFT");
        break;
        
      case DIR_RIGHT:

        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_RIGHT_ARROW);
        delay(100);
        bleKeyboard.releaseAll();
      
        setText("RIGHT",3,5);
        Serial.println("RIGHT");
        break;
        
      case DIR_NEAR:
      
        setText("NEAR",3,5);
        Serial.println("NEAR");
        break;
        
      case DIR_FAR:

        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('l');
        delay(100);
        bleKeyboard.releaseAll();
      
        setText("FAR",3,5);
        Serial.println("FAR");
        break;
        
      default:
        Serial.println("NONE");
    }

    delay(1000);
    setText("......",3,5);
    digitalWrite(2,0);
  }
}

void setText(String text,int x,int y){

  oled.clearDisplay();              
  oled.setTextXY(x,y);              
  oled.putString(text);
}
