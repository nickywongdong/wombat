/*Below examples demonstrate the usage of I2C library to read and write the RTC(DS1307) time. */
 
void RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
{
	I2C_Start();                            // Start I2C communication
 
	I2C_Write(C_Ds1307WriteMode_U8);        // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307SecondRegAddress_U8); // Select the SEC RAM address
 
	I2C_Write(var_sec_u8);	               // Write sec from RAM address 00H
	I2C_Write(var_min_u8);	               // Write min from RAM address 01H
	I2C_Write(var_hour_u8);	               // Write hour from RAM address 02H
 
	I2C_Stop();                 	      // Stop I2C communication after Setting the Time
}
 
 
void RTC_GetTime(uint8_t *ptr_hour_u8,uint8_t *ptr_min_u8,uint8_t *ptr_sec_u8)
{
	I2C_Start();                              // Start I2C communication
 
	I2C_Write(C_Ds1307WriteMode_U8);	         // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307SecondRegAddress_U8);   // Request Sec RAM address at 00H
 
	I2C_Stop();			        // Stop I2C communication after selecting Sec Register
 
	I2C_Start();		                // Start I2C communication
	I2C_Write(C_Ds1307ReadMode_U8);          // connect to DS1307(Read mode) by sending its ID
 
	*ptr_sec_u8 = I2C_Read(1);               // read second and return Positive ACK
	*ptr_min_u8 = I2C_Read(1); 	        // read minute and return Positive ACK
	*ptr_hour_u8 = I2C_Read(0);              // read hour and return Negative/No ACK
 
	I2C_Stop();		                // Stop I2C communication after reading the Time
}

void mian()
{
    *ptr_sec_u8 = I2C_Read(1);                // read second and return Positive ACK
    *ptr_min_u8 = I2C_Read(1); 	             // read minute and return Positive ACK
    *ptr_hour_u8 = I2C_Read(0);              // read hour and return Negative/No ACK
}