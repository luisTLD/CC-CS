/*
Leia duas strings sendo que a primeira é o nome de uma página web e a segunda, seu endereço. 
Por exemplo, Pontifícia Universidade Católica de Minas Gerais e www.pucminas.br. 
Em seguida, mostre na tela o número de vogais (sem e com acento), consoantes e dos padrões <br> e <table> 
que aparecem no código dessa página. A entrada padrão é composta por várias linhas. 
Cada uma contém várias strings sendo que a primeira é um endereço web e as demais o nome dessa página web. 
A última linha da entrada padrão contém a palavra FIM. 
A saída padrão contém várias linhas sendo que cada uma apresenta o número de ocorrência (valor x_{i} entre parênteses) 
de cada caractere ou string solicitado. Cada linha de saída será da seguinte forma: 
a(x_{1}) e(x_{2}) i(x_{3}) o(x_{4}) u(x_{5}) á(x_{6}) é(x_{7}) í(x_{8}) ó(x_{9}) ú(x_{10}) à(x_{11}) 
è(x_{12}) ì(x_{13}) ò(x_{14}) ù(x_{15}) ã(x_{16}) õ(x_{17}) â(x_{19}) ê(x_{19}) î(x_{20}) ô(x_{21}) 
û(x_{22}) consoante(x_{23}) *<br>*(x_{24}) *<table>*(x_{25}) nomepágina(x_{26}).
*/

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Main {
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);

      boolean printNewLine = false;

      String link = new String();
      String input = new String();

      // char[] vog = {'a', 'e', 'i', 'o', 'u', 'á', 'é', 'í', 'ó', 'ú', 'à', 'è', 'ì', 'ò', 'ù', 'ã', 'õ', 'â', 'ê', î', 'ô', 'û'}
      char[] vog = { 97, 101, 105, 111, 117, 225, 233, 237, 243, 250, 224, 232, 236, 242, 249, 227, 245, 226, 234,
238, 244, 251 }; // total = 22
      char[] cons = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x',
'y', 'z' }; // total = 21
      int[] count = new int[25]; // 0 - 21 ( vog ) 22 ( cons ) 23 - 24 ( br & table )

      while (!((input = sc.nextLine()).equals("FIM"))){
         link = sc.nextLine();
         link = htmlCode(link);

         if ( printNewLine ) System.out.printf("\n");
         printNewLine = true;

         objCount(vog, cons, count, link);
         objPrint(vog, count);
         System.out.print(input);

         arrayReset(count);
      }

      sc.close();
   }

   static void verChar(char[] vog, char[] cons, int[] count, char c) {
      boolean aux = false;

      for (int i = 0; i < 21; i++) {
         if (c == cons[i]) {
            count[22]++;
            aux = true;
            break;
         }
      }
      if (!aux) {
         for (int i = 0; i < 22; i++) {
            if (c == vog[i]) {
               count[i]++;
               break;
            }
         }
      }
   }

   static String htmlCode(String link) {
      StringBuilder resp = new StringBuilder();

      try {
      URL url = new URL(link);
      BufferedReader htmlRead = new BufferedReader(new InputStreamReader(url.openStream()));

      while ((link = htmlRead.readLine()) != null) resp.append(link);
      } 
      catch (MalformedURLException mue) {
			mue.printStackTrace();
		} 
      catch (IOException ioe) {
			ioe.printStackTrace();
		}
      return resp.toString();
   }

   static void objCount(char[] vog, char[] cons, int[] count, String link){
      for (int i = 0; i < link.length(); i++) {
         if ( link.charAt(i) == '<'){
            if (link.substring(i, i+4).equals("<br>")) count[23]++;
            else if (link.substring(i, i+7).equals("<table>")) count[24]++;
         }
         else {
            verChar(vog, cons, count, link.charAt(i));
         }
      }
      count[0] -= count[24];
      count[1] -= count[24];
      count[22] -= (count[24]*3) + (count[23]*2);
   }

   static void objPrint(char[] vog, int[] count){
      for (int i = 0; i < 22; i++) {
         System.out.printf("%s(%d) ", vog[i], count[i]);
      }
      System.out.printf("consoante(%d) ", count[22]);
      System.out.printf("<br>(%d) ", count[23]);
      System.out.printf("<table>(%d) ", count[24]);
   }

   static void arrayReset(int[] count){
      for (int i = 0; i < count.length; i++) count[i] = 0;
   }

}