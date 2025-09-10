package fr.ubordeaux.ao;

public class Mail {
    private String mail;
    private final static String LOCAL_PART = "[A-Za-z0-9_.!#$%&'*+/=?^_`{|}~-]";
    private final static String DOMAIN = "[A-Za-z0-9_.-]";
    private final static String EMAIL = "^"+LOCAL_PART+'@'+DOMAIN+'$';

    public Mail(String mail) {
        if (mail.matches(EMAIL)) {
            this.mail = mail;
        }
        else {
            System.err.println("invalid email address");
            return;
        }
    }

    public String getMail() {
        return mail;
    }

    @Override
    public String toString() {
        return mail.toString();
    }

}