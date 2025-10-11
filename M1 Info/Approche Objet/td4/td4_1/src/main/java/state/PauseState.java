package state;

import command.Command;
import td4.Automata;

public class PauseState implements State {

    private Automata automata;

    public PauseState(Automata automata) {
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

            default:
                throw new Exception("ERROR : Wrong command : expected PLAY, got " + currentCommand.toString());
        }
    }

    @Override
    public void loop() {
        System.out.println("PAUSE !");
    }

}
