package td4;
import command.Command;
import state.State;

public class Automata implements Context {

    private Command command;
    private State state = null;

    public Automata() {
        this.command = Command.STOP;
    }

    public void request() {
        try {       
            getState().handle();
        } catch(Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public State getState() {
        return state;
    }

    public Command getCurrentCommand() {
        return command;
    }

    public void setState(State state) {
        this.state = state;
    }

    public void setCurrentCommand(Command command) {
        this.command = command;
    }
}
