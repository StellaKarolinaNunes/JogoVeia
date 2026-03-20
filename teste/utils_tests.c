#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "../utils.h"

void test_visible_strlen() {
    assert(visible_strlen("teste") == 5);
    assert(visible_strlen("\033[31mteste\033[0m") == 5);
}
