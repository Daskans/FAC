package mvcExample;

import javafx.application.Application;
import javafx.stage.Stage;
import mvcExample.controller.Controller;
import mvcExample.model.Model;
import mvcExample.view.View;

public class MainApp extends Application {

    @Override
    public void start(Stage stage) {

        View view = new View(stage);
        Model model = new Model();
        Controller controller = new Controller(view, model);
    }

}
