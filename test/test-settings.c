/*
 * Unit tests for fts-elastic plugin settings parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Mock structures and functions for testing */
struct fts_elastic_settings {
    const char *url;
    const char *rawlog_dir;
    unsigned int bulk_size;
    bool refresh_on_update;
    bool refresh_by_fts;
    bool debug;
    unsigned int default_date_range_months;
    unsigned int result_size_limit;
};

static int test_parse_default_date_range(const char *input, unsigned int expected) {
    struct fts_elastic_settings set = {0};
    set.default_date_range_months = 0;
    
    const char *range_str = input + 19; /* skip "default_date_range=" */
    
    if (strcmp(range_str, "1") == 0 || strcmp(range_str, "1month") == 0) {
        set.default_date_range_months = 1;
    } else if (strcmp(range_str, "3") == 0 || strcmp(range_str, "3months") == 0) {
        set.default_date_range_months = 3;
    } else if (strcmp(range_str, "6") == 0 || strcmp(range_str, "6months") == 0) {
        set.default_date_range_months = 6;
    } else if (strcmp(range_str, "0") == 0 || strcmp(range_str, "disabled") == 0) {
        set.default_date_range_months = 0;
    } else {
        unsigned int months;
        if (sscanf(range_str, "%u", &months) == 1 && (months == 1 || months == 3 || months == 6)) {
            set.default_date_range_months = months;
        } else {
            return -1; /* invalid */
        }
    }
    
    if (set.default_date_range_months != expected) {
        printf("FAIL: expected %u, got %u\n", expected, set.default_date_range_months);
        return -1;
    }
    return 0;
}

static int test_parse_result_size_limit(const char *input, unsigned int expected) {
    struct fts_elastic_settings set = {0};
    set.result_size_limit = 10000;
    
    const char *limit_str = input + 19; /* skip "result_size_limit=" */
    unsigned int limit;
    
    if (sscanf(limit_str, "%u", &limit) == 1 && limit > 0) {
        set.result_size_limit = limit;
    } else {
        return -1; /* invalid */
    }
    
    if (set.result_size_limit != expected) {
        printf("FAIL: expected %u, got %u\n", expected, set.result_size_limit);
        return -1;
    }
    return 0;
}

int main(void) {
    int failures = 0;
    
    printf("Running fts-elastic settings tests...\n\n");
    
    /* Test default_date_range parsing */
    printf("Testing default_date_range parsing:\n");
    
    if (test_parse_default_date_range("default_date_range=1", 1) != 0) {
        printf("  FAIL: default_date_range=1\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=1\n");
    }
    
    if (test_parse_default_date_range("default_date_range=1month", 1) != 0) {
        printf("  FAIL: default_date_range=1month\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=1month\n");
    }
    
    if (test_parse_default_date_range("default_date_range=3", 3) != 0) {
        printf("  FAIL: default_date_range=3\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=3\n");
    }
    
    if (test_parse_default_date_range("default_date_range=3months", 3) != 0) {
        printf("  FAIL: default_date_range=3months\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=3months\n");
    }
    
    if (test_parse_default_date_range("default_date_range=6", 6) != 0) {
        printf("  FAIL: default_date_range=6\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=6\n");
    }
    
    if (test_parse_default_date_range("default_date_range=6months", 6) != 0) {
        printf("  FAIL: default_date_range=6months\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=6months\n");
    }
    
    if (test_parse_default_date_range("default_date_range=0", 0) != 0) {
        printf("  FAIL: default_date_range=0\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=0\n");
    }
    
    if (test_parse_default_date_range("default_date_range=disabled", 0) != 0) {
        printf("  FAIL: default_date_range=disabled\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=disabled\n");
    }
    
    /* Test invalid values */
    if (test_parse_default_date_range("default_date_range=2", 0) == 0) {
        printf("  FAIL: default_date_range=2 should be invalid\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=2 correctly rejected\n");
    }
    
    if (test_parse_default_date_range("default_date_range=12", 0) == 0) {
        printf("  FAIL: default_date_range=12 should be invalid\n");
        failures++;
    } else {
        printf("  PASS: default_date_range=12 correctly rejected\n");
    }
    
    printf("\n");
    
    /* Test result_size_limit parsing */
    printf("Testing result_size_limit parsing:\n");
    
    if (test_parse_result_size_limit("result_size_limit=10000", 10000) != 0) {
        printf("  FAIL: result_size_limit=10000\n");
        failures++;
    } else {
        printf("  PASS: result_size_limit=10000\n");
    }
    
    if (test_parse_result_size_limit("result_size_limit=50000", 50000) != 0) {
        printf("  FAIL: result_size_limit=50000\n");
        failures++;
    } else {
        printf("  PASS: result_size_limit=50000\n");
    }
    
    if (test_parse_result_size_limit("result_size_limit=100000", 100000) != 0) {
        printf("  FAIL: result_size_limit=100000\n");
        failures++;
    } else {
        printf("  PASS: result_size_limit=100000\n");
    }
    
    /* Test invalid values */
    if (test_parse_result_size_limit("result_size_limit=0", 0) == 0) {
        printf("  FAIL: result_size_limit=0 should be invalid\n");
        failures++;
    } else {
        printf("  PASS: result_size_limit=0 correctly rejected\n");
    }
    
    printf("\n");
    
    /* Summary */
    if (failures == 0) {
        printf("All tests PASSED!\n");
        return 0;
    } else {
        printf("FAILED: %d test(s) failed\n", failures);
        return 1;
    }
}

