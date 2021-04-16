#include <ESP8266WiFi.h>
#include <PubSubClient.h>//Library Description :https://pubsubclient.knolleary.net/api

// Update these with values suitable for your network.
const char* ssid =  "Orange-<Mario>_<Marco>";
const char* password = "$minanagy1993@gmail.com01229386627$M";
const char* broker_userName = "MinaNagy";
const char* broker_password = "MinaNagy1234";
const char* broker = "broker.emqx.io";
const char* topicPublish = "minanagy/out";
const char* topicSubscribe = "minanagy/in";
boolean ledState=HIGH;
// Initialize the client library
WiFiClient espClient;//Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().
PubSubClient client(espClient);
long currentTime,lastTime;
int count;
char messages[50];
void setup_wifi() {

  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");//endline
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length) {
   ledState=!ledState;
   digitalWrite(2,ledState);
   Serial.print("Message arrived in topic: ");
   Serial.println(topic);
   Serial.print("Message:");
   for (int i = 0; i < length; i++) {
       Serial.print((char) payload[i]);
   }
   Serial.println();
   Serial.println("-----------------------");
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("conncecting to .........");
    Serial.println(broker);
    if (client.connect("test2",broker_userName,broker_password)) {
      Serial.println("connected to");
       Serial.println(broker);
    } else {
     /* Serial.print("failed, rc=");
      Serial.print(client.state());*/
      Serial.println(" try again in 5 seconds");
      delay(5000);// Wait 5 seconds before retrying
    }
  }
}

void setup() {
  pinMode(2,OUTPUT);
  digitalWrite(2,ledState);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(broker,1883);//BrokerName,Port
  client.setCallback(callback);

}
void loop() {
    if(!client.connected()){
      reconnect();
    }
    client.loop();
    currentTime=millis();
    if(currentTime-lastTime>2000){
      count++;
      snprintf(messages,75,"Count : %ld",count);
      Serial.print("Sending Messages .....");
      Serial.println(messages);
      client.publish(topicPublish,messages);
      lastTime=millis();
    }
     //client.subscribe(topicSubscribe);
     client.subscribe("minanagy/test");

    
}

/*
// Library for Connect Wifi & Connect Broker


*/