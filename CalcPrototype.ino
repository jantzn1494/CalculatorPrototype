/*  Nathan Jantz       - njantz2
 *  Karen Chan         - kchan43
 *  Ebrahim Broachwala - ebroac2
 *  Derek Altman       - daltma3
 *  
 *  Standard Calculator
 *  Use LCD 1602 Module for output, top will list operation and bottom will show answer.
 *  Use 5 push buttons for input: number up, number down, clear, addition, multiplication.
 *  
 *  Circuit setup:
 *  LCD:
 *  VSS = GND
 *  VDD = 5v
 *  V0  = 6
 *  RS  = 12
 *  RW  = GND
 *  E   = 11
 *  D4  = 5
 *  D5  = 4
 *  D6  = 3
 *  D7  = 2
 *  A   = 5v (w/ 220 resistor)
 *  K   = GND
 *  
 *  Buttons:
 *  Number up = 13 (w/ resistor)
 *  Number down = 10 (w/ resistor)
 *  Clear = 9 (w/ resistor)
 *  Addition = 8 (w/ resistor)
 *  Multiplication = 7 (w/ resistor)
 *  
 */
 #include<LiquidCrystal.h>

//Constants
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int contrast = 0;
const int Up = 13, Down = 10, Clear = 9, Add = 8, Mult = 7;
const int Status = 0; //for checking button status

//Variables
int v1, v2, op = 0;   //value 1, value 2, and operator
String str;           //string used for output on LCD

void setup() { 
  lcd.begin(16, 2);         // Set up LCD
  analogWrite(6, contrast); //pin 6 of contrast 0
  lcd.setCursor(0,0);       //Cursor is at row 1, column 1
  //button setup
  pinMode(Up, INPUT);
  pinMode(Down, INPUT);
  pinMode(Clear, INPUT);
  pinMode(Add, INPUT);
  pinMode(Mult, INPUT);
}

void loop() {
  delay(10); //required for bounce
  if(Status != digitalRead(Up)){      //Up button pressed
    while(Status != digitalRead(Up)){ //required for bounce
      delay(10);
    }
    if(op > 0){ //if operator exists, add 1 to second value
      v2++;
    }
    else{       //else add 1 to first
      v1++;
    }
  }
  if(Status != digitalRead(Down)){      //Down button pressed
    while(Status != digitalRead(Down)){ //required for bounce
      delay(10);
    }
    if(op > 0){ //if operator exists, subtract 1 from second value
      v2--;
    }
    else{       //else subtract 1 from first
      v1--;
    }
  }
  if(Status != digitalRead(Clear)){      //Clear button pressed
    while(Status != digitalRead(Clear)){ //required for bounce
      delay(10);
    }
    v1 = 0; //value 1 cleared
    v2 = 0; //value 2 cleared
    op = 0; //no operator
  }
  if(Status != digitalRead(Add)){      //Add button pressed
    while(Status != digitalRead(Add)){ //required for bounce
      delay(10);
    }
    op = 1; //used for output later
  }
  if(Status != digitalRead(Mult)){      //Mult button pressed
    while(Status != digitalRead(Mult)){ //required for bounce
      delay(10);
    }
    op = 2; //used for output later
  }
  
  /*----------------LCD code----------------*/
  lcd.clear();        //Clear LCD
  lcd.setCursor(0,0); //First Row
  
  if(op > 0){             //Operation Exists
    if(op == 1){
      str = String(String(v1) + " + " + String(v2)); 
      lcd.print(str);     //Print Operation
      lcd.setCursor(8,1); //Second Row
      lcd.print(v1 + v2);
    }
    else if(op == 2){
      str = String(String(v1) + " x " + String(v2));
      lcd.print(str);     //Print Operation
      lcd.setCursor(8,1); //Second Row
      lcd.print(v1 * v2);
    }
    else{
      str = "Error";
      lcd.print(str);     //Print Error Message
    }
  }
  else{                   //Operation DNE Yet
    str = String(v1);
    lcd.print(str);       //Current Number
  }
}


/*-------------------------lab material---------------------------------
  //lab material
  lcd.setCursor(0,0); // First Row
  lcd.print(Name);    // Print Name

  lcd.setCursor(scrollCursor, 1);          // Second Row
  lcd.print(Quote.substring(Start, Stop)); // Print only the substring between start and stop

  delay(400);

  lcd.clear();

  if(Start == 0 && scrollCursor > 0){ // start scroll
    scrollCursor--;
    Stop++;
  }
  else if(Start == Stop){ // reset string
    Start = Stop = 0;
    scrollCursor = 16;    // width of screen
  }
  else if((Stop == Quote.length()) && (scrollCursor == 0)){ // end reached, allow to scroll off screen
    Start++;
  }
  else{ //scroll text between beginning and end of quote
    Start++;
    Stop++;
  }

}
*/
