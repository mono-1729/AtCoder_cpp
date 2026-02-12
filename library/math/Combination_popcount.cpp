// m桁の数(2進数表記)のうち、1のビットがk個のものを列挙してリストを返すやつ
std::vector<uint64_t> enumerate_popcount_k(int k, int m) {
    if (m < 0 || m > 64) throw std::invalid_argument("m out of range");
    if (k < 0 || k > m)  throw std::invalid_argument("k out of range");

    std::vector<uint64_t> vec;
    if (k == 0) { vec.push_back(0); return vec; }

    uint64_t now = (k == 64 ? ~0ULL : ((1ULL << k) - 1)); 
    uint64_t limit = (m == 64 ? ~0ULL : (1ULL << m));

    while (now && now < limit) {
        vec.push_back(now);
        uint64_t nxt = next_same_popcount(now);
        if (nxt == 0 || nxt >= limit) break;
        now = nxt;
    }
    return vec;
}