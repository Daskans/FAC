import csv, sys

class ParserCSV:

    def __init__(self, file_path_name, sep):

        self.file_path_name = file_path_name
        self.sep = sep

    
    def readColCSV(self, n):

        with open(self.file_path_name) as file:
            self.reader = csv.reader(file, delimiter = self.sep)
            column = []
            for line in self.reader:
                try:
                    column.append(float(line[n]))
                except:
                    pass
        return column

if __name__ == "__main__":
    print("data1.csv")
    p = ParserCSV("./data1.csv", " ")
    print(p.readColCSV(0))
    print("data2.csv")
    p = ParserCSV("./data2.csv", " ")
    print(p.readColCSV(1))
