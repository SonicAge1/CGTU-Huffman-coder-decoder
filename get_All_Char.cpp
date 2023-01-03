char* get_All_Char(char* Str) {
    char AllCharList[99] = { '\0' };
    char* allCharList = AllCharList;
    int strLen = 0, allCharLen = 0,utfCode = 0,counter = 0,trueLen = 0;
    char aChar;
    bool var = false;

    while (Str[trueLen] != '\0') {//原字符串长度
        utfCode = int (Str[trueLen]);
        if(utfCode < 0  && counter != 2){
            counter ++;
        }else if(utfCode >=0){
            strLen++;
        }else if(utfCode < 0  && counter == 2){
            strLen++;
            counter = 0;
        }
        trueLen++;
    }

    /*while (allCharList[allCharLen] != '\0') {
        allCharLen++;/arset长度
    }*/

    for (int i = 0; i < trueLen; i++) {
        aChar = Str[i];

        for (int j = 0; j < allCharLen; j++) {
            if (aChar == allCharList[j]) {
                var = true;
            }
        }

        if (!var) {
            allCharList[allCharLen] = aChar;
            allCharLen++;
        }
        else {
            var = false;
        }
    }
    return allCharList;
}