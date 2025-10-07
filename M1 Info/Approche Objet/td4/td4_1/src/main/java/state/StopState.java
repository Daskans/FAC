package state;

import command.Command;
import td4.Automata;

public class StopState implements State {

    private Automata automata;

    public StopState(Automata automata) {
        this.automata = automata;
    }

    @Override
    public void handle() throws Exception {
        loop();
        Command currentCommand = automata.getCurrentCommand();
        switch (currentCommand) {
            case PLAY:
                automata.setState(new PlayState(automata));
                break;

            case FORWARD:
                automata.setState(new ForwardState(automata));
                break;

            case REWIND:
                automata.setState(new RewindState(automata));
                break;

            default:
                throw new Exception("ERROR : Wrong command : expected PLAY, REWIND or FORWARD, got " + currentCommand.toString());
        }
    }

    @Override
    public void loop() {
        System.out.println("STOP !");
    }

}
