import java.io.*;
import java.net.*;

public class TCPClient{


    public static void main(String [] args) throws exception{
	String sentence;
	String modifiedSentence;


	//Cria stream de entrada
	BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
	//Cria socket cliente, conecta ao servidor
	Socket clientSocket = new Socket("192.168.1.66",6200);
	//Cria stream de saida, ligado ao socket
	DataOutputStream outToServer = new DataOutputStream (clientSocket.getOutputStream());
	//Cria stream de entrada, ligado ao socket
	BufferedReader inFromServer = new BufferedReader (new InputStreamReader(clientSocket.getInputStream()));
	sentence = inFromUser.readLine();
	//Envia linha para o servidor
	outToServer.writeBytes(sentence + "\n");
	modifiedSentence = inFromServer.readLine();
	//Le linha do servidor
	System.out.println(modifiedSentence);
	clientSocket.close();

    }



}


