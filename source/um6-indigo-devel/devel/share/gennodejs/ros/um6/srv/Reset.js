// Auto-generated. Do not edit!

// (in-package um6.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class ResetRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.zero_gyros = null;
      this.reset_ekf = null;
      this.set_mag_ref = null;
      this.set_accel_ref = null;
    }
    else {
      if (initObj.hasOwnProperty('zero_gyros')) {
        this.zero_gyros = initObj.zero_gyros
      }
      else {
        this.zero_gyros = false;
      }
      if (initObj.hasOwnProperty('reset_ekf')) {
        this.reset_ekf = initObj.reset_ekf
      }
      else {
        this.reset_ekf = false;
      }
      if (initObj.hasOwnProperty('set_mag_ref')) {
        this.set_mag_ref = initObj.set_mag_ref
      }
      else {
        this.set_mag_ref = false;
      }
      if (initObj.hasOwnProperty('set_accel_ref')) {
        this.set_accel_ref = initObj.set_accel_ref
      }
      else {
        this.set_accel_ref = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ResetRequest
    // Serialize message field [zero_gyros]
    bufferOffset = _serializer.bool(obj.zero_gyros, buffer, bufferOffset);
    // Serialize message field [reset_ekf]
    bufferOffset = _serializer.bool(obj.reset_ekf, buffer, bufferOffset);
    // Serialize message field [set_mag_ref]
    bufferOffset = _serializer.bool(obj.set_mag_ref, buffer, bufferOffset);
    // Serialize message field [set_accel_ref]
    bufferOffset = _serializer.bool(obj.set_accel_ref, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ResetRequest
    let len;
    let data = new ResetRequest(null);
    // Deserialize message field [zero_gyros]
    data.zero_gyros = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [reset_ekf]
    data.reset_ekf = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [set_mag_ref]
    data.set_mag_ref = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [set_accel_ref]
    data.set_accel_ref = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'um6/ResetRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '88aed859f96ffbc3fdce434a0b135bb3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool zero_gyros
    bool reset_ekf
    bool set_mag_ref
    bool set_accel_ref
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ResetRequest(null);
    if (msg.zero_gyros !== undefined) {
      resolved.zero_gyros = msg.zero_gyros;
    }
    else {
      resolved.zero_gyros = false
    }

    if (msg.reset_ekf !== undefined) {
      resolved.reset_ekf = msg.reset_ekf;
    }
    else {
      resolved.reset_ekf = false
    }

    if (msg.set_mag_ref !== undefined) {
      resolved.set_mag_ref = msg.set_mag_ref;
    }
    else {
      resolved.set_mag_ref = false
    }

    if (msg.set_accel_ref !== undefined) {
      resolved.set_accel_ref = msg.set_accel_ref;
    }
    else {
      resolved.set_accel_ref = false
    }

    return resolved;
    }
};

class ResetResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ResetResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ResetResponse
    let len;
    let data = new ResetResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'um6/ResetResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ResetResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: ResetRequest,
  Response: ResetResponse,
  md5sum() { return '88aed859f96ffbc3fdce434a0b135bb3'; },
  datatype() { return 'um6/Reset'; }
};
