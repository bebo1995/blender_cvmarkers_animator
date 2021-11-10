import csv
import bpy
import mathutils
import time
import functools
from bone import Bone


def parseCSV(csvPath):
    bones = []
    with open(csvPath) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                b = Bone.fromCSVLine(row)
                bones.append(b)
                print(b.toString())
                line_count += 1
    #print(f'Processed {line_count} lines.')
    return bones


def timer_call_fnc(bone):
    # parsing camera scene detected bones
    bones = parseCSV(
        '/home/alberto/VSCode workspace/blender_cvmarkers_animator/detectedBones.csv')

    # moving Blender scene bones
    bone.location[0] = bones[0].location[0]
    bone.location[1] = bones[0].location[1]
    bone.location[2] = bones[0].location[2]
    bone.rotation_euler[0] = bones[0].rotation[0] / 360 * 6.28
    bone.rotation_euler[1] = bones[0].rotation[1] / 360 * 6.28
    bone.rotation_euler[2] = bones[0].rotation[2] / 360 * 6.28
    return 0.01  # call every 0.01 seconds


def main():
    bones = parseCSV(
        '/home/alberto/VSCode workspace/blender_cvmarkers_animator/detectedBones.csv')
    bpy.ops.object.mode_set(mode='POSE')
    armature = bpy.data.objects["metarig"]
    bone = armature.pose.bones[bones[0].id]
    bone.rotation_mode = "XYZ"
    bpy.app.timers.register((functools.partial(timer_call_fnc, bone)))
    timer_call_fnc(bone)  # make first call

    # unregister later:
    #bpy.app.timers .unregister( timer_call_fnc )


if __name__ == "__main__":
    main()
