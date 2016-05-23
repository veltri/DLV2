input = """
"kevin alone".
"a,b" | "ich liebe dich" :- "kevin alone", not ab.

"\" :- "a,b".
"\," :- "a,b".
",\" :- "a,b".

"I am completely"("crazy for you") :- "ich liebe dich".
"""
output = """
"kevin alone".
"a,b" | "ich liebe dich" :- "kevin alone", not ab.

"\" :- "a,b".
"\," :- "a,b".
",\" :- "a,b".

"I am completely"("crazy for you") :- "ich liebe dich".
"""
