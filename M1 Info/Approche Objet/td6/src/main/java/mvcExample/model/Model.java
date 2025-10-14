package mvcExample.model;

import mvcExample.view.Observer;

public class Model implements Subject {
    private Observer observer;
    public void addTicket(String ticketText) {

    }

    public void removeTicket() {

    }

    @Override
    public void notifyObserver() {
        observer.update(this);
    }

    @Override
    public void addObserver(Observer observer) {
        this.observer = observer;
    }
}
