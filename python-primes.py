from sys import argv

def is_prime(n):
    factors = 0
    for i in range(2, n):
        if n % i == 0:
            factors += 1
    return factors == 0

limit = int(argv[1])
total = 0

for i in range(2, limit):
    if is_prime(i):
        total += 1

print("Found", total, "primes between 2 and", limit)