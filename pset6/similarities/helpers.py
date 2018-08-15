from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())

def print_matrix(m):
    for row in m:
        for col in row:
            print(col[0], end="\t")
        print()
        
def distances(a, b):
    """Calculate edit distance from a to b"""
    # init matrix
    M = [[(None, None) for _ in range(len(b) + 1)] for __ in range(len(a) + 1)]
    M[0][0] = 0, None
    
    # init first row
    M[0][1:] = [(i, Operation.INSERTED) for i in range(1, len(b) + 1)]
    
    # init first column
    for i in range(1, len(a) + 1):
        M[i][0] = (i, Operation.DELETED)
    
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            M[i][j] = calc_edit_distance(i, j, M, a[i - 1], b[j - 1])
    
    return M


def calc_edit_distance(i, j, M, char_a, char_b):
    delete = M[i][j - 1][0] + 1
    insert = M[i - 1][j][0] + 1
    other = M[i - 1][j - 1][0]
    mini = min(delete, insert, other)
    if mini == delete:
        return (delete, Operation.DELETED)
    if mini == insert:
        return (insert, Operation.INSERTED)
    if char_a != char_b:
        return (other + 1, Operation.SUBSTITUTED)
    return (other, None)