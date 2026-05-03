#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// these are pins given on the xiao for the camera -- built-in basically from the interwebs

#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39

#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    11
#define Y7_GPIO_NUM    12
#define Y6_GPIO_NUM    14
#define Y5_GPIO_NUM    16
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    17
#define Y2_GPIO_NUM    15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

//start websocket to share feed
WebServer server(80);
camera_config_t config;

void handleCamera() {
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;
  config.fb_location  = CAMERA_FB_IN_PSRAM;

}

void handleStream() {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "multipart/x-mixed-replace; boundary=frame", "");

    char header[64];

    while (true) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) continue;

        snprintf(header, sizeof(header),
            "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n",
            fb->len);

        server.sendContent(header);
        server.sendContent((char*)fb->buf, fb->len);
        server.sendContent("\r\n");

        esp_camera_fb_return(fb);
        delay(33);
    }
}

void setup() {
  Serial.begin(115200);   

  //remember to change before committing
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.disconnect();
  delay(1000);  // longer delay
  WiFi.begin("Daddy iPhone", "Nguyen2941");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 60) {
      delay(1000);  // longer between attempts
      attempts++;
      Serial.print("Attempt ");
      Serial.print(attempts);
      Serial.print(" status: ");
      Serial.println(WiFi.status());
  }

  Serial.println(WiFi.localIP());
  server.on("/",handleStream);
  server.begin();

  handleCamera();

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("camera doesnt start");
    return;
  } 
  Serial.println("camera success");
}

void loop() {
  server.handleClient();
}

