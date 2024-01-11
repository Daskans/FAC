from tkinter import *

class View(Frame):

    def __init__(self, parent):

        super().__init__(parent)
        self.parent = parent
        self.temperature_lbl = Label(self.parent, width='20', height = '5', font = ('Arial', 25), bg='ivory')
        self.temperature_lbl.pack(side=TOP, padx=5, pady=5)

        self.increase_btn = Button(self.parent, text ='Increase')
        self.increase_btn.pack(side=LEFT, padx=5, pady=5)

        self.decrease_btn = Button(self.parent, text ='Decrease')
        self.decrease_btn.pack(side=RIGHT, padx=5, pady=5)

        self.celsius_btn = Button(self.parent, text ='Celsius', width = 10)
        self.celsius_btn.pack(pady = 5)

        self.farenheit_btn = Button(self.parent, text ='Farenheit', width = 10)
        self.farenheit_btn.pack(pady = 5)

    def update(self, text : str) -> None:
        
        self.temperature_lbl.config(text = text)
