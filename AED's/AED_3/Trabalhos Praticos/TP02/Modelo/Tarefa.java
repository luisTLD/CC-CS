package Modelo;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.time.LocalDate;

public class Tarefa implements Registro.Registro
{
    // Campos da classe Tarefa
    private int id;                      // ID único da tarefa
    private int id_categoria;            // ID da categoria associada à tarefa
    private String nome;                 // Nome da tarefa
    private LocalDate data_criacao;      // Data de criação da tarefa
    private LocalDate data_conclusao;    // Data de conclusão da tarefa
    private String status;               // Status da tarefa (e.g., "pendente", "concluída")
    private byte prioridade;             // Prioridade da tarefa (0 a 127)

    // Construtor padrão, inicializa com valores padrão
    public Tarefa()
    {
        this(-1, -1, "", LocalDate.now(), LocalDate.now(), "", (byte) 0);
    }

    // Construtor para escrever no arquivo, onde ainda não temos o ID correto
    public Tarefa(int id_c, String n, LocalDate x, LocalDate y, String s, byte p)
    {
        this(-1, id_c, n, x, y, s, p);
    }

    // Construtor completo para inicialização com todos os campos
    public Tarefa(int i, int ic, String n, LocalDate x, LocalDate y, String s, byte p)
    {
        this.id = i;                // Atribui o ID único da tarefa
        this.id_categoria = ic;     // Atribui o ID da categoria associada
        this.nome = n;              // Atribui o nome da tarefa
        this.data_criacao = x;      // Atribui a data de criação
        this.data_conclusao = y;    // Atribui a data de conclusão
        this.status = s;            // Atribui o status da tarefa
        this.prioridade = p;        // Atribui a prioridade da tarefa
    }

    // Métodos Getters e Setters para os campos da classe
    public int getId() { return this.id; }
    public void setId(int id) { this.id = id; }

    public int getIdCategoria() { return this.id_categoria; }
    public void setIdCategoria(int id_categoria) { this.id_categoria = id_categoria; }

    public String getNome() { return this.nome; }
    public void setNome(String nome) { this.nome = nome; }

    public LocalDate getDataCriacao() { return this.data_criacao; }
    public void setDataCriacao(LocalDate data_criacao) { this.data_criacao = data_criacao; }

    public LocalDate getDataConclusao() { return this.data_conclusao; }
    public void setDataConclusao(LocalDate data_conclusao) { this.data_conclusao = data_conclusao; }

    public String getStatus() { return this.status; }
    public void setStatus(String status) { this.status = status; }

    public byte getPrioridade() { return this.prioridade; }
    public void setPrioridade(byte prioridade) { this.prioridade = prioridade; }

    // Converte todos os campos da instância em um array de bytes
    public byte[] toByteArray() throws IOException
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);

        dos.writeInt(this.id);                         // Escreve o ID
        dos.writeInt(this.id_categoria);               // Escreve o ID da categoria
        dos.writeUTF(this.nome);                       // Escreve o nome
        dos.writeInt((int) this.data_criacao.toEpochDay());   // Escreve a data de criação como número de dias desde a epoch
        dos.writeInt((int) this.data_conclusao.toEpochDay()); // Escreve a data de conclusão como número de dias desde a epoch
        dos.writeUTF(this.status);                    // Escreve o status
        dos.writeByte(this.prioridade);               // Escreve a prioridade

        return baos.toByteArray();
    }

    // Converte um array de bytes em valores e os atribui aos campos da instância
    public void fromByteArray(byte[] b) throws IOException
    {
        ByteArrayInputStream bais = new ByteArrayInputStream(b);
        DataInputStream dis = new DataInputStream(bais);

        this.id = dis.readInt();                      // Lê o ID
        this.id_categoria = dis.readInt();            // Lê o ID da categoria
        this.nome = dis.readUTF();                    // Lê o nome
        this.data_criacao = LocalDate.ofEpochDay(dis.readInt());   // Lê a data de criação a partir de dias desde a epoch
        this.data_conclusao = LocalDate.ofEpochDay(dis.readInt()); // Lê a data de conclusão a partir de dias desde a epoch
        this.status = dis.readUTF();                  // Lê o status
        this.prioridade = dis.readByte();             // Lê a prioridade
    }

    // Retorna uma representação textual da instância da tarefa
    public String toString() {
        return "\nID............: " + this.id +
               "\nID Categoria..: " + this.id_categoria +
               "\nNome..........: " + this.nome +
               "\nData Criação..: " + this.data_criacao +
               "\nData Conclusão: " + this.data_conclusao +
               "\nStatus........: " + this.status +
               "\nPrioridade....: " + this.prioridade;
    }
}
