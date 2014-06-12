input = """
edge( n2, n4). edge( n2, n3). edge( n3, n5).
edge( n4, n6). edge( n4, n5). edge( n5, n7).
edge( n6, n8). edge( n6, n7). edge( n7, n9).
edge( n8,n10). edge( n8, n9). edge( n9,n11).
               edge(n10,n11).
"""
output = """
edge( n2, n4). edge( n2, n3). edge( n3, n5).
edge( n4, n6). edge( n4, n5). edge( n5, n7).
edge( n6, n8). edge( n6, n7). edge( n7, n9).
edge( n8,n10). edge( n8, n9). edge( n9,n11).
               edge(n10,n11).
"""
