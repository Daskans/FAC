package mvcExample.view;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import mvcExample.model.Model;
import mvcExample.model.Subject;

public class View implements Observer {

    private Label label;
    private Button addTicketButton;
    private Button processTicketButton;
    private TextField ticketInputField;
    private TextArea ticketListArea;

    public View(Stage stage) {
        stage.setTitle("Liste des choses à faire");

        // Label for instructions or status
        label = new Label("Ajouter un ticket:");

        // Input field for ticket text
        ticketInputField = new TextField();
        ticketInputField.setPromptText("Entrer le ticket...");

        // Button to add a ticket
        addTicketButton = new Button("Ajouter ticket");

        // Button to process (or handle) a ticket
        processTicketButton = new Button("Traiter ticket");

        // Text area to display the list of tickets
        ticketListArea = new TextArea();
        ticketListArea.setEditable(false);
        ticketListArea.setWrapText(true);
        ticketListArea.setPrefHeight(200);  // Adjust the height as needed
        ticketListArea.setPromptText("Les tickets apparaissent ici...");

        // Vertical box layout
        VBox layout = new VBox(10, label, ticketInputField, addTicketButton, processTicketButton, ticketListArea);
        layout.setPadding(new Insets(10, 20, 10, 20));  // Top, Right, Bottom, Left

        Scene scene = new Scene(layout, 600, 400);

        stage.setScene(scene);
        stage.show();
    }

    // Set action for the "Ajouter ticket" button
    public void setOnAddTicketAction(EventHandler<ActionEvent> event) {
        addTicketButton.setOnAction(event);
    }

    // Set action for the "Traiter ticket" button
    public void setOnProcessTicketAction(EventHandler<ActionEvent> event) {
        processTicketButton.setOnAction(event);
    }

    // Retrieve the input from the ticket text field
    public String getTicketInputText() {
        return ticketInputField.getText();
    }

    // Clear the input text field after adding a ticket
    public void clearTicketInput() {
        ticketInputField.clear();
    }

    // Afficher un message dans une fenêtre popup
    public void showPopup(String message) {
        Stage popupStage = new Stage();
        popupStage.initModality(Modality.APPLICATION_MODAL); // Modality to block interaction with main window
        popupStage.setTitle("Message");

        // Create the Label with the message
        Label messageLabel = new Label(message);

        // Create the "OK" Button to close the popup
        Button okButton = new Button("OK");
        okButton.setOnAction(e -> popupStage.close()); // Close the popup when clicked

        // VBox layout for the popup
        VBox popupLayout = new VBox(10, messageLabel, okButton);
        popupLayout.setPadding(new Insets(20));

        Scene popupScene = new Scene(popupLayout, 300, 150);
        popupStage.setScene(popupScene);
        popupStage.showAndWait(); // Show the popup and wait for it to be closed
    }

    @Override
    public void update(Subject subject) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'update'");
    }
}
