#include <LiquidCrystal.h>

#define B1 A0
#define B2 A1
#define B3 A2
#define B4 A3

#define buzzer 10
#define temp_sense A5

uint32_t tick_ms;

int blink_flag;
struct Clock
{
  int hour;
  int minute;
  int second;
  int format;
  
};

LiquidCrystal lcd(12,11,5,4,3,2);

Clock main_display{0,30,0,0};
Clock change_display{0,0,0,0};
Clock alarm_display{0,31,0,0};

void setup() 
{
 
  TCCR1A = 0x00;  
  
  TCCR1B = 0x04; 
  
  TIMSK1 = 0x01;  
  
  TCNT1  = 0x85EE;
  
  lcd.begin(16,2); 
  Serial.begin(9600);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);  
}



void loop()
{
  
  if(millis() - tick_ms >= 100){
    tick_ms = millis(); 
   
    lcd.clear();
    alarm_statechart();
    statechart();
  }
  
}

ISR (TIMER1_OVF_vect)
{ // interrupt
  TCNT1 = 0x85EE; 
  if(blink_flag == 0)
  {
    blink_flag = 1;
    main_display.second++;
  }
  else
  {
    blink_flag = 0;
  }
  
  if(main_display.second == 60)
  {
    main_display.minute++;       
    main_display.second = 0;
  }
  if(main_display.minute == 60)
  {
    main_display.hour++;
    main_display.minute = 0;
  }

  if(main_display.hour == 24)
  {
    //reset
    main_display.hour = 0;
  }
}

uint8_t read_B1_button()
{ 
  uint8_t button = digitalRead(B1);
  static uint8_t button_z = 1;
  uint8_t event = 0;
  
  if(button_z == 1 && button == 0)
  {
     event = 1;
  }

  button_z = button;
  
  return event;
}

uint8_t read_B2_button()
{ 
  uint8_t button = digitalRead(B2);
  static uint8_t button_z = 1;
  uint8_t event = 0;
  
  if(button_z == 1 && button == 0)
  {
     event = 1;
  }

  button_z = button;
  
  return event;
}

uint8_t read_B3_button()
{ 
  uint8_t button = digitalRead(B3);
  static uint8_t button_z = 1;
  uint8_t event = 0;
  
  if(button_z == 1 && button == 0)
  {
     event = 1;
  }

  button_z = button;
  
  return event;
}

uint8_t read_B4_button()
{ 
  uint8_t button = digitalRead(B4);
  static uint8_t button_z = 1;
  uint8_t event = 0;
  
  if(button_z == 1 && button == 0){
     event = 1;
  }

  button_z = button;
  
  return event;
}
uint8_t read_B1_hold(int ms)
{ 
  static int timer = 0;
  uint8_t output;
  
  if(digitalRead(B1) == 0){
    timer++;
  }else{
    timer =0;
  }

  if(timer >= ms){
    output = 1;
  }else{
    output = 0;
  }
  return output;
}

uint8_t read_B2_hold(int ms){ 
  static int timer = 0;
  uint8_t output;
  
  if(digitalRead(B2) == 0){
    timer++;
  }else{
    timer =0;
  }

  if(timer >= ms){
    output = 1;
  }else{
    output = 0;
  }
  return output;
}

int read_temp()
{  
 
  int sensor_input = analogRead(temp_sense);  
  sensor_input = sensor_input << 5;
  sensor_input = ((long)sensor_input * 5000) >> 15;
  sensor_input -= 500;

  return sensor_input*0.1;
}

void alarm_print_hour(int hh, int time_format)
{
  int hour_buffer;
  
  lcd.setCursor(6,0);
  if(!time_format){ 
    if(hh <10){ 
      lcd.print("0");
    }
    lcd.print(hh);

  }else{ 
    if(hh > 12){  
      hour_buffer = hh - 12;
    }else{
      hour_buffer = hh;
    }
    if(hh == 0){
      hour_buffer = 12;
    }
    if(hour_buffer < 10){
      lcd.print("0");
    }
    
    lcd.print(hour_buffer);
  } 

}
void alarm_print_format(int hh, int time_format, int alarm_mode){
  lcd.setCursor(7,1);
  if(!time_format){ 
    lcd.print("24h");
  }
  else{
    if(hh < 12){
      
      lcd.print("AM");  
    }else{
     
      lcd.print("PM");
    }
  }

  lcd.setCursor(8,0);
  lcd.print(":");

  lcd.setCursor(12,1);
  lcd.print("AL:");
  if(alarm_mode){
    lcd.print("O"); 
  }else{
    lcd.print("X"); 
  }
  
}
void alarm_print_minute(int mm){
  lcd.setCursor(9,0);
  if(mm < 10){
    lcd.print("0");
  }
  lcd.print(mm);
}

void buzzer_ring(int reset){
  int array_tone[10] = {0, 0, 0 , 1 , 1, 0 , 0 , 0 , 1 , 1}; 
  static int index = 0;
  if(!reset){
    index = 0; 
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, !array_tone[index]);
    index++;
    if(index >= 10){
      index = 0;
    }
  }
}

void clock_print_hour(int hh, int format){
  int hour_buffer;
  
  lcd.setCursor(0,0);
  if(!format){ 
    if(hh <10){
      lcd.print("0");
    }
    lcd.print(hh);

  }else{ 

    
    if(hh > 12){
      hour_buffer = hh - 12;
    }else{
      hour_buffer = hh;
    }
    if(hh == 0){
      hour_buffer = 12;
    }
    if(hour_buffer < 10){
      lcd.print("0");
    }
    
    lcd.print(hour_buffer);
  }
 
}

void clock_print_minute(int mm){
  lcd.setCursor(3,0);
  if(mm < 10){
    lcd.print("0");
  }
  lcd.print(mm);
}

void clock_print_second(){
  lcd.setCursor(2,0);
  if(blink_flag){
    lcd.print(":");
  }else{  
    lcd.print(" ");
  }
}

void clock_print_format(int hh, int format){
    lcd.setCursor(1,1);
    if(!format){ 
      lcd.print("24h");
    }
    else{
      if(hh < 12){
       
        lcd.print("AM");  
      }else{
       
        lcd.print("PM");
      }
    }
}


void alarm_statechart(){
  int B4_event = read_B4_button();
  static int timer_100ms = 0;
  static int alarm_state = 0;
  static int snooze_indication = 0;
  static int hour_buff = 0;
  static int minute_buff = 0;
  
  
  if((!alarm_state) && (main_display.hour == alarm_display.hour) && (main_display.minute == alarm_display.minute) && alarm_display.format){
    if(main_display.second == 0){
      alarm_state = 1;
      
      Serial.println("RING");
    }
  }
  
  if(alarm_state == 1){
    
    if(B4_event){ // if snooze button is pressed, snooze
      B4_event = 0;   
      alarm_state = 2;
      timer_100ms = 0;
      
      snooze_indication++;
      
      if(snooze_indication <= 10){
        //still snooze
        Serial.println("SNOOZE");
        
        minute_buff = alarm_display.minute + (snooze_indication * 5);
        
        if(minute_buff >= 60){
          minute_buff = minute_buff - 60;
          hour_buff = alarm_display.hour + 1;     
        }
        if(hour_buff >= 24){
          hour_buff -= 24; 
        }
        Serial.print(hour_buff);
        Serial.print(":");
        Serial.println(minute_buff);
       }else{
        alarm_state = 0;
        Serial.println("SNOOZE OUT");
      }
    }
    if(timer_100ms >= 600){ 
      Serial.println("ALARM TIMEOUT");
      timer_100ms = 0;
      alarm_state = 0;
      
    } 
    if(!alarm_display.format){ 
      //alarm off
      alarm_state = 0;
      timer_100ms = 0;
      Serial.println("NONACTIVE");
    }
  }

  
  if(alarm_state == 2){ // snooze state
    if(!alarm_display.format){
      alarm_state = 0;
      Serial.println("NONACTIVE");    
    }
    
    buzzer_ring(0);
    
    //detect alarm
    if(hour_buff == main_display.hour && minute_buff == main_display.minute && main_display.second == 0){
      alarm_state = 1;
      Serial.println("SNOOZE RING");
    }
      
  }

    
  
  if(alarm_state == 0){ 
    buzzer_ring(0);
    snooze_indication = 0;
    minute_buff = 0;
    hour_buff = 0;
  }
  if(alarm_state == 1){ // while ringing
  
    timer_100ms++;
    buzzer_ring(1);
  }
 

}

void statechart(){
  
  int B1_hold = read_B1_hold(30);
  int B2_hold = read_B2_hold(30);
  int B2_event = read_B2_button();
  int B1_event = read_B1_button();
  int B3_event = read_B3_button();

  
  static int timer_100ms = 0;
  static int clock_state = 0;   
  
  static int alarm_state = 0;   
  static int temp_state = 0;     
                                 
  
  if(B1_event && main_display.format == 0 && clock_state == 0 && alarm_state == 0){
    main_display.format = 1; 
    
  }else if(B1_event && main_display.format && clock_state == 0 && alarm_state == 0){
    main_display.format = 0;  
  }

  if(B2_event && alarm_display.format == 0 && alarm_state == 0 && clock_state == 0){
    alarm_display.format = 1; 
    
  }else if(B2_event && alarm_display.format && alarm_state == 0 && clock_state == 0){
    alarm_display.format = 0;  
  }

  if(B3_event && alarm_state == 0 && clock_state == 0 && temp_state == 0){
    B3_event = 0;
    temp_state = 1;
  }else if(B3_event && !alarm_state && !clock_state && temp_state){
    B3_event = 0;
    temp_state = 0;
  }
  
  if(clock_state == 0){
    if(alarm_state == 0 && B2_hold){
      alarm_state = 1;
      B2_event = 0;
      alarm_display.format = 1;
      change_display.minute = alarm_display.minute; 
    }
    if(alarm_state == 1&& B2_event){
      B2_event = 0;
      alarm_state = 2;
      alarm_display.minute = change_display.minute;
      change_display.hour = alarm_display.hour; 
    }
    if(alarm_state == 2 && B2_event){
      B2_event = 0;
      alarm_state = 0;
      alarm_display.hour = change_display.hour;
      
    }
    
  }
  
  if(alarm_state == 0){
    if(clock_state == 0 && B1_hold){
      clock_state = 1;
      B1_event = 0;
      change_display.minute = main_display.minute;
      main_display.format = !main_display.format;
    }
    if(clock_state == 1 && B1_event){
      B1_event = 0;
      clock_state = 2;
      main_display.minute = change_display.minute;
      main_display.second = 0;
      change_display.hour = main_display.hour;
    }
    if(clock_state == 2 && B1_event){
      clock_state = 0;
      B1_event = 0;
      main_display.hour = change_display.hour;
      
    }
  }
  
  if(alarm_state == 0){
    alarm_print_hour(alarm_display.hour, main_display.format);
    alarm_print_format(alarm_display.hour, main_display.format, alarm_display.format);
    alarm_print_minute(alarm_display.minute);
  }
  if(alarm_state == 1){
   
    static int a = 0;
    
    alarm_print_hour(alarm_display.hour, main_display.format);
    alarm_print_format(alarm_display.hour, main_display.format, alarm_display.format);
    if(B3_event){
      B3_event = 0;
      change_display.minute++;
      if(change_display.minute >= 60){
        change_display.minute = 0;
      }
      
      a = 1;
    }
    if(blink_flag == 1 || a == 1){
      alarm_print_minute(change_display.minute); 
      if(blink_flag == 1){
        a = 0;
      }
    }
  }

  if(alarm_state == 2){
   
    static int a = 0;
    
    alarm_print_minute(alarm_display.minute); 
    alarm_print_format(change_display.hour, main_display.format, alarm_display.format);
    if(B3_event){
      B3_event = 0;
      change_display.hour++;
      if(change_display.hour >= 24){
        change_display.hour = 0;
      }
      
      a = 1;
    }
    if(blink_flag == 1 || a == 1){
      alarm_print_hour(change_display.hour, main_display.format);
      
      if(blink_flag == 1){
        a = 0;
      }
    }
  }
  
  
  if(clock_state == 0){
    
    clock_print_minute(main_display.minute);
    clock_print_hour(main_display.hour, main_display.format);
    clock_print_format(main_display.hour, main_display.format);
    clock_print_second();
  }
  if(clock_state == 1){
   
    static int a = 0;
    
    clock_print_hour(main_display.hour, main_display.format);
    clock_print_format(main_display.hour, main_display.format);
    clock_print_second();
    if(B3_event){
      B3_event = 0;
      change_display.minute++;
      if(change_display.minute >= 60){
        change_display.minute = 0;
      }
      
      a = 1;
    }
    if(blink_flag == 1 || a == 1){
      clock_print_minute(change_display.minute); 
      if(blink_flag == 1){
        a = 0;
      }
    }
  }

  if(clock_state == 2){
    
    static int a = 0;
    clock_print_minute(main_display.minute);
    clock_print_format(change_display.hour, main_display.format);
    clock_print_second();
    if(B3_event){
      B3_event = 0;
      change_display.hour++;
      if(change_display.hour >= 24){
        change_display.hour = 0; 
      }
      a = 1;
    }
    if(blink_flag == 1 || a == 1){
      clock_print_hour(change_display.hour, main_display.format); 
      if(blink_flag == 1){
        a = 0;
      }
    }
  }

  if(temp_state == 0)
  {
    int temp = read_temp();
    lcd.setCursor(12,0);
    lcd.print(temp);
    lcd.setCursor(15,0);
    lcd.print("C");
  }else if (temp_state == 1)
  {
    int temp = read_temp();
    temp = ((float)temp * 1.8) + 32;
    temp = round(temp);
    lcd.setCursor(12,0);
    lcd.print(temp);
    lcd.setCursor(15,0);
    lcd.print("F");
  }
}
