BUILD_DIR = out
LOG_DIR = logs
GCC = gcc
CFLAGS = -g -Wall -Wextra -Wshadow -std=c11 -fprofile-arcs -ftest-coverage
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=${LOG_DIR}/
# BIGINT_SRCS = bigint_calculator.c \
# 				bigint_parser.c \
# 				bigint_arithmetic.c \
# 				bigint_calculator_test.c
# BIGINT_OBJS:=$(BIGINT_SRCS:.c=.o)
BIGINT_OBJS = ${BUILD_DIR}/bigint_calculator.o ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_calculator_test.o

run: bigint
	$(VALGRIND)bigint.log ./${BUILD_DIR}/bigint

bigint: ${BUILD_DIR}/bigint_calculator.o ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_main.o
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm

bigintcalculator: bigint_calculator
	./${BUILD_DIR}/bigint_calculator

bigintparser: bigint_parser
	./${BUILD_DIR}/$^

bigintarithmetic_test: bigint_arithmetic
	$(VALGRIND)bigint_arithmetic_test.log ./${BUILD_DIR}/$^
	gcov ./${BUILD_DIR}/$^
	

bigint_calculator: $(BIGINT_OBJS)
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm

bigint_parser: ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_parser_test.o
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm

bigint_arithmetic: ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_arithmetic_test_cmocka.o
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm -lcmocka


# if an object ﬁle is needed, compile the corresponding .c ﬁle
${BUILD_DIR}/%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${LOG_DIR}/* ${BUILD_DIR}/* *.o *.gcov