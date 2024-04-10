package fr.ubx.poo.td6.view;

import java.io.*;

import fr.ubx.poo.td6.model.*;
import javafx.scene.control.*;
import javafx.scene.input.Clipboard;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.stage.FileChooser;
import javafx.application.Application;

public class EditorView extends BorderPane {
    private final Stage stage;
    private Grid grid = new Grid(0,0);
    private final PickerView pickerView;
    private final Clipboard clipboard = Clipboard.getSystemClipboard();
    private final ClipboardContent clipboardContent = new ClipboardContent();

    public EditorView(Stage stage)  {
        // Tile picker
        this.pickerView = new PickerView();
        this.setRight(pickerView);
        this.stage = stage;
        
        GridRepo gridRepoVar = new GridRepoVar();
        GridRepoString gridRepoString = new GridRepoString();
        GridRepoStringRLE gridRepoStringRLE = new GridRepoStringRLE();
        FileChooser fileChooser = new FileChooser();
        GridView gridView = new GridView(grid, pickerView);
        


        // Create menu
        MenuBar menuBar = new MenuBar();
        Menu fileMenu = new Menu("File");
        Menu editMenu = new Menu("Edit");

        MenuItem newItem = new MenuItem("New map");
        MenuItem loadItemJ = new MenuItem("Load from Java declaration");
        MenuItem exportItemJ = new MenuItem("Export as Java declaration");
        MenuItem loadItemS = new MenuItem("Load from string");
        MenuItem exportItemS = new MenuItem("Export as string");
        MenuItem loadItemSZ = new MenuItem("Load from compressed string");
        MenuItem exportItemSZ = new MenuItem("Export as compressed string");
        MenuItem loadItemF = new MenuItem("Load from file");
        MenuItem exportItemF = new MenuItem("Export to file");
        MenuItem connectivityItem = new MenuItem("Check connectivity");
        MenuItem marksItem = new MenuItem("Clear marks");
        MenuItem exitItem = new MenuItem("Exit");
        exitItem.setAccelerator(KeyCombination.keyCombination("Ctrl+Q"));
        fileMenu.getItems().addAll(
            newItem, new SeparatorMenuItem(),
            loadItemJ, exportItemJ, new SeparatorMenuItem(),
            loadItemS, exportItemS, new SeparatorMenuItem(),
            loadItemSZ, exportItemSZ, new SeparatorMenuItem(),
            loadItemF, exportItemF, new SeparatorMenuItem(),
            exitItem);
            menuBar.getMenus().addAll(fileMenu, editMenu);
            this.setTop(menuBar);
            editMenu.getItems().addAll(connectivityItem, marksItem);
        
        // New map
        newItem.setOnAction(e -> {
            Form form = new Form(stage, "Size of the map : width x height");
            String[] parts = form.getText().replaceAll("\\s+","").split("x");
            if (parts.length != 2)
                return;
            try {
                int x = Integer.parseInt(parts[0]);
                int y = Integer.parseInt(parts[1]);
                this.grid = gridRepoString.create(x,y);
                updateGrid(grid);
            } catch (NumberFormatException numberFormatException) {
                return;
            }
        });
        
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
            this.grid = gridRepoString.load(form.getText());
            updateGrid(grid);
        });

        // Export as String
        exportItemS.setOnAction(e -> {
            exportDialog(gridRepoString.export(grid));
        });

        // Load from compressed String
        loadItemSZ.setOnAction(e -> {
            Form form = new Form(stage, "Input compressed string");
            this.grid = gridRepoStringRLE.load(form.getText());
            updateGrid(grid);
        });

        // Export as compressed String
        exportItemSZ.setOnAction(e -> {
            exportDialog(gridRepoStringRLE.export(grid));
        });

        // Load from file
        loadItemF.setOnAction(e -> {
            File file = fileChooser.showOpenDialog(stage);
            if (file != null) {
                try (Reader reader = new FileReader(file);) { // Wrap it in a BufferedReader for efficiency
                    this.grid = gridRepoStringRLE.load(reader);
                    updateGrid(grid);
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        // Export to file
        exportItemF.setOnAction(e -> {
            File file = fileChooser.showSaveDialog(stage);
            if (file == null) {
                Form form = new Form(stage, "File name");
                file = new File(fileChooser.getInitialDirectory(), form.getText());
            }
            try (Writer writer = new FileWriter(file);) { // Wrap it in a BufferedReader for efficiency
                gridRepoStringRLE.export(grid, writer);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });

        marksItem.setOnAction(e -> gridView.getMarker().clear());

        // Exit
        exitItem.setOnAction(e -> System.exit(0));

        

        connectivityItem.setOnAction(e -> {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText(null);
            alert.setContentText("We should indicate whether the map is fully connected or not!");
            alert.showAndWait();
        });

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
