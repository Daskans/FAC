from tkinter import *

class Application():

    def __init__(self):

        self.fenetre = Tk()                         # création de l'objet "fenetre"
        self.fenetre.title("My thermometer")        # titre de "fenêtre"
        self.label = Label(self.fenetre, text="10°C", width='20', height = '5', font = ('Arial', 25), bg='ivory')           # création de la fenetre elle même // c'est un label
        self.label.pack(side=TOP, padx=5, pady=5)

        Button(self.fenetre, text ='Increase', command = self.increase).pack(side=RIGHT, padx=5, pady=5)         # widget button
        Button(self.fenetre, text ='Decrease', command = self.decrease).pack(side=LEFT, padx=5, pady=5)
        Button(self.fenetre, text ='Fahrenheit', command = self.fahrenheit).pack(side=TOP, padx=5, pady=5)
        Button(self.fenetre, text ='Celsius', command = self.celsius).pack(side=BOTTOM, padx=5, pady=5)
        
        self.fenetre.mainloop()

    def increase(self):
        value = int(self.label['text'][:-2])
        unit = self.label['text'][-2:]
        self.label.config( text = str( value + 1 ) + unit)

    def decrease(self):
        value = int(self.label['text'][:-2])
        unit = self.label['text'][-2:]
        self.label.config( text = str( value - 1 ) + unit)

    def fahrenheit(self):
        value = int(self.label['text'][:-2])
        unit = self.label['text'][-2:]
        if unit == "°C" :
            self.label.config( text = str (int( value * (9/5) ) + 32 ) + '°F')

    def celsius(self):
        value = int(self.label['text'][:-2])
        unit = self.label['text'][-2:]
        if unit == "°F" :
            self.label.config( text = str (int(( value - 32 ) * (5/9) )) + '°C')


if __name__ == '__main__':
    app = Application()