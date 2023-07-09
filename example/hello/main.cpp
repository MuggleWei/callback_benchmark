#include "muggle/c/muggle_c.h"
#include "func.h"
#include "vfunc.h"
#include <chrono>
#include <map>

#define ARR_SIZE 1000000

static fnCallback callbacks[50] = {
	// func_call0,	 func_call1,  func_call2,  func_call3,	func_call4,
	// func_call5,	 func_call6,  func_call7,  func_call8,	func_call9,
	// func_call10, func_call11, func_call12, func_call13, func_call14,
	// func_call15, func_call16, func_call17, func_call18, func_call19,
	// func_call20, func_call21, func_call22, func_call23, func_call24,
	// func_call25, func_call26, func_call27, func_call28, func_call29,
	// func_call30, func_call31, func_call32, func_call33, func_call34,
	// func_call35, func_call36, func_call37, func_call38, func_call39,
	// func_call40, func_call41, func_call42, func_call43, func_call44,
	// func_call45, func_call46, func_call47, func_call48, func_call49,

	callback0,	callback1,	callback2,	callback3,	callback4,	callback5,
	callback6,	callback7,	callback8,	callback9,	callback10, callback11,
	callback12, callback13, callback14, callback15, callback16, callback17,
	callback18, callback19, callback20, callback21, callback22, callback23,
	callback24, callback25, callback26, callback27, callback28, callback29,
	callback30, callback31, callback32, callback33, callback34, callback35,
	callback36, callback37, callback38, callback39, callback40, callback41,
	callback42, callback43, callback44, callback45, callback46, callback47,
	callback48, callback49,
};

static vfnCallback vcallbacks[50] = {
	vfunc_call0,  vfunc_call1,	vfunc_call2,  vfunc_call3,	vfunc_call4,
	vfunc_call5,  vfunc_call6,	vfunc_call7,  vfunc_call8,	vfunc_call9,
	vfunc_call10, vfunc_call11, vfunc_call12, vfunc_call13, vfunc_call14,
	vfunc_call15, vfunc_call16, vfunc_call17, vfunc_call18, vfunc_call19,
	vfunc_call20, vfunc_call21, vfunc_call22, vfunc_call23, vfunc_call24,
	vfunc_call25, vfunc_call26, vfunc_call27, vfunc_call28, vfunc_call29,
	vfunc_call30, vfunc_call31, vfunc_call32, vfunc_call33, vfunc_call34,
	vfunc_call35, vfunc_call36, vfunc_call37, vfunc_call38, vfunc_call39,
	vfunc_call40, vfunc_call41, vfunc_call42, vfunc_call43, vfunc_call44,
	vfunc_call45, vfunc_call46, vfunc_call47, vfunc_call48, vfunc_call49,
};

void run_func(uint32_t *arr)
{
	uint32_t a = 0;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		// callback0(a, i);
		a = callbacks[arr[i]](a, i);
	}
	end = std::chrono::steady_clock::now();

	auto elapsed =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	LOG_INFO("fn use: %llu ns", (unsigned long long)elapsed.count());
}

void run_vfunc(uint32_t *arr)
{
	uint32_t a = 0;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	VFuncBase *vfn = new VFuncImpl();

	begin = std::chrono::steady_clock::now();
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		// vfunc_call0(vfn, a, i);
		a = vcallbacks[arr[i]](vfn, a, i);
	}
	end = std::chrono::steady_clock::now();

	auto elapsed =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	LOG_INFO("vfn use: %llu ns", (unsigned long long)elapsed.count());

	delete vfn;
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
void run_func_with_likely(uint32_t *arr)
{
	uint32_t a = 0;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		if (__builtin_expect(!!(arr[i] == 0), 1)) {
			a = callback0(a, i);
		} else {
			a = callbacks[arr[i]](a, i);
		}
	}
	end = std::chrono::steady_clock::now();

	auto elapsed =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	LOG_INFO("fn with builtin_expect use: %llu ns",
			 (unsigned long long)elapsed.count());
}

void run_vfunc_with_likely(uint32_t *arr)
{
	uint32_t a = 0;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	VFuncBase *vfn = new VFuncImpl();

	begin = std::chrono::steady_clock::now();
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		if (__builtin_expect(!!(arr[i] == 0), 1)) {
			a = vfunc_call0(vfn, a, i);
		} else {
			a = vcallbacks[arr[i]](vfn, a, i);
		}
	}
	end = std::chrono::steady_clock::now();

	auto elapsed =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	LOG_INFO("vfn with builtin_expect use: %llu ns",
			 (unsigned long long)elapsed.count());

	delete vfn;
}
#endif

uint32_t do_something(uint32_t a, uint32_t n)
{
	return a + n;
}

void run_empty(uint32_t *arr)
{
	uint32_t a = 0;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	MUGGLE_UNUSED(arr);
	MUGGLE_UNUSED(a);

	begin = std::chrono::steady_clock::now();
	for (uint32_t i = 0; i < ARR_SIZE; i++) {
		a = do_something(a, i);
	}
	end = std::chrono::steady_clock::now();

	auto elapsed =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	LOG_INFO("vfn use: %llu ns", (unsigned long long)elapsed.count());
}

void run(uint32_t *arr, char flag)
{
	if (flag == 'f') {
		run_func(arr);
	} else if (flag == 'v') {
		run_vfunc(arr);
	} else if (flag == 'F') {
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		run_func_with_likely(arr);
#else
		LOG_ERROR("unsupport __builtin_expect");
#endif
	} else if (flag == 'V') {
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		run_vfunc_with_likely(arr);
#else
		LOG_ERROR("unsupport __builtin_expect");
#endif
	} else if (flag == 'a') {
		run_func(arr);
		run_vfunc(arr);
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		run_func_with_likely(arr);
		run_vfunc_with_likely(arr);
#endif
	} else if (flag == 'e') {
		run_empty(arr);
	} else {
		LOG_ERROR("invalid flags");
		LOG_ERROR(
			"flag options:\n"
			"\tf: call function pointer\n"
			"\tv: call virtual function\n"
			"\tF: [gcc/clang] call function pointer with __builtin_expect\n"
			"\tV: [gcc/clang] call virtual function with __builtin_expect\n"
			"\ta: call function pointer and virtual function\n"
			"\te: call empty");
	}
}

int main(int argc, char *argv[])
{
	muggle_log_complicated_init(LOG_LEVEL_DEBUG, -1, NULL);

	if (argc != 2) {
		LOG_ERROR(
			"Usage: %s <f|v|a|e>\n"
			"\tf: call function pointer\n"
			"\tv: call virtual function\n"
			"\tF: [gcc/clang] call function pointer with __builtin_expect\n"
			"\tV: [gcc/clang] call virtual function with __builtin_expect\n"
			"\ta: call function pointer and virtual function\n"
			"\te: call empty",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	uint32_t *arr = (uint32_t *)malloc(sizeof(uint32_t) * ARR_SIZE);
	FILE *fp = fopen("data.bin", "rb");
	if (fp == NULL) {
		LOG_ERROR("failed find data file, ensure already run example_gen_rand");
		exit(EXIT_FAILURE);
	}
	size_t nbytes = fread(arr, sizeof(uint32_t), ARR_SIZE, fp);
	if (nbytes != ARR_SIZE) {
		LOG_ERROR("failed read data, nbytes=%u", nbytes);
		exit(EXIT_FAILURE);
	}
	fclose(fp);

	run(arr, argv[1][0]);
	// for (int i = 0; i < 16; i++) {
	//     run(arr, argv[1][0]);
	// }

	free(arr);

	return 0;
}
