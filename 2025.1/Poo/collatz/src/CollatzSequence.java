import java.util.Scanner;

public class CollatzSequence {
    //proximo numero da seuqentcia
    public static int nextCollatz(int n) {
        if (n % 2 == 0) {
            return n / 2; // Se n for par
        } else {
            return (n * 3) + 1; // Se n for ímpar
        }
    }

    // soma da sequencia
    public static int calculateCollatzSum(int n){
        int current = n;
        int soma = current;
        while (current != 1){
            current = nextCollatz(current);
            soma += current;
        }
        return soma;
    }
    public static void generateCollatzSequence(int n) {
        System.out.print("Sequência de Collatz: " + n);
        while (n != 1) {
            n = nextCollatz(n); // Calcula o próximo número da sequência
            System.out.print(" → " + n); // Exibe o próximo número
        }
        System.out.println(); // Pula uma linha após exibir a sequência
    }    
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite um número inteiro positivo: ");
        int n = scanner.nextInt();

        // Validar a entrada
        if (n < 1) {
            System.out.println("Erro: O número deve ser um inteiro positivo.");
        } else {
            // Gerar e exibir a sequência de Collatz
            generateCollatzSequence(n);

            // Calcular e exibir a soma dos termos
            int sum = calculateCollatzSum(n);
            System.out.println("Soma dos termos: " + sum);
        }

        scanner.close();
    }
}
