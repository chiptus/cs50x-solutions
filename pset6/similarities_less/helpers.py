from nltk.tokenize import sent_tokenize


def unique_lines(s):
    return set(s.splitlines())


def unique_sentences(s):
    return set(sent_tokenize(s))


def unique_substrings(s, n):
    return set([s[0 + i:n + i] for i in range(0, len(s) - n + 1)])


def lines(a, b):
    """Return lines in both a and b"""
    return list(unique_lines(a).intersection(unique_lines(b)))


def sentences(a, b):
    """Return sentences in both a and b"""
    return list(unique_sentences(a).intersection(unique_sentences(b)))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    return list(unique_substrings(a, n).intersection(unique_substrings(b, n)))
