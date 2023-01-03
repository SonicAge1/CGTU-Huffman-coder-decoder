int* get_Node_Weight(char* allCharArr, char* Str) {
    static int weightList[99] = {'\0'};
    int allCharArrLen = 0;int StrLen = 0;
    int i = 0;int j = 0;
    while(allCharArr[i] !=  '\0'){
        i++;
        allCharArrLen++;
    }
    while(Str[j] !=  '\0'){
        j++;
        StrLen++;
    }

    for (int i = 0; i < allCharArrLen; i++) {
        weightList[i] = 0;
        for (int j = 0; j < StrLen; j++) {
            if (Str[j] == allCharArr[i]) {
                weightList[i]++;
            }
        }
    }
    return weightList;
}