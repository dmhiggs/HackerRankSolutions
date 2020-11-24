#include <iostream>
// #include <string.h> //for memset
using namespace std;
#define mod ~(1u<<31)
#define size (1u<<26)
// #define getbit(a,b) (a & (1u << b))
// #define setbit(a,b) ((a & (1u << b)) ? 0 : (a |= (1u << b)))

int main() {
    uint32_t n, s, p, q;
    cin >> n >> s >> p >> q;

    int *intbits = new int[size];
    for (int i= 0; i < size; i++) intbits[i] = 0;
    // memset(intbits, 0, sizeof(int)*size);
    // uint32_t intbits[size] = {0};

    s &= mod;
    for (int i = 0; i < n && i < 80000000; i++) { // n < 92215409 after get rid of / & %
        uint32_t bits = s&31;
        uint32_t index = s>>5;

        //check if hit number before
        if ((intbits[index] ^= (1u << bits)) == 0) {
            //if it hits the same number then it's starting to repeat a pattern
            cout << i;
            return 0;
        }

        s = ((p*s)+q) & mod;
    }

    
    //if gets through loop without returning then n uniques
    cout << n;
    delete[] intbits;
    return 0;
}
