package fr.ubx.poo.td6.model;

public record Position(int x, int y) {
    @Override
    public String toString() {
        return "(" + x + "," + y + ")";
    }
}
