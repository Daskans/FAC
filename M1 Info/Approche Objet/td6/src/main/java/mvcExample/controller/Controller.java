package mvcExample.controller;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import mvcExample.model.Model;
import mvcExample.view.View;

public class Controller {

    private View view;
    private Model model;
    private CommandManager commandManager = new CommandManager();

    public Controller(View view, Model model) {
        this.view = view;
        this.model = model;
        model.addObserver(view);
        initializeViewActions();
    }

    private void initializeViewActions() {
        view.setOnAddTicketAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                // Ajout d ’ une nouvelle commande
                commandManager.addNewCommand (() -> {
                    // Code où le modèle ajoute un nouveau ticket
                    String ticketText = view.getTicketInputText();
                    model.addTicket(ticketText);
                    model.notifyObserver();
                });
                // Execution de la première commande
                commandManager.executeNextCommand();
            }
        });

        view.setOnProcessTicketAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                // Ajout d ’ une nouvelle commande
                commandManager.addNewCommand (() -> {
                    // Code où le modèle ajoute un nouveau ticket
                    model.removeTicket();
                    model.notifyObserver();
                });
                // Execution de la première commande
                commandManager.executeNextCommand();
            }
        });
    }

}
