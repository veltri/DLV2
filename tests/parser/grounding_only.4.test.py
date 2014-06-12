input = """
oraInizio(8).
oraInizio(9).
oraInizio(10).
oraInizio(11).
oraInizio(12).

precede(H,H1) :- oraInizio(H), oraInizio(H1), H < H1.
precede(G,G1) :- giornoSuccessivo(G,G1).
precede(G,G1) :- giornoSuccessivo(G,G2), precede(G2,G1).
giornoSuccessivo(lun,mar).
giornoSuccessivo(mar,mer).
giornoSuccessivo(mer,gio)."""
output = """
oraInizio(8).
oraInizio(9).
oraInizio(10).
oraInizio(11).
oraInizio(12).

precede(H,H1) :- oraInizio(H), oraInizio(H1), H < H1.
precede(G,G1) :- giornoSuccessivo(G,G1).
precede(G,G1) :- giornoSuccessivo(G,G2), precede(G2,G1).
giornoSuccessivo(lun,mar).
giornoSuccessivo(mar,mer).
giornoSuccessivo(mer,gio)."""
