// C++ code

/* 
Objetivo: Simular uma ULA que realiza AND, OR, NOT, SOMA entre 2 Bits

Este codigo nao trata nenhuma entrada
input == "xyz"
x == Bit_A (0 ou 1)
y == Bit_B (0 ou 1)
z == op_code (0 == AND, 1 == OR, 2 == NOT_A, 3 == A + B)
*/

// input
String code;

/*
 [0] == Bit_A, [1] == Bit_B, [2] == Output_A, [3] == Output_B,
 [4] == op01, [5] == op02
*/
int led_pin[6] = {12, 13, 8, 9, 10, 11};


// [0] == Bit_A, [1] == Bit_B, [2] == op, [3] == Output
unsigned char bytes[4];

void setup()
{
    Serial.begin(9600);
  
  	// Definir as "portas"
    for (int i = 0; i < 6; i++)
    {
      	pinMode(led_pin[i], OUTPUT);
    }
  
    loop();
}

void loop()
{
  	// Esperar entrada, delay(10) para evitar loop excessivo
  	while (!Serial.available()) delay(10);
  	code = Serial.readString();
  
  	// Converter valor para Byte do Bit_A, Bit_B, op_code
  	for (int i = 0; i < 3; i++)
    {
      	bytes[i] = code[i] - '0';
    }
  	
  	// Realizar operacoes
  	switch (bytes[2])
    {
    	case 0x00:
      		bytes[3] = bytes[0] & bytes[1];
      		break;
      	case 0x01:
      		bytes[3] = bytes[0] | bytes[1];
      		break;
     	case 0x02:
      		bytes[3] = ~bytes[0];
      		break;
      	case 0x03:
      		bytes[3] = bytes[0] + bytes[1];
      		break;
    }
  	
	
  			// Ligar ou Desligar 
  
  	// Led Bit_A, Bit_B
  	for (int i = 0; i < 2; i++)
    {
      	if(bytes[i] == 0x01) digitalWrite(led_pin[i], HIGH);
      	else digitalWrite(led_pin[i], LOW);
    }
  
  	// Led op
	if((bytes[2] & 0x01) == 0x01) digitalWrite(led_pin[4], HIGH);
    else digitalWrite(led_pin[4], LOW);
  	if((bytes[2] & 0x02) == 0x02) digitalWrite(led_pin[5], HIGH);
    else digitalWrite(led_pin[5], LOW);
  
  	// Led Output
  	if((bytes[3] & 0x01) == 0x01) digitalWrite(led_pin[2], HIGH);
    else digitalWrite(led_pin[2], LOW);
  	if((bytes[3] & 0x02) == 0x02) digitalWrite(led_pin[3], HIGH);
    else digitalWrite(led_pin[3], LOW);
  
}