int *problem1(int *a, int alen, int *b, int blen, int *rlen) {
    int *result = malloc(sizeof(int)*(alen+blen)); // O(N+M) space
    int ai = 0;
    int bi = 0;
    int i = 0;
    while (ai < alen || bi < blen) {        // sources not empty, O(N+M) time
        if (bi == blen || a[ai] < b[bi]) {
            if (a[ai] != result[i-1]) {     // not a dupe, O(1) time
                result[i++] = a[ai];
            }
            ++ai;
        } else {
            if (b[bi] != result[i-1]) {
                result[i++] = b[bi];
            }
            ++bi;
        }
    }
    *rlen = i;                              // error?
    return result;
}

int problem2(char *cal, int callen, int pto) {
    int maxVacation = 0;
	for (int i = 0; i < callen-pto; ++i) {  // O(N)
        int numHolidays = 0;
        int numPto = 0;
        for (int j = i; j < callen; ++j) {  // best: O(K+H), worst: O(N)
            if (cal[i] == 'H') {
                ++numHolidays;
            } else {
                if (numPto < pto) {
                    ++numPto;
                } else {
                    int numVacation = numPto + numHolidays;
                    if (numVacation > maxVacation) {
                        maxVacation = numVacation;
                    }
                    break;
                }
            }
        }
        // missing:
        //int numVacation = numPto + numHolidays;
        //if (numVacation > maxVacation) {
        //    maxVacation = numVacation;
        //}
    }
    return maxVacation;
}

int problem2_alt(char *cal, int callen, int pto) {
    int *vacation = alloca(sizeof(int)*callen);

    int ptoRemaining = pto;
    for (int i = 0; i < callen; ++i) {
        if (cal[i] == 'H') {
            continue;
        } else {
            if (ptoRemaining == 0) {
                vacation[0] += i;
                break;
            }
            --ptoRemaining;
        }
    }
    for (int i = 1; i < callen; ++i) {     // O(N)
        for (int j = i; j < callen; ++j) { // O(K+H)
            if (cal[j] == 'H') {
                continue;
            } else {
                vacation[i] = vacation[i-1] + (j-i);
                break;
            }
        }
    }

    int maxVacation = 0;
    for (int i = 0; i < callen; ++i) {
        if (vacation[i] > maxVacation) {
            maxVacation = vacation[i];
        }
    }

    return maxVacation;
}

// todo: try sorted intervals O(logN)?
// todo: try hashed intervals O(1)?