from fractions import Fraction
r = Fraction(input())
N = int(input())
ans = (r - Fraction("1e-100")).limit_denominator(N)
print(*ans.as_integer_ratio())