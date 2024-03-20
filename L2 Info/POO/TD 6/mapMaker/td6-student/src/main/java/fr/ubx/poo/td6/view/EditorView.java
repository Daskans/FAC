package fr.ubx.poo.td6.view;

import fr.ubx.poo.td6.model.*;
import javafx.scene.control.*;
import javafx.scene.input.Clipboard;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class EditorView extends BorderPane {
    private final Stage stage;
    private Grid grid = new Grid(0,0);
    private final PickerView pickerView;
    private final Clipboard clipboard = Clipboard.getSystemClipboard();
    private final ClipboardContent clipboardContent = new ClipboardContent();

    public EditorView(Stage stage)  {
        this.stage = stage;
        GridRepo gridRepoVar = new GridRepoVar();
        //GridRepo gridRepoString = new GridRepoString();
        //GridRepo gridRepoStringRLE = new GridRepoStringRLE();

        // Tile picker
        this.pickerView = new PickerView();
        this.setRight(pickerView);

        // Create menu
        MenuBar menuBar = new MenuBar();
        Menu fileMenu = new Menu("File");

        MenuItem loadItemJ = new MenuItem("Load from Java declaration");
        MenuItem exportItemJ = new MenuItem("Export as Java declaration");
        MenuItem loadItemS = new MenuItem("Load from string");
        MenuItem exportItemS = new MenuItem("Export as string");
        MenuItem loadItemSZ = new MenuItem("Load from compressed string");
        MenuItem exportItemSZ = new MenuItem("Export as compressed string");
        MenuItem exitItem = new MenuItem("Exit");
        exitItem.setAccelerator(KeyCombination.keyCombination("Ctrl+Q"));
        fileMenu.getItems().addAll(
                loadItemJ, exportItemJ, new SeparatorMenuItem(),
                loadItemS, exportItemS, new SeparatorMenuItem(),
                loadItemSZ, exportItemSZ, new SeparatorMenuItem(),
                exitItem);
        menuBar.getMenus().addAll(fileMenu);
        this.setTop(menuBar);


        // Load from Java declarastion
        loadItemJ.setOnAction(e -> {
            Form form = new Form(stage, "Name field");
            this.grid = gridRepoVar.load(form.getText());
            updateGrid(grid);
        });

        // Export as Java declaration
        exportItemJ.setOnAction(e -> {
            exportDialog(gridRepoVar.export(grid));
        });

        // Load from String
        loadItemS.setOnAction(e -> {
            Form form = new Form(stage, "Input string");
//            this.grid = gridRepoString.load(form.getText());
            updateGrid(grid);
        });

        // Export as String
        exportItemS.setOnAction(e -> {
//            exportDialog(gridRepoString.export(grid))
        });

        // Load from compressed String
        loadItemSZ.setOnAction(e -> {
            Form form = new Form(stage, "Input compressed string");
//            this.grid = gridRepoStringRLE.load(form.getText());
            updateGrid(grid);
        });

        // Export as compressed String
        exportItemSZ.setOnAction(e -> {
//            exportDialog(gridRepoStringRLE.export(grid))
        });

        // Exit
        exitItem.setOnAction(e -> System.exit(0));
    }

    private void updateGrid(Grid grid) {
        if (grid != null) {
            Pane gridView = new GridView(grid, pickerView);
            this.setCenter(gridView);
            stage.sizeToScene();
        }
    }

    private void exportDialog(String msg) {
        clipboardContent.putString(msg);
        clipboard.setContent(clipboardContent);
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Export");
        alert.setHeaderText("Saved to clipboard");
        alert.getDialogPane().setContent(new TextArea(msg));
        alert.setResizable(true);
        alert.showAndWait();
    }

}
