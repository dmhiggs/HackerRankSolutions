#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <string.h>
using namespace std;

//testing out understanding with smaller sets
int bitsofx(int n, int s, int p, int q) {
    int uniques = 0;
    const uint bits = 16; //seems to break if bits > 28
    const ulong mod = static_cast<ulong>(pow(2,bits-1));
    // bitset<2147483648> bittracking;
    uint intbits[mod/bits];
    memset(intbits, 0, sizeof(intbits));//sizeof(uint)*mod/bits);

    vector<bitset<bits>> v(mod/bits);

    uint x = s % mod;
    for (int i = 0; i < n; i++) {
        // cout << "x=" << x << endl;
        //find where x is in intbits --> what index then what bit in index
        // check if it's 0 --> set and increment uniques
        uint index = x/bits;
        uint bit = x%bits;
        bitset<bits> b = v[index];
        // if (b[bit]==0) {
        if ((intbits[index] & (1 << bit))==0) {
            // put the changed bits back
            intbits[index] |= (1 << bit);
            uniques++;
            // cout << "x=" << x << endl;
        }

        // cout << "math " << p*x << "+" << q << " %" << mod << endl;
        x = (p*x+q) % mod;
        // while (x >= mod) x = (p*x+q) % mod; //for smaller bit sizes
    }
    return uniques;
}

//booth's algorithm to avoid using p*x+q
void mathBitsMult(uint64_t *x, uint32_t p, uint32_t q) {
    //math it out
    int last = 0;

    //x * p
    //step 0 initialize
    //0, upper 32 bits 0, x 32 bits, last 0
    for (int i = 0; i < 32; i++) {
        // cout << "x is " << *x << endl;
        //if last two are 00 do nothing
        //if last two are 01 add p
        //if last two are 10 add -p
        //if last two are 11 do nothing
        uint64_t ppos = p;
        while (ppos != 0 && ((*x & (1U << 0))==0 && last == 1)) {
            //add
            // bitset<8> x1(*x);
            // cout << "last is 1, x is " << x1 << endl;
            int carry = *x & (ppos << 32);
            *x = *x ^ (ppos << 32);
            ppos = carry << 1;
            ppos = ppos >> 32;
        }

        uint64_t pneg = ~p;
        ppos = 1;
        while (ppos != 0) {
            int carry = pneg & ppos;
            pneg ^= ppos;
            ppos = carry << 1;
        }
        while (pneg != 0 && ((*x & (1U << 0))==1 && last == 0)) {
            //go through each left side bit to add -p (sub)
            int carry = *x & (pneg << 32);
            *x = *x ^ (pneg << 32);
            pneg = carry << 1;
            pneg = pneg >> 32;
        }
        if ((*x & (1U << 0))==1 && last == 0) {
            *x = ~(*x);
            ppos = 1;
            while (ppos != 0 && ((*x & (1U << 0))==1 && last == 0)) {
                int carry = *x & ppos;
                *x ^= ppos;
                ppos = carry << 1;
            }
        }
            // bitset<64> x1(*x);
            // cout << "last is " << last << ", x is " << x1 << ", x is " << *x << endl;

        //save last bit into last
        last = (*x & (1U << 0));
        //shift right
        *x = (*x >> 1);
    }

    //x + q
    while (q != 0) {
        int carry = *x & q;
        *x ^= q;
        q = carry << 1;
    }
}

//TEST CASES and expected results
//100000000 1232077670 126810854 1536183938
//26
// 100000000 2065188356 657733125 1636844041
// 100000000
//100000000 569099406 1607140150 823906344
//31
// 10 1972857628 499841161 437173653
// 10
//10000 573272257 859433109 1894136138
//10000
// 10000000 658061970 695098531 1430548937
// 10000000

//100000000 923092883 976061291 1205350525
//100000000
// 100000000 1506922183 1236189611 306853238
// 100000000
//100000000 831602480 704408287 1134515747
//100000000
// 100000000 178349423 584642695 2037647927
// 100000000
//100000000 2065188356 657733125 1636844041
//100000000


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

        //a(n) = (a(n-1)*p+q) % (1U << 31)
        //a(0) = s % (1U << 31)
        //a(3) = (((s)p+q)p+q)p+q = ((s*p+q)p+q)p+q = (s*p^2+pq+q)p+q = s*p^3+p^2q+pq+q
        //a(n) = s * p^n + p^(n-1)q + ... + pq + q
        //a(n) = s * p^n + q(p^(n-1) + p^(n-2) + ... + p + 1)
                //SUMMATION of p^(n-1) from 0 to n-1 = (p^n - 1)/(p - 1), where p != 1
        //a(n) = s * p^n + q * (p^n - 1)/(p - 1) --> if p!=1
        //a(n) = s + q*n --> if p==1 -->basically y=mx+b, so linear in some cases
        //this math was probably unnecessary

    uint32_t n, s, p, q;
    cin >> n >> s >> p >> q;
    uint32_t uniques = 0;

    // code for testing with smaller numbers...with less bits...
    // uniques = bitsofx(n, s, p, q);
    // if (uniques > 0) {
    //     cout << uniques;
    //     return 0;
    // }

    uint64_t mod = static_cast<uint64_t> (pow(2,31));
    int *intbits = new int[mod/32];
    memset(intbits, 0, sizeof(int)*mod/32);

    //f(x)=p^x * s + q * (p^x - 1)/(p - 1), when p != 1
    //f(x)=s + q*n, when p==1

    uint64_t x = s % mod;
    for (int i = 0; i < n; i++) {
        uint32_t index = x/32;
        uint32_t bit = x%32;
        if ((intbits[index] & (1U << bit))==0) {
            intbits[index] |= (1U << bit);
            uniques++;
        }
        s = x;
        x = p*x+q;// % mod; //oh my god why is this math causing a timeout
        // cout << x << endl;
        // mathBitsMult(&x, p, q); //still causes timeout with larger n
        x = x % mod;
        if (x == s) break; //if get same number, then will continue getting same number
    }

    cout << uniques << endl;
    return 0;
}