;; Auto-generated. Do not edit!


(when (boundp 'um6::Reset)
  (if (not (find-package "UM6"))
    (make-package "UM6"))
  (shadow 'Reset (find-package "UM6")))
(unless (find-package "UM6::RESET")
  (make-package "UM6::RESET"))
(unless (find-package "UM6::RESETREQUEST")
  (make-package "UM6::RESETREQUEST"))
(unless (find-package "UM6::RESETRESPONSE")
  (make-package "UM6::RESETRESPONSE"))

(in-package "ROS")





(defclass um6::ResetRequest
  :super ros::object
  :slots (_zero_gyros _reset_ekf _set_mag_ref _set_accel_ref ))

(defmethod um6::ResetRequest
  (:init
   (&key
    ((:zero_gyros __zero_gyros) nil)
    ((:reset_ekf __reset_ekf) nil)
    ((:set_mag_ref __set_mag_ref) nil)
    ((:set_accel_ref __set_accel_ref) nil)
    )
   (send-super :init)
   (setq _zero_gyros __zero_gyros)
   (setq _reset_ekf __reset_ekf)
   (setq _set_mag_ref __set_mag_ref)
   (setq _set_accel_ref __set_accel_ref)
   self)
  (:zero_gyros
   (&optional __zero_gyros)
   (if __zero_gyros (setq _zero_gyros __zero_gyros)) _zero_gyros)
  (:reset_ekf
   (&optional __reset_ekf)
   (if __reset_ekf (setq _reset_ekf __reset_ekf)) _reset_ekf)
  (:set_mag_ref
   (&optional __set_mag_ref)
   (if __set_mag_ref (setq _set_mag_ref __set_mag_ref)) _set_mag_ref)
  (:set_accel_ref
   (&optional __set_accel_ref)
   (if __set_accel_ref (setq _set_accel_ref __set_accel_ref)) _set_accel_ref)
  (:serialization-length
   ()
   (+
    ;; bool _zero_gyros
    1
    ;; bool _reset_ekf
    1
    ;; bool _set_mag_ref
    1
    ;; bool _set_accel_ref
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _zero_gyros
       (if _zero_gyros (write-byte -1 s) (write-byte 0 s))
     ;; bool _reset_ekf
       (if _reset_ekf (write-byte -1 s) (write-byte 0 s))
     ;; bool _set_mag_ref
       (if _set_mag_ref (write-byte -1 s) (write-byte 0 s))
     ;; bool _set_accel_ref
       (if _set_accel_ref (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _zero_gyros
     (setq _zero_gyros (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _reset_ekf
     (setq _reset_ekf (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _set_mag_ref
     (setq _set_mag_ref (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _set_accel_ref
     (setq _set_accel_ref (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass um6::ResetResponse
  :super ros::object
  :slots ())

(defmethod um6::ResetResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass um6::Reset
  :super ros::object
  :slots ())

(setf (get um6::Reset :md5sum-) "88aed859f96ffbc3fdce434a0b135bb3")
(setf (get um6::Reset :datatype-) "um6/Reset")
(setf (get um6::Reset :request) um6::ResetRequest)
(setf (get um6::Reset :response) um6::ResetResponse)

(defmethod um6::ResetRequest
  (:response () (instance um6::ResetResponse :init)))

(setf (get um6::ResetRequest :md5sum-) "88aed859f96ffbc3fdce434a0b135bb3")
(setf (get um6::ResetRequest :datatype-) "um6/ResetRequest")
(setf (get um6::ResetRequest :definition-)
      "bool zero_gyros
bool reset_ekf
bool set_mag_ref
bool set_accel_ref
---

")

(setf (get um6::ResetResponse :md5sum-) "88aed859f96ffbc3fdce434a0b135bb3")
(setf (get um6::ResetResponse :datatype-) "um6/ResetResponse")
(setf (get um6::ResetResponse :definition-)
      "bool zero_gyros
bool reset_ekf
bool set_mag_ref
bool set_accel_ref
---

")



(provide :um6/Reset "88aed859f96ffbc3fdce434a0b135bb3")


