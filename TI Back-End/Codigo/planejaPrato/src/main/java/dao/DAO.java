package dao;

import java.sql.*;

public class DAO {
	protected Connection conexao;
	
	public DAO() {
		conexao = null;
	}
	// conecta com o banco de dados sql (a tabela deve estar em minusculo, senha: edson, username: postgres)
	public boolean conectar() {
		String driverName = "org.postgresql.Driver";                    
		String serverName = "localhost";
		String mydatabase = "PlanejaPrato";
		int porta = 5432;
		String url = "jdbc:postgresql://" + serverName + ":" + porta +"/" + mydatabase;
		String username = "postgres";
		String password = "luissql";
		boolean status = false;

		try {
			Class.forName(driverName);
			conexao = DriverManager.getConnection(url, username, password);
			status = (conexao == null);
			System.out.println("Conexão efetuada com o postgres!");
			// Codigo para printar no console, todas as tabelas encontradas no SQL
			Class.forName(driverName);
            Connection conexao = DriverManager.getConnection(url, username, password);
            DatabaseMetaData metaData = conexao.getMetaData();
            ResultSet tables = metaData.getTables(null, null, null, new String[]{"TABLE"});

            //System.out.println("Tabelas encontradas:");
            while (tables.next()) {
                String tableName = tables.getString("TABLE_NAME");
                // printar as tabelas
                //System.out.println(tableName);
            }

		} catch (ClassNotFoundException e) { 
			System.err.println("Conexão NÃO efetuada com o postgres -- Driver não encontrado -- " + e.getMessage());
		} catch (SQLException e) {
			System.err.println("Conexão NÃO efetuada com o postgres -- " + e.getMessage());
		}

		return status;
	}
	
	//fechar conexao com bd
	public boolean close() {
		boolean status = false;
		
		try {
			conexao.close();
			status = true;
		} catch (SQLException e) {
			System.err.println(e.getMessage());
		}
		return status;
	}
}