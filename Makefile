GCC = gcc
CFLAGS = -g -Wall -Wextra -Wshadow -std=c11 -Wpedantic
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=
BUILD_DIR = out
# BIGINT_SRCS = bigint_calculator.c \
# 				bigint_parser.c \
# 				bigint_arithmetic.c \
# 				bigint_calculator_test.c
# BIGINT_OBJS:=$(BIGINT_SRCS:.c=.o)
BIGINT_OBJS = ${BUILD_DIR}/bigint_calculator.o ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_calculator_test.o


biginttest: bigint_test
	./${BUILD_DIR}/bigint_test

bigintcalculator: bigint_calculator
	./${BUILD_DIR}/bigint_calculator

bigintparser: bigint_parser
	./${BUILD_DIR}/$^

bigintarithmetic: bigint_arithmetic
	./${BUILD_DIR}/$^
	

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
	rm -f outputs/* logs/* *.o ${BUILD_DIR}/*