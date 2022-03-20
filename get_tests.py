from random import randrange


def gen_test(n, m):
    st = set()
    f = open(f'tests/{n}-{m}.txt', 'w')
    f.write(f'{n} {m}\n')

    if m == max_m(n):
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if i == j:
                    f.write('0 ')
                else:
                    f.write('1 ')
            f.write('\n')
    else:
        for i in range(m):
            a = randrange(1, n + 1)
            b = randrange(1, n + 1)
            while a == b or (a, b) in st or (b, a) in st:
                b = randrange(1, n + 1)

            st.add((a, b))

        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if (i, j) in st or (j, i) in st:
                    f.write('1 ')
                else:
                    f.write('0 ')
            f.write('\n')

    f.close()


def max_m(n):
    if n % 2 == 0:
        return (n + 1) * (n // 2)
    return (n + 1) * (n // 2) + n // 2 + 1


if __name__ == '__main__':
    for n in range(100, 1001, 100):
        print(n)
        for m in range(max_m(n) // 5, max_m(n) + 1, max_m(n) // 5):
            print(m)
            gen_test(n, m)
