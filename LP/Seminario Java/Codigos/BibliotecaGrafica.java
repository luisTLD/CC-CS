import java.awt.*;
import java.awt.event.*;

public class BibliotecaGrafica extends Frame implements ActionListener {
    // Campos de texto para entrada dos números
    TextField num1Field, num2Field, resultField;
    
    public BibliotecaGrafica() {
        // Define o layout da janela
        setLayout(new FlowLayout());
        
        // Cria os componentes
        Label num1Label = new Label("Número 1:");
        num1Field = new TextField(10);  // Campo de texto com largura de 10 caracteres
        
        Label num2Label = new Label("Número 2:");
        num2Field = new TextField(10);
        
        Label resultLabel = new Label("Resultado:");
        resultField = new TextField(10);
        resultField.setEditable(false);  // Campo de resultado não pode ser editado
        
        Button sumButton = new Button("Somar");
        sumButton.addActionListener(this);  // Adiciona ação para o botão
        
        // Adiciona os componentes ao Frame
        add(num1Label);
        add(num1Field);
        add(num2Label);
        add(num2Field);
        add(sumButton);
        add(resultLabel);
        add(resultField);
        
        // Configurações do Frame
        setSize(300, 200);
        setTitle("Calculadora de Soma");
        
        // Adiciona um listener para fechar a janela
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }

    public void actionPerformed(ActionEvent e) {
        try {
            // Lê os valores dos campos de texto
            int num1 = Integer.parseInt(num1Field.getText());
            int num2 = Integer.parseInt(num2Field.getText());
            
            // Calcula a soma
            int sum = num1 + num2;
            
            // Exibe o resultado
            resultField.setText(String.valueOf(sum));
        } catch (NumberFormatException ex) {
            resultField.setText("Erro");
        }
    }

    public static void main(String[] args) {
        // Cria e exibe a aplicação
        BibliotecaGrafica app = new BibliotecaGrafica();
        app.setVisible(true);
    }
}