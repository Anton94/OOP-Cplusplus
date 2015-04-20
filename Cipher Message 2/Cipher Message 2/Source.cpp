#include <cstdio>
#include <cstring>
#include <vector>
#include "HashMap.h"

using namespace std;

int n, k;
char str[MAX];

int main(void) {
	FILE* in = stdin; FILE* out = stdout;
	///    in = fopen("1706.in", "rt");

	fscanf(in, "%d", &k);
	fscanf(in, "%s", str); n = (int)strlen(str);
	for (int i = 0; i < n; i++)
		str[n + i] = str[i];

	basePower[0][0] = basePower[1][0] = basePower[2][0] = 1;
	for (int i = 1; i < MAX; i++) {
		basePower[0][i] = ((long long)basePower[0][i - 1] * BASE1) % MOD1;
		basePower[1][i] = ((long long)basePower[1][i - 1] * BASE2) % MOD2;
		basePower[2][i] = ((long long)basePower[2][i - 1] * BASE3) % MOD3;
	}

	int ans = 0;
	HashMap <int> hmap;
	// start == 0
	for (int i = 0; i < k; i++) {
		Hash hash;
		for (int c = i; c < k; c++) {
			hash.append(str[c]);
			/*if (!hmap.contains(hash) || hmap.get(hash) == 0) {
				hmap.insert(hash, 1);
				ans++;
			}
			else {
				hmap.get(hash)++;
			}*/

			if(!hmap.contains(hash)) {
				hmap.insert(hash, 1);
				ans++;
			}
			else if (hmap.get(hash) == 0)
			{
				hmap.get(hash)++;
				ans++;
			}
			else {
				hmap.get(hash)++;
			}
		}
	}
	fprintf(out, "%d", ans);

	for (int start = 1; start < n; start++) {
		// Remove all substrings, starting at index start - 1.
		Hash hash;
		for (int len = 1; len <= k; len++) {
			hash.append(str[start - 1 + len - 1]);
			hmap.get(hash)--;
			/*if (hmap.get(hash) == 0)
				ans--;*/
			if (hmap.get(hash) == 0)
			{
				ans--;
				hmap.remove(hash);
			}
		}

		// Add all new substrings, ending in index start + k - 1
		hash = Hash();
		for (int i = start; i < start + k; i++) {
			hash.append(str[i]);
		}
		// Starting with the string with length k ending in index start + k - 1, remove characters
		// one by one
		for (int i = start; i < start + k; i++) {
			/*if (!hmap.contains(hash) || hmap.get(hash) == 0) {
				hmap.insert(hash, 1);
				ans++;
			}
			else {
				hmap.get(hash)++;
			}*/
			
			if (!hmap.contains(hash)) {
				hmap.insert(hash, 1);
				ans++;
			}
			else if (hmap.get(hash) == 0)
			{
				hmap.get(hash)++;
				ans++;
			}
			else {
				hmap.get(hash)++;
			}
			hash.removeFront(str[i]);
		}
		fprintf(out, " %d", ans);
	}
	//fprintf(out, "\n");
	return 0;
}