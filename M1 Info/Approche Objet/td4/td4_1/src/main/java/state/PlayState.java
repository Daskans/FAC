package state;

import command.Command;
import td4.Automata;

public class PlayState implements State {

    private Automata automata;

    public PlayState(Automata automata) {
        this.automata = automata;
    }

    @Override
    public void handle() throws Exception {
        loop();
        Command currentCommand = automata.getCurrentCommand();
        switch (currentCommand) {
            case STOP:
                automata.setState(new StopState(automata));
                break;

            case PAUSE:
                automata.setState(new PauseState(automata));
                break;

            default:
                throw new Exception("ERROR : Wrong command : expected STOP or PAUSE, got " + currentCommand.toString());
        }
    }

    @Override
    public void loop() {
        System.out.println("PLAY !");
    }

}