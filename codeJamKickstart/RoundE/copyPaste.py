#!/usr/bin/env python
# -*- coding: utf-8 -*-
def solve(s, buff=None):
    if len(s) < 6:
        return len(s)
    charsUsed = set()
    n = 0
    i = 0
    while i < len(s):
        if s[i] not in charsUsed:
            charsUsed.add(s[i])
            n += 1
            i += 1
        else:
            j = 1
            while i+j <= len(s) and s[:i].find(s[i:i+j]) >= 0:
                j += 1
            j -= 1
            if j > 1:
                if buff is not None and j <= len(buff) and s[i:i+len(buff)] == buff:
                    i += len(buff)
                    n += 1
                else:
                    if j > 2 or (j == 2 and not s[i+j+2:].find(s[i:i+j+1]) and s[i:i+j+1] != s[i:i+j]):
                        buff = s[i:i+j]
                        i += len(buff)
                        n += 2
                    else:
                        i += 1
                        n += 1
            else:
                i += 1
                n += 1
    return n


if __name__ == "__main__":
    testcases = input()

    for caseNr in range(1, int(testcases)+1):
        cipher = input()
        print("Case #%i: %s" % (caseNr, solve(cipher)))



