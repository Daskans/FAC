package fr.ubx.poo.td6.model;

import java.io.*;

public interface GridRepoIO {
    Grid load(Reader in) throws IOException;
    void export(Grid grid, Writer ou) throws IOException;
}
