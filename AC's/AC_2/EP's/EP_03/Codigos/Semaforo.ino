// C++ code

/*
Objetivo: ficar piscando o led azul, e em uma determinada 
sequencia, ligar ou desligar os demais led's
*/

bool blink = true;
int count = -1;

// [0] == blue, [1] == green, [2] == yellow, [3] == red
int led_pin[4] = {10, 11, 12, 13};

void setup()
{
    Serial.begin(9600);
  
  	// Definir as "portas"
    for (int i = 0; i < 4; i++)
    {
      	pinMode(led_pin[i], OUTPUT);
    }

    loop();
}

void loop()
{
  	// Ligar ou desligar o led azul
  	if (blink)
    {
      digitalWrite(led_pin[0], HIGH);
      if (count == 8) digitalWrite(led_pin[2], LOW);
      
      // Definir qual vai ser o prox led a ligar
      count = (count + 1) % 9;
    }
  	else digitalWrite(led_pin[0], LOW);
    
  	// Deacordo com o count, ligar o led certo e apagar o ultimo
  
  	// Ligar Led vermelho
    if (count < 3)
    {
      digitalWrite(led_pin[3], HIGH);
    }	
  	// Ligar Led verde
  	else if (count < 7)
    {
      if (count == 3)
      {
        digitalWrite(led_pin[3], LOW);
      }
      digitalWrite(led_pin[1], HIGH);
    }
  	// Ligar Led amarelo
  	else
    {
      if (count == 7)
      {
        digitalWrite(led_pin[1], LOW);
      }
      digitalWrite(led_pin[2], HIGH);
    }

    // trocar entre "0 e 1" para piscar o led azul
	blink = !blink;
	delay(500);
}