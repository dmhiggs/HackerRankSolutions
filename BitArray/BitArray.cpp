#include <iostream>
#include <string.h>
using namespace std;

//100000000 831602480 704408287 1134515747 -- test case 6
//100000000 -- expected result

int main() {
    uint64_t n, s, p, q;
    cin >> n >> s >> p >> q;

    uint64_t mod = (1U<<31);
    int *intbits = new int[mod/32];
    memset(intbits, 0, sizeof(int)*mod/32);

    s = s % mod;
    for (int i = 0; i < n; i++) { // n >= 91015409 timesout for testcase6 on hackerrank
        uint32_t index = s/32;
        uint32_t bit = s%32;
        if ((intbits[index] & (1U << bit))!=0) {
            //if it hits the same number then it's starting to repeat a pattern
            cout << i << endl;
            return 0;
        }
        intbits[index] |= (1U << bit);

        s = (p*s+q) % mod; //oh my god why is this math causing a timeout
    }

    //if gets through loop without returning then n uniques
    cout << n << endl;
    return 0;
}
