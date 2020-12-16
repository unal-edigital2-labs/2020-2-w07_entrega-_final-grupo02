#include <Wire.h>

#define OV7670_I2C_ADDRESS 0x21 /*Dirección del bus i2c para ña camara*/


void setup() {
  Wire.begin();
  Serial.begin(9600);  
  Serial.println("prueba estado actual");
  get_cam_register();
  
  set_cam_RGB444_QCIF();
  set_color_matrix();
  delay(100);
  Serial.println("Despues de config");
  get_cam_register();
  
}


void set_cam_RGB444_QCIF(){
   
  OV7670_write(0x12, 0x80);

  delay(100);
 
 OV7670_write(0x12, 0x0C);  //COM7: Set QCIF and RGB
 OV7670_write(0x11, 0xC0);       //CLKR: Set internal clock to use external clock
 OV7670_write(0x0C, 0x08);       //COM3: Enable Scaler
 OV7670_write(0x3E, 0x00);
 OV7670_write(0x40,0xD0);      //COM15: Set RGB
 OV7670_write(0x8C,0x02);      // Set RGB 444

 //Color Bar
 //OV7670_write(0x42, 0x08); 
 //OV7670_write(0x12, 0x0E);


 OV7670_write(0x3A,0x04);
 OV7670_write(0x14,0x18); // control de ganancia 

 OV7670_write(0x1E,0x18); // control de ganancia 

 OV7670_write(0x17,0x14);  //cambia hstart
 OV7670_write(0x18,0x02);  // cambia hstop
 OV7670_write(0x32,0x80);  // href deja el valor qye  viene por default
 OV7670_write(0x19,0x03);  // vref start
 OV7670_write(0x1A,0x7B);  // vref stop
 OV7670_write(0x03,0x0A);  // cambia vref

 
 OV7670_write(0x33,0x0B);  //
 OV7670_write(0x69,0x00);   // abajo
 OV7670_write(0xB1,0x0C);  
 OV7670_write(0xB2, 0x0E);
 OV7670_write(0xB3,0x80);    
 
}

void get_cam_register(){
  Serial.print ("0x12 ");   
  Serial.println(get_register_value(0x12), HEX); //COM7
  Serial.print ("0x11 ");   
  Serial.println(get_register_value(0x11), HEX); //
  Serial.print ("0x0C ");   
  Serial.println(get_register_value(0x0C), HEX); //
  Serial.print ("0x3E ");   
  Serial.println(get_register_value(0x3E), HEX); //
  Serial.print ("0x40 ");   
  Serial.println(get_register_value(0x40), HEX); //
  Serial.print ("0x3A ");   
  Serial.println(get_register_value(0x3A), HEX); //
  Serial.print ("0x14 ");   
  Serial.println(get_register_value(0x14), HEX);
 Serial.print ("0x17 ");   
   Serial.println(get_register_value(0x17), HEX);
 Serial.print ("0x18 ");   
   Serial.println(get_register_value(0x18), HEX);
   Serial.print ("0x32 "); 
  Serial.println(get_register_value(0x32), HEX);
  Serial.print ("0x19 "); 
  Serial.println(get_register_value(0x19), HEX);
  Serial.print ("0x1A "); 
  Serial.println(get_register_value(0x1a), HEX);
  Serial.print ("0x03 "); 
  Serial.println(get_register_value(0x03), HEX);
  Serial.print ("0x0F "); 
  Serial.println(get_register_value(0x0f), HEX);
  Serial.print ("0x1E "); 
  Serial.println(get_register_value(0x1e), HEX);
  Serial.print ("0x33 "); 
  Serial.println(get_register_value(0x33), HEX);
  Serial.print ("0x3C "); 
  Serial.println(get_register_value(0x3c), HEX);
  Serial.print ("0x69 "); 
  Serial.println(get_register_value(0x69), HEX);
  Serial.print ("0x78 "); 
  Serial.println(get_register_value(0x78), HEX);

}


int OV7670_write(int reg_address, byte data){
  return I2C_write(reg_address, &data, 1);
 }

int I2C_write(int start, const byte *pData, int size){
 //  Serial.println ("I2C init");   
    int n,error;
    Wire.beginTransmission(OV7670_I2C_ADDRESS);
    n = Wire.write(start);
    if(n != 1){
      Serial.println ("I2C ERROR WRITING START ADDRESS");   
      return 1;
    }
    n = Wire.write(pData, size);
    if(n != size){
      Serial.println( "I2C ERROR WRITING DATA");
      return 1;
    }
    error = Wire.endTransmission(true);
    if(error != 0){
      Serial.println( String(error));
      return 1;
    }
    Serial.println ("WRITE OK");
    return 0;
 }

byte get_register_value(int register_address){
  byte data = 0;
  Wire.beginTransmission(OV7670_I2C_ADDRESS);
  Wire.write(register_address);
  Wire.endTransmission();
  Wire.requestFrom(OV7670_I2C_ADDRESS,1);
  while(Wire.available()<1);
  data = Wire.read();
  return data;
}


void set_color_matrix(){
   OV7670_write(0x12, 0x0c);
    OV7670_write(0x11, 0x00);
    OV7670_write(0x0c, 0x00);
    OV7670_write(0x3E, 0x00);
    OV7670_write(0x8c, 0x02);
    OV7670_write(0x04, 0x00);
    OV7670_write(0x3a, 0x00);//
    OV7670_write(0x14, 0x38);
    OV7670_write(0x4f, 0x40);
    OV7670_write(0x50, 0x34);
    OV7670_write(0x51, 0x0c);
    OV7670_write(0x52, 0x17);
    OV7670_write(0x23, 0x29);
    OV7670_write(0x54, 0x40);
    OV7670_write(0x58, 0x1e);
    OV7670_write(0x3d, 0xc0);
    OV7670_write(0x11, 0x00);//
    OV7670_write(0x0e, 0x61);
    OV7670_write(0x0f, 0x4b);
    OV7670_write(0x16, 0x02);
    OV7670_write(0x1e, 0x37);
    OV7670_write(0x21, 0x02);
    OV7670_write(0x22, 0x91);
    OV7670_write(0x29, 0x07);
    OV7670_write(0x33, 0x0b);
    OV7670_write(0x35, 0x0b);
    OV7670_write(0x37, 0x1d);
    OV7670_write(0x38, 0x71);
    OV7670_write(0x39, 0x2a);
    OV7670_write(0x3c, 0x78);
    OV7670_write(0x4d, 0x40);
    OV7670_write(0x4e, 0x20);
    OV7670_write(0x69, 0x00);
    OV7670_write(0x6b, 0x4a);
    OV7670_write(0x74, 0x10);
    OV7670_write(0x8d, 0x4f);
    OV7670_write(0x8e, 0x00);
    OV7670_write(0x8f, 0x00);
    OV7670_write(0x90, 0x00);
    OV7670_write(0x91, 0x00);
    OV7670_write(0x96, 0x00);
    OV7670_write(0x9a, 0x00);
    OV7670_write(0xb0, 0x84);
    OV7670_write(0xb1, 0x0c);
    OV7670_write(0xb2, 0x0e);
    OV7670_write(0xb3, 0x82);
    OV7670_write(0xb8, 0x0a);
}


void loop(){
}
