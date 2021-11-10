class Bone:
    def __init__(self, id, location, rotation):
        self.id = id
        self.location = location
        self.rotation = rotation

    @staticmethod
    def fromCSVLine(csv_line):
        return Bone(csv_line[0],
                    [float(csv_line[1]), float(
                        csv_line[2]), float(csv_line[3])],
                    [float(csv_line[4]), float(csv_line[5]), float(csv_line[6])])

    def toString(self):
        locationstr = ''.join(map(str, self.location))
        rotationstr = ''.join(map(str, self.rotation))
        string = "bone " + self.id + " : " + "\n" + "location : "
        string += str(self.location[0]) + ", " + \
            str(self.location[1]) + ", " + str(self.location[2])
        string += "\n" + "rotation : "
        string += str(self.rotation[0]) + ", " + \
            str(self.rotation[1]) + ", " + str(self.rotation[2])
        string += "\n"
        return string
