package app;

import java.io.*;
import java.net.URI;
import java.net.http.*;
import java.net.http.HttpResponse.BodyHandlers;
import org.json.JSONObject;

public class OpenAIClient {
    private final String apiKey = "key";
    private final HttpClient httpClient = HttpClient.newHttpClient();
    
    public String createImages(String text) {
        String nome = "";
        String imageUrl = "";
        JSONObject requestBody = new JSONObject()
            .put("model", "dall-e-2")
            .put("prompt", text)
            .put("n", 1)
            .put("size", "512x512");

        HttpRequest request = HttpRequest.newBuilder()
            .uri(URI.create("https://api.openai.com/v1/images/generations"))
            .header("Authorization", "Bearer " + apiKey)
            .header("Content-Type", "application/json")
            .POST(HttpRequest.BodyPublishers.ofString(requestBody.toString()))
            .build();

        try {
            HttpResponse<String> response = httpClient.send(request, BodyHandlers.ofString());
            JSONObject jsonResponse = new JSONObject(response.body());
            imageUrl = jsonResponse.getJSONArray("data").getJSONObject(0).getString("url");

     
            // Download da imagem usando a URL e salvá-la localmente
            URI imageUri = URI.create(imageUrl);
            HttpRequest imageRequest = HttpRequest.newBuilder()
                .uri(imageUri)
                .build();

            HttpResponse<InputStream> imageResponse = httpClient.send(imageRequest, BodyHandlers.ofInputStream());

            if (imageResponse.statusCode() == 200) {
                // Diretório onde você quer salvar a imagem (certifique-se de que ele existe)
                String destinationFolder = "src/main/resources/public/img/";
                String replaceImg = text.toLowerCase().replace(" ", "-"); 
                nome = replaceImg + ".png"; // Nome do arquivo de saída

                // Criar o arquivo de saída e escrever a imagem nele
                File outputFile = new File(destinationFolder + nome);
                if (!outputFile.getParentFile().exists()) {
                    outputFile.getParentFile().mkdirs(); // Criar diretórios se não existirem
                }

                FileOutputStream outputStream = new FileOutputStream(outputFile);

                byte[] buffer = new byte[2048];
                int bytesRead;

                // Escrever os dados da imagem no arquivo
                while ((bytesRead = imageResponse.body().read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }

                outputStream.close(); // Fechar o FileOutputStream
                System.out.println("Imagem salva com sucesso!");
            } else {
                System.out.println("Erro ao salvar imagem: Código de resposta HTTP " + imageResponse.statusCode());
            }
			
			
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        
        System.out.println(imageUrl);
        return nome;
    }

    public static void main(String[] args) {
        //OpenAIClient client = new OpenAIClient();
        //String nome = client.createImages("bolo De cenoura");
        //System.out.println(nome);
    }
}
