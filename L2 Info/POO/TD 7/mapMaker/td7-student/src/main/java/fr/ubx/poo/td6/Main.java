package fr.ubx.poo.td6;

import fr.ubx.poo.td6.view.EditorView;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage)  {
        EditorView editorView = new EditorView(stage);
        Scene scene = new Scene(editorView);
        stage.setTitle("Mars map editor");
        stage.setScene(scene);
        stage.sizeToScene();
        stage.show();
    }

    public static void main(String[] args) { launch(); }
}