#include "src/unity.h"
#include "../sudoku.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}



void test_function_is_existingInSubunit(void)
{   
    int row = 2;
    int col = 4;
    int count = 0;

    while (count < 9){

        TEST_ASSERT(is_existingInSubunit(row,col,count) == 1);
        count++;
    }
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_is_existingInSubunit);
    return UNITY_END();
}