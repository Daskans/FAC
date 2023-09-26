class FileRepo:
    
    def transformData2CSV(self, times, points, sep):

        csv_rows = [0]*len(times)
        for i in range(len(csv_rows)):
            csv_rows[i] = str(times[i])
            csv_rows[i] += sep+str(points[i].getX())+sep+str(points[i].getY()) 
        return  "\n".join(csv_rows)


    def export2CSV(self, times, points, filename="sample",  sep = ","):

        csv_text = self.transformData2CSV(times, points, sep)
        try:
            with open(filename+'.csv', 'w') as f:
                f.write(csv_text)
        except (IOError, EOFError) as e:
            print("Error while writing to file : ", e)
