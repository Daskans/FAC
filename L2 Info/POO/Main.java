class Main {
    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++) {
            System.out.printf(args[i] + " ");
        }
        System.out.printf("\n");
        System.out.printf("Inverse = ");
        for (int i = 0; i < args.length; i++) {
            System.out.printf(args[args.length - i - 1] + " ");
        }
        System.out.printf("\n");
    }
}