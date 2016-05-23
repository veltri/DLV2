input = """
Melted_fuse_1 | Melted_fuse_2 :- High_current.
Light_off   :- Melted_fuse_1, Melted_fuse_2.
Light_off   :- Power_failure.
Light_off   :- Broken_bulb.
Burns_plate_1  :- not Melted_fuse_1, not Power_failure.
Burns_plate_2  :- not Melted_fuse_2, not Power_failure.
"""
output = """
Melted_fuse_1 | Melted_fuse_2 :- High_current.
Light_off   :- Melted_fuse_1, Melted_fuse_2.
Light_off   :- Power_failure.
Light_off   :- Broken_bulb.
Burns_plate_1  :- not Melted_fuse_1, not Power_failure.
Burns_plate_2  :- not Melted_fuse_2, not Power_failure.
"""
