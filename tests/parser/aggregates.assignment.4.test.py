input = """
% The variables to be aggregated over must appear only
% in the aggregate conjunction, while here they appear
% as guard, too.

ouch :- #count{Y : a(Y)} = Y.
"""
output = """
% The variables to be aggregated over must appear only
% in the aggregate conjunction, while here they appear
% as guard, too.

ouch :- #count{Y : a(Y)} = Y.
"""
