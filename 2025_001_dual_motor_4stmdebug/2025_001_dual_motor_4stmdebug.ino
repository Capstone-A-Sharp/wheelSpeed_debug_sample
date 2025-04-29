#include <SoftwareSerial.h>

// 소프트웨어 시리얼 핀 설정 (디버깅용)
#define DEBUG_RX 8
#define DEBUG_TX 9
SoftwareSerial DebugSerial(DEBUG_RX, DEBUG_TX);

// 9bit 데이터를 저장할 변수
unsigned int received9bitData = 0;

void setup() {
  // 디버깅용 소프트웨어 시리얼 시작 (8bit, 9600bps)
  DebugSerial.begin(9600);
  // DebugSerial.println("Debug Serial Ready");

  // 하드웨어 UART 시작 (9bit 모드로 설정)
  Serial.begin(9600);  // 기본 8bit로 시작
  UCSR0B |= (1 << UCSZ02); // UCSZ02=1로 9bit 모드 활성화 (UCSR0C는 기본 UCSZ01=1, UCSZ00=1)

  // DebugSerial.println("Hardware UART (9bit) Ready");
}

void loop() {
  // 하드웨어 UART에서 9bit 데이터 수신
  if (UCSR0A & (1 << RXC0)) { // 데이터 수신 완료되었는지 확인
    uint8_t ninthBit = (UCSR0B & (1 << RXB80)) ? 1 : 0; // 9번째 비트 읽기
    uint8_t lowByte = UDR0; // 수신된 8bit 데이터 읽기

    // 9bit 통합하여 16bit unsigned int로 저장
    received9bitData = (static_cast<uint16_t>(ninthBit) << 8) | lowByte;

    // 디버깅용 출력
    // DebugSerial.print("R: 0b");
    // for (int i = 8; i >= 0; i--) {
    //   DebugSerial.print((received9bitData >> i) & 1);
    // }
    // DebugSerial.println();
    // DebugSerial.print(" (");
    DebugSerial.println(received9bitData);
    // DebugSerial.println(")");
  }
}