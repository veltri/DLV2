input = """
% Range facts for truely negative predicates.

% small(0..12).
%-small(13..19).

% Ensure inconsistency is caught!

 small(13).
"""
output = """
% Range facts for truely negative predicates.

% small(0..12).
%-small(13..19).

% Ensure inconsistency is caught!

 small(13).
"""
