from FileRepo import FileRepo
from Point import Point
from random import randint as rd

times = [i for i in range(10)]
points = [Point(rd(0,100),rd(0,100)) for i in range(10)]
fp = FileRepo()
fp.export2CSV(times, points, "test")


