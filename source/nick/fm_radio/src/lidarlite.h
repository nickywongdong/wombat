// lidarlite.h
// Interface for Lidar-Lite V2 (Blue Label) with NVIDIA Jetson TK1
// The MIT License (MIT)
// 
// Copyright (c) 2015 Jetsonhacks
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LIDARLITE_H
#define LIDARLITE_H

#include <cstddef>
//#include <i2c.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>
#include <thread>


//#include <bits/stdc++.h>


typedef int boolean;
#define true 1
#define false 0



#define BTNUP          2// used for seeking UP (normally CLOSED push button)
#define VOL_POT        A0// volume POT LOG taper 10K
#define BTNDN          3// used for seeking DOWN (normally CLOSED push button)

uint16_t gChipID = 0;
uint8_t RDA5807P_REGW[10];

#define kLidarLiteI2CAddress       0x60

#define READ            1
#define WRITE           0

#define ADRW            0x20
#define ADRR            0x21
//

//#define                 _SHARE_CRYSTAL_24MHz_
//#define                 _SHARE_CRYSTAL_12MHz_
#define                 _SHARE_CRYSTAL_32KHz_
//#define                 _FM_STEP_50K_

//5807M,5807FP,5807NN,5807NP
uint8_t RDA5807N_initialization_reg[]={
#if defined(_SHARE_CRYSTAL_24MHz_)
  0xC4, 0x51, //02H:
#elif defined(_SHARE_CRYSTAL_12MHz_)
  0xC4, 0x11, //02H:
#elif defined(_SHARE_CRYSTAL_32KHz_)
  0xC4, 0x01,//change 01 to 05 enables the RDS/RBDS
#else
  0xC0, 0x01,
#endif
  0x00, 0x00,
  0x04, 0x00,
  0xC3, 0xad,  //05h
  0x60, 0x00,
  0x42, 0x12,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,  //0x0ah
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,  //0x10h
  0x00, 0x19,
  0x2a, 0x11,
  0xB0, 0x42,
  0x2A, 0x11,  //
  0xb8, 0x31,  //0x15h
  0xc0, 0x00,
  0x2a, 0x91,
  0x94, 0x00,
  0x00, 0xa8,
  0xc4, 0x00,  //0x1ah
  0xF7, 0xcF,
  0x12, 0x14,  //0x1ch
  0x80, 0x6F,
  0x46, 0x08,
  0x00, 0x86,  //10000110
  0x06, 0x61,  //0x20H
  0x00, 0x00,
  0x10, 0x9E,
  0x23, 0xC8,
  0x04, 0x06,
  0x0E, 0x1C,  //0x25H     //0x04 0x08
};

int16_t freq = 10110;
uint16_t vol = 1;
//
// added items - Mel
boolean bassBit = true;// bass boost
boolean monoBit = false;// force MONO not stereo
const boolean seekUP = true;
const boolean seekDN = false;
uint8_t minSignalStrength = 36;// anything below this probably set a MONO flag for better reception
uint8_t signalStrength;
long previousMillis = 0;// last time the function was called
long interval = 2000;// interval for the signal level function (2 seconds)
int8_t stationStep = 10;// kHz steps bewteen the stations (North America = 10)
boolean hasVolumePot = false;// flag if you have a POT attached or not



void delay(int milliseconds);

/*// I2C Slave Address
#define kLidarLiteI2CAddress                    0x62

// Internal Control Registers 
#define kLidarLiteCommandControlRegister        0x00    // Command Control Register
#define kLidarLiteVelocityMeasurementOutput     0x09    // Velocity [Read Only]: in .1 meters/sec (8 bit signed value)
// High byte set means read two bytes
#define kLidarLiteCalculateDistanceMSB          0x8f    // Calculated distance in cm (difference between signal and reference delay)
                                                        // High byte of calculated delay of signal [Read Only]: reference – calculated after correlation record processing
                                                        // If the returned MSB is 1 then the reading is not considered valid.

#define kLidarLiteCalculateDistanceLSB          0x10    // Low byte of calculated delay of signal [Read Only]: reference – calculated after correlation record processing
#define kLidarLitePreviousMeasuredDistanceMSB   0x94    // Previous high byte of calculated delay of signal
#define kLidarLitePreviousMeasuredDistanceLSB   0x15    // Previous low byte of calculated delay of signal

// External Control Registers
#define kLidarLiteHardwareVersion               0x41    // Hardware Version: revisions begin with 0x01
#define kLidarLiteSoftwareVersion               0x4f    // Software Version: Revisions begin with 0x01

// Register Command
#define kLidarLiteMeasure                       0x04    // Take acquisition & correlation processing with DC correction
*/


//===========================================================
// FM functions
//===========================================================
unsigned char OperationRDAFM_2w(unsigned char operation, unsigned char *data, int numBytes)
{
  if(operation == READ)
  {
    Wire.requestFrom(kLidarLiteI2CAddress, numBytes);
    for(int i=0;i<numBytes;i++)
    {
      *data++ = Wire.read();
    }
  }
  else
  {
    Wire.beginTransmission(kLidarLiteI2CAddress);
    for(int i=0;i<numBytes;i++)
    {
      Wire.write(*data++);
    }
    Wire.endTransmission();
  }
  return 0;
}


void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

/**
 * @brief Get the signal level(RSSI) of the current frequency
 * @author RDA Ri'an Zeng
 * @date 2008-11-05
 * @param int16_t curf:frequency value
 * @return uint8_t: the signal level(RSSI)
 * @retval
 */
uint8_t RDA5807P_GetSigLvl( int16_t curf )
{
  uint8_t RDA5807P_reg_data[4]={
    0                                                  };
  OperationRDAFM_2w(READ,&(RDA5807P_reg_data[0]), 4);
  //delay(50);    //Delay 50 ms
  return  (RDA5807P_reg_data[2]>>1);  /*??rssi*/
}


class LidarLite
{
public:
    unsigned char kI2CBus ;         // I2C bus of the Lidar-Lite
    int kI2CFileDescriptor ;        // File Descriptor to the Lidar-Lite
    int error ;
    LidarLite();
    ~LidarLite() ;
    bool openLidarLite() ;                   // Open the I2C bus to the Lidar-Lite
    void closeLidarLite();                   // Close the I2C bus to the Lidar-Lite
    int writeLidarLite(int writeRegister,int writeValue) ;
    int readLidarLite(int readRegister) ;
    //taken from arduino sketch:
    void showSignalStrength();
    //int getDistance() ;
    //int getPreviousDistance() ;
    //int getVelocity() ;
    //int getHardwareVersion() ;
    //int getSoftwareVersion() ;
    int getError() ;

};

#endif // LIDARLITE_H
