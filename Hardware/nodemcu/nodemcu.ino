#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EspSoftwareSerial.h>
#include <math.h>

SoftwareSerial se_read(D5, D6); // write only
SoftwareSerial se_write(D0, D1); // read only

struct ProjectData {
    int32_t problem;
    int32_t level;
    int32_t room;
    int32_t sos_level; 
    int32_t sos_room;
    // unit32_t timing;
    // uint32_t check_empty;

    
} project_data = {0,2,1,0,0};

struct ServerData {
    int32_t problem;
    int32_t level;
    int32_t room;
    int32_t sos_level;
    int32_t sos_room;
    // unit32_t timing;
    // uint32_t check_empty;
   
} server_data = {0,2,1,0,0};
String const url = "http://ecourse.cpe.ku.ac.th/exceed/api/";
const char GET_SERVER_DATA = 1;
const char GET_SERVER_DATA_RESULT = 2;
const char UPDATE_PROJECT_DATA = 3;

// wifi configuration
const char SSID[] = "EXCEED_RIGHT_1_2.4GHz"; //CHUT
const char PASSWORD[] = "1234567890"; //*123*abc

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


// uint32_t getAndPrint(String var_get){
//     uint32_t tmp;
//     String txt_buildpar = "buapalm" + var_get;
//     GET(get_builder(&txt_buildpar).c_str(), get_request, tmp); // tmp = GET
//     Serial.print("GET <<  " + var_get + " : ");
//     Serial.println(tmp);
//     return tmp;
// }

// uint32_t postAndPrint(uint32_t var_post){
//     Serial.print("POST >> Problem : ");
//     Serial.println(var_post);
//     POST(set_builder("buapalm-" + (String)var_post, var_post).c_str(), update_data_to_server_callback) 
// }

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
    // unit32_t sos_level;
    // uint32_t sos_room;
    // uint32_t timing;
    // uint32_t check_empty;

        // server_data.problem = getAndPrint("problem");
        // server_data.level = getAndPrint("level");
        // server_data.room = getAndPrint("room");
        // server_data.check_empty = getAndPrint("check_empty");
//
//        GET(get_builder("buapalm-problem").c_str(), get_request,server_data.problem);
//        Serial.print("GET << problem : ");
//        Serial.println(server_data.problem);

        // GET(get_builder("buapalm-level").c_str(), get_request,server_data.level);
        // Serial.print("GET << level : ");
        // Serial.println(server_data.level);

        // GET(get_builder("buapalm-room").c_str(), get_request,server_data.room);
        // Serial.print("GET << room : ");
        // Serial.println(server_data.room);

        // GET(get_builder("buapalm-check_empty").c_str(), get_request,server_data.check_empty);
        // Serial.print("GET << check_empty : ");
        // Serial.println(server_data.check_empty);

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
                  // uint32_t problem;
                  // uint32_t level;
                  // uint32_t room;
                  // unit32_t timing;
                  // uint32_t check_empty;
                    int32_t problem  = project_data->problem;
                    int32_t level  = project_data->level;
                    int32_t room  = project_data->room;
                    int32_t sos_level = project_data->sos_level;
                    int32_t sos_room = project_data->sos_room;
//                    int32_t check_empty  = project_data->check_empty;

                    // postAndPrint(problem);
                    // postAndPrint(level);
                    // postAndPrint(room);
                    // postAndPrint(check_empty);

                    Serial.print("POST >> problem : ");
                    Serial.println(problem);
                    POST(set_builder("buapalm-problem", problem).c_str(), update_data_to_server_callback); 

                    Serial.print("POST >> level : ");
                    Serial.println(level);
                    POST(set_builder("buapalm-level", level).c_str(), update_data_to_server_callback); 

                    Serial.print("POST >> room : ");
                    Serial.println(room);
                    POST(set_builder("buapalm-room", room).c_str(), update_data_to_server_callback); 

                    Serial.print("POST >> sos_level : ");
                    Serial.println(sos_level);
                    POST(set_builder("buapalm-sos_level", sos_level).c_str(), update_data_to_server_callback); 
                    
                    Serial.print("POST >> sos_room : ");
                    Serial.println(sos_room);
                    POST(set_builder("buapalm-sos_room", sos_room).c_str(), update_data_to_server_callback); 


                    // Serial.print("POST >> check_empty : ");
                    // Serial.println(check_empty);
                    // POST(set_builder("buapalm-check_empty", check_empty).c_str(), update_data_to_server_callback); 

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
