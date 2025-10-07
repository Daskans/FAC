package td4;
import command.Command;
import state.StopState;

public class Main {
    public static void main ( String [] args ) {
        Automata automata = new Automata ();
        automata.setState (new StopState(automata));
        automata.setCurrentCommand(Command.PLAY);
        automata.request ();
        automata.setCurrentCommand(Command.STOP);
        automata.request ();
        automata.setCurrentCommand(Command.REWIND);
        automata.request ();
        automata.setCurrentCommand(Command.PLAY);
        automata.request ();
        automata.setCurrentCommand(Command.STOP);
        automata.request ();
    }
}