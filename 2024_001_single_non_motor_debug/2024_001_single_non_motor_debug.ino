#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX에 핀 2, 3을 할당

void setup() {
  Serial.begin(9600);         // 기본 시리얼 모니터
  mySerial.begin(9600);       // 가상 시리얼 포트
}

void loop() {
  if (mySerial.available()) { // 가상 포트로부터 데이터가 들어오면
    int receivedData = mySerial.read(); // 1바이트를 읽음
    // Serial.print("Received data: ");
    Serial.println(receivedData); // 바이트 값을 그대로 출력
  }
}
