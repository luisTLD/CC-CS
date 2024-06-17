#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "classe.hpp"
#include "auxlib.hpp"

/*
union dados {
  std::string stringTemp;
  float floaTemp;
};
*/ // tentativa falha de usar union

int contarLinhas(std::fstream &file);

void menu();

void verSuaPassagem(passagemVoo passagem[], compradores &lista);

void comprarPassagem(passagemVoo passagem[], compradores &lista);

void verCompradores(passagemVoo passagem[], compradores &lista);

void escolha(passagemVoo passagem[], compradores &lista, std::fstream &file);

void preencherClasse(passagemVoo passagem[], std::fstream &file);

void confirmarClasse(passagemVoo passagem[], std::fstream &file, int tam);

void atualizarClasse(passagemVoo passagem[], std::fstream &file);

void atualizarFile(passagemVoo passagem[], std::fstream &file);

void excluirClasse(passagemVoo passagem[], std::fstream &file);

void editarVoo(passagemVoo passagem[], std::fstream &file);

void procurarVoo(passagemVoo passagem[]);

void mostrarPassagens(passagemVoo passagem[]);

void mostrarUmaPassagem(passagemVoo passagem[], int i);

int acharTamanhoClasse(passagemVoo passagem[]);

int acharID(passagemVoo passagem[]);

int maiorID(passagemVoo passagem[]);

int main() {
  std::fstream file;
  if (contarLinhas(file) < 3) {
    file.open("passagens.txt", std::ios::out);
    file << "0\n";
    file << "0\n";
    file.close();
  }
  // dados temp;
  passagemVoo passagem[20];
  compradores lista;
  escolha(passagem, lista, file);
}

void menu() {
  std::cout << "\n\t<-- Voos -->\n" << std::endl;
  std::cout << "0) Voltar ao menu\n" << std::endl;
  std::cout << "1) Cadastrar Voo" << std::endl;
  std::cout << "2) Ver Voos" << std::endl;
  std::cout << "3) Procurar Voos" << std::endl;
  std::cout << "4) Editar passagem" << std::endl;
  std::cout << "5) Excluir passagem" << std::endl;
  std::cout << "6) Comprar" << std::endl;
  std::cout << "7) Ver compradores" << std::endl;
  std::cout << "8) Ver sua passagem" << std::endl;
  std::cout << "9) Encerrar" << std::endl;
}

void escolha(passagemVoo passagem[], compradores &lista, std::fstream &file) {
  int loop = 1;
  int op = 0;
  int test = 1;
  menu();
  std::cout << "\nDigite sua opcao: ";
  do {
    atualizarClasse(passagem, file);
    std::cin >> op;
    if (std::cin.fail()) {
      std::cin.clear();
    }
    buffer();
    switch (op) {
    case 1:
      preencherClasse(passagem, file);
      break;
    case 2:
      mostrarPassagens(passagem);
      break;
    case 3:
      procurarVoo(passagem);
      break;
    case 4:
      editarVoo(passagem, file);
      break;
    case 5:
      excluirClasse(passagem, file);
      break;
    case 6:
      comprarPassagem(passagem, lista);
      break;
    case 7:
      verCompradores(passagem, lista);
      break;
    case 8:
      verSuaPassagem(passagem, lista);
      break;
    case 9:
      std::cout << "\n\n\t<--- Programa encerrado --->" << std::endl;
      loop = 0;
      break;
    default:
      std::cout << "\nDigite um numero valido!" << std::endl;
      test = 0;
      break;
    }
    if ( test == 1 ){
        if (loop == 1 ) {
          std::cout << "\nDeseja ver outra opcao ? responder com SIM ou NAO: ";
          if (SimNao()){
            std::cout << "\n\tCarregando...";
            system("clear || cls");
            menu();
            std::cout << "\nDigite sua opcao: ";
          }
          else {
            loop = 0;
            std::cout << "\n\tEncerrando...";
            system("clear || cls");
          }
        }
    }
    test = 1;
  } while (loop != 0 );
}

void preencherClasse(passagemVoo passagem[], std::fstream &file) {
  int tam = 0;
  tam = acharTamanhoClasse(passagem);
  std::string tempString;
  float tempFloat = 0;
  int tempInt = 0;

  if (tam == 0) {
    passagem[tam].set_id(1);
  } else {
    tempInt = passagem[tam - 1].get_id() + 1;
    passagem[tam].set_id(tempInt);
  }

  std::cout << "\nInsira o codigo de origem, 3 letras: ";
  tempString = verificarCodigo();
  if ( tempString[0] == '0' ){
    return;
  }
  passagem[tam].set_codigoOrigem(tempString);

  std::cout << "\nInsira o codigo de destino, 3 letras: ";
  tempString = verificarCodigo();
  passagem[tam].set_codigoDestino(tempString);

  std::cout << "\nInsira a cidade de origem: ";
  std::getline(std::cin, tempString);
  removerNovaLinha(tempString);
  minusculo(tempString);
  passagem[tam].set_cidadeOrigem(tempString);

  std::cout << "\nInsira a cidade de destino: ";
  std::getline(std::cin, tempString);
  removerNovaLinha(tempString);
  minusculo(tempString);
  passagem[tam].set_cidadeDestino(tempString);

  std::cout << "\nInsira a data, formato DD/MM/YYYY: ";
  tempString = verificarAno();
  passagem[tam].set_data(tempString);

  std::cout << "\nInsira a hora de saida, formato HH:mm: ";
  tempString = verificarHorario();
  passagem[tam].set_saidaHora(tempString);

  std::cout << "\nInsira a hora de chegada, formato HH:mm: ";
  tempString = verificarHorario();
  passagem[tam].set_chegadaHora(tempString);

  std::cout << "\nInsira o valor, R$";
  tempFloat = std::stof(verificarNumero());
  passagem[tam].set_valor(tempFloat);

  passagem[tam].set_disponiveis(100);
  confirmarClasse(passagem, file, tam);
}

void confirmarClasse(passagemVoo passagem[], std::fstream &file, int tam) {
  mostrarUmaPassagem(passagem, tam);
  std::cout << "\nConfirmar passagem? responder com SIM ou NAO: ";
  if (SimNao()) {
    atualizarFile(passagem, file);
    std::cout << "\nPassagem cadastrada!" << std::endl;
  } else {
    std::cout << "\nPassagem cancelada!" << std::endl;
  }
}

void atualizarClasse(passagemVoo passagem[], std::fstream &file) {
  int total = 0;
  std::string tempString;
  total = contarLinhas(file);
  file.open("passagens.txt", std::ios::in);
  std::getline(file, tempString);
  std::getline(file, tempString);
  for (int i = 0; i < total - 2; i++) {
    std::getline(file, tempString, ';');
    passagem[i].set_id(std::stoi(tempString));

    std::getline(file, tempString, ';');
    passagem[i].set_codigoOrigem(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_codigoDestino(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_cidadeOrigem(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_cidadeDestino(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_data(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_saidaHora(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_chegadaHora(tempString);

    std::getline(file, tempString, ';');
    passagem[i].set_valor(std::stof(tempString));

    std::getline(file, tempString, '\n');
    passagem[i].set_disponiveis(std::stoi(tempString));
  }
  file.close();
  for (int i = total - 2; i < 20; i++) {
    passagem[i].set_id(-1);
  }
}

void atualizarFile(passagemVoo passagem[], std::fstream &file) {
  int total = 0;
  std::string tempString;
  total = acharTamanhoClasse(passagem);
  file.open("passagens.txt", std::ios::out);
  file << total << "\n";
  file << passagem[total - 1].get_id() << "\n";
  for (int i = 0; i < total; i++) {
    file << passagem[i].get_id() << ";" << passagem[i].get_codigoOrigem() << ";"
         << passagem[i].get_codigoDestino() << ";"
         << passagem[i].get_cidadeOrigem() << ";"
         << passagem[i].get_cidadeDestino() << ";" << passagem[i].get_data()
         << ";" << passagem[i].get_saidaHora() << ";"
         << passagem[i].get_chegadaHora() << ";" << passagem[i].get_valor()
         << ";" << passagem[i].get_disponiveis() << "\n";
  }
  file.close();
}

void mostrarPassagens(passagemVoo passagem[]) {
  int tam = 0;
  tam = acharTamanhoClasse(passagem);
  if (tam == 0) {
    std::cout << "\nNao ha passagens cadastradas!\n";
  } else {
    std::cout << "\n\tPassagens:\n" << std::endl;
    for (int i = 0; i < tam; i++) {
      std::cout << "ID: " << passagem[i].get_id() << std::endl;
      std::cout << "Codigo Origem: " << passagem[i].get_codigoOrigem()
                << std::endl;
      std::cout << "Codigo Destino: " << passagem[i].get_codigoDestino()
                << std::endl;
      std::cout << "Cidade Origem: " << passagem[i].get_cidadeOrigem()
                << std::endl;
      std::cout << "Cidade Destino: " << passagem[i].get_cidadeDestino()
                << std::endl;
      std::cout << "Data: " << passagem[i].get_data() << std::endl;
      std::cout << "Hora de Saida: " << passagem[i].get_saidaHora()
                << std::endl;
      std::cout << "Hora de Chegada: " << passagem[i].get_chegadaHora()
                << std::endl;
      std::cout << "Valor: " << passagem[i].get_valor() << std::endl;
      std::cout << "Disponiveis: " << passagem[i].get_disponiveis()
                << std::endl;
      std::cout << "\n\t------------------------\n" << std::endl;
    }
  }
}

void mostrarUmaPassagem(passagemVoo passagem[], int i) {
  std::cout << "\n\tPassagem:\n" << std::endl;
  std::cout << "ID: " << passagem[i].get_id() << std::endl;
  std::cout << "Codigo Origem: " << passagem[i].get_codigoOrigem() << std::endl;
  std::cout << "Codigo Destino: " << passagem[i].get_codigoDestino()
            << std::endl;
  std::cout << "Cidade Origem: " << passagem[i].get_cidadeOrigem() << std::endl;
  std::cout << "Cidade Destino: " << passagem[i].get_cidadeDestino()
            << std::endl;
  std::cout << "Data: " << passagem[i].get_data() << std::endl;
  std::cout << "Hora de Saida: " << passagem[i].get_saidaHora() << std::endl;
  std::cout << "Hora de Chegada: " << passagem[i].get_chegadaHora()
            << std::endl;
  std::cout << "Valor: " << passagem[i].get_valor() << std::endl;
  std::cout << "Disponiveis: " << passagem[i].get_disponiveis() << std::endl;
}

void editarVoo(passagemVoo passagem[], std::fstream &file) {
  std::string tempString;
  int tempInt = 0;
  float tempFloat = 0;
  int id = 0;
  id = acharID(passagem);
  if (id == -1) {
    return;
  }
  mostrarUmaPassagem(passagem, id);
  std::cout << "\n1) Codigo Origem" << std::endl;
  std::cout << "2) Codigo Destino" << std::endl;
  std::cout << "3) Cidade Origem" << std::endl;
  std::cout << "4) Cidade Destino" << std::endl;
  std::cout << "5) Data" << std::endl;
  std::cout << "6) Hora de Saida" << std::endl;
  std::cout << "7) Hora de Chegada" << std::endl;
  std::cout << "8) Valor" << std::endl;
  std::cout << "9) Assentos Disponiveis\n" << std::endl;
  std::cout << "Digite o topico que deseja editar: ";
  int loop = 1;
  int op = 0;
  while (loop) {
    std::cin >> op;
    buffer();
    switch (op) {
    case 1:
      std::cout << "\nDigite o novo Codigo Origem: ";
      tempString = verificarCodigo();
      std::cout << "\nNovo Codigo Origem: " << tempString << std::endl;
      std::cout
          << "\nConfirmar novo Codigo Origem ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_codigoOrigem(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 2:
      std::cout << "\nDigite o novo Codigo Destino: ";
      tempString = verificarCodigo();
      std::cout << "\nNovo Codigo Destino: " << tempString << std::endl;
      std::cout
          << "\nConfirmar novo Codigo Destino ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_codigoDestino(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 3:
      std::cout << "\nDigite a nova Cidade Origem: ";
      std::getline(std::cin, tempString);
      removerNovaLinha(tempString);
      minusculo(tempString);
      std::cout << "\nNova Cidade Origem: " << tempString << std::endl;
      std::cout
          << "\nConfirmar nova Cidade Origem ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_cidadeOrigem(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 4:
      std::cout << "\nDigite a nova Cidade Destino: ";
      std::getline(std::cin, tempString);
      removerNovaLinha(tempString);
      minusculo(tempString);
      std::cout << "\nNova Cidade Destino: " << tempString << std::endl;
      std::cout
          << "\nConfirmar nova Cidade Destino ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_cidadeDestino(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 5:
      std::cout << "\nDigite o novo Ano: ";
      tempString = verificarAno();
      std::cout << "\nNovo Ano: " << tempString << std::endl;
      std::cout << "\nConfirmar novo Ano ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_data(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 6:
      std::cout << "\nDigite a nova Hora de Saida: ";
      tempString = verificarHorario();
      std::cout << "\nNova Hora de Saida: " << tempString << std::endl;
      std::cout
          << "\nConfirmar nova Hora de Saida ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_saidaHora(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 7:
      std::cout << "\nDigite a nova Hora de Chegada: ";
      tempString = verificarHorario();
      std::cout << "\nNova Hora de Chegada: " << tempString << std::endl;
      std::cout
          << "\nConfirmar nova Hora de Chegada ? respoonder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_chegadaHora(tempString);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 8:
      std::cout << "\nDigite o novo valor: ";
      tempFloat = std::stof(verificarNumero());
      std::cout << "\nNovo valor: " << tempFloat << std::endl;
      std::cout << "Confirmar novo valor ? responder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_valor(tempFloat);
      } else {
        std::cout << "Mudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    case 9:
      std::cout << "\nDigite o novo numero de assentos: ";
      tempInt = std::stoi(verificarNumero());
      std::cout << "\nNovo valor: " << tempInt << std::endl;
      std::cout
          << "Confirmar novo numero de assentos ? responder com SIM ou NAO: ";
      if (SimNao()) {
        std::cout << "\n <--- Voo alterado! --->" << std::endl;
        passagem[id].set_disponiveis(tempInt);
      } else {
        std::cout << "\nMudanca cancelada!" << std::endl;
      }
      loop = 0;
      break;
    default:
      std::cout << "Numero invalido!";
      break;
    }
    if (loop == 1) {
      if (std::cin.fail()) {
        std::cin.clear();
        buffer();
      }
      std::cout << "\nDigite sua opcao: ";
    }
  }
  atualizarFile(passagem, file);
  mostrarUmaPassagem(passagem, id);
}

void procurarVoo(passagemVoo passagem[]) {
  int op = 0;
  std::string tempString;
  int id = 0;
  int ver = 1;
  int total = 0;
  total = acharTamanhoClasse(passagem);
  std::cout << "\n1) ID\n";
  std::cout << "2) Codigo de origem\n";
  std::cout << "3) Codigo de destino\n";
  std::cout << "4) Cidade de origem\n";
  std::cout << "5) Cidade de destino\n";
  std::cout << "Outro numero para sair\n" << std::endl;
  std::cout << "Escolha a opcao de pesquisa: ";
  std::cin >> op;
  buffer();

  switch (op) {
  case 1:
    std::cout << "Insira o ID: ";
    std::cin >> id;
    for (int i = 0; i < total; i++) {
      if (passagem[i].get_id() == id) {
        mostrarUmaPassagem(passagem, i);
        ver = 0;
      }
    }
    break;
  case 2:
    std::cout << "Insira o codigo de origem: ";
    std::cin >> tempString;
    for (int i = 0; i < total; i++) {
      if (passagem[i].get_codigoOrigem() == tempString) {
        mostrarUmaPassagem(passagem, i);
        ver = 0;
      }
    }
    break;
  case 3:
    std::cout << "Insira o codigo de destino: ";
    std::cin >> tempString;
    for (int i = 0; i < total; i++) {
      if (passagem[i].get_codigoDestino() == tempString) {
        mostrarUmaPassagem(passagem, i);
        ver = 0;
      }
    }
    break;
  case 4:
    std::cout << "Insira a cidade de origem: ";
    std::cin >> tempString;
    for (int i = 0; i < total; i++) {
      if (passagem[i].get_cidadeOrigem() == tempString) {
        mostrarUmaPassagem(passagem, i);
        ver = 0;
      }
    }
    break;
  case 5:
    std::cout << "Insira a cidade de destino: ";
    std::cin >> tempString;
    for (int i = 0; i < total; i++) {
      if (passagem[i].get_cidadeDestino() == tempString) {
        mostrarUmaPassagem(passagem, i);
        ver = 0;
      }
    }
    break;
  default:
    if (std::cin.fail()) {
      std::cin.clear();
      buffer();
    }
    std::cout << "\nSaindo!" << std::endl;
    ver = 0;
    break;
  }
  if (ver) {
    std::cout << "\nPassagem nao encontrada!" << std::endl;
  }
}

void excluirClasse(passagemVoo passagem[], std::fstream &file) {
  int id = 0;
  int total = 0;
  total = acharTamanhoClasse(passagem);
  if (total == 0) {
    std::cout << "\nNao ha passagens cadastradas!\n";
  } else {
    id = acharID(passagem);
    if (id == -1) {
      return;
    }
    mostrarUmaPassagem(passagem, id);
    std::cout << "\nDeseja excluir voo id: " << passagem[id].get_id()
              << "? Responder com SIM ou NAO: ";
    if (SimNao()) {
      file.open("passagens.txt", std::ios::out);
      file << total - 1 << "\n";
      passagem[id].set_id(-1);
      file << maiorID(passagem) << "\n";
      for (int i = 0; i < total; i++) {
        if (i != id) {
          file << passagem[i].get_id() << ";" << passagem[i].get_codigoOrigem()
               << ";" << passagem[i].get_codigoDestino() << ";"
               << passagem[i].get_cidadeOrigem() << ";"
               << passagem[i].get_cidadeDestino() << ";"
               << passagem[i].get_data() << ";" << passagem[i].get_saidaHora()
               << ";" << passagem[i].get_chegadaHora() << ";"
               << passagem[i].get_valor() << ";"
               << passagem[i].get_disponiveis() << "\n";
        }
      }
      file.close();
      atualizarClasse(passagem, file);
      std::cout << "\nVoo excluido!" << std::endl;
    } else {
      std::cout << "\nCancelado!" << std::endl;
    }
  }
}

int acharTamanhoClasse(passagemVoo passagem[]) {
  int tamanho = 0;
  for (int i = 0; i < 20; i++) {
    if (passagem[i].get_id() != -1) {
      tamanho++;
    }
  }
  return tamanho;
}

int acharID(passagemVoo passagem[]) {
  int id = 0;
  int total = 0;
  int loop = 1;
  int i = 0;
  total = acharTamanhoClasse(passagem);
  std::cout << "\nDigite o ID da passagem: ";
  std::cin >> id;
  for (i = 0; i < total; i++) {
    if (passagem[i].get_id() == id) {
      loop = 0;
      break;
    }
  }
  if (loop != 0) {
    if (std::cin.fail()) {
      std::cin.clear();
      buffer();
    }
    std::cout << "\nID nao encontrado!\n";
    i = -1;
  }
  return i;
}

int maiorID(passagemVoo passagem[]) {
  int total = 0;
  int maiorID = 0;
  total = acharTamanhoClasse(passagem);
  maiorID = passagem[0].get_id();
  for (int i = 0; i < total; i++) {
    if (maiorID < passagem[i].get_id()) {
      maiorID = passagem[i].get_id();
    }
  }
  return maiorID;
}

int contarLinhas(std::fstream &file) {
  int total = 0;
  std::string temp;
  file.open("passagens.txt", std::ios::in);
  while (std::getline(file, temp)) {
    total++;
  }
  file.close();
  return total;
}

void comprarPassagem(passagemVoo passagem[], compradores &lista){
    int id = 0;
    int compID = 0;
    std::string nome;
    id = acharID(passagem);
    buffer();
    if ( id == -1 ){
        return;
    }
    mostrarUmaPassagem(passagem, id);
    std::cout << "\nDigite seu nome: ";
    std::getline(std::cin, nome);
    std::cout << "Seu ID eh: " << lista.get_ultimoId() << std::endl;
    lista.comprar(passagem[id].get_id(), nome);
}

void verCompradores(passagemVoo passagem[], compradores &lista){
    int ind = 0;
    ind = acharID(passagem);
    if ( ind == -1 ){
        return;
    }
    std::cout <<  std::endl;
    for ( int i = 0; i < lista.get_total(); i++ ){
        if ( lista.compradorId(i) == passagem[ind].get_id() ){
            lista.mostrar(i);
        }
    }
}

void verSuaPassagem(passagemVoo passagem[], compradores &lista){
    int id = 0;
    int idPass = 0;
    int indc = 0;
    std::cout << "\nDigite seu ID: ";
    std::cin >> id;
    if ( id == 0 ){
        return;
    }
    if (std::cin.fail()) {
      std::cin.clear();
    }
    buffer();
    idPass = lista.pesquisar(id).get_idPass();
    for ( int i = 0; i < acharTamanhoClasse(passagem); i++ ){
        if ( passagem[i].get_id() == idPass){
            indc = i;
            break;
        }
    }
    mostrarUmaPassagem(passagem, indc);

}
