#ifndef AUX_LIB
#define AUX_LIB

#include <cstdlib>
#include <iostream>
#include <string>

void buffer();

int SimNao();

int minusculo(std::string &s);

int maiusculo(std::string &s);

std::string verificarCodigo();

std::string verificarHorario();

std::string verificarAno();

std::string verificarNumero();

void removerNovaLinha(std::string &str);

void buffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int SimNao() {
  std::string ver;
  int tam = 0;
  while (1) {
    std::cin >> ver;
    tam = minusculo(ver);
    if (ver == "sim" || ver == "s") {
      return 1;
    } else if (ver == "nao" || ver == "n") {
      return 0;
    } else {
      std::cout << "Entrada invalida, Digite SIM ou NAO: ";
    }
  }
}

std::string verificarCodigo() {
  std::string codigo;
  bool validar;

  do {
    std::getline(std::cin, codigo);
    removerNovaLinha(codigo);

    validar = true;
     if (codigo.length() != 3 && (codigo[0] != '0')) {
      validar = false;
    }
    else if(codigo[0] == '0'){
        return codigo;
    }
    else {
      for (char c : codigo) {
        if (!isalpha(c)) {
          validar = false;
          break;
        }
      }
    }

    if (!validar) {
      std::cout << "Entrada invalida, digite 3 letras: ";
    }
  } while (!validar);

  for (char &c : codigo) {
    c = toupper(c);
  }
  std::cout << "Codigo valido!" << std::endl;
  return codigo;
}

std::string verificarHorario() {
  std::string tempo;
  bool validar;

  do {
    std::getline(std::cin, tempo);
    removerNovaLinha(tempo);

    validar = true;

    if (tempo.length() != 5 || tempo[2] != ':') {
      validar = false;
    } else {
      std::string horaString = tempo.substr(0, 2);
      std::string minutoString = tempo.substr(3, 2);

      if (!std::isdigit(horaString[0]) || !std::isdigit(horaString[1]) ||
          !std::isdigit(minutoString[0]) || !std::isdigit(minutoString[1])) {
        validar = false;
      } else {
        int hora = std::stoi(horaString);
        int minuto = std::stoi(minutoString);

        if (hora > 24 || minuto > 59) {
          validar = false;
        }
      }
    }

    if (!validar) {
      std::cout << "Entrada invalida, digite no formato HH:mm ";
    }
  } while (!validar);
  std::cout << "Hora valida!" << std::endl;
  return tempo;
}

std::string verificarAno() {
  std::string ano;
  bool validar;

  do {
    std::getline(std::cin, ano);
    removerNovaLinha(ano);

    validar = true;

    if (ano.length() != 10 || ano[2] != '/' || ano[5] != '/') {
      validar = false;
    } else {
      std::string diaString = ano.substr(0, 2);
      std::string mesString = ano.substr(3, 2);
      std::string anoString = ano.substr(6, 4);

      if (!std::isdigit(diaString[0]) || !std::isdigit(diaString[1]) ||
          !std::isdigit(mesString[0]) || !std::isdigit(mesString[1]) ||
          !std::isdigit(anoString[0]) || !std::isdigit(anoString[1]) ||
          !std::isdigit(anoString[2]) || !std::isdigit(anoString[3])) {
        validar = false;
      } else {
        int dia = std::stoi(diaString);
        int mes = std::stoi(mesString);
        int ano = std::stoi(anoString);

        if (dia > 31 || mes > 12 || ano < 2022) {
          validar = false;
        }
      }
    }

    if (!validar) {
      std::cout << "Entrada invalida, insira uma data no formato DD/MM/YYYY: ";
    }
  } while (!validar);
  std::cout << "Ano valido!" << std::endl;
  return ano;
}

std::string verificarNumero() {
  std::string numero;
  bool validar;

  do {
    std::getline(std::cin, numero);
    removerNovaLinha(numero);

    validar = true;
    int ponto = 0;
    int decimal = 0;

    for (char c : numero) {
      if (c == '.') {
        ponto++;
        if (ponto > 1) {
          validar = false;
          break;
        }
      } else if (ponto == 1) {
        decimal++;
        if (decimal > 2 || !std::isdigit(c)) {
          validar = false;
          break;
        }
      } else if (!std::isdigit(c)) {
        validar = false;
        break;
      }
    }
  } while (!validar);

  return numero;
}

void removerNovaLinha(std::string &str) {
  if (!str.empty() && str.back() == '\n') {
    str.pop_back();
  }
}

int minusculo(std::string &s) {
  for (char &c : s) {
    c = std::tolower(c);
  }
  return s.size();
}

int maiusculo(std::string &s) {
  for (char &c : s) {
    c = std::toupper(c);
  }
  return s.size();
}

#endif
