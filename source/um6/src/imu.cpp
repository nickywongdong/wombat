/*--------------------------------------------------------------------
******************************************************************************
* @file imu.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
* @version V0.0.2
* @created 15/05/2014
* @Modified 24/08/2015
* @e-mail isaac25silva@yahoo.com.br
* @brief serial imu
****************************************************************************

Arquivo fonte contendo o programa que lê os dados da IMU via serial e escreve
na memória compartilhada os valores do girocópio, acelerometro e magnetômetro
estes valores são publicados na memoria a cada 5ms, ou seja, uma frequência de
200Hz


Para usar este processo deverá ser instalado o BOOST usando o comando abaixo

    sudo apt-get install libboost-all-dev

Para instalar o serial.h entrar na pasta serial, apagar a pasta build e executar os seguintes comandos:

mkdir build
cd build
cmake ..
make
sudo make install

/--------------------------------------------------------------------*/

/**
 *
 *  \file
 *  \brief      Main entry point for UM6 driver. Handles serial connection
 *              details, as well as all ROS message stuffing, parameters,
 *              topics, etc.
 *  \author     Mike Purvis <mpurvis@clearpathrobotics.com>
 *  \copyright  Copyright (c) 2013, Clearpath Robotics, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Clearpath Robotics, Inc. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CLEARPATH ROBOTICS, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Please send comments, questions, or patches to code@clearpathrobotics.com
 *
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <serial.h>
#include <comms.h>
#include <registers.h>
#include <cmath>
#include <unistd.h>

// variables for data logging
std::string loggingDirectory, filepath;
bool loggingDirectorySet = false;
std::ofstream ahrs_csv;

double accelz;

const uint8_t TRIGGER_PACKET = UM6_TEMPERATURE;

double IMU_GYRO_X, IMU_GYRO_Y, IMU_GYRO_Z, IMU_ACCEL_X, IMU_ACCEL_Y, IMU_ACCEL_Z, IMU_COMPASS_X, IMU_COMPASS_Y, IMU_COMPASS_Z, IMU_EULER_X, IMU_EULER_Y, IMU_EULER_Z, IMU_QUAT_X, IMU_QUAT_Y, IMU_QUAT_Z, IMU_STATE;

/**
 * Function generalizes the process of writing an XYZ vector into consecutive
 * fields in UM6 registers.
 */
template<typename RegT>
void configureVector3(um6::Comms* sensor, const um6::Accessor<RegT>& reg,
                      std::string param, std::string human_name)
{
  if (reg.length != 3)
  {
    throw std::logic_error("configureVector3 may only be used with 3-field registers!");
  }
}

/**
 * Function generalizes the process of commanding the UM6 via one of its command
 * registers.
 */
template<typename RegT>
void sendCommand(um6::Comms* sensor, const um6::Accessor<RegT>& reg, std::string human_name)
{
  std::cout<<"Sending command: " << human_name<<std::endl;
  if (!sensor->sendWaitAck(reg))
  {
    throw std::runtime_error("Command to device failed.");
  }
}


/**
 * Send configuration messages to the UM6, critically, to turn on the value outputs
 * which we require, and inject necessary configuration parameters.
 */
void configureSensor(um6::Comms* sensor)
{
  um6::Registers r;

  // Enable outputs we need.
  const uint8_t UM6_BAUD_115200 = 0x5;
  uint32_t comm_reg = UM6_BROADCAST_ENABLED |
                      UM6_GYROS_PROC_ENABLED | UM6_ACCELS_PROC_ENABLED | UM6_MAG_PROC_ENABLED |
                      UM6_QUAT_ENABLED | UM6_EULER_ENABLED | UM6_COV_ENABLED | UM6_TEMPERATURE_ENABLED |
                      UM6_BAUD_115200 << UM6_BAUD_START_BIT;
  r.communication.set(0, comm_reg);
  if (!sensor->sendWaitAck(r.communication))
  {
    throw std::runtime_error("Unable to set communication register.");
  }

  // Optionally disable mag and accel updates in the sensor's EKF.
  bool mag_updates, accel_updates;
  uint32_t misc_config_reg = UM6_QUAT_ESTIMATE_ENABLED;
  if (mag_updates)
  {
    misc_config_reg |= UM6_MAG_UPDATE_ENABLED;
  }
  else
  {
    std::cout<<"Excluding magnetometer updates from EKF."<<std::endl;
  }
  if (accel_updates)
  {
    misc_config_reg |= UM6_ACCEL_UPDATE_ENABLED;
  }
  else
  {
    std::cout<<"Excluding accelerometer updates from EKF."<<std::endl;
  }
  r.misc_config.set(0, misc_config_reg);
  if (!sensor->sendWaitAck(r.misc_config))
  {
    throw std::runtime_error("Unable to set misc config register.");
  }

  // Optionally disable the gyro reset on startup. A user might choose to do this
  // if there's an external process which can ascertain when the vehicle is stationary
  // and periodically call the /reset service.
  bool zero_gyros;
  if (zero_gyros) sendCommand(sensor, r.cmd_zero_gyros, "zero gyroscopes");

  // Configurable vectors.
  configureVector3(sensor, r.mag_ref, "~mag_ref", "magnetic reference vector");
  configureVector3(sensor, r.accel_ref, "~accel_ref", "accelerometer reference vector");
  configureVector3(sensor, r.mag_bias, "~mag_bias", "magnetic bias vector");
  configureVector3(sensor, r.accel_bias, "~accel_bias", "accelerometer bias vector");
  configureVector3(sensor, r.gyro_bias, "~gyro_bias", "gyroscope bias vector");
}


bool handleResetService(um6::Comms* sensor,
                        bool zero_gyros = true, bool reset_ekf = true,
                        bool set_mag_ref = true, bool set_accel_ref = true)
{
  um6::Registers r;
  if (zero_gyros) sendCommand(sensor, r.cmd_zero_gyros, "zero gyroscopes");
  if (reset_ekf) sendCommand(sensor, r.cmd_reset_ekf, "reset EKF");
  if (set_mag_ref) sendCommand(sensor, r.cmd_set_mag_ref, "set magnetometer reference");
  if (set_accel_ref) sendCommand(sensor, r.cmd_set_accel_ref, "set accelerometer reference");
  return true;
}

/**
 * Uses the register accessors to grab data from the IMU.
 */
//void publishMsgs(um6::Registers& r, ros::NodeHandle* n, const std_msgs::Header& header)
void publishMsgs(um6::Registers& r)
{
    IMU_GYRO_X = r.gyro.get_scaled(1);
    IMU_GYRO_Y = r.gyro.get_scaled(0);
    IMU_GYRO_Z = -r.gyro.get_scaled(2);

    IMU_ACCEL_X = r.accel.get_scaled(1);
    IMU_ACCEL_Y = r.accel.get_scaled(0);
    IMU_ACCEL_Z = -r.accel.get_scaled(2);

    IMU_COMPASS_X = r.mag.get_scaled(1);
    IMU_COMPASS_Y = r.mag.get_scaled(0);
    IMU_COMPASS_Z = -r.mag.get_scaled(2);

    IMU_EULER_X = r.euler.get_scaled(1);
    IMU_EULER_Y = r.euler.get_scaled(0);
    IMU_EULER_Z = -r.euler.get_scaled(2);

    IMU_QUAT_X = r.quat.get_scaled(2);
    IMU_QUAT_Y = r.quat.get_scaled(1);
    IMU_QUAT_Z = -r.quat.get_scaled(3);
}


/**
 * serial port connection/reconnection.
 */
int main(int argc, char **argv) {

  // get logging directory from arguments
  if(argc > 1) {
    loggingDirectory = argv[1];
    loggingDirectorySet = true;
    filepath = loggingDirectory + "/ahrs_log.csv";
    std::cout << filepath << std::endl;
    ahrs_csv.open(filepath.c_str(), std::ofstream::out | std::ofstream::app);
    if(ahrs_csv.is_open()) {
      printf("File open for writing!\n");
    }
  }

  // Load parameters from private node handle.
  //std::string port("/dev/robot/imu");
  std::string port("/dev/ttyUSB0");
  int32_t baud = 115200;

  serial::Serial ser;
  ser.setPort(port);
  ser.setBaudrate(baud);
  serial::Timeout to = serial::Timeout(500, 500, 0, 500, 0);
  ser.setTimeout(to);

  bool first_failure = true;
  while (1) {
    try
    {
      ser.open();
    }
    catch(const serial::IOException& e)
    {
      #if DEBUG
      std::cout<<"Unable to connect to port."<<std::endl;
      #endif
    }
    if (ser.isOpen())
    {
      #if DEBUG
      std::cout<<"Successfully connected to serial port."<<std::endl;
      #endif

      first_failure = true;

      try
      {
        um6::Comms sensor(&ser);
        configureSensor(&sensor);
        um6::Registers registers;
        handleResetService(&sensor);
        int t=0;
        while (1)
        {
            if(t>20) {

              // std::cout<<"Robo caido = "<<std::fixed<<IMU_STATE<<std::endl;
              // std::cout<<"med_acc_z = "<<std::fixed<<med_accel_z<<std::endl;
              // std::cout<<"giros_x = "<<std::fixed<<IMU_GYRO_X<<std::endl;
              // std::cout<<"giros_y = "<<std::fixed<<IMU_GYRO_Y<<std::endl;
              // std::cout<<"giros_z = "<<std::fixed<<IMU_GYRO_Z<<std::endl;
              //
              // std::cout<<"accel_x = "<<std::fixed<<IMU_ACCEL_X<<std::endl;
              // std::cout<<"accel_y = "<<std::fixed<<IMU_ACCEL_Y<<std::endl;
              // std::cout<<"accel_z = "<<std::fixed<<IMU_ACCEL_Z<<std::endl;
              //
              // std::cout<<"magne_x = "<<std::fixed<<IMU_COMPASS_X<<std::endl;
              // std::cout<<"magne_y = "<<std::fixed<<IMU_COMPASS_Y<<std::endl;
              // std::cout<<"magne_z = "<<std::fixed<<IMU_COMPASS_Z<<std::endl;
              // std::cout<<"Quat_x = "<<std::fixed<<IMU_QUAT_X<<std::endl;
              // std::cout<<"Quat_y = "<<std::fixed<<IMU_QUAT_Y<<std::endl;
              // std::cout<<"Quat_z = "<<std::fixed<<IMU_QUAT_Z<<std::endl;

              std::cout<<"Pitch  X = "<<std::fixed<<IMU_EULER_X*360/6.28318530718<<std::endl;
              std::cout<<"Roll   Y = "<<std::fixed<<IMU_EULER_Y*360/6.28318530718<<std::endl;
              std::cout<<"Yaw Z = "<<std::fixed<<IMU_EULER_Z*360/6.28318530718<<std::endl<<std::endl;

              

              t = 0;
            }
            t++;
          if (sensor.receive(&registers) == TRIGGER_PACKET)
          {
            // Triggered by arrival of final message in group.
            //header.stamp = ros::Time::now();
            //publishMsgs(registers, &n, header);
            publishMsgs(registers);
            //ros::spinOnce();
          }
        }
      }
      catch(const std::exception& e)
      {
        if (ser.isOpen()) {
          ser.close();
        }

        #if DEBUG
        std::cout << "Attempting reconnection after error." << std::endl;
        #endif
      }
    }
    else
    {
      #if DEBUG
      std::cout<< "Could not connect to serial device " << port << ". Trying again." << std::endl;
      #endif

      first_failure = false;
    }
  }

  ahrs_csv.close();
  ser.close();
  return 0;
}
