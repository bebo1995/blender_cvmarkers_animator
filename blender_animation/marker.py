class Marker:
    def __init__(self, id, coordinates, orientation):
        self.id = id
        self.coordinates = coordinates
        self.orientation = orientation

    @staticmethod
    def fromCSVLine(csv_line):
        return Marker(csv_line[0], [csv_line[1], csv_line[2], csv_line[3]], [csv_line[4], csv_line[5], csv_line[6]])

    def toString(self):
        coordinatesstr = ''.join(map(str, self.coordinates))
        orientationstr = ''.join(map(str, self.orientation))
        string = "marker " + self.id + " : " + "\n" + "coordinates :"
        string += coordinatesstr
        string += "\n" + "orientation :"
        string += orientationstr
        string += "\n"
        return string
