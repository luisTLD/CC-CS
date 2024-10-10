# Tinkercad

- [ULA 4 Bits VNM](https://www.tinkercad.com/things/6Yxkuh4V6mp-ula-4bits-vnm)

# ULA 4 bits VNM - Simulação

## Descrição
Este projeto simula uma ULA (Unidade Lógica Aritmética) de 4 bits VNM utilizando C++ para gerar o código hexadecimal necessário para a execução no Thinkercad.

## Arquivos
- `Encoder/testeula.ula`: Contém as atribuições de variáveis e as operações para a ULA.
- `main.cpp`: Código em C++ que gera o arquivo `testeula.hex`, com os códigos em hexadecimal para a ULA de 4 bits VNM.

## Instruções
1. Execute o código `main.cpp` para gerar o arquivo `testeula.hex` com os códigos em hexadecimal.
2. No Thinkercad, carregue o arquivo `testeula.hex` na memória da ULA de 4 bits.
3. No Monitor Serial, cole ou digite os códigos gerados.
4. Após carregar a memória da ULA, escreva "fim" no Monitor Serial.
5. Observe os LEDs da ULA acendendo de acordo com as operações realizadas.

## Finalização
Quando a ULA terminar as operações, os LEDs correspondentes a cada bit indicarão o resultado.
