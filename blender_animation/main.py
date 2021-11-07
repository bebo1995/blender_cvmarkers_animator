import csv
from marker import Marker

markers = []
with open('markersDetection.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            line_count += 1
        else:
            m = Marker.fromCSVLine(row)
            markers.append(m)
            print(m.toString())
            line_count += 1
    print(f'Processed {line_count} lines.')
