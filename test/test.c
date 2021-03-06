/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (c) 2020 Brett Sheffield <bacs@librecast.net> */

#include "test.h"

int fails = 0;

void vfail_msg(char *msg, va_list argp)
{
	char *b;
	b = malloc(_vscprintf(msg, argp) + 1);
	vsprintf(b, msg, argp);
	printf("\n            %-70s", b);
	free(b);
	fails++;
}

void fail_msg(char *msg, ...)
{
	va_list argp;
	va_start(argp, msg);
	vfail_msg(msg, argp);
	va_end(argp);
}

void test_assert(int condition, char *msg, ...)
{
	if (!condition) {
		va_list argp;
		va_start(argp, msg);
		vfail_msg(msg, argp);
		va_end(argp);
	}
}

void test_strcmp(char *str1, char *str2, char *msg, ...)
{
	if (str1 == NULL || str2 == NULL || strcmp(str1, str2)) {
		va_list argp;
		va_start(argp, msg);
		vfail_msg(msg, argp);
		va_end(argp);
	}
}

void test_strncmp(char *str1, char *str2, size_t len, char *msg, ...)
{
	if (str1 == NULL || str2 == NULL || strncmp(str1, str2, len)) {
		va_list argp;
		va_start(argp, msg);
		vfail_msg(msg, argp);
		va_end(argp);
	}
}

void test_expect(char *expected, char *got)
{
	test_strcmp(expected, got, "expected: '%s', got: '%s'", expected, got);
}

void test_expectn(char *expected, char *got, size_t len)
{
	test_strncmp(expected, got, len, "expected: '%s', got: '%s'", expected, got);
}

void test_log(char *msg, ...)
{
	char *b;
	va_list argp;
	va_start(argp, msg);
	b = malloc(_vscprintf(msg, argp) + 1);
	vsprintf(b, msg, argp);
	fprintf(stderr, "%s\n", b);
	va_end(argp);
	free(b);
}

void test_name(char *str, ...)
{
	char *b;
	va_list argp;
	va_start(argp, str);
	b = malloc(_vscprintf(str, argp) + 1);
	vsprintf(b, str, argp);
	printf("%-70s", b);
	test_log("  (%s)", b);
	va_end(argp);
	free(b);
}

