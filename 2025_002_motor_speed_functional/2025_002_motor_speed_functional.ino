#include <SoftwareSerial.h>

// SoftwareSerial 핀 설정
#define SW_RX 2  // 소프트웨어 시리얼 수신핀
#define SW_TX 3  // 소프트웨어 시리얼 송신핀 (여기선 사용 안함)
SoftwareSerial SoftSerial(SW_RX, SW_TX);

unsigned int bufferNum = 0;
unsigned int speedL = 0;
unsigned int speedR = 0;

void readWheelSpeed(){
  static String buffer = "";  // 수신된 문자열 임시 저장

  // 소프트웨어 시리얼에 수신 데이터가 있을 경우
  while (SoftSerial.available()) {
    char ch = SoftSerial.read();

    if (isDigit(ch)) {
      buffer += ch; // 숫자면 버퍼에 추가
    } else if (ch == '\n' || ch == '\r') {
      // 엔터(개행 문자)가 들어오면 문자열 → 숫자 변환
      if (buffer.length() > 0) {
        bufferNum = buffer.toInt(); // 정수로 변환
        
        if(bufferNum >> 8)speedR = bufferNum & 0xFF;
        else             {speedL = bufferNum & 0xFF;}

        buffer = ""; // 버퍼 초기화
      }
    } else {
      // 숫자도 아니고 엔터도 아니면 무시
    }
  }
}

void sendWheelSpeedDataAsJson(){
  Serial.print("\"Wheel_Speed\": {\"L\":");
  Serial.print(speedL);
  Serial.print(", \"R\":");
  Serial.print(speedR);
  Serial.println("}");
}

void setup() {
  Serial.begin(115200);
  SoftSerial.begin(9600);
}

void loop() {
  readWheelSpeed();
  sendWheelSpeedDataAsJson();
  delay(100);
}