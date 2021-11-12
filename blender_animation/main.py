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
            if len(row) == 0:
                print("Empty file \n")
                return bones                
            if line_count == 0:
                line_count += 1
            else:
                b = Bone.fromCSVLine(row)
                bones.append(b)
                print(b.toString())
                line_count += 1
    #print(f'Processed {line_count} lines.')
    return bones


def timer_call_fnc(armature_bones):
    # parsing camera scene detected bones
    detected_bones = parseCSV(
        '/home/alberto/VSCode workspace/blender_cvmarkers_animator/detectedBones.csv')

    # moving Blender scene bones
    if len(detected_bones) == 0:
        print("Empty file \n")
        return 0.01
    for detected_bone in detected_bones:
        bone = armature_bones[detected_bone.id]
        bone.rotation_mode = "XYZ"
        bone.location[0] = -(detected_bone.location[0] * 10)
        bone.location[1] = -(detected_bone.location[1] * 10)
        bone.location[2] = -(detected_bone.location[2] * 10)
        bone.rotation_euler[0] = detected_bone.rotation[2]
        bone.rotation_euler[1] = detected_bone.rotation[1]
        bone.rotation_euler[2] = -(detected_bone.rotation[0])
    return 0.01  # call every 0.01 seconds


def main():
    bpy.ops.object.mode_set(mode='POSE')
    armature = bpy.data.objects["metarig"]
    armature_bones = armature.pose.bones
    bpy.app.timers.register((functools.partial(timer_call_fnc, armature_bones)))
    timer_call_fnc(armature_bones)  # make first call

    # unregister later:
    #bpy.app.timers .unregister( timer_call_fnc )


if __name__ == "__main__":
    main()
