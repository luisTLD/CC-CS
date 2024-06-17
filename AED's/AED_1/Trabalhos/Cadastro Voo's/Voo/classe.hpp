class passagemVoo {
private:
  int id;
  std::string codigoOrigem;
  std::string codigoDestino;
  std::string cidadeOrigem;
  std::string cidadeDestino;
  std::string data;
  std::string saidaHora;
  std::string chegadaHora;
  float valor;
  int disponiveis;

public:
  passagemVoo() : id(-1) {}

  int get_id() { return this->id; }
  std::string get_codigoOrigem() { return this->codigoOrigem; }
  std::string get_codigoDestino() { return this->codigoDestino; }
  std::string get_cidadeOrigem() { return this->cidadeOrigem; }
  std::string get_cidadeDestino() { return this->cidadeDestino; }
  std::string get_data() { return this->data; }
  std::string get_saidaHora() { return this->saidaHora; }
  std::string get_chegadaHora() { return this->chegadaHora; }
  float get_valor() { return this->valor; }
  int get_disponiveis() { return this->disponiveis; }

  void set_id(int id) { this->id = id; }
  void set_codigoOrigem(std::string codigoOrigem) {this->codigoOrigem = codigoOrigem;}
  void set_codigoDestino(std::string codigoDestino) {this->codigoDestino = codigoDestino;}
  void set_cidadeOrigem(std::string cidadeOrigem) {this->cidadeOrigem = cidadeOrigem;}
  void set_cidadeDestino(std::string cidadeDestino) {this->cidadeDestino = cidadeDestino;}
  void set_data(std::string data) {this->data = data;}
  void set_saidaHora(std::string saidaHora) {this->saidaHora = saidaHora;}
  void set_chegadaHora(std::string chegadaHora) {this->chegadaHora = chegadaHora;}
  void set_valor(float valor) {this->valor = valor;}
  void set_disponiveis(int disponiveis) {this->disponiveis = disponiveis;}
};

class comprador {
private:
  passagemVoo *passagem;
  std::string nome;
  int idComp;
  int idPass;

public:
  comprador(){
        idComp = -1;
        passagem = NULL;
  }

  passagemVoo get_passagem(){return *(this->passagem);}
  std::string get_nome(){return this->nome;}
  int get_idComp(){return this->idComp;}
  int get_idPass(){return this->idPass;}

  void set_passagem(passagemVoo passagem){this->passagem = &passagem;}
  void set_nome(std::string nome){this->nome = nome;}
  void set_idComp(int idComp){this->idComp = idComp;}
  void set_idPass(int idPass){this->idPass = idPass;}
};

class compradores{
private:
    comprador vetor[200];
    int total;
    int ultimoId;

public:
    compradores() : total(0), ultimoId(1) {}

    void comprar(int id, std::string nome){
        vetor[total].set_idPass(id);
        vetor[total].set_idComp(this->ultimoId);
        vetor[total].set_nome(nome);
        total++;
        ultimoId++;
    }

    comprador pesquisar(int id){
        for ( int i = 0; i < get_total(); i++ ){
            if ( vetor[i].get_idComp() == id ){
                return vetor[i];
            }
        }
        comprador* c = new comprador;
        return *c;
    }

    int compradorId(int id){
        return vetor[id].get_idPass();
    }

    void mostrar(int id){
        std::cout << vetor[id].get_idComp() << ") ";
        std::cout << vetor[id].get_nome() << std::endl;
    }

    int get_ultimoId(){
        return ultimoId;
    }

    int get_total(){
      return total;
    }
};
