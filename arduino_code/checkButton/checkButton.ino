/* 4-Way Button:  Click, Double-Click, Press+Hold, and Press+Long-Hold Test Sketch

By Jeff Saltzman
Oct. 13, 2009

To keep a physical interface as simple as possible, this sketch demonstrates generating four output events from a single push-button.
1) Click:  rapid press and release
2) Double-Click:  two clicks in quick succession
3) Press and Hold:  holding the button down
4) Long Press and Hold:  holding the button for a long time
*/

#define buttonPin 2        // analog input pin to use as a digital input
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Zion";
const char* password =  "ZionStage";
const char* server_address = "http://192.168.43.34:1337/api/alerts/";

//=================================================

void setup() {
   Serial.begin(115200);
   // Set button input pin
   pinMode(buttonPin, INPUT);
   digitalWrite(buttonPin, HIGH );

   Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  IPAddress ip = WiFi.localIP();
   Serial.println(ip);
}

//=================================================
// Events to trigger

void clickEvent() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  HTTPClient http;   
 
   http.begin(server_address);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header

   String postdata = "{\"alert\" : { \"username\" : \"Jean\" }}";
   int httpResponseCode = http.POST(postdata);   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
    }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 Serial.println("click");
  //delay(1000);  //Send a request every 10 seconds
}
   

void doubleClickEvent() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  HTTPClient http;   
 
   http.begin(server_address);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header

   String postdata = "{\"alert\" : { \"username\" : \"Jean\" }}";
   int httpResponseCode = http.POST(postdata);   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
   Serial.println("double click");
  //delay(1000);  //Send a request every 10 seconds
}


void holdEvent() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  HTTPClient http;   
 
   http.begin(server_address);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header

   String postdata = "{\"alert\" : { \"username\" : \"Jean\" }}";
   int httpResponseCode = http.POST(postdata);   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
   Serial.println("hold");
  //delay(1000);  //Send a request every 10 seconds
}
void longHoldEvent() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  HTTPClient http;   
 
   http.begin(server_address);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header

   String postdata = "{\"alert\" : { \"username\" : \"Jean\" }}";
   int httpResponseCode = http.POST(postdata);   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
   Serial.println("long hold");
}

//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 3000;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

int checkButton() {    
   int event = 0;
   buttonVal = digitalRead(buttonPin);
   // Button pressed down
   if (buttonVal == HIGH && buttonLast == LOW && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;
       longHoldEventPast = false;
       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button released
   else if (buttonVal == LOW && buttonLast == HIGH && (millis() - downTime) > debounce)
   {        
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 2;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == LOW && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 1;
       DCwaiting = false;
   }
   // Test for hold
   if (buttonVal == HIGH && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           event = 3;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           //downTime = millis();
           holdEventPast = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime) >= longHoldTime)
       {
           if (not longHoldEventPast)
           {
               event = 4;
               longHoldEventPast = true;
           }
       }
   }
   buttonLast = buttonVal;
   return event;
}

void loop() {
   // Get button event and act accordingly
   int b = checkButton();
   if (b == 1) clickEvent();
   if (b == 2) doubleClickEvent();
   if (b == 3) holdEvent();
   if (b == 4) longHoldEvent();
   

   
   
 
  delay(1000);  //Send a request every 1 seconds
}
