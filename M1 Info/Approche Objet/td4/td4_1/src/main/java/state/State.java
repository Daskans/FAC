package state;

public interface State {
    void handle() throws Exception;
    void loop();
}
