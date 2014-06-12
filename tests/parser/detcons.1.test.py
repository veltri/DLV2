input = """
% Test with the following options:
%
% dl x -det
% dl x -det -filter=edb -filter=det -filter=true -filter=false -filter=ok
% dl x -det -filter=edb -filter=det -filter=true -filter=false -pfilter=ok

% EDB
edb.
edb_filtered.

% IDB, immediate.
det :- edb.
det_filtered :- edb.

% IDB, undefined.
undef1 | undef2 :- det.

% IDB, deterministic.
true | false :- det.
:- false.

true_filtered | false_filtered :- det.
:- false_filtered.

% IDB, deterministic, true negation.
ok | -ok :- edb.
:- -ok.

ok_filtered | -ok_filtered :- edb.
:- -ok_filtered.
"""
output = """
% Test with the following options:
%
% dl x -det
% dl x -det -filter=edb -filter=det -filter=true -filter=false -filter=ok
% dl x -det -filter=edb -filter=det -filter=true -filter=false -pfilter=ok

% EDB
edb.
edb_filtered.

% IDB, immediate.
det :- edb.
det_filtered :- edb.

% IDB, undefined.
undef1 | undef2 :- det.

% IDB, deterministic.
true | false :- det.
:- false.

true_filtered | false_filtered :- det.
:- false_filtered.

% IDB, deterministic, true negation.
ok | -ok :- edb.
:- -ok.

ok_filtered | -ok_filtered :- edb.
:- -ok_filtered.
"""
