package mvcExample.model;

import mvcExample.view.Observer;

public interface Subject {
    void notifyObserver();
    void addObserver(Observer observer);
}
