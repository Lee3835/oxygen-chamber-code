

#include <DFRobot_EOxygenSensor.h>
#include <DHT.h>
unsigned long time;

// DHT11 센서에 대한 핀 정의
#define DHTPIN 2     // DHT11 센서의 데이터 핀
#define DHTTYPE DHT11 // DHT11 센서 사용

DHT dht(DHTPIN, DHTTYPE);

// 솔레노이드 밸브 및 리니어 액추에이터에 대한 핀 정의
const int Relay1 = 9;  // 액추에이터 동작을 위한 릴레이 핀
const int Relay2 = 8;  // 액추에이터 원상 복구를 위한 릴레이 핀

// 산소 센서에 대한 설정
#define OXYGEN_I2C_ADDRESS E_OXYGEN_ADDRESS_0
DFRobot_EOxygenSensor_I2C oxygen(&Wire, OXYGEN_I2C_ADDRESS);

void setup()
{
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
  {
    delay(1000);
  }

  // 온습도 센서 초기화
  dht.begin();

  // 산소 센서 초기화
  while (!oxygen.begin())
  {
    Serial.println("NO Devices!");
    delay(1000);
  }
  Serial.println("Devices connected successfully!");
}

void loop()
{
  // 산소 농도 측정
  float oxygenConcentration = oxygen.readOxygenConcentration();

  // 온습도 측정
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Time: ");
  time = millis();

  Serial.println(time); // 프로그램 시작후 지난 시간 출력
  Serial.print("Oxygen concentration: ");
  Serial.print(oxygenConcentration);
  Serial.println("% VOL");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  delay(1000);

  // DHT 모니터 자리



  if (oxygenConcentration < 85)
  {
    // 산소 농도가 85 미만인 경우
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, HIGH);
    delay(1400);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay1, HIGH);
    delay(1400);
  }
  else
  {
    // 산소 농도가 85 이상인 경우
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay1, HIGH);
    delay(1000);
  }
}
