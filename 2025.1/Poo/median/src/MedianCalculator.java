import java.util.Scanner;
public class MedianCalculator {
    public static int findMedian(int a, int b, int c) {
        int median;
        if ((a <= b && b <= c) || (c <= b && b <= a)) {
            median = b; // b é a mediana
        } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
            median = a; // a é a mediana
        } else {
            median = c; // c é a mediana
        }
        return median;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Digite o primeiro número: ");
        int a = scanner.nextInt();
        System.out.println("Digite o segundo número: ");
        int b = scanner.nextInt();
        System.out.println("Digite o terceiro número: ");
        int c = scanner.nextInt();
        int median = findMedian(a, b, c);
        System.out.println("A mediana dos números é: " + median ); 
        scanner.close();  
    }             
}
