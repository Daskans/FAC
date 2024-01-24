public class Robot {

    String nom;
    Position position;
    double energy;
    double cost;

    Robot(String nom, Position position, double energy, double cost) {
        this.nom = nom;
        this.position = position;
        this.energy = energy;
        this.cost = cost;
    }

    double rayonAction() {
        return energy/cost;
    }

    boolean canMove(Position target) {
        return position.distance(target) <= rayonAction();
    }

    void showRobot() {
        System.out.printf("Robot " + nom +
                            "\n     Position : ");
        position.showPosition();
        System.out.println("     Energy : " + energy +
                            "\n     Cost : " + cost);
    }

    boolean move(Position target) {
        double distance = position.distance(target);
        if (!canMove(target)) {
            System.err.println("ERROR : not enough energy (distance was " + distance +")");
            return false;
        }
        energy -= cost*distance;
        int dx = target.x - position.x;
        int dy = target.y - position.y;
        position.displacement(dx, dy);
        return true;
    }
}
