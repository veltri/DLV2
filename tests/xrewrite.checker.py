def decodeModels(string):
    models = []

    for model in string.split("\n"):
        if model != "" :
            model = model.strip()
            models.append(model)
            
    return sorted(models)
    
def checker(actualOutput, actualError):
    global output
    expectedModels = decodeModels(output)
    actualModels = decodeModels(actualOutput)
    #print(expectedModels)
    #print(actualModels)
    if expectedModels != actualModels:
        reportFailure(expectedModels, actualModels)
    else:
        reportSuccess(expectedModels, actualModels)
