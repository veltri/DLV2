def decodeRules(string):
    rules = []

    for rule in string.split("\n"):
        rule = rule.strip()
        rule = "".join(rule.split())
        if len(rule) > 0:
            rules.append(rule)
            
    return sorted(rules)
    
def checker(actualOutput, actualError):
    global output
    expectedRules = decodeRules(output)
    actualRules = decodeRules(actualOutput)
    print(expectedRules)
    print(actualRules)
    if expectedRules != actualRules:
        reportFailure(expectedRules, actualRules)
    else:
        reportSuccess(expectedRules, actualRules)
