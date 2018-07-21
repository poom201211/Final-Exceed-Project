#include <SoftwareSerial.h>
#define REFLECT_1 16
//#define DOOR_1 7
#define SWITCH 4
#define BUZZER 5
#define LED_1 2
#define LED_2 3
#define LED_3 6
#define LDR 17

int count = 0;
int lastcolor = 0; //no color readed
int buttonState, lastState, state = 0, led_state = 0;


SoftwareSerial se_read(12, 13); // write only
SoftwareSerial se_write(10, 11); // read only

struct ProjectData {
  int32_t problem;
  int32_t level;
  int32_t room;
  int32_t sos_level;
  int32_t sos_room;
} project_data = {0, 2, 1, 0, 0};

struct ServerData {
  int32_t problem;
  int32_t level;
  int32_t room;
  int32_t sos_level;
  int32_t sos_room;
} server_data = {0, 2, 1, 0, 0};

const char GET_SERVER_DATA = 1;
const char GET_SERVER_DATA_RESULT = 2;
const char UPDATE_PROJECT_DATA = 3;

ProjectData last_value = {0, 2, 1, 0, 0};

void send_to_nodemcu(char code, void *data, char data_size) {
  char *b = (char*)data;
  char sent_size = 0;
  while (se_write.write(code) == 0) {
    delay(1);
  }
  while (sent_size < data_size) {
    sent_size += se_write.write(b, data_size);
    delay(1);
  }
}
//####### 0=no_color_readed  1=black  2=purple 3=white #######

int reflector(int color) {
  if (color <= 90) {
    if (lastcolor == 0) {
      count++;
    }
    else {
      count = 0;
    }
    lastcolor = 0;  //no color readed
  }
  else if (color > 890) {
    if (lastcolor == 3) {  //"white"
      count++;
    }
    else {
      count = 0;
    }
    lastcolor = 3;
  }
  else if (color < 200) {
    if (lastcolor == 1) {   //black
      count++;
      //Serial.print(lastcolor);
      //Serial.println("\t");
    }
    else {
      count = 0;
    }
    lastcolor = 1;
  }
  else {
    if (lastcolor == 2) {  //gray
      count++;
    }
    else {
      count = 0;
    }
    lastcolor = 2;
  }
  if (count >= 5) {
//    Serial.println("collect!! : ");
//    Serial.print(lastcolor);
    if(lastcolor != 0 ){
    digitalWrite(LED_3, HIGH); }
    return (lastcolor);
  }
  else {
    Serial.print(lastcolor);
    digitalWrite(LED_3, LOW);
  }
}

int checkUpdate(){

  if(last_value.problem != project_data.problem){
    last_value.problem = project_data.problem;
    return 1;
  }
  if(last_value.level != project_data.level){
     last_value.level = project_data.level;
     return 1;
  };
  if(last_value.room != project_data.room){
     last_value.room = project_data.room;
     return 1;
  };
  if(last_value.sos_level != project_data.sos_level){
    last_value.sos_level = project_data.sos_level;
    return 1;
  }
  if(last_value.sos_room != project_data.sos_room){
    last_value.sos_room = project_data.sos_room;
    return 1;
  }
  return 0;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  se_read.begin(38400);
  se_write.begin(38400);
  pinMode(REFLECT_1, INPUT);
  //  pinMode(DOOR_1, INPUT);
  pinMode(SWITCH, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LDR, INPUT);
  while (!se_read.isListening()) {
    se_read.listen();
  }

  Serial.println((int)sizeof(ServerData));
  Serial.println("ARDUINO READY!");
}

uint32_t last_sent_time = 0;
uint32_t last_sent = 0;
boolean is_data_header = false;
char expected_data_size = 0;
char cur_data_header = 0;
char buffer[256];
int8_t cur_buffer_length = -1;

void loop() {
  uint32_t cur_time = millis();
  //send to nodemcu
  int color_1 = analogRead(REFLECT_1);
  project_data.problem = reflector(color_1);
  delay(1000);
  //  project_data.check_empty = digitalRead(DOOR_1);

  buttonState = digitalRead(SWITCH);
  if (buttonState == LOW && lastState == HIGH) {
    state = !state;
    if (state) {
      project_data.sos_level = 1;
      project_data.sos_room = 1;
      analogWrite(BUZZER, 100);
      delay(1500);
      analogWrite(BUZZER, LOW);
    } else {
      digitalWrite(LED_1, LOW);
    }
  }

  lastState = buttonState;

  if (state) {
    if (cur_time - last_sent > 500) {//sos
      digitalWrite(LED_1, (led_state) ? HIGH : LOW);
      led_state = !led_state;
      last_sent = cur_time;
    }
  }

  if (analogRead(LDR) < 100) {
    digitalWrite(LED_2, HIGH);
  }
  else
  {
    digitalWrite(LED_2, LOW);
  }

  //  if ((project_data.problem) != 0) {
  //    digitalWrite(LED_1, HIGH);
  //  }
  //if ((project_data.problem) == 0)
  //{
  //digitalWrite(LED_1, LOW);
  //}

  if (cur_time - last_sent_time > 500) {//always update
    if(checkUpdate()) send_to_nodemcu(UPDATE_PROJECT_DATA, &project_data, sizeof(ProjectData));
    send_to_nodemcu(GET_SERVER_DATA, &server_data, sizeof(ServerData));
    last_sent_time = cur_time;
  }
  //read from sensor....
  //send to nodemcu

  //read data from server pass by nodemcu
  while (se_read.available()) {
    char ch = se_read.read();
    //Serial.print("RECV: ");
    //Serial.println((byte)ch);
    if (cur_buffer_length == -1) {
      cur_data_header = ch;
      switch (cur_data_header) {
        case GET_SERVER_DATA_RESULT:
          //unknown header
          expected_data_size = sizeof(ServerData);
          cur_buffer_length = 0;
          break;
      }
    } else if (cur_buffer_length < expected_data_size) {
      buffer[cur_buffer_length++] = ch;
      if (cur_buffer_length == expected_data_size) {
        switch (cur_data_header) {
          case GET_SERVER_DATA_RESULT: {
              ServerData *data = (ServerData*)buffer;
              //use data to control sensor
              //              Serial.print("color we get: ");
              //              Serial.println(data->problem);
            } break;
        }
        cur_buffer_length = -1;
      }
    }
  }
}

