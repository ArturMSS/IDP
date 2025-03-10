import java.util.Scanner;

public class PalindromeChecker {
    public static boolean isValidInput(String input) {
        // Remove espaços em branco no início e no fim
        input = input.trim();
        // Verifica se a entrada não está vazia
        return !input.isEmpty();
    }
    public static boolean isPalindrome(String input) {
        // Converte a entrada para minúsculas para ignorar diferenças entre maiúsculas e minúsculas
        input = input.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        int length = input.length(); // Obtém o tamanho da string
        // Compara os caracteres da esquerda para a direita e da direita para a esquerda
        for (int i = 0; i < length / 2; i++) {
            if (input.charAt(i) != input.charAt(length - 1 - i)) {
                return false; // Não é um palíndromo
            }
        }
        return true; // É um palíndromo
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input;

        // Loop para garantir que uma entrada válida seja inserida
        while (true) {
            System.out.print("Digite uma sequência: ");
            input = scanner.nextLine();

            // Verifica se a entrada é válida
            if (isValidInput(input)) {
                break; // Sai do loop se a entrada for válida
            } else {
                System.out.println("Erro: A entrada não pode estar vazia.");
            }
        }

        // Verifica se a entrada é um palíndromo
        if (isPalindrome(input)) {
            System.out.println("A sequência \"" + input + "\" é um palíndromo.");
        } else {
            System.out.println("A sequência \"" + input + "\" não é um palíndromo.");
        }

        scanner.close();
    }
}

