#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include "index.h"

const char* WiFissid = "SSID";
const char* WiFiPassword = "PASSWORD";
const int WebServerPort = PORT;
const int WebSocketsPort = PORT;

ESP8266WebServer WebServer(WebServerPort);
WebSocketsServer SocketsServer(WebSocketsPort);

String User = "Not Changed";
String UserTime = "Not Changed";
String Mode = "StaticColor";
String ModeDescription = "";
bool MusicMode = true;

float AnimationDelay = 12.5;

const int RedPin = 13;
const int GreenPin = 12;
const int BluePin = 14; 

const int Resolution = 256;
int RedValue = 255;
int GreenValue = 255;
int BlueValue = 255;

int TargetRedValue = 0;
int TargetGreenValue = 0;
int TargetBlueValue = 0;

int LastPredominantColor = 0; // 0 = Red, 1 = Green, 2 = Blue
long AnimationTimeStart;

/* Color and Animation Functions */

void UpdateColors()
{
  analogWrite(RedPin, RedValue);
  analogWrite(GreenPin, GreenValue);
  analogWrite(BluePin, BlueValue);
}

void GenerateTargetValues()
{
  if(Mode == "Fade")
  {
    int NewPredominantColor = random(0, 2);
  
    if(LastPredominantColor == 0)
    {
      if(NewPredominantColor == 0)
      {
        LastPredominantColor = 1;
      }
      else
      {
        LastPredominantColor = 2;
      }
    }
    else if (LastPredominantColor == 1)
    {
      if(NewPredominantColor == 0)
      {
        LastPredominantColor = 0;
      }
      else
      {
        LastPredominantColor = 2;
      }
    }
    else
    {
      if(NewPredominantColor == 0)
      {
        LastPredominantColor = 0;
      }
      else
      {
        LastPredominantColor = 1;
      }
    }
 
    if(LastPredominantColor == 0)
    {
      TargetRedValue = 255;
  
      if(random(0, 2) == 0)
      {
        TargetGreenValue = random(50, 200);
        TargetBlueValue = random(0, 120);
      }
      else
      {
        TargetBlueValue = random(100, 220);
        TargetGreenValue = random(0, 120);
      }
    }
    else if(LastPredominantColor == 1)
    {
      TargetGreenValue = 255;
  
      if(random(0, 2) == 0)
      {
        TargetRedValue = random(50, 200);
        TargetBlueValue = random(0, 120);
      }
      else
      {
        TargetBlueValue = random(50, 200);
        TargetRedValue = random(0, 120);
      }
    }
    else
    {
      TargetBlueValue = 255;
  
      if(random(0, 2) == 0)
      {
        TargetRedValue = random(50, 200);
        TargetGreenValue = random(0, 120);
      }
      else
      {
        TargetGreenValue = random(50, 200);
        TargetRedValue = random(0, 120);
      }
    }
  }
  else if(Mode == "Romantic")
  {
    TargetRedValue = random(50, 256);

    if(random(0, 2) == 0)
    {
      TargetBlueValue = random(0, TargetRedValue);
    }
    else
    {
      TargetBlueValue = 0;
    }
    TargetGreenValue = 0;
  }
}

void Fade()
{
  if(millis() - AnimationTimeStart >= AnimationDelay)
  {
    AnimationTimeStart = millis();

    if(TargetRedValue > RedValue)
    {
      RedValue++;
    }
    else if(TargetRedValue < RedValue)
    {
      RedValue--;
    }

    if(TargetGreenValue > GreenValue)
    {
      GreenValue++;
    }
    else if(TargetGreenValue < GreenValue)
    {
      GreenValue--;
    }

    if(TargetBlueValue > BlueValue)
    {
      BlueValue++;
    }
    else if(TargetBlueValue < BlueValue)
    {
      BlueValue--;
    }

    UpdateColors();
       
    if(RedValue == TargetRedValue and GreenValue == TargetGreenValue and BlueValue == TargetBlueValue)
    {
      GenerateTargetValues();
      AnimationTimeStart = millis();
    }
  }
}

/* Update client data */

void UpdateClient(uint8_t num, bool UpdateUserInfo, bool UpdateModeInfo)
{
  if(UpdateUserInfo == true)
  {
    StaticJsonDocument<400> UserJSON;

    UserJSON["DataType"] = "UserInfo";
    UserJSON["User"] = User;
    UserJSON["UserTime"] = UserTime;

    String UserData;
    serializeJson(UserJSON, UserData);
    SocketsServer.sendTXT(num, UserData);
  }

  if(UpdateModeInfo == true)
  {
    StaticJsonDocument<400> ModeJSON;

    ModeJSON["DataType"] = "ModeInfo";
    ModeJSON["Mode"] = Mode;
    ModeJSON["ModeDescription"] = ModeDescription;
    ModeJSON["ModeDelay"] = AnimationDelay;
    ModeJSON["MusicMode"] = MusicMode; 
    
    String ModeData;
    serializeJson(ModeJSON, ModeData);
    SocketsServer.sendTXT(num, ModeData);
  }
}

/* Serve Web Page */

void ServeMainPage()
{
  WebServer.send(200, "text/html", MainPage);
}

/* Web Sockets Get Input */

void WebSocketsGetData(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  if(type == WStype_CONNECTED)
  {
    Serial.println("Client Connected");

    /* Send Init Data */
    StaticJsonDocument<400> InitJSON;

    InitJSON["DataType"] = "Init";
    InitJSON["User"] = User;
    InitJSON["UserTime"] = UserTime;
    InitJSON["RedValue"] = RedValue;
    InitJSON["GreenValue"] = GreenValue;
    InitJSON["BlueValue"] = BlueValue;
    InitJSON["Mode"] = Mode;
    InitJSON["ModeDescription"] = ModeDescription;
    InitJSON["ModeDelay"] = AnimationDelay;
    InitJSON["MusicMode"] = MusicMode;
    
    String InitData;
    serializeJson(InitJSON, InitData);
    SocketsServer.sendTXT(num, InitData);
  }
  else if(type == WStype_TEXT)
  {
    String Payload = String((char *) &payload[0]);

    StaticJsonDocument<400> ClientJSON;
    DeserializationError Error = deserializeJson(ClientJSON, Payload);
    
    if(Error) 
    {
      Serial.print("JSON Error");
      Serial.println(Error.f_str());
      return;
    }

    if(ClientJSON["Password"] == "ratustelefantastice")
    {
      User = (const char*)ClientJSON["User"];
      UserTime = (const char*)ClientJSON["UserTime"];
      UpdateClient(num, true, false); // a se inlocui tu toti userii conectati nu numai num

      if(Mode != ClientJSON["Mode"] or AnimationDelay != ClientJSON["ModeDelay"])
      {
        if(ClientJSON["Mode"] == "MusicToggle")
        {
          MusicMode = ClientJSON["State"];
          ModeDescription = " Music state: " + String(MusicMode);
          UpdateClient(num, false, true);
          return;
        }
        
        Mode = (const char*)ClientJSON["Mode"];
        AnimationDelay = ClientJSON["Delay"];
        
        if(Mode == "StaticColor")
        {
          RedValue = ClientJSON["RedValue"];
          GreenValue = ClientJSON["GreenValue"];
          BlueValue = ClientJSON["BlueValue"];

          ModeDescription = "";
          UpdateColors();  
        }
        if(Mode == "Fade" or Mode == "Romantic")
        {
          if(AnimationDelay < 4)
          {
            ModeDescription = "with delay of " + String(AnimationDelay) + "ms (very fast)";  
          }
          else if(AnimationDelay < 7.5)
          {
            ModeDescription = "with delay of " + String(AnimationDelay) + "ms (fast)";  
          }
          else if(AnimationDelay < 12)
          {
            ModeDescription = "with delay of " + String(AnimationDelay) + "ms (medium)";  
          }
          else if(AnimationDelay < 20)
          {
            ModeDescription = "with delay of " + String(AnimationDelay) + "ms (slow)";  
          }
          else
          {
            ModeDescription = "with delay of " + String(AnimationDelay) + "ms (very slow)";  
          }

          GenerateTargetValues();
          AnimationTimeStart = millis();
        }
        
        UpdateClient(num, false, true);
      }
    }
  }
  else if(type == WStype_DISCONNECTED)
  {
    Serial.println("Client disconnected");
  }
}

/* Setup */

void setup() 
{
  /* Map Pins and Set Default Color */
  analogWriteRange(Resolution);
  UpdateColors();
  
  /* Start Serial */
  Serial.begin(9600);

  /* Connect to WiFi */
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFissid, WiFiPassword);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }

  Serial.println(WiFi.localIP());

  /* Start and Config Web Server */
  WebServer.on("/password=PASSWORD&user=USER0", ServeMainPage);
  WebServer.on("/password=PASSWORD&user=USER1", ServeMainPage);
  WebServer.begin();

  /* Start and Config Web Sockets Server */
  SocketsServer.begin(); 
  SocketsServer.onEvent(WebSocketsGetData); 
}

void loop()
{
  WebServer.handleClient();
  SocketsServer.loop();
  
  if(Mode == "Fade" or Mode == "Romantic")
  {
    Fade();
  }
}
