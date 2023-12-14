class Model:

    def __init__(self, temperature : int):
        
        self.__temperature = temperature

    def celsius(self) -> int:
        
        self.__temperature = int((self.__temperature - 32) * 5 / 9)

    def farenheit(self) -> int:
        
        self.__temperature =  int(9 / 5 * self.__temperature + 32)

    def increase(self) -> int:
        
        self.__temperature =  int(self.__temperature + 1)

    def decrease(self) -> int:
        
        self.__temperature =  int(self.__temperature - 1)

    def getTemperature(self) -> int:
        
        self.__temperature = self.__temperature
