import java.util.Scanner;
public class FortalecerSenha{
    public static void main(String[] args) {
        //Cria um objeto Scanner chamado scanner para ler entradas do usuário
        Scanner scanner = new Scanner (System.in);
        String senha;
        System.out.println("Digite a senha: ");
        senha = scanner.nextLine();
        // validar senha
        while(senha.length() < 1 || senha.length() > 10 || !senha.matches("[a-z]+")){
            System.out.println("Senha inválida, a senha deve conter apenas letras de a-z e ter no maximo 10 caracteres");            
            System.out.println("Digite a senha: ");
            senha = scanner.nextLine();
        }
        String senhaFortalecida = fortalecerSenha(senha);
        int tempoDigitacao = calcularTempoDigitacao(senhaFortalecida);

        System.out.println("Senha fortalecida: " + senhaFortalecida);
        System.out.println("Tempo de digitação: " + tempoDigitacao + " segundos");
        scanner.close();

    }
    public static int calcularTempoDigitacao(String s){
        int tempoDigitacao = 2; //primeira letra sempre leva 2 segundos
        for (int i=1; i < s.length() ; i++){
            if(s.charAt(i) == s.charAt(i-1)){
                tempoDigitacao += 1; // caso a proxima letra seja =
            } else {
                tempoDigitacao += 2; //letra diferente
            }
        }
        return tempoDigitacao;
    }

    public static String fortalecerSenha(String s) {
        String melhorSenha = s;
        int melhorTempo = calcularTempoDigitacao(s);

        // Testa todas as posições para inserir um novo caractere
        for (int i = 0; i <= s.length(); i++) {
            for (char a = 'a'; a <= 'z'; a++) { // Testa todas as letras minúsculas
                String senhaTemp = s.substring(0, i) + a + s.substring(i);
                int tempo = calcularTempoDigitacao(senhaTemp);

                // Atualiza se for uma senha com maior tempo de digitação
                if (tempo > melhorTempo) {
                    melhorTempo = tempo;
                    melhorSenha = senhaTemp;
                }
            }
        }
        return melhorSenha;
    }
}