#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EspSoftwareSerial.h>
#include <math.h>

SoftwareSerial se_read(D5, D6); // write only
SoftwareSerial se_write(D0, D1); // read only

struct ProjectData {
    uint32_t problem;
    uint32_t level;
    uint32_t room;
    // unit32_t timing;
    uint32_t check_empty;

    
} project_data = {0,2,1,1};

struct ServerData {
    uint32_t problem;
    uint32_t level;
    uint32_t room;
    // unit32_t timing;
    uint32_t check_empty;
   
} server_data = {0,2,1,1};
String const url = "http://ecourse.cpe.ku.ac.th/exceed/api/";
const char GET_SERVER_DATA = 1;
const char GET_SERVER_DATA_RESULT = 2;
const char UPDATE_PROJECT_DATA = 3;

// wifi configuration
const char SSID[] = "CHUT";
const char PASSWORD[] = "*123*abc";

// for nodemcu communication
uint32_t last_sent_time = 0;
char expected_data_size = 0;
char cur_data_header = 0;
char buffer[256];
int8_t cur_buffer_length = -1;

void send_to_arduino(char code, void *data, char data_size) {
  char *b = (char*)data;
  int sent_size = 0;
  while (se_write.write(code) == 0) {
    delay(1);
  }
  while (sent_size < data_size) {
    sent_size += se_write.write(b, data_size); 
    delay(1);
  }
}

void wifi_initialization() {
  Serial.println("WIFI INITIALIZING.");

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    yield();
    delay(10);
  }

  Serial.println("WIFI INITIALIZED.");
}

void serial_initialization() {
  Serial.begin(115200);
  se_read.begin(38400);
  se_write.begin(38400);

  while (!se_read.isListening()) {
    se_read.listen();
  }

  Serial.println();
  Serial.println("SERIAL INITIALIZED.");
}

String set_builder(const char *key, int32_t value) {
  String str = url;
  str = str + key;
  str = str + "/set/?value=";
  str = str + value;
  return str;
}
String get_builder(const char *key) {
  String str = url;
  str = str + key;
  str = str + "/view/";
  return str;
}

//condition for connect server
void update_data_to_server_callback(String const &str) {
//  Serial.println("update_data_to_server_callback FINISHED!");
}

bool GET(const char *url, void (*callback)(String const &str,int32_t &value), int32_t &value) {
  HTTPClient main_client;
  main_client.begin(url);
  if (main_client.GET() == HTTP_CODE_OK) {
    // Serial.println("GET REQUEST RESPONSE BEGIN");
    if (callback != 0) {
      callback(main_client.getString(),value);
    }
    delay(200);
    return true;
  }
//   Serial.println("GET REQUEST RESPONSE BEGIN");
  return false;
}
bool GET(const char *url, void (*callback)(String const &str,float &value), float &value) {
  HTTPClient main_client;
  main_client.begin(url);
  if (main_client.GET() == HTTP_CODE_OK) {
//    Serial.println("GET REQUEST RESPONSE BEGIN");
    if (callback != 0) {
      callback(main_client.getString(),value);
    }
    delay(200);
    return true;
  }
  
//  Serial.println("GET REQUEST RESPONSE BEGIN");
  return false;
}

bool POST(const char *url, void (*callback)(String const &str)) {
  HTTPClient main_client;
  main_client.begin(url);
  if (main_client.GET() == HTTP_CODE_OK) {
//    Serial.println("GET REQUEST RESPONSE BEGIN");
    if (callback != 0) {
      callback(main_client.getString());
    }
    delay(200);
    return true;
  }
//  Serial.println("GET REQUEST RESPONSE BEGIN");
  return false;
}

int get_request_int(String const &str) {
  int32_t tmp = str.toInt();
  return tmp;
}

float get_request_float(String const &str) {
  float tmp = str.toFloat();
  return tmp;
}
void get_request(String const &str, int32_t &value){
  value = get_request_int(str);
}
void get_request(String const &str, float &value){
  value = get_request_float(str);  
}

void get_request_raw_callback(String const &str) {
//  Serial.println("GET REQUEST RESPONSE BEGIN");
  Serial.println("========================");
  Serial.println(str.c_str());
  Serial.println("========================");
//  Serial.println("GET REQUEST RESPONSE END");
}


uint32_t getAndPrint(String var_get){
    uint32_t tmp;
    GET(get_builder("buapalm-" + var_get).c_str(), get_request, tmp); // tmp = GET
    Serial.print("GET <<  " + var_get + " : ");
    Serial.println(tmp);
    return tmp;
}
unit32_t postAndPrint(uint32_t var_post){
    Serial.print("POST >> Problem : ");
    Serial.println(var_post);
    POST(set_builder("buapalm-" + (String)var_post, var_post).c_str(), update_data_to_server_callback) 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  serial_initialization();
  wifi_initialization();

  Serial.print("sizeof(ServerData): ");
  Serial.println((int)sizeof(ServerData));
  Serial.print("ESP READY!");
}
void loop() {
  /* 1) Server polling data from server every 1500 ms
     2) Arduino always get local data
  */
    uint32_t cur_time = millis();
  if (cur_time - last_sent_time > 500) { //always update
    
    // uint32_t problem;
    // uint32_t level;
    // uint32_t room;
    // unit32_t timing;
    // uint32_t check_empty;
        server_data.problem = getAndPrint("problem");
        server_data.level = getAndPrint("level");
        server_data.room = getAndPrint("room");
        server_data.check_empty = getAndPrint("check_empty");
    // Serial.print("GET");
    // GET(get_builder("buapalm-openair").c_str(), get_request,server_data.is_button_pressed);
    // GET(get_builder("buapalm-is_button_pressed").c_str(), get_request,server_data.is_button_pressed);
    // Serial.print("is_button_pressed : ");
    // Serial.println(server_data.is_button_pressed);
    // GET(get_builder("buapalm-light_lux").c_str(), get_request,server_data.light_lux);
    // Serial.print("light_lux : ");
    // Serial.println(server_data.light_lux);
    // GET(get_builder("buapalm-door").c_str(), get_request,server_data.door);
    // Serial.print("door : ");
    // Serial.println(server_data.door);
    // //float variable
    // GET(get_builder("buapalm-temp").c_str(), get_request,server_data.temp); 
    // Serial.print("temp : ");
    // Serial.println(server_data.temp);
    // GET(get_builder("buapalm-humi").c_str(), get_request,server_data.humi); 
    // Serial.print("humi : ");
    // Serial.println(server_data.humi);
    // GET(get_builder("buapalm-sound").c_str(), get_request,server_data.sound); 
    // Serial.print("sound : ");
    // Serial.println(server_data.sound);
    // GET("http://ecourse.cpe.ku.th:1515/api/exceed-plus/view/", get_request,server_data.plus); 
    // Serial.print("plus : ");
    // Serial.println(server_data.plus);


    last_sent_time = cur_time;
  }

  while (se_read.available()) {
    char ch = se_read.read();
    //Serial.print("RECV: ");0
    //Serial.println((byte)ch);
    if (cur_buffer_length == -1) {
      cur_data_header = ch;
      switch (cur_data_header) {
        case UPDATE_PROJECT_DATA:
          expected_data_size = sizeof(ProjectData);
          cur_buffer_length = 0;
          break;
        case GET_SERVER_DATA:
          expected_data_size = sizeof(ServerData);
          cur_buffer_length = 0;
          break;
      }
    } else if (cur_buffer_length < expected_data_size) {
      buffer[cur_buffer_length++] = ch;
      if (cur_buffer_length == expected_data_size) {
        switch (cur_data_header) {
          case UPDATE_PROJECT_DATA: {
              ProjectData *project_data = (ProjectData*)buffer;
              //depend on what your data is int32_t var = project_data->var;
              //POST(...)
                    uint32_t problem  = project_data->problem;
                    
                    postAndPrint(problem);

                    Serial.print("POST >> Problem : ");
                    Serial.println(problem);
                    POST(set_builder("buapalm-problem", problem).c_str(), update_data_to_server_callback); 
                    // float temp = project_data->temp;
                    // int32_t light_lux = project_data->light_lux;
                    // int32_t is_button_pressed = project_data->is_button_pressed;
                    // float sound = project_data->sound;
                    // int32_t door = project_data->door;
                    // float humi = project_data->humi;
                    // int32_t openair = project_data->openair; 
                    // Serial.println("POSTTTTTTTTTTTTTTTTTTTTT");
                    // Serial.print("Temp : ");
                    // Serial.println(temp);
                    // Serial.print("light_lux : ");
                    // Serial.println(light_lux);
                    // Serial.print("is_button_pressed : ");
                    // Serial.println(is_button_pressed);
                    // Serial.print("sound : ");
                    // Serial.println(sound);
                    // Serial.print("door : ");
                    // Serial.println(door);
                    // Serial.print("openair : ");
                    // Serial.println(openair);
                    POST(set_builder("buapalm-humi", humi).c_str(), update_data_to_server_callback);
                    POST(set_builder("buapalm-temp", temp).c_str(), update_data_to_server_callback);
//                    delay(100);
//                    POST(set_builder("buapalm-light_lux", light_lux).c_str(), update_data_to_server_callback);
                    POST(set_builder("buapalm-is_button_pressed", is_button_pressed).c_str(), update_data_to_server_callback);
                    // delay(100);
                    POST(set_builder("buapalm-sound", sound).c_str(), update_data_to_server_callback);
                    POST(set_builder("buapalm-door", door).c_str(), update_data_to_server_callback); 
                    POST(set_builder("buapalm-openair", openair).c_str(), update_data_to_server_callback); 
                       
                    delay(100);
            }
            break;
          case GET_SERVER_DATA:
            send_to_arduino(GET_SERVER_DATA_RESULT, &server_data, sizeof(ServerData));
            break;
        }
        cur_buffer_length = -1;
      }
    }
  }
}
