package Menu;

import Arquivo.Backup;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Scanner;

public class MenuBackup 
{
    private static Backup backup;
    private static Scanner sc = new Scanner(System.in);


    public MenuBackup () throws Exception { backup = new Backup( ); }


    public void menu() throws Exception
    {
        int opcao;
        System.out.println("\nAEDsIII");
        System.out.println("-------");
        System.out.println("> Inicio > Backup");
        System.out.println("1 - Realizar Backup");
        System.out.println("2 - Restaurar Backup");
        System.out.println("0 - Voltar");
        System.out.print  ("Opção: ");
        try
        {
            opcao = Integer.valueOf(sc.nextLine());
        }
        catch (NumberFormatException e)
        {
            opcao = -1;
        }
    
        switch(opcao) 
        {
            case 0:
                break;
            case 1:
                realizarBackup( );
                break;
            case 2:
                restaurarBackup( );
                break;
            default:
                System.err.println("Opcao invalida.");
                break;
        }
    } 
    public static String getDataHoraAtual() { return ( LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd--HH-mm-ss")) ); } 

    public static void realizarBackup( ) throws Exception
    {
        System.out.println( "\nBackup:" );
        try
        {
            System.out.println( "\nConfirmar? (S/N)" );
            char resp = sc.nextLine( ).charAt(0);

            if( resp == 'S' || resp == 's' ) 
            {
                backup.createBackup(getDataHoraAtual( )+".db");
                System.out.println("Backup realizado");
            }
            else
            {
                System.out.println("cancelado");
            } 
        }
        catch (Exception e)
        {
            System.err.println("Erro");
        } 
    } 

    public static void restaurarBackup() throws Exception
    {
        System.out.println("\nRestaurar");
        
        try
        {
            ArrayList<String> backupsList = backup.listBackups();

            if( !backupsList.isEmpty( )) 
            {
                System.out.print( "ID do arquivo de backup: ");
                String input = sc.nextLine( );
    
                if(input.length( ) > 0) 
                {
                    int id_backup = Integer.parseInt(input);
                    backup.restoreBackup( backupsList.get(id_backup-1 )+".db");

                    System.out.println( "Backup restaurado");
                }
                else
                {
                    System.err.println( "ID invalido");
                } 
            }
        }
        catch (Exception e)
        {
            System.err.println("Erro");
        }
    }
} 
