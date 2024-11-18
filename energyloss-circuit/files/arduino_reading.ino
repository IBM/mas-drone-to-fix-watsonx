#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      delay(1);
  }

  auto connected = false;
  while (!connected) {
    if (ina219.begin()) {
      connected = true;
    }
    Serial.println("Connecting...");
    delay(1000);
  }
  
  ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntVoltage = ina219.getShuntVoltage_mV();
  float busVoltage = ina219.getBusVoltage_V(); 
  float current = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();
  float voltage = busVoltage + (shuntVoltage / 1000);

  Serial.print(1); Serial.print(',');
  Serial.print(shuntVoltage); Serial.print(',');
  Serial.print(busVoltage);Serial.print(',');
  Serial.print(voltage);Serial.print(',');
  Serial.print(current);Serial.print(',');
  Serial.print(power_mW);Serial.print(',');
  Serial.println("");

  delay(1000);

}


float* getReadings(Adafruit_INA219 ina219) {
  static float output[6];

  float shuntVoltage = ina219.getShuntVoltage_mV();
  float busVoltage = ina219.getBusVoltage_V(); 
  float current = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();
  output[0] = 0;
  output[1] = shuntVoltage;
  output[2] = busVoltage;
  output[3] = busVoltage + (shuntVoltage / 1000);
  output[4] = current ;
  output[5] = power_mW;

  return output;
} 

// Send data to Serial port using below format:
// <solarPanelNumber>,<shuntVoltage>,<busVoltage>,<loadVoltage>,<Current>,<Power>\n
void printReadings( float vals[]) {
    Serial.print(vals[0]); Serial.print(',');
    Serial.print(vals[1]);Serial.print(',');
    Serial.print(vals[2]);Serial.print(',');
    Serial.print(vals[3]);Serial.print(',');
    Serial.print(vals[4]);Serial.print(',');
    Serial.println(vals[5]);
}
