import csv
import bpy
import mathutils
from marker import Marker


def parseCSV(csvPath):
    markers = []
    with open(csvPath) as csv_file:
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
    return markers


def main():
    # while(True):
    markers = parseCSV(
        '/home/alberto/VSCode workspace/blender_cvmarkers_animator/markersDetection.csv')

    bpy.ops.object.mode_set(mode='POSE')
    armature = bpy.data.objects["metarig"]
    bone = armature.pose.bones["hips"]
    bone.rotation_mode = "XYZ"
    bone.rotation_euler[0] = float(
        markers[0].coordinates[1]) * 100 / 360 * 6.28
    bone.rotation_euler[1] = float(
        markers[0].coordinates[0]) * 100 / 360 * 6.28


if __name__ == "__main__":
    main()
