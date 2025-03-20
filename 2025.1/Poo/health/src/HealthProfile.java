import java.util.Calendar;
import java.util.Scanner;

public class HealthProfile {
    // Atributos privados
    private String firstName;
    private String lastName;
    private int dayOfBirth;
    private int monthOfBirth;
    private int yearOfBirth;
    private char gender;
    private double heightInInches;
    private double weightInPounds;

    // Construtor
    public HealthProfile(String firstName, String lastName, char gender, int dayOfBirth, int monthOfBirth, int yearOfBirth, double heightInInches, double weightInPounds) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
        this.dayOfBirth = dayOfBirth;
        this.monthOfBirth = monthOfBirth;
        this.yearOfBirth = yearOfBirth;
        this.heightInInches = heightInInches;
        this.weightInPounds = weightInPounds;
    }

    // Métodos de acesso (getters e setters)
    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public char getGender() {
        return gender;
    }

    public void setGender(char gender) {
        this.gender = gender;
    }

    public int getDayOfBirth() {
        return dayOfBirth;
    }

    public void setDayOfBirth(int dayOfBirth) {
        this.dayOfBirth = dayOfBirth;
    }

    public int getMonthOfBirth() {
        return monthOfBirth;
    }

    public void setMonthOfBirth(int monthOfBirth) {
        this.monthOfBirth = monthOfBirth;
    }

    public int getYearOfBirth() {
        return yearOfBirth;
    }

    public void setYearOfBirth(int yearOfBirth) {
        this.yearOfBirth = yearOfBirth;
    }

    public double getHeightInInches() {
        return heightInInches;
    }

    public void setHeightInInches(double heightInInches) {
        this.heightInInches = heightInInches;
    }

    public double getWeightInPounds() {
        return weightInPounds;
    }

    public void setWeightInPounds(double weightInPounds) {
        this.weightInPounds = weightInPounds;
    }

    public int calculateAge() {
        Calendar today = Calendar.getInstance();
        int currentYear = today.get(Calendar.YEAR);
        int currentMonth = today.get(Calendar.MONTH) + 1; // Janeiro é 0
        int currentDay = today.get(Calendar.DAY_OF_MONTH);

        int age = currentYear - yearOfBirth;

        // Ajusta a idade se o aniversário ainda não ocorreu este ano
        if (monthOfBirth > currentMonth || (monthOfBirth == currentMonth && dayOfBirth > currentDay)) {
            age--;
        }

        return age;
    }

    public int calculateMaxHeartRate() {
        return 220 - calculateAge();
    }

    public String calculateTargetHeartRate() {
        int maxHeartRate = calculateMaxHeartRate();
        int minTarget = (int) (maxHeartRate * 0.50);
        int maxTarget = (int) (maxHeartRate * 0.85);
        return minTarget + " bpm - " + maxTarget + " bpm";
    }

    public double calculateBMI() {
        return (weightInPounds * 703) / (heightInInches * heightInInches);
    }

    //exibir a tabela de referência do BMI
    public static void displayBMITable() {
        System.out.println("\nBMI \tClassificação");
        System.out.println("Menos de 18.5 \tAbaixo do peso");
        System.out.println("18.5 – 24.9 \tPeso normal");
        System.out.println("25.0 – 29.9 \tSobrepeso");
        System.out.println("30.0 ou mais \tObesidade");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Solicitar dados do usuário
        System.out.print("Digite seu primeiro nome: ");
        String firstName = scanner.nextLine();

        System.out.print("Digite seu sobrenome: ");
        String lastName = scanner.nextLine();

        // Validação do gênero
        char gender;
        while (true) {
            System.out.print("Digite seu gênero (M/F): ");
            gender = scanner.next().toUpperCase().charAt(0); // Converte para maiúscula
            if (gender == 'M' || gender == 'F') {
                break; // Sai do loop se o gênero for válido
            } else {
                System.out.println("Gênero inválido! Digite M para masculino ou F para feminino.");
            }
        }

        System.out.print("Digite sua data de nascimento (dia mês ano separados por espaço): ");
        int dayOfBirth = scanner.nextInt();
        int monthOfBirth = scanner.nextInt();
        int yearOfBirth = scanner.nextInt();

        System.out.print("Digite sua altura em polegadas: ");
        double heightInInches = scanner.nextDouble();

        System.out.print("Digite seu peso em libras: ");
        double weightInPounds = scanner.nextDouble();

        // Criar objeto HealthProfile
        HealthProfile person = new HealthProfile(firstName, lastName, gender, dayOfBirth, monthOfBirth, yearOfBirth, heightInInches, weightInPounds);

        // Exibir informações
        System.out.println("\nNome: " + person.getFirstName() + " " + person.getLastName());
        System.out.println("Gênero: " + (person.getGender() == 'M' ? "Masculino" : "Feminino"));
        System.out.println("Data de nascimento: " + String.format("%02d/%02d/%04d", person.getDayOfBirth(), person.getMonthOfBirth(), person.getYearOfBirth()));
        System.out.println("Idade: " + person.calculateAge() + " anos");
        System.out.println("Altura: " + person.getHeightInInches() + " polegadas");
        System.out.println("Peso: " + person.getWeightInPounds() + " libras");
        System.out.printf("Índice de Massa Corporal (BMI): %.1f\n", person.calculateBMI());
        System.out.println("Frequência cardíaca máxima: " + person.calculateMaxHeartRate() + " bpm");
        System.out.println("Faixa de frequência cardíaca alvo: " + person.calculateTargetHeartRate());

        // Exibir tabela de referência do BMI
        displayBMITable();

        scanner.close();
    }
}    

