/*
  This example demonstrates how to read the raw voltage from the ADS122C04 AIN1 and AIN0 pins.

  The function readRawVoltage:
  - disables the IDAC current source
  - sets the gain to 1
  - configures the chip to use the internal 2.048V reference

  readRawVoltage returns a int32_t. The LSB is 2.048 / 2^23 = 0.24414 uV (0.24414 microvolts).

  If you want to configure the chip manually, see Example_ManualConfig.

*/

#include <Wire.h>

#include <SparkFun_ADS122C04_ADC_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_ADS122C0
SFE_ADS122C04 mySensor;

void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  //Serial.println(F("Qwiic PT100 Example"));
  Wire.begin();

  //mySensor.enableDebugging(); //Uncomment this line to enable debug messages on Serial

  if (mySensor.begin() == false) //Connect to the PT100 using the defaults: Address 0x45 and the Wire port
  {
    //Serial.println(F("Qwiic PT100 not detected at default I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }

 //RAW MODE
 //GAIN 128
 //DATA RATE 2000SPS
   mySensor.setInputMultiplexer(ADS122C04_MUX_AIN1_AIN0); // Route AIN1 and AIN0 to AINP and AINN
  mySensor.setGain(ADS122C04_GAIN_128); // Set the gain to 1
  mySensor.enablePGA(ADS122C04_PGA_ENABLED); // Disable the Programmable Gain Amplifier
  mySensor.setDataRate(ADS122C04_DATA_RATE_1000SPS); // Set the data rate (samples per second) to 20
  mySensor.setOperatingMode(ADS122C04_OP_MODE_TURBO); // Disable turbo mode
  mySensor.setConversionMode(ADS122C04_CONVERSION_MODE_CONTINUOUS); // Use single shot mode
  mySensor.setVoltageReference(ADS122C04_VREF_INTERNAL); // Use the internal 2.048V reference
  mySensor.enableInternalTempSensor(ADS122C04_TEMP_SENSOR_OFF); // Disable the temperature sensor
  mySensor.setDataCounter(ADS122C04_DCNT_DISABLE); // Disable the data counter (Note: the library does not currently support the data count)
  mySensor.setDataIntegrityCheck(ADS122C04_CRC_DISABLED); // Disable CRC checking (Note: the library does not currently support data integrity checking)
  mySensor.setBurnOutCurrent(ADS122C04_BURN_OUT_CURRENT_OFF); // Disable the burn-out current
  mySensor.setIDACcurrent(ADS122C04_IDAC_CURRENT_OFF); // Disable the IDAC current
  mySensor.setIDAC1mux(ADS122C04_IDAC1_DISABLED); // Disable IDAC1
  mySensor.setIDAC2mux(ADS122C04_IDAC2_DISABLED); // Disable IDAC2
mySensor.start();
}

void loop()
{
 
  // Get the raw voltage as int32_t
 // int raw_voltage = mySensor.readRawVoltage();
  int raw_ADC_data=0;
  static int printDivider = 10;
  // Convert to Volts (method 1)
  //float volts_1 = ((float)raw_v) ;


  raw_ADC_data = mySensor.readADC();
    // Pad the zeros
  if(--printDivider <= 0)
  {
    if (raw_ADC_data <= 0xFFFFF) Serial.print(F("0"));
    if (raw_ADC_data <= 0xFFFF) Serial.print(F("0"));
    if (raw_ADC_data <= 0xFFF) Serial.print(F("0"));
    if (raw_ADC_data <= 0xFF) Serial.print(F("0"));
    if (raw_ADC_data <= 0xF) Serial.print(F("0"));
    Serial.println(raw_ADC_data);
    printDivider = 10;
  }
  //Serial.print(F("V\t"));
  //Serial.print(volts_2, 7); // Print the voltage with 7 decimal places
  //Serial.println(F("V"));

  //delay(10); //Don't pound the I2C bus too hard
}
