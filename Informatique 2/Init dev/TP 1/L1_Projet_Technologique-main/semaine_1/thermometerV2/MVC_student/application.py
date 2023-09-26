
import tkinter as tk
from view import View
from model import Model
from controller import Controller

class Application(tk.Tk):

    def __init__(self):

        super().__init__()
        self.title('My Thermometer')

        # create a view
        view = View(self)
        model = Model(10)

        # create a controller
        controller = Controller(model, view)
        

if __name__ == '__main__':
    app = Application()
    app.mainloop()