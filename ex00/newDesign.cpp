/*PROGRAM BitcoinExchange
    
    DATA:
        map<string, float> _database

    ─────────────────────────────────────────────
    PUBLIC: loadDatabase(filename)
    ─────────────────────────────────────────────
        open file
        if file cant be opened → print error, return false
        skip header line
        for each line in file:
            split at ','
            left  → date
            right → value
            convert value to float
            store in _database
        return true

    ─────────────────────────────────────────────
    PUBLIC: processInput(filename)
    ─────────────────────────────────────────────
        open file
        if file cant be opened → print error, return false
        skip header line
        for each line in file:
            error = validLine(line, date, strValue)
            if error != OK → printError(error, line), continue
            
            error = validDate(date)
            if error != OK → printError(error, date), continue
            
            error = validValue(strValue)
            if error != OK → printError(error, strValue), continue
            
            value = convert strValue to float
            price = lookup(date)
            print: date => value = price * value
        return true

    ─────────────────────────────────────────────
    PRIVATE: validLine(line, &date, &strValue)
    ─────────────────────────────────────────────
        split line at '|' using getline
        left  → date
        right → strValue
        if strValue is empty → return ERR_BAD_INPUT
        trim date
        trim strValue
        return OK

    ─────────────────────────────────────────────
    PRIVATE: validDate(date)
    ─────────────────────────────────────────────
        if date length != 10 → return ERR_BAD_DATE
        if date[4] != '-' or date[7] != '-' → return ERR_BAD_DATE
        extract year, month, day as integers
        if month < 1 or month > 12 → return ERR_BAD_DATE
        if day < 1 or day > 31 → return ERR_BAD_DATE
        if date > today → return ERR_BAD_DATE
        if date < 2009-01-02 → return ERR_BAD_DATE
        return OK

    ─────────────────────────────────────────────
    PRIVATE: validValue(strValue)
    ─────────────────────────────────────────────
        if strValue is empty → return ERR_BAD_INPUT
        convert strValue to float
        if value < 0 → return ERR_NEGATIVE
        if value > 1000 → return ERR_TOO_LARGE
        return OK

    ─────────────────────────────────────────────
    PRIVATE: lookup(date)
    ─────────────────────────────────────────────
        key = _database.lower_bound(date)
        if key == end or key->first != date
            --key
        return key->second

    ─────────────────────────────────────────────
    PRIVATE: printError(error, context)
    ─────────────────────────────────────────────
        if error == ERR_BAD_INPUT  → print "Error: bad input => " + context
        if error == ERR_BAD_DATE   → print "Error: bad input => " + context
        if error == ERR_NEGATIVE   → print "Error: not a positive number."
        if error == ERR_TOO_LARGE  → print "Error: too large a number."

    ─────────────────────────────────────────────
    FREE FUNCTION: trim(str)
    ─────────────────────────────────────────────
        start = first non-space character
        end   = last non-space character
        return str.substr(start, end - start + 1)

    ─────────────────────────────────────────────
    MAIN
    ─────────────────────────────────────────────
        if argc != 2 → print error, return 1
        BitcoinExchange btc
        btc.loadDatabase("data.csv")
        btc.processInput(argv[1])*/