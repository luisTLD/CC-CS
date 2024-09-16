import Utils.Registro;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.time.LocalDate;

public class Tarefa implements Registro
{
    private int id;                     // Identificador unico da tarefa
    private String nome;                // Nome ou descricao da tarefa
    private LocalDate data_criacao;     // Data em que a tarefa foi criada
    private LocalDate data_conclusao;   // Data em que a tarefa foi concluída
    private String status;              // Status atual da tarefa ("Pendente", "Concluída", "Em Progresso")
    private byte prioridade;            // Nivel de prioridade da tarefa (0 - 5) -> (baixo - alto) 

    // Construtor padrao, inicializa com valores padrão
    public Tarefa()
    {
        this(-1, "", LocalDate.now(), LocalDate.now(), "", (byte) 0);
    }

    // Construtor para escrever no arquivo, onde ainda nao temos o ID correto
    public Tarefa(String n, LocalDate x, LocalDate y, String s, byte p)
    {
        this(-1, n, x, y, s, p);
    }

    // Construtor completo para inicializacao com todos os campos
    public Tarefa(int i, String n, LocalDate x, LocalDate y, String s, byte p)
    {
        this.id = i;
        this.nome = n;
        this.data_criacao = x;
        this.data_conclusao = y;
        this.status = s;
        this.prioridade = p;
    }

    // Metodos Getters e Setters
    public int getId() { return this.id; }
    public void setId(int id) { this.id = id; }

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

    // Converte todos os campos da instancia em um array de bytes
    public byte[] toByteArray() throws IOException
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);

        dos.writeInt(this.id);
        dos.writeUTF(this.nome);
        dos.writeInt((int) this.data_criacao.toEpochDay());
        dos.writeInt((int) this.data_conclusao.toEpochDay());
        dos.writeUTF(this.status);
        dos.writeByte(this.prioridade);

        return baos.toByteArray();
    }

    // Converte um array de bytes em valores e os atribui aos campos da instancia
    public void fromByteArray(byte[] b) throws IOException
    {
        ByteArrayInputStream bais = new ByteArrayInputStream(b);
        DataInputStream dis = new DataInputStream(bais);

        this.id = dis.readInt();
        this.nome = dis.readUTF();
        this.data_criacao = LocalDate.ofEpochDay(dis.readInt());
        this.data_conclusao = LocalDate.ofEpochDay(dis.readInt());
        this.status = dis.readUTF();
        this.prioridade = dis.readByte();
    }

    // Retorna uma representacao textual da instancia da tarefa
    public String toString() {
        return "\nID............: " + this.id +
               "\nNome..........: " + this.nome +
               "\nData Criação..: " + this.data_criacao +
               "\nData Conclusão: " + this.data_conclusao +
               "\nStatus........: " + this.status +
               "\nPrioridade....: " + this.prioridade;
    }

}
