import os
import json

import numpy as np
from nuscenes.nuscenes import NuScenes
from shapely.geometry import box

nusc = NuScenes(version='v1.0-mini',
                dataroot='.\\data\\sets\\nuscenes',
                verbose=True)
my_scene = nusc.scene[0]
first_sample_token = my_scene['first_sample_token']

current_sample = nusc.get('sample', first_sample_token)
sample_id = 0

extractData_2d = []
"""
def takeSecond(elem):
    return elem[1]
"""

while not current_sample['next'] == '':
    current_sample_data_token = current_sample['data']['RADAR_FRONT']
    cur_pth, boxes, cam_intri = nusc.get_sample_data(current_sample_data_token)

    current_anns_in_current_sample = {
        'sample_id': sample_id,
        'num_anns': len(boxes),
        'rectPoints': []
    }

    for box in boxes:
        corners_3d = box.corners()
        in_front = np.argwhere(corners_3d[2, :] > 0).flatten()
        if (len(in_front) != 4):
            continue
        else:
            cornersRadar_2d = corners_3d[:, in_front][0:2, :]
            x = list(cornersRadar_2d[0, :])
            x[2], x[3] = x[3], x[2]
            y = list(cornersRadar_2d[1, :])
            y[2], y[3] = y[3], y[2]

            cornersRadar_2d_dict = {'x': x, 'y': y}
            current_anns_in_current_sample['rectPoints'].append(
                cornersRadar_2d_dict)

    extractData_2d.append(current_anns_in_current_sample)

    current_sample_token = current_sample['next']
    current_sample = nusc.get('sample', current_sample_token)
    sample_id += 1

prj_pth = os.path.dirname(os.path.realpath(__file__))
dest_pth = os.path.join(prj_pth, "map_anns_in_radar.json")

with open(dest_pth, "w") as f:
    try:
        json.dump(extractData_2d, f, indent=4, separators=(',', ': '))
    except IOError:
        print("write json Error")
    else:
        print("write to json succeed")