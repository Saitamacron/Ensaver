#include <LiquidCrystal.h>

// variables that will not change -- pins for the buttons and the relay
const int startButton = 7;          
const int relay = 10;
const int addTime = 6;
const int removeTimer = 8;
const int resetButton = 9;


// creates the screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// variables that will change:
int buttonState = 0;         
int addButtonState = 0;
int removeTimerState = 0;
int resetButtonState = 0;
int time = 0;
boolean isStarted = false;

void setup() {

  // setups the pins and the input/output
  pinMode(startButton, INPUT);
  pinMode (relay, OUTPUT);
  pinMode (addTime, INPUT);
  pinMode (removeTimer, INPUT);
  pinMode (resetButton, INPUT); 

  // opens the relay when the Arduino starts
  digitalWrite(relay, HIGH);
  
  // setups the screen
  lcd.begin(16, 2);
}

void loop() {

  // checks if a button is pressed
  buttonState = digitalRead(startButton);
  addButtonState = digitalRead(addTime);
  removeTimerState = digitalRead(removeTimer);
  resetButtonState = digitalRead(resetButton);

  // displays the current time on the screen
  lcd.setCursor(0, 0);
  lcd.print("Current time : ");
  lcd.setCursor(0, 1);
  lcd.print(time);

  // adds time to the timer when the add button is pressed (3600 seconds, or one hour)
  if (addButtonState == HIGH) {
    lcd.clear();
    time = time + 3600;
    delay(1100);
  }

  // removes time to the timer when the remove button is pressed (3600 seconds, or one hour)
  if(removeTimerState == HIGH){ 
    lcd.clear();
    time = time - 3600;
    delay(1100);
  }

  // resets the timer when the reset button is pressed
  if(resetButtonState == HIGH){
      time = 0;
      lcd.clear();
      delay(1100);
  }

  // starts the timer when the start button is pressed
  if (buttonState == HIGH) {
    digitalWrite(relay, HIGH);
    isStarted = true;

    // converts the seconds to milliseconds
    for(int i = 0; i<time; i++) {
       delay(1000);
    }
    
  } else if(isStarted == true) {
    digitalWrite(relay, LOW); // opens the relay (no current) when the time reaches the end
    isStarted = false;
  }
  
}
