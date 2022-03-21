from random import randrange


def gen_test(n, m, i, answer):  # answer = 0 - No; answer = 1 - Cycle or chain
    st = set()
    f = open(f'tests/{n}-{i}-{answer}.txt', 'w')
    f.write(f'{n}\n')
    print('            ', n, m, i, answer)
    if m == max_m(n):
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if i == j:
                    f.write('0 ')
                else:
                    f.write('1 ')
            f.write('\n')
    else:
        last = -1

        degree = {}

        for v in range(1, n + 1):
            degree[v] = 0

        for i in range(m):
            if last == -1 or not answer:
                a = randrange(1, n + 1)
            else:
                a = last
            b = randrange(1, n + 1)

            time = 0

            while a == b or (a, b) in st or (b, a) in st or (answer and degree[b] == n - 2):
                # print(a == b, (a, b) in st, (b, a) in st, (answer and degree[b] == n - 2))
                b = randrange(1, n + 1)
                time += 1
                if time > n:
                    f.close()
                    return False


            st.add((a, b))

            last = b

            degree[b] += 1

        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if (i, j) in st or (j, i) in st:
                    f.write('1 ')
                else:
                    f.write('0 ')
            f.write('\n')

    f.close()
    return True


def max_m(n):
    n -= 1
    if n % 2 == 0:
        return (n + 1) * (n // 2)
    return (n + 1) * (n // 2) + n // 2 + 1


if __name__ == '__main__':
    for n in range(410, 1001, 10):
        print(n)
        k = max_m(n) // 5
        print('k = ', k, 'max_n = ', max_m(n))
        for i in range(5):
            print('    ', i)
            for ans in range(2):
                print('        ', ans)
                while not gen_test(n, k * (i + 1), i + 1, ans):
                    pass
