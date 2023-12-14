
class Controller:

    def __init__(self, model, view):

        self.__view = view
        self.__model = model
        self.__CELSIUS = "°C"
        self.__FARENHEIT = "°F"

        #Binding
        self.__view.update(str(self.__model.getTemperature()) + self.__CELSIUS)

        #callback
        self.__view.increase_btn.config(command = self.increase)
        self.__view.farenheit_btn.config(command = self.farenheit)
        self.__view.decrease_btn.config(command = self.decrease)
        self.__view.celsius_btn.config(command = self.celsius)


    def increase(self) -> None:
        self.__model.increase()
        self.__view.update(str(self.__model.getTemperature())+self.getUnit())

    def decrease(self) -> None:
        self.__model.decrease()
        self.__view.update(str(self.__model.getTemperature())+self.getUnit())

    def farenheit(self) -> None:
        if self.getUnit == self.__CELSIUS :
            self.__model.farhenheit()
            self.__view.update(str(self.__model.getTemperature())+self.getUnit())

    def celsius(self) -> None:
        if self.getUnit == self.__FARENHEIT :
            self.__model.celsius()
            self.__view.update(str(self.__model.getTemperature())+self.getUnit())

    def getUnit(self) -> str:
        
        return self.__view.temperature_lbl['text'][-2:]
