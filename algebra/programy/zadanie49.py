import matplotlib.pyplot as plt


def gcd(a, b):
    """
    Greatest common divisor of a, b
    """
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a


def get_coprime_count(n):
    """
    Return a number of coprime pairs a,b where 1 <= a, b <= n
    """
    count = 0
    for a in range(1, n):
        for b in range(1, n):
            if gcd(a, b) == 1:
                count += 1
    return count


def extravagant_function(n):
    return get_coprime_count(n) / (n ** 2)


rng = 200
rng = rng + 1
res = []
for i in range(1, rng):
    res.append(extravagant_function(i))

mean_value = sum(res) / rng

# Find the index of the maximum value
max_index = res.index(max(res))

# Set up the plot
plt.scatter([i for i in range(1, rng)], res, s=10,
            label=r'$f(n)=\left|\{(a,b) \mid 1 \leq a,b \leq n, \text{NWD}(a,b)=1\}\right| \cdot n^{-2}$')
plt.annotate(f'Mean Value\n({len(res)}, {mean_value:.4f})', xy=(len(res) / 2, mean_value),
             xytext=(len(res) / 2, mean_value - 0.2),
             arrowprops=dict(facecolor='black', arrowstyle='->'),
             bbox=dict(boxstyle='round,pad=0.3', edgecolor='red', facecolor='white'))
plt.axhline(y=mean_value, color='red', linestyle='--', label='Mean Value')

# Set axis labels
plt.xlabel('Consecutive Numbers')
plt.ylabel('Extravagant Function')

# Set axis ranges
plt.xlim(1, rng)
plt.ylim(0, 0.8)

# Increase precision
plt.locator_params(axis='x', nbins=10)  # Increase the number of x-axis ticks for better precision

# Add legend
plt.legend()

# Add title
plt.title("Ex.49 Extravagant function over the consecutive numbers.")

# Add grid lines
plt.grid(True, linestyle='--', alpha=0.7)

# Show the plot
plt.show()

# Hipothesis: the limit of this series is:
# ϕ - one over the golden ratio.
# 1/ϕ ~ approx. 0.618 ???

# k < n : NWD = (k,n) = 1 = 1 = phi (n)... <--- check this
