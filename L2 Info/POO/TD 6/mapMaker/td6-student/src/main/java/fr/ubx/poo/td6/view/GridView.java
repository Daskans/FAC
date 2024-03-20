package fr.ubx.poo.td6.view;

import fr.ubx.poo.td6.model.Grid;
import fr.ubx.poo.td6.model.Position;
import javafx.scene.effect.ColorAdjust;
import javafx.scene.layout.BorderPane;

public class GridView extends BorderPane {
    private final Grid grid;
    private final PickerView pickerView;

    private final ColorAdjust effect = new ColorAdjust();


    public GridView(Grid grid, PickerView pickerView) {
        this.grid = grid;
        this.pickerView = pickerView;
        effect.setBrightness(0.2);
        setPrefSize(grid.getWidth() * ImageResource.size,
                grid.getHeight() * ImageResource.size);
        for (int i = 0; i < this.grid.getWidth(); i++) {
            for (int j = 0; j < this.grid.getHeight(); j++) {
                createTile(i, j);
            }
        }
    }

    private void createTile(int i, int j) {
        int layoutX = i * ImageResource.size;
        int layoutY = j * ImageResource.size;
        Tile tile = new Tile(ImageResource.get(this.grid.get(i, j)), layoutX, layoutY);
        getChildren().add(tile);
        tile.setOnMouseClicked(e -> update(tile, i, j));
        tile.setOnMouseEntered(e -> {
            pickerView.setTilePos(new Position(i, j));
            tile.setEffect(effect);
            if (e.isShiftDown()) {
                update(tile, i, j);
            }
        });
        tile.setOnMouseExited(e -> {
            pickerView.setTilePos(null);
            tile.setEffect(null);
        });
    }

    private void update(Tile tile, int i, int j) {
        if (pickerView.getSelected() != null && pickerView.getSelected() != grid.get(i, j)) {
            getChildren().remove(tile);
            grid.set(i, j, pickerView.getSelected());
            createTile(i, j);
        }
    }
}
