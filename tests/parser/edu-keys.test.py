input = """
Teacher :- Class.
Class   :- Hour, Room.
Room    :- Hour, Teacher.
Room    :- Hour, Student.

key_found :- Teacher, Class, Hour, Room, Student.
"""
output = """
Teacher :- Class.
Class   :- Hour, Room.
Room    :- Hour, Teacher.
Room    :- Hour, Student.

key_found :- Teacher, Class, Hour, Room, Student.
"""
