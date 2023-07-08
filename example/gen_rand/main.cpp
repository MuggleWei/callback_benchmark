#include "muggle/c/muggle_c.h"
#include <cstdio>
#include <map>

#define ARR_SIZE 1000000

int main()
{
	muggle_log_complicated_init(LOG_LEVEL_DEBUG, -1, NULL);

	srand((unsigned int)time(NULL));

	std::map<uint32_t, uint32_t> cnt_dict;

	uint32_t *arr = (uint32_t *)malloc(sizeof(uint32_t) * ARR_SIZE);
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		uint32_t r = 0;
		r = rand() % (30000 + 47);
		// r = rand() % 50;

		if (r < 10000) {
			arr[i] = 0;
		} else if (r >= 10000 && r < 20000) {
			arr[i] = 1;
		} else if (r >= 20000 && r < 30000) {
			arr[i] = 2;
		} else {
			arr[i] = r - 30000 + 3;
		}

		if (cnt_dict.find(arr[i]) != cnt_dict.end()) {
			cnt_dict[arr[i]]++;
		} else {
			cnt_dict[arr[i]] = 0;
		}
	}

	uint32_t count = 0;
	for (auto it = cnt_dict.begin(); it != cnt_dict.end(); it++) {
		if (it->first < 3) {
			LOG_INFO("%u: %u", it->first, it->second);
		} else {
			count += it->second;
		}
	}
	LOG_INFO("other: %u", count);

	FILE *fp = fopen("data.bin", "wb");
	fwrite(arr, sizeof(uint32_t), ARR_SIZE, fp);
	fclose(fp);

	free(arr);

	return 0;
}
