def decodeRules(string):
    rules = []

    # Remove comments
    while string.find('%') != -1:
        subStringBeforeComment = string[:string.find('%')]
        subStringAfterComment = string[string.find('%'):]
        if subStringAfterComment.find('\n') != -1:
            string = subStringBeforeComment + subStringAfterComment[subStringAfterComment.find('\n')+1:]
        else:
            string = subStringBeforeComment
    
    # Remove whitespaces and endlines
    string = "".join(string.split())

    # Split in single rules
    while len(string) > 0:
        rule = ""
        if string.startswith(':~'):
            rule = string[:string.find(']')+1]
            string = string[string.find(']')+1:]
        else:
            posToCut = -1
            posQMark = string.find('?')
            posDot = string.find('.')
            if posQMark != -1 and posDot != -1:
                if posQMark < posDot:
                    posToCut = posQMark
                else:
                    posToCut = posDot
            elif posDot != -1:
                posToCut = posDot
            elif posQMark != -1:
                posToCut = posQMark
            else:
                posToCut = len(string)-1
            rule = string[:posToCut+1]
            string = string[posToCut+1:]
        #print(rule)
        if len(rule) > 0:
            rules.append(rule)

    return sorted(rules)
    
def checker(actualOutput, actualError):
    global output
    expectedRules = decodeRules(output)
    actualRules = decodeRules(actualOutput)
    #print(expectedRules)
    #print(actualRules)
    if expectedRules != actualRules:
        reportFailure(expectedRules, actualRules)
    else:
        reportSuccess(expectedRules, actualRules)
