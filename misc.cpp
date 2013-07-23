#include "misc.hpp"

QString removeTrailingZeros(QString s) {
    /* . as decimal separator is hardcoded */
    int start = s.indexOf('.');
    if (start != -1) {
        int i = s.size() - 1;
        while (i >= start && (s[i] == '0' ||
                s[i] == '.')) {
            --i;
        }
        s.chop(s.size()-1-i);
    }
    return s;
}
