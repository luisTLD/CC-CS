import java.io.File;
import java.time.LocalDate;
import java.lang.reflect.Constructor;

import Utils.Arquivo;

public class Main
{
    public static void main(String[] args)
    {
        // Instancia para manipular tarefas no arquivo (CRUD)
        Arquivo<Tarefa> arq_tarefas;
        
        // Criar tarefas para fazer testes
        LocalDate hoje = LocalDate.of(2024, 9, 15);
        Tarefa t1 = new Tarefa("Zerar Black Myth Wukong", hoje, LocalDate.of(2024, 10, 1), "Em Progresso", (byte) 2);
        Tarefa t2 = new Tarefa("Entregar TP01 AED3", hoje, LocalDate.of(2024, 9, 16), "Concluido", (byte) 3);
        Tarefa t3 = new Tarefa("Estudar AC", hoje, LocalDate.of(2024, 10, 3), "Pendente", (byte) 1);
        Tarefa t4 = new Tarefa("Resolver desafio da mochila", hoje, LocalDate.of(2024, 10, 12), "Pendente", (byte) 0);

        try
        {
            // Apagar os arquivos atuais para fazer o teste do 0
            (new File(".\\dados\\tarefas.db")).delete();
            (new File(".\\dados\\tarefas.hash_d.db")).delete();
            (new File(".\\dados\\tarefas.hash_c.db")).delete();
            
            // Escrever as tarefas testes no arquivo
            Constructor<Tarefa> constructor = Tarefa.class.getConstructor();
            arq_tarefas = new Arquivo<>("tarefas", constructor);
            arq_tarefas.create(t1);
            arq_tarefas.create(t2);
            arq_tarefas.create(t3);
            arq_tarefas.create(t4);

            // Comecar os testes
            System.out.println("\nTestes feitos com os Registro de ID: 1 e ID: 3");

            // Procurar uma tarefa por ID e printa-la no console
            System.out.println("\n     <----- Teste leitura ----->");
            System.out.println(arq_tarefas.read(1));
            System.out.println(arq_tarefas.read(3));

            // Alterar para um nome menor 
            System.out.println("\n\n      <----- Teste alterar nome ----->");
            t1.setNome("Zerar BM Wukong");
            arq_tarefas.update(t1);
            System.out.println(arq_tarefas.read(1));
            
            // Alterar para um nome maior
            t3.setNome("Estudar Arquitetura de Computadores");
            arq_tarefas.update(t3);
            System.out.println(arq_tarefas.read(3));

            // Deletar uma tarefa
            System.out.println("\n\n      <----- Teste deletar tarefa ----->");
            arq_tarefas.delete(1);
            System.out.println(arq_tarefas.read(1));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}