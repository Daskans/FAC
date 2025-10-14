package mvcExample.controller;

import java.util.LinkedList;
import java.util.Queue;

public class CommandManager {
    Queue<Command> bagOfCommand = new LinkedList<Command>();

    void addNewCommand(Command command) {
        bagOfCommand.add(command);
    }

    void executeNextCommand() {
        Command command = bagOfCommand.remove();
        command.execute();
    }
}
