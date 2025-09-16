package fr.ubordeaux.ao;

public class PhoneNumber {
    private int number;
    private static final String number_regex = "^(0|0033)[1-9][0-9]{8}$";

    public PhoneNumber(int number) {
        if (String.valueOf(number).matches(number_regex)) {
            this.number = number;
        } else {
            throw new IllegalArgumentException("ERROR : Incorrect phone number");
        }
    }

    public int getPhoneNumber() {
        return number;
    }

}